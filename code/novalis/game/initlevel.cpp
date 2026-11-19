#include "common.h"
#include "initlevel.h"
#include "draw.h"
#include "fastfunc.h"
#include "framebuf.h"
#include "hero.h"
#include "memcard.h"
#include "mobyutil.h"
#include "music.h"
#include "vendor.h"
#include "vuchain.h"

#define COLL_JOINT_CACHE_EMPTY 0x87654321

// Game time added for each level load.
#define LEVEL_LOAD_ELAPSED_TIME 180

void InitLevel(void)
{
    music_RegisterBankCB();
    VU1_setBufSizeByLevel();
    InitMemSlots();

    textureCursor = GSmemBase;
    textureCursorEnd = GSmemBase;

    FastMemSet(CollJointCacheKeys, COLL_JOINT_CACHE_EMPTY, sizeof(CollJointCacheKeys));
    FastMemSet(MobyClassLookup, -1, sizeof(MobyClassLookup));
    FastMemSet(MobyTexLookup, -1, sizeof(MobyTexLookup));
    FastMemSet(MobyMipDists, 0, sizeof(MobyMipDists));
    FastMemSet(TieClassLookup, -1, sizeof(TieClassLookup));
    FastMemSet(TieTexLookup, -1, sizeof(TieTexLookup));
    FastMemSet(TieMipDists, 0, sizeof(TieMipDists));
    FastMemSet(ShrubClassLookup, -1, sizeof(ShrubClassLookup));
    FastMemSet(ShrubTexLookup, -1, sizeof(ShrubTexLookup));
    FastMemSet(ShrubMipDists, 0, sizeof(ShrubMipDists));

    InitViewContext();
    UpdateViewContext();
    VU1_initChain();
    ResetParticles();
    DMAC_VIF1_Enable();

    UnlockPurchasableItems();
    if (Level != 0) {
        MB_UnlockLevel(Level);
    }

    ElapsedTime += LEVEL_LOAD_ELAPSED_TIME;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initlevel", UnlockPurchasableItems);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initlevel", AddToUnlockedList);

TEXT_PADDING(0x27BD0090, 0x00000000);
