#include "common.h"
#include "moby.h"
#include "sky.h"

struct sky_shell {
    int cluster_cnt;
    int gouraud;
};

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyLevelNone);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyLevel_01);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029EF90);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F258);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkySpace);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SetupSkyGifPaging);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", DoSkyGifPaging);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", func_0029F660);

void SkyDrawShell(int shell_index)
{
    if (shell_index < Sky->shell_cnt) {
        sky_shell *shell = Sky->shells[shell_index];

        if (shell->gouraud)
            SkyDrawShellGouraud(shell);

        else
            SkyDrawShellTextured(shell);
    }
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyDrawShellTextured);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/skyfunc", SkyDrawShellGouraud);
