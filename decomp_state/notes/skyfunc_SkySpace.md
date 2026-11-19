# SkySpace

The closest C++ attempt has the original size (0x240). Comparing the object with relocation fields masked leaves two differences at offsets 0x1B8 and 0x1BC. The compiler emits the high half of the sky-origin address before adding 0x30 to the matrix address. Retail does these two instructions in the opposite order before the same quadword copy.

Use the six-case shell switch, including the fallthrough from shell 0 and the explicit scale reset in case 1. A same-file initialized float for the space sky angle reproduces the GP-relative loads. The original float is at 0x001604C4 and is written by Space_UpdateCutsceneScene. The origin vector is at 0x00160520. If the C++ matches, place the float and the switch jump table at their original addresses.

Using a local matrix pointer, naming the translation or origin pointer separately, and reversing the inline helper's operand order all kept the same two-instruction swap. A struct assignment changed the copy and register allocation.
