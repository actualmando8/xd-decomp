// Decompiled from: menuField.cpp
// Address range: 0x8005B3D8..0x8005C060 | size: 0xC88
// PowerPC 750CL / Gekko (GameCube)
// Compiler: Metrowerks CodeWarrior

/*
  Field menu module - handles in-field menu display with cursor animations.
  Calling convention: r3-r7 args, r3 return
*/

#include <math.h>

// Forward declarations
typedef struct tagWINDOW_WORK tagWINDOW_WORK;
typedef struct tagSPRITE_WORK tagSPRITE_WORK;
typedef struct GSvec GSvec;

void    __construct_array(void* ptr, void(*ctor)(void*), s32 start, s32 size, s32 count);
s32     fadeCheck(void);
s32     heroMoveCheckEvent(GSvec* pos);
void    floorEventExecScript(s32 event, s32 param);
void    menuIntUnderTakerDispIconOff2(void);
void    heroMoveInitEvent(void);
void    mailMainReceiveTerminate(void);
void    GSthreadSwitch(void);
void    floorFieldCameraPause(void);
void    GSmodelAllPauseAnimation(void);
s32     GSgfxVideoGetVsyncRate(void);
void    menuCreateOffScreen(void);
s32     menuGetOffScreenFlag(void);
s32     soundGetEnvID(void);
s32     soundGetVolume(void);
void    GSsndPushVolumeALL(s32 vol, s32 time, s32 flag1, s32 flag2);
void    GSgfxVideoSetLockFrameRate(s32 rate);
s32     GSflagGet(s32 id);
s32     fn_80233AB4(s32 param);
void    menuOpen(s32 id, s32 param);
s32     menuCloseCustom(s32 id, s32 param0, s32 param1);
void    menuPokemonOpen(s32 id, s32 param0, s32 param1);
void    menuPdaOpen(void);
s32     menuPocket2Open(s32 id, void* data, s32 param);
s32     menuPocket2GetItemScript(s32 result);
void    heroMoveAddAutoEvent(GSvec* pos, s32 event, s32 item, s32 param1, s32 param2);
void    menuReport(void);
void    menuClose(s32 id);
s32     scriptContinueSave(void);
void    menuOffScreenRelease(void);
void    GSsndPopVolumeALL(s32 vol, s32 flag1, s32 flag2);
void    soundSetVolumeID(s32 id, s32 vol, s32 param);
void    menuCloseSync(s32 id, s32 param);
void    heroMoveTermEvent(void);
void    GSmodelAllUnpauseAnimation(void);
void    floorFieldCameraUnpause(void);
void    menuIntUnderTakerDispIconRestore2(void);
void    winAnimeCursor(tagWINDOW_WORK* win);
void    winSpriteSetDisp(tagSPRITE_WORK* sprite, s32 disp);
void    winSetSequence(tagSPRITE_WORK* sprite, s32 seq);
void    winSeqSetMenu(s32 seqId, s32 param);
s32     timeGetLastFrameSec(void);
float   menuGetLastTime(void);
void    GSmsgGetRect(void* msg, s32* out);
void    GSmsgPrint2(void* msg, s16 x, s16 y, s16 z);
s32     pokecoloGetRomVersion(void);
void    sin(float* rad, float* result);

// GSvec structure (12 bytes = 3 floats)
struct GSvec {
    float x, y, z;
};

// GSvec constructor (empty)
void GSvec::GSvec(void) {
}

// SDA21-relative globals
static u32  barcolor = 0xC0C0D000;
static float _cursorSec = 0.8f;
static float _max_alpha = 255.0f;
static float _min_alpha = 200.0f;

// SBSS globals
static u8   _openFieldMenu;
static float _fieldMenuTimer;
static s32  _soundEnvID;
static s32  _soundEnvVol;
static float _menuFieldCursorAngle;

// BSS globals
static float _menuFiledAlpha[6];  // size 0x14 = 5 floats + padding

// ROData constants
static const float const_0    = 0.0f;
static const float const_255  = 255.0f;
static const float const_0_4  = 0.4f;
static const float const_pi   = 3.1415927f;
static const float const_2    = 2.0f;
static const float const_2pi  = 6.2831855f;
static const float const_1    = 1.0f;
static const float const_0_5  = 0.5f;
static const float const_20   = 20.0f;
static const float const_50   = 50.0f;
static const double const_dbl = 4503599627370496.0;  // 2^52

// ============================================================================
// Helper functions (local / static)
// ============================================================================

