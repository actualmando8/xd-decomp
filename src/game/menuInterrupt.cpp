// Decompiled from: menuInterrupt.cpp
// Address range: 0x800665F4..0x80066C48 | size: 0x654

/* Forward declarations */
s32     menuIsCheck(s32 menuId);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 sync);
s32     menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32* e);
s32     winSpriteGetLayerID(void* winSprite);
void*   GSgfxLayerFindByID(s32 id);
void*   GSfloorGetCurrent(void);
void*   floorDataBiosGetPtr(void* floor);
s32     floorDataBiosGetFloorKind(void* floorData);
s32     GSflagTest(s32 flag);
void    winSpriteSetDisp(void* winSprite, s32 disp);
void    menuButtonNormal(void* winWork);
s32     winSeqCheckMove(void* winWork, s32 seq);
void    winSeqSetMenu(void* winWork, s32 seq);
void    GSsndPlayNow(s32 sndId);
void    GSinputMotorStart(s32 a, s32 b, s32 c, s32 d, s32 e);
void*   gamedatasaveGetStatus(s32 a, s32 b);
float   cos(float x);
float   timeGetLastFrameSec(void);

/* Constants for alpha calculation */
static const float TWO_PI = 6.2831855f;
static const float PERIOD = 1.5f;
static const float ALPHA_SCALE = 300.0f;
static const float ONE = 1.0f;
static const float HALF = 0.5f;

/* Global state */
static u8 _menuIntVibFlag = 1;
static u8 _underTakerIconFlag = 1;
static float _menuIntFrameCount;
static float _menuIntFrameCount2;

extern void* undertakerdata;

/*
  Address: 0x800665F4 | size: 0x5C
  menuIntUnderTakerOpenIcon()
  Toggles UnderTaker icon menu (0xC1). If open, closes it. If closed, opens it.
*/
void menuIntUnderTakerOpenIcon(void) {
    if (menuIsCheck(0xC1)) {
        menuClose(0xC1);
    } else {
        menuOpenCustom(0xC1, 0, 0, 0, 1, 0);
    }
}

/*
  Address: 0x80066650 | size: 0x44
  menuIntUnderTakerMenuClose()
  Closes UnderTaker icon menu with sync.
*/
void menuIntUnderTakerMenuClose(void) {
    if (menuIsCheck(0xC1)) {
        menuClose(0xC1);
        menuCloseSync(0xC1, 1);
    }
}

/*
  Address: 0x80066694 | size: 0x44
  menuIntUnderTakerMenuOpen()
  Opens UnderTaker icon menu and sets vibration flag.
*/
void menuIntUnderTakerMenuOpen(void) {
    _menuIntVibFlag = 1;
    menuOpenCustom(0xC1, 0, 0, 0, 1, 0);
}

/*
  Address: 0x800666D8 | size: 0xC
  menuIntUnderTakerDispIconRestore2()
  Enables UnderTaker icon display.
*/
void menuIntUnderTakerDispIconRestore2(void) {
    _underTakerIconFlag = 1;
}

/*
  Address: 0x800666E4 | size: 0xC
  menuIntUnderTakerDispIconOff2()
  Disables UnderTaker icon display.
*/
void menuIntUnderTakerDispIconOff2(void) {
    _underTakerIconFlag = 0;
}

/*
  Address: 0x800666F0 | size: 0xC8
  menuIntUnderTakerHook(void* winWork, void* spriteWork)
  Hook function for UnderTaker icon. Shows/hides based on floor kind and flags.
*/
void menuIntUnderTakerHook(void* winWork, void* spriteWork) {
    winSpriteGetLayerID(spriteWork);
    GSgfxLayerFindByID(0);
    void* floor = GSfloorGetCurrent();
    floorDataBiosGetPtr(floor);
    s32 floorKind = floorDataBiosGetFloorKind(floor);
    
    if (_underTakerIconFlag) {
        void* utData = undertakerdata;
        s32 flag = ((u32*)utData)[0x24 / 4];
        
        if (GSflagTest(flag)) {
            if (floorKind == 1) {
                winSpriteSetDisp(spriteWork, 1);
                
                s16 spriteIdx = ((s16*)spriteWork)[3];
                if (spriteIdx == 0x65C) {
                    if (((u8*)winWork)[1] != 0) {
                        s32 alpha = _menuIntGetAlpha2__Fv();
                        ((u8*)spriteWork)[0x67] = (u8)alpha;
                    }
                }
                return;
            }
        }
    }
    
    winSpriteSetDisp(spriteWork, 0);
}

/*
  Address: 0x800667B8 | size: 0x98
  _menuIntGetAlpha2__Fv()
  Calculates pulsing alpha value using cosine wave.
  Formula: alpha = ((cos(TWO_PI * frameCount / PERIOD) + 1) * 0.5 * ALPHA_SCALE)
  Clamped to range [0x32, 0xFF].
*/
static s32 _menuIntGetAlpha2__Fv(void) {
    float value = TWO_PI * _menuIntFrameCount2 / PERIOD;
    float cosVal = cos(value);
    cosVal = (s32)cosVal; // frsp - truncate to integer float
    
    float alpha = (cosVal + ONE) * HALF * ALPHA_SCALE;
    s32 alphaInt = (s32)alpha; // fctiwz
    
    if (alphaInt > 0xFF) alphaInt = 0xFF;
    if (alphaInt < 0x32) alphaInt = 0x32;
    
    float dt = timeGetLastFrameSec();
    _menuIntFrameCount2 += dt;
    
    return alphaInt;
}

