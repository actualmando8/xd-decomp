// Decompiled from: menuSaveLoad.cpp
// Address range: 0x80037A48..0x80038104 | size: 0x6BC

/* Forward declarations */
void*   __nw__FUl(s32 size);
void    fadeSet(s32 type, float speed);
s32     GSflagGet(s32 flag);
void    winSpriteSetDisp(void* winSprite, s32 disp);
s32     darkPokemonGetReliveNum(void);
s32     darkPokemonGetSnatchSuccessNum(void);
void    msgctrlSetValue(s32 ctrlId, s32 value);
void*   savedataGetStatus(s32 a, s32 b);
void    gamedatasaveSetStatus(s32 a, s32 b, s32 c);
s32     gamedatasaveGetStatus(s32 a, s32 b);
void    memcardTaskCall(s32 task, s32 a, s32 b);
void*   memcardMemAllocForSavedata(void);
s32     memcardMemFreeForSavedata(void* ptr);
void*   heroGetStatus(s32 a, s32 b, s32 c);
s32     floorGetNextFloorID(void);
void    winSeqSetMenu(void* winWork, s32 seq);
s32     menuOpen(s32 menuId, s32 param);
void    winMsgOpen(s32 menuId, s32 msgId, s32 a, s32 b);
s32     menuSubOpenYesNo(s32 menuId, s32 x, s32 y, s32 param);
void    winMsgClose(s32 menuId);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 sync);
void*   pokecoloGetPlayTimeValue(void);
void    pokecoloSetPlayTime(double time);
s32     pokecoloGetRomVersion(void);
s32     GSflagTest(s32 flag);
void*   memcpy(void* dest, const void* src, s32 size);
void    __dl__FPv(void* ptr);

/* Constants */
static const float FADE_SPEED = 0.5f;
static const double ONE_DOUBLE = 1.0;

/* Jump table for menuSaveLoadHook - dispatches based on sprite index offset */
// Indices 0x266-0x26E map to different handlers
static void (*const jump_table_2163[])(void) = {
    // 0x266 - Relive check
    (void*)0x80037C1C,
    // 0x267 - Display check  
    (void*)0x80037BAC,
    // 0x268 - Default
    (void*)0x80037C44,
    // 0x269 - Default
    (void*)0x80037C44,
    // 0x26A - Relive check
    (void*)0x80037C1C,
    // 0x26B - Display check 2
    (void*)0x80037BD8,
    // 0x26C - Default
    (void*)0x80037C44,
    // 0x26D - Default
    (void*)0x80037C44,
    // 0x26E - Relive check
    (void*)0x80037C1C,
    // 0x26F - Display check
    (void*)0x80037BAC,
};

/* Global state */
static void* _saveload;
static s32   _PrevPlayTime;
extern void* flag_etc;

/* Class: menuSaveload */
class menuSaveload {
public:
    s32 _pad0[4];
    void Ctrl(void* winWork);
    void Main(void);
    s32 ComfirmOverwriting(void);
    void SaveParameterSet(void);
    s32 IsReport(void);
    void _menuClose(s32 menuId);
};

/*
  Address: 0x80037A48 | size: 0xAC
  menuSaveLoadCtrl(void* winWork)
  Main control for save/load screen. Dispatches to menuSaveload::Ctrl or handles fade transitions.
*/
void menuSaveLoadCtrl(void* winWork) {
    if (_saveload != 0) {
        ((menuSaveload*)_saveload)->Ctrl(winWork);
        return;
    }
    
    s8 state = ((s8*)winWork)[1];
    
    if (state == 0) {
        if (((s8*)winWork)[2] == 0) {
            fadeSet(2, FADE_SPEED);
            ((s8*)winWork)[2] = 1;
        }
    } else if (state == 3) {
        if (((s8*)winWork)[2] == 0) {
            fadeSet(3, FADE_SPEED);
            ((s8*)winWork)[2] = 1;
        }
    }
}

/*
  Address: 0x80037AF4 | size: 0x58
  menuReport()
  Entry point for save report screen. Creates menuSaveload object, runs Main, destroys.
*/
void menuReport(void) {
    void* obj = __nw__FUl(4);
    if (obj != 0) {
        __ct__12menuSaveloadFv(obj);
    }
    _saveload = obj;
    ((menuSaveload*)obj)->Main();
    __dt__12menuSaveloadFv(_saveload, 1);
    _saveload = 0;
}

