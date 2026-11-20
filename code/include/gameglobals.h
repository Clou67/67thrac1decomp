#ifndef GAMEGLOBALS_H
#define GAMEGLOBALS_H

// Values of gameMode.
enum gameMode_t {
    GAME_MODE_NORMAL,
    GAME_MODE_MOVIE,
    GAME_MODE_SCENE,
    GAME_MODE_PAUSE,
    GAME_MODE_FREEZE
};

extern int gameMode;
extern int CutscenePlaying;
// Game time in frames.
extern int worldUpdateTime;
extern int gameLanguage;
// Play time in game frames.
extern int TotalPlayTime;

#endif
