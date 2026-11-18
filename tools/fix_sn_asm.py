#!/usr/bin/env python3
"""Post-process splat output for the SN assembler (ps2eeas).

ps2eeas pads DIV-type instructions near branches (an R5900 erratum
workaround) and has no switch to turn that off. The original bytes are
already padded where needed, so those instructions are written as raw words
from splat's comment field. ps2eeas does not count a .word as filling a
branch delay slot, so a branch or jump that follows a raw word in a delay
slot is written as a raw word too (its offset or target is position-fixed).
"""
import re
import sys
from pathlib import Path

DIV_OPS = {"div", "divu", "div1", "divu1", "ddiv", "ddivu", "pdivw", "pdivuw", "pdivbw",
           "div.s", "sqrt.s", "rsqrt.s"}
LINE = re.compile(r"^(\s*/\* [0-9A-F]+ [0-9A-F]+ ([0-9A-F]{8}) \*/)(\s*)(\S+)(.*)$")


def is_branch(op):
    return op.startswith("b") or op.startswith("j")


def raw(match):
    word = int.from_bytes(bytes.fromhex(match.group(2)), "little")
    return "%s%s.word 0x%08X /* %s%s */" % (match.group(1), match.group(3), word, match.group(4), match.group(5))


def fix(path):
    lines = path.read_text().split("\n")
    changed = False
    previous_branch = False
    # ps2eeas still sees an open delay slot after raw words placed in one.
    slot_open = False

    for index, line in enumerate(lines):
        match = LINE.match(line)

        if not match:
            continue

        op = match.group(4)
        in_delay_slot = previous_branch or slot_open

        if op in DIV_OPS:
            lines[index] = raw(match)
            changed = True
            slot_open = in_delay_slot
            previous_branch = False
        elif slot_open and is_branch(op):
            lines[index] = raw(match)
            changed = True
            previous_branch = False
        else:
            slot_open = False
            previous_branch = is_branch(op)

    if changed:
        path.write_text("\n".join(lines))

    return changed


def main(root):
    count = sum(fix(path) for path in Path(root).rglob("*.s"))
    print("fix_sn_asm: rewrote %d files" % count)


if __name__ == "__main__":
    main(sys.argv[1] if len(sys.argv) > 1 else "code/_generated/novalis")
