#ifndef VUCHAIN_H
#define VUCHAIN_H

// Write position in the current VU1 DMA chain buffer.
extern unsigned int *vu1_bufPtr;

void Vif1ChainCmd(int command);

#endif
