#ifndef VENDOR_H
#define VENDOR_H

// Items the vendor sells, ended by VENDOR_ITEM_NONE. The low bits are the item id;
// VENDOR_ITEM_AMMO marks an entry that sells ammo for that weapon.
#define VENDOR_ITEM_COUNT 12
#define VENDOR_ITEM_ID_MASK 0x3F
#define VENDOR_ITEM_AMMO 0x40
#define VENDOR_ITEM_NONE 0xFF

// Temporary: marks a core small-data variable until the core has its own build.
extern unsigned char PurchasableVendorItems[VENDOR_ITEM_COUNT] __attribute__((section(".sdata")));

struct MobyInstance;

struct VendorRenderState {
    char unk_00[0x24];
    MobyInstance *dudeMoby;
    char unk_28[4];
    char *scrollText;
    char unk_30[0x14];
    int scrollPosition;
};

extern VendorRenderState VendorRender;

void Vendor_ResetHUDPass(void);

void Vendor_CopyScrollString(char *text);

#endif
