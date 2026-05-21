// menuPocketTool.cpp - Pocket Menu Toolkit
// Address: 0x8001EC10..0x80022080 | size: 0x3470
// Functions: 106
//
// Classes:
//   CMenuGlobalState - Global menu state container
//   CMenuPokemonCursor - Pokemon cursor with animation
//   CInfoWindow - Info window with message control
//   CMetaMenu - Base menu class with fade/animation system
//   CState - State machine base class
//
// Utility functions for:
//   Sound management (save/restore/stop)
//   Pokemon creation (debug functions)
//   Sprite/window drawing
//   Math utilities (direction, distance, degree refresh)

#include "global.h"

/* Forward declarations */
struct Pokemon;
struct CAnt;
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct MENU_ITEM;
struct MENU_SPRITE;
struct GSmodel;
struct GSbound;

typedef u32 GSgfxLayerID;
typedef u32 GSgfxColAu8;

/* Struct definitions based on assembly analysis */
struct MenuPtWorkSound {
    u32 bgmId;          // 0x0
    u32 envId;          // 0x4
    u8  bgmVolume;      // 0x8
    u8  envVolume;      // 0x9
};

struct CMenuPokemonCursor {
    u8     active;              // 0x0 - Is cursor active
    u8     animState;           // 0x1 - Animation state
    u8     catchState;          // 0x2 - Catch state
    u8     field_3;             // 0x3
    float  scale;               // 0x8 - Pokemon scale
    s16    posX;                // 0x14 - X position
    s16    posY;                // 0x16 - Y position
    u32*   positionTable;       // 0x18 - Position table pointer
    u32    positionIndex;       // 0x1C - Current position index
    u32    field_20;            // 0x20
    Pokemon pokemon;            // 0x20 - Pokemon data
    CAnt   ant1;                // 0xE4 - Ant 1
    CAnt   ant2;                // 0x118 - Ant 2
    u8     field_14C;           // 0x14C - Flag
    float  field_150;           // 0x150 - Timer
    // ... more fields ...
};

struct CInfoWindow {
    u32 windowId;         // 0x0
    u32 msgId;            // 0x4
    u8  isActive;         // 0x8
    u8  hasMessage;       // 0x9
    u32 msgState;         // 0xC
    u32 msgCtrl[4];       // 0x10 - Message control values
    u16 keyState;         // 0x30
};

