# CreateMotionBlur

The partial match initializes the source and marks the trail active before
clearing the history head, history length, and copy count. Independent and
chained zero assignments both produce 0x28 bytes. GCC schedules the copy
count store ahead of the two halfword stores, while retail clears the copy
count last. The three stores at offsets 0x14 through 0x1C differ.
