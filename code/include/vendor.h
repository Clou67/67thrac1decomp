#ifndef VENDOR_H
#define VENDOR_H

// Items the vendor sells, ended by VENDOR_ITEM_NONE. The low bits are the item id;
// VENDOR_ITEM_AMMO marks an entry that sells ammo for that weapon.
#define VENDOR_ITEM_COUNT 12
#define VENDOR_ITEM_ID_MASK 0x3F
#define VENDOR_ITEM_AMMO 0x40
#define VENDOR_ITEM_NONE 0xFF

extern unsigned char PurchasableVendorItems[8]; // fakematch

#endif
