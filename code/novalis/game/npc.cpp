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

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_FindEntry);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_SetEntryState);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_InitInstance);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/npc", InfobotHint_SetState);
