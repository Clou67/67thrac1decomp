# MB_WrapRot

The existing flags produce all 0x54 bytes, with two differing instructions.
Both updating the angle in steps and passing `(angle + pi) / turn` directly
to `FastFrac` put the sum in `$f12`. Retail puts it in `$f0` and reads
that register when dividing by one full turn. Keep the assembly until a
natural expression produces the same register allocation.
