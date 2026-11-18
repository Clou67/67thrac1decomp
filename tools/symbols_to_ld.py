#!/usr/bin/env python3
"""Turn splat symbol_addrs files into a linker script of PROVIDE() definitions.

Symbols an object defines win; the rest (core functions and globals, and
overlay symbols still inside INCLUDE_ASM data) resolve to their addresses.
"""
import re
import sys

SYMBOL = re.compile(r"^\s*([A-Za-z_][\w.$]*)\s*=\s*(0x[0-9A-Fa-f]+|\d+)\s*;")


def main(output, inputs):
    lines = []

    for path in inputs:
        for line in open(path):
            match = SYMBOL.match(line)

            if match:
                lines.append("PROVIDE(%s = %s);" % (match.group(1), match.group(2)))

    with open(output, "w") as file:
        file.write("\n".join(lines) + "\n")


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2:])