/*
  Address: 0x80037B4C | size: 0x110
  menuSaveLoadHook(void* winWork, void* spriteWork)
  Hook for save/load screen icons. Uses jump table based on sprite index.
  Checks flag 0x3C4 against floor data for display logic.
*/
void menuSaveLoadHook(void* winWork, void* spriteWork) {
    s32 flag = GSflagGet(0x3C4);
    void* flagData = flag_etc;
    s32 flagValue = ((u32*)flagData)[0x148 / 4];
    
    s32 enabled = (flag >= flagValue) ? 1 : 0;
    
    s16 spriteIdx = ((s16*)spriteWork)[3];
    s32 offset = spriteIdx - 0x266;
    
    if (offset > 9) {
        return;
    }
    
    // Jump table dispatch
    // (simplified - actual implementation uses indirect branch)
    
    if (offset == 0 || offset == 4 || offset == 8) {
        // Relive check
        s32 reliveNum = darkPokemonGetReliveNum();
        if (reliveNum == 0) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
        }
    } else if (offset == 1 || offset == 9) {
        // Display check
        if (enabled == 0) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
            if (_saveload != 0) {
                ((menuSaveload*)_saveload)->SaveParameterSet();
            } else {
                _SaveParameterSet__Fv();
            }
        }
    } else if (offset == 5) {
        // Display check 2
        if (enabled == 0) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
        }
    }
}

/*
  Address: 0x80037C5C | size: 0x44
  __dt__12menuSaveloadFv(void* this, s32 flags)
  Destructor for menuSaveload class.
*/
void __dt__12menuSaveloadFv(void* this, s32 flags) {
    if (this != 0 && flags > 0) {
        __dl__FPv(this);
    }
}

/*
  Address: 0x80037CA0 | size: 0xC
  __ct__12menuSaveloadFv(void* this)
  Constructor for menuSaveload class. Initializes member to 0.
*/
void __ct__12menuSaveloadFv(void* this) {
    ((u32*)this)[0] = 0;
}

/*
  Address: 0x80037CAC | size: 0xE8
  Main__12menuSaveloadFv(void* this)
  Main loop for save report. Shows report, confirms overwrite, saves.
*/
void Main__12menuSaveloadFv(void* this) {
    menuSaveload* self = (menuSaveload*)this;
    
    if (self->IsReport()) {
        menuOpen(0x64, 0);
        winMsgOpen(2, 0x3BF2, 1, 1);
        s32 result = menuSubOpenYesNo(0, 0x1C2, 0xC0, 0);
        
        if (result == 0) {
            s32 confirm = self->ComfirmOverwriting();
            if (confirm != 0) {
                s32 nextFloor = floorGetNextFloorID();
                gamedatasaveSetStatus(0, 5, nextFloor);
                memcardTaskCall(4, 2, 0);
            }
        }
        
        winMsgClose(1);
        self->_menuClose(0x64);
    } else {
        winMsgOpen(2, 0x3BE9, 1, 1);
        winMsgClose(1);
    }
}

