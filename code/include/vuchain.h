#ifndef VUCHAIN_H
#define VUCHAIN_H

// Current level (core global).
extern int Level;

#define LEVEL_COUNT 19

// Per-level size of a VU1 chain buffer.
extern int vu1_buf_table[LEVEL_COUNT];
extern int vu1_bufSize;

// Memory slot table set up by InitMemSlots (RC1 layout; only the fields known so far).
struct MEMSLOTS {
    void *base;
    unsigned char *vu1_chain[2];
};

extern MEMSLOTS MemSlots;

// The two VU1 DMA chain buffers, built and sent in turn.
extern unsigned char *vu1_DmaBuffers[];
// Which of vu1_DmaBuffers is being built.
extern int vu1_bufId;
// Write position in the VU1 chain buffer being built.
extern unsigned char *vu1_bufPtr;
// End of the chain built last frame (kept by the swap).
extern unsigned char *vu1_chainEnd;

// Scratch memory carved from the top of the chain buffer being built.
extern unsigned char *EngScratchPad;
extern int EngScratchPadSize;
extern unsigned char *SkinVertexCache;

#define SKIN_VERTEX_CACHE_SIZE 0x2000

// Word at a byte offset from the VU1 chain write position.
#define VU1_CHAIN_WORD(offset) (*(unsigned int *)(vu1_bufPtr + (offset)))
// Doubleword at a byte offset from the VU1 chain write position.
#define VU1_CHAIN_DWORD(offset) (*(unsigned long *)(vu1_bufPtr + (offset)))

// DMA tag ids (bits 28-30): payload follows the tag inline (cnt) or sits at the address in word 1 (ref).
#define DMA_TAG_CNT 0x10000000
#define DMA_TAG_REF 0x30000000

// VIF codes (bits 24-31 of a VIF word).
#define VIF_DIRECT 0x50000000
#define VIF_CHAIN_CMD 0x90000000

// GIFtag for one A+D register write: NLOOP 1 with EOP, NREG 1, REGS = A+D.
#define GIF_TAG_AD_LOW 0x8001
#define GIF_TAG_AD_HIGH 0x10000000
#define GIF_REG_AD 0xE

#define GS_REG_SCISSOR_1 0x40

// Display size, read by the scissor clamp (core global).
extern int occlViewParams[];

// GS register blocks streamed to the VU1 by reference.
extern unsigned int Gif_Tex_Flush[12];
extern unsigned int vu1GsRegsNormal[12];
extern unsigned int vu1GsRegsEffects[12];
extern unsigned int vu1GsRegsFont[44];

void VU1_setBufSizeByLevel(void);
void VU1_initChain(void);
void VU1_swapChain(void);
void VU1_addDataRef(void *data, int qcnt);
void VU1_addVIFcode(unsigned int vifcode);
void VU1_addGSregister(unsigned int reg, unsigned long value);
void VU1_setScissor(int left, int right, int top, int bottom);
void VU1_texFlush(void);
void VU1_gsRegsNormal(void);
void VU1_gsRegsEffects(void);
void VU1_gsRegsFont(void);
void Vif1ChainCmd(int command);

#endif
