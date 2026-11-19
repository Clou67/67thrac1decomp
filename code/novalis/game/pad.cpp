#include "common.h"
#include "pad.h"
#include "fastfunc.h"
#include "moby.h"

extern "C" {
int scePad2LinkDriver(void);
int scePad2Init(int mode);
int scePad2CreateSocket(Pad2SocketParam *param, void *buffer);
int scePad2GetState(int socket);
int scePad2GetButtonProfile(int socket, unsigned char *profile);
int scePad2GetActuatorProfile(int socket, unsigned char *profile);
int scePad2Read(int socket, unsigned char *data);
}

#define PAD2_SOCKET_MODE 2
#define PAD2_STATE_READY 1

// A profile whose four bytes are all set belongs to a DualShock 2.
#define PAD_PROFILE_NONE 0xFFFFFFFF
#define PAD_TERM_ID_DUALSHOCK2 0x79

// The profile calls report no more than this many entries.
#define PAD_PROFILE_MAX 5

// Stick bytes are centered on 0x7F and ignored inside the dead zone.
#define PAD_STICK_COUNT 4
#define PAD_STICK_CENTER 0x7F
#define PAD_STICK_DEAD_ZONE 0x30
#define PAD_STICK_RANGE 76

// Buttons from the sixth byte on report pressure from 0 to 0xFF.
#define PAD_PRESSURE_SCALE 0.003921569f
#define PAD_PRESSURE_FIRST 4
#define PAD_DATA_STICK_BYTES 6
#define PAD_DATA_PRESSURE_BYTES 18

// Buttons the HUD gives up while it has the stick.
#define PAD_HUD_DIVERT_ACTION_BUTTONS (PAD_TRIANGLE | PAD_CIRCLE | PAD_UP | PAD_DOWN)
#define PAD_HUD_MENU_BUTTONS (PAD_SELECT | PAD_START)

// A stick push counts as a flick when it jumps from rest to nearly full within a few frames.
#define PAD_FLICK_ENGAGED 0.9f
#define PAD_FLICK_RESTING 0.25f
#define PAD_FLICK_FRAMES 4
#define PAD_FLICK_TURN 0.9599311f
#define PAD_FLICK_TURN_FRAMES 5

void InitPadRing(void)
{
    PAD *pad = &padState;

    pad->ringIndex = 0;
    pad->ringValidSize = 0;
}

#ifdef ALLOW_NON_MATCHING
int PadRingBitsOn(int bits, int frames, int *frame)
{
    PAD *pad = &padState;
    int *ring = pad->bitsOnRing;
    int *held;
    int age;

    if (frames > pad->ringValidSize)
        frames = pad->ringValidSize;

    frames++;
    for (age = 1; age < frames; age++) {
        held = &ring[(pad->ringIndex - age + PAD_RING_LENGTH) % PAD_RING_LENGTH];

        if (*held & bits) {
            if (frame != 0)
                *frame = age - 1;

            return *held & bits;
        }
    }

    return 0;
}
#else
INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pad", PadRingBitsOn);
#endif

int PadRingCoincidentBitsOn(int firstBits, int secondBits, int frames, int window)
{
    int frame[2];
    int coincident = 0;

    if (PadRingBitsOn(firstBits, frames, &frame[0])) {
        if (PadRingBitsOn(secondBits, frames, &frame[1]))
            coincident = FastAbsI(frame[0] - frame[1]) < window;
    }

    return coincident;
}

float PadRingAng(int frames)
{
    PAD *pad = &padState;

    if (frames > pad->ringValidSize)
        frames = pad->ringValidSize;

    return pad->analogMagRing[(pad->ringIndex - frames + PAD_RING_LENGTH) % PAD_RING_LENGTH];
}

TEXT_PADDING(0x27BD0040, 0x00000000);

void pad_Init(void)
{
    scePad2LinkDriver();
    scePad2Init(0);

    PadSocketParam.mode = PAD2_SOCKET_MODE;
    PadSocketParam.enabled = 0;
    padState.socket = scePad2CreateSocket(&PadSocketParam, &padState);
    PadSocketParam.mode = PAD2_SOCKET_MODE;
    PadSocketParam.enabled = 1;

    padState.phase = PAD_PHASE_PROFILE;
    padState.state = 0;
}

