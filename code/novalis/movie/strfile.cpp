#include "common.h"
#include "strfile.h"

int strFileBegin(StrFile *file, int sector, int frame_count)
{
    file->sector = sector;
    file->frame_count = frame_count;
    return 1;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/strfile", strFileDelete__FP7StrFile);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/strfile", FUN_0031b908);
