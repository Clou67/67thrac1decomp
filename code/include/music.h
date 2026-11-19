#ifndef MUSIC_H
#define MUSIC_H

struct MusicTransition {
    char unk0[0x1C];
    int unk1C;
    char unk20[2];
    signed char requested_track;
    char unk23[0x15];
    short primary_track;
    char unk3A[6];
    short primary_command;
    char unk42[0xE];
    int unk50;
    short speechId;
    short unk56;
    short unk58;
    short state;
    short secondary_command;
    char unk5E[0x1A];
    short transition_command;
};

// Speech ids are offset by this much from the ids stored in the help messages.
#define MUSIC_SPEECH_ID_BASE 30000

// Values of MusicTransition::state seen so far; 6 and 7 are the finishing states.
#define MUSIC_STATE_READY 3
#define MUSIC_STATE_STOPPING 5
#define MUSIC_STATE_FINISHING 6

extern MusicTransition musicTransition;

void music_Sync(int wait);
void music_Pause(int fade);
void music_Unpause(void);
void music_RegisterBankCB(void);
void music_PlayPreseekedSpeech(void);
// Nonzero while a music_LoadFile read is still streaming in.
extern short CdReadActive[];

void music_LoadFile(void *destination, int sector, int length);
int music_LoadFileSync(void *destination, int sector, int length);

#endif