void UpdatePadEx(PAD *pad)
{
    unsigned char data[0x40];
    int length;
    int index;

    pad->bits = 0;
    pad->bitsPrev = pad->unmaskedBits;
    pad->digitalBitsPrev = pad->digitalBits;
    pad->digitalBits = 0;

    pad->state = scePad2GetState(pad->socket);
    if (pad->state == PAD2_STATE_READY) {
        switch (pad->phase) {
        case PAD_PHASE_PROFILE:
            length = scePad2GetButtonProfile(pad->socket, data);
            if (*(unsigned int *)data == PAD_PROFILE_NONE)
                pad->term_id = PAD_TERM_ID_DUALSHOCK2;
            else
                pad->term_id = 0;

            if (length < PAD_PROFILE_MAX) {
                for (index = 0; index < length; index++)
                    pad->profile[index] = data[index];

                pad->phase = PAD_PHASE_READY;
            } else {
                length = 0;
                pad->phase = PAD_PHASE_UNSUPPORTED;
            }

            for (index = length; index < PAD_PROFILE_SIZE; index++)
                pad->profile[index] = data[index];

            length = scePad2GetActuatorProfile(pad->socket, data);
            if (length < PAD_PROFILE_MAX) {
                for (index = 0; index < length; index++)
                    pad->vib_profile[index] = data[index];
            } else
                length = 0;

            for (index = length; index < PAD_PROFILE_SIZE; index++)
                pad->vib_profile[index] = data[index];

            ClearPadInput(pad);
            break;

        case PAD_PHASE_READY:
            length = scePad2Read(pad->socket, data);
            ProcessPadInput(pad, data, length);
            break;

        case PAD_PHASE_UNSUPPORTED:
            ClearPadInput(pad);
            break;
        }
    } else {
        ClearPadInput(pad);
        pad->phase = PAD_PHASE_PROFILE;
    }

    pad->act_direct[0] = 0;
    pad->act_direct[1] = 0;
}

void ClearPadInput(PAD *pad)
{
    int index;

    pad->digitalBits = 0;
    pad->bits = 0;
    pad->bitsOn = 0;
    pad->bitsOff = 0;
    pad->handsOffStick = pad->handsOff = 1;
    pad->digitalBitsOn = 0;
    pad->digitalBitsOff = 0;
    pad->hudBits = 0;
    pad->hudBitsOn = 0;
    pad->hudBitsOff = 0;
    pad->useAnalog = 0;

    for (index = 0; index < PAD_ANALOG_COUNT; index++) {
        pad->analog[index] = 0.0f;
        pad->hudAnalog[index] = 0.0f;
    }
}

#ifdef ALLOW_NON_MATCHING
static inline void MirrorPadBits(int &bits)
{
    if (bits & PAD_LEFT)
        bits = (bits & ~PAD_LEFT) | PAD_RIGHT;
    else if (bits & PAD_RIGHT)
        bits = (bits & ~PAD_RIGHT) | PAD_LEFT;
}

