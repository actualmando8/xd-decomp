// Decompiled from: menuTitleOption.cpp
// Address range: 0x800A6D54..0x800A7614 | size: 0x8C0

#include "global.h"

/* Forward declarations */
void    menuTitleCursorAnimeMain(void* work);
void    menuCursorNormal(void* work, s32 mode);
s32     windowGetKeyInfo(s32 work);
s32     windowGetKeyRepeat(s32 work);
void    menuPlaySe(s32 work, s32 seId);
s32     GSsndGetOutputMode(void);
void    GSsndSetOutputMode(s32 mode, s32 value);
void    GSinputMotorStart(s32 a, s32 b, s32 c, s32 d, s32 e);
void    gamedatasaveGetStatus(s32 a, s32 b);
void    gamedatasaveSetStatus(s32 a, s32 b, s32 c);
void    winSeqSetMenu(s32 work, s32 seqId);
void    fadeSet(s32 type, float value);
void    menuPdaSubCalcAlpha(float* alphas, s32 count, s32 mode);
void    menuPdaSubInitAlpha(float* alphas, s32 count, s32 startIdx);
void    menuOpen(s32 layers, s32 unused);
void    menuCloseCustom(s32 layers, s32 a, s32 b);
s32     windowSearchID(s32 id, s32 work);
void    menuButtonNormal(void* work);
void    winMsgOpen(s32 type, s32 msgId, s32 a, s32 b);
void    winMsgClose(s32 type);
s32     menuSubOpenYesNo(s32 x, s32 y, s32 z, s32 w);
void    memcardTaskCall(s32 a, s32 b, s32 c);
s32     memcardIsMemCardValid(void);
void    fadeCheck(s32 type);
void    menuToolSetSelect(s32 mode);
void    GSmsgPrint2(s32 x, s32 y, s32 z, s32 msgId, s32 flags, s32 a, s32 b);
void    menuTitleCursorAnime(void* work, void* item);
s32     fn_800A3A1C(void);

/* Global variables */
static struct {
    s32    field_0;
    s32    field_4;
    s32    field_8;
    s32    field_C;
    float  field_10;
    float  field_14;
    float  field_18;
    float  field_1C;
    float  field_20;
    float  field_24;
    float  field_28;
} _menuTitleOptionWork;  // 0x8043D2F8

static float _atable[3];  // 0x8043D324

/* Constants */
static const float FADE_VALUE = 0.5f;       // @2210
static const float FRAME_MAX = 1.0f;        // @2228
static const float FRAME_MIN = 0.0f;        // @2229
static const float ROT_BASE = 0.20943952f;  // @2254 (pi/15)
static const float ROT_SPEED = 6.2831855f;  // @2259 (2*pi)
static const float POS_SPEED = 3.0f;        // @2387

/* Message table */
static const s32 menuOptionMsgTable[3] = {
    0x42E7, 0x42E8, 0x42E9
};

/* Jump table for menuTitleOptionHook */
static void (*const hookJumpTable[18])(void) = {
    (void(*)(void))0x800A7300,  // 0x56
    (void(*)(void))0x800A7320,
    (void(*)(void))0x800A7340,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7178,
    (void(*)(void))0x800A71C8,
    (void(*)(void))0x800A7218,
    (void(*)(void))0x800A7270,
    (void(*)(void))0x800A72C8,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7398,
    (void(*)(void))0x800A7360,
};

/*
  Address: 0x800A6D54 | size: 0xDC
  menuTitleOptionCtrl(void* work)
  Main control function for title option menu.
*/
void menuTitleOptionCtrl(void* work) {
    menuTitleCursorAnimeMain(work);

    s8 state = ((u8*)work)[1];
    s32 menuId = ((u32*)work)[0x9C / 4];

    if (state == 2) {
        // State 2: Calculate alpha for 3 items
        menuPdaSubCalcAlpha(_atable, 3, 3);
    } else if (state == 0) {
        // State 0: Opening
        if (((u8*)work)[2] == 0) {
            winSeqSetMenu(((u32*)work)[1], 0x24);
            fadeSet(2, FADE_VALUE);
            ((u8*)work)[2] = 1;
        }
    } else if (state >= 2 && state < 4) {
        // State 3: Option menu
        if (((u8*)work)[2] == 0) {
            winSeqSetMenu(((u32*)work)[1], 0x17B);
            fadeSet(3, FADE_VALUE);
            ((u8*)work)[2] = 1;
        }
    }
}