/*
  Address: 0x8005C01C | size: 0x44
  _menuFieldCheckPDA()
  Checks if PDA menu should be available.
  Returns 1 for XD (romVer==1), or checks flag 0x3f1 for Colosseum.
*/
static s32 _menuFieldCheckPDA(void) {
    if (pokecoloGetRomVersion() == 1) {
        return 1;
    }
    s32 flag = GSflagGet(0x3f1);
    // Metrowerks idiom: (-flag)|flag >> 31 = (flag < 0) ? 1 : 0
    s32 val = (-flag) | flag;
    return val >> 31;
}

/*
  Address: 0x8005BFCC | size: 0x50
  _menuFieldCheckCursor(long menuType)
  Checks cursor based on menu type and PDA availability.
*/
static s32 _menuFieldCheckCursor(s32 menuType) {
    if (_menuFieldCheckPDA()) {
        return menuType;
    }
    // Adjust menuType based on comparison
    if (menuType < 1) {
        return menuType;
    }
    return menuType + 1;
}

/*
  Address: 0x8005B95C | size: 0xCC
  _animAlpha(long index)
  Animates alpha value using sine wave for cursor blinking.
  Uses _fieldMenuTimer with period 2*pi.
*/
static void _animAlpha(s32 index) {
    float timerIncrement = const_2 * menuGetLastTime() / _cursorSec;
    _fieldMenuTimer += timerIncrement;
    if (_fieldMenuTimer >= const_2pi) {
        _fieldMenuTimer -= const_2pi;
    }

    // Alpha = min_alpha + (max_alpha - min_alpha) * sin(timer) * 0.5 + 1.0
    float range = _max_alpha - _min_alpha;
    float sinResult;
    sin(&_fieldMenuTimer, &sinResult);
    float alpha = _min_alpha + range * sinResult * const_0_5 + const_1;

    // Clamp to 255
    if (alpha > const_255) {
        alpha = const_255;
    }

    _menuFiledAlpha[index] = alpha;
}

/*
  Address: 0x8005B888 | size: 0xD4
  _menuFieldDrawItemSub(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long index)
  Draws a menu item with alpha fade animation.
*/
static void _menuFieldDrawItemSub(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, s32 index) {
    float lastFrame = timeGetLastFrameSec();
    float fadeSpeed = lastFrame / const_0_4;

    if (win->field_0x9E == index) {
        winSpriteSetDisp(sprite, 1);
        _animAlpha(index);
    } else {
        // Fade out alpha
        float* alphaPtr = &_menuFiledAlpha[index];
        if (*alphaPtr > const_0) {
            *alphaPtr -= fadeSpeed;
            if (*alphaPtr < const_0) {
                *alphaPtr = const_0;
            }
        }
    }

    // Set color with alpha
    u32 color = barcolor;
    u32 alphaInt = (u32)(*alphaPtr);  // fctiwz truncation
    color = (color & 0xFFFFFF00) | (alphaInt & 0xFF);
    sprite->field_0x64 = color;
}

/*
  Address: 0x8005B7A4 | size: 0xE4
  _menuFieldCursorCheck(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long index)
  Checks cursor position and displays message.
*/
static void _menuFieldCursorCheck(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, s32 index) {
    winSpriteSetDisp(sprite, 0);

    void* msg = (void*)sprite->field_0x4C;
    if (msg != 0) {
        s16 offset;
        if (win->field_0x9E == index) {
            offset = 0xF0F1 - 0xF01;  // = 0xF1
        } else {
            offset = 0xF0F1 - 0xF80;  // = 0x71
        }

        s32 rectData;
        GSmsgGetRect(msg, &rectData);
        s16 width = (s16)(rectData >> 16);
        s16 x = sprite->field_0x54 - width;
        s32 signX = (x >> 31);
        x = (signX + x) >> 1;  // max(0, x)
        s16 finalX = (s16)x;

        GSmsgGetRect(msg, &rectData);
        s16 height = (s16)rectData;
        s32 baseY = win->field_0x1C;
        s16 y = baseY - sprite->field_0x56;
        s32 signY = (y >> 31);
        y = (signY + y) >> 1;
        s16 finalY = (s16)((y - 2) & 0xFFFF);

        GSmsgPrint2(msg, finalX, finalY, 0);
    }
}

/*
  Address: 0x8005B754 | size: 0x50
  _menuFieldFlashCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long index)
  Sets cursor visibility based on current selection.
*/
static void _menuFieldFlashCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, s32 index) {
    if (win->field_0x9E == index) {
        sprite->field_0x70 = _menuFieldCursorAngle;
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }
}

