#include "common.h"
#include "initlevel.h"
#include "moby.h"
#include "sky.h"
#include "vuchain.h"

struct sky_shell {
    int cluster_cnt;
    int gouraud;
};

extern char skyGifPageLabel[];
extern int GifLoadCnt;

void FastMtx4Identity(float *matrix);
void printf_stub3(const char *format, ...);

void SkyLevelNone(void)
{
    FastMtx4Identity(&outMatrix.v0.x);

    for (int shell_index = 0; shell_index < Sky->shell_cnt; shell_index++)
        SkyDrawShell(shell_index);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyLevel_01);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029EF90);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F258);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkySpace);

void SetupSkyGifPaging(void)
{
    sky_gif_page_markerA = vu1_bufPtr.tag++;
    printf_stub3(skyGifPageLabel, 1);

    textureCursor = textureCursorEnd;
    GifLoadCnt = 0;

    for (int texture_index = 0; texture_index < Sky->tex_cnt; texture_index++)
        Sky->tex_defs[texture_index].tex0 = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", DoSkyGifPaging);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F660);

void SkyDrawShell(int shell_index)
{
    if (shell_index < Sky->shell_cnt) {
        sky_shell *shell = Sky->shells[shell_index];

        if (shell->gouraud)
            SkyDrawShellGouraud(shell);

        else
            SkyDrawShellTextured(shell);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyDrawShellTextured);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyDrawShellGouraud);
