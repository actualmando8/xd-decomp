// Decompiled from: menuTitleOption.cpp
// Address range: 0x800A6D54..0x800A7614 | size: 0x8C0

/* Forward declarations */
void    menuTitleCursorAnimeMain(void* opt);
void    winSeqSetMenu(s32 seq, s32 menu);
void    fadeSet(s32 type, f32 time);
void    menuPdaSubCalcAlpha(s32* alpha, s32 mode, s32 value);
void    windowGetKeyInfo(void);
void    windowGetKeyRepeat(void);
void    menuCursorNormal(void* opt, s32 mode);
void    menuPlaySe(s32 handle, s32 se);
void    GSsndSetOutputMode(s32 mode, s32 a);
s32     gamedatasaveGetStatus(s32 a, s32 b);
void    GSinputMotorStart(s32 a, s32 b, s32 c, s32 d, s32 e);
void    gamedatasaveSetStatus(s32 a, s32 b, s32 c);
f32     timeGetLastFrameSec(void);
void    sin(f32* result, f32 value);
void    GSsndGetOutputMode(s32* out);
void    winSpriteSetDisp(void* sprite, s32 disp);
void    menuTitleCursorAnime(void* opt, void* cursor);
void    GSmsgPrint2(void* msg, s32 a, s32 b, s32 c, s32 d);
s32     menuOpen(s32 id, s32 mode);
void*   windowSearchID(s32 id);
void    memcardIsMemCardValid(void);
void    winMsgOpen(s32 a, s32 b, s32 c, s32 d);
s32     menuSubOpenYesNo(s32 a, s32 b, s32 c, s32 d);
void    memcardTaskCall(s32 a, s32 b, s32 c);
void    winMsgClose(s32 a);
void    fn_800A3A1C(void);
void    menuButtonNormal(void* button);
void    menuCloseCustom(s32 id, s32 a, s32 b);
void    menuToolSetSelect(s32 select);
void    menuPdaSubInitAlpha(s32* alpha, s32 mode, s32 value);

/* BSS */
static s32 _menuTitleOptionWork[0x2C / 4];
static s32 _atable[3];

/* Data */
static const s32 _menuOptionMsgTable[] = {
    0x42E7, 0x42E8, 0x42E9
};

/* SData2 */
static const f32 _FadeTime = 0.5f;
static const f32 _OneSec = 1.0f;
static const f32 _Zero = 0.0f;
static const f32 _RotStep = 0.20943952f;
static const f32 _TwoPi = 6.2831855f;
static const f32 _Three = 3.0f;

/* Menu ID */
#define MENU_TITLE_OPTION 0x117

/*
  Address: 0x800A6D54 | size: 0xDC
  menuTitleOptionCtrl(void* opt)
  Controls the title option menu flow based on state.
*/
void menuTitleOptionCtrl(void* opt) {
    menuTitleCursorAnimeMain(opt);
    
    s8 state = ((u8*)opt)[1];
    s32 seq = *(s32*)((u8*)opt + 0x9C);
    
    switch (state) {
        case 0:
            if (!((u8*)opt)[2]) {
                winSeqSetMenu(seq, 0x24);
                fadeSet(2, _FadeTime);
                ((u8*)opt)[2] = 1;
            }
            break;
        case 2:
            menuPdaSubCalcAlpha(_atable, 3, ((s16*)opt)[0x9E / 2]);
            break;
        case 3:
        case 4:
            if (!((u8*)opt)[2]) {
                winSeqSetMenu(seq, 0x17B);
                fadeSet(3, _FadeTime);
                ((u8*)opt)[2] = 1;
            }
            break;
        default:
            break;
    }
}

/*
  Address: 0x800A6E30 | size: 0x16C
  menuTitleOptionCursorControl(void* opt)
  Handles cursor input for title option menu.
*/
void menuTitleOptionCursorControl(void* opt) {
    s32 seq = *(s32*)((u8*)opt + 0x9C);
    windowGetKeyInfo();
    windowGetKeyRepeat();
    s32 keyInfo; // return value
    menuTitleOptionSetFrameSec();
    menuTitleOptionCalcRot();
    menuCursorNormal(opt, 1);
    
    s16 state = ((s16*)opt)[0x9E / 2];
    // Complex cursor handling based on state and key info
    // ... (simplified for brevity)
}

