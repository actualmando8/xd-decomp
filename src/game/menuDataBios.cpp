// Decompiled from: menuDataBios.cpp
// Address range: 0x8007C870..0x8007CD64 | size: 0x4F4

/* Forward declarations */
void*   windowGetCursorToItem(void);
void*   menuSpriteBiosGetPtr(s32 idx);
void*   menuSpriteBiosGetValPtr(void* bios, s32 idx);
s32     pokecoloGetLanguage(void);
void*   menuItemBiosGetPtr(s32 type, s32 idx);
void*   menuDataBiosGetPtr(s32 idx);
s32     dbgMenuGetLayerID(void);

/* External globals */
extern void* menu_se;
extern s32   menu_se_number;
extern s32   _menu_seq_number;
extern void* _menu_seq[];
extern s32   _menu_sprite_number;
extern void* _menu_sprite[];
extern s32   _menu_data_number;
extern void* _menu_data[];
extern void* _menu_item[];
extern void* _menu_itemmx[];
extern void* _menu_item_tool[];
extern void* _menu_item_debug[];
extern void* _menu_item_pda[];
extern void* _menu_itembt[];
extern void* _menu_item_xd[];

/*
  Address: 0x8007C870 | size: 0x78
  menuBiosGetCursorSize(void* bios, s32 idx)
  Returns cursor size based on item index.
  Special sizes for indices 0x7D, 0xBE, 0xC1-0xC2, 0xC3+.
*/
s32 menuBiosGetCursorSize(void* bios, s32 idx) {
    void* item = windowGetCursorToItem();
    void* spriteBios = menuSpriteBiosGetPtr(idx);
    menuSpriteBiosGetValPtr(spriteBios, idx);
    
    s16 cursorIdx = ((s16*)item)[0xE / 2];
    s32 size = 0;
    
    if (cursorIdx == 0x7D || cursorIdx == 0xBE) {
        size = 0x147;
    } else if (cursorIdx >= 0xC1 && cursorIdx < 0xC3) {
        size = 0x14D;
    } else if (cursorIdx < 0x7D) {
        // default 0
    } else if (cursorIdx >= 0xC3) {
        // default 0
    }
    
    return size;
}

/*
  Address: 0x8007C8E8 | size: 0x70
  menuSeBiosGetSndId(void* bios, s32 idx)
  Gets sound effect ID from bios struct based on index.
  Maps index to offset within bios struct.
*/
s16 menuSeBiosGetSndId(void* bios, s32 idx) {
    s16 result = 0;
    
    switch (idx) {
        case 1: result = ((s16*)bios)[2]; break;
        case 2: result = ((s16*)bios)[3]; break;
        case 3: result = ((s16*)bios)[4]; break;
        case 4: result = ((s16*)bios)[0]; break;
        case 5: result = ((s16*)bios)[1]; break;
        case 6: result = ((s16*)bios)[5]; break;
        default: result = 0; break;
    }
    
    return result;
}

/*
  Address: 0x8007C958 | size: 0x38
  menuSeBiosGetPtr(s32 idx)
  Gets pointer to SE bios entry by index.
  Returns NULL if menu_se not initialized or index out of range.
*/
void* menuSeBiosGetPtr(s32 idx) {
    if (menu_se == 0) return 0;
    
    s32 count = _menu_seq_number; // TODO: verify - uses menu_se_number
    if (idx >= count) return 0;
    
    return &((void**)menu_se)[idx];
}

/*
  Address: 0x8007C990 | size: 0x28
  menuSeqBiosGetPtr(s32 idx)
  Gets pointer to sequence bios entry by index.
*/
void* menuSeqBiosGetPtr(s32 idx) {
    if (idx >= _menu_seq_number) return 0;
    return _menu_seq[idx];
}

/*
  Address: 0x8007C9B8 | size: 0x90
  menuSpriteBiosGetValPtr(void* bios, s32 idx)
  Gets pointer to value array in sprite bios, indexed by language.
  Language mapping: 0,1,2,3,4,5,6 -> 0,1,2,3,4 (clamped)
*/
void* menuSpriteBiosGetValPtr(void* bios, s32 idx) {
    s32 lang = pokecoloGetLanguage();
    s32 langIdx;
    
    if (lang == 0 || lang == 1) {
        langIdx = 0;
    } else if (lang == 2) {
        langIdx = 0;
    } else if (lang == 3) {
        langIdx = 1;
    } else if (lang == 4) {
        langIdx = 2;
    } else if (lang == 5) {
        langIdx = 3;
    } else if (lang == 6) {
        langIdx = 4;
    } else {
        langIdx = 0;
    }
    
    return (void*)((u8*)bios + langIdx * 0xC + 8);
}

/*
  Address: 0x8007CA48 | size: 0x28
  menuSpriteBiosGetPtr(s32 idx)
  Gets pointer to sprite bios entry by index.
  Each entry is 0x48 bytes.
*/
void* menuSpriteBiosGetPtr(s32 idx) {
    if (idx >= _menu_sprite_number) return 0;
    return _menu_sprite[idx];
}

