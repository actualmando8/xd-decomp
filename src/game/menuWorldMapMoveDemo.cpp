// Decompiled from: menuWorldMapMoveDemo.cpp
// Address range: 0x8009D4E8..0x8009D6B8 | size: 0x1D0

s32     floorGetCurrentGroupID(void);
s32     HSD_Rand(void);
void    cameraPlayAnime(s32 group, s32 animeId);
void    GSthreadSwitch(void);
void    GSfloorPop(void);

struct WorldMapModel;
struct WorldMapMoveDemo;

void    SetModel__13WorldMapModelFUlUlb(WorldMapModel* this, s32 group, s32 modelId, s32 flag);
void    SetMotion__13WorldMapModelFUlsfb(WorldMapModel* this, s32 modelId, s16 motion, f32 param);
u32     GetAnimeFrameCount__13WorldMapModelFUlUl(WorldMapModel* this, s32 modelId, s32 param);
s32     GetAnimeFrame__13WorldMapModelFUl(WorldMapModel* this, s32 modelId);
void    releaseOffscreenData__13WorldMapModelFv(WorldMapModel* this);
void*   __nw__FUl(u32 size);
void    __dl__FPv(void* ptr);

/* Animation table - 15 entries of (motion, modelId) pairs */
static const struct {
    s16 motion;
    u32 modelId;
} _animeTable[] = {
    { 0x0000, 0x1B491800 }, { 0x0001, 0x1B781800 }, { 0x0002, 0x1B791800 },
    { 0x0003, 0x1B7A1800 }, { 0x0004, 0x1B7B1800 }, { 0x0005, 0x1B7C1800 },
    { 0x0006, 0x1B7D1800 }, { 0x0007, 0x1B7E1800 }, { 0x0008, 0x1B7F1800 },
    { 0x0009, 0x1B801800 }, { 0x000A, 0x1B811800 }, { 0x000B, 0x1B821800 },
    { 0x000C, 0x1B831800 }, { 0x000D, 0x1B841800 }, { 0x000E, 0x1B851800 },
};

/* Global state */
static WorldMapMoveDemo* pMoveDemo;

/*
  Address: 0x8009D4E8 | size: 0x5C
  menuWorldMapMoveDemoExit()
  Cleans up MoveDemo: releases offscreen data, deletes object, clears pointer.
*/
void menuWorldMapMoveDemoExit(void) {
    WorldMapMoveDemo* demo = pMoveDemo;
    if (demo != 0) {
        if (demo->field_0x0 != 0) {
            releaseOffscreenData__13WorldMapModelFv(demo);
        }
        __dl__FPv(demo);
        pMoveDemo = 0;
    }
}

/*
  Address: 0x8009D544 | size: 0x2C
  menuWorldMapMoveDemoMain()
  Calls Main() on pMoveDemo if non-null.
*/
void menuWorldMapMoveDemoMain(void) {
    if (pMoveDemo != 0) {
        Main__16WorldMapMoveDemoFv(pMoveDemo);
    }
}

/*
  Address: 0x8009D570 | size: 0x38
  menuWorldMapMoveDemoInit()
  Allocates and initializes MoveDemo object.
*/
void menuWorldMapMoveDemoInit(void) {
    void* ptr = __nw__FUl(4);
    if (ptr != 0) {
        *(s32*)ptr = 0;
    }
    pMoveDemo = (WorldMapMoveDemo*)ptr;
}

/*
  Address: 0x8009D5A8 | size: 0x110
  Main__16WorldMapMoveDemoFv(WorldMapMoveDemo* this)
  WorldMapMoveDemo::Main()
  Sets up model, plays random camera anime and motion, waits for animation to complete, then pops floor.
  Uses integer division to calculate random index from HSD_Rand().
*/
void Main__16WorldMapMoveDemoFv(WorldMapMoveDemo* this) {
    s32 group = floorGetCurrentGroupID();
    
    SetModel__13WorldMapModelFUlUlb(this, group, 0x1B4A400, 0);
    
    // Random index selection using fast division
    s32 rand = HSD_Rand();
    s32 rand_upper = rand & 0xFFFF0000;
    // Fast division by 15 using multiplication by 0x8889 (magic number for /15)
    s32 div_result = (((s64)(rand_upper * (0x8889 - 0x7777)) >> 3) + (rand_upper < 0)) * 15;
    s32 index = ((rand_upper - div_result) & 0xFFFF0000) >> 18;
    
    const void* entry = &_animeTable[index];
    s16 motion = entry->motion;
    u32 modelId = entry->modelId;
    
    cameraPlayAnime(group, modelId);
    SetMotion__13WorldMapModelFUlsfb(this, 0x1B4B000, motion, 0.0f);
    
    u32 frameCount = GetAnimeFrameCount__13WorldMapModelFUlUl(this, 0x1B4B000, 0);
    f32 remaining = (f32)frameCount - 30.0f;
    
    // Wait loop until animation completes
    while (remaining >= 0.0f) {
        GetAnimeFrame__13WorldMapModelFUl(this, 0x1B4B000);
        if (remaining < 0.0f) break;
        GSthreadSwitch();
    }
    
    GSfloorPop();
}
