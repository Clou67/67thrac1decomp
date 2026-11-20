#include "common.h"
#include "draw.h"
#include "debug.h"

void ResetDebugEnables(void)
{
    int enabled = 1;
    for (int flag = DRAW_CONFIG_ENABLE_COUNT - 1; flag >= 0; --flag)
        drawConfig.enables[flag] = enabled;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", func_00215278);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DebugFontQueue);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DebugFontFlush);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DebugFontDrawString);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DebugFontPrintCenter);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", func_00215670);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DebugCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", UpdateDebugCamera);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", UpdateDebugSelections);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", func_002174D8);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/debug", DrawDebugMenu);

void STUB_002187f8(void)
{
}

void STUB_00218800(void)
{
}

void STUB_00218808(void)
{
}

void STUB_00218810(void)
{
}

void STUB_00218818(void)
{
}

void STUB_00218820(void)
{
}

void STUB_00218828(void)
{
}

void STUB_00218830(void)
{
}
