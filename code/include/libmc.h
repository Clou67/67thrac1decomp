#ifndef LIBMC_H
#define LIBMC_H

// Sony memory card library (libmc). Written in C, so it keeps C linkage.

// One directory entry filled in by sceMcGetDir.
struct sceMcTblGetDir {
    unsigned char Create[8];
    unsigned char Modify[8];
    unsigned int FileSizeByte;
    unsigned short AttrFile;
    unsigned short Reserve1;
    unsigned int Reserve2;
    unsigned int PdaAplNo;
    unsigned char EntryName[32];
};

// sceMcOpen modes.
#define SCE_RDONLY 0x0001
#define SCE_WRONLY 0x0002
#define SCE_CREAT 0x0200
#define SCE_RDWR_CREATE (SCE_WRONLY | SCE_CREAT | 0x0001)

// sceMcSeek origins.
#define SCE_SEEK_SET 0
#define SCE_SEEK_CUR 1

extern "C" {
int sceMcInit(void);
int sceMcSync(int mode, int *cmd, int *result);
int sceMcGetInfo(int port, int slot, int *type, int *free, int *format);
int sceMcFormat(int port, int slot);
int sceMcUnformat(int port, int slot);
int sceMcChdir(int port, int slot, const char *newDir, char *oldDir);
int sceMcOpen(int port, int slot, const char *name, int mode);
int sceMcRead(int fd, void *buffer, int size);
int sceMcWrite(int fd, const void *buffer, int size);
int sceMcClose(int fd);
int sceMcSeek(int fd, int offset, int mode);
int sceMcMkdir(int port, int slot, const char *name);
int sceMcDelete(int port, int slot, const char *name);
int sceMcGetDir(int port, int slot, const char *name, unsigned int mode, int maxent, sceMcTblGetDir *table);
}

#endif