/*
  Address: 0x800A6E30 | size: 0x16C
  menuTitleOptionCursorControl(void* work)
  Handles cursor movement and input for title option menu.
*/
void menuTitleOptionCursorControl(void* work) {
    s32 menuId = ((u32*)work)[0x9C / 4];
    s32 keyInfo = windowGetKeyInfo(menuId);
    s32 keyRepeat = windowGetKeyRepeat(menuId);
    _menuTitleOptionSetFrameSec__Fv();
    _menuTitleOptionCalcRot__Fv();
    menuCursorNormal(work, 1);

    s16 cursorIdx = ((s16*)work)[0xA / 2];

    if (cursorIdx == 1) {
        // Cursor at index 1
        if (keyInfo & (1 << 29)) {  // A button press
            menuPlaySe(((u32*)work)[1], 1);
            if (gamedatasaveGetStatus(0, 9) != 0) {
                GSinputMotorStart(1, 0, 0xFF, 0x1E, 0);
            }
            gamedatasaveSetStatus(0, 9, 0);
            _menuTitleOptionWork.field_8 = 1;
            _menuTitleOptionWork.field_20 = FRAME_MAX;
            _menuTitleOptionWork.field_C = 1;
        }
        if (keyInfo & (1 << 28)) {  // B button press
            menuPlaySe(((u32*)work)[1], 1);
            gamedatasaveSetStatus(0, 9, 1);
            _menuTitleOptionWork.field_18 = FRAME_MIN;
        }
    } else if (cursorIdx == 0) {
        // Cursor at index 0
        if (keyInfo & (1 << 29)) {  // A button press
            menuPlaySe(((u32*)work)[1], 1);
            GSsndSetOutputMode(1, 1);
        }
        if (keyInfo & (1 << 28)) {  // B button press
            menuPlaySe(((u32*)work)[1], 1);
            GSsndSetOutputMode(0, 0);
        }
    }
}

/*
  Address: 0x800A6F9C | size: 0x12C
  _menuTitleOptionSetFrameSec()
  Updates frame timing for animations.
*/
void _menuTitleOptionSetFrameSec__Fv(void) {
    float dt = timeGetLastFrameSec();
    _menuTitleOptionWork.field_1C = dt;
    _menuTitleOptionWork.field_24 += dt;

    if (_menuTitleOptionWork.field_24 >= FRAME_MAX) {
        _menuTitleOptionWork.field_24 = FRAME_MIN;
    }

    s32 status = gamedatasaveGetStatus(0, 9);
    if (status == 1) {
        if (_menuTitleOptionWork.field_20 != FRAME_MIN) {
            _menuTitleOptionWork.field_20 += dt;
            if (_menuTitleOptionWork.field_20 >= FRAME_MAX) {
                _menuTitleOptionWork.field_20 = FRAME_MIN;
                _menuTitleOptionWork.field_8 = 0;
            }
        }
    } else {
        _menuTitleOptionWork.field_20 += dt;
        if (_menuTitleOptionWork.field_20 >= FRAME_MAX) {
            _menuTitleOptionWork.field_8++;
            _menuTitleOptionWork.field_20 = FRAME_MIN;

            if (_menuTitleOptionWork.field_8 > 0) {
                _menuTitleOptionWork.field_C ^= 1;
                if (_menuTitleOptionWork.field_C) {
                    _menuTitleOptionWork.field_18 = FRAME_MIN;
                } else {
                    _menuTitleOptionWork.field_18 = ROT_BASE;
                }
            }
        }
    }
}

/*
  Address: 0x800A70C8 | size: 0x54
  _menuTitleOptionCalcRot()
  Calculates rotation angle for animations.
*/
void _menuTitleOptionCalcRot__Fv(void) {
    float angle = sin(ROT_SPEED * _menuTitleOptionWork.field_20 * _menuTitleOptionWork.field_28);
    _menuTitleOptionWork.field_10 = _menuTitleOptionWork.field_18 * angle;
}

