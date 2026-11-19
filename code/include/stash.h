#ifndef STASH_H
#define STASH_H

void Stash_Init(void);

int Stash_SendData(void *source, int transferQwords, int reserveQwords, int comment);

#endif
