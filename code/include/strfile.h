#ifndef STRFILE_H
#define STRFILE_H

struct StrFile {
    unsigned int frame_count;
    unsigned int sector;
};

int strFileBegin(StrFile *file, int sector, int frame_count);
int strFileDelete(StrFile *file);
int strFileRead(StrFile *file, unsigned char *destination, int size, int asynchronous);

#endif
