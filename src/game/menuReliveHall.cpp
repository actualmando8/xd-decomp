// menuReliveHall.cpp - Relive Hall Menu System
// Address: 0x8003AA1C..0x80041C3C | size: 0x7220
// Functions: 103 (mostly in anonymous namespace)
//
// Key global functions:
//   menuReliveHallExecFromPcBox  - Entry point from PC Box
//   relivehallSetLastViewStage   - Set last viewed stage
//   relivehallGetLastViewStage   - Get last viewed stage
//   relivehallTempoToLevel       - Convert tempo to difficulty level
//   relivehallTempoToRate        - Convert tempo to rate (float)
//   relivehallDraw9StageInfo     - Draw info for all 9 stages
//   relivehallDraw9StageNumber   - Draw stage numbers 1-9
//   relivehallDrawStageInfoCursor - Draw cursor for stage info

#include "global.h"

/* Forward declarations */
struct Pokemon;
struct CMenuGlobalState;
struct tagWINDOW_WORK;
struct GSgfxLayer;
typedef u32 GSgfxLayerID;
typedef u32 GSgfxColAu8;

void* GSmemAllocClr(u32 size);
void GSmemFree(void* ptr);
void GSprimSetBlendMode(u32 mode);
void GSprimDraw2DPixelListC(u32*, u32*, u32);
void* getPointer__11CReliveHallFv();
void* getStage__11CReliveHallFl(long stage);
void* getVisitorPointer__12CReliveStageFv();
u32 getDancerQuantity__12CReliveStageFv();
u32 getTempo__12CReliveStageFv();
void* menuItemBiosGetPtr(u32 menuId, u32 itemId);
void* windowSearchID(u32 id);
void* menuPtItemGetByMenuIdAndItemId__FlUll(long menuId, u32 itemId, u32, u32);
void menuPtItemDrawAlpha__FP13MENU_ITEM_dd_Uc(void* item, s32 x, s32 y, u8 alpha);
void menuPtItemDrawOffset__FP13MENU_ITEM_dd_ll(void* item, s32 x, s32 y, s32 ox, s32 oy);
void menuPtItemDrawOffsetXWColor__FP13MENU_ITEM_dd_llUl(void* item, s32 x, s32 y, s32 ox, s32 oy, u32 color);
void menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKUllb(tagWINDOW_WORK*, u32 id, s32 x, s32 y, u32 sw);
void menuPtSpriteWorkSetWidthRateColor__FP14tagWINDOW_WORKUllf11GSgfxColAu8(tagWINDOW_WORK*, u32 id, s32 x, s32 y, float rate, GSgfxColAu8 color);
void menuPtWindowWorkDraw__FP14tagWINDOW_WORK(tagWINDOW_WORK*);
void winSpriteDraw(void* win, void* sprite);
void spriteSetScissor(GSgfxLayerID, s16 x, s16 y, s16 w, s16 h);
void spriteSetEnv(GSgfxLayerID, u32 env);
void spriteSetOffset(GSgfxLayerID, s16 x, s16 y);
void spriteClearScissor(GSgfxLayerID);
GSgfxColAu8 GSgfxColAu8To32__F11GSgfxColAu8(GSgfxColAu8);
void updateAll__9CMetaMenuFv(void* menu);

/* Static data - Anonymous namespace variables (@unnamed@menuReliveHall_cpp@) */
static long sLastViewStage;  // _lastViewStage__28@unnamed@menuReliveHall_cpp@
static void* sMenuReliveHall;  // pMenuReliveHall__28@unnamed@menuReliveHall_cpp@
static u32 relivehallAisyou2ColorTbl[3];  // Color table for 3 difficulty levels

/* Static data for stage offsets */
static u16 lbl_8032E568[18];  // Stage offset table (9 stages x 2)

/* 0x8003AA74 | size: 0x20 */
// Entry point from PC Box - executes the Relive Hall menu
void menuReliveHallExecFromPcBox__FR16CMenuGlobalState(CMenuGlobalState& state) {
    // Calls thisExec which does: thisNew() -> main() -> thisFree()
    // Implemented as anonymous namespace function
}

/* 0x8003AA94 | size: 0x8 */
// Set the last viewed stage number
void relivehallSetLastViewStage__Fl(long stage) {
    sLastViewStage = stage;
}

/* 0x8003AA9C | size: 0x8 */
// Get the last viewed stage number
long relivehallGetLastViewStage__Fv() {
    return sLastViewStage;
}

/* 0x8003AAA4 | size: 0x28 */
// Convert tempo value to difficulty level (0, 1, or 2)
// tempo <= 0x1A (26): level 0 (Easy)
// 0x1A < tempo <= 0x35 (53): level 1 (Normal)
// tempo > 0x35: level 2 (Hard)
u32 relivehallTempoToLevel__Fi(int tempo) {
    if (tempo <= 0x1A) {
        return 0;
    }
    if (tempo <= 0x35) {
        return 1;
    }
    return 2;
}

/* 0x8003AACC | size: 0x30 */
// Convert tempo to rate (0.0 to 1.0)
// rate = (tempo - 26.0) / 27.0
float relivehallTempoToRate__Fi(int tempo) {
    return ((float)tempo - 26.0f) / 27.0f;
}