/*
  Address: 0x80037D94 | size: 0x1A4
  ComfirmOverwriting__12menuSaveloadFv(void* this)
  Confirms save overwrite. Backs up save data, checks conditions, shows confirmation.
  Returns 1 if confirmed, 0 if cancelled.
*/
s32 ComfirmOverwriting__12menuSaveloadFv(void* this) {
    menuSaveload* self = (menuSaveload*)this;
    s32 confirmed = 1;
    
    void* backup = memcardMemAllocForSavedata();
    void* saveData = savedataGetStatus(0, 0);
    memcpy(backup, saveData, 0x7FD0);
    
    s32 result = memcardTaskCall(3, 2, 0);
    if (result != 3) {
        confirmed = 0;
    } else {
        s32 status = gamedatasaveGetStatus(0, 4);
        if (status == 0) {
            confirmed = 0;
        } else {
            // Check hero status
            void* hero1 = heroGetStatus(0, 2, 0);
            void* hero2 = heroGetStatus(0, 2, 0);
            if (hero1 != hero2) {
                s32 status2 = gamedatasaveGetStatus(0, 4);
                if (status2 != 0) {
                    confirmed = 0;
                }
            }
        }
    }
    
    // Store play time
    s32 playTime = pokecoloGetPlayTimeValue();
    ((s32*)self)[0] = playTime;
    self->SaveParameterSet();
    
    winMsgOpen(2, 0x3BF3, 1, 1);
    s32 yesNo = menuSubOpenYesNo(0, 0x1C2, 0xC0, 1);
    confirmed = (yesNo == 0) ? 1 : 0;
    
    // Calculate time difference
    s32 currentPlayTime = pokecoloGetPlayTimeValue();
    s32 diff = currentPlayTime - ((s32*)self)[0];
    ((s32*)self)[0] = diff;
    
    // Restore save data
    saveData = savedataGetStatus(0, 0);
    memcpy(saveData, backup, 0x7FD0);
    
    // Adjust play time
    currentPlayTime = pokecoloGetPlayTimeValue();
    double timeDiff = (double)((s32*)self)[0] + (double)currentPlayTime;
    ((s32*)self)[0] = 0;
    pokecoloSetPlayTime(timeDiff);
    
    memcardMemFreeForSavedata(backup);
    
    // Normalize to 0 or 1
    confirmed = (confirmed != 0) ? 1 : 0;
    return confirmed;
}

/*
  Address: 0x80037F38 | size: 0x5C
  _SaveParameterSet__Fv()
  Static version of SaveParameterSet. Sets message control values for save screen.
*/
void _SaveParameterSet__Fv(void) {
    s32 playTime = pokecoloGetPlayTimeValue();
    if (_PrevPlayTime != 0) {
        playTime = _PrevPlayTime;
    }
    msgctrlSetValue(0x4C, playTime);
    
    s32 snatchNum = darkPokemonGetSnatchSuccessNum();
    msgctrlSetValue(0x34, snatchNum);
    
    s32 reliveNum = darkPokemonGetReliveNum();
    msgctrlSetValue(0x35, reliveNum);
}

/*
  Address: 0x80037F94 | size: 0x68
  SaveParameterSet__12menuSaveloadFv(void* this)
  Instance version of SaveParameterSet. Uses object's stored play time if set.
*/
void SaveParameterSet__12menuSaveloadFv(void* this) {
    menuSaveload* self = (menuSaveload*)this;
    s32 playTime = pokecoloGetPlayTimeValue();
    if (((s32*)self)[0] != 0) {
        playTime = ((s32*)self)[0];
    }
    msgctrlSetValue(0x4C, playTime);
    
    s32 snatchNum = darkPokemonGetSnatchSuccessNum();
    msgctrlSetValue(0x34, snatchNum);
    
    s32 reliveNum = darkPokemonGetReliveNum();
    msgctrlSetValue(0x35, reliveNum);
}

/*
  Address: 0x80037FFC | size: 0x38
  IsReport__12menuSaveloadFv(void* this)
  Checks if save report should be shown.
  Returns 0 for ROM version 1 (demo), otherwise checks flag 0x3DE.
*/
s32 IsReport__12menuSaveloadFv(void* this) {
    s32 romVer = pokecoloGetRomVersion();
    if (romVer == 1) {
        return 0;
    }
    return GSflagTest(0x3DE);
}

/*
  Address: 0x80038034 | size: 0x94
  Ctrl__12menuSaveloadFP14tagWINDOW_WORK(void* this, void* winWork)
  Control handler for save/load screen. Sets menu sequence based on state.
*/
void Ctrl__12menuSaveloadFP14tagWINDOW_WORK(void* this, void* winWork) {
    s8 state = ((s8*)winWork)[1];
    
    if (state == 0) {
        if (((s8*)winWork)[2] == 0) {
            winSeqSetMenu(winWork, 0x17F);
            ((s8*)winWork)[2] = 1;
        }
    } else if (state == 3) {
        if (((s8*)winWork)[2] == 0) {
            winSeqSetMenu(winWork, 0x185);
            ((s8*)winWork)[2] = 1;
        }
    }
}

/*
  Address: 0x800380C8 | size: 0x3C
  _menuClose__12menuSaveloadFl(void* this, s32 menuId)
  Closes menu with synchronization.
*/
void _menuClose__12menuSaveloadFl(void* this, s32 menuId) {
    menuClose(menuId);
    menuCloseSync(menuId, 1);
}
