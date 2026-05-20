// Decompiled from: dbgMenuFlag.cpp
// Address range: 0x8000804C..0x80008998 | size: 0x94C

/*
  Debug menu for flag manipulation.
  Allows viewing and toggling game flags.
*/

/* Global data */
static s32 _dbgMenuFlagCursor;
static char buff$1425[0x80];

/* External data */
extern u16 flag_data[];
extern u32 flag_data_number;
extern u8 flag_etc[];
extern u32 flag_etc_number;

/* Forward declarations */
static s32 _dbgMenuFlagGetID(s32 index);
static char* _dbgMenuFlagInfoGetMsg(s32 index);
static s32 _dbgMenuFlagGetMenuNum(void* param, s32 menuNum);

/*
  Address: 0x8000804C | size: 0x158
  dbgMenuFlagInfoDraw(void* param)
  Draws the flag info display window showing all flags.
*/
void dbgMenuFlagInfoDraw(void* param) {
    u32 dispMax = menuDataBiosGetDispMax(*(u32*)((u8*)param + 4), 0x28);
    u32 totalCount = *flag_data_number;
    u32 count = *(u32*)flag_data;
    if (count > dispMax) count = dispMax;
    
    u32 height = count * 0xD;
    menuSubDrawSimpleWindow(*(u32*)((u8*)param + 0x1C), 0x1E, 0x28, height, 0x7D);
    
    // Draw cursor triangle
    if (_dbgMenuFlagCursor > 0) {
        menuSubDrawTriangle(*(u32*)((u8*)param + 0x1C), 0x46, 0x21, 0x5A, 0x21, 0x50, 0x17);
    }
    
    // Draw down arrow if scrollable
    s32 diff = (s32)count - (s32)_dbgMenuFlagCursor;
    if (diff > (s32)dispMax) {
        menuSubDrawTriangle(*(u32*)((u8*)param + 0x1C), 0x46, height + 0x2F, 0x5A, height + 0x39, 0x50, 0x17);
    }
    
    // Draw flag entries
    u16* flagData = flag_data;
    for (u32 i = 0; i < count; i++) {
        s16 flagId = *(s16*)(flagData + i * 2 + 1);
        u16 color = (flagId == (u16)i) ? 0xFF00FF : -1;
        
        char* msg = _dbgMenuFlagInfoGetMsg(i + _dbgMenuFlagCursor);
        GSprint(*(u32*)((u8*)param + 0x1C), 0x1E, 0x28 + i * 0xD, color, msg, 0);
        
        s32 flagValue = GSflagGet(i + _dbgMenuFlagCursor);
        GSprint(*(u32*)((u8*)param + 0x1C), 0x82, 0x28 + i * 0xD, color, "%d", flagValue);
    }
}

/*
  Address: 0x800081A4 | size: 0x1E4
  dbgMenuFlagInfoCursor(void* param)
  Handles cursor movement and flag toggling in the flag info display.
*/
void dbgMenuFlagInfoCursor(void* param) {
    void* keyInfo = windowGetKeyInfo();
    u16 keys = *(u16*)((u8*)keyInfo + 6);
    
    u32 dispMax = menuDataBiosGetDispMax(*(u32*)((u8*)param + 4), 0x28);
    u32 totalCount = *flag_data_number;
    s32 count = *(s32*)flag_data;
    if ((s32)count > (s32)dispMax) dispMax = count;
    
    s16 cursor = _dbgMenuFlagCursor;
    s16 offset = 0;
    
    // Handle key input
    if (keys & 0x8000) {  // Y key
        offset--;
    } else if (keys & 0x4000) {  // X key
        offset++;
    } else if (keys & 0x2000) {  // A key - page up
        offset -= dispMax - 1;
    } else if (keys & 0x1000) {  // B key - page down
        offset += dispMax - 1;
    }
    
    // Clamp cursor position
    cursor += offset;
    if (cursor < 0) {
        cursor += offset;
        if (cursor < 0) {
            cursor = (s16)(count - dispMax);
            if (cursor < 0) cursor = 0;
        }
    } else if (cursor >= (s16)dispMax) {
        cursor -= dispMax - 1;
        if (cursor >= (s16)count) {
            cursor = 0;
        }
    }
    
    // Toggle flag with A/B button
    if (keys & 0x0100) {  // A button
        GSflagOn(cursor + _dbgMenuFlagCursor);
    } else if (keys & 0x0200) {  // B button
        GSflagOff(cursor + _dbgMenuFlagCursor);
    }
    
    _dbgMenuFlagCursor = cursor;
    *(u32*)((u8*)param + 0x88) = cursor + _dbgMenuFlagCursor;
}

/*
  Address: 0x80008388 | size: 0x4C
  _dbgMenuFlagInfoGetMsg(index)
  Gets the message string for a flag index.
*/
static char* _dbgMenuFlagInfoGetMsg(s32 index) {
    s32 flagId = _dbgMenuFlagGetID(index);
    sprintf(buff$1425, "[%4d]", flagId);
    return buff$1425;
}

/*
  Address: 0x800083D4 | size: 0x11C
  _dbgMenuFlagGetID(index)
  Gets the flag ID at the given index, traversing the flag tree.
*/
static s32 _dbgMenuFlagGetID(s32 index) {
    if (index < 0) return 0;
    
    u32 count = *(u32*)flag_data;
    if (index >= (s32)count) return 0;
    
    s16 currentId = flag_data[index * 2 + 1];
    if (index == 0) return currentId;
    
    // Traverse flag tree
    s32 depth = (index - 1) / 8;
    s32 offset = (index - 1) % 8;
    
    for (s32 i = 0; i < depth; i++) {
        u16* flagEntry = (u16*)(flag_data + currentId * 6);
        currentId = flagEntry[2];  // Get child flag ID
    }
    
    u16* flagEntry = (u16*)(flag_data + currentId * 6);
    return flagEntry[2];
}