/*
  Address: 0x8005B6C4 | size: 0x90
  _menuFieldMenuCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long index)
  Handles menu cursor animation and display.
*/
static void _menuFieldMenuCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, s32 index) {
    if (win->field_0x9E == index) {
        if (win->field_0xA2 != index) {
            winAnimeCursor(win);
            _fieldMenuTimer = const_0;
        }
        winSpriteSetDisp(sprite, 1);
    } else {
        winSpriteSetDisp(sprite, 0);
    }

    if (win->field_0x1 == 3) {
        winSetSequence(sprite + 0xc, 0);
    }
}

// ============================================================================
// Public API functions (global)
// ============================================================================

/*
  Address: 0x8005B3D8 | size: 0x2EC
  menuFieldDrawItem2(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, long itemID)
  Dispatches drawing based on item ID (stored at sprite+0x6 as s16).
  
  Uses a large switch-like structure with binary search on itemID ranges.
  Item IDs map to different cursor/drawing functions with indices 0-4.
*/
void menuFieldDrawItem2(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, s32 itemID) {
    s16 id = sprite->field_0x6;

    // Binary search dispatch based on item ID ranges
    if (id == 0x2c6) {
        _menuFieldDrawItemSub(win, sprite, 3);
    } else if (id >= 0x2c6) {
        if (id == 0x66b) {
            _menuFieldMenuCursor(win, sprite, 0);
        } else if (id >= 0x66b) {
            if (id == 0x670) {
                _menuFieldMenuCursor(win, sprite, 0);
            } else if (id >= 0x670) {
                if (id == 0x673) {
                    _menuFieldMenuCursor(win, sprite, 3);
                } else if (id >= 0x673) {
                    // fallthrough
                } else if (id == 0x672) {
                    _menuFieldMenuCursor(win, sprite, 2);
                } else {
                    _menuFieldMenuCursor(win, sprite, 1);
                }
            } else if (id == 0x66e) {
                _menuFieldMenuCursor(win, sprite, 3);
            } else if (id >= 0x66e) {
                if (id == 0x66f) {
                    _menuFieldMenuCursor(win, sprite, 4);
                } else {
                    _menuFieldMenuCursor(win, sprite, 2);
                }
            } else if (id == 0x66d) {
                _menuFieldMenuCursor(win, sprite, 1);
            } else {
                _menuFieldMenuCursor(win, sprite, 0);
            }
        } else if (id == 0x2cb) {
            _menuFieldCursorCheck(win, sprite, 0);
        } else if (id >= 0x2cb) {
            if (id == 0x2ce) {
                _menuFieldCursorCheck(win, sprite, 3);
            } else if (id >= 0x2ce) {
                // fallthrough
            } else if (id == 0x2cd) {
                _menuFieldCursorCheck(win, sprite, 2);
            } else {
                _menuFieldCursorCheck(win, sprite, 1);
            }
        } else if (id == 0x2c9) {
            _menuFieldFlashCursor(win, sprite, 2);
        } else if (id >= 0x2c9) {
            if (id == 0x2ca) {
                _menuFieldFlashCursor(win, sprite, 3);
            } else {
                _menuFieldFlashCursor(win, sprite, 1);
            }
        } else if (id == 0x2c8) {
            _menuFieldFlashCursor(win, sprite, 0);
        } else {
            _menuFieldFlashCursor(win, sprite, 0);
        }
    } else if (id == 0x1e) {
        _menuFieldFlashCursor(win, sprite, 4);
    } else if (id >= 0x1e) {
        if (id == 0x23) {
            _menuFieldCursorCheck(win, sprite, 4);
        } else if (id >= 0x23) {
            if (id == 0x2c4) {
                _menuFieldDrawItemSub(win, sprite, 1);
            } else if (id >= 0x2c4) {
                if (id == 0x2c5) {
                    _menuFieldDrawItemSub(win, sprite, 2);
                } else {
                    _menuFieldFlashCursor(win, sprite, 3);
                }
            } else if (id == 0x2c3) {
                _menuFieldDrawItemSub(win, sprite, 0);
            } else {
                // fallthrough
            }
        } else if (id == 0x21) {
            _menuFieldCursorCheck(win, sprite, 2);
        } else if (id >= 0x21) {
            if (id == 0x22) {
                _menuFieldCursorCheck(win, sprite, 3);
            } else {
                _menuFieldCursorCheck(win, sprite, 1);
            }
        } else if (id == 0x20) {
            _menuFieldCursorCheck(win, sprite, 0);
        } else {
            _menuFieldCursorCheck(win, sprite, 0);
        }
    } else if (id == 0x19) {
        _menuFieldDrawItemSub(win, sprite, 4);
    } else if (id >= 0x19) {
        if (id == 0x1c) {
            _menuFieldFlashCursor(win, sprite, 2);
        } else if (id >= 0x1c) {
            if (id == 0x1d) {
                _menuFieldFlashCursor(win, sprite, 3);
            } else {
                _menuFieldFlashCursor(win, sprite, 0);
            }
        } else if (id == 0x1b) {
            _menuFieldFlashCursor(win, sprite, 1);
        } else {
            _menuFieldFlashCursor(win, sprite, 0);
        }
    } else if (id == 0x16) {
        _menuFieldDrawItemSub(win, sprite, 1);
    } else if (id >= 0x16) {
        if (id == 0x18) {
            _menuFieldDrawItemSub(win, sprite, 3);
        } else if (id >= 0x18) {
            _menuFieldDrawItemSub(win, sprite, 2);
        } else {
            _menuFieldDrawItemSub(win, sprite, 2);
        }
    } else if (id == 0x15) {
        // fallthrough
    } else if (id >= 0x15) {
        _menuFieldDrawItemSub(win, sprite, 0);
    }
    // Default: no action
}