void ProcessPadInput(PAD *pad, unsigned char *data, int length)
{
    Vec4 stick;
    float stickLength;
    float stickAngle;
    int index;
    int age;
    int turn;

    pad->bits = (data[0] << 8 | data[1]) ^ 0xFFFF;
    pad->digitalBits = pad->bits;

    for (index = PAD_ANALOG_COUNT - 1; index >= 0; index--)
        pad->analog[index] = 0.0f;

    if (length >= PAD_DATA_STICK_BYTES) {
        for (index = 0; index < PAD_STICK_COUNT; index++) {
            int deflection = data[index + 2] - PAD_STICK_CENTER;

            if (deflection < 0)
                deflection = -deflection;

            if (deflection >= PAD_STICK_DEAD_ZONE) {
                pad->analog[index] = FastIntToFloat(deflection - PAD_STICK_DEAD_ZONE) / FastIntToFloat(PAD_STICK_RANGE);
                if (pad->analog[index] > 1.0f)
                    pad->analog[index] = 1.0f;

                if (data[index + 2] < PAD_STICK_CENTER)
                    pad->analog[index] = -pad->analog[index];
            }
        }
    }

    if (length >= PAD_DATA_PRESSURE_BYTES) {
        for (index = PAD_PRESSURE_FIRST; index < PAD_ANALOG_COUNT; index++)
            pad->analog[index] = FastIntToFloat(data[index + 2]) * PAD_PRESSURE_SCALE;
    }

    if (CheatsActivated[CHEAT_MIRROR_MODE]) {
        pad->analog[2] = -pad->analog[2];
        pad->analog[0] = -pad->analog[0];

        MirrorPadBits(pad->bits);
        pad->digitalBits = pad->bits;
    }

    for (index = 0; index < PAD_ANALOG_COUNT; index++)
        pad->hudAnalog[index] = pad->analog[index];

    if (pad->analog[2] != 0.0f || pad->analog[3] != 0.0f)
        pad->useAnalog = 1;
    else
        pad->useAnalog = 0;

    if (pad->analog[2] < 0.0f)
        pad->bits |= PAD_LEFT;

    if (pad->analog[2] > 0.0f)
        pad->bits |= PAD_RIGHT;

    if (pad->analog[3] < 0.0f)
        pad->bits |= PAD_UP;

    if (pad->analog[3] > 0.0f)
        pad->bits |= PAD_DOWN;

    pad->handsOffStick = (pad->bits & PAD_DPAD) == 0;
    pad->handsOff = pad->bits == 0;
    pad->bitsOn = ~pad->bitsPrev & pad->bits;
    pad->digitalBitsOn = ~pad->bitsPrev & pad->digitalBits;
    pad->bitsOff = ~pad->bits & pad->bitsPrev;
    pad->digitalBitsOff = ~pad->bits & pad->digitalBitsPrev;
    pad->hudBitsOn = pad->bitsOn;
    pad->hudBitsOff = pad->bitsOff;
    pad->hudBits = pad->bits;
    pad->unmaskedBits = pad->bits;

    if (CheatsActivated[CHEAT_MIRROR_MODE]) {
        pad->hudAnalog[2] = -pad->hudAnalog[2];
        pad->hudAnalog[0] = -pad->hudAnalog[0];

        MirrorPadBits(pad->hudBits);
        MirrorPadBits(pad->hudBitsOn);
        MirrorPadBits(pad->hudBitsOff);
    }

    if (pad->hudDivert == PAD_HUD_DIVERT_ACTIONS) {
        pad->bits &= ~PAD_HUD_DIVERT_ACTION_BUTTONS;
        pad->bitsOn &= ~PAD_HUD_DIVERT_ACTION_BUTTONS;
        pad->bitsOff &= ~PAD_HUD_DIVERT_ACTION_BUTTONS;
        pad->analog[0] = 0.0f;
        pad->analog[1] = 0.0f;
        pad->hudDivert = PAD_HUD_DIVERT_NONE;
    }

    if (pad->hudDivert == PAD_HUD_DIVERT_MENU_ONLY) {
        pad->bits &= PAD_HUD_MENU_BUTTONS;
        pad->bitsOn &= PAD_HUD_MENU_BUTTONS;
        pad->bitsOff &= PAD_HUD_MENU_BUTTONS;
        pad->digitalBits &= PAD_HUD_MENU_BUTTONS;
        pad->handsOffStick = 1;
        pad->analog[2] = 0.0f;
        pad->analog[3] = 0.0f;
        pad->hudDivert = PAD_HUD_DIVERT_NONE;
    }

    stick.x = pad->analog[2];
    stick.y = pad->analog[3];
    stickLength = FastVec3Length(&stick.x);
    stickAngle = FastArcTan(stick.x, stick.y);

    pad->analogMagRing[pad->ringIndex] = stickLength;
    pad->analogAngRing[pad->ringIndex] = stickAngle;

    if (stickLength > PAD_FLICK_ENGAGED) {
        for (age = 1; age < FastScaleRoundInt(PAD_FLICK_FRAMES); age++) {
            float previous = pad->analogMagRing[(pad->ringIndex - age + PAD_RING_LENGTH) % PAD_RING_LENGTH];

            if (previous > PAD_FLICK_ENGAGED)
                break;

            if (previous < PAD_FLICK_RESTING) {
                pad->bitsOn |= PAD_STICK_FLICK;
                break;
            }
        }

        if ((pad->bitsOn & PAD_STICK_FLICK) == 0) {
            for (turn = 1; turn < FastScaleRoundInt(PAD_FLICK_TURN_FRAMES); turn++) {
                if (FastDiffRots(pad->analogAngRing[(pad->ringIndex - turn + PAD_RING_LENGTH) % PAD_RING_LENGTH], stickAngle) > PAD_FLICK_TURN) {
                    pad->bitsOn |= PAD_STICK_FLICK;
                    break;
                }
            }
        }
    }

    pad->bitsOnRing[pad->ringIndex] = pad->bitsOn;
    pad->ringIndex = (pad->ringIndex + 1) % PAD_RING_LENGTH;
    if (++pad->ringValidSize > PAD_RING_LENGTH)
        pad->ringValidSize = PAD_RING_LENGTH;

    if (pad->repeatSpeed != 0) {
        if (pad->bits != 0 && pad->bits == pad->bitsPrev) {
            pad->repeatCounter--;
            if (pad->repeatCounter == 0 || pad->repeatCounter == 0xFF) {
                pad->bitsOn = pad->bits;
                pad->repeatCounter = pad->repeatSpeed;
            }
        } else
            pad->repeatCounter = pad->repeatDelay;
    }
}
#else
INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pad", ProcessPadInput);
// The delay slot of its final jr, which the split left as its own entry.
INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/pad", func_0027C474);
#endif

void UpdatePad(void)
{
    UpdatePadEx(&padState);
}
