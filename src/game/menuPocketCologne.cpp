// Decompiled from: menuPocketCologne.cpp
// Address range: 0x80063560..0x80063D1C | size: 0x7BC

/* Forward declarations */
void*   itemDataBiosGetPtr(s32 itemId);
s32     itemDataBiosGetKind(void* itemData);
s32     itemCheckValid(void* item);
s32     itemGetStatus(void* item, s32 a, s16 b, s32 c);
s32     itemBiosGetNum(void* item);
void*   heroItemGetItemKindToItemAryPtr(s32 a, s32 kind, s32 b, s32 c, s32 d);
void*   menuItemBiosGetPtr(s32 menuId, s32 itemId);
s32     windowGetActiveID(void);
void    menuSubCursorAnimeValGet(void* a, void* b);
s32     winSpriteGetLayerID(void* window, void* work);
void    windowDrawSpriteCursor(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g);
void    winSpriteSetDisp(void* work, s32 disp);
void*   GSmsgGetRect(s32 msgId);
void    GSmsgPrint2(s32 layer, s32 x, s32 y, s32 a, s32 msgId);
void    msgctrlSetValue(s32 ctrlId, s32 value);
s32     windowGetKeyRepeat(void);
void    menuSubCursorAnimeStart(void);
void    winSeqSetMenu(s32 seqId, s32 menuId);
void    menuSubCursorAnimeInit(void);
void    menuSubCursorAnimeMain(void);
void    menuOpenCustom(s32 menuId, s32 a, void* arg, s32 b, s32 c, s32 d);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 sync);

/* BSS data */
static f32 ActMenuCursorBlinkTime;
static s32 first$1990;
static s8  init$1991;

/* SData2 constants */
static const f32 float_0 = 0.0f;
static const f32 float_0_0333 = 0.033333335f;
static const f32 float_1 = 1.0f;

/* Data tables */
static const s32 itemIds_2041[] = { 0x130, 0x12F, 0x12E, 0x12D };
static const s32 cursorIds_2063[] = { 0x12C, 0x12B, 0x12A, 0x129 };

/*
  Address: 0x80063560 | size: 0xE0
  getItemNum__FUs(u16 itemId)
  Gets the total number of an item in the player's inventory.
*/
s32 getItemNum__FUs(u16 itemId) {
    itemDataBiosGetPtr(itemId);
    s32 kind = itemDataBiosGetKind();
    void** itemArray = heroItemGetItemKindToItemAryPtr(0, kind, 0, 0, 0);
    if (!itemArray) return 0;
    
    s32 total = 0;
    u16 itemIdClear = itemId & 0xFFFF;
    s16 maxIdx = ((s16*)&itemId)[1];
    
    for (s16 i = 0; i < maxIdx; i++) {
        if (itemCheckValid(itemArray)) {
            s32 itemKind = itemGetStatus(itemArray, 0, 0x1B, 0);
            if (itemKind == itemIdClear) {
                s32 num = itemBiosGetNum(itemArray);
                total += num;
            }
        }
        itemArray = (void**)((s32*)itemArray + 1);
    }
    
    return total;
}

/*
  Address: 0x80063640 | size: 0x44
  getStockMax__FUs(u16 itemId)
  Gets the maximum stock of an item.
*/
s32 getStockMax__FUs(u16 itemId) {
    itemDataBiosGetPtr(itemId);
    s32 kind = itemDataBiosGetKind();
    heroItemGetItemKindToItemAryPtr(0, kind, 0, 0, 0);
    return ((s16*)&itemId)[1];
}

/*
  Address: 0x80063684 | size: 0x28
  getItemName__FUl(u32 itemId)
  Gets the name of an item.
*/
s32 getItemName__FUl(u32 itemId) {
    itemDataBiosGetPtr(itemId & 0xFFFF);
    return itemDataBiosGetName();
}

/*
  Address: 0x800636AC | size: 0x70
  menuPocketColognDrawLineCursor(void* window, void* work)
  Draws the line cursor for the cologne menu.
*/
void menuPocketColognDrawLineCursor(void* window, void* work) {
    s32 menuId = ((s32*)window)[4 / 4];
    s16 itemId = ((s16*)work)[6 / 2];
    void* menuItem = menuItemBiosGetPtr(menuId, itemId);
    s32 lineHeight = getLineHeight__FP14tagWINDOW_WORK(window);
    s16 lineIdx = ((s16*)window)[0x9E / 2];
    s16 baseY = ((s16*)menuItem)[8 / 2];
    s16 y = baseY + lineHeight * lineIdx;
    ((s16*)work)[0x52 / 2] = y;
}

