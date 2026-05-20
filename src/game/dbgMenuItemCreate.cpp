// Decompiled from: dbgMenuItemCreate.cpp
// Address range: 0x8000E1F4..0x8000E53C | size: 0x348

/*
  Debug menu for item creation.
  Allows players to create items by selecting item ID and quantity.
  Uses keyboard input to navigate and modify values.
*/

/* Global data */
static u32 initFlag$1274;
static u32 Num;
static u32 ItemID;

/* External data */
extern u32 item_data_index_number;

/* Forward declarations */
static void nbItemCtrl(void);
static void itemNameCtrl(void);

/*
  Address: 0x8000E1F4 | size: 0xD0
  nbItemCtrl()
  Controls the item quantity (Num) using keyboard input.
  Bit 28 (Y key): +1
  Bit 21 (PageUp): +10
  Bit 29 (X key): -1
  Bit 22 (PageDown): -10
  Max value: 0x3E7 (999)
*/
static void nbItemCtrl(void) {
    void* keyInfo = windowGetKeyInfo();
    u16 keys = *(u16*)((u8*)keyInfo + 6);
    
    // Y key (bit 28): Increment by 1
    if (keys & 0x8000) {
        Num++;
        if (Num > 0x3E7) {
            Num = 0x3E7;
        }
    }
    
    // PageUp (bit 21): Increment by 10
    if (keys & 0x2000) {
        Num += 10;
        if (Num > 0x3E7) {
            Num = 0x3E7;
        }
    }
    
    // X key (bit 29): Decrement by 1
    if (keys & 0x4000) {
        if (Num > 0) Num--;
    }
    
    // PageDown (bit 22): Decrement by 10
    if (keys & 0x1000) {
        if (Num >= 10) Num -= 10;
        else Num = 0;
    }
}

/*
  Address: 0x8000E2C4 | size: 0xE0
  itemNameCtrl()
  Controls the item ID using keyboard input.
  Bit 28 (Y key): +1
  Bit 21 (PageUp): +10
  Bit 29 (X key): -1
  Bit 22 (PageDown): -10
  Wraps around based on item_data_index_number
*/
static void itemNameCtrl(void) {
    void* keyInfo = windowGetKeyInfo();
    u16 keys = *(u16*)((u8*)keyInfo + 6);
    
    // Y key (bit 28): Increment by 1
    if (keys & 0x8000) {
        ItemID++;
        u32 maxId = *(u32*)((u8*)&item_data_index_number);
        if (ItemID >= maxId) {
            ItemID = maxId - 1;
        }
    }
    
    // PageUp (bit 21): Increment by 10
    if (keys & 0x2000) {
        ItemID += 10;
        u32 maxId = *(u32*)((u8*)&item_data_index_number);
        if (ItemID >= maxId) {
            ItemID = maxId - 1;
        }
    }
    
    // X key (bit 29): Decrement by 1
    if (keys & 0x4000) {
        if (ItemID > 0) ItemID--;
    }
    
    // PageDown (bit 22): Decrement by 10
    if (keys & 0x1000) {
        if (ItemID >= 10) ItemID -= 10;
        else ItemID = 0;
    }
}

/*
  Address: 0x8000E3A4 | size: 0xB8
  menuDbgItemCreateCursor(void* param)
  Controls cursor position (0 = item ID, 1 = quantity).
  Bit 31 (A key): Decrement cursor
  Bit 30 (B key): Increment cursor
  Calls itemNameCtrl or nbItemCtrl based on cursor position.
*/
void menuDbgItemCreateCursor(void* param) {
    s16 cursor = *(s16*)((u8*)param + 0x9E);
    void* keyInfo = windowGetKeyInfo();
    u16 keys = *(u16*)((u8*)keyInfo + 6);
    
    // A key (bit 31): Decrement cursor
    if (keys & 0x8000) {
        cursor--;
        *(s16*)((u8*)param + 0x9E) = cursor;
        if (cursor < 0) {
            *(s16*)((u8*)param + 0x9E) = 0;
        }
    }
    
    // B key (bit 30): Increment cursor
    if (keys & 0x4000) {
        cursor++;
        *(s16*)((u8*)param + 0x9E) = cursor;
        if (cursor > 1) {
            *(s16*)((u8*)param + 0x9E) = 1;
        }
    }
    
    cursor = *(s16*)((u8*)param + 0x9E);
    if (cursor == 0) {
        itemNameCtrl();
    } else if (cursor == 1) {
        nbItemCtrl();
    }
    
    return;
}

/*
  Address: 0x8000E45C | size: 0xE0
  menuDbgItemCreate()
  Main entry point for the debug item creation menu.
  Opens menu 0x24, validates item data, and adds items to hero inventory.
*/
void menuDbgItemCreate(void) {
    if (initFlag$1274 == 0) {
        ItemID = 1;
        initFlag$1274 = 1;
    }
    Num = 1;
    
    while (1) {
        // Open menu 0x24 with flag 1
        s32 result = menuOpen(0x24, 1);
        if (result == -1) {
            // Menu closed - cleanup
            menuClose(0x24);
            menuCloseSync(0x24, 1);
            return;
        }
        
        // Validate item ID
        if (!itemDataCheckValid(ItemID)) {
            continue;
        }
        
        // Validate quantity
        if (Num < 1 || Num > 0x3E7) {
            continue;
        }
        
        // Open menu 0x55
        s32 menu55 = menuOpen(0x55, 1);
        menuCloseCustom(0x55, 0, 1);
        
        if (menu55 != 0) {
            continue;
        }
        
        // Add item to hero inventory
        heroItemAddItemDataId(0, ItemID, Num, -1);
    }
}
