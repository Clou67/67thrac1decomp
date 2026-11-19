#include "common.h"
#include "shrub.h"
#include "draw.h"
#include "fastfunc.h"
#include "initlevel.h"
#include "vuchain.h"

// GS memory the shrub textures may use before they overflow it.
#define SHRUB_GS_MEMORY_LIMIT 0x400000

// Scratchpad range ShrubProc leaves its results in.
#define SHRUB_SPR_RESULT_ADDRESS 0x3200
#define SHRUB_SPR_RESULT_QWORDS 0x40

void DmaShrubTextures(void)
{
    DmaTag *start = vu1_bufPtr.tag++;

    ShrubVu1Marker.tag->tag = DMA_TAG_NEXT;
    ShrubVu1Marker.tag->addr = (unsigned int)vu1_bufPtr.tag;
    ShrubVu1Marker.tag->vif0 = 0;
    ShrubVu1Marker.tag->vif1 = 0;

    if (drawConfig.shrub) {
        if (drawConfig.shrub_texture_paging) {
            int gsEnd = BuildShrubTextureDma(textureCursor);

            VU1_texFlush();

            if (gsEnd > SHRUB_GS_MEMORY_LIMIT)
                printf_stub("shrub texture overflow\n");

            if (ShrubGsMax < gsEnd)
                ShrubGsMax = gsEnd;
        }
    }

    // Return from the texture uploads to the packets after the opening marker.
    vu1_bufPtr.tag->tag = DMA_TAG_NEXT;
    vu1_bufPtr.tag->addr = (unsigned int)(ShrubVu1Marker.tag + 1);
    vu1_bufPtr.tag->vif0 = 0;
    vu1_bufPtr.tag->vif1 = 0;
    vu1_bufPtr.tag++;

    // The first link jumps over the uploads to this point.
    start->tag = DMA_TAG_NEXT;
    start->addr = (unsigned int)vu1_bufPtr.tag;
    start->vif0 = 0;
    start->vif1 = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/shrubfunc", PatchShrubGifs);

void DrawShrub(void)
{
    ShrubVu1Marker.tag = vu1_bufPtr.tag++;
    textureCursor = textureCursorEnd;

    printf_stub3(ShrubTextureLabel, 1);

    if (drawConfig.shrub) {
        FlushCache(0);
        ShrubProc();
        FastFromSpr(ShrubSprStash, SHRUB_SPR_RESULT_ADDRESS, SHRUB_SPR_RESULT_QWORDS);
    }

    printf_stub3(ShrubDrawLabel, 7);
    DmaShrubTextures();
    printf_stub2(ShrubDrawLabel, 7);
}
