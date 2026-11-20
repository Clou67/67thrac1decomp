# MB_SetZBoundsFromGround

The 0xC0-byte attempt copies the moby's position into two ground-probe
endpoints, uses `CollLine` with the ground probe flags, and sets the height
bounds from the hit point with 0.2 units of padding.

Four words differ. Retail addresses the hit point at 0x28 from the
collision output base at `MemSlots + 0x40`. The attempt emits two loads
at 0x68 from `MemSlots`. In the no-hit branch the two stores that clear
the bounds are reversed.
