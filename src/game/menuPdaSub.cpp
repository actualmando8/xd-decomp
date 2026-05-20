// Decompiled from: menuPdaSub.cpp
// Address range: 0x80052CBC..0x800531DC | size: 0x520

/* Forward declarations */
s32     timeGetLastFrameSec(void);
s32     winSpriteGetLayerID(void* winSprite);
void*   GSgfxLayerFindByID(s32 id);
void*   menuItemBiosGetPtr(s32 a, s32 b);
void    menuSubAnimAlpha(void* a, s32 b, s32 c, s32 d, s32 e);
void    winSpriteSetDisp(void* winSprite, s32 disp);
void    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void* layer, void* vf);
void    beginSurface__10GSgfxLayerFUs(void* layer, u32 format);
void    endSurface__10GSgfxLayerFv(void* layer);
void*   GSgfxVFGetPredef(s32 predef);

/* Constants */
static const float ALPHA_MAX = 255.0f;
static const float ALPHA_INC_SPEED = 0.1f;
static const float ALPHA_DEC_SPEED = 0.2f;
static const float ALPHA_MIN = 0.0f;
static const float POS_THRESHOLD = 30.0f;
static const float POS_MAX = 100.0f;
static const double SCROLL_BASE = 1.0;

/*
  Address: 0x80052CBC | size: 0xD8
  menuPdaSubCalcAlpha(float* alphas, s32 count, s32 mode)
  Calculates alpha fade for an array of floats.
  mode == 0: increment towards ALPHA_MAX
  mode != 0: decrement towards ALPHA_MIN
  Uses last frame time for smooth animation.
*/
void menuPdaSubCalcAlpha(float* alphas, s32 count, s32 mode) {
    float dt = timeGetLastFrameSec();
    float incStep = dt * (mode == 0 ? ALPHA_INC_SPEED : ALPHA_INC_SPEED);
    float decStep = dt * ALPHA_DEC_SPEED;
    
    for (s32 i = 0; i < count; i++) {
        if (mode == 0) {
            // Increment towards ALPHA_MAX
            if (alphas[i] < ALPHA_MAX) {
                alphas[i] += incStep;
                if (alphas[i] > ALPHA_MAX) {
                    alphas[i] = ALPHA_MAX;
                }
            }
        } else {
            // Decrement towards ALPHA_MIN
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
  menuPdaSubInitAlpha(float* alphas, s32 count, s32 startIdx)
  Initializes alpha array: entries before startIdx set to ALPHA_MAX, rest to ALPHA_MIN.
*/
void menuPdaSubInitAlpha(float* alphas, s32 count, s32 startIdx) {
    for (s32 i = 0; i < count; i++) {
        if (i == startIdx) {
            alphas[i] = ALPHA_MAX;
        } else {
            alphas[i] = ALPHA_MIN;
        }
    }
}

/*
  Address: 0x80052DD0 | size: 0xF4
  menuPdaSubCalcPositon(float* pos, float target, float speed)
  Calculates smooth position interpolation towards target.
  Clamps position changes based on threshold and speed.
*/
void menuPdaSubCalcPositon(float* pos, float target, float speed) {
    float current = *pos;
    float dt = timeGetLastFrameSec();
    float diff = target - current;
    float absDiff = (diff >= 0.0f) ? diff : -diff;
    float step = speed * dt;
    
    if (absDiff > POS_MAX) {
        step *= POS_THRESHOLD;
    }
    
    if (diff > ALPHA_MIN) {
        *pos = current + step;
    } else {
        *pos = current - step;
    }
    
    // Clamp check
    float remaining = target - *pos;
    float absRemaining = (remaining > ALPHA_MIN) ? remaining : -remaining;
    
    if (absRemaining < step) {
        *pos = target;
    }
}

/*
  Address: 0x80052EC4 | size: 0x264
  menuPdaSubScrollBar(void* winSprite, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f)
  Renders a scroll bar on the given window sprite layer.
  Handles position calculations and vertex rendering.
*/
void menuPdaSubScrollBar(void* winSprite, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f) {
    s32 layerId = winSpriteGetLayerID(winSprite);
    void* layer = GSgfxLayerFindByID(layerId);
    
    if (layer == 0) {
        return;
    }
    
    if (e > f) {
        u8 flag = ((u8*)winSprite)[4];
        flag |= 0x2;
        ((u8*)winSprite)[4] = flag;
    } else {
        u8 flag = ((u8*)winSprite)[4];
        flag &= ~0x2;
        ((u8*)winSprite)[4] = flag;
        return;
    }
    
    void* bios = menuItemBiosGetPtr(b, d);
    s16 offset = ((s16*)bios)[6];
    
    // Calculate scroll positions
    s16 y1 = offset ^ 0x8000;
    s16 y2 = ((s16*)bios)[0] ^ 0x8000;
    s16 y3 = (y2 + f) ^ 0x8000;
    
    double base = SCROLL_BASE;
    float scrollStep = (float)(base - (double)e);
    float scrollRange = (float)(base - (double)c);
    
    if (scrollRange != 0.0f) {
        float ratio = scrollStep / scrollRange;
        float pos1 = ratio * (float)(base - (double)e);
        float pos2 = ratio * (float)(base - (double)c);
        
        // Set layer state
        ((u32*)layer)[0x1644 / 4] = 1;
        ((u32*)layer)[0x1648 / 4] = 4;
        ((u32*)layer)[0x164C / 4] = 5;
        ((u32*)layer)[0x1650 / 4] = 5;
        ((u32*)layer)[0x170C / 4] |= 0x1;
        ((u32*)layer)[0x16A8 / 4] |= 0x40;
        ((u32*)layer)[0x17C4 / 4] |= 0x1;
        ((u32*)layer)[0x1760 / 4] |= 0x40;
        ((u32*)layer)[0x1998 / 4] = 0x80;
    }
    
    void* vf = GSgfxVFGetPredef(0);
    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vf);
    beginSurface__10GSgfxLayerFUs(layer, 4);
    
    // Render vertices (simplified - actual vertex data written to vertex buffer)
    // ... vertex rendering code ...
    
    endSurface__10GSgfxLayerFv(layer);
}

/*
  Address: 0x80053128 | size: 0xB4
  menuPdaSubCheckUpDownCursor(void* winSprite, s16* idx, s32 min, s32 max, s32 animState)
  Checks and updates up/down cursor visibility based on scroll position.
  Returns animation state.
*/
void menuPdaSubCheckUpDownCursor(void* winSprite, s16* idx, s32 min, s32 max, s32 animState) {
    s32 result = menuSubAnimAlpha(winSprite, 0, 0, 0, animState);
    ((u8*)winSprite)[0x67] = (u8)result;
    
    if (result) {
        if (min > max) {
            if (*idx == 0) {
                winSpriteSetDisp(winSprite, 0);
            } else {
                winSpriteSetDisp(winSprite, 1);
            }
        } else {
            winSpriteSetDisp(winSprite, 0);
        }
    } else {
        if (min > max) {
            s16 diff = *idx - min;
            if (max != diff) {
                winSpriteSetDisp(winSprite, 1);
            } else {
                winSpriteSetDisp(winSprite, 0);
            }
        } else {
            winSpriteSetDisp(winSprite, 0);
        }
    }
}