/*
  Address: 0x8007CA70 | size: 0x48
  menuItemBiosSetXY(s32 type, s32 idx, s16 x, s16 y)
  Sets X/Y position in menu item bios.
*/
void menuItemBiosSetXY(s32 type, s32 idx, s16 x, s16 y) {
    void* item = menuItemBiosGetPtr(type, idx);
    if (item != 0) {
        ((s16*)item)[3] = x;
        ((s16*)item)[4] = y;
    }
}

/*
  Address: 0x8007CAB8 | size: 0x44
  menuItemBiosGetSelectFlag(s32 type, s32 idx)
  Gets select flag (bit 0) from menu item bios.
  Returns 0 or 1.
*/
s32 menuItemBiosGetSelectFlag(s32 type, s32 idx) {
    void* item = menuItemBiosGetPtr(type, idx);
    if (item == 0) return 0;
    
    u8 flags = ((u8*)item)[0];
    s32 bit = (flags >> 0) & 0x1;
    // Normalize to 0 or 1
    return (bit != 0) ? 1 : 0;
}

/*
  Address: 0x8007CAFC | size: 0x44
  menuItemBiosSetSelectFlag(s32 type, s32 idx, s32 flag)
  Sets select flag (bit 0) in menu item bios.
*/
void menuItemBiosSetSelectFlag(s32 type, s32 idx, s32 flag) {
    void* item = menuItemBiosGetPtr(type, idx);
    if (item == 0) return;
    
    u8 flags = ((u8*)item)[0];
    flag = flag & 0x1;
    flags = (flags & ~0x1) | flag;
    ((u8*)item)[0] = flags;
}

/*
  Address: 0x8007CB40 | size: 0x3C
  menuItemBiosGetLayerID(s32 type, s32 idx)
  Gets layer ID for menu item.
  Returns debug layer ID if item type is 3 (debug), otherwise 7.
*/
s32 menuItemBiosGetLayerID(s32 type, s32 idx) {
    void* data = menuDataBiosGetPtr(type);
    u8 flags = ((u8*)data)[0];
    s32 itemClass = (flags >> 3) & 0x1;
    
    if (itemClass == 3) {
        return dbgMenuGetLayerID();
    }
    return 7;
}

/*
  Address: 0x8007CB7C | size: 0xFC
  menuItemBiosGetPtr(s32 type, s32 idx)
  Gets pointer to menu item based on type and index.
  Type 0: _menu_item
  Type 1: _menu_itemmx
  Type 2: _menu_item_tool
  Type 3: _menu_item_debug
  Type 4: _menu_item_pda
  Type 5: _menu_itembt
  Type 6: _menu_item_xd
*/
void* menuItemBiosGetPtr(s32 type, s32 idx) {
    void* data = menuDataBiosGetPtr(type);
    u8 flags = ((u8*)data)[0];
    s32 itemClass = (flags >> 3) & 0x7;
    
    switch (itemClass) {
        case 0: return _menu_item[idx];
        case 1: return _menu_itemmx[idx];
        case 2: return _menu_item_tool[idx];
        case 3: return _menu_item_debug[idx];
        case 4: return _menu_item_pda[idx];
        case 5: return _menu_itembt[idx];
        case 6: return _menu_item_xd[idx];
        default: return 0;
    }
}

/*
  Address: 0x8007CC78 | size: 0x58
  menuDataBiosGetXY(s32 idx, s16* x, s16* y)
  Gets X/Y position from menu data bios, storing in provided pointers.
*/
void menuDataBiosGetXY(s32 idx, s16* x, s16* y) {
    void* data = menuDataBiosGetPtr(idx);
    if (x != 0) {
        *x = ((s16*)data)[4];
    }
    if (y != 0) {
        *y = ((s16*)data)[5];
    }
}

/*
  Address: 0x8007CCD0 | size: 0x40
  menuDataBiosSetXY(s32 idx, s16 x, s16 y)
  Sets X/Y position in menu data bios.
*/
void menuDataBiosSetXY(s32 idx, s16 x, s16 y) {
    void* data = menuDataBiosGetPtr(idx);
    ((s16*)data)[4] = x;
    ((s16*)data)[5] = y;
}

/*
  Address: 0x8007CD10 | size: 0x24
  menuDataBiosGetDispMax(s32 idx)
  Gets display max value from menu data bios (byte offset 3).
*/
u8 menuDataBiosGetDispMax(s32 idx) {
    void* data = menuDataBiosGetPtr(idx);
    return ((u8*)data)[3];
}

/*
  Address: 0x8007CD34 | size: 0x30
  menuDataBiosGetPtr(s32 idx)
  Gets pointer to menu data entry by index.
  Clamps negative indices to 0, and out-of-range to 1.
*/
void* menuDataBiosGetPtr(s32 idx) {
    if (idx < 0) idx = 0;
    
    if (idx >= _menu_data_number) {
        idx = 1;
    }
    
    return _menu_data[idx];
}
