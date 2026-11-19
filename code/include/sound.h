#ifndef SOUND_H
#define SOUND_H

void snd_PauseAllSoundsInGroup(int group);
void snd_ContinueAllSoundsInGroup(int group);
void snd_FlushSoundCommands(void);
void snd_SetMasterVolume(int group, int volume);

// Sound system state (only the fields known so far).
struct SoundVoice {
    unsigned char unk_00[0x10];
    int volume;
    int pitch_bend;
    unsigned char unk_18[0x58];
};

struct SoundAudioState {
    unsigned char unk_00[0x48];
    int group_volume[6];
    int reverb_owner;
    int reverb_depth;
    unsigned char reverb_type;
    unsigned char reverb_delay;
    unsigned char reverb_feedback;
    unsigned char reverb_commands;
    int pending_commands;
    SoundVoice voices[30];
};

extern SoundAudioState audioState;
char sound_Update(void);
int sound_LevelPlay(int entry, int flags, int owner);

int sound_SetVol(int handle, int volume);

#endif
