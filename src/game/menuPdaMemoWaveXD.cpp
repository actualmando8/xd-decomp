// Decompilation of menuPdaMemoWaveXD.cpp
// Original address: 0x80065854..0x800665F4 | size: 0xDA0
// Functions: 10
// This file implements the Pokemon cry waveform visualization

#include "global.h"

// Forward declarations
void* GSfloorGetCurrent(void);
void* GSgfxLayerFindByID(int id);
void* GSsplineCreate(int type, int param2, int param3);
void GSsplineAddControlVectorValue(void* spline, void* vector);
void GSsplineFree(void* spline);
void GSsndPlay(int soundId, int param2, int param3);
int GSsndGetStatus(int soundHandle);
void GSthreadSwitch(void);
int GSinputButtonsChanged(int buttonMask);
int GSinputButtonsPressed(int buttonMask);
int memoDataGetCount(void);
void* menuPdaMemoListGetPokemonDataPointer(int index);
void* pokemonDataBiosGetVoice(void* pokemonData);
void* pokemonNakigoeDataBiosGetDataAddress(void* pokemonData);

// Graphics layer functions
void setRenderStateAndSelect(void* layer, void* vfx);
void beginSurface(void* layer, u16 param2);
void endSurface(void* layer);
void* GSgfxVFBuildTemp(int param1, int param2, int param3, int param4, int param5, int param6, int param7, int param8, int param9, int param10);

// Struct for display work
typedef struct {
    u32 field_0;
    u32 field_4;
    u32 field_8;
    u32 field_C;
    u32 field_10;
    float field_14;
    float field_18;
    float field_1C;
    float field_20;
} NakigoeDispWork;

// pdaMemoNakigoe class - size 0x124
typedef struct {
    NakigoeDispWork dispWork[8];   // 0x00 - 0x120 (8 * 0x24)
    u32 counter;                    // 0x120
} pdaMemoNakigoe;

// Global variable
extern pdaMemoNakigoe* _nakigoe;

// Floating point constants
static const float @2246 = 0.0f;
static const float @2247 = 255.0f;
static const float @2248 = 0.5f;
static const float @2249 = 0.2f;
static const double @2251 = 65536.0;
static const float @2278 = 10.0f;
static const float @2361 = 1.0f;
static const float @2362 = 556.0f;
static const double @2364 = 1.0;
static const float @2403 = 105.0f;

/* 0x80065854 | size: 0x38 */
// Hook function for cry display
// r3 = windowWork, r4 = spriteWork
void menuPdaMemoWaveHook(void* windowWork, void* spriteWork)
{
    if (_nakigoe) {
        _nakigoe->NakigoeDispFunc(windowWork, spriteWork);
    }
}

/* 0x8006588C | size: 0x54 */
// Initialize cry display
void menuPdaMemoWaveInit(void)
{
    if (_nakigoe) {
        // Clear all disp work
        for (int i = 0; i < 0x124; i += 0x24) {
            *(u32*)((u32)_nakigoe + i) = 0x0;
        }
        _nakigoe->DispInit();
    }
}

/* 0x800658E0 | size: 0x13C */
// Main cry visualization loop
// r3 = pokemonId
void menuPdaMemoWave(int pokemonId)
{
    pdaMemoNakigoe* nakigoe = _nakigoe;
    if (!nakigoe) {
        nakigoe = (pdaMemoNakigoe*)__nw(0x124);
        if (nakigoe) {
            // Clear all disp work
            for (int i = 0; i < 0x124; i += 0x24) {
                *(u32*)((u32)nakigoe + i) = 0x0;
            }
            nakigoe->DispInit();
        }
        _nakigoe = nakigoe;
    }
    
    // Clear disp work
    for (int i = 0; i < 0x124; i += 0x24) {
        *(u32*)((u32)_nakigoe + i) = 0x0;
    }
    _nakigoe->DispInit();
    
    _nakigoe->SetNakigoe(pokemonId);
    
    while (1) {
        if (!_nakigoe->NakigoeCheck()) {
            // Check for A button press (restart cry)
            if (GSinputButtonsChanged(0x1) & GSinputButtonsPressed(0x1) & 0x400000) {
                _nakigoe->SetNakigoe(pokemonId);
            }
            // Check for B button press (exit)
            else if (!(GSinputButtonsChanged(0x1) & GSinputButtonsPressed(0x1) & 0x200000)) {
                GSthreadSwitch();
                continue;
            }
        }
        break;
    }
}

