// Decompilation of menuInterrupt.cpp
// Original address: 0x800665F4..0x80066C48 | size: 0x654
// Functions: 12

#include "global.h"

// Forward declarations
void menuIsCheck(void);
void menuClose(int menuId);
void menuCloseSync(int menuId, int sync);
void menuOpenCustom(int menuId, int param4, int param5, int param6, int param7, int param8, int param9);
int winSpriteGetLayerID(void* spriteWork);
void* GSgfxLayerFindByID(int id);
void* GSfloorGetCurrent(void);
void* floorDataBiosGetPtr(void);
int floorDataBiosGetFloorKind(void);
int GSflagTest(int flagId);
void winSpriteSetDisp(void* spriteWork, int disp);
void winSeqSetMenu(int seqId, int menuId);
int winSeqCheckMove(int seqId);
void menuButtonNormal(void* windowWork);
void GSsndPlayNow(int soundId);
void* gamedatasaveGetStatus(int param1, int param2);
void GSinputMotorStart(int param1, int param2, int param3, int param4, int param5);
float timeGetLastFrameSec(void);
float cos(float x);

// Global variables (from .sda21 references)
extern u8 _menuIntVibFlag;
extern u8 _underTakerIconFlag;
extern float _menuIntFrameCount;
extern float _menuIntFrameCount2;
extern void* undertakerdata;

// Floating point constants
static const float @2178 = 6.2831855f;   // 2*PI
static const float @2179 = 3.1415927f;   // PI
static const float @2180 = 127.5f;
static const float @2181 = 1.0f;
static const float @2182 = 2.0f;

/* 0x800665F4 | size: 0x5C */
// Opens icon menu 0xC1 if not already open
void menuIntUnderTakerOpenIcon(void)
{
    if (menuIsCheck()) {
        menuClose(0xc1);
    } else {
        menuOpenCustom(0xc1, 0x0, 0x0, 0x0, 0x1, 0x0, 0);
    }
}

/* 0x80066650 | size: 0x44 */
// Closes icon menu 0xC1 with sync
void menuIntUnderTakerMenuClose(void)
{
    if (menuIsCheck()) {
        menuClose(0xc1);
        menuCloseSync(0xc1, 0x1);
    }
}

/* 0x80066694 | size: 0x44 */
// Opens icon menu 0xC1 and sets vibration flag
void menuIntUnderTakerMenuOpen(void)
{
    _menuIntVibFlag = 0x1;
    menuOpenCustom(0xc1, 0x0, 0x0, 0x0, 0x1, 0x0, 0);
}

/* 0x800666D8 | size: 0xC */
// Restores UnderTaker icon display flag
void menuIntUnderTakerDispIconRestore2(void)
{
    _underTakerIconFlag = 0x1;
}

/* 0x800666E4 | size: 0xC */
// Turns off UnderTaker icon display flag
void menuIntUnderTakerDispIconOff2(void)
{
    _underTakerIconFlag = 0x0;
}

/* 0x800666F0 | size: 0xC8 */
// Hook function for UnderTaker icon display
// r3 = windowWork, r4 = spriteWork
void menuIntUnderTakerHook(void* windowWork, void* spriteWork)
{
    winSpriteGetLayerID();
    GSgfxLayerFindByID(0);
    GSfloorGetCurrent();
    floorDataBiosGetPtr();
    int floorKind = floorDataBiosGetFloorKind();
    
    if (_underTakerIconFlag) {
        if (GSflagTest(0x24 + *(int*)((u32)undertakerdata + 0x24))) {
            if (floorKind == 0x1) {
                winSpriteSetDisp(spriteWork, 0x1);
                if (*(s16*)((u32)spriteWork + 0x6) == 0x65c) {
                    if (*(s8*)((u32)windowWork + 0x1)) {
                        *(u8*)((u32)spriteWork + 0x67) = _menuIntGetAlpha2();
                    }
                }
                return;
            }
        }
    }
    winSpriteSetDisp(spriteWork, 0x0);
}

/* 0x800667B8 | size: 0x98 */
// Calculates alpha value for UnderTaker icon animation
// Uses cosine wave for fade effect
u8 _menuIntGetAlpha2(void)
{
    float frameCount = _menuIntFrameCount2;
    float value = (frameCount * @2178) / @2179;
    float cosResult = cos(value);
    int alpha = (int)((@2181 + cosResult) * @2182 * @2180);
    
    if (alpha > 0xff) alpha = 0xff;
    if (alpha < 0x32) alpha = 0x32;
    
    _menuIntFrameCount2 = frameCount + timeGetLastFrameSec();
    return (u8)alpha;
}

