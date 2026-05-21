// Decompiled from: menuReliveMeter.cpp
// Address range: 0x8005F524..0x800605B8 | size: 0x1094
// PowerPC 750CL / Gekko (GameCube)
// Compiler: Metrowerks CodeWarrior

/*
  Relive meter drawing module - renders DP (Dark Pokemon) meter bars
  using GSgfx layer primitives with vertex buffer FIFO writes.
  Calling convention: r3-r7 args, r3 return
*/

#include <math.h>

// Forward declarations
typedef struct DarkPokemon DarkPokemon;
typedef struct GSgfxLayer GSgfxLayer;
typedef struct GSgfxVF GSgfxVF;

void    __construct_array(void* ptr, void(*ctor)(void*), s32 start, s32 size, s32 count);
s32     timeGetLastFrameSec(void);
float   timeGetLastFrameSec(void);
DarkPokemon* getDarkPokemon__7PokemonFv(void);
s32     isDarkPokemon__7PokemonCFv(void);
s32     getInitDarkPointDirect__11DarkPokemonCFv(void);
s32     getDarkPointDirect__11DarkPokemonCFv(void);
GSgfxLayer* GSgfxLayerFindByID(u32 id);
GSgfxVF* GSgfxVFGetPredef(u32 id);
void    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(GSgfxLayer* this, GSgfxVF* vf);
void    beginSurface__10GSgfxLayerFUs(GSgfxLayer* this, u32 type);
void    endSurface__10GSgfxLayerFv(GSgfxLayer* this);
void    sin(float* x, float* result);

// SDA21-relative globals
static float meterCount;
static float max_alpha = 255.0f;
static float const_6_2831855 = 6.2831855f; // 2*PI
static float const_1 = 1.0f;
static float const_150 = 150.0f;

// Vertex FIFO base address (GSgfx)
// ASM: lis r7, 0xCC01 / stores to -0x8000(r7) = 0xCC010000
static volatile void* const pVF = (void*)0xCC010000;

// Helper to write to vertex FIFO
static inline void vfWrite16(u16 val) {
    *(volatile u16*)pVF = val;
}
static inline void vfWrite8(u8 val) {
    *(volatile u8*)pVF = val;
}

// Local helper for drawing meter sub-elements
// _menuDrawReliveMeterSub(DarkPokemon*, long, long, long, long, unsigned char, GSgfxLayer*)
static void _menuDrawReliveMeterSub__FP11DarkPokemonllllUcP10GSgfxLayer(
    DarkPokemon* dp, s32 p1, s32 p2, s32 p3, s32 p4, u8 p5, GSgfxLayer* layer) {
    s32 initDp = getInitDarkPointDirect__11DarkPokemonCFv();
    s32 dpVal = getDarkPointDirect__11DarkPokemonCFv();
    _menuDrawReliveMeterSubDpValue__FllllllUcP10GSgfxLayer(
        initDp, dpVal, p1, p2, p3, p4, p5, layer);
}

// menuDrawReliveMeter3(Pokemon*, long, long, long, long, unsigned char, u32 layerId)
// Address: 0x8005F524 | size: 0x74
void menuDrawReliveMeter3(Pokemon* pkmn, s32 p1, s32 p2, s32 p3, s32 p4, u8 p5, u32 layerId) {
    GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
    if (layer != NULL) {
        DarkPokemon* dp = getDarkPokemon__7PokemonFv();
        _menuDrawReliveMeterSub__FP11DarkPokemonllllUcP10GSgfxLayer(
            dp, p1, p2, p3, p4, p5, layer);
    }
}

// menuDrawReliveMeterByDarkPokemon(DarkPokemon*, long, long, long, long, unsigned char, u32 layerId)
// Address: 0x8005F598 | size: 0x6C
void menuDrawReliveMeterByDarkPokemon(DarkPokemon* dp, s32 p1, s32 p2, s32 p3, s32 p4, u8 p5, u32 layerId) {
    GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
    if (layer != NULL) {
        _menuDrawReliveMeterSub__FP11DarkPokemonllllUcP10GSgfxLayer(
            dp, p1, p2, p3, p4, p5, layer);
    }
}

