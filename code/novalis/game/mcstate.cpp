#include "common.h"
#include "mcstate.h"

void UpdateMCState(void)
{
    int previousState = mc_state;

    state_functions[mc_state]();

    mcstate_time++;

    if (mc_state != previousState) {
        mcstate_time = 0;
    }
}

void csf_init(void)
{
    mc_state = CS_NOCARD;
    g_memcard.autosave = 0;
    g_memcard.memcards[0].result = g_memcard.res;
}

void csf_good_save(void)
{
    int flags = mcstate_flags;

    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
    mcstate_flags &= ~MCSTATE_FLAG_SAVE;

    if (g_memcard.autosave == 0) {
        mc_state = CS_NOCARD;
        return;
    }

    if (flags & MCSTATE_FLAG_SAVE_FAILED) {
        mcstate_flags = (mcstate_flags ^ MCSTATE_FLAG_SAVE_FAILED) | MCSTATE_FLAG_PROMPT;
        mc_state = CS_PROMPT_SAVE_FAILED;
    } else if (flags & MCSTATE_FLAG_LOAD_FAILED) {
        mcstate_flags = (mcstate_flags ^ MCSTATE_FLAG_LOAD_FAILED) | MCSTATE_FLAG_PROMPT;
        mc_state = CS_PROMPT_LOAD_FAILED;
    } else if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        g_memcard.autosave = 0;
        mcstate_flags |= MCSTATE_FLAG_CARD_CHANGED;
        mc_state = CS_GOOD_LOAD;
    } else if (flags & MCSTATE_FLAG_DO_SAVE) {
        mcstate_flags ^= MCSTATE_FLAG_DO_SAVE;
        mc_state = CS_SAVING;
    }
}

void csf_good_load(void)
{
    if (!(mcstate_flags & MCSTATE_FLAG_CARD_CHANGED)) {
        mc_state = CS_NOCARD;
    }
}

void csf_nocard(void)
{
    g_memcard.nextstage = -1;
    mc_state = CS_WAIT_FOR_CARD;
    g_memcard.nextslot = -1;
}

void csf_wait_for_card(void)
{
    int result = g_memcard.memcards[0].result;

    mcstate_flags &= ~MCSTATE_FLAG_ANSWER_NO;

    if (result == MC_RESULT_SAME_CARD) {
        mc_state = CS_FORMATTED;
    } else if (result == MC_RESULT_NEW_CARD) {
        g_memcard.memcards[0].result = MC_RESULT_SAME_CARD;
        mc_state = CS_FORMATTED;
    } else if (result == MC_RESULT_UNFORMATTED) {
        mc_state = CS_UNFORMATTED;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025ee30);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025ee70);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025eef0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025ef20);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025ef80);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025efb8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025eff8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f068);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f0a0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f118);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f158);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f1d0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f260);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f288);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f2b0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f2d0);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f2f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", CardState_Reset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f398);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f3e0);
