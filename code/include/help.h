#ifndef HELP_H
#define HELP_H

// An entry of the help message table loaded with the level.
struct HelpMsg {
    char *text;
    int id;
    int vag;
    int unk;
};

#define HELP_NO_VAG -1
#define HELP_NO_MESSAGE -1

// How often a message has been shown, when it was last shown (in time buckets) and
// the levels it was shown in (one bit per level).
struct HelpDatum {
    unsigned short timesUsed;
    unsigned short lastTime;
    unsigned int level_die;
};

#define HELP_DATUM_COUNT 0x94

// Values of HelpDef::state.
enum help_state {
    HELP_STATE_IDLE,
    HELP_STATE_BOX_OPENING,
    HELP_STATE_PROMPT,
    HELP_STATE_PROMPT_TO_BOX,
    HELP_STATE_TEXT_FADE_IN,
    HELP_STATE_TEXT_SHOWN,
    HELP_STATE_TEXT_FADE_OUT,
    HELP_STATE_BOX_CLOSING,
    HELP_STATE_SUSPENDED
};

struct HelpDef {
    int state;
    int counter;
    int half_width;
    int half_height;
    int center_x;
    int center_y;
    int frame_half_width;
    int frame_half_height;
    int message_index;
    int message_id;
    int message_flg;
    int num_message;
    int ready;
    int ready_timer;
    short suspend;
    short text_shown;
    int suspend_timer;
};

// A row of the table tying help ids to their messages; either column can be searched.
struct HelpPair {
    short column[2];
};

#define HELP_PAIR_COUNT 150

extern HelpDef Help;
extern HelpMsg *HelpMsgs;
extern HelpDatum HelpDataMessages[];
extern HelpPair HelpPairs[];

// Set while the scene allows the help box to be drawn and heard.
extern unsigned char sceneHelpMsgFlag0;
extern unsigned char sceneHelpMsgFlag1;

// Log of the help messages shown, most recent last.
extern unsigned char activeMessageRecords[];
extern int activeMessageRecordCount;

void Help_Skip(void);
int Help_QueueMessage(int id, int flag);
void Help_Kill(void);
void Help_ClearUsedSinceDeath(void);
int Help_FindIndex(int id);
char *msg_string(int id);
void Help_Suspend(void);
void Help_Resume(void);
void Help_StartMessageBox(void);
void Help_Update(void);
void Help_DrawIconBox(void);
void Help_Draw(void);
int Help_FindPairIndex(short id, int reverse, unsigned short *other);
void Help_AddToLog(int id);

#endif