/* 0x80065A1C | size: 0x70 */
// Set cry data for Pokemon
// r3 = this, r4 = pokemonId
void pdaMemoNakigoe::SetNakigoe(int pokemonId)
{
    u32 voiceId = GetVocie(pokemonId);
    SetSE(voiceId);
    s8* waveData = GetWaveDispDataAddress(pokemonId);
    DispRequest(waveData, voiceId);
}

/* 0x80065A8C | size: 0x2C */
// Play cry sound
// r3 = this, r4 = soundId
void pdaMemoNakigoe::SetSE(u32 soundId)
{
    GSsndPlay(soundId, 0x0, 0x0);
}

/* 0x80065AB8 | size: 0x68 */
// Get voice ID for Pokemon
// r3 = this, r4 = pokemonId
u32 pdaMemoNakigoe::GetVocie(int pokemonId)
{
    if (memoDataGetCount()) {
        void* pokemonData = menuPdaMemoListGetPokemonDataPointer(pokemonId);
        if (pokemonData) {
            return (u32)pokemonDataBiosGetVoice(pokemonData);
        }
        return 0xFFFFFFFF;
    }
    return 0xFFFFFFFF;
}

/* 0x80065B20 | size: 0x50 */
// Initialize display work structures
void pdaMemoNakigoe::DispInit(void)
{
    for (int i = 0; i < 8; i++) {
        DispRequest((s8*)0, 0x0);
    }
}

/* 0x80065B70 | size: 0x2A4 */
// Request display update with wave data
// r3 = this, r4 = waveData, r5 = voiceId
void pdaMemoNakigoe::DispRequest(s8* waveData, u32 voiceId)
{
    // Increment counter (circular buffer)
    _counter++;
    if (_counter >= 8) {
        _counter = 0;
    }
    
    int idx = _counter;
    int offset = idx * 0x24;
    NakigoeDispWork* work = &dispWork[idx];
    
    work->field_0 = voiceId;
    work->field_8 = voiceId;
    work->field_C = @2246;
    work->field_14 = @2246;
    work->field_10 = 0x0;
    work->field_18 = 0x1;
    work->field_1C = @2249;
    work->field_20 = @2248;
    
    // Process previous entries
    int prevIdx = idx - 1;
    if (prevIdx < 0) {
        prevIdx = 7;
    }
    
    // Update wave positions using floating point math
    for (int i = 0; i < prevIdx; i++) {
        NakigoeDispWork* w = &dispWork[i];
        // Update field_10 with XOR operation
        w->field_10 ^= 0x80000000;
        // Update field_4 with floating point addition
        w->field_4 = w->field_4 - @2251 + @2249;
        // Update field_20
        w->field_20 = w->field_20 + @2249;
    }
}

/* 0x80065E14 | size: 0xFC */
// Display function for cry visualization
// r3 = this, r4 = windowWork, r5 = spriteWork
void pdaMemoNakigoe::NakigoeDispFunc(void* windowWork, void* spriteWork)
{
    // Process all 8 display work entries
    for (int i = 0; i < 8; i++) {
        u32 layerId = dispWork[i].field_1C;
        DispFuncSub(&dispWork[i], (int)layerId);
    }
    
    // Update wave positions
    int count = _counter;
    for (int i = 0; i < count; i++) {
        NakigoeDispWork* w = &dispWork[i];
        w->field_1C = w->field_1C - @2278;
        if (w->field_1C < @2246) {
            w->field_1C = @2246;
        }
    }
    for (int i = 7; i >= 0; i--) {
        NakigoeDispWork* w = &dispWork[i];
        w->field_1C = w->field_1C - @2278;
        if (w->field_1C < @2246) {
            w->field_1C = @2246;
        }
    }
}