/*
  Address: 0x8006371C | size: 0x64
  getLineHeight__FP14tagWINDOW_WORK(void* window)
  Gets the line height for the menu.
*/
s32 getLineHeight__FP14tagWINDOW_WORK(void* window) {
    s32 menuId = ((s32*)window)[4 / 4];
    void* item1 = menuItemBiosGetPtr(menuId, 0x12B);
    void* item2 = menuItemBiosGetPtr(menuId, 0x12C);
    s16 y1 = ((s16*)item1)[8 / 2];
    s16 y2 = ((s16*)item2)[8 / 2];
    s32 diff = y2 - y1;
    return (diff < 0) ? -diff : diff;
}

/*
  Address: 0x80063780 | size: 0xF4
  menuPocketColognDrawCursor(void* window, void* work)
  Draws the cursor for the cologne menu.
*/
s32 menuPocketColognDrawCursor(void* window, void* work) {
    s16 lineIdx = ((s16*)window)[0x9E / 2];
    s16 itemId = ((s16*)work)[6 / 2];
    
    s32 cursorId = cursorIds_2063[lineIdx];
    if (cursorId == itemId) {
        // Draw cursor animation
        s32 activeWin = windowGetActiveID();
        s32 menuId = ((s32*)window)[4 / 4];
        if (menuId == activeWin) {
            menuSubCursorAnimeValGet(window, work);
        }
        s32 layer = winSpriteGetLayerID(window, work);
        windowDrawSpriteCursor(0, 0, -1, layer, 0, 0xC2, 0);
    }
    
    winSpriteSetDisp(work, 0);
    return 0;
}

/*
  Address: 0x80063874 | size: 0x214
  menuPocketColognDrawItemText(void* window, void* work)
  Draws item text for the cologne menu.
*/
s32 menuPocketColognDrawItemText(void* window, void* work) {
    s16 itemId = ((s16*)work)[6 / 2];
    void* data = ((void**)window)[0x68 / 4];
    
    if (itemId == 0x127) {
        // Draw item name
        s32 name = getItemName__FUl(0x200);
        s32 menuId = ((s32*)window)[4 / 4];
        void* menuItem = menuItemBiosGetPtr(menuId, 0x127);
        s16 x = ((s16*)menuItem)[0xA / 2];
        s32 rect = GSmsgGetRect(name);
        s16 width = rect >> 16;
        s32 layer = winSpriteGetLayerID(window, work);
        s32 xPos = (width - x + (width - x >> 31)) >> 1;
        GSmsgPrint2(layer, xPos, 0, -1, name);
        return 0;
    }
    
    // Check item ID against known cologne items
    s32 idx = -1;
    if (itemId == itemIds_2041[0]) idx = 0;
    else if (itemId == itemIds_2041[1]) idx = 1;
    else if (itemId == itemIds_2041[2]) idx = 2;
    else if (itemId == itemIds_2041[3]) idx = 3;
    else idx = 4;
    
    if (idx >= 0) {
        s32 maxIdx = ((s32*)data)[0x14 / 4];
        if (idx < maxIdx) {
            s16 itemIdx = ((s16*)data)[(idx * 4 + 4) / 2];
            if (itemIdx != 0) {
                s32 name = getItemName__FUl(itemIdx);
                s32 layer = winSpriteGetLayerID(window, work);
                GSmsgPrint2(layer, 0, 0, -1, name);
                
                // Draw stock count
                s32 menuId = ((s32*)window)[4 / 4];
                void* menuItem = menuItemBiosGetPtr(menuId, 0x130);
                s16 x = ((s16*)menuItem)[0xA / 2];
                s32 stock = getStockMax__FUs(itemIdx);
                msgctrlSetValue(0x34, stock);
                s32 rect1 = GSmsgGetRect(0x426F);
                s16 w1 = rect1 >> 16;
                s32 rect2 = GSmsgGetRect(0x428F);
                s16 w2 = rect2 >> 16;
                s32 xPos = (w1 + w2 - x + (w1 + w2 - x >> 31)) >> 1;
                GSmsgPrint2(layer, xPos, 0, -1, 0x428F);
                
                s32 num = getItemNum__FUs(itemIdx);
                msgctrlSetValue(0x34, num);
                s32 rect3 = GSmsgGetRect(0x426F);
                s16 w3 = rect3 >> 16;
                s32 xPos2 = (w3 - x + (w3 - x >> 31)) >> 1;
                GSmsgPrint2(layer, xPos2, 0, -1, 0x426F);
            }
        }
    }
    
    return 0;
}

