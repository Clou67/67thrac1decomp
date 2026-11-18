#ifndef SOUND_H
#define SOUND_H

void snd_PauseAllSoundsInGroup(int group);
void snd_ContinueAllSoundsInGroup(int group);
void snd_FlushSoundCommands(void);
char sound_Update(void);
int sound_LevelPlay(int entry, int flags, int owner);

#endif