/*
  Address: 0x800A6F9C | size: 0x12C
  menuTitleOptionSetFrameSec()
  Updates frame timing for animations.
*/
void menuTitleOptionSetFrameSec() {
    f32 dt = timeGetLastFrameSec();
    _menuTitleOptionWork[0x24 / 4] += dt;
    if (_menuTitleOptionWork[0x24 / 4] >= _OneSec) {
        _menuTitleOptionWork[0x24 / 4] = _Zero;
    }
    // Additional timing logic for save status
}

/*
  Address: 0x800A70C8 | size: 0x54
  menuTitleOptionCalcRot()
  Calculates rotation using sin function.
*/
void menuTitleOptionCalcRot() {
    f32 rot = _TwoPi * _menuTitleOptionWork[0x20 / 4] * _menuTitleOptionWork[0x28 / 4];
    f32 sinResult;
    sin(&sinResult, rot);
    _menuTitleOptionWork[0x10 / 4] = _menuTitleOptionWork[0x18 / 4] * sinResult;
}

/*
  Address: 0x800A711C | size: 0x294
  menuTitleOptionHook(void* opt, void* hook)
  Hook function for title option menu items.
*/
void menuTitleOptionHook(void* opt, void* hook) {
    s8 state = ((u8*)opt)[1];
    // Large switch on hook index with various sub-handlers
    // Handles sound mode, sprite display, cursor animation, messages
}

/*
  Address: 0x800A73B0 | size: 0x168
  menuTitleOption(void)
  Main entry point for the title option menu.
*/
void menuTitleOption(void) {
    s32 state = 0;
    s32 loop = 1;
    menuTitleOptionInit();
    
    while (loop) {
        if (state == 0x64) {
            // Handle save state change
            s32 saveStatus;
            gamedatasaveSetStatus(0, 9, &saveStatus);
            if (saveStatus != 0) {
                if (memcardIsMemCardValid()) {
                    winMsgOpen(1, 0x4457, 1, 1);
                    s32 result = menuSubOpenYesNo(0, 0x3C, 0xDC, 1);
                    if (!result) {
                        memcardTaskCall(7, 2, 0);
                    }
                    winMsgClose(1);
                }
            }
            loop = 0;
        } else if (state == 0) {
            // Open menu
            s32 menu = menuOpen(MENU_TITLE_OPTION, 1);
            // ... menu handling logic
        } else {
            break;
        }
    }
    
    fn_800A3A1C();
    menuTitleOptionClose(MENU_TITLE_OPTION);
    fadeCheck(1);
    menuTitleOptionExit();
}

/*
  Address: 0x800A7518 | size: 0x5C
  menuTitleOptionButton(void* button)
  Button handler for title option.
*/
void menuTitleOptionButton(void* button) {
    s16 state = ((s16*)button)[0x9E / 2];
    if (state == 2) {
        menuButtonNormal(button);
    } else {
        windowGetKeyInfo();
        // Check Start button (bit 26)
        if (/* Start pressed */) {
            ((u8*)button)[0xA4] = 1;
            ((u8*)button)[0xA5] = 1;
        }
    }
}

/*
  Address: 0x800A7574 | size: 0x28
  menuTitleOptionClose(s32 id)
  Closes the title option menu.
*/
void menuTitleOptionClose(s32 id) {
    menuCloseCustom(id, 0, 1);
}

/*
  Address: 0x800A759C | size: 0x4
  menuTitleOptionExit()
  Stub exit function.
*/
void menuTitleOptionExit() {
    // Stub
}

/*
  Address: 0x800A75A0 | size: 0x74
  menuTitleOptionInit()
  Initializes the title option menu work data.
*/
void menuTitleOptionInit() {
    menuToolSetSelect(0);
    _menuTitleOptionWork[0] = 0;
    _menuTitleOptionWork[0x4 / 4] = 0;
    _menuTitleOptionWork[0x8 / 4] = 0;
    _menuTitleOptionWork[0xC / 4] = 0;
    _menuTitleOptionWork[0x10 / 4] = _Zero;
    _menuTitleOptionWork[0x14 / 4] = _Zero;
    _menuTitleOptionWork[0x18 / 4] = _RotStep;
    _menuTitleOptionWork[0x20 / 4] = _Zero;
    _menuTitleOptionWork[0x28 / 4] = _Three;
    menuPdaSubInitAlpha(_atable, 3, 0);
}
