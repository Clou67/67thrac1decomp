#ifndef STRFILE_H
#define STRFILE_H

struct StrFile {
    unsigned int size;
    unsigned int sector;
};

int strFileBegin(StrFile *file, int sector, int file_size);
int strFileDelete(StrFile *file);
int strFileRead(StrFile *file, unsigned char *destination, int size, int asynchronous);

#endif
