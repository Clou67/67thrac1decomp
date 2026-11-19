#ifndef MATHFUNC_INLINE_H
#define MATHFUNC_INLINE_H

#include "moby.h"

// Copies a quadword vector through $2, as the original's inline vector helpers do.
static inline void CopyVec4Inline(Vec4 *destination, Vec4 *source)
{
    __asm__ volatile("lq $2, 0(%1)\n\tsq $2, 0(%0)" : : "r"(destination), "r"(source) : "$2", "memory");
}

// Retail clears an aligned vector directly from the zero register.
static inline void ClearVec4Inline(Vec4 *vector)
{
    __asm__ volatile("sq $0, %0" : "=m"(*vector) : : "memory");
}

#endif
