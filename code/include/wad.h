#ifndef WAD_H
#define WAD_H

// Where a file lives on the disc: start sector and length in sectors.
struct WadEntry {
    int offset;
    int length;
};

// The boot WAD's table of contents (DL g_wad.misc); only the entries known so far.
struct BootAssets {
    int unk_0[2];
    WadEntry debugFont;
    WadEntry savegame;
};

extern BootAssets bootAssets;

#endif
