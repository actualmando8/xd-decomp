// Decompiled from: menuSaveLoad.cpp
// Address range: 0x80037A48..0x80038104 | size: 0x6BC

#include "global.h"

/* Forward declarations */
void    menuOpen(s32 layers, s32 unused);
void    menuClose(s32 layers);
void    menuCloseSync(s32 layers, s32 sync);
void    winMsgOpen(s32 type, s32 msgId, s32 a, s32 b);
void    winMsgClose(s32 type);
s32     menuSubOpenYesNo(s32 x, s32 y, s32 z, s32 w);
void    winSeqSetMenu(s32 work, s32 seqId);
void    fadeSet(s32 type, float value);
s32     GSflagGet(s32 flag);
s32     GSflagTest(s32 flag);
void*   memcardMemAllocForSavedata(s32 type);
void    memcardMemFreeForSavedata(void* ptr);
void    savedataGetStatus(s32 a, s32 b);
void    gamedatasaveGetStatus(s32 a, s32 b);
void    gamedatasaveSetStatus(s32 a, s32 b, s32 c);
void    heroGetStatus(s32 a, s32 b, s32 c);
void    memcardTaskCall(s32 a, s32 b, s32 c);
void    msgctrlSetValue(s32 id, s32 value);
s32     darkPokemonGetReliveNum(void);
s32     darkPokemonGetSnatchSuccessNum(void);
s32     pokecoloGetPlayTimeValue(void);
void    pokecoloSetPlayTime(s32 value);
s32     pokecoloGetRomVersion(void);
void*   __nw__FUl(s32 size);
void    __dl__FPv(void* ptr);
void    __ct__12menuSaveloadFv(void* this);
void    __dt__12menuSaveloadFv(void* this, s32 mode);
void    Main__12menuSaveloadFv(void* this);
s32     IsReport__12menuSaveloadFv(void* this);
void    ComfirmOverwriting__12menuSaveloadFv(void* this);
void    SaveParameterSet__12menuSaveloadFv(void* this);
void    _SaveParameterSet__Fv(void);
void    Ctrl__12menuSaveloadFP14tagWINDOW_WORK(void* this, void* work);
void    _menuClose__12menuSaveloadFl(s32 layers);
s32     floorGetNextFloorID(void);

/* Global variables */
static void* _saveload;          // 0x804EA7C8
static s32    _PrevPlayTime;     // 0x804EA7CC

/* Constants */
static const float FADE_VALUE = 0.5f;  // @2131
static const double PLAY_TIME_SCALE = 1.0; // @2192

/* Jump table for menuSaveLoadHook */
// @2163 - Function pointers for different menu items
static void (*const menuSaveLoadHookTable[10])(void) = {
    (void(*)(void))0x80037C1C,  // 0x56
    (void(*)(void))0x80037BAC,
    (void(*)(void))0x80037C44,
    (void(*)(void))0x80037C44,
    (void(*)(void))0x80037C1C,
    (void(*)(void))0x80037BD8,
    (void(*)(void))0x80037C44,
    (void(*)(void))0x80037C44,
    (void(*)(void))0x80037C1C,
    (void(*)(void))0x80037BAC,
};

/*
  Address: 0x80037A48 | size: 0xAC
  menuSaveLoadCtrl(tagWINDOW_WORK* work)
  Main control function for save/load menu.
*/
void menuSaveLoadCtrl(void* work) {
    if (_saveload != NULL) {
        Ctrl__12menuSaveloadFP14tagWINDOW_WORK(_saveload, work);
        return;
    }

    s8 state = ((u8*)work)[1];
    if (state == 3) {
        // Closing state
        if (((u8*)work)[2] == 0) {
            fadeSet(3, FADE_VALUE);
            ((u8*)work)[2] = 1;
        }
    } else if (state == 0) {
        // Opening state
        if (((u8*)work)[2] == 0) {
            fadeSet(2, FADE_VALUE);
            ((u8*)work)[2] = 1;
        }
    }
}

