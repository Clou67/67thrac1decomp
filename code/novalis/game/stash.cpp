#include "common.h"
#include "sce.h"
#include "stash.h"

enum { STASH_SLOT_COUNT = 64, STASH_QWORD_BYTES = 16, STASH_RPC_SERVER = 0x11,
       STASH_RPC_FETCH = 1, STASH_RPC_INFO = 2, STASH_MAX_FETCH_QWORDS = 0xFFFF };

struct StashInfo {
    int base;
    int size;
    SifRpcClient client;
    int next;
    int count;
};

struct StashBlock {
    int address;
    int qwords;
    int comment;
    int padding;
};

extern StashInfo StashState;
extern StashBlock StashBlocks[];

void Stash_Init(void)
{
    sceSifInitRpc(0);
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/stash", Stash_InitOnce);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/stash", func_002A7740);

int Stash_SendData(void *source, int transferQwords, int reserveQwords, int comment)
{
    StashInfo *state = &StashState;
    int reserveBytes = reserveQwords * STASH_QWORD_BYTES;
    if (state->size - (state->next - state->base) < reserveBytes)
        return -1;
    if (state->count == STASH_SLOT_COUNT)
        return -2;

    SifDmaTransfer transfer;
    transfer.source = source;
    transfer.destination = (void *)state->next;
    transfer.size = transferQwords * STASH_QWORD_BYTES;
    transfer.attributes = 0;
    sceSifSetDma(&transfer, 1);

    int slot = state->count++;
    StashBlocks[slot].address = state->next;
    StashBlocks[slot].qwords = reserveQwords;
    StashBlocks[slot].comment = comment;
    state->next += reserveBytes;
    return slot;
}

int Stash_Upload(void *source, unsigned int slot, int offset, int qwords)
{
    if (slot >= STASH_SLOT_COUNT || StashBlocks[slot].qwords == 0)
        return -3;
    if (StashBlocks[slot].qwords < offset + qwords)
        return -1;

    SifDmaTransfer transfer;
    transfer.source = source;
    transfer.destination = (void *)(StashBlocks[slot].address + offset * STASH_QWORD_BYTES);
    transfer.size = qwords * STASH_QWORD_BYTES;
    transfer.attributes = 0;
    sceSifSetDma(&transfer, 1);
    return 0;
}

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/stash", Stash_Copy);

INCLUDE_ASM("code/_generated/novalis/nonmatchings/game/stash", Stash_GetSize);
