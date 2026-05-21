// Decompiled from menuPdaSearcher.cpp (0x80041C3C - 0x80042CD0)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// File size: 0x1094 bytes | 13 functions

#include "system.h"

// ============================================================
// Forward declarations for external functions
// ============================================================
extern s32 _getWorldMapFlag__FUs(u16 index);
extern void _esaPrintMsg__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(void* win, void* spr, u32 msgId);
extern void _esaNumSet__FP14tagSPRITE_WORKUs(void* spr, u16 index);
extern void _animCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKUs(void* win, void* spr, u16 index);
extern void _animMojiCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKUs(void* win, void* spr, u16 index);
extern void winSpriteSetDisp(void* spr, u32 visible);
extern void* GSgfxLayerFindByID(u32 id);
extern void* menuSpriteBiosGetPtr(u32 spriteId);
extern void* menuSpriteBiosGetValPtr(u32 spriteId);
extern u32 winSpriteGetLayerID(void* win, void* spr);
extern void* GSresGetResourceAllGroup(u32 baseId);
extern u32 GStextureGetXsize(void* texture);
extern u32 GStextureGetYsize(void* texture);
extern void* GSgfxVFGetPredef(u32 index);
extern void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void* layer, void* vf);
extern void beginSurface__10GSgfxLayerFUs(void* layer, u16 format);
extern void endSurface__10GSgfxLayerFv(void* layer);
extern float GSlerpGetLinearInterpolationFloat(float start, float end, float t);
extern void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(
    void* layer, u8 func, u8 src, void* mtx, u8 param, void* mtx2);
extern void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(
    void* layer, u8 channel, u8 alpha, u8 src1, u8 src2, u32 param, void* light, u8 type,
    u8 diffuseFunc);
extern void menuItemBiosGetPtr(u32 itemId);
extern float cos(float x);
extern float sin(float x);

extern u16 esabaGetDigestRate(void);
extern u32 esabaGetPokemonID(u16 index);
extern u32 esabaGetEsaNum(u32 index);
extern void GSflagGet(u32 group, u32 id);
extern void GSmsgGetRect(u32 msgId, s16* x, s16* y);
extern void GSmsgPrintRect(void* win, void* spr, s16 x, s16 y, u32 msgId);
extern void menuOpen(u32 menuId, u32 param);
extern void menuClose(u32 menuId);
extern void menuCloseSync(u32 menuId, u32 sync);
extern void winSeqSetMenu(void* win, u32 menuId);
extern float timeGetLastFrameSec(void);
extern void* windowGetKeyInfo(void* win);

// ============================================================
// External data references
// ============================================================
// Global timer array
extern float _esaTimer[10];

// Meter index arrays - used for ESA number display
static const u32 _esaMeterIndex0[] = {
    0x198, 0x199, 0x19A, 0x19B, 0x19C, 0x19D, 0x19E, 0x19F, 0x1A0, 0x1A1
};
static const u32 _esaMeterIndex1[] = {
    0x1A2, 0x1A3, 0x1A4, 0x1A7, 0x1A5, 0x1A6, 0x1A8, 0x1A9, 0x1AA, 0x1AB
};
static const u32 _esaMeterIndex2[] = {
    0x1AC, 0x1AD, 0x1AE, 0x1AF, 0x1B0, 0x1B1, 0x1B2, 0x1B3, 0x1B4, 0x1B5
};
static const u32* const _esaMeterIndex[] = {
    _esaMeterIndex0, _esaMeterIndex1, _esaMeterIndex2
};

// sdata2 constants
static float const FLOAT_0 = 0.0f;
static float const FLOAT_1 = 1.0f;
static float const FLOAT_2 = 2.0f;
static float const FLOAT_6_283185 = 6.283185f;  // 2*PI
static float const FLOAT_3_141593 = 3.141593f;  // PI
static float const FLOAT_0_016 = 0.016f;
static float const FLOAT_0_05 = 0.05f;
static float const FLOAT_0_5 = 0.5f;
static float const FLOAT_0_003 = 0.003f;
static float const FLOAT_0_001 = 0.001f;
static float const FLOAT_0_0001 = 0.0001f;

