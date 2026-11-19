#include "common.h"
#include "sce.h"
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

void voBufDelete(VoBuf *buffer)
{
}

void voBufReset(VoBuf *buffer)
{
    buffer->count = 0;
    buffer->write = 0;
}

int voBufIsFull(VoBuf *buffer)
{
    return buffer->count == buffer->size;
}

void voBufIncCount(VoBuf *buffer)
{
    DIntr();
    buffer->tag[buffer->write].status = VO_TAG_FILLED;
    buffer->count++;
    buffer->write = (buffer->write + 1) % buffer->size;
    EIntr();
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufGetData__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufIsEmpty);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufGetTag__FP5VoBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/vobuf", voBufDecCount__FP5VoBuf);
