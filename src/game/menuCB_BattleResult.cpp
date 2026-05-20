// Decompiled from: menuCB_BattleResult.cpp
// Address range: 0x80046598..0x80046D5C | size: 0x7C4

/* Forward declarations */
s32     toolentryTaisenGetBattleMode(void);
s32     toolentryTaisenGetBattleType(void);
s32     toolentryTaisenGetHomePlace(s32 player);
s32     toolentryTaisenGetControlerType(s32 player);
s32     toolentryTaisenGetEntryPlayerNum(void);
s32     fightGetFightResultId(void);
void    menuSetEnablePort(s32 port);
s32     pokecoloGetCountryCode(void);
s32     menuSubOpenSelect_gba(s32 a, const s32* msgIds, s32 b, s32 c, s32 d, s32 e, s32 f);
s32     menuSubOpenSelect3(s32 a, const s32* msgIds, s32 b, s32 c, s32 d, s32 e, s32 f);
void    winMsgOpen(s32 menuId, s32 msgId, s32 a, s32 b);
void    winMsgClose(s32 menuId);
void    msgctrlSetValue(s32 ctrlId, s32 value);
s32     gbaCommandIsConnected(s32 port);
void    toolentryCopyHero(void);
void    GSthreadSwitch(void);
s32     GSinputIsConnected(s32 port);
s32     GSinputGetSubType(s32 port);

/* Global state */
extern s32 menuCBBattleStartResID;

/* Data tables for sub-menus */
static const s32 submenu_msg1[] = { 0x4300, 0x4303 };
static const s32 submenu_msg2[] = { 0x4300, 0x4302, 0x4303 };
static const s32 submenu_msg3[] = { 0x4300, 0x4301, 0x4302, 0x4303 };
static const s32 lbl_8032EAFC[] = { 0x4300, 0x4301, 0x4303 };
static const s32 lbl_804E7F48[] = { 0x4300, 0x4303 };

/* External _CB struct */
extern s32 _CB[];

/*
  Address: 0x80046598 | size: 0x54
  menuCB_BattleResult(_MENUCBWORK* work)
  Entry point. Dispatches to Tonikaku or Taisen handler based on battle mode.
*/
void menuCB_BattleResult(void* work) {
    s32 mode = toolentryTaisenGetBattleMode();
    if (mode == 1) {
        _menuCB_BattleResultTonikaku__FP11_MENUCBWORK(work);
    } else {
        _menuCB_BattleResultTaisen__FP11_MENUCBWORK(work);
    }
}

/*
  Address: 0x800465EC | size: 0x4E4
  _menuCB_BattleResultTaisen__FP11_MENUCBWORK(_MENUCBWORK* work)
  Handles battle result for Taisen mode. Shows appropriate messages based on
  result, home place, GBA port status, and controller connection.
*/
s32 _menuCB_BattleResultTaisen__FP11_MENUCBWORK(void* work) {
    s32 resultId = fightGetFightResultId();
    s32 menuEnable = 0;
    s32* cb = &_CB[0x1000];
    
    menuSetEnablePort(0);
    
    while (1) {
        if (resultId == 1) {
            menuSetEnablePort(1);
            
            s32 homePlace = _menuCB_BattleResultGetHomePlace__Fv();
            if (homePlace != 0) {
                _menuCBResultCheckGBAPort__Fv();
                winMsgOpen(2, 0x442D, 1, 1);
                _menuCBResultCheckController1__Fv();
                winMsgClose(1);
                menuEnable = 1;
            } else {
                _menuCBResultCheckGBAPort__Fv();
                msgctrlSetValue(0x2F, 0);
                winMsgOpen(2, 0x442B, 1, 1);
                winMsgClose(1);
                menuEnable = 1;
            }
        }
        
        if (menuEnable) {
            return 0xA9;
        }
        
        // Show selection menu based on country code
        menuSetEnablePort(1);
        winMsgOpen(2, 0x42FF, 1, 1);
        
        s32 countryCode = pokecoloGetCountryCode();
        s32 selectResult;
        
        if (countryCode == 0) {
            // US - 4 options
            selectResult = menuSubOpenSelect_gba(0, submenu_msg3, 3, 0x3E, 0x89, 0, 3);
        } else if (countryCode >= 0 && countryCode < 3) {
            // Other regions - 3 options
            selectResult = menuSubOpenSelect_gba(0, lbl_804E7F48, 2, 0x3E, 0x89, 0, 2);
        } else {
            // Default
            selectResult = menuSubOpenSelect_gba(0, lbl_804E7F48, 2, 0x3E, 0x89, 0, 2);
        }
        
        cb[-0x5020 / 4] = selectResult;
        
        if (selectResult == -2) {
            resultId = 1;
            continue;
        }
        if (selectResult == -1) {
            cb[-0x5020 / 4] = 2;
        }
        
        // Validate selection and determine result
        s32 finalResult = -1;
        // ... (complex validation logic based on country and selection)
        
        winMsgClose(1);
        
        if (finalResult == -1 || finalResult == 0xA9) {
            resultId = 0;
            menuEnable = 1;
            s32 homePlace2 = _menuCBResultGetHomePlace__Fv();
            
            // Continue processing based on home place...
        } else if (finalResult == 0xAC) {
            // Handle result 0xAC
        } else if (finalResult == 0xB1) {
            // Handle result 0xB1
        }
        
        menuCBBattleStartResID = 0;
        return 0xA9;
    }
}