// Global variables
extern u16 _maxscale;
extern s16 _startangle;
extern u32 esabadata_number;
extern u32 worldmapXD_data;

// Jump table for menuPdaSeatcherHook - dispatches to label handlers
// Based on the index value from sprite work
static const void* const hook_jump_table[] = {
    (void*)0x80041CA8, (void*)0x80041CA8, (void*)0x80041CA8, (void*)0x80041CA8,
    (void*)0x80041CA8, (void*)0x80041CA8, (void*)0x80041CA8, (void*)0x80041CA8,
    (void*)0x80041CA8, (void*)0x80041CA8, (void*)0x80041D70, (void*)0x80041D70,
    (void*)0x80041D70, (void*)0x80041D70, (void*)0x80041D70, (void*)0x80041D70,
    (void*)0x80041D70, (void*)0x80041D70, (void*)0x80041D70, (void*)0x80041D70,
    (void*)0x80041DA4, (void*)0x80041DA4, (void*)0x80041DA4, (void*)0x80041DA4,
    (void*)0x80041DA4, (void*)0x80041DA4, (void*)0x80041DA4, (void*)0x80041DA4,
    (void*)0x80041DA4, (void*)0x80041DA4, (void*)0x80041DD8, (void*)0x80041DD8,
    (void*)0x80041DD8, (void*)0x80041DD8, (void*)0x80041DD8, (void*)0x80041DD8,
    (void*)0x80041DD8, (void*)0x80041DD8, (void*)0x80041DD8, (void*)0x80041DD8,
    (void*)0x80041E0C, (void*)0x80041E0C, (void*)0x80041E0C, (void*)0x80041E0C,
    (void*)0x80041E0C, (void*)0x80041E0C, (void*)0x80041E0C, (void*)0x80041E0C,
    (void*)0x80041E0C, (void*)0x80041E0C, (void*)0x80041E64, (void*)0x80041E64,
    (void*)0x80041E64, (void*)0x80041E64, (void*)0x80041E64, (void*)0x80041E64,
    (void*)0x80041E64, (void*)0x80041E64, (void*)0x80041E64, (void*)0x80041E64,
    (void*)0x80041EBC, (void*)0x80041EBC, (void*)0x80041EBC, (void*)0x80041EBC,
    (void*)0x80041EBC, (void*)0x80041EBC, (void*)0x80041EBC, (void*)0x80041EBC,
    (void*)0x80041EBC, (void*)0x80041EBC, (void*)0x80041F14, (void*)0x80041F14,
    (void*)0x80041F14, (void*)0x80041F14, (void*)0x80041F14, (void*)0x80041F14,
    (void*)0x80041F14, (void*)0x80041F14, (void*)0x80041F14, (void*)0x80041F14,
    (void*)0x80041F6C, (void*)0x80041F6C, (void*)0x80041F6C, (void*)0x80041F6C,
    (void*)0x80041F6C, (void*)0x80041F6C, (void*)0x80041F6C, (void*)0x80041F6C,
    (void*)0x80041F6C, (void*)0x80041F6C, (void*)0x80041FC4, (void*)0x80041FC4,
    (void*)0x80041FC4, (void*)0x80041FC4, (void*)0x80041FC4, (void*)0x80041FC4,
    (void*)0x80041FC4, (void*)0x80041FC4, (void*)0x80041FC4, (void*)0x80041FC4,
};

// ============================================================
// Function implementations
// ============================================================

/*
 * menuPdaSeatcherHook
 * Original address: 0x80041C3C
 * Size: 0x428 bytes
 *
 * Hook function for the PDA searcher menu.
 * Dispatches to different handlers based on the index value from sprite work.
 * Each handler checks world map flags and displays appropriate messages.
 *
 * Register usage:
 *   r30 -> tagWINDOW_WORK*
 *   r31 -> tagSPRITE_WORK*
 */
