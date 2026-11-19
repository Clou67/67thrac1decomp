#ifndef VOBUF_H
#define VOBUF_H

struct VoData {
    unsigned char v[0xD0000];
};

struct VoTag {
    int status;
    int buffer;
    int dummy[14];
    unsigned int v[10000][2];  // Novalis GS image packet storage.
};

struct VoBuf {
    VoData *data;
    VoTag *tag;
    volatile int write;
    volatile int count;
    int size;
};

void voBufCreate(VoBuf *buffer, VoData *data, VoTag *tag, int size);
void voBufDelete(VoBuf *buffer);
void voBufReset(VoBuf *buffer);
int voBufIsFull(VoBuf *buffer);
void voBufIncCount(VoBuf *buffer);
VoData *voBufGetData(VoBuf *buffer);
int voBufIsEmpty(VoBuf *buffer);
VoTag *voBufGetTag(VoBuf *buffer);
void voBufDecCount(VoBuf *buffer);

#endif
