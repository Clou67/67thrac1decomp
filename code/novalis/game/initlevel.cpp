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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initlevel", InitLevel);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initlevel", UnlockPurchasableItems);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/initlevel", AddToUnlockedList);

TEXT_PADDING(0x27BD0090, 0x00000000);
