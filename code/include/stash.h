#ifndef STASH_H
#define STASH_H

void Stash_Init(void);

int Stash_SendData(void *source, int transferQwords, int reserveQwords, int comment);

int Stash_Upload(void *source, unsigned int slot, int offset, int qwords);

int Stash_GetSize(unsigned int slot);

#endif