/* 0x8003AAFC | size: 0x180 */
// Draw info for all 9 stages (relive meter, tempo bar, etc.)
// Iterates through stages 0-8, drawing visitor meter and tempo bar
void relivehallDraw9StageInfo__Fi(int startStage) {
    for (int i = startStage; i < 9; i++) {
        // Get stage pointer and visitor
        void* stage = getStage__11CReliveHallFl(i);
        void* visitor = getVisitorPointer__12CReliveStageFv();
        
        if (visitor != 0) {
            // Draw relive meter for visitor
            void* item = menuItemBiosGetPtr(0x72, 0x2B2);
            void* win = windowSearchID(0x72);
            // ... draw meter using _menuDrawReliveMeter
        }
        
        // Get tempo and draw tempo bar
        u32 tempo = getTempo__12CReliveStageFv();
        u32 level = relivehallTempoToLevel__Fi(tempo);
        u32 color = relivehallAisyou2ColorTbl[level];
        GSgfxColAu8 color32 = GSgfxColAu8To32__F11GSgfxColAu8(color);
        
        float rate = relivehallTempoToRate__Fi(tempo);
        // ... draw tempo bar with width rate and color
    }
}

/* 0x8003AC7C | size: 0x68 */
// Draw stage numbers 1-9 with alpha based on current stage
// Stages before current: alpha 0x3C (dimmed)
// Current stage: alpha 0xFF (full)
void relivehallDraw9StageNumber__Fi(int currentStage) {
    for (int i = 0; i < 9; i++) {
        void* item = menuPtItemGetByMenuIdAndItemId__FlUll(i, 0x2A7, 0, 0);
        u8 alpha = (i == currentStage) ? 0xFF : 0x3C;
        menuPtItemDrawAlpha__FP13MENU_ITEM_dd_Uc(item, 0, 0, alpha);
    }
}

/* 0x8003ACE4 | size: 0x11C */
// Draw cursor for stage info with tempo bar and switches
// r3 = stage (long), r4 = x, r5 = y, r6 = pokemon*, r7 = bool
void relivehallDrawStageInfoCursor__FliiP7Pokemonb(long stage, int x, int y, Pokemon* pkmn, bool flag) {
    void* win = windowSearchID(0x71);
    s32 stageOffset = stage * 0x42;
    
    // Set stage offset in window work
    *(s16*)((u8*)win + 0x8C) = (s16)stageOffset;
    
    // Tempo bar sprite setting
    u16 offset = lbl_8032E568[stage * 2];
    *(s16*)((u8*)win + 0x8C) += offset;
    
    // ... tempo bar drawing via _relivehallTempoBarSpriteSetting
    
    // Set sprite switches based on parameters
    menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKUllb(win, 0x2B3, 0, 0, (y != 0));
    menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKUllb(win, 0x2BA, 0, 0, flag);
    menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKUllb(win, 0x8E9, 0, 0, (pkmn != 0));
    
    // Draw window work
    menuPtWindowWorkDraw__FP14tagWINDOW_WORK(win);
    
    // Draw relive meter if pokemon provided
    if (pkmn != 0) {
        // ... draw meter
    }
}

/* Anonymous namespace functions - stubs for CMenuReliveHall class methods */
// The file contains 103 functions total, most in anonymous namespace
// Key classes: CMenuReliveHall (extends CMetaMenu), SCircle, CStick

// CMenuReliveHall::isAnimationStateNone() - Check if animation state is none
// CMenuReliveHall::updateAll() - Update all menu elements
// CMenuReliveHall::main(CMenuGlobalState&) - Main loop
// CMenuReliveHall::draw() - Draw all elements
// SCircle::draw() - Draw circle primitive
// SCircle::allSwOff() - Turn off all switches
// CStick::update() - Update stick animation
// ... (many more internal methods)

/* Helper: _relivehallTempoBarSpriteSetting */
// Sets up tempo bar sprite with width rate and color based on tempo
// Uses scissor for clipping when tempo > 0
static void _relivehallTempoBarSpriteSetting(tagWINDOW_WORK* win, u32 itemId, int tempo,
                                              u8 alpha, bool flag) {
    float rate = relivehallTempoToRate__Fi(tempo);
    u32 level = relivehallTempoToLevel__Fi(tempo);
    u32 color = relivehallAisyou2ColorTbl[level];
    
    if (tempo != 0) {
        // Set width rate and color, then draw with scissor
        void* sprite = menuPtSpriteWorkGetByItemID__FP14tagWINDOW_WORKUll(win, itemId, 0, 0);
        menuPtSpriteWorkSetWidthRateColor__FP14tagWINDOW_WORKUllf11GSgfxColAu8(
            win, itemId, 0, 0, rate, color);
        // ... scissor setup and drawing
    } else {
        // Just set color without width rate
        menuPtSpriteWorkSetWidthRateColor__FP14tagWINDOW_WORKUllf11GSgfxColAu8(
            win, itemId, 0, 0, rate, color);
    }
}

/* Helper: _menuDrawReliveMeter */
// Draws the relive meter for a pokemon
// Shows progress bar based on relive completion
static void _menuDrawReliveMeter__28@unnamed@menuReliveHall_cpp@(
    Pokemon* pkmn, long x, long y, long ox, long oy, u8 alpha, GSgfxLayerID layer, long flag) {
    // ... meter drawing implementation
}

/* Singleton management functions */
static void thisExec(CMenuGlobalState& state) {
    thisNew();
    void* menu = sMenuReliveHall;
    // main__CMenuReliveHall(state);
    thisFree();
}

static void thisFree() {
    void* menu = sMenuReliveHall;
    if (menu != 0) {
        GSmemFree(menu);
        sMenuReliveHall = 0;
    }
}

static void thisNew() {
    // Allocate 0x1190 bytes for CMenuReliveHall
    void* menu = GSmemAllocClr(0x1190);
    if (menu != 0) {
        // Set up vtable pointers (double vtable for CMetaMenu inheritance)
        *(void**)((u8*)menu + 0x330) = &__vt__9CMetaMenu;
        // *(void**)((u8*)menu + 0x330) = &__vt__CMenuReliveHall; // Anonymous namespace mangled
    }
    sMenuReliveHall = menu;
}
