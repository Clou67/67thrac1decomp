#!/usr/bin/env python3

import os
import shutil
import sys

from pathlib import Path

import splat
import splat.scripts.split as split

ROOT = Path(__file__).parent.resolve()

BASENAME = "SCUS_971.99"
CONFIG_FILE ="config/RC1.yaml"
NOVALIS_CONFIG_FILE = "config/novalis/novalis.yaml"


def main():
    # `python3 configure.py novalis` splits the Novalis level overlay instead of the boot ELF.
    config = NOVALIS_CONFIG_FILE if "novalis" in sys.argv[1:] else CONFIG_FILE
    split.main([Path(config)], modes="all", verbose=True)


if __name__ == "__main__":
    main()