s32 menuPdaSeatcherHook(void* win, void* spr) {
    s16 index;

    index = *(s16*)((u32)spr + 6);
    // Index range check: must be between 0x198 and 0x198 + 0x2D = 0x1C5
    if (index < 0x198 || index > 0x1C5) {
        return 0;
    }

    // Dispatch based on jump table
    // The jump table maps index values to different handlers
    // Each handler checks world map flags and displays messages
    switch (index) {
        case 0x198: case 0x199: case 0x19A: case 0x19B: case 0x19C:
        case 0x19D: case 0x19E: case 0x19F: case 0x1A0: case 0x1A1:
            if (_getWorldMapFlag__FUs(0)) {
                _esaPrintMsg__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(win, spr, 0x3C17);
            }
            break;
        case 0x1A2: case 0x1A3: case 0x1A4: case 0x1A7: case 0x1A5:
        case 0x1A6: case 0x1A8: case 0x1A9: case 0x1AA: case 0x1AB:
            if (_getWorldMapFlag__FUs(1)) {
                _esaPrintMsg__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(win, spr, 0x3C18);
            }
            break;
        case 0x1AC: case 0x1AD: case 0x1AE: case 0x1AF: case 0x1B0:
        case 0x1B1: case 0x1B2: case 0x1B3: case 0x1B4: case 0x1B5:
            if (_getWorldMapFlag__FUs(2)) {
                _esaPrintMsg__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(win, spr, 0x3C19);
            }
            break;
        // Additional cases for different index ranges...
        // The pattern continues with different flag checks and message IDs
    }

    return 0;
}

/*
 * _animMojiCursor
 * Original address: 0x80042064
 * Size: 0xB4 bytes
 *
 * Animates the text cursor using cosine-based oscillation.
 * Sets the alpha value at offset 0x67 of the sprite work.
 */
void _animMojiCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKUs(void* win, void* spr, u16 index) {
    float timer;
    float cosValue;
    float alpha;
    u8 baseAlpha;
    s32 scaledAlpha;

    timer = _esaTimer[index];
    cosValue = cos(timer);
    // Clamp cosValue to [0, 1] range
    if (cosValue < FLOAT_0) {
        cosValue = FLOAT_0;
    }
    // Scale to alpha range
    alpha = (FLOAT_1 - cosValue) * FLOAT_255;
    if (alpha < FLOAT_0) {
        alpha = FLOAT_0;
    }

    baseAlpha = *(u8*)((u32)win + 0x93);
    // Fixed-point multiplication: (baseAlpha * alpha) >> 7 with rounding
    scaledAlpha = (s32)((baseAlpha * (s32)alpha + 0x4000) >> 7);
    if (scaledAlpha < 0) scaledAlpha = 0;
    if (scaledAlpha > 255) scaledAlpha = 255;

    *(u8*)((u32)spr + 0x67) = (u8)scaledAlpha;
}

/*
 * _animCursor
 * Original address: 0x80042118
 * Size: 0x71C bytes
 *
 * Large animation function for cursor rendering.
 * Updates timer, calculates animation parameters, and renders cursor to GSgfxLayer.
 * Contains extensive GSgfxLayer configuration for texture generation and color units.
 *
 * Register usage:
 *   r27 -> tagWINDOW_WORK*
 *   r28 -> tagSPRITE_WORK*
 *   r25 -> index
 *   r29 -> GStexture*
 *   r30 -> GSgfxLayer*
 *   r26 -> texture height
 *   r25 -> texture width
 */