/*
  Address: 0x80037AF4 | size: 0x58
  menuReport()
  Entry point for save report menu.
  Allocates menuSaveload object, runs Main(), then destroys.
*/
void menuReport(void) {
    void* obj = __nw__FUl(4);
    if (obj != NULL) {
        __ct__12menuSaveloadFv(obj);
    }
    _saveload = obj;
    Main__12menuSaveloadFv(obj);
    __dt__12menuSaveloadFv(_saveload, 1);
    _saveload = NULL;
}

/*
  Address: 0x80037B4C | size: 0x110
  menuSaveLoadHook(tagWINDOW_WORK* work, void* item)
  Hook function called for each menu item.
  Uses jump table based on item index.
*/
void menuSaveLoadHook(void* work, void* item) {
    // Check if flag 0x3C4 is set and play time >= threshold
    s32 flag = GSflagGet(0x3C4);
    s32 playTime = ((u32*)flag)[0x148 / 4];
    s32 enabled = (playTime >= 0) ? 1 : 0;

    s16 itemIdx = ((s16*)item)[3];
    s32 offset = itemIdx - 0x56;
    if (offset < 0 || offset > 9) {
        return;
    }

    // Jump table dispatch
    // ... (handled by compiler-generated switch)
    s32 result = 0;

    switch (offset) {
        case 0: // 0x56
            result = 0;
            break;
        case 1:
            if (enabled) {
                winSpriteSetDisp(item, 1);
            } else {
                winSpriteSetDisp(item, 0);
            }
            if (_saveload != NULL) {
                SaveParameterSet__12menuSaveloadFv(_saveload);
            } else {
                _SaveParameterSet__Fv();
            }
            break;
        case 2:
            if (darkPokemonGetReliveNum() > 0) {
                winSpriteSetDisp(item, 1);
            } else {
                winSpriteSetDisp(item, 0);
            }
            break;
        // ... other cases
    }
}

/*
  Address: 0x80037C5C | size: 0x44
  menuSaveload::~menuSaveload()
  Destructor for menuSaveload class.
*/
void __dt__12menuSaveloadFv(void* this, s16 mode) {
    if (this != NULL && mode > 0) {
        __dl__FPv(this);
    }
}

/*
  Address: 0x80037CA0 | size: 0xC
  menuSaveload::menuSaveload()
  Constructor - initializes play time field to 0.
*/
void __ct__12menuSaveloadFv(void* this) {
    ((s32*)this)[0] = 0;
}

/*
  Address: 0x80037CAC | size: 0xE8
  menuSaveload::Main()
  Main logic for save report menu.
  Shows yes/no dialog for saving, handles overwrite confirmation.
*/
void Main__12menuSaveloadFv(void* this) {
    if (IsReport__12menuSaveloadFv(this)) {
        menuOpen(0x64, 0);
        winMsgOpen(2, 0x3BF2, 1, 1);
        s32 result = menuSubOpenYesNo(0, 0x1C2, 0xC0, 0);

        if (result == 0) {
            // User selected Yes
            if (ComfirmOverwriting__12menuSaveloadFv(this)) {
                s32 floorId = floorGetNextFloorID();
                gamedatasaveSetStatus(0, 5, floorId);
                memcardTaskCall(4, 2, 0);
            }
        }

        winMsgClose(1);
        _menuClose__12menuSaveloadFl(0x64);
    } else {
        winMsgOpen(2, 0x3BE9, 1, 1);
        winMsgClose(1);
    }
}

