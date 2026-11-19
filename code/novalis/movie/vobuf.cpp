#include "common.h"
#include "vobuf.h"

enum {
    VO_TAG_EMPTY = 0,
    VO_TAG_FILLED = 2
};

void voBufCreate(VoBuf *buffer, VoData *data, VoTag *tag, int size)
{
    buffer->count = 0;
    buffer->data = data;
    buffer->tag = tag;
    buffer->size = size;
    buffer->write = 0;

    for (int slot = 0; slot < size; slot++)
        buffer->tag[slot].status = VO_TAG_EMPTY;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufDelete__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufReset__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufIsFull__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufIncCount__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufGetData__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufIsEmpty);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufGetTag__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufDecCount__FP5VoBuf);
