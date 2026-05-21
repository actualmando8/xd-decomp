// Decompiled from: menuPdaSub.cpp
// Address range: 0x80052CBC..0x800531DC | size: 0x520

#include "global.h"

/* Forward declarations */
float   timeGetLastFrameSec(void);
s32     winSpriteGetLayerID(void* winSprite);
void*   GSgfxLayerFindByID(s32 id);
void*   menuItemBiosGetPtr(s32 category, void* biosPtr);
void    winSpriteSetDisp(void* winSprite, s32 disp);
void    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void* layer, void* vf);
void    beginSurface__10GSgfxLayerFUs(void* layer, u32 format);
void    endSurface__10GSgfxLayerFv(void* layer);
void*   GSgfxVFGetPredef(s32 predef);

/* Constants from .sdata2 */
static const float ALPHA_MAX = 255.0f;    // @2076
static const float ALPHA_INC_SPEED = 0.1f; // @2077
static const float ALPHA_DEC_SPEED = 0.2f; // @2078
static const float ALPHA_MIN = 0.0f;      // @2079
static const float POS_THRESHOLD = 30.0f;  // @2111
static const float POS_MAX = 100.0f;      // @2112
static const double SCROLL_BASE = 256.0;  // @2157

/*
  Address: 0x80052CBC | size: 0xD8
  Registers: r3=alphas, r4=count, r5=mode
  Calculates alpha fade for an array of floats based on elapsed time.
  For index == mode: increment towards ALPHA_MAX
  For index != mode: decrement towards ALPHA_MIN
*/
void menuPdaSubCalcAlpha(float* alphas, s32 count, s32 mode) {
    float dt = timeGetLastFrameSec();
    float scaled = ALPHA_MAX * dt;
    float incStep = scaled / ALPHA_INC_SPEED;
    float decStep = scaled / ALPHA_DEC_SPEED;

    for (s32 i = 0; i < count; i++) {
        if (i == mode) {
            if (alphas[i] < ALPHA_MAX) {
                alphas[i] += incStep;
                if (alphas[i] > ALPHA_MAX) {
                    alphas[i] = ALPHA_MAX;
                }
            }
        } else {
            if (alphas[i] > ALPHA_MIN) {
                alphas[i] -= decStep;
                if (alphas[i] < ALPHA_MIN) {
                    alphas[i] = ALPHA_MIN;
                }
            }
        }
    }
}

/*
  Address: 0x80052D94 | size: 0x3C
  Registers: r3=alphas, r4=count, r5=startIdx
  Initializes alpha array: entry at startIdx set to ALPHA_MAX, rest to ALPHA_MIN.
*/
void menuPdaSubInitAlpha(float* alphas, s32 count, s32 startIdx) {
    float maxVal = ALPHA_MAX;
    float minVal = ALPHA_MIN;
    
    for (s32 i = 0; i < count; i++) {
        if (i == startIdx) {
            alphas[i] = maxVal;
        } else {
            alphas[i] = minVal;
        }
    }
}

/*
  Address: 0x80052DD0 | size: 0xF4
  Registers: r3=pos, f1=target, f2=speed
  Calculates smooth position interpolation towards target.
  Clamps position changes based on threshold and speed.
*/
void menuPdaSubCalcPositon(float* pos, float target, float speed) {
    float current = *pos;
    float dt = timeGetLastFrameSec();
    float diff = target - current;
    float absDiff = (diff >= 0.0f) ? diff : -diff;
    float stepBase = speed * dt;
    float step = POS_THRESHOLD * stepBase;

    // If absDiff > POS_MAX, multiply step by POS_THRESHOLD
    if (absDiff > POS_MAX) {
        step = step * POS_THRESHOLD;
    }

    // Apply step in the direction of diff
    if (diff >= 0.0f) {
        *pos = current + step;
    } else {
        *pos = current - step;
    }

    // Clamp: if we overshot, set to target
    float remaining = target - *pos;
    float absRemaining = (remaining >= 0.0f) ? remaining : -remaining;
    float absStep = (step >= 0.0f) ? step : -step;

    if (absRemaining <= absStep) {
        *pos = target;
    }
}

/*
  Address: 0x80052EC4 | size: 0x264
  Registers: r3=winSprite, r4=menuItem, r5=index, r6=biosPtr, r7=min, r8=max, r9=flags, r10=unused
  Renders a scroll bar on the given window sprite layer.
  Handles position calculations and vertex rendering.
*/
void menuPdaSubScrollBar(
    void* winSprite,
    void* menuItem,
    s32 index,
    void* biosPtr,
    s32 min,
    s32 max,
    s32 flags
) {
    s32 layerId = winSpriteGetLayerID(winSprite);
    void* layer = GSgfxLayerFindByID(layerId);

    if (layer == NULL) {
        return;
    }

    // Set/clear bit 2 of byte offset 0x4 based on min > max
    if (min > max) {
        ((u8*)menuItem)[4] |= 0x2;
    } else {
        ((u8*)menuItem)[4] &= ~0x2;
        return;
    }

    void* bios = menuItemBiosGetPtr(index, biosPtr);

    s16 itemHeight = ((s16*)bios)[0xC / 2]; // offset 0xC
    s16 yBase = ((s16*)bios)[0];

    // Calculate Y positions as signed 16-bit using XOR with 0x8000
    s16 yMin = (s16)((u16)min ^ 0x8000);
    s16 yMax = (s16)((u16)max ^ 0x8000);
    
    // Convert min/max to double for floating point calculations
    double dMin = (double)yMin;
    double dMax = (double)yMax;
    
    // Calculate scroll ratio
    double scrollRange = dMax - dMin;
    double itemRange = (double)((s16)((u16)yBase ^ 0x8000) + max) - (double)((s16)((u16)yBase ^ 0x8000) + min);
    float ratio = (float)((dMax - SCROLL_BASE) - (dMin - SCROLL_BASE)) / (itemRange - SCROLL_BASE);
    
    // Calculate scroll bar positions
    float scrollPos1 = ratio * (float)(dMax - SCROLL_BASE);
    float scrollPos2 = ratio * (float)(dMin - SCROLL_BASE);
    
    // Set up rendering
    ((u32*)layer)[0x1644 / 4] = 1;
    ((u32*)layer)[0x1648 / 4] = 4;
    ((u32*)layer)[0x164C / 4] = 5;
    ((u32*)layer)[0x1650 / 4] = 0x80;
    
    // Set render flags
    ((u32*)layer)[0x170C / 4] |= 0x1;
    ((u32*)layer)[0x16A8 / 4] |= 0x40;
    ((u32*)layer)[0x17C4 / 4] |= 0x1;
    ((u32*)layer)[0x1760 / 4] |= 0x40;
    
    // Get vertex format and set render state
    void* vf = GSgfxVFGetPredef(0xA0);
    ((u32*)layer)[0x1998 / 4] = 0xA0;
    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vf);
    beginSurface__10GSgfxLayerFUs(layer, 0);
    
    // Render scroll bar vertices
    // ... (vertex buffer manipulation)
    
    endSurface__10GSgfxLayerFv(layer);
}
