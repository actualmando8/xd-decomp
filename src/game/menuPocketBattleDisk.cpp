// Decompiled from: menuPocketBattleDisk.cpp
// Address range: 0x8000E97C..0x8000F5E8 | size: 0xC6C

/*
  Battle Disk pocket menu - handles Battle Router disk selection.
  Contains cursor management, item list printing, and disk selection.
*/

/* Forward declarations */
void    menuItemBiosGetPtr(void*, s16);
void    windowGetActiveID(void);
void    menuSubCursorAnimeValGet(void*, void*);
void    winSpriteGetLayerID(void*, void*);
void    windowDrawSpriteCursor(void*, s32, s32, s32, s32, s32, s32);
void    winSpriteSetDisp(void*, s32);
void    menuSubCursorAnimeInit(void);
void    menuSubCursorAnimeMain(void);
void    menuSubCursorAnimeStart(void);
void    winSeqSetMenu(s32, s32);
void    GSmsgGetRect(s32);
void    GSmsgPrint2(s32, s32, s32, s32, s32);
void    spriteSetScissor(s32, s32, s32, s32);
void    spriteSetEnv(void);
void    spriteSetOffset(s32, s32);
void    spriteClearScissor(void);
void    menuPdaSubScrollBar(void*, s32, s32, s32, s32, s32);
void    menuPtPlaySe__FUl(u32);
void    menuCloseCustom(s32, s32, s32);
void    menuOpenCustom(s32, s32, s32, s32, s32, s32, s32);
void    menuBattleDiskOpenDoc(s32);
void    menuBattleDiskCloseDoc(void);
void    menuPocketButtonWait__Fv(void);
void    windowGetKeyRepeat(void);
void    menuPocketToolFloatToZero__FRff(float*, float);
void    memset(void*, s32, s32);
void    heroItemGetItemKindToItemAryPtr(void*, s32, void*, s32, s32, s32, s32);
void    itemCheckValid(void*);
void    itemBiosGetItemDataId(void*);
void    itemDataBiosGetPtr(u32);
void    itemDataBiosGetName(void*);
void    menuSpriteBiosGetPtr(s32, s16, s16, s16);
void    menuSpriteBiosGetValPtr(void*);
void    windowDrawSprite2(s32, s32, s32, s16, s16, s16, s32, s32);
void    deckDataVirtualDB_GetFlagData__FUs(u16);

/* Static data structure */
struct BattleDiskData {
    void* window_work;         // 0x0
    void* sprite_work;         // 0x4
    u32   nb_item_slot;        // 0x8
    s16   cursor_x;            // 0xC
    s16   cursor_y;            // 0xE
    u8    flag_14;             // 0x14
    u8    flag_15;             // 0x15
    float scroll_pos;          // 0x18
    u8    flag_1C;             // 0x1C
    u8    padding[0xB];        // 0x1D
    s8    scroll_byte;         // 0x67
};

static BattleDiskData g_battleDiskData;

/* Static float constants */
static const float const_255 = 255.0f;
static const float const_1 = 1.0f;
static const float const_7 = 7.0f;
static const float const_0033 = 0.033333335f;
static const float const_0 = 0.0f;
static const float const_neg30 = -30.0f;
static const float const_30 = 30.0f;

extern u32 g_2177[2];

/*
  Address: 0x8000E97C | size: 0x58
  menuPocketBattleDiskDrawLineCursor(void* win, void* spr)
  Draws the line cursor at the current cursor position.
*/
void menuPocketBattleDiskDrawLineCursor(void* win, void* spr) {
    void* item = menuItemBiosGetPtr(*(void**)spr, *(s16*)((u8*)spr + 6));
    s16 y = getCursorPositionY__Fv();
    s16 pos = *(s16*)((u8*)item + 8) + y;
    *(s16*)((u8*)spr + 0x52) = pos;
}

/*
  Address: 0x8000E9D4 | size: 0xC0
  menuPocketBattleDiskDrawBallCursor(void* win, void* spr)
  Draws the ball cursor with animation.
*/
void menuPocketBattleDiskDrawBallCursor(void* win, void* spr) {
    s32 animValues[2];
    animValues[0] = g_2177[0];
    animValues[1] = g_2177[1];
    animValues[2] = -1;
    
    s32 activeId = windowGetActiveID();
    if (*(s32*)((u8*)win + 4) == activeId) {
        menuSubCursorAnimeValGet(animValues, &animValues[2]);
    }
    
    s32 layer = winSpriteGetLayerID(win, spr);
    s16 y = getCursorPositionY__Fv();
    windowDrawSpriteCursor(
        animValues[2], win, 0, y, -1, 0xC2, 0
    );
    winSpriteSetDisp(spr, 0);
}