/*
  Address: 0x80037D94 | size: 0x1A4
  menuSaveload::ComfirmOverwriting()
  Confirms save overwrite with user.
  Reads savedata, compares hero status, shows confirmation dialog.
  Returns 1 if user confirmed overwrite.
*/
s32 ComfirmOverwriting__12menuSaveloadFv(void* this) {
    s32 result = 1;
    void* saveBuf = memcardMemAllocForSavedata(1);

    savedataGetStatus(0, 0);
    memcpy(saveBuf, /* savedata ptr */, 0x27FD0);
    memcardTaskCall(3, 2, 0);

    if (/* task result */ == 3) {
        if (gamedatasaveGetStatus(0, 4) != NULL) {
            savedataGetStatus(saveBuf, 2);
            void* hero1 = heroGetStatus(saveBuf, 2, 0);
            void* hero2 = heroGetStatus(/* current */, 2, 0);

            if (hero1 != hero2) {
                if (gamedatasaveGetStatus(saveBuf, 4) == NULL) {
                    pokecoloGetPlayTimeValue();
                    ((s32*)this)[0] = /* play time */;
                    SaveParameterSet__12menuSaveloadFv(this);

                    winMsgOpen(2, 0x3BF3, 1, 1);
                    s32 confirm = menuSubOpenYesNo(0, 0x1C2, 0xC0, 1);

                    if (confirm != 0) {
                        result = 0;
                    } else {
                        result = 1;
                    }

                    // Calculate play time delta
                    s32 currentPlayTime = pokecoloGetPlayTimeValue();
                    s32 delta = currentPlayTime - ((s32*)this)[0];
                    ((s32*)this)[0] = delta;
                }
            }
        }
    }

    // Restore savedata
    savedataGetStatus(0, 0);
    memcpy(/* savedata ptr */, saveBuf, 0x27FD0);

    // Update play time
    s32 playTime = pokecoloGetPlayTimeValue();
    s32 delta = ((s32*)this)[0];
    double scaled = (double)(playTime + delta) - PLAY_TIME_SCALE;
    pokecoloSetPlayTime((s32)scaled);

    ((s32*)this)[0] = 0;
    memcardMemFreeForSavedata(saveBuf);

    return result;
}

/*
  Address: 0x80037F38 | size: 0x5C
  _SaveParameterSet()
  Static version that sets message parameters from global state.
*/
void _SaveParameterSet__Fv(void) {
    s32 playTime = pokecoloGetPlayTimeValue();
    if (_PrevPlayTime != 0) {
        playTime = _PrevPlayTime;
    }
    msgctrlSetValue(0x4C, playTime);
    msgctrlSetValue(0x34, darkPokemonGetSnatchSuccessNum());
    msgctrlSetValue(0x35, darkPokemonGetReliveNum());
}

/*
  Address: 0x80037F94 | size: 0x68
  menuSaveload::SaveParameterSet()
  Instance version that sets message parameters.
*/
void SaveParameterSet__12menuSaveloadFv(void* this) {
    s32 playTime = pokecoloGetPlayTimeValue();
    if (((s32*)this)[0] != 0) {
        playTime = ((s32*)this)[0];
    }
    msgctrlSetValue(0x4C, playTime);
    msgctrlSetValue(0x34, darkPokemonGetSnatchSuccessNum());
    msgctrlSetValue(0x35, darkPokemonGetReliveNum());
}

/*
  Address: 0x80037FFC | size: 0x38
  menuSaveload::IsReport()
  Checks if save report should be shown.
  Returns 0 if ROM version == 1, otherwise checks flag 0x3DE.
*/
s32 IsReport__12menuSaveloadFv(void* this) {
    if (pokecoloGetRomVersion() == 1) {
        return 0;
    }
    return GSflagTest(0x3DE);
}

/*
  Address: 0x80038034 | size: 0x94
  menuSaveload::Ctrl(tagWINDOW_WORK* work)
  Controls menu sequence based on work state.
*/
void Ctrl__12menuSaveloadFP14tagWINDOW_WORK(void* this, void* work) {
    s8 state = ((u8*)work)[1];
    if (state == 3) {
        // Closing
        if (((u8*)work)[2] == 0) {
            winSeqSetMenu(((u32*)work)[1], 0x185);
            ((u8*)work)[2] = 1;
        }
    } else if (state == 0) {
        // Opening
        if (((u8*)work)[2] == 0) {
            winSeqSetMenu(((u32*)work)[1], 0x17F);
            ((u8*)work)[2] = 1;
        }
    }
}

/*
  Address: 0x800380C8 | size: 0x3C
  menuSaveload::_menuClose(long layers)
  Closes menu with synchronization.
*/
void _menuClose__12menuSaveloadFl(s32 layers) {
    menuClose(layers);
    menuCloseSync(layers, 1);
}

/* Helper function declarations */
void winSpriteSetDisp(void* sprite, s32 disp);
void* memcpy(void* dst, const void* src, s32 size);
