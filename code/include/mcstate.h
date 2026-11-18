#ifndef MCSTATE_H
#define MCSTATE_H

#include "memcard.h"
#include "freeze.h"

// Memory card states, in DL's order with the states RC1 doesn't have left out.
enum mcstate_t {
    CS_INIT,
    CS_GOOD_SAVE,
    CS_GOOD_LOAD,
    CS_NOCARD,
    CS_WAIT_FOR_CARD,
    CS_UNFORMATTED,
    CS_PROMPT_FORMAT,
    CS_FORMAT_PENDING,
    CS_FORMATTING,
    CS_FORMATTED,
    CS_CHECK_SAVE,
    CS_CHECKING_SAVE,
    CS_NOSAVE,
    CS_PROMPT_CREATE_SAVE,
    CS_CREATE_SAVE_PENDING,
    CS_CREATING_SAVE,
    CS_NEWCARD,
    CS_PROMPT_FORMAT_FAILED,
    CS_PROMPT_CREATE_FAILED,
    CS_NO_ROOM,
    CS_PROMPT_LOAD_FAILED,
    CS_PROMPT_SAVE_FAILED,
    CS_SAVING,
    CS_PROMPT_BEGIN_UNFORMATTED,
    CS_PROMPT_BEGIN_NOSAVE,
    CS_EOL
};

// mcstate_flags bits.
#define MCSTATE_FLAG_CARD_CHANGED 0x1
#define MCSTATE_FLAG_SAVE 0x2
#define MCSTATE_FLAG_LOAD 0x4
#define MCSTATE_FLAG_FORMAT_YES 0x8
#define MCSTATE_FLAG_CREATE_YES 0x10
#define MCSTATE_FLAG_ANSWER_NO 0x20
#define MCSTATE_FLAG_PROMPT 0x40
#define MCSTATE_FLAG_SAVE_FAILED 0x80
#define MCSTATE_FLAG_LOAD_FAILED 0x100
#define MCSTATE_FLAG_DO_SAVE 0x200

extern int mc_state;
extern int mcstate_flags;
extern int mcstate_time;
extern int InFrontEnd;
extern void (*state_functions[CS_EOL])(void);

void UpdateMCState(void);

#endif
