#include "common.h"
#include "npc.h"
#include "fastfunc.h"
#include "gameglobals.h"
#include "help.h"
#include "hero.h"
#include "hud.h"
#include "libc.h"
#include "memcard.h"
#include "pad.h"
#include "vuchain.h"

#define SCRATCHPAD 0x70000000

// Facing tolerance between the hero and a moby that only talks when faced (about 90 degrees).
#define INFOBOT_HINT_HERO_FACING 1.57f

// HUD entries shown while the hero is near a hint.
#define HUD_TYPE_PROMPT 12
#define HUD_TYPE_BOLT_COUNTER 2
#define HUD_PROMPT_FRAMES 10
#define BOLT_COUNTER_TEXTURE 0x754E
#define BOLT_COUNTER_MAXIMUM 9999999
#define BOLT_COUNTER_FRAMES 60

// Languages, each with its own thousands separator.
#define LANGUAGE_COUNT 6

// Level object state set once a moby's hint has been triggered.
#define LEVEL_OBJECT_HINT_SEEN 1

int BoltHudHandle = -1;

int InfobotHint_Update(MobyInstance *moby, InfobotHint *hint)
{
    HeroState *hero = &Hero;
    InfobotHintEntry *entry;
    int index;
    int handle;

    if (hero->state == HERO_STATE_VISIBOMB_CONTROL)
        return 0;

    if (hero->health == 0)
        return 0;

    if (!hint->initialized)
        InfobotHint_InitInstance(moby, hint);

    if (gameMode != GAME_MODE_NORMAL)
        return 0;

    if (hint == 0)
        return 0;

    if (hint->entry == -1)
        return 0;

    if (hint->anyDirection == INFOBOT_HINT_DISABLED)
        return 0;

    if (FastVec3Dist(&moby->pos, &hero->pos) > hint->radius + hint->radius)
        return 0;

    InfobotHint_SetState(moby, hint, 0);

    // The moby must face the hero, and the hero the moby.
    if (hint->anyDirection == 0) {
        if (FastDiffRots(FastArcTan(hero->pos.x - moby->pos.x, hero->pos.y - moby->pos.y), moby->rotation.z) > hint->radius)
            return 0;

        if (FastDiffRots(FastArcTan(moby->pos.x - hero->pos.x, moby->pos.y - hero->pos.y), hero->rot.z) > INFOBOT_HINT_HERO_FACING)
            return 0;
    }

    if (worldUpdateTime < ActiveHint.nextTime)
        return 0;

    if (hint->anyDirection != 0 || (padState.bitsOn & PAD_TRIANGLE)) {
        index = InfobotHint_FindEntry(moby);
        if (LevelObjectStates[index].state == 0)
            LevelObjectStates[index].state = LEVEL_OBJECT_HINT_SEEN;

        ActiveHint.moby = moby;
        ActiveHint.hint = hint;

        entry = &hint->entries[hint->entry];
        if (entry->flags & INFOBOT_HINT_HAS_COST) {
            if (entry->condition == INFOBOT_HINT_ENOUGH_BOLTS)
                HeroBolts -= VendorPrices[entry->conditionValue].bolts;

            else if (entry->condition == INFOBOT_HINT_ITEM_FLAG)
                ItemFlags[entry->conditionValue] = 0;
        }

        if (entry->scene == -1) {
            InfobotHint_SetState(moby, hint, 1);
            return 1;
        }

        ActiveHint.moby = moby;
        ActiveHint.hint = hint;

        if (entry->scene & INFOBOT_HINT_MOVIE) {
            PlayInfobotMovie((short)(entry->scene ^ INFOBOT_HINT_MOVIE));
            return 1;
        }

        Hud_SetEntryIconById(BoltHudHandle);
        BoltHudHandle = -1;
        mode_movieUnInit(entry->scene);
        return 1;
    }

    if (Hud_SetEntryMinValueById(BoltHudHandle, HUD_PROMPT_FRAMES))
        BoltHudHandle = RegisterHUDCallback(HUD_TYPE_PROMPT, 0, HudEntry_InitCounterSlide, HudEntry_UpdateCounterWrap, Draw_PromptMsg, 0, 0);

    // Entries with a bolt price also show the bolt counter.
    {
        InfobotHintEntry *priced = &hint->entries[hint->entry];

        if (priced->condition == INFOBOT_HINT_ENOUGH_BOLTS || priced->condition == INFOBOT_HINT_PRICE) {
            handle = RegisterHUDCallback(HUD_TYPE_BOLT_COUNTER, BOLT_COUNTER_TEXTURE, Hud_DrawTexQuadUV_Fixed, BoltHud_Update, Draw_BoltCountUI, &HeroBolts, BOLT_COUNTER_MAXIMUM);
            Hud_SetEntryMinValueById(handle, FastScaleRoundInt(BOLT_COUNTER_FRAMES));
        }
    }

    return 0;
}

int InfobotHint_FindEntry(MobyInstance *moby)
{
    int index;
    int end;

    if ((unsigned int)Level >= LEVEL_COUNT)
        return 0;

    index = LevelObjectStart[Level];
    end = LevelObjectStart[Level + 1];
    for (; index < end; index++) {
        if (LevelObjectMobys[index] == moby)
            return index;
    }

    return -1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_SetEntryState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_InitInstance);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_SetState);