struct CMetaMenu {
    void* vtable;              // 0x0
    u32   field_4;             // 0x4 - Alpha fade state
    u32   field_8;             // 0x8
    u32   field_C;             // 0xC
    u32   field_10;            // 0x10
    u32   field_14;            // 0x14
    u32   field_18;            // 0x18
    u32   field_1C;            // 0x1C
    u32   field_20;            // 0x20
    u32   field_24;            // 0x24
    u32   field_28;            // 0x28
    u32   field_2C;            // 0x2C
    u32   field_30;            // 0x30
    u32   field_34;            // 0x34
    u32   field_38;            // 0x38
    u32   field_3C;            // 0x3C
    u32   field_40;            // 0x40
    u32   field_44;            // 0x44
    u32   field_48;            // 0x48
    u32   field_4C;            // 0x4C
    u32   field_50;            // 0x50
    u32   field_54;            // 0x54
    u32   field_58;            // 0x58
    u32   field_5C;            // 0x5C
    u32   field_60;            // 0x60
    u32   field_64;            // 0x64
    u32   field_68;            // 0x68
    u32   field_6C;            // 0x6C
    u32   field_70;            // 0x70
    u32   field_74;            // 0x74
    u32   field_78;            // 0x78
    u32   field_7C;            // 0x7C
    u32   field_80;            // 0x80
    u32   field_84;            // 0x84
    u32   field_88;            // 0x88
    u32   field_8C;            // 0x8C
    u32   field_90;            // 0x90
    u32   field_94;            // 0x94
    u32   field_98;            // 0x98
    u32   field_9C;            // 0x9C
    u32   field_A0;            // 0xA0
    u32   field_A4;            // 0xA4
    u32   field_A8;            // 0xA8
    u32   field_AC;            // 0xAC
    u32   field_B0;            // 0xB0
    u32   field_B4;            // 0xB4
    u32   field_B8;            // 0xB8
    u32   field_BC;            // 0xBC
    u32   field_C0;            // 0xC0
    u32   field_C4;            // 0xC4
    u32   field_C8;            // 0xC8
    u32   field_CC;            // 0xCC
    u32   field_D0;            // 0xD0
    u32   field_D4;            // 0xD4
    u32   field_D8;            // 0xD8
    u32   field_DC;            // 0xDC
    u32   field_E0;            // 0xE0
    u32   field_E4;            // 0xE4
    u32   field_E8;            // 0xE8
    u32   field_EC;            // 0xEC
    u32   field_F0;            // 0xF0
    u32   field_F4;            // 0xF4
    u32   field_F8;            // 0xF8
    u32   field_FC;            // 0xFC
    u32   field_100;           // 0x100
    u32   field_104;           // 0x104
    u32   field_108;           // 0x108
    u32   field_10C;           // 0x10C
    u32   field_110;           // 0x110
    u32   field_114;           // 0x114
    u32   field_118;           // 0x118
    u32   field_11C;           // 0x11C
    u32   field_120;           // 0x120
    u32   field_124;           // 0x124
    u32   field_128;           // 0x128
    u32   field_12C;           // 0x12C
    u32   field_130;           // 0x130
    u32   field_134;           // 0x134
    u32   field_138;           // 0x138
    u32   field_13C;           // 0x13C
    u32   field_140;           // 0x140
    u32   field_144;           // 0x144
    u32   field_148;           // 0x148
    u32   field_14C;           // 0x14C
    u32   field_150;           // 0x150
    u32   field_154;           // 0x154
    u32   field_158;           // 0x158
    u32   field_15C;           // 0x15C
    u32   field_160;           // 0x160
    u32   field_164;           // 0x164
    u32   field_168;           // 0x168
    u32   field_16C;           // 0x16C
    u32   field_170;           // 0x170
    u32   field_174;           // 0x174
    u32   field_178;           // 0x178
    u32   field_17C;           // 0x17C
    u32   field_180;           // 0x180
    u32   field_184;           // 0x184
    u32   field_188;           // 0x188
    u32   field_18C;           // 0x18C
    u32   field_190;           // 0x190
    u32   field_194;           // 0x194
    u32   field_198;           // 0x198
    u32   field_19C;           // 0x19C
    u32   field_1A0;           // 0x1A0
    u32   field_1A4;           // 0x1A4
    u32   field_1A8;           // 0x1A8
    u32   field_1AC;           // 0x1AC
    u32   field_1B0;           // 0x1B0
    u32   field_1B4;           // 0x1B4
    u32   field_1B8;           // 0x1B8
    u32   field_1BC;           // 0x1BC
    u32   field_1C0;           // 0x1C0
    u32   field_1C4;           // 0x1C4
    u32   field_1C8;           // 0x1C8
    u32   field_1CC;           // 0x1CC
    u32   field_1D0;           // 0x1D0
    u32   field_1D4;           // 0x1D4
    u32   field_1D8;           // 0x1D8
    u32   field_1DC;           // 0x1DC
    u32   field_1E0;           // 0x1E0
    u32   field_1E4;           // 0x1E4
    u32   field_1E8;           // 0x1E8
    u32   field_1EC;           // 0x1EC
    u32   field_1F0;           // 0x1F0
    u32   field_1F4;           // 0x1F4
    u32   field_1F8;           // 0x1F8
    u32   field_1FC;           // 0x1FC
    u32   field_200;           // 0x200
    u32   field_204;           // 0x204
    u32   field_208;           // 0x208
    u32   field_20C;           // 0x20C
    u32   field_210;           // 0x210
    u32   field_214;           // 0x214
    u32   field_218;           // 0x218
    u32   field_21C;           // 0x21C
    u32   field_220;           // 0x220
    u32   field_224;           // 0x224
    u32   field_228;           // 0x228
    u32   field_22C;           // 0x22C
    u32   field_230;           // 0x230
    u32   field_234;           // 0x234
    u32   field_238;           // 0x238
    u32   field_23C;           // 0x23C
    u32   field_240;           // 0x240
    u32   field_244;           // 0x244
    u32   field_248;           // 0x248
    u32   field_24C;           // 0x24C
    u32   field_250;           // 0x250
    u32   field_254;           // 0x254
    u32   field_258;           // 0x258
    u32   field_25C;           // 0x25C
    u32   field_260;           // 0x260
    u32   field_264;           // 0x264
    u32   field_268;           // 0x268
    u32   field_26C;           // 0x26C
    u32   field_270;           // 0x270
    u32   field_274;           // 0x274
    u32   field_278;           // 0x278
    u32   field_27C;           // 0x27C
    u32   field_280;           // 0x280
    u32   field_284;           // 0x284
    u32   field_288;           // 0x288
    u32   field_28C;           // 0x28C
    u32   field_290;           // 0x290
    u32   field_294;           // 0x294
    u32   field_298;           // 0x298
    u32   field_29C;           // 0x29C
    u32   field_2A0;           // 0x2A0
    u32   field_2A4;           // 0x2A4
    u32   field_2A8;           // 0x2A8
    u32   field_2AC;           // 0x2AC
    u32   field_2B0;           // 0x2B0
    u32   field_2B4;           // 0x2B4
    u32   field_2B8;           // 0x2B8
    u32   field_2BC;           // 0x2BC
    u32   field_2C0;           // 0x2C0
    u32   field_2C4;           // 0x2C4
    u32   field_2C8;           // 0x2C8
    u32   field_2CC;           // 0x2CC
    u32   field_2D0;           // 0x2D0
    u32   field_2D4;           // 0x2D4
    u32   field_2D8;           // 0x2D8
    u32   field_2DC;           // 0x2DC
    u32   field_2E0;           // 0x2E0
    u32   field_2E4;           // 0x2E4
    u32   field_2E8;           // 0x2E8
    u32   field_2EC;           // 0x2EC
    u32   field_2F0;           // 0x2F0
    u32   field_2F4;           // 0x2F4
    u32   field_2F8;           // 0x2F8
    u32   field_2FC;           // 0x2FC
    u32   field_300;           // 0x300
    u32   field_304;           // 0x304
    u32   field_308;           // 0x308
    u32   field_30C;           // 0x30C
    u32   field_310;           // 0x310
    u32   field_314;           // 0x314
    u32   field_318;           // 0x318
    u32   field_31C;           // 0x31C
    u32   field_320;           // 0x320 - Frame counter low
    u32   field_324;           // 0x324 - Frame counter high
    u32   field_328;           // 0x328
    u32   field_32C;           // 0x32C
    void* vtable_ptr;          // 0x330 - Vtable for method calls
};

