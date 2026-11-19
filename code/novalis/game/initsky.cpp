#include "common.h"
#include "sky.h"
#include "framebuf.h"
#include "gsregs.h"
#include "vuchain.h"

// Alpha test (pass when alpha >= 0x60, else write RGB only) with depth test on.
#define SKY_TEST (GS_TEST_ATE | GS_TEST_ATST_GEQUAL | GS_TEST_AREF(0x60) | GS_TEST_AFAIL_RGB_ONLY | GS_TEST_ZTE | GS_TEST_ZTST_GEQUAL)

void InitSky(void)
{
    SetupSkyGifPaging();

    if (Level == LEVEL_NOVALIS) {
        SkyLevel_01();
    } else {
        SkyLevelNone();
    }

    DoSkyGifPaging();

    VU1_addGSregister(GS_REG_TEST_1, SKY_TEST);
    VU1_addGSregister(GS_REG_ZBUF_1, GS_ZBUF_PSMZ24 | GS_ZBUF_ZBP(GSmemZbuf));
}
