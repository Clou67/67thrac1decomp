# DoSkyGifPaging

The retail code patches the opening DMA NEXT tag, optionally emits the GIF texture upload and flush, then links the sky chain back into the current packet chain and resets the texture cursor.

Writes through the existing DmaTag layout produce 256 bytes versus the original 300. Using Vu1ChainCursor word views for both markers preserves more pointer reloads and reaches 304 bytes. It still changes instruction order, including hoisting the pending-load check and dropping the GP-relative delay-slot reload of vu1_bufPtr. Pointer-typed address stores and volatile declarations were also tested without a match. The meaning of the pending-load word at 0x0016A474 still needs confirmation.

Carrying the first outgoing tag pointer across the optional upload, with separate cursor increments and word views for both markers, produces the original 300-byte size with 50 differing words. This gets the conditional reload and call positions right, but the register allocation and marker stores still diverge.