/* 0x80065F10 | size: 0x440 */
// Sub function for display rendering with spline interpolation
// r3 = this, r4 = dispWork, r5 = layerId
void pdaMemoNakigoe::DispFuncSub(NakigoeDispWork* work, int layerId)
{
    u32 voiceId = work->field_0;
    if (!voiceId) {
        return;
    }
    
    u8 dataLen = work->field_0;
    int len = dataLen + 2;
    
    // Update field_4
    work->field_4 = (float)len - @2364;
    
    // Update counters
    if (work->field_18 < len) {
        work->field_18++;
    } else if (work->field_10 < len) {
        work->field_10++;
    } else if (work->field_10 < len + 0x1e) {
        work->field_10 = len;
        work->field_14 = work->field_14 + @2249;
    } else {
        work->field_10 = len;
        work->field_C = work->field_C + @2249;
        work->field_14 = work->field_14 + @2249;
    }
    
    // Create spline for smooth wave rendering
    void* spline = GSsplineCreate(0x3, 0x1, len);
    if (!spline) {
        return;
    }
    
    // Add control points to spline
    GSsplineAddControlVectorValue(spline, (void*)0x43300000);
    
    // Process wave data
    for (int i = 0; i < dataLen; i++) {
        s8 sample = work->waveData[i];
        sample ^= 0x8000;
        GSsplineAddControlVectorValue(spline, (void*)sample);
    }
    
    // Final control point
    GSsplineAddControlVectorValue(spline, (void*)0x43300000);
    
    // Draw lines between spline points
    int numPoints = work->field_C;
    for (int i = 0; i < numPoints; i++) {
        // Get spline values and draw line
        _drawLine(layerId, &work->vecStart, &work->vecEnd, work->field_4);
    }
    
    GSsplineFree(spline);
}

/* 0x80066350 | size: 0x88 */
// Check if cry sound is still playing
int pdaMemoNakigoe::NakigoeCheck(void)
{
    int isPlaying = 0;
    for (int i = 0; i < 8; i++) {
        if (dispWork[i].field_0) {
            int status = GSsndGetStatus(dispWork[i].field_8);
            if (status == 0x2) {
                isPlaying = 1;
            } else if (status >= 0x2 && status < 0x4) {
                isPlaying = 1;
            }
        }
    }
    return isPlaying;
}

/* 0x800663D8 | size: 0x1BC */
// Draw line between two vectors on graphics layer
// r3 = layerId, r4 = vecStart, r5 = vecEnd, f1 = alpha
void _drawLine(int layerId, float* vecStart, float* vecEnd, float alpha)
{
    void* layer = GSgfxLayerFindByID(layerId);
    if (!layer) {
        return;
    }
    
    // Build vertex format
    void* vfx = GSgfxVFBuildTemp(0x0, 0x3, 0x0, 0x0, 0x1, 0x5, 0x0, 0x0, 0x0, 0x0);
    
    // Set render state
    setRenderStateAndSelect(layer, vfx);
    
    // Configure layer settings
    *(u32*)((u32)layer + 0x1998) = 0xa8;
    *(u8*)((u32)layer + 0xd34) = 0x18;
    *(u32*)((u32)layer + 0xd38) = 0x0;
    *(u32*)((u32)layer + 0x16ac) |= 0x4;
    *(u32*)((u32)layer + 0x16a8) |= 0x1;
    *(u32*)((u32)layer + 0x1764) |= 0x4;
    *(u32*)((u32)layer + 0x1760) |= 0x1;
    
    beginSurface(layer, 0x0);
    
    // Calculate screen coordinates
    s16 x1 = (s16)(vecStart[0] * @2248 + @2403);
    s16 y1 = (s16)(vecStart[1] * @2248 + @2403);
    s16 x2 = (s16)(vecEnd[0] * @2248 + @2403);
    s16 y2 = (s16)(vecEnd[1] * @2248 + @2403);
    
    // Write vertex data to vertex buffer
    u16* vbuf = (u16*)0xCC010000;
    *vbuf++ = x1;
    *vbuf++ = y1;
    *vbuf++ = 0x96E6 | (vecStart[2] & 0xFF) | 0xF000;
    *vbuf++ = x2;
    *vbuf++ = y2;
    *vbuf++ = 0x96E6 | (vecEnd[2] & 0xFF) | 0xF000;
    
    endSurface(layer);
    
    // Restore layer settings
    *(u8*)((u32)layer + 0xd34) = 0x6;
    *(u32*)((u32)layer + 0xd38) = 0x0;
    *(u32*)((u32)layer + 0x16ac) |= 0x4;
    *(u32*)((u32)layer + 0x16a8) |= 0x1;
    *(u32*)((u32)layer + 0x1764) |= 0x4;
    *(u32*)((u32)layer + 0x1760) |= 0x1;
}

/* 0x80066594 | size: 0x60 */
// Get wave display data address for Pokemon
// r3 = this, r4 = pokemonId
s8* pdaMemoNakigoe::GetWaveDispDataAddress(int pokemonId)
{
    if (memoDataGetCount()) {
        void* pokemonData = menuPdaMemoListGetPokemonDataPointer(pokemonId);
        if (pokemonData) {
            return (s8*)pokemonNakigoeDataBiosGetDataAddress(pokemonData);
        }
        return (s8*)0x0;
    }
    return (s8*)0x0;
}