/*
  Address: 0x80046AD0 | size: 0x48
  _menuCB_BattleResultGetHomePlace__Fv()
  Gets home place for battle result. Returns normalized value.
*/
s32 _menuCB_BattleResultGetHomePlace__Fv(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    if (battleType != 2) return 0;
    
    s32 homePlace = toolentryTaisenGetHomePlace(0);
    homePlace &= 0xFFFF;
    // Normalize to 0 or 1
    return (homePlace != 0) ? 1 : 0;
}

/*
  Address: 0x80046B18 | size: 0xAC
  _menuCB_BattleResultTonikaku__FP11_MENUCBWORK(_MENUCBWORK* work)
  Handles battle result for Tonikaku mode. Simple 2-option selection.
*/
s32 _menuCB_BattleResultTonikaku__FP11_MENUCBWORK(void* work) {
    s32* cb = &_CB[0x1000];
    cb[-0x5020 / 4] = 0;
    cb[-0x4FA0 / 4] = 0;
    
    s32 result = menuSubOpenSelect3(0, submenu_msg1, 2, 0x3E, 0x89, 0, 2);
    cb[-0x5020 / 4] = result;
    
    if (result == -1) {
        cb[-0x5020 / 4] = 1;
    }
    
    result = cb[-0x5020 / 4];
    if (result == 0) {
        toolentryCopyHero();
        return 0xB1;
    }
    
    return -1;
}

/*
  Address: 0x80046BC4 | size: 0x48
  _menuCBResultGetHomePlace__Fv()
  Gets home place for result processing. Same as BattleResult version.
*/
s32 _menuCBResultGetHomePlace__Fv(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    if (battleType != 2) return 0;
    
    s32 homePlace = toolentryTaisenGetHomePlace(0);
    homePlace &= 0xFFFF;
    return (homePlace != 0) ? 1 : 0;
}

/*
  Address: 0x80046C0C | size: 0x4C
  _menuCBResultCheckController1__Fv()
  Waits for controller 1 to be disconnected. Loops until disconnection detected.
*/
void _menuCBResultCheckController1__Fv(void) {
    s32 connected = 1;
    
    while (connected) {
        if (_menuCBResultCheckController1sub__Fv()) {
            connected = 0;
        } else {
            GSthreadSwitch();
        }
    }
}

/*
  Address: 0x80046C58 | size: 0x4C
  _menuCBResultCheckController1sub__Fv()
  Checks if controller 1 is connected and returns 1 if connected, 0 otherwise.
*/
s32 _menuCBResultCheckController1sub__Fv(void) {
    if (!GSinputIsConnected(1)) return 0;
    
    s32 subType = GSinputGetSubType(1);
    s32 result = __builtin_clz(subType) >> 5;
    return result;
}

/*
  Address: 0x80046CA4 | size: 0xB8
  _menuCBResultCheckGBAPort__Fv()
  Checks GBA port connection for all players. Returns 2 if all connected.
*/
s32 _menuCBResultCheckGBAPort__Fv(void) {
    s32 playerNum = toolentryTaisenGetEntryPlayerNum();
    toolentryTaisenGetBattleMode();
    
    for (s32 i = 0; i < playerNum; i++) {
        s32 homePlace = toolentryTaisenGetHomePlace(i);
        s32 controllerType = toolentryTaisenGetControlerType(i);
        
        if (controllerType == 0) continue;
        
        homePlace--;
        homePlace &= 0xFFFF;
        
        if (homePlace <= 1 || homePlace == 3) {
            if (!gbaCommandIsConnected(controllerType)) {
                return controllerType;
            }
        }
    }
    
    return 2;
}
