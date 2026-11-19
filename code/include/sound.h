#ifndef SOUND_H
#define SOUND_H

void snd_PauseAllSoundsInGroup(int group);
void snd_ContinueAllSoundsInGroup(int group);
void snd_FlushSoundCommands(void);
void snd_SetMasterVolume(int group, int volume);

// Sound system state (only the fields known so far).
struct SoundAudioState {
    unsigned char unk_00[0x48];
    int group_volume[6];
};

extern SoundAudioState audioState;
char sound_Update(void);
int sound_LevelPlay(int entry, int flags, int owner);

#endif
