#ifndef MATHINLINE_H
#define MATHINLINE_H

#include "moby.h"

// Copies a quadword vector through $2, as the original's inline vector helpers do.
static inline void CopyVec4(Vec4 *destination, Vec4 *source)
{
    __asm__ volatile("lq $2, 0(%1)\n\tsq $2, 0(%0)" : : "r"(destination), "r"(source) : "$2", "memory");
}

#endif
