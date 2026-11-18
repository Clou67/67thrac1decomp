#include "common.h"
#include "help.h"
#include "draw.h"
#include "fastfunc.h"
#include "font.h"
#include "gameglobals.h"
#include "gsregs.h"
#include "hud.h"
#include "mobyutil.h"
#include "music.h"
#include "pad.h"
#include "pause.h"
#include "sound.h"
#include "vuchain.h"

// Frames a message box takes to open, close and fade its text.
#define HELP_BOX_OPEN_FRAMES 6
#define HELP_TRANSITION_FRAMES 8
#define HELP_TEXT_FADE_FRAMES 4

// Frames to wait before the box can be used, before the prompt gives way to the
// text, how long the text stays up and how long a suspended box stays hidden.
#define HELP_READY_FRAMES 0x78
#define HELP_PROMPT_FRAMES 0x18
#define HELP_TEXT_SHOWN_FRAMES 0x1A4
#define HELP_SUSPEND_FRAMES 60

// Selector under which the box asks the moby code to show a message.
#define HELP_MESSAGE_SELECTOR 5

// Layout of the message box (screen space, 512 wide).
#define HELP_BOX_CENTER_X 0x100
#define HELP_BOX_BOTTOM_OFFSET 60
#define HELP_BOX_BOTTOM_MARGIN 12
#define HELP_BOX_PADDING_X 10
#define HELP_BOX_PADDING_Y 5
#define HELP_BOX_START_HALF_SIZE 8
#define HELP_ICON_HALF_SIZE 0x20
#define HELP_ICON_SIZE 0x40
#define HELP_ICON_FONT 4
#define HELP_ICON_FADE_STEP 21
#define HELP_ICON_ALPHA 0x7E
#define HELP_ALPHA_OPAQUE 0x80
#define HELP_FRAME_ALPHA 0x60
#define HELP_SPRITE_RGB 0x808080
#define HELP_TEXT_RGB 0xFFA888
#define HELP_TEXT_COLOR 0x80FFA888

// Bookkeeping of what has been shown: a message can be counted up to this many
// times, play time is kept in buckets of this many frames, and the top bit of
// level_die marks a message as used since the last death.
#define HELP_TIMES_USED_MAX 0xFFFF
#define HELP_FRAMES_PER_MINUTE 600
#define HELP_LEVEL_DIE_USED 0x80000000

HelpDef Help = {
    HELP_STATE_IDLE, 0,
    0, 0, 0, 0, 0, 0,
    HELP_NO_MESSAGE, HELP_NO_MESSAGE, 0, 0,
    0, 0, 0, 0, 0
};

// Rows of (id, value); the id is looked up in either column.
HelpPair HelpPairs[HELP_PAIR_COUNT] = {
    {3, 21106}, {0, 21103}, {1, 21104}, {2, 21105},
    {1000, 21107}, {1001, 21108}, {1002, 21109}, {1003, 21110},
    {4, 21111}, {5, 21112}, {2000, 21113}, {2001, 21114},
    {2002, 21115}, {2003, 21116}, {2004, 21117}, {2005, 21118},
    {2006, 21119}, {2007, 21120}, {2008, 21121}, {2009, 21122},
    {3000, 21123}, {3001, 21124}, {3002, 21125}, {3003, 21126},
    {3004, 21127}, {3005, 21128}, {3006, 21129}, {3007, 21130},
    {4000, 21131}, {4001, 21132}, {4002, 21133}, {4003, 21134},
    {4004, 21135}, {5000, 21136}, {5001, 21137}, {5002, 21138},
    {5003, 21139}, {5004, 21140}, {5005, 21141}, {6000, 21142},
    {6001, 21143}, {6002, 21144}, {6003, 21145}, {6004, 21146},
    {6005, 21147}, {6006, 21148}, {6007, 21149}, {6008, 21150},
    {8000, 21151}, {8001, 21152}, {8002, 21153}, {8003, 21154},
    {9000, 21155}, {10000, 21156}, {10001, 21157}, {10002, 21158},
    {10003, 21159}, {10004, 21160}, {11000, 21161}, {11001, 21162},
    {11002, 21163}, {11003, 21164}, {12000, 21165}, {12001, 21166},
    {1004, 21167}, {1005, 21168}, {1006, 21169}, {1007, 21170},
    {1008, 21171}, {2010, 21172}, {2011, 21173}, {2012, 21174},
    {2013, 21175}, {4005, 21176}, {20000, 21177}, {20001, 21178},
    {20002, 21179}, {20003, 21180}, {20004, 21181}, {20005, 21182},
    {20006, 21183}, {20007, 21184}, {6009, 21185}, {6010, 21186},
    {3008, 21187}, {11004, 21188}, {11005, 21189}, {11006, 21190},
    {11007, 21191}, {11008, 21192}, {8004, 21193}, {9001, 21194},
    {10005, 21195}, {12002, 21196}, {5006, 21197}, {5007, 21198},
    {3009, 21199}, {5008, 21200}, {3010, 21201}, {3011, 21202},
    {5009, 21203}, {3012, 21204}, {5010, 21205}, {5011, 21206},
    {3013, 21207}, {10006, 21208}, {10007, 21209}, {10008, 21210},
    {11009, 21211}, {12003, 21212}, {12004, 21213}, {13000, 21214},
    {8005, 21215}, {11010, 21216}, {20008, 21217}, {20009, 21218},
    {20010, 21219}, {20011, 21220}, {20012, 21221}, {20013, 21222},
    {20014, 21223}, {20015, 21224}, {14000, 21225}, {15000, 21226},
    {15001, 21227}, {15002, 21228}, {16000, 21229}, {15003, 21230},
    {15004, 21231}, {20016, 21232}, {15005, 21233}, {16001, 21234},
    {16002, 21235}, {18000, 21236}, {11011, 21237}, {16003, 21238},
    {15006, 21239}, {15007, 21240}, {15008, 21241}, {17000, 21242},
    {18001, 21243}, {18002, 21244}, {8006, 21245}, {16004, 21246},
    {2014, 21247}, {20017, 21248}, {20018, 21249}, {20019, 21250},
    {0, 0}, {0, 0},
};

