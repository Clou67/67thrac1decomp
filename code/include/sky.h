#ifndef SKY_H
#define SKY_H

struct Mtx4;
struct DmaTag;
struct sky_shell;
struct sky_sprite;

struct sky_tex {
    unsigned long tex0;
    unsigned long tex1;
};

struct SKY {
    int unk_00;
    short clear_screen;
    short shell_cnt;
    short sprite_cnt;
    short sprite_max;
    short tex_cnt;
    short fx_cnt;
    sky_tex *tex_defs;
    void *tex_data;
    char *fx_list;
    sky_sprite *sprites;
    sky_shell *shells[8];
};

extern SKY *Sky;
extern Mtx4 outMatrix;
extern DmaTag *sky_gif_page_markerA;

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
