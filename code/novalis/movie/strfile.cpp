#include "sce.h"
#include "strfile.h"

int strFileBegin(StrFile *file, int sector, int frame_count)
{
    file->sector = sector;
    file->frame_count = frame_count;
    return 1;
}

int strFileDelete(StrFile *file)
{
    return 1;
}

int strFileRead(StrFile *file, unsigned char *destination, int size, int asynchronous)
{
    const int sector_shift = 11;
    int sectors = size >> sector_shift;
    int bytes_read = 0;
    sceCdRMode mode;

    mode.trycount = 100;
    mode.spindlctrl = 0;
    mode.datapattern = 0;
    sceCdRead(file->sector, sectors, destination, &mode);

    if (!asynchronous) {
        file->sector += sectors;
        sceCdSync(0);
        bytes_read = size;
    }

    return bytes_read;
}
