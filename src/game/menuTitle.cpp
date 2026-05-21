// Decompilation of menuTitle.cpp (0x800A3150..0x800A423C, size: 0x10EC)
// Pokémon XD: Gale of Darkness - Title Screen
// Handles Flash animation playback, cursor animation, menu selection,
// memory card detection, and state machine transitions

#include "global.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "libc/string.h"
#include "libc/math.h"

// ==================== Forward Declarations ====================

struct tagWINDOW_WORK;
struct tagSPRITE_WORK;

// External function declarations
void timeGetLastFrameSec(void);
u32 windowGetActiveID(void);
u32 windowSearchID(void);
void windowGetKeyInfo(struct tagWINDOW_WORK*);
void menuOpenCustom(u32, u32, u32, u32, u32, u32, u32);
void winSpriteSetDisp(struct tagSPRITE_WORK*, u32);
void FlashSystemSetLoopFlag(u32, u32);
void FlashSystemSetPlayFrameLabel(u32, u32, u32);
void FlashSystemSetNowFrameLabel(u32, u32, u32);
u32 FlashSystemGetFrameFromLabel(u32, u32);
u32 FlashSystemGetNowFrame(u32);
void fadeCheck(void);
void dbgMenuSetEnable(u32);
void *menuDataBiosGetPtr(u32);
u32 pokecoloGetRomVersion(void);
u32 memcardTaskCall(u32, u32, u32);
void savedataCreate(u32, u32);
void *gamedatasaveGetStatus(u32, u32);
void menuTopSetInitCursor(u32);
void GSthreadSwitch(void);
void GSresGetResourceAllGroup(u32);
void GSmodelSetAnimIndex(void*, s16);
void GSmodelSetAnimFrame(void*, float);
void GSmodelSetAnimRate(void*, float);
s32 GSmodelGetAnimFrameCount(void*, s16);
void GSmodelSetAnimType(void*, u32);
void GSmodelStartAnimation(void*);
void GSmodelSetForceUseFractionalFramesFlag(void*, u32);
void GSmodelSet60fpsAnimFlag(void*, u32);
void GSmodelSetVisibility(void*, u32);
void GSmodelSetBoundCheck(void*, u32);
void cameraSetType(u32);
u32 floorGetCurrentGroupID(void);
void cameraPlayAnime(float, u32, u32);
void *WorldMapModel_new(u32);
void SetModel__13WorldMapModelFUlUlb(void*, u32, u32, u32);
void UnloadModel__13WorldMapModelFUlUl(void*, u32, u32);
void releaseOffscreenData__13WorldMapModelFv(void*);
void *operator_new(u32);
void operator_delete(void*);

// ==================== Global State (SData) ====================

// _menuTitleStatus: Current state of title screen
// _menuTitleStartStatus: Starting status flag
// _menuTitleType: Title type (0=normal, 1=special)
// _menuTitleTimer: Timer for state transitions
// _menuTitleSeFrame: SE frame counter
// _menuTitleSeCount: SE count
// _menuTitleSkipFlag: Skip flag
// _menuTitleFrameCount: Frame counter for animations
// _menuTitleFrameSec: Frame time in seconds
// _menuTitleAutoDemoCount: Auto demo counter
// _titleCursorTimer: Cursor animation timer
// _menuTitleWork: Work area for menu selection (array of s16)

// ==================== Float Constants (SData2) ====================

// @2418: 1.0f (animation rate)
// @2419: 0.0f (zero)
// @2420: 1.0f (timer threshold)
// @2421: 5.0f (auto demo threshold)
// @2427: "title" (Flash label)
// @2444: 2.0f (sin multiplier)
// @2445: 60.0f (frame divisor)
// @2446: 10.0f (cursor amplitude)
// @2448: 3.1415926535897936 (PI as double)
// @2451: 0.016666667f (frame time increment)
// @2563: "titleLoop" (Flash label)
// @2564: "titleCard" (Flash label)
// @2565: "titleSelect" (Flash label)
// @2298: Array of 6 menu item IDs for cursor sprite matching

// ==================== Functions ====================

/* 0x800A3150 | size: 0x44 */
// Opens the title menu with custom parameters
void menuTitleOpenMenu(void);