/*
  Address: 0x80063A88 | size: 0xA4
  menuPocketColognCursor(void* window)
  Handles cursor movement for the cologne menu.
*/
s32 menuPocketColognCursor(void* window) {
    void* data = ((void**)window)[0x68 / 4];
    s32 keyRepeat = windowGetKeyRepeat();
    s32 maxLines = ((s32*)data)[0x14 / 4];
    s16 lineIdx = ((s16*)window)[0x9E / 2];
    
    // Handle D-pad up (bit 30)
    if (keyRepeat & (1 << 30)) {
        s16 newIdx = lineIdx + 1;
        if (newIdx >= maxLines) newIdx = maxLines - 1;
        ((s16*)window)[0x9E / 2] = newIdx;
    }
    // Handle D-pad down (bit 31)
    if (keyRepeat & (1 << 31)) {
        s16 newIdx = lineIdx - 1;
        if (newIdx < 0) newIdx = 0;
        ((s16*)window)[0x9E / 2] = newIdx;
    }
    
    if (lineIdx != ((s16*)window)[0x9E / 2]) {
        menuSubCursorAnimeStart();
    }
    
    return 0;
}

/*
  Address: 0x80063B2C | size: 0xDC
  menuPocketColognCtrl(void* work)
  Controls the cologne menu state machine.
*/
s32 menuPocketColognCtrl(void* work) {
    s8 state = ((s8*)work)[1];
    
    switch (state) {
        case 0:
            // Init state
            if (((s8*)work)[2] == 0) {
                winSeqSetMenu(0x32, 0x60);
                ActMenuCursorBlinkTime = float_0;
                ((s8*)work)[2] = 1;
                menuSubCursorAnimeInit();
            }
            break;
        case 2:
            // Update cursor blink time
            ActMenuCursorBlinkTime += float_0_0333;
            if (ActMenuCursorBlinkTime > float_1) {
                ActMenuCursorBlinkTime = float_0;
            }
            menuSubCursorAnimeMain();
            break;
        case 3:
            // Cleanup state
            if (((s8*)work)[2] == 0) {
                winSeqSetMenu(0x32, 0x64);
                ((s8*)work)[2] = 1;
            }
            break;
    }
    
    return 0;
}

/*
  Address: 0x80063C08 | size: 0x30
  makePocketCologneArg__FP18POCKET_COLOGNE_ARGUl(void* arg, u32 itemId)
  Makes the argument struct for the cologne menu.
*/
void makePocketCologneArg__FP18POCKET_COLOGNE_ARGUl(void* arg, u32 itemId) {
    ((s32*)arg)[0] = itemId;
    ((s16*)arg)[4 / 2] = 0x201;
    ((s16*)arg)[8 / 2] = 0x202;
    ((s16*)arg)[0xC / 2] = 0x203;
    ((s16*)arg)[0x10 / 2] = 0;
    ((s32*)arg)[0x14 / 4] = 4;
}

/*
  Address: 0x80063C38 | size: 0xE4
  menuPocketCologne(void* arg)
  Main entry point for the pocket cologne menu.
*/
s32 menuPocketCologne(void* arg) {
    if (init$1991 == 0) {
        first$1990 = 1;
        init$1991 = 1;
    }
    if (first$1990 != 0) {
        first$1990 = 0;
    }
    
    POCKET_COLOGNE_ARG localArg;
    makePocketCologneArg__FP18POCKET_COLOGNE_ARGUl(&localArg, (u32)arg);
    
    s32 activeWin = windowGetActiveID();
    s32 menuId = menuOpenCustom(0x32, activeWin, &localArg, 0, 1, 1);
    
    menuClose(0x32);
    menuCloseSync(0x32, 1);
    
    if (menuId >= 0 && menuId < ((s32*)&localArg)[0x1C / 4]) {
        s16 itemId = ((s16*)&localArg)[(menuId * 4 + 0xC) / 2];
        s32 num = getItemNum__FUs(itemId);
        if (num > 0) {
            return itemId;
        }
        return 0;
    }
    
    return 0;
}