// menuDrawReliveMeter(Pokemon*, long, long, long, u32 layerId)
// Address: 0x8005F604 | size: 0x94
void menuDrawReliveMeter(Pokemon* pkmn, s32 p1, s32 p2, s32 p3, u32 layerId) {
    if (isDarkPokemon__7PokemonCFv()) {
        GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
        if (layer != NULL) {
            DarkPokemon* dp = getDarkPokemon__7PokemonFv();
            _menuDrawReliveMeterSub__FP11DarkPokemonllllUcP10GSgfxLayer(
                dp, 0, 0, p1, p2, 0xFF, layer);
        }
    }
}

// menuDrawReliveUpdate()
// Address: 0x8005F698 | size: 0x2C
void menuDrawReliveUpdate(void) {
    float dt = timeGetLastFrameSec();
    meterCount += dt;
}

// _menuDrawReliveMeterSubDpValue(long, long, long, long, long, long, unsigned char, GSgfxLayer*)
// Address: 0x8005F6C4 | size: 0xE78
// LARGE function - renders the DP meter bar using GSgfx vertex primitives
// Uses fixed-point math for DP value scaling and vertex position calculation
static void _menuDrawReliveMeterSubDpValue__FllllllUcP10GSgfxLayer(
    s32 initDp, s32 curDp, s32 p2, s32 p3, s32 p4, s32 p5, u8 p6, GSgfxLayer* layer) {
    
    if (initDp == 0) {
        return;
    }
    
    // Fixed-point division: p4 * 0x64 * const / initDp
    // Calculates scaled DP value (0-5 range clamped)
    s32 scaledVal;
    {
        s64 tmp = (s64)p4 * 0x64;
        // Fixed-point multiplication with 0x51EC.851F / 0x9C0A.3F63 constants
        s64 hi = tmp * (s64)0x51EC851FULL;
        s64 lo = tmp * (s64)(s32)0x9C0A3F63ULL;
        s64 sum = hi + lo;
        s32 q = (s32)(sum >> 7);
        q += q >> 31; // arithmetic fixup
        scaledVal = q * 0x28;
        s32 q2 = (s32)((s64)scaledVal * (s64)(s32)0x51EC851FULL >> 5);
        q2 += q2 >> 31;
        scaledVal = q2;
    }
    
    // Clamp scaledVal to [0, 5]
    if (scaledVal > 5) scaledVal = 5;
    
    // Calculate alpha from p5
    s32 alphaVal;
    {
        s64 tmp = (s64)p5 * 0x64;
        s64 hi = tmp * (s64)0x66666667ULL;
        s32 q = (s32)(hi >> 3);
        q += q >> 31;
        alphaVal = q;
        if (alphaVal > 5) alphaVal = 5;
    }
    
    // Write initial vertex data
    u16* vf = (u16*)pVF;
    
    // Setup render state
    layer->field_1998 = 0x80;
    vfWrite8(0x06);
    vfWrite8(0x03);
    layer->field_d38 = 0;
    layer->field_16ac |= 4;
    layer->field_16a8 |= 1;
    layer->field_1764 |= 4;
    layer->field_1760 |= 1;
    
    GSgfxVF* vfPredef = GSgfxVFGetPredef(0);
    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
    beginSurface__10GSgfxLayerFUs(layer, 4);
    
    // Write vertex data to FIFO
    s16 yCoord = (s16)p2;
    s16 xCoord = (s16)p3;
    u8 col1 = (u8)((u32)scaledVal & 0xFF);
    u8 col2 = p6;
    
    // First vertex block
    vfWrite16(yCoord);
    vfWrite16(xCoord);
    vfWrite8(col1);
    vfWrite8(col2);
    vfWrite16((s16)(scaledVal * 5 + p4));
    vfWrite16(xCoord);
    vfWrite8(col1);
    vfWrite8(col2);
    vfWrite16((s16)(scaledVal * 5 + p4));
    vfWrite16(yCoord);
    vfWrite8(col1);
    vfWrite8(col2);
    vfWrite16((s16)(scaledVal + p4));
    vfWrite16(yCoord);
    vfWrite8(col1);
    vfWrite8(col2);
    
    endSurface__10GSgfxLayerFv(layer);
    
    // Draw 5 segments
    s32 seg;
    for (seg = 0; seg < 5; seg++) {
        layer->field_1998 = 0x80;
        vfWrite8(0x06);
        vfWrite8(0x03);
        layer->field_d38 = 0;
        layer->field_16ac |= 4;
        layer->field_16a8 |= 1;
        layer->field_1764 |= 4;
        layer->field_1760 |= 1;
        
        vfPredef = GSgfxVFGetPredef(0);
        setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
        beginSurface__10GSgfxLayerFUs(layer, 4);
        
        s16 y1 = (s16)(seg + p2 + 1);
        u8 c1 = (u8)((u32)scaledVal & 0xFF);
        vfWrite16(y1);
        vfWrite16((s16)(scaledVal * 5 + p4));
        vfWrite8(c1);
        vfWrite8(p6);
        vfWrite16((s16)(scaledVal * 5 + p4));
        vfWrite16((s16)(scaledVal + p4));
        vfWrite8(c1);
        vfWrite8(p6);
        vfWrite16((s16)(scaledVal + p4));
        vfWrite16((s16)(scaledVal + p4));
        vfWrite8(c1);
        vfWrite8(p6);
        vfWrite16((s16)(scaledVal + p4));
        vfWrite16(y1);
        vfWrite8(c1);
        vfWrite8(p6);
        
        endSurface__10GSgfxLayerFv(layer);
    }
    
    if (curDp != 0) {
        // Calculate second scaled value
        s32 scaledVal2;
        {
            s64 tmp = (s64)curDp * 0x64;
            s32 q = (s32)(tmp / initDp);
            s64 hi = q * (s64)0x51EC851FULL;
            s32 q2 = (s32)(hi >> 3);
            q2 += q2 >> 31;
            scaledVal2 = q2 + 1;
            if (scaledVal2 > 5) scaledVal2 = 5;
        }
        
        s32 i;
        for (i = 0; i < scaledVal2; i++) {
            layer->field_1998 = 0x86;
            vfWrite8(0xE1);
            vfWrite8(0x00);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 4);
            
            s16 yBase = (s16)(p3 + 1);
            s16 xBase = (s16)(p4 + 1);
            s32 off = (s32)scaledVal * (scaledVal2 - i);
            s32 off2 = (s32)((s64)off * 0x66666667ULL >> 3);
            off2 += off2 >> 31;
            s16 xOff = (s16)(p2 + off2);
            
            vfWrite16(yBase);
            vfWrite16(xBase);
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            vfWrite16(xOff);
            vfWrite16(xBase);
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            vfWrite16(xOff);
            vfWrite16((s16)(p2 + p5));
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            vfWrite16((s16)(p2 + p5));
            vfWrite16(yBase);
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            
            endSurface__10GSgfxLayerFv(layer);
            
            // Draw connector lines
            layer->field_1998 = 0xA8;
            vfWrite8(0x06);
            vfWrite8(0x36);
            vfWrite8(0xE1);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 2);
            
            vfWrite16((s16)(p2 + 1));
            vfWrite16((s16)(p3 + 2));
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            vfWrite16(xOff);
            vfWrite16((s16)(p3 + 2));
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            
            endSurface__10GSgfxLayerFv(layer);
            
            layer->field_1998 = 0xA8;
            vfWrite8(0x06);
            vfWrite8(0x00);
            vfWrite8(0x6C);
            vfWrite8(0xB5);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 2);
            
            vfWrite16((s16)(p2 + 1));
            vfWrite16((s16)(p4 + 1));
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            vfWrite16(xOff);
            vfWrite16((s16)(p4 + 1));
            vfWrite8((u8)((u32)i & 0xFF));
            vfWrite8(p6);
            
            endSurface__10GSgfxLayerFv(layer);
        }
    } else {
        // Animate meter when no current DP
        float sinArg = const_6_2831855 * meterCount;
        float sinVal;
        sin(&sinArg, &sinVal);
        sinVal = (float)((s32)sinVal);
        float alpha = (sinVal + const_1) * const_150;
        if (alpha > max_alpha) alpha = max_alpha;
        
        s32 alphaInt = (s32)alpha;
        s32 alphaClamped = p6 & 0xFF;
        
        // Fixed-point alpha calculation
        s64 tmp = (s64)alphaInt * alphaClamped;
        s32 q = (s32)((s64)tmp * (s64)(s32)0x80817F7FULL >> 7);
        q += q >> 31;
        s32 alphaFinal = q & 0xFFFF;
        s32 alphaFinal2 = (s32)((s64)alphaFinal * 0x4B * (s64)(s32)0x51EC851FULL >> 5);
        alphaFinal2 += alphaFinal2 >> 31;
        
        s16 yCoord = (s16)p2;
        s16 xCoord = (s16)(p3 + 1);
        u8 c1 = (u8)((u32)alphaFinal & 0xFF);
        s16 xCoord2 = (s16)(p4 + 1);
        u8 c2 = (u8)((u32)alphaFinal2 & 0xFF);
        
        s32 j;
        for (j = 0; j < 5; j++) {
            layer->field_1998 = 0x80;
            vfWrite8(0x06);
            vfWrite8(0x00);
            vfWrite8(0x03);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 4);
            
            s16 y1 = (s16)(j + p2 + 1);
            s16 x1 = (s16)(j * 5 + p4);
            
            vfWrite16(y1);
            vfWrite16(x1);
            vfWrite8(c1);
            vfWrite8(c2);
            vfWrite16(x1);
            vfWrite16((s16)(j + p4));
            vfWrite8(c1);
            vfWrite8(c2);
            vfWrite16((s16)(j + p4));
            vfWrite16((s16)(j + p4));
            vfWrite8(c1);
            vfWrite8(c2);
            vfWrite16((s16)(j + p4));
            vfWrite16(y1);
            vfWrite8(c1);
            vfWrite8(c2);
            
            endSurface__10GSgfxLayerFv(layer);
            
            // Connector lines
            layer->field_1998 = 0xA8;
            vfWrite8(0x06);
            vfWrite8(0x36);
            vfWrite8(0xE1);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 2);
            
            vfWrite16((s16)(p2 + 1));
            vfWrite16((s16)(p3 + 2));
            vfWrite8(c1);
            vfWrite8(c2);
            vfWrite16(x1);
            vfWrite16((s16)(p3 + 2));
            vfWrite8(c1);
            vfWrite8(c2);
            
            endSurface__10GSgfxLayerFv(layer);
            
            layer->field_1998 = 0xA8;
            vfWrite8(0x06);
            vfWrite8(0x00);
            vfWrite8(0x6C);
            vfWrite8(0xB5);
            layer->field_d38 = 0;
            layer->field_16ac |= 4;
            layer->field_16a8 |= 1;
            layer->field_1764 |= 4;
            layer->field_1760 |= 1;
            
            vfPredef = GSgfxVFGetPredef(0);
            setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vfPredef);
            beginSurface__10GSgfxLayerFUs(layer, 2);
            
            vfWrite16((s16)(p2 + 1));
            vfWrite16((s16)(p4 + 1));
            vfWrite8(c1);
            vfWrite8(c2);
            vfWrite16(x1);
            vfWrite16((s16)(p4 + 1));
            vfWrite8(c1);
            vfWrite8(c2);
            
            endSurface__10GSgfxLayerFv(layer);
        }
    }
}