void _animCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKUs(void* win, void* spr, u16 index) {
    void* layer;
    void* texture;
    void* spriteBios;
    u32 texWidth, texHeight;
    u32 layerId;
    float timer;
    float cosValue;
    float alpha;
    u8 baseAlpha;
    s32 scaledAlpha;
    float scale;
    // Vertex data for cursor rendering
    float vertexData[4][3]; // 4 vertices, 3 components each (x, y, z)

    // Update timer
    _updateTimer__FUs(index);

    // Calculate animation parameters
    timer = _esaTimer[index];
    cosValue = cos((FLOAT_1 - timer / FLOAT_6_283185) * FLOAT_2);
    if (cosValue < FLOAT_0) {
        cosValue = FLOAT_0;
    }

    baseAlpha = *(u8*)((u32)win + 0x93);
    scaledAlpha = (s32)((baseAlpha * (s32)(cosValue * FLOAT_255) + 0x4000) >> 7);
    if (scaledAlpha < 0) scaledAlpha = 0;
    if (scaledAlpha > 255) scaledAlpha = 255;
    *(u8*)((u32)spr + 0x67) = (u8)scaledAlpha;

    // Get scale using linear interpolation
    scale = GSlerpGetLinearInterpolationFloat(_maxscale, *(float*)&_maxscale + 1, cosValue);

    // Get layer and sprite bios data
    layerId = winSpriteGetLayerID(win, spr);
    layer = GSgfxLayerFindByID(layerId);
    spriteBios = menuSpriteBiosGetPtr(0x2DE);
    menuSpriteBiosGetValPtr(0x2DE);

    // Get texture from resource
    texture = GSresGetResourceAllGroup(*(u32*)((u32)spriteBios + 8));
    texWidth = GStextureGetXsize(texture);
    texHeight = GStextureGetYsize(texture);

    // Calculate vertex positions based on sprite bios data
    // ... (complex vertex calculation using texture dimensions and sprite parameters)

    // Configure GSgfxLayer for rendering
    // Set texture generation function
    // ... (extensive layer configuration)

    // Begin surface rendering
    beginSurface__10GSgfxLayerFUs(layer, 4);

    // Render 4 vertices with calculated positions
    for (i = 0; i < 4; i++) {
        // Calculate vertex position using sin/cos of angle
        // Write vertex data to GS command buffer
    }

    endSurface__10GSgfxLayerFv(layer);
}

/*
 * _updateTimer
 * Original address: 0x80042834
 * Size: 0xAC bytes
 *
 * Updates the timer array with elapsed time.
 * Uses digest rate and frame time for animation timing.
 */
void _updateTimer__FUs(u16 index) {
    u16 digestRate;
    float elapsed;
    float lastTime;
    float newTimer;

    digestRate = esabaGetDigestRate();
    elapsed = *(float*)&digestRate - FLOAT_1;
    lastTime = _gettLastTime__Fv();
    newTimer = _esaTimer[index] + (FLOAT_0_016 * FLOAT_0_05 * cos(elapsed)) / lastTime;
    _esaTimer[index] = newTimer;
    // Wrap timer to [0, 2*PI] range
    if (_esaTimer[index] > FLOAT_6_283185) {
        _esaTimer[index] -= FLOAT_6_283185;
    }
}

/*
 * _esaPrintMsg
 * Original address: 0x800428E0
 * Size: 0x88 bytes
 *
 * Prints a message to the window/sprite with positioning.
 * Uses GSmsgGetRect to get message dimensions and centers the text.
 */
void _esaPrintMsg__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(void* win, void* spr, u32 msgId) {
    s16 rectX, rectY;
    s16 sprY;
    s16 offsetX;

    sprY = *(s16*)((u32)spr + 0x54);
    GSmsgGetRect(msgId, &rectX, &rectY);
    offsetX = (s16)((rectX - sprY) >> 1);

    GSmsgPrintRect(win, spr, offsetX, 0, msgId);
}

/*
 * _esaNumSet
 * Original address: 0x80042968
 * Size: 0x138 bytes
 *
 * Sets the ESA number display based on meter index.
 * Compares the current number against stored values to determine display state.
 */
void _esaNumSet__FP14tagSPRITE_WORKUs(void* spr, u16 index) {
    u32* meterTable;
    u32 currentNum;
    u32 i;
    u32 displayIndex;

    meterTable = (u32*)_esaMeterIndex[index & 0xFFFF];
    currentNum = esabaGetEsaNum(meterTable[0]);

    if (currentNum == 0) {
        winSpriteSetDisp(spr, 0);
        return;
    }

    // Compare against stored values
    displayIndex = 0xA; // Default to "unknown"
    for (i = 0; i < 10; i++) {
        if (currentNum == meterTable[i]) {
            displayIndex = i;
            break;
        }
    }

    // Set display based on comparison
    if (currentNum >= displayIndex + 1) {
        winSpriteSetDisp(spr, 1);
    } else {
        winSpriteSetDisp(spr, 0);
    }
}

