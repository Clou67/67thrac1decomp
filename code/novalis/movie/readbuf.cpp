#include "readbuf.h"

void readBufCreate(ReadBuf *buffer)
{
    buffer->capacity = READ_BUF_CAPACITY;
    buffer->put_pos = 0;
    buffer->count = 0;
}

void readBufDelete(ReadBuf *buffer)
{
}

int readBufBeginPut(ReadBuf *buffer, unsigned char **destination)
{
    int free_space = buffer->capacity - buffer->count;

    if (free_space != 0)
        *destination = buffer->data + buffer->put_pos;

    return free_space;
}

void readBufEndPut(ReadBuf *buffer, int size)
{
    int free_space = buffer->capacity - buffer->count;
    int written = size < free_space ? size : free_space;

    buffer->put_pos = (buffer->put_pos + written) % buffer->capacity;
    buffer->count += written;
}

int readBufBeginGet(ReadBuf *buffer, unsigned char **source)
{
    if (buffer->count != 0) {
        int get_pos = (buffer->put_pos - buffer->count + buffer->capacity) % buffer->capacity;
        *source = buffer->data + get_pos;
    }

    return buffer->count;
}

int readBufEndGet(ReadBuf *buffer, int size)
{
    int consumed = size < buffer->count ? size : buffer->count;
    buffer->count -= consumed;

    return consumed;
}