/*
  Address: 0x800A711C | size: 0x294
  menuTitleOptionHook(void* work, void* item)
  Hook function called for each menu item.
  Uses jump table based on item index.
*/
void menuTitleOptionHook(void* work, void* item) {
    s8 state = ((u8*)work)[1];
    s32 menuId = ((u32*)work)[0x9C / 4];

    if (state >= 3) {
        return;
    }

    s16 itemIdx = ((s16*)item)[3];
    s32 offset = itemIdx - 0x56;
    if (offset < 0 || offset > 17) {
        return;
    }

    // Jump table dispatch
    // ... (handled by compiler-generated switch)

    switch (offset) {
        case 5:  // Music toggle
            if (GSsndGetOutputMode() == 0) {
                winSpriteSetDisp(item, 1);
                if (((s16*)work)[0xA / 2] == 0) {
                    menuTitleCursorAnime(work, item);
                }
            } else {
                winSpriteSetDisp(item, 0);
            }
            break;
        case 6:  // SE toggle
            if (GSsndGetOutputMode() == 0) {
                winSpriteSetDisp(item, 0);
            } else {
                winSpriteSetDisp(item, 1);
                if (((s16*)work)[0xA / 2] == 0) {
                    menuTitleCursorAnime(work, item);
                }
            }
            break;
        case 7:  // Vibration toggle
            if (gamedatasaveGetStatus(0, 9) == 1) {
                winSpriteSetDisp(item, 0);
            } else {
                winSpriteSetDisp(item, 1);
                if (((s16*)work)[0xA / 2] == 1) {
                    menuTitleCursorAnime(work, item);
                }
            }
            break;
        case 8:  // Another vibration option
            if (gamedatasaveGetStatus(0, 9) == 1) {
                winSpriteSetDisp(item, 1);
                if (((s16*)work)[0xA / 2] == 1) {
                    menuTitleCursorAnime(work, item);
                }
            } else {
                winSpriteSetDisp(item, 0);
            }
            break;
        case 9:  // Demo option
            if (((s16*)work)[0xA / 2] == 2) {
                winSpriteSetDisp(item, 1);
                menuTitleCursorAnime(work, item);
            } else {
                winSpriteSetDisp(item, 0);
            }
            break;
        case 0:  // Alpha value 0
            _atable[0] = (float)((s32)_atable[0]);
            ((u8*)item)[0x67] = (u8)_atable[0];
            break;
        case 1:  // Alpha value 1
            _atable[1] = (float)((s32)_atable[1]);
            ((u8*)item)[0x67] = (u8)_atable[1];
            break;
        case 2:  // Alpha value 2
            _atable[2] = (float)((s32)_atable[2]);
            ((u8*)item)[0x67] = (u8)_atable[2];
            break;
        case 17: // Message display
            if (((s16*)work)[0xA / 2] >= 0) {
                GSmsgPrint2(
                    ((u32*)work)[0x1C / 4],
                    0,
                    -0x100 | ((u8*)work)[0x93],
                    menuOptionMsgTable[((s16*)work)[0xA / 2]],
                    0, -8, 0
                );
            }
            break;
    }
}

/*
  Address: 0x800A73B0 | size: 0x168
  menuTitleOption()
  Main entry point for title option menu.
*/
void menuTitleOption(void) {
    s32 state = 0;
    s32 flag = 1;
    _menuTitleOptionInit__Fv();

    while (1) {
        if (state == 0x64) {
            // Check save status
            s32 saveStatus = gamedatasaveGetStatus(0, 9);
            if (saveStatus != /* previous */) {
                if (memcardIsMemCardValid()) {
                    winMsgOpen(1, 0x4457, 1, 1);
                    s32 result = menuSubOpenYesNo(0, 0x3C, 0xDC, 1);
                    if (result == 0) {
                        memcardTaskCall(7, 2, 0);
                    }
                    winMsgClose(1);
                }
            }
            flag = 0;
        }

        if (flag == 0) {
            break;
        }

        // Main loop continues...
        fn_800A3A1C();
        _menuTitleOptionClose__Fl(0x117);
        fadeCheck(1);
        _menuTitleOptionExit__Fv();
    }
}

/*
  Address: 0x800A7518 | size: 0x5C
  menuTitleOptionButton(void* work)
  Handles button input for title option menu.
*/
void menuTitleOptionButton(void* work) {
    s16 field_9E = ((s16*)work)[0x9E / 2];
    if (field_9E == 2) {
        menuButtonNormal(work);
    } else {
        s32 keyInfo = windowGetKeyInfo(0);
        if (keyInfo & (1 << 26)) {  // Start button
            ((u8*)work)[0xA4] = 1;
            ((u8*)work)[0xA5] = 1;
        }
    }
}

/*
  Address: 0x800A7574 | size: 0x28
  _menuTitleOptionClose(long layers)
  Closes menu with custom settings.
*/
void _menuTitleOptionClose__Fl(s32 layers) {
    menuCloseCustom(layers, 0, 1);
}

/*
  Address: 0x800A759C | size: 0x4
  _menuTitleOptionExit()
  Exit function (empty placeholder).
*/
void _menuTitleOptionExit__Fv(void) {
    // Empty function
}

/*
  Address: 0x800A75A0 | size: 0x74
  _menuTitleOptionInit()
  Initializes title option menu work structure.
*/
void _menuTitleOptionInit__Fv(void) {
    menuToolSetSelect(0);

    _menuTitleOptionWork.field_0 = 0;
    _menuTitleOptionWork.field_14 = FRAME_MIN;
    _menuTitleOptionWork.field_10 = FRAME_MIN;
    _menuTitleOptionWork.field_4 = 0;
    _menuTitleOptionWork.field_20 = FRAME_MIN;
    _menuTitleOptionWork.field_28 = POS_SPEED;
    _menuTitleOptionWork.field_18 = ROT_BASE;
    _menuTitleOptionWork.field_8 = 0;
    _menuTitleOptionWork.field_C = 0;

    menuPdaSubInitAlpha(_atable, 3, 0);
}

/* Helper function declarations */
void winSpriteSetDisp(void* sprite, s32 disp);
float timeGetLastFrameSec(void);
float sin(float x);