/*
  Address: 0x8000EA94 | size: 0x44
  getCursorPositionY()
  Calculates the Y position for the cursor based on scroll and page.
*/
s16 getCursorPositionY__Fv(void) {
    s16 page = g_battleDiskData.cursor_y;
    s16 y = page * 0x1E;
    if (g_battleDiskData.flag_14 == 0) {
        float f = g_battleDiskData.scroll_pos;
        y += (s16)(s64)f;
    }
    return y;
}

/*
  Address: 0x8000EAD8 | size: 0x74
  menuPocketBattleDiskDrawRollDown()
  Draws the roll-down indicator.
*/
void menuPocketBattleDiskDrawRollDown(void) {
    if (g_battleDiskData.flag_1C == 0) {
        return;
    }
    s16 pos = g_battleDiskData.cursor_x;
    s32 max = g_battleDiskData.nb_item_slot;
    if (pos + 8 < max) {
        float val = (const_1 - g_battleDiskData.scroll_pos) * const_255;
        g_battleDiskData.scroll_byte = (s8)(s64)val;
    } else {
        g_battleDiskData.scroll_byte = 0;
    }
}

/*
  Address: 0x8000EB4C | size: 0x68
  menuPocketBattleDiskDrawRollUp()
  Draws the roll-up indicator.
*/
void menuPocketBattleDiskDrawRollUp(void) {
    if (g_battleDiskData.flag_1C == 0) {
        return;
    }
    s16 pos = g_battleDiskData.cursor_x;
    if (pos <= 0) {
        float val = (const_1 - g_battleDiskData.scroll_pos) * const_255;
        g_battleDiskData.scroll_byte = (s8)(s64)val;
    } else {
        g_battleDiskData.scroll_byte = 0;
    }
}

/*
  Address: 0x8000EBB4 | size: 0x64
  menuPocketBattleDiskPageBar(void* win, void* spr)
  Draws the page scroll bar.
*/
void menuPocketBattleDiskPageBar(void* win, void* spr) {
    menuPdaSubScrollBar(
        win, *(s32*)((u8*)win + 4),
        &g_battleDiskData.nb_item_slot, 0x110, 8, 0xD2FF
    );
    winSpriteSetDisp(spr, 0);
}

/*
  Address: 0x8000EC18 | size: 0xF4
  menuPocketBattleDiskCtrl(void* work)
  Controls the battle disk menu state machine.
*/
void menuPocketBattleDiskCtrl(void* work) {
    s8 state = *(s8*)((u8*)work + 1);
    
    if (state == 0) {
        if (*(s8*)((u8*)work + 2) == 0) {
            winSeqSetMenu(0x3B, 0x60);
            *(u8*)((u8*)work + 2) = 1;
            menuSubCursorAnimeInit();
        }
    } else if (state == 2) {
        _controlCursor__34__Fv();
        menuPocketToolFloatToZero__FRff(&g_battleDiskData.scroll_pos, const_7);
        g_battleDiskData.scroll_pos += const_0033;
        if (g_battleDiskData.scroll_pos > const_1) {
            g_battleDiskData.scroll_pos = const_0;
        }
        menuSubCursorAnimeMain();
    } else if (state >= 2 && state < 4) {
        if (*(s8*)((u8*)work + 2) == 0) {
            winSeqSetMenu(0x3B, 0x64);
            *(u8*)((u8*)work + 2) = 1;
        }
    }
}

/*
  Address: 0x8000ED0C | size: 0x78
  menuPocketBattleDiskPrintItemKind(void* win, void* spr)
  Prints the item kind text.
*/
void menuPocketBattleDiskPrintItemKind(void* win, void* spr) {
    s32 rect = GSmsgGetRect(0x14D3);
    s16 width = rect >> 16;
    s32 layer = winSpriteGetLayerID(win, spr);
    s16 y = *(s16*)((u8*)spr + 0x54);
    s16 pos = (y - width) >> 1;
    GSmsgPrint2(layer, 0, pos, -1, 0x14D3);
}

/*
  Address: 0x8000ED84 | size: 0xEC
  menuPocketBattleDiskPrintItemList(void* win, void* spr)
  Prints the list of battle disks with scissor clipping.
*/
void menuPocketBattleDiskPrintItemList(void* win, void* spr) {
    void* itemA = menuItemBiosGetPtr(*(void**)win, 0x11B);
    void* itemB = menuItemBiosGetPtr(*(void**)win, *(s16*)((u8*)spr + 6));
    s32 layer = winSpriteGetLayerID(win, spr);
    
    s16 wA = *(s16*)((u8*)itemA + 6);
    s16 wB = *(s16*)((u8*)itemB + 6);
    s16 hA = *(s16*)((u8*)itemA + 8);
    s16 hB = *(s16*)((u8*)itemB + 8);
    s16 x = *(s16*)((u8*)itemA + 0xA);
    s16 y = *(s16*)((u8*)itemA + 0xC);
    
    spriteSetScissor(x, y, wB - wA, hB - hA);
    spriteSetEnv();
    printItemList__34__FP14tagWINDOW_WORKP14tagSPRITE_WORK(win, spr);
    spriteSetOffset(0, 0);
    spriteClearScissor();
    spriteSetEnv();
}