struct CState {
    u32   state_id;            // 0x0
    u32   field_4;             // 0x4
    u32   field_8;             // 0x8
    u32   field_C;             // 0xC - Sub-state counter
    float field_10;            // 0x10 - Timer
    float field_14;            // 0x14 - Delta time
    u32   field_18;            // 0x18
    u8    field_1C[0x64];      // 0x1C - Padding/data
};

struct CMenuGlobalState {
    u8    field_0;             // 0x0
    u8    field_1;             // 0x1
    u8    field_2;             // 0x2
    u8    field_3;             // 0x3
    CMenuPokemonCursor pokemonCursor;  // 0xC
    u8    padding[0x154];      // Padding to offset 0x160
    CState state;              // 0x160
};

/* External function declarations */
u32 soundGetBGMID();
u32 soundGetEnvID();
void soundGetVolume(u32 id);
void soundOpenPlay(u32 id, u32 type, u8 volume);
void soundOpenPlayEnv(u32 id, u32 type, u8 volume);
void GSsndPlayNow(u32 seId);

void pokemonCreate(Pokemon* pkmn, u16 species, u32 flags);
void pokemonSetDarkPokemonStatus(Pokemon* pkmn);
void* pokemonBiosGetInitDp(Pokemon* pkmn);
void setDarkPoint__7PokemonFf(Pokemon* pkmn, float dp);
void* darkPokemonGetDarkPokemon(u16 species);
u16 getPokemonID__11DarkPokemonCFv(void* darkPkmn);
void setStatus__11DarkPokemonF17darkPokemonStatus(void* darkPkmn, u32 status);
void setSnatchIndex__11DarkPokemonFUc(void* darkPkmn, u8 index);
u32 gamedataGetStatus(u32 group, u32 index);
void pokemonInit(Pokemon* pkmn);
u32 checkValid__7PokemonCFv(const Pokemon* pkmn);

