// Decompiled from: menuCB_Common.cpp
// Address range: 0x80049DA4..0x8004A090 | size: 0x2EC

/* Forward declarations */
s32     winMsgCheck(void);
void    winMsgClose(s32 a);
void    winMsgOpen(s32 a, s32 b, s32 c, s32 d);
s32     menuCBTrainerBios_GetHomePlace(void* trainer);
s32     gbaCommandIsConnected(s32 portId);
void*   menuSpriteBiosGetValPtr(s32 spriteId);
s32     menuCB_CurrentMenuID(void);
void    menuCloseCustom(s32 a, s32 b, s32 c);
s32     windowGetActiveID(void);

/* BSS data */
static s32 _CBC[0x44 / 4];

/*
  Address: 0x80049DA4 | size: 0x20
  menuCB_MessageDispCheck(void)
  Wrapper for winMsgCheck.
*/
s32 menuCB_MessageDispCheck(void) {
    return winMsgCheck();
}

/*
  Address: 0x80049DC4 | size: 0x24
  menuCB_MessageDispOff(void)
  Closes message window.
*/
void menuCB_MessageDispOff(void) {
    winMsgClose(0);
}

/*
  Address: 0x80049DE8 | size: 0x30
  menuCB_MessageDispOn(s32 a, s32 b)
  Opens message window with flags.
*/
void menuCB_MessageDispOn(s32 a, s32 b) {
    winMsgOpen(7, a, b, 0);
}

/*
  Address: 0x80049E18 | size: 0x8C
  menuCB_GetDisconnectedGBA(void)
  Iterates through 4 trainer slots and finds the first disconnected GBA.
  Returns the port ID of the disconnected GBA, or 0 if none found.
*/
s32 menuCB_GetDisconnectedGBA(void) {
    s32* cb = &_CB[0];
    s32 result = 0;
    
    for (s32 i = 0; i < 4; i++) {
        s32 portId = cb[0x4CBC / 4 + i];
        if (portId == 0) {
            cb += 0x1320 / 4;
            continue;
        }
        
        s32 homePlace = menuCBTrainerBios_GetHomePlace((s32*)cb + 0x4C98 / 4);
        if (homePlace == 0) {
            cb += 0x1320 / 4;
            continue;
        }
        
        s32 connected = gbaCommandIsConnected(portId);
        if (connected == 0) {
            result = portId;
            break;
        }
        
        cb += 0x1320 / 4;
    }
    
    return result;
}

/*
  Address: 0x80049EA4 | size: 0x58
  menuCB_SetSprite(void* work, s32 spriteId)
  Copies sprite values from sprite bios to work struct.
*/
void menuCB_SetSprite(void* work, s32 spriteId) {
    void* spritePtr = menuSpriteBiosGetValPtr(spriteId);
    
    ((s16*)work)[0x54 / 2] = ((s16*)spritePtr)[4 / 2];
    ((s16*)work)[0x56 / 2] = ((s16*)spritePtr)[6 / 2];
    ((s32*)work)[0x58 / 4] = ((s32*)spritePtr)[8 / 4];
    ((s16*)work)[0x5C / 2] = ((s16*)spritePtr)[0 / 2];
    ((s16*)work)[0x5E / 2] = ((s16*)spritePtr)[2 / 2];
}

/*
  Address: 0x80049EFC | size: 0x64
  menuCB_MenuRollback(s32 targetMenuId)
  Pops menus until the current menu ID matches the target.
*/
s32 menuCB_MenuRollback(s32 targetMenuId) {
    while (1) {
        s32 currentId = menuCB_CurrentMenuID();
        if (currentId == targetMenuId) {
            break;
        }
        menuCB_MenuPop();
        
        // Decrement counter at _CBC + 0x40
        if (_CBC[0x40 / 4] != 0) {
            _CBC[0x40 / 4]--;
        }
    }
    
    return menuCB_CurrentMenuID();
}

/*
  Address: 0x80049F60 | size: 0x84
  menuCB_MenuPop(void)
  Pops the current menu from the stack.
*/
s32 menuCB_MenuPop(void) {
    s32 currentId = menuCB_CurrentMenuID();
    s32 activeWindow = windowGetActiveID();
    
    if (activeWindow == currentId) {
        menuCloseCustom(currentId, 0, 0);
    }
    
    s32 counter = _CBC[0x40 / 4];
    if (counter == 0) {
        return -1;
    }
    
    _CBC[0x40 / 4] = counter - 1;
    
    return menuCB_CurrentMenuID();
}

/*
  Address: 0x80049FE4 | size: 0x3C
  menuCB_MenuPush(s32 menuId)
  Pushes a new menu onto the stack.
*/
s32 menuCB_MenuPush(s32 menuId) {
    s32 counter = _CBC[0x40 / 4];
    if (counter >= 8) {
        return 0; // Stack overflow
    }
    
    _CBC[0x40 / 4] = counter + 1;
    _CBC[counter] = menuId;
    _CBC[counter + 1] = 0; // Clear next slot
    
    return _CBC[counter];
}

/*
  Address: 0x8004A020 | size: 0x18
  menuCB_CurrentMenuID(void)
  Returns the current menu ID from the stack.
*/
s32 menuCB_CurrentMenuID(void) {
    s32 counter = _CBC[0x40 / 4];
    return _CBC[counter];
}

/*
  Address: 0x8004A038 | size: 0x58
  menuCB_InitMenu(void)
  Initializes the menu stack.
*/
void menuCB_InitMenu(void) {
    for (s32 i = 0; i < 0x44 / 4; i++) {
        _CBC[i] = 0;
    }
    _CBC[0] = 3; // Initial menu ID
}
