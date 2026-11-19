#include "common.h"
#include "readbuf.h"

void readBufCreate(ReadBuf *buffer)
{
    buffer->capacity = READ_BUF_CAPACITY;
    buffer->put_pos = 0;
    buffer->count = 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/readbuf", readBufDelete__FP7ReadBuf);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/readbuf", readBufBeginPut__FP7ReadBufPPUc);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/readbuf", readBufEndPut__FP7ReadBufi);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/readbuf", readBufBeginGet__FP7ReadBufPPUc);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/movie/readbuf", readBufEndGet__FP7ReadBufi);