/*
  Address: 0x8005BA28 | size: 0x138
  menuFieldMainCtrl(tagWINDOW_WORK* win)
  Main control for field menu opening/closing sequences.
  
  Sets up alpha values and menu sequences based on window state.
*/
s32 menuFieldMainCtrl(tagWINDOW_WORK* win) {
    s8 state = win->field_0x1;

    if (state == 3) {
        // Closing state
        if (win->field_0x2 == 0) {
            winSeqSetMenu(7, 0);
            win->field_0x2 = 1;
        }
    } else if (state >= 3) {
        // No action
    } else if (state == 0) {
        // Opening state
        if (win->field_0x2 == 0) {
            winSeqSetMenu(1, 0);
            s16 cursorPos = win->field_0x9E;
            _fieldMenuTimer = const_0;

            // Set alpha values based on cursor position
            for (s32 i = 0; i < 5; i++) {
                _menuFiledAlpha[i] = (cursorPos == i) ? const_0 : const_255;
            }
            win->field_0x2 = 1;
        }
    } else {
        // No action
    }

    return 0;
}

/*
  Address: 0x8005BB60 | size: 0x460
  menuFieldMain(s32 menuType)
  Main entry point for field menu.
  
  Handles:
  - Fade check and early return
  - Hero event processing
  - Camera/model pausing
  - Off-screen menu creation
  - Sound volume management
  - Menu selection dispatch (Pokemon, PDA, Pocket, Report)
  - Cleanup and restoration
*/
s32 menuFieldMain(s32 menuType) {
    GSvec vecArray1[3];  // stack at +0xc
    GSvec vecArray2[3];  // stack at +0x40
    GSvec vecArray3[3];  // stack at +0x74
    GSvec vecArray4[3];  // stack at +0xa8
    s32 fieldMenuType;

    // Construct GSvec arrays
    __construct_array(vecArray1, (void(*)(void*))GSvec::GSvec, 0, 12, 3);
    __construct_array(vecArray2, (void(*)(void*))GSvec::GSvec, 0, 12, 3);
    __construct_array(vecArray3, (void(*)(void*))GSvec::GSvec, 0, 12, 3);
    __construct_array(vecArray4, (void(*)(void*))GSvec::GSvec, 0, 12, 3);

    // Check for fade
    if (fadeCheck()) return 0;

    // Process hero events
    s32 eventCount = heroMoveCheckEvent(vecArray1);
    for (s32 i = 0; i < eventCount; i++) {
        s32 event = vecArray1[i].x;  // TODO: Verify event struct layout
        floorEventExecScript((s32)event, 4);
    }

    menuIntUnderTakerDispIconOff2();
    heroMoveInitEvent();
    mailMainReceiveTerminate();
    GSthreadSwitch();
    floorFieldCameraPause();
    GSmodelAllPauseAnimation();
    _openFieldMenu = 1;
    GSthreadSwitch();

    // Calculate fade timing
    s32 vsyncRate = GSgfxVideoGetVsyncRate();
    double timeBase = const_dbl;
    float fadeTime = const_20 / ((float)vsyncRate - (float)timeBase);
    menuCreateOffScreen();

    // Wait for off-screen ready
    while (!menuGetOffScreenFlag()) {
        GSthreadSwitch();
    }

    // Save sound state
    s32 envID = soundGetEnvID();
    _soundEnvID = envID;
    if (envID != 0) {
        _soundEnvVol = soundGetVolume();
    }

    // Push sound volume
    GSsndPushVolumeALL(0x55, 0x1f4, 1, 1);
    GSgfxVideoSetLockFrameRate(0);

    // Determine menu type based on flags
    if (!GSflagGet(0x30d)) {
        if (_menuFieldCheckPDA()) {
            fieldMenuType = 0x57;
        } else {
            fieldMenuType = 0x58;
        }
    } else {
        fieldMenuType = 0x70;
    }

    fn_80233AB4(fieldMenuType);

    // Menu type dispatch
    s8 romVer = menuType;
    if (romVer == 1) {
        // XD: Direct pocket menu
        s32 pocketResult = menuPocket2Open(0, vecArray1, 0);
        if (pocketResult >> 16 != 0) {
            s32 itemScript = menuPocket2GetItemScript(pocketResult);
            if ((itemScript + 0x10000) != 0) {
                heroMoveAddAutoEvent(vecArray2, itemScript & 0xFFFF, 0, 0, 0);
            }
        }
    } else if (romVer >= 1) {
        if (romVer < 0 || romVer > 4) {
            // Invalid - skip
        } else if (!GSflagGet(0x30d)) {
            // Normal menu flow
            _soundEnvID = 0;
            float maxAlpha = const_255;

            while (1) {
                GSgfxVideoSetLockFrameRate(0);
                _menuFiledAlpha[0] = maxAlpha;
                _menuFiledAlpha[1] = maxAlpha;
                _menuFiledAlpha[2] = maxAlpha;
                _menuFiledAlpha[3] = maxAlpha;
                _menuFiledAlpha[4] = maxAlpha;

                menuOpen(fieldMenuType, 1);
                s32 selection = _menuFieldCheckCursor(fieldMenuType);

                if (selection != 0) {
                    if (selection == 1) {
                        menuCloseCustom(fieldMenuType, 0, 1);
                        menuPdaOpen();
                        GSmodelAllPauseAnimation();
                    } else if (selection == 2) {
                        menuCloseCustom(fieldMenuType, 0, 1);
                        s32 pocketResult = menuPocket2Open(0, vecArray1, 0);
                        GSmodelAllPauseAnimation();
                        if (pocketResult >> 16 != 0) {
                            s32 itemScript = menuPocket2GetItemScript(pocketResult);
                            if ((itemScript + 0x10000) != 0) {
                                heroMoveAddAutoEvent(vecArray3, itemScript & 0xFFFF, 0, 0, 0);
                                break;
                            }
                        }
                    } else if (selection == 3) {
                        menuCloseCustom(fieldMenuType, 0, 1);
                        menuReport();
                    }
                    GSthreadSwitch();
                } else {
                    menuCloseCustom(fieldMenuType, 0, 1);
                    menuPokemonOpen(1, 0, 0);
                    GSmodelAllPauseAnimation();
                }
            }
        } else {
            // Flag 0x30d set - simplified flow
            _soundEnvID = 0;
            while (1) {
                GSgfxVideoSetLockFrameRate(0);
                menuOpen(fieldMenuType, 1);
                s32 selection = menuType;
                if (selection != 0) {
                    if (selection == 1) {
                        if (scriptContinueSave() == 1) {
                            menuOffScreenRelease();
                            _openFieldMenu = 0;
                            GSthreadSwitch();
                        }
                    } else {
                        // Other selections
                    }
                } else {
                    menuClose(fieldMenuType);
                    menuPokemonOpen(1, 0, 0);
                }
            }
        }
    }

    // Cleanup
    s32 pocketResult = menuPocket2GetItemScript(0);
    GSsndPopVolumeALL(0x1f4, 1, 1);

    // Restore sound volume
    s32 currentEnvID = soundGetEnvID();
    if (_soundEnvID == currentEnvID) {
        soundSetVolumeID(currentEnvID, 0x1f4, _soundEnvVol);
    }

    GSthreadSwitch();
    menuClose(fieldMenuType);

    // Calculate release fade timing
    vsyncRate = GSgfxVideoGetVsyncRate();
    timeBase = const_dbl;
    fadeTime = const_20 / ((float)vsyncRate - (float)timeBase);
    menuReleaseOffScreen();
    menuCloseSync(fieldMenuType, 1);
    GSgfxVideoSetLockFrameRate(1);
    heroMoveTermEvent();
    GSmodelAllUnpauseAnimation();
    floorFieldCameraUnpause();
    _openFieldMenu = 0;
    menuIntUnderTakerDispIconRestore2();

    return 0;
}

/*
  Address: 0x8005BFC4 | size: 0x8
  menuFieldIsOpen()
  Returns the _openFieldMenu flag.
*/
s32 menuFieldIsOpen(void) {
    return _openFieldMenu;
}
