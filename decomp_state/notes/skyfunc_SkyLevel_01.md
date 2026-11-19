# SkyLevel_01

A switch on shell indices 2, 3, and 4 reproduces the rotation cases and their shared Euler-to-matrix call. Each case masks worldUpdateTime to the shell's period and maps it to [-pi, pi). The default calls FastMtx4Identity.

The best attempt has the original size (0x180) and matches from offset 0x60 onward with relocation fields masked. Clearing the local rotation through two unsigned long members leaves 22 differing words. The early differences include the register saves and reuse of the first Sky load. Retail clears the vector with a single sq from the zero register and reloads Sky before checking the shell count.

A quadword assignment generates a zero in a general-purpose register before sq. Aggregate and component initialization change the frame or store sequence. Calling FastVecZero adds a call.
