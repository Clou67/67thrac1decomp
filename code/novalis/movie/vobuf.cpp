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

VoData *voBufGetData(VoBuf *buffer)
{
    if (voBufIsFull(buffer))
        return 0;

    return &buffer->data[buffer->write];
}

int voBufIsEmpty(VoBuf *buffer)
{
    return buffer->count == 0;
}

VoTag *voBufGetTag(VoBuf *buffer)
{
    if (voBufIsEmpty(buffer))
        return 0;

    int slot = (buffer->write - buffer->count + buffer->size) % buffer->size;
    return &buffer->tag[slot];
}

void voBufDecCount(VoBuf *buffer)
{
    if (buffer->count > 0)
        buffer->count--;
}