/*
  Address: 0x800084F0 | size: 0x1A0
  dbgMenuFlagCursor(void* param)
  Handles cursor movement in the main flag menu.
*/
void dbgMenuFlagCursor(void* param) {
    void* keyInfo = windowGetKeyInfo();
    u16 keys = *(u16*)((u8*)keyInfo + 6);
    
    s32 menuNum = _dbgMenuFlagGetMenuNum(param, 0);
    u32 dispMax = menuDataBiosGetDispMax(*(u32*)((u8*)param + 4), 0);
    if (menuNum > (s32)dispMax) dispMax = menuNum;
    
    s16 cursor = *(s16*)((u8*)param + 0x9C);
    s16 offset = 0;
    
    // Handle key input
    if (keys & 0x8000) {  // Y key
        offset--;
    } else if (keys & 0x4000) {  // X key
        offset++;
    } else if (keys & 0x2000) {  // A key - page up
        offset -= dispMax - 1;
    } else if (keys & 0x1000) {  // B key - page down
        offset += dispMax - 1;
    }
    
    // Clamp cursor position
    cursor += offset;
    if (cursor < 0) {
        cursor += offset;
        if (cursor < 0) {
            cursor = (s16)(dispMax - menuNum);
            if (cursor < 0) cursor = 0;
        }
    } else if (cursor >= (s16)dispMax) {
        cursor -= dispMax - 1;
        if (cursor >= (s16)menuNum) {
            cursor = 0;
        }
    }
    
    *(s16*)((u8*)param + 0x9C) = cursor;
    *(u32*)((u8*)param + 0x88) = cursor + *(s16*)((u8*)param + 0x9C);
}

/*
  Address: 0x80008690 | size: 0x134
  dbgMenuFlagCheck()
  Checks and sets flags. Opens number input menu for flag manipulation.
*/
s32 dbgMenuFlagCheck(void) {
    if (GSfloorIsFloorPushed()) {
        GSsndPlayNow(0x13);
        // Display loading message
        for (u32 i = 0; i < 0xF; i++) {
            dbgMenuGetLayerID();
            GSprint(0, 0xC8, 0xF0, -1, "Loading...", 0);
            GSthreadSwitch();
        }
        return -1;
    }
    
    if (GSinputButtonsPressed(1) & 0x40000) {  // Start button
        s32 result;
        while ((result = menuOpen(0x27, 1)) > 0) {
            s32 flagId = GSflagGet(result);
            s32 newValue = menuSubOpenNumberInputDigit(&newValue);
            if (newValue == 0) continue;
            GSflagSet(result, newValue);
        }
        if (result == -1) {
            menuClose(0x27);
            return -1;
        }
    }
    
    // Open etc menu
    s32 etcResult = menuOpen(0xB, 1);
    menuClose(0xB);
    if (etcResult > 0) {
        dbgMenuFlagSetEtc(etcResult);
    } else if (etcResult == -1) {
        return -1;
    }
    
    return 0;
}

/*
  Address: 0x800087C4 | size: 0x11C
  dbgMenuFlagSetEtc(menuSelection)
  Sets various game flags based on menu selection.
  Handles follower Pokemon, Pokedoll, and floor position.
*/
void dbgMenuFlagSetEtc(s32 menuSelection) {
    u8* etcData = flag_etc + menuSelection * 0x20;
    
    // Set flag
    GSflagSet(0x3C4, *(u32*)(etcData + 8));
    GSflagSet(0x3DE, 1);
    
    // Handle follower Pokemon
    s8 followerType = etcData[menuSelection * 5];
    switch (followerType) {
        case 0: heroSetFollowerWithID(0, 0); break;
        case 1: heroSetFollowerWithID(1, 0); break;
        case 2: heroSetFollowerWithID(2, 0); break;
        case 3: heroSetFollowerWithID(3, 0); break;
    }
    
    // Set Pokedoll
    savedataGetStatus(0, 2);
    u16 pokedoll = *(u16*)(etcData + 4);
    heroBiosSetPokedoru(pokedoll);
    
    // Call script if specified
    u32 scriptId = *(u32*)(etcData + 0xC);
    if (scriptId != 0) {
        appScriptCommonCall(scriptId);
    }
    
    // Change floor position
    s16 floorId = *(s16*)(etcData + 2);
    if (floorId == 0) {
        floorId = GSfloorGetCurrent();
    }
    float x = *(float*)(etcData + 0x10);
    float y = *(float*)(etcData + 0x14);
    float z = *(float*)(etcData + 0x18);
    floorChangePos(floorId, 0, x, y, z);
}

/*
  Address: 0x800088E0 | size: 0xB8
  _dbgMenuFlagGetMenuNum(param, menuNum)
  Gets the number of menu entries for the flag menu.
*/
static s32 _dbgMenuFlagGetMenuNum(void* param, s32 menuNum) {
    if (menuNum != 0) {
        *(u32*)menuNum = 0;
    }
    
    s32 count = 0;
    for (u32 i = 0; i < *flag_etc_number; i++) {
        u32* etcEntry = (u32*)(flag_etc + i * 0x20 + 0x1C);
        if (*etcEntry == 0) continue;
        
        if (menuNum != 0) {
            count++;
            u32 msgRect = GSmsgGetRect(*etcEntry);
            u32 width = msgRect >> 16;
            u32 currentWidth = *(u32*)menuNum;
            if (width > currentWidth) {
                *(u32*)menuNum = width;
            }
        }
    }
    
    return count;
}