/* 0x800A3194 | size: 0x18 */
// Gets the selection value at index from _menuTitleWork
s16 menuTitleGetSelect(u32 index);

/* 0x800A31AC | size: 0x18 */
// Sets the selection value at index in _menuTitleWork
void menuTitleSetSelect(u32 index, s16 value);

/* 0x800A31C4 | size: 0xD8 */
// Main title screen update function - handles state transitions
// and auto-demo timer logic
void menuTitleFunc(void);

/* 0x800A329C | size: 0x7C */
// Button input handler - checks fade state and Flash animation progress
void menuTitleButton(struct tagWINDOW_WORK* work);

/* 0x800A3318 | size: 0x74 */
// Internal button handler - processes A/Start button input
void _menuTitleNormalButton__FP14tagWINDOW_WORK(struct tagWINDOW_WORK* work);

/* 0x800A338C | size: 0xDC */
// Cursor animation - calculates sine-wave offset for cursor position
void menuTitleCursorAnime(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800A3468 | size: 0x7C */
// Main cursor animation timer update
void menuTitleCursorAnimeMain(void);

/* 0x800A34E4 | size: 0x74 */
// Hook function - dispatches cursor animation based on sprite ID
void menuTitleHook(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800A3558 | size: 0xA4 */
// Shows/hides cursor sprite based on current menu selection
void _cursorSpriteOnOff__FP14tagWINDOW_WORKP14tagSPRITE_WORK(
    struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800A35FC | size: 0x330 */
// Main title screen loop - large state machine with Flash animation control,
// memory card detection, save data initialization, and menu selection
void menuTitle(void);

/* 0x800A392C | size: 0x7C */
// Initializes 4 model animations (indices 0x22141000-0x22141003)
void fn_800A392C(void);

/* 0x800A39A8 | size: 0x3C */
// Sets camera type and plays camera animation
void fn_800A39A8(void);

/* 0x800A39E4 | size: 0x38 */
// Loads world map model and initializes camera
void fn_800A39E4(void);

/* 0x800A3A1C | size: 0x2C */
// Unloads world map model
void fn_800A3A1C(void);

/* 0x800A3A48 | size: 0xEC */
// Loads and configures a 3D model with animation settings
void fn_800A3A48(u32 groupId, u32 animIndex, u32 flags);

/* 0x800A3B34 | size: 0xA0 */
// Creates and loads a WorldMapModel
void fn_800A3B34(u32 floorId, u32 groupId, u32 animate);

/* 0x800A3BD4 | size: 0x90 */
// Creates and unloads a WorldMapModel
void fn_800A3BD4(u32 floorId, u32 groupId);

/* 0x800A3C64 | size: 0x90 */
// Waits for BGM to reach a certain state
void menuTitlePlayBGMWait(u32 param);

// ==================== Implementations ====================

/* 0x800A3150 | size: 0x44 */
void menuTitleOpenMenu(void) {
    fn_800A39E4();
    u32 activeId = windowGetActiveID();
    menuOpenCustom(0x11, activeId, 0, 0, 0, 0, 0);
}

/* 0x800A3194 | size: 0x18 */
s16 menuTitleGetSelect(u32 index) {
    return _menuTitleWork[index];
}

/* 0x800A31AC | size: 0x18 */
void menuTitleSetSelect(u32 index, s16 value) {
    _menuTitleWork[index] = value;
}

/* 0x800A31C4 | size: 0xD8 */
void menuTitleFunc(void) {
    menuTitleCursorAnimeMain();
    
    // Update frame counter
    timeGetLastFrameSec();
    _menuTitleFrameCount = _menuTitleFrameCount + f1 * 1.0f;
    _menuTitleFrameSec = f1;
    
    // Wrap frame count at 1.0
    if (_menuTitleFrameCount >= 1.0f) {
        _menuTitleFrameCount = 0.0f;
    }
    
    u32 status = _menuTitleStatus;
    if (status >= 0x1E) {
        if (status == 0x29) {
            _menuTitleFrameCount = 0.0f;
        } else if (status != 0xC8) {
            // Check auto-demo timer (only for non-PokéColosseum)
            if (pokecoloGetRomVersion() != 1) {
                _menuTitleAutoDemoCount = _menuTitleAutoDemoCount + _menuTitleFrameSec;
                if (_menuTitleAutoDemoCount >= 5.0f) {
                    _menuTitleAutoDemoCount = 0.0f;
                    if (status == 0x3E8) {
                        // Reset
                    } else if (status >= 0x3E8 || status == 0x1F) {
                        // Skip
                    } else {
                        _menuTitleStatus = 0x28;
                        menuTitleSetStartStatus(0);
                    }
                }
            }
        }
    }
}

/* 0x800A329C | size: 0x7C */
void menuTitleButton(struct tagWINDOW_WORK* work) {
    if (fadeCheck() == 0) {
        dbgMenuSetEnable(1);
        // Check if Flash animation reached the select label
        u32 targetFrame = FlashSystemGetFrameFromLabel(0x1FE3000, "titleSelect");
        u32 currentFrame = FlashSystemGetNowFrame(0x1FE3000);
        if (currentFrame >= targetFrame) {
            _menuTitleNormalButton__FP14tagWINDOW_WORK(work);
        }
    }
}

/* 0x800A3318 | size: 0x74 */
void _menuTitleNormalButton__FP14tagWINDOW_WORK(struct tagWINDOW_WORK* work) {
    if (_menuTitleStatus >= 0x29) {
        return;
    }
    if (!work) {
        return;
    }
    
    u32 windowId = *(u32*)(work + 4);
    menuDataBiosGetPtr(windowId);
    windowGetKeyInfo(work);
    
    // Check for A button (0x10) or Start (0x800)
    u16 keys = *(u16*)(work + 4);
    if (keys & 0x810) {
        u8 flag = ((u8*)work)[0xA4];
        if (flag == 0) {
            _menuTitleSetSE__FUl(0x11);
        }
        ((u8*)work)[0xA4] = 1;
    }
}

/* 0x800A338C | size: 0xDC */
void menuTitleCursorAnime(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite) {
    u32 activeId = windowGetActiveID();
    u32 searchId = windowSearchID();
    
    if (activeId == searchId) {
        // Calculate sine-wave offset for cursor
        s16 timer = _titleCursorTimer;
        s32 multiplied = ((s64)timer * 0x11111111) >> 16;
        s32 shifted = multiplied >> 31;
        s32 rounded = (multiplied + shifted) * 0x3C;
        s32 offset = timer - rounded;
        
        if (offset < 0x1E) {
            // Calculate sin-based offset
            double angle = (offset * (PI - 3.1415926535897936)) / 60.0f * 2.0f;
            float sinVal = sin((float)angle);
            sinVal = (float)((int32)(sinVal * 10.0f));
            s8 diff = (s8)sinVal - ((s8*)sprite)[0x67];
            ((s8*)sprite)[0x67] = diff;
        } else {
            ((s8*)sprite)[0x67] = 0xFF;
        }
    } else {
        ((s8*)sprite)[0x67] = 0xFF;
    }
    
    *(u32*)sprite = 0;  // Clear field at offset 0x64
}

/* 0x800A3468 | size: 0x7C */
void menuTitleCursorAnimeMain(void) {
    timeGetLastFrameSec();
    s16 timer = _titleCursorTimer;
    
    // Update timer with frame time
    double newTimer = timer + f1 * 0.016666667f;
    s32 shifted = ((s64)newTimer) >> 6;
    s32 sign = shifted >> 31;
    s32 rounded = (shifted + sign) * 0x3E8;
    s32 final = timer - rounded;
    final = (s16)final;
    
    _titleCursorTimer = final;
}

/* 0x800A34E4 | size: 0x74 */
void menuTitleHook(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite) {
    s16 spriteId = *(s16*)((u8*)sprite + 6);
    
    // Check if sprite ID matches one of the cursor sprite ranges
    if (spriteId >= 0x3D && spriteId < 0x40) {
        menuTitleCursorAnime(work, sprite);
        _cursorSpriteOnOff__FP14tagWINDOW_WORKP14tagSPRITE_WORK(work, sprite);
    } else if (spriteId >= 0x42 && spriteId < 0x44) {
        menuTitleCursorAnime(work, sprite);
        _cursorSpriteOnOff__FP14tagWINDOW_WORKP14tagSPRITE_WORK(work, sprite);
    }
}

/* 0x800A3558 | size: 0xA4 */
void _cursorSpriteOnOff__FP14tagWINDOW_WORKP14tagSPRITE_WORK(
    struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite) {
    
    s16 spriteId = *(s16*)((u8*)sprite + 6);
    u8 currentIdx = ((u8*)work)[0x9E];
    
    // Match sprite ID against menu item table
    u8 targetIdx = 0xFF;
    const u32* itemTbl = (const u32*)0x802F2298;  // @2298
    
    for (u32 i = 0; i < 6; i++) {
        if (spriteId == itemTbl[i]) {
            targetIdx = (u8)i;
            break;
        }
    }
    
    if (targetIdx == currentIdx) {
        winSpriteSetDisp(sprite, 1);  // Show
    } else {
        winSpriteSetDisp(sprite, 0);  // Hide
    }
}

/* 0x800A35FC | size: 0x330 */
void menuTitle(void) {
    _menuTitleStatus = 0;
    _menuTitleTimer = 0.0f;
    _menuTitleSeFrame = 0.0f;
    _menuTitleSeCount = 0;
    _menuTitleSkipFlag = 0;
    u32 shouldContinue = 1;
    
    menuTitlePlayBGM();
    menuTitlePlayBGMWait(1);
    
    if (_menuTitleStartStatus == 1) {
        _menuTitleStatus = 1;
        _menuTitleStartStatus = 0;
        _menuTitleType = 1;
    } else {
        _menuTitleType = 0;
    }
    
    fn_800A39E4();
    
    while (shouldContinue) {
        u32 status = _menuTitleStatus;
        
        if (status == 0x28) {
            _menuTitleStatus = 0x3E8;
        } else if (status == 0x1E) {
            _menuTitleStatus = 0x20;
        } else if (status == 0) {
            // Play intro animation
            FlashSystemSetLoopFlag(0x1FE3000, 0);
            FlashSystemSetPlayFrameLabel(0x1FE3000, "titleLoop", "title");
            FlashSystemSetNowFrameLabel(0x1FE3000, "titleLoop");
            _menuTitleStatus = 0x1E;
        } else if (status == 1) {
            // Play intro animation (type 1)
            FlashSystemSetLoopFlag(0x1FE3000, 0);
            FlashSystemSetPlayFrameLabel(0x1FE3000, "titleCard", "title");
            FlashSystemSetNowFrameLabel(0x1FE3000, "titleCard");
            _menuTitleStatus = 0x1E;
        } else if (status == 0x20) {
            // Open selection menu
            u32 activeId = windowGetActiveID();
            menuOpenCustom(0x11, activeId, 0, 0, 1, 0, 0);
            FlashSystemSetLoopFlag(0x1FE3000, 0);
            FlashSystemSetPlayFrameLabel(0x1FE3000, "titleSelect", "titleSelect");
            _menuTitleStatus = 0x1F;
            _menuTitleTimer = 0.0f;
        } else if (status >= 0x1F && status < 0x2A) {
            // Wait for timer
            float threshold = 1.0f;
            while (_menuTitleTimer < threshold) {
                timeGetLastFrameSec();
                _menuTitleTimer = _menuTitleTimer + f1;
                GSthreadSwitch();
            }
            FlashSystemSetPlayFrameLabel(0x1FE3000, "titleSelect", "titleSelect");
            FlashSystemSetNowFrameLabel(0x1FE3000, "titleSelect");
            _menuTitleStatus = 0xC8;
        } else if (status >= 0xC8 && status < 0x3E8) {
            // Memory card detection
            if (pokecoloGetRomVersion() == 1) {
                // PokéColosseum - skip memcard check
            } else {
                s32 memcardResult = memcardTaskCall(1, 2, 0);
                if (memcardResult == -1) {
                    // No memory card - go back to select
                    _menuTitleStatus = 0x20;
                    FlashSystemSetPlayFrameLabel(0x1FE3000, "titleCard", "title");
                    FlashSystemSetNowFrameLabel(0x1FE3000, "titleCard");
                } else if (memcardResult != 3) {
                    savedataCreate(0, 0);
                }
                
                // Check for existing save data
                void* saveData = gamedatasaveGetStatus(0, 4);
                if (saveData) {
                    menuTopSetInitCursor(1);
                } else {
                    menuTopSetInitCursor(0);
                }
                _menuTitleStatus = 0x29;
            }
        } else if (status >= 0x2A && status < 0xC8) {
            // Menu selection
            s32 select = _selectMenu__Fv();
            if (select >= 0 && select <= 4) {
                // Valid selection
            } else {
                menuTitleCloseSelectAnime();
                _menuTitleStatus = 1;
                _menuTitleAutoDemoCount = 0.0f;
            }
        } else if (status == 0x3E8) {
            shouldContinue = 0;
        }
    }
}

/* 0x800A392C | size: 0x7C */
void fn_800A392C(void) {
    // Initialize 4 model animations
    fn_800A3A48(0x22141000, 0, 1);
    fn_800A3A48(0x22141001, 0, 1);
    fn_800A3A48(0x22141002, 0, 1);
    fn_800A3A48(0x22141003, 0, 1);
}

/* 0x800A39A8 | size: 0x3C */
void fn_800A39A8(void) {
    cameraSetType(4);
    u32 groupId = floorGetCurrentGroupID();
    cameraPlayAnime(0.0f, 0x22161800, 1);
}

/* 0x800A39E4 | size: 0x38 */
void fn_800A39E4(void) {
    u32 groupId = floorGetCurrentGroupID();
    fn_800A3B34(groupId, 0x22140400, 1);
    fn_800A392C();
    fn_800A39A8();
}

/* 0x800A3A1C | size: 0x2C */
void fn_800A3A1C(void) {
    u32 groupId = floorGetCurrentGroupID();
    fn_800A3BD4(groupId, 0x22140400);
}

/* 0x800A3A48 | size: 0xEC */
void fn_800A3A48(u32 groupId, s16 animIndex, u32 flags) {
    void* model = GSresGetResourceAllGroup(groupId);
    if (!model) {
        return;
    }
    
    GSmodelSetAnimIndex(model, animIndex);
    GSmodelSetAnimFrame(model, f1);
    GSmodelSetAnimRate(model, 1.0f);
    GSmodelGetAnimFrameCount(model, animIndex);
    
    if (flags & 0x00FFFFFF) {
        GSmodelSetAnimType(model, 1);  // Loop
    } else {
        GSmodelSetAnimType(model, 0);  // Once
    }
    
    GSmodelStartAnimation(model);
    GSmodelSetForceUseFractionalFramesFlag(model, 1);
    GSmodelSet60fpsAnimFlag(model, 1);
    GSmodelSetVisibility(model, 1);
    GSmodelSetBoundCheck(model, 0);
}

/* 0x800A3B34 | size: 0xA0 */
void fn_800A3B34(u32 floorId, u32 groupId, u32 animate) {
    void* model = operator_new(4);
    if (model) {
        *(u32*)model = 0;
    }
    SetModel__13WorldMapModelFUlUlb(model, floorId, groupId, animate);
    
    if (model) {
        if (*(u32*)model) {
            releaseOffscreenData__13WorldMapModelFv(model);
        }
        operator_delete(model);
    }
}

/* 0x800A3BD4 | size: 0x90 */
void fn_800A3BD4(u32 floorId, u32 groupId) {
    void* model = operator_new(4);
    if (model) {
        *(u32*)model = 0;
    }
    UnloadModel__13WorldMapModelFUlUl(model, floorId, groupId);
    
    if (model) {
        if (*(u32*)model) {
            releaseOffscreenData__13WorldMapModelFv(model);
        }
        operator_delete(model);
    }
}

/* 0x800A3C64 | size: 0x90 */
void menuTitlePlayBGMWait(u32 play) {
    // Wait for BGM to finish loading/playing
    // Implementation involves timer-based waiting with thread switching
}