void GSthreadSwitch();
void GSmodelGetBound(GSmodel*, GSbound*);
void GSboundGetSize(GSbound*, float* size);
void* Sequence_GetGSmodel(u32 seqId);
u32 Sequence_GetModelSize(u32 seqId);
void memoGetScaleAngle(u32 memoId, float* scale, float* angle);

u32 windowGetKeyTrg();
u32 windowGetKeyOn();
u32 windowGetActiveID();
void* windowSearchID(u32 id);
void windowCloseMain(u32 id);
void windowDrawSprite(u32 spriteId, s32 x, s32 y, s32 w, s32 h, u32 color);
void windowDrawSprite2(u32 spriteId, s32 x, s32 y, s32 w, s32 h, u32 color, u32 flags, u32 alpha);
void* menuSpriteBiosGetPtr(u16 spriteId);
void* menuSpriteBiosGetValPtr(void* sprite);
void* menuDataBiosGetPtr(u32 dataId);
void* menuItemBiosGetPtr(u32 menuId, u32 itemId);
void menuOpenCustom(u32 menuId, u32 parentId, s32 x, s32 y, u32 flags);
void menuSetDisp(u32 menuId, u32 disp);
void menuPtWindowWorkDraw__Fl(long menuId);
void menuPtWindowWorkDraw__FP14tagWINDOW_WORK(tagWINDOW_WORK* win);
void menuPtWindowWorkDrawPrime__FP14tagWINDOW_WORK(tagWINDOW_WORK* win);
void menuPtMenuLoad__Fl(long menuId);
void menuPtSpriteDraw__FUsll(u16 spriteId, long x, long y);
void menuPtSpriteDrawColor__FUsllUl(u16 spriteId, long x, long y, u32 color);
void menuPtSpriteDrawColor__FUsllllUl(u16 spriteId, long x, long y, long w, long h, u32 color);
void menuPtSpriteDrawCenterColor__FUsllUl(u16 spriteId, long x, long y, u32 color);
void menuPtSpriteDrawAndRollScale__FUsUlffff(u16 spriteId, u32 color, float x, float y, float w, float h);
void menuPtItemDrawAlpha__FP13MENU_ITEM_dd_Uc(MENU_ITEM* item, s32 x, s32 y, u8 alpha);
void menuPtItemDrawOffset__FP13MENU_ITEM_dd_ll(MENU_ITEM* item, s32 x, s32 y, long ox, long oy);
void menuPtItemDrawOffsetXWColor__FP13MENU_ITEM_dd_llUl(MENU_ITEM* item, s32 x, s32 y, long ox, long oy, u32 color);
void menuPtSpriteWorkSetWidthRateColor__FP14tagWINDOW_WORKUllf11GSgfxColAu8(tagWINDOW_WORK* win, u32 menuId, long itemId, float rate, GSgfxColAu8 color);
void menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKP14tagSPRITE_WORKb(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, u32 sw);
void menuPtSpriteWorkSetSw__FP14tagWINDOW_WORKUllb(tagWINDOW_WORK* win, u32 menuId, long x, long y, u32 sw);
void menuPtSpriteWorkSetSpriteId__FP14tagSPRITE_WORKUl(tagSPRITE_WORK* sprite, u32 id);
void menuPtSpriteWorkSetMenuSprite__FP14tagSPRITE_WORKP15MENU_SPRITE_dd(tagSPRITE_WORK* sprite, MENU_SPRITE* menuSprite, s32 x, s32 y);
void menuPtSpriteWorkSetMenuItem__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, u32 id);
void* menuPtGetSpriteWorkByHookFunction__FP14tagWINDOW_WORKPvUll(tagWINDOW_WORK* win, void* hook, u32 menuId, long x, long y);
void* menuPtItemGetBySpriteWork__FP14tagWINDOW_WORKP14tagSPRITE_WORK(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite);
u32 menuPtSpriteWorkGetIndexFromId__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite, u32 id);
void* menuPtSpriteWorkGetByItemID__FP14tagWINDOW_WORKUll(tagWINDOW_WORK* win, u32 menuId, long itemId);
void* menuPtSpriteWorkGetByItemID__FlUll(long menuId, u32 itemId, u32, u32);
void menuPtSpriteWorkSetMsgId__FlUllUl(long menuId, u32 itemId, u32, u32 msgId);
GSgfxColAu8 GSgfxColAu8To32__F11GSgfxColAu8(GSgfxColAu8 color);