/* 0x80066850 | size: 0xB8 */
// Main control for UnderTaker interrupt menu
// r3 = windowWork
void menuIntUnderTakerMainCtrl(void* windowWork)
{
    s8 state = *(s8*)((u32)windowWork + 0x1);
    u8 flag = *(u8*)((u32)windowWork + 0x2);
    int seqId = *(int*)((u32)windowWork + 0x4);
    
    if (state == 0x0) {
        GSsndPlayNow(0x5b4);
        if (_menuIntVibFlag) {
            _menuIntVibSet();
        }
        if (!flag) {
            winSeqSetMenu(seqId, 0x171);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
        _menuIntVibFlag = 0x1;
    } else if (state == 0x3) {
        if (!flag) {
            winSeqSetMenu(seqId, 0x177);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
    }
}

/* 0x80066908 | size: 0x128 */
// Hook function for interrupt menu
// r3 = windowWork, r4 = spriteWork
void menuIntHook(void* windowWork, void* spriteWork)
{
    s16 spriteId = *(s16*)((u32)spriteWork + 0x6);
    int* ptr = (int*)((u32)windowWork + 0x68);
    int value = *ptr;
    
    if (spriteId == 0x4be) {
        if (value) {
            winSpriteSetDisp(spriteWork, 0x0);
        } else {
            winSpriteSetDisp(spriteWork, 0x1);
            if (*(s8*)((u32)windowWork + 0x1)) {
                *(u8*)((u32)spriteWork + 0x67) = _menuIntGetAlpha();
            }
        }
    } else if (spriteId == 0x505) {
        if (value == 0x1) {
            winSpriteSetDisp(spriteWork, 0x1);
            if (*(s8*)((u32)windowWork + 0x1)) {
                *(u8*)((u32)spriteWork + 0x67) = _menuIntGetAlpha();
            }
        } else {
            winSpriteSetDisp(spriteWork, 0x0);
        }
    } else if (spriteId >= 0x507 && spriteId < 0x505) {
        if (value == 0x2) {
            winSpriteSetDisp(spriteWork, 0x1);
            if (*(s8*)((u32)windowWork + 0x1)) {
                *(u8*)((u32)spriteWork + 0x67) = _menuIntGetAlpha();
            }
        } else {
            winSpriteSetDisp(spriteWork, 0x0);
        }
    }
}

/* 0x80066A30 | size: 0x98 */
// Calculates alpha value for interrupt menu animation
// Uses cosine wave for fade effect
u8 _menuIntGetAlpha(void)
{
    float frameCount = _menuIntFrameCount;
    float value = (frameCount * @2178) / @2179;
    float cosResult = cos(value);
    int alpha = (int)((@2181 + cosResult) * @2182 * @2180);
    
    if (alpha > 0xff) alpha = 0xff;
    if (alpha < 0x32) alpha = 0x32;
    
    _menuIntFrameCount = frameCount + timeGetLastFrameSec();
    return (u8)alpha;
}

/* 0x80066AC8 | size: 0x44 */
// Button handler for interrupt menu
// r3 = windowWork
void menuIntButton(void* windowWork)
{
    int seqId = *(int*)((u32)windowWork + 0x4);
    if (!winSeqCheckMove(seqId)) {
        menuButtonNormal(windowWork);
    }
}

/* 0x80066B0C | size: 0xF4 */
// Main control for interrupt menu
// r3 = windowWork
void menuIntMainCtrl(void* windowWork)
{
    s8 state = *(s8*)((u32)windowWork + 0x1);
    int* ptr = (int*)((u32)windowWork + 0x68);
    u8 flag = *(u8*)((u32)windowWork + 0x2);
    int seqId = *(int*)((u32)windowWork + 0x4);
    int value = *ptr;
    
    if (state == 0x0) {
        _menuIntVibSet();
        int soundId = 0x0;
        if (value == 0x1) {
            soundId = 0x564;
        } else if (value == 0x0) {
            soundId = 0x566;
        } else if (value >= 0x1 && value < 0x3) {
            soundId = 0x565;
        }
        if (soundId) {
            GSsndPlayNow(soundId);
        }
        if (!flag) {
            winSeqSetMenu(seqId, 0x171);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
    } else if (state == 0x3) {
        if (!flag) {
            winSeqSetMenu(seqId, 0x177);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
    }
}

/* 0x80066C00 | size: 0x48 */
// Sets vibration if save status allows
void _menuIntVibSet(void)
{
    if (!gamedatasaveGetStatus(0x0, 0x9)) {
        GSinputMotorStart(0x1, 0x0, 0xff, 0x1e, 0x0);
    }
}