/*
 * menuPdaSearcherCtrl
 * Original address: 0x80042AA0
 * Size: 0x9C bytes
 *
 * Controller for the PDA searcher menu.
 * Manages menu state transitions based on flags.
 */
s32 menuPdaSearcherCtrl(void* self) {
    s8 state;
    s8 subState;

    state = *(s8*)((u32)self + 1);
    subState = *(s8*)((u32)self + 2);

    if (state == 3) {
        if (subState == 0) {
            winSeqSetMenu(*(void**)((u32)self + 4), 0x136);
            *(u8*)((u32)self + 2) = 1;
        }
    } else if (state >= 0) {
        if (state == 0) {
            if (subState == 0) {
                winSeqSetMenu(*(void**)((u32)self + 4), 0x132);
                *(u8*)((u32)self + 2) = 1;
                _esaMonInit__Fv();
            }
        }
    }

    return 0;
}

/*
 * _getWorldMapFlag
 * Original address: 0x80042B3C
 * Size: 0x6C bytes
 *
 * Gets the world map flag for a given index.
 * Returns 1 if the flag is set, 0 otherwise.
 */
s32 _getWorldMapFlag__FUs(u16 index) {
    u32 group;
    u32 id;

    if (index > 2) {
        return 0;
    }

    // Get flag group and ID from world map data
    group = *(u32*)((u32)&index + 0x804EC960);
    id = *(u16*)((u32)&index + 0x804EC964);
    id = (id << index * 2) & 0xFFFF;

    return GSflagGet(worldmapXD_data, id + 4) ? 1 : 0;
}

/*
 * _esaMonInit
 * Original address: 0x80042BA8
 * Size: 0x34 bytes
 *
 * Initializes the ESA timer array with zero values.
 */
void _esaMonInit__Fv(void) {
    u32* timerPtr;
    u32 count;
    u32 i;

    timerPtr = (u32*)_esaTimer;
    count = *(u32*)esabadata_number;

    for (i = 0; i < count; i++) {
        *timerPtr++ = 0;
    }
}

/*
 * fn_80042BDC
 * Original address: 0x80042BDC
 * Size: 0x50 bytes
 *
 * Checks for key press and sets flags.
 */
void fn_80042BDC(void* self) {
    void* keyInfo;
    u16 keyState;

    if (self == 0) {
        return;
    }

    keyInfo = windowGetKeyInfo(self);
    keyState = *(u16*)((u32)keyInfo + 4);
    if (keyState & 0x4000000) { // B button pressed
        *(u8*)((u32)self + 0xA4) = 1;
        *(u8*)((u32)self + 0xA5) = 1;
    }
}

/*
 * menuPdaSearcher
 * Original address: 0x80042C2C
 * Size: 0x4C bytes
 *
 * Main entry point for the PDA searcher menu.
 * Opens menus and handles the return flow.
 */
void menuPdaSearcher(void) {
    s32 result;

    menuOpen(0x77, 0);

    do {
        result = menuOpen(0x6D, 1);
    } while (result >= 0);

    _menuClose__Fl(0x6D);
    _menuClose__Fl(0x77);
}

/*
 * _menuClose
 * Original address: 0x80042C78
 * Size: 0x38 bytes
 *
 * Closes a menu with synchronization.
 */
void _menuClose__Fl(s32 menuId) {
    menuClose(menuId);
    menuCloseSync(menuId, 1);
}

/*
 * _gettLastTime
 * Original address: 0x80042CB0
 * Size: 0x20 bytes
 *
 * Wrapper for timeGetLastFrameSec.
 */
float _gettLastTime__Fv(void) {
    return timeGetLastFrameSec();
}
