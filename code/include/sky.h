#ifndef SKY_H
#define SKY_H

struct sky_shell;

struct SKY {
    int unk_00;
    short clear_screen;
    short shell_cnt;
    char unk_08[0x18];
    sky_shell *shells[8];
};

extern SKY *Sky;

void SkyDrawShell(int shell_index);
void SkyDrawShellTextured(sky_shell *shell);
void SkyDrawShellGouraud(sky_shell *shell);

void SetupSkyGifPaging(void);
void DoSkyGifPaging(void);

// Per-level sky setup.
void SkyLevelNone(void);
void SkyLevel_01(void);

void InitSky(void);

#endif