void spriteSetScissor(GSgfxLayerID id, s16 x, s16 y, s16 w, s16 h);
void spriteSetEnv(GSgfxLayerID id, u32 env);
void spriteSetOffset(GSgfxLayerID id, s16 x, s16 y);
void spriteClearScissor(GSgfxLayerID id);
void spriteClearEnv(GSgfxLayerID id);
void winSpriteDraw(void* win, void* sprite);
u32 winSpriteGetLayerID(void* win, void* sprite);
void winSpriteSetDisp(void* sprite, u32 disp);
u32 winSpriteGetDisp(void* sprite);

void GSgfxLayerSetActive(u32 layerId);
u32 GSgfxVideoGetVsyncRate();
void GSprimSetQuadVertexOrder(u32 order);
void GSprimDraw2DQuad4V(void* xy, void* st, u32 color, u32* flags);
void GSprimDraw2DTexQuad4V(void* xy, void* st, u32 color, u32* flags);
void GSprimDraw2DPixelListC(u32* pixels, u32* colors, u32 count);
void GSprimSetBlendMode(u32 mode);
void GSresGetResourceAllGroup(u32 groupId);
u32 GStextureGetXsize(void* texture);
u32 GStextureGetYsize(void* texture);

void GSmsgExec(u32 msgId, u32 x, u32 y);
void GSmsgKill(u32 msgId);
u32 GSmsgIsCheck(u32 msgId);
void GSmsgPrint2(u32 layerId, s32 x, s32 y, u32 color, u32 msgId);
void GSmsgMain(u32 flags);
void msgctrlSetValue(u32 ctrlId, u32 value);

u32 timeGetLastFrameSec();
u32 timeGetLastFrameTime();
void fadeSetToBlackOutIfNotBlack(float time);
void fadeSetToBlackInIfBlack(float time);
void fadeSet(u32 type, float time);
u32 fadeCheck(u32 type);
u32 floorGetMenuLayerID();

void init__4CAntFv(CAnt* ant);
void initByPokemonAndSetColorAnimationInAny__4CAntFP7Pokemon(CAnt* ant, Pokemon* pkmn);
void setAnimation__4CAntFl(CAnt* ant, long animId);
void drawAndUpdate__4CAntFv(CAnt* ant);
void drawAndUpdate__4CAntF12PocketVecs(CAnt* ant, PocketVec<s>* vec);

