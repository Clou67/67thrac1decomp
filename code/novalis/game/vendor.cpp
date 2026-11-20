#include "common.h"
#include "moby.h"
#include "libc.h"
#include "framebuf.h"
#include "draw.h"
#include "vendor.h"

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", ProjectBoxToScreen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", ProjectBoxToScreenInt);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_ParseMobySeqs);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", LoadVendorItems);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Spawn_Moby11_Vendor);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_RestoreHero);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_EndWeaponCutscene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_StartWeaponCutscene);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_SetScrollText);

extern const char VendorScrollFormat[];

void Vendor_CopyScrollString(char *text)
{
    sprintf(VendorRender.scrollText, VendorScrollFormat, text);
    VendorRender.scrollPosition = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_UpdateDude);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_PlayDudeSpeech);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_SpawnPreviewMoby);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", PurchaseHandler);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", vendor_PreUpdate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawScrollText);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_UpdateScrollText);

void DrawMobyListProc(MobyInstance *moby, int count);
extern int VendorDudeVisible;
enum { VENDOR_PREVIEW_WIDTH = 512, VENDOR_PREVIEW_HEIGHT = 128 };

void Vendor_DrawDudeMoby(void)
{
    DrawFilledRectGS(0, 0, VENDOR_PREVIEW_WIDTH, VENDOR_PREVIEW_HEIGHT, VENDOR_PREVIEW_WIDTH, VENDOR_PREVIEW_HEIGHT, 0);
    if (VendorDudeVisible == 1)
        DrawMobyListProc(VendorRender.dudeMoby, 1);
}

extern const char VendorBoltsThousandsFormat[];
extern const char VendorBoltsFormat[];

int Vendor_FormatBolts(char *text, int bolts)
{
    if (bolts < 1000)
        return sprintf(text, VendorBoltsFormat, bolts);
    return sprintf(text, VendorBoltsThousandsFormat, bolts / 1000, bolts % 1000);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", DrawVendorHintFrame);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", DrawWeaponStrings);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", DrawBuyButton);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", DrawExitButton);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawItemInfo);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawFlickerText);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_SetupScreenRender);

void Vendor_ResetHUDPass(void)
{
    PutDrawBufferLarge();
    InitViewContext();
    UpdateViewContext();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_HudUpdate);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", func_002B368C);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawMobyHighlight);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawScreen);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", Vendor_DrawScrollingOverlay);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/vendor", vendor_PostUpdate);
