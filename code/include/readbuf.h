#ifndef READBUF_H
#define READBUF_H

enum { READ_BUF_CAPACITY = 0x50000 };

struct ReadBuf {
    unsigned char data[READ_BUF_CAPACITY];
    int put_pos;
    int count;
    int capacity;
};

void readBufCreate(ReadBuf *buffer);
void readBufDelete(ReadBuf *buffer);
int readBufBeginPut(ReadBuf *buffer, unsigned char **destination);
void readBufEndPut(ReadBuf *buffer, int size);
int readBufBeginGet(ReadBuf *buffer, unsigned char **source);
int readBufEndGet(ReadBuf *buffer, int size);

#endif