/*
  Address: 0x8000EE70 | size: 0x8
  menuPocketBattleDiskCursor()
  Stub - returns 0.
*/
s32 menuPocketBattleDiskCursor(void) {
    return 0;
}

/*
  Address: 0x8000EE78 | size: 0xC8
  menuPocketBattleDiskMain(void* win, void* spr)
  Main loop for battle disk selection.
*/
s32 menuPocketBattleDiskMain(void* win, void* spr) {
    memset(&g_battleDiskData, 0, 0x24);
    g_battleDiskData.window_work = win;
    g_battleDiskData.sprite_work = spr;
    g_battleDiskData.nb_item_slot = getNbItemSlot__34__Fv();
    g_battleDiskData.flag_1C = 0;
    g_battleDiskData.cursor_x = 0;
    
    while (1) {
        g_battleDiskData.flag_1C = 1;
        s32 item = selectItem__34__Fv();
        g_battleDiskData.flag_1C = 0;
        if (item == 0) {
            break;
        }
        if (item - 0x215 != 0) {
            menuBattleDiskOpenDoc(item);
            menuPocketButtonWait__Fv();
            menuBattleDiskCloseDoc();
        }
    }
    
    menuCloseCustom(0x3B, 0, 1);
    return item;
}

/*
  Address: 0x8000EF40 | size: 0x2C4
  _controlCursor()
  Handles cursor movement with arrow keys and C-button.
*/
void _controlCursor__34__Fv(void) {
    s32 keys = windowGetKeyRepeat();
    s32 maxItems = g_battleDiskData.nb_item_slot;
    float threshold = const_30;
    float pos = g_battleDiskData.scroll_pos;
    s32 maxPage = (maxItems + 7) >> 3;
    
    // ... cursor control logic with page/item navigation
    // Handles left/right arrow for page, up/down for items within page
    // C-button cycles through items
}

/*
  Address: 0x8000F204 | size: 0x154
  printItemList(tagWINDOW_WORK* win, tagSPRITE_WORK* spr)
  Prints the item list with names and used marks.
*/
void printItemList__34__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* win, void* spr) {
    // Iterates through visible items and prints names
    // Shows used mark for disks that have been used
}

/*
  Address: 0x8000F358 | size: 0xAC
  diskUsedMarkDisplay(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, int index)
  Displays the used mark on a disk slot.
*/
void diskUsedMarkDisplay__34__FP14tagWINDOW_WORKP14tagSPRITE_WORKi(void* win, void* spr, int index) {
    // Gets sprite for used mark (ID 0xD9) and draws it
}

/*
  Address: 0x8000F404 | size: 0x6C
  selectItem()
  Opens custom menu and gets selected item ID.
*/
s32 selectItem__34__Fv(void) {
    s32 activeId = windowGetActiveID();
    menuOpenCustom(0x3B, activeId, 0, 0, 1, 0, 0);
    if (r3 == -1) {
        return 0;
    }
    s32 pos = g_battleDiskData.cursor_x + g_battleDiskData.cursor_y;
    *(s32*)((u8*)&g_battleDiskData + 0x20) = pos;
    return getItemIDFromMenuPos__34__Fi(pos);
}

/*
  Address: 0x8000F470 | size: 0xB8
  getItemIDFromMenuPos(int pos)
  Gets the item ID at the given menu position.
*/
s32 getItemIDFromMenuPos__34__Fi(int pos) {
    void** itemAry = heroItemGetItemKindToItemAryPtr(
        &g_battleDiskData.window_work, 7, 0, 0, 0, 0
    );
    s32 result = -1;
    s32 count = 0;
    
    for (s32 i = 0; i < *(s16*)r5; i++) {
        if (itemCheckValid(itemAry)) {
            count++;
            if (count < pos) {
                // Continue searching
            } else {
                result = itemBiosGetItemDataId(itemAry);
                break;
            }
        }
        itemAry++;
    }
    
    return result;
}

/*
  Address: 0x8000F528 | size: 0x98
  getNbItemSlot()
  Counts the number of valid item slots.
*/
s32 getNbItemSlot__34__Fv(void) {
    void** itemAry = heroItemGetItemKindToItemAryPtr(
        &g_battleDiskData.window_work, 7, 0, 0, 0, 0
    );
    s32 count = 0;
    
    for (s32 i = 0; i < *(s16*)r5; i++) {
        if (itemCheckValid(itemAry)) {
            count++;
        }
        itemAry++;
    }
    
    return count;
}

/*
  Address: 0x8000F5C0 | size: 0x28
  getItemNameMsg(unsigned long itemID)
  Gets the message ID for an item name.
*/
s32 getItemNameMsg__34__FUl(u32 itemID) {
    itemDataBiosGetPtr(itemID);
    return itemDataBiosGetName(r3);
}