/*
  Address: 0x80066850 | size: 0xB8
  menuIntUnderTakerMainCtrl(void* winWork)
  Main control for UnderTaker interrupt. Handles state transitions.
*/
s32 menuIntUnderTakerMainCtrl(void* winWork) {
    s8 state = ((s8*)winWork)[1];
    
    switch (state) {
        case 0: {
            GSsndPlayNow(0x5B4);
            if (_menuIntVibFlag) {
                _menuIntVibSet__Fv();
            }
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x171);
                ((s8*)winWork)[2] = 1;
            }
            _menuIntVibFlag = 1;
            break;
        }
        case 3: {
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x177);
                ((s8*)winWork)[2] = 1;
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}

/*
  Address: 0x80066908 | size: 0x128
  menuIntHook(void* winWork, void* spriteWork)
  Hook for interrupt icons. Handles display based on sprite index and game state.
  Sprite indices: 0x4BE (mail), 0x505 (phone), 0x507 (BA)
*/
void menuIntHook(void* winWork, void* spriteWork) {
    s16 spriteIdx = ((s16*)spriteWork)[3];
    void* data = ((void**)winWork)[0x68 / 4];
    s32 state = ((u32*)data)[0];
    
    if (spriteIdx == 0x4BE) {
        // Mail icon
        if (state == 0) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
            if (((u8*)winWork)[1] != 0) {
                s32 alpha = _menuIntGetAlpha__Fv();
                ((u8*)spriteWork)[0x67] = (u8)alpha;
            }
        }
    } else if (spriteIdx == 0x505) {
        // Phone icon
        if (state == 1) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
            if (((u8*)winWork)[1] != 0) {
                s32 alpha = _menuIntGetAlpha__Fv();
                ((u8*)spriteWork)[0x67] = (u8)alpha;
            }
        }
    } else if (spriteIdx >= 0x507) {
        // BA icon
        if (state == 2) {
            winSpriteSetDisp(spriteWork, 0);
        } else {
            winSpriteSetDisp(spriteWork, 1);
            if (((u8*)winWork)[1] != 0) {
                s32 alpha = _menuIntGetAlpha__Fv();
                ((u8*)spriteWork)[0x67] = (u8)alpha;
            }
        }
    }
}

/*
  Address: 0x80066A30 | size: 0x98
  _menuIntGetAlpha__Fv()
  Calculates pulsing alpha value using cosine wave (same as GetAlpha2, different counter).
*/
static s32 _menuIntGetAlpha__Fv(void) {
    float value = TWO_PI * _menuIntFrameCount / PERIOD;
    float cosVal = cos(value);
    cosVal = (s32)cosVal; // frsp
    
    float alpha = (cosVal + ONE) * HALF * ALPHA_SCALE;
    s32 alphaInt = (s32)alpha; // fctiwz
    
    if (alphaInt > 0xFF) alphaInt = 0xFF;
    if (alphaInt < 0x32) alphaInt = 0x32;
    
    float dt = timeGetLastFrameSec();
    _menuIntFrameCount += dt;
    
    return alphaInt;
}

/*
  Address: 0x80066AC8 | size: 0x44
  menuIntButton(void* winWork)
  Button handler for interrupt icons. Triggers normal button if no movement.
*/
void menuIntButton(void* winWork) {
    if (winSeqCheckMove(winWork, 0) == 0) {
        menuButtonNormal(winWork);
    }
}

/*
  Address: 0x80066B0C | size: 0xF4
  menuIntMainCtrl(void* winWork)
  Main control for interrupt icons. Handles state transitions and sound effects.
*/
s32 menuIntMainCtrl(void* winWork) {
    s8 state = ((s8*)winWork)[1];
    void* data = ((void**)winWork)[0x68 / 4];
    
    switch (state) {
        case 0: {
            _menuIntVibSet__Fv();
            
            s32 dataState = ((u32*)data)[0];
            s32 sndId = 0;
            
            if (dataState == 0) {
                sndId = 0x566;
            } else if (dataState == 1) {
                sndId = 0x564;
            } else if (dataState == 2) {
                sndId = 0x565;
            } else if (dataState >= 3) {
                // No sound
            }
            
            if (sndId != 0) {
                GSsndPlayNow(sndId);
            }
            
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x171);
                ((s8*)winWork)[2] = 1;
            }
            break;
        }
        case 3: {
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x177);
                ((s8*)winWork)[2] = 1;
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}

/*
  Address: 0x80066C00 | size: 0x48
  _menuIntVibSet__Fv()
  Starts controller vibration if game condition allows.
  Checks gamedatasaveGetStatus(0, 9) - if returns 0, enables vibration.
*/
static void _menuIntVibSet__Fv(void) {
    s32 status = gamedatasaveGetStatus(0, 9);
    if (status != 0) {
        GSinputMotorStart(1, 0, 0xFF, 0x1E, 0);
    }
}
