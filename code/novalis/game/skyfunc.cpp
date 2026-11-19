#include "common.h"
#include "initlevel.h"
#include "moby.h"
#include "sky.h"
#include "vuchain.h"

struct sky_shell {
    int cluster_cnt;
    int gouraud;
};

struct SkyGifPageMarker {
    DmaTag *tag;
};

struct DrawConfig {
    int unk_00;
    int sky_texture_paging;
    int sky;
};

extern SkyGifPageMarker sky_gif_page_markerA;
extern SkyGifPageMarker sky_gif_page_markerB;
extern DrawConfig drawConfig;
extern char skyGifPageLabel[];
extern int GifLoadCnt;

void FastMtx4Identity(float *matrix);
void printf_stub3(const char *format, ...);
void BuildGifTextureDma(void);

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
    sky_gif_page_markerA.tag = vu1_bufPtr.tag++;
    printf_stub3(skyGifPageLabel, 1);

    textureCursor = textureCursorEnd;
    GifLoadCnt = 0;

    for (int texture_index = 0; texture_index < Sky->tex_cnt; texture_index++)
        Sky->tex_defs[texture_index].tex0 = 0;
}

void DoSkyGifPaging(void)
{
    // The first link jumps to the optional upload packets.
    sky_gif_page_markerB.tag = vu1_bufPtr.tag++;
    sky_gif_page_markerA.tag->tag = DMA_TAG_NEXT;
    sky_gif_page_markerA.tag->addr = (unsigned int)vu1_bufPtr.tag;
    sky_gif_page_markerA.tag->vif0 = 0;
    sky_gif_page_markerA.tag->vif1 = 0;

    if (drawConfig.sky_texture_paging != 0) {
        BuildGifTextureDma();
        VU1_texFlush();
    }

    // Return from the uploads to the sky packets after the opening marker.
    DmaTag *page_link = vu1_bufPtr.tag;
    page_link->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(sky_gif_page_markerA.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;

    // The bypass link rejoins the chain after this return link.
    vu1_bufPtr.tag++;
    sky_gif_page_markerB.tag->tag = DMA_TAG_NEXT;
    sky_gif_page_markerB.tag->addr = (unsigned int)vu1_bufPtr.tag;
    sky_gif_page_markerB.tag->vif0 = 0;
    sky_gif_page_markerB.tag->vif1 = 0;

    gsTextureAllocation.cursor = gsTextureAllocation.start;
}

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
