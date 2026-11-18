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

void csf_unformatted(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_UNFORMATTED) {
        mc_state = CS_NOCARD;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_SAVE) {
        mc_state = CS_PROMPT_FORMAT;
    }
}

void csf_prompt_format(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_UNFORMATTED) {
        mc_state = CS_NOCARD;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_ANSWER_NO) {
        mcstate_flags ^= MCSTATE_FLAG_ANSWER_NO;

        if (InFrontEnd) {
            mc_state = CS_PROMPT_BEGIN_UNFORMATTED;
            return;
        }

        mc_state = CS_UNFORMATTED;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_FORMAT_YES) {
        mcstate_flags ^= MCSTATE_FLAG_FORMAT_YES;
        mc_state = CS_FORMAT_PENDING;
    }
}

void csf_format_pending(void)
{
    g_memcard.memcards[0].result = MC_RESULT_SAME_CARD;

    if (g_memcard.nextstage < 0) {
        g_memcard.nextslot = 0;
        g_memcard.nextstage = MC_STAGE_FORMAT;
    }

    mc_state = CS_FORMATTING;
}

void csf_formatting(void)
{
    if (g_memcard.stage == MC_STAGE_IDLE && g_memcard.nextstage < 0) {
        if (g_memcard.err != 0) {
            mc_state = CS_PROMPT_FORMAT_FAILED;
            mcstate_flags |= MCSTATE_FLAG_PROMPT;
            return;
        }

        mc_state = CS_CREATE_SAVE_PENDING;
    }
}

void csf_formatted(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        mc_state = CS_NOCARD;
        return;
    }

    if (mcstate_flags & (MCSTATE_FLAG_SAVE | MCSTATE_FLAG_LOAD)) {
        mc_state = CS_CHECK_SAVE;
    }
}

void csf_check_save(void)
{
    if (g_memcard.stage == MC_STAGE_IDLE && g_memcard.nextstage < 0) {
        g_memcard.nextstage = MC_STAGE_CHECK_SAVE;
        g_memcard.nextslot = 0;
        mc_state = CS_CHECKING_SAVE;
    }
}

void csf_checking_save(void)
{
    if (g_memcard.memcards[0].result < MC_RESULT_NEW_CARD) {
        mc_state = CS_NOCARD;
        return;
    }

    if (g_memcard.memcards[0].saveslot == -2) {
        if (g_memcard.memcards[0].free < MC_SAVE_SIZE) {
            mc_state = CS_NO_ROOM;
            return;
        }

        mc_state = CS_NOSAVE;
        return;
    }

    if (g_memcard.memcards[0].saveslot > -2) {
        mc_state = CS_NEWCARD;
    }
}

void csf_nosave(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        mc_state = CS_NOCARD;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_SAVE) {
        mc_state = CS_PROMPT_CREATE_SAVE;
    }
}

void csf_prompt_create_save(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        mc_state = CS_NOCARD;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_ANSWER_NO) {
        mcstate_flags ^= MCSTATE_FLAG_ANSWER_NO;

        if (InFrontEnd) {
            mc_state = CS_PROMPT_BEGIN_NOSAVE;
            return;
        }

        mc_state = CS_NOSAVE;
        return;
    }

    if (mcstate_flags & MCSTATE_FLAG_CREATE_YES) {
        mcstate_flags ^= MCSTATE_FLAG_CREATE_YES;
        mc_state = CS_CREATE_SAVE_PENDING;
    }
}

void csf_create_save_pending(void)
{
    if (g_memcard.stage == MC_STAGE_IDLE && g_memcard.nextstage < 0) {
        g_memcard.nextstage = MC_STAGE_CREATE_SAVE;
        g_memcard.nextslot = 0;
        mc_state = CS_CREATING_SAVE;
    }
}

void csf_creating_save(void)
{
    if (g_memcard.stage == MC_STAGE_IDLE && g_memcard.nextstage < 0) {
        if (g_memcard.err != 0) {
            mc_state = CS_PROMPT_CREATE_FAILED;
            mcstate_flags |= MCSTATE_FLAG_PROMPT;
            return;
        }

        g_memcard.nextstage = MC_STAGE_CHECK_SAVE;
        g_memcard.useslot = 0;
        g_memcard.memcards[0].saveslot = 0;
        g_memcard.nextslot = 0;
        mc_state = CS_NEWCARD;
    }
}

void csf_newcard(void)
{
    int flags = mcstate_flags;

    mcstate_flags &= ~MCSTATE_FLAG_LOAD;
    mcstate_flags &= ~MCSTATE_FLAG_SAVE;

    if (flags & MCSTATE_FLAG_SAVE_FAILED) {
        mcstate_flags = (mcstate_flags ^ MCSTATE_FLAG_SAVE_FAILED) | MCSTATE_FLAG_PROMPT;
        mc_state = CS_PROMPT_SAVE_FAILED;
    } else if (flags & MCSTATE_FLAG_LOAD_FAILED) {
        mcstate_flags = (mcstate_flags ^ MCSTATE_FLAG_LOAD_FAILED) | MCSTATE_FLAG_PROMPT;
        mc_state = CS_PROMPT_LOAD_FAILED;
    } else if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        mc_state = CS_NOCARD;
    } else if (g_memcard.autosave != 0) {
        mc_state = CS_GOOD_SAVE;
    }
}

void csf_prompt_format_failed(void)
{
    if (!(mcstate_flags & MCSTATE_FLAG_PROMPT)) {
        mc_state = CS_NOCARD;
    }
}

void csf_prompt_create_failed(void)
{
    if (!(mcstate_flags & MCSTATE_FLAG_PROMPT)) {
        mc_state = CS_NOCARD;
    }
}

void csf_no_room(void)
{
    if (g_memcard.memcards[0].result != MC_RESULT_SAME_CARD) {
        mc_state = CS_NOCARD;
    }
}

void csf_prompt_load_failed(void)
{
    if (!(mcstate_flags & MCSTATE_FLAG_PROMPT)) {
        mc_state = CS_NOCARD;
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f2f8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", CardState_Reset);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f398);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/mcstate", FUN_0025f3e0);