void Help_Skip(void)
{
    switch (Help.state) {
    case HELP_STATE_IDLE:
        Help.message_id = HELP_NO_MESSAGE;
        break;
    case HELP_STATE_BOX_OPENING:
    case HELP_STATE_PROMPT:
        Help.state = HELP_STATE_BOX_CLOSING;
        Help.counter = 0;
        break;
    case HELP_STATE_PROMPT_TO_BOX:
        Help.state = HELP_STATE_BOX_CLOSING;
        Help.counter = 0;
        break;
    case HELP_STATE_TEXT_FADE_IN:
        Help.state = HELP_STATE_TEXT_FADE_OUT;
        Help.counter = HELP_TEXT_FADE_FRAMES - Help.counter;
        break;
    case HELP_STATE_TEXT_SHOWN:
        Help.state = HELP_STATE_TEXT_FADE_OUT;
        Help.counter = 0;
        break;
    case HELP_STATE_TEXT_FADE_OUT:
    case HELP_STATE_BOX_CLOSING:
        break;
    }
}

int Help_QueueMessage(int id, int flag)
{
    if (Help.state == HELP_STATE_IDLE && Help.message_id == HELP_NO_MESSAGE) {
        if (musicTransition.unk50 == 0 && musicTransition.unk1C == HELP_NO_MESSAGE) {
            if (HelpDataMessages[flag].timesUsed != HELP_TIMES_USED_MAX) {
                Help.message_id = id;
                Help.message_flg = flag;
                Help_AddToLog(id);
                return 1;
            }
        }
    }

    return 0;
}

void Help_Kill(void)
{
    if (Help.state != HELP_STATE_IDLE) {
        int vag = HelpMsgs[Help.message_index].vag;

        if (vag != HELP_NO_VAG) {
            if (vag == musicTransition.speechId - MUSIC_SPEECH_ID_BASE) {
                if ((unsigned short)(musicTransition.state - MUSIC_STATE_FINISHING) >= 2) {
                    musicTransition.state = MUSIC_STATE_STOPPING;
                }
            }
        }

        Help.state = HELP_STATE_IDLE;
        Help.message_id = HELP_NO_MESSAGE;
        Help.message_index = HELP_NO_MESSAGE;
        Help.counter = 0;
    }
}

void Help_ClearUsedSinceDeath(void)
{
    int i;

    for (i = 0; i < HELP_DATUM_COUNT; i++) {
        HelpDataMessages[i].level_die &= ~HELP_LEVEL_DIE_USED;
    }
}

int Help_FindIndex(int id)
{
    int found = -1;
    int index = 0;

    if (Help.num_message > 0) {
        if (HelpMsgs[0].id == id) {
            found = 0;
        } else {
        next:
            index++;
            if (index < Help.num_message) {
                if (HelpMsgs[index].id == id) {
                    found = index;
                } else {
                    goto next;
                }
            }
        }
    }

    return found;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", msg_string);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_Suspend);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_Resume);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_StartMessageBox);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_Update);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_DrawIconBox);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_Draw);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_FindPairIndex);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/help", Help_AddToLog);