void menuSubOpenSelect(u32 flags, int param1, long param2, long param3, long param4);
void tutorialManage__9CMetaMenuFv(CMetaMenu* menu);
void tutorialManageUpdate__9CMetaMenuFv(CMetaMenu* menu);

/* Static variables */
static u32 _darkPokemonIndex;
static u8 init$2678;
static float multi$2677;
static s16 defaultPositionTbl__18CMenuPokemonCursor[2];
static CMetaMenu* pCurrentMenu__9CMetaMenu;
static CMetaMenu* _pThis;
static u32 _selectItemQuantity;
static u32 darkPokemonList_number;

/* Static function declarations */
static u16 pokemonindex__Fi(int index);
static void _tutorialWindowCursorFunc__FP14tagWINDOW_WORK(tagWINDOW_WORK* win);
static void _tutorialWindowButtonFunc__FP14tagWINDOW_WORK(tagWINDOW_WORK* win);

/* 0x8001EC10 | size: 0x80 */
void menuPtRestoreSound__FP15MenuPtWorkSound(MenuPtWorkSound* sound) {
    if (sound->bgmId != 0) {
        u32 currentBgm = soundGetBGMID();
        if (currentBgm != sound->bgmId) {
            soundOpenPlay(sound->bgmId, 0x32, sound->bgmVolume);
        }
    }
    if (sound->envId != 0) {
        u32 currentEnv = soundGetEnvID();
        if (currentEnv != sound->envId) {
            soundOpenPlayEnv(sound->envId, 0x32, sound->envVolume);
        }
    }
}

/* 0x8001EC90 | size: 0x90 */
void menuPtSaveSound__FP15MenuPtWorkSound(MenuPtWorkSound* sound) {
    u32 bgmId = soundGetBGMID();
    u8 bgmVol = 0;
    if (bgmId != 0) {
        soundGetVolume(bgmId);
        bgmVol = (u8)r3;
    }
    u32 envId = soundGetEnvID();
    u8 envVol = 0;
    if (envId != 0) {
        soundGetVolume(envId);
        envVol = (u8)r3;
    }
    sound->bgmId = bgmId;
    sound->envId = envId;
    sound->bgmVolume = bgmVol;
    sound->envVolume = envVol;
}

/* 0x8001ED20 | size: 0xA0 */
void menuPtStopSound__FP15MenuPtWorkSound(MenuPtWorkSound* sound) {
    u32 bgmId = soundGetBGMID();
    u8 bgmVol = 0;
    if (bgmId != 0) {
        soundGetVolume(bgmId);
        bgmVol = (u8)r3;
        soundOpenPlay(bgmId, 0x32, 0xFF);
    }
    u32 envId = soundGetEnvID();
    u8 envVol = 0;
    if (envId != 0) {
        soundGetVolume(envId);
        envVol = (u8)r3;
    }
    sound->bgmId = bgmId;
    sound->envId = envId;
    sound->bgmVolume = bgmVol;
    sound->envVolume = envVol;
}

/* 0x8001EDC0 | size: 0x34 */
void menuPocketButtonWait__Fv() {
    while (1) {
        GSthreadSwitch();
        u32 keys = windowGetKeyTrg();
        u16 aButton = (keys >> 26) & 3;
        if (aButton != 0) break;
    }
}

/* 0x8001EDF4 | size: 0x13C */
float menuGetPokemonScale__FUli(u32 seqId, int modelSize) {
    GSmodel* model = Sequence_GetGSmodel(seqId);
    int size = Sequence_GetModelSize(seqId);
    
    float baseScale;
    switch (size) {
        case -2: baseScale = 0.5f; break;
        case -1: baseScale = 0.75f; break;
        case 0:  baseScale = 1.0f; break;
        case 1:  baseScale = 1.25f; break;
        case 2:  baseScale = 1.5f; break;
        case 3:  baseScale = 1.75f; break;
        default: baseScale = 1.0f; break;
    }
    
    float scale, angle;
    memoGetScaleAngle(seqId, &scale, &angle);
