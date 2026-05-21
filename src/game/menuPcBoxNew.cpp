// Decompilation of menuPcBoxNew.cpp (0x80068264..0x80069300, size: 0x109C)
// Pokémon XD: Gale of Darkness - PC Box Menu (Revised)
// Handles PC Box selection, Relive Hall access, Hologroom Suite, and tutorial modes
//
// Key functions:
//   loop()  - 0x788 bytes at 0x80068814, state machine with jump table dispatch
//   main()  - 0x33C bytes at 0x80068F9C, initialization based on callFrom parameter

#include "global.h"
#include "libc/stddef.h"
#include "libc/stdint.h"
#include "libc/string.h"

// ==================== Forward Declarations ====================

struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct CMetaMenu;
struct CMenuGlobalState;
struct Pokemon;
struct MenuPtWorkSound;

// External function declarations
void systemInit__4CAntFv(void);
void systemFree__4CAntFv(void);
void init__6CStateFv(void);
void update__6CStateFv(void);
void init__16CMenuGlobalStateFv(void);
void *getPointer__11CReliveHallFv(void);
void allocMakeBackup__11CReliveHallFv(void);
void checkWithBackupSet__11CReliveHallFv(void);
int isOpen__11CReliveHallFv(void);
void init__11CReliveHallFv(void);
u32 relivehallGetLastViewStage__Fv(void);
void relivehallSetLastViewStage__Fl(u32);
void *getPointer__5PCBOXFv(void);
void init__5PCBOXFv(void);
void setPokemon__5PCBOXFP7PokemonScSc(struct Pokemon*, s8, s8, s8);
u32 menuPcBoxGetLastViewBox__Fv(void);
void menuPcBoxSetLastViewBox__Fl(u32);
void *menuPcBoxDouguHikidashi__F31MENU_PCBOX_DOUGU_HIKIDASHI_MODE(u32);
void menuReliveHallExecFromPcBox__FR16CMenuGlobalState(struct CMenuGlobalState*);
void menuHologramExecFromPcBox__FR16CMenuGlobalState(struct CMenuGlobalState*);
void menuPcBoxPokemon__FR16CMenuGlobalState(struct CMenuGlobalState*);
void menuPtPlaySe__FUl(u32);
void menuPtPlayBgm__FUl(u32);
void menuPtSaveSound__FP15MenuPtWorkSound(struct MenuPtWorkSound*);
void menuPtRestoreSound__FP15MenuPtWorkSound(struct MenuPtWorkSound*);
void menuPtSpriteWorkSetMenuItem__FP14tagWINDOW_WORKP14tagSPRITE_WORKUl(struct tagWINDOW_WORK*, struct tagSPRITE_WORK*, u32);
void localWindowSetTable__9CMetaMenuFPl(struct CMetaMenu*, void*);
void localWindowCreateAll__9CMetaMenuFv(void);
void localWindowDeleteAll__9CMetaMenuFv(void);
void systemFadeInKick__9CMetaMenuFv(void);
void systemFadeOutSetAndWait__9CMetaMenuFf(float);
void systemFadeWaitToEnd__9CMetaMenuFv(void);
void menuOpen(u32, u32);
void menuClose(u32);
void menuCloseSync(u32, u32);
void menuOpenCustom(u32, u32, u32, u32, u32, u32, u32);
u32 windowSearchID(u32);
u32 windowGetActiveID(void);
u32 windowGetValue(u32);
void winSeqSetMenu(u32, u32);
void winSpriteSetDisp(struct tagSPRITE_WORK*, u32);
void GSfsysReadWait(u32);
void GSfsysFree(u32);
void GSresFreeGroup(u32);
void GSfloorPop(void);
void *savedataGetStatus(u32, u32);
void *memcardMemAllocForSavedata(void);
void *memcardMemFreeForSavedata(void*);
void pokemonCreate(struct Pokemon*, u16, u32);
void menuPocketSetDarkPokemon__FR7PokemonfUs(struct Pokemon*, float, u16);
void gamedataGetStatus(u32, u32, void*);
void *menuPocket2Call(u32, u32, u32);

// ==================== Constants ====================

static const float FADE_NORMAL = 0.5f;
static const float FADE_REVERSE = -1.0f;

// Window IDs
static const u32 WINDOW_PCBOX = 0x79;
static const u32 WINDOW_POCKET = 0x8A;

// Resource IDs
static const u32 RESOURCE_PCBOX = 0x16;
static const u32 RESOURCE_RELIVE_HALL = 0x824;
static const u32 RESOURCE_POCKET = 0x66F;

// Menu sequence IDs
static const u32 MENU_SEQ_PCBOX_MAIN = 0x1C4;
static const u32 MENU_SEQ_PCBOX_EXIT = 0x1C8;

// Menu item IDs from _selectMenuTbl
static const u32 ITEM_PCBOX_PREV = 0x3B70;
static const u32 ITEM_PCBOX_NEXT = 0x3BB1;
static const u32 ITEM_PCBOX_SELECT = 0x3BB2;
static const u32 ITEM_PCBOX_RELIVE = 0x3BB4;
static const u32 ITEM_PCBOX_HOLOGRAM = 0x3BB6;
static const u32 ITEM_PCBOX_DOUGU_0 = 0x3BB7;
static const u32 ITEM_PCBOX_DOUGU_1 = 0x3BB8;
static const u32 ITEM_PCBOX_DOUGU_2 = 0x3BB9;
static const u32 ITEM_PCBOX_DOUGU_3 = 0x3BBA;

// State IDs
enum PcBoxState {
    STATE_IDLE = 0,
    STATE_1 = 1,
    STATE_2 = 2,
    STATE_3 = 3,
    STATE_4 = 4,
    STATE_5 = 5,
    STATE_6 = 6,
    STATE_7 = 7,
    STATE_8 = 8,
    STATE_9 = 9,
    STATE_A = 10,
    STATE_B = 11,
};

// enumCallFrom values
enum EnumCallFrom {
    CALLFROM_NORMAL = 0,
    CALLFROM_RELIVE_HALL = 1,
    CALLFROM_HOLOGRAM = 2,
    CALLFROM_RELIVE_HALL_TUTORIAL = 3,
    CALLFROM_TUTORIAL = 4,
};

// ==================== Data Tables ====================

// Pokemon species for tutorial (18 Pokemon)
static const u16 _pokemonTbl[] = {
    0x014A, 0x0173, 0x0141, 0x0148, 0x0132, 0x0151,
    0x015A, 0x014F, 0x016F, 0x014C, 0x0130, 0x015F,
    0x0122, 0x0140, 0x0169, 0x018B, 0x0178, 0x0163
};

// Dark Pokemon markers (index 2 onwards are Dark Pokemon)
static const u16 _darkPokemonTbl[] = {
    0x000A, 0x0001
};

// ==================== Global State (BSS) ====================

// _menuGlobalState: 0x208 bytes at 0x804355E0
// _menuPcBox: 0x358 bytes at 0x804357E8
// localWindowTable: 4 bytes at 0x804E7FD8

// ==================== Wrapper Functions ====================

/* 0x80068264 | size: 0x10 */
// Returns the cancel exit flag from global state
u8 menuReliveHallTutorialGetIsCancelExit__Fv(void);

/* 0x80068274 | size: 0x4 */
void menuReliveHallTutorialExit(void) {
}

/* 0x80068278 | size: 0x2C */
// Entry point for Relive Hall Tutorial mode
void menuReliveHallTutorialMain(void);

/* 0x800682A4 | size: 0x4 */
void menuReliveHallTutorialInit(void) {
}

/* 0x800682A8 | size: 0x4 */
void menuHologramExit(void) {
}

/* 0x800682AC | size: 0x2C */
// Entry point for Hologroom Suite mode
void menuHologramMain(void);

/* 0x800682D8 | size: 0x4 */
void menuHologramInit(void) {
}

/* 0x800682DC | size: 0x4 */
void menuReliveHallExit(void) {
}

/* 0x800682E0 | size: 0x2C */
// Entry point for Relive Hall mode
void menuReliveHallMain(void);

/* 0x8006830C | size: 0x4 */
void menuReliveHallInit(void) {
}

/* 0x80068310 | size: 0x4 */
void menuPcBoxExit(void) {
}

/* 0x80068314 | size: 0x2C */
// Main entry point for PC Box menu
void menuPcBoxMain(void);

/* 0x80068340 | size: 0x4 */
void menuPcBoxInit(void) {
}

/* 0x80068344 | size: 0x8 */
u32 menuPcBoxSelectMenuItem(void) {
    return 0;
}

/* 0x8006834C | size: 0x30 */
// Control handler - dispatches to ctrl() method
u32 menuPcBoxCtrl(struct tagWINDOW_WORK* work);

/* 0x8006837C | size: 0x38 */
// Draw callback for menu item 3
u32 menuPcBoxItem3(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800683B4 | size: 0x38 */
// Draw callback for menu item 2
u32 menuPcBoxItem2(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800683EC | size: 0x38 */
// Draw callback for menu item 1
u32 menuPcBoxItem1(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x80068424 | size: 0x38 */
// Draw callback for menu item 0
u32 menuPcBoxItem0(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x8006845C | size: 0x34 */
// Draw callback for info text
u32 menuPcBoxInfo(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x80068490 | size: 0x34 */
// Draw callback for title
u32 menuPcBoxTitle(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800684C4 | size: 0x38 */
// Draw callback for red bar 3
u32 menuPcBoxBarRed3(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x800684FC | size: 0x38 */
// Draw callback for red bar 2
u32 menuPcBoxBarRed2(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x80068534 | size: 0x38 */
// Draw callback for red bar 1
u32 menuPcBoxBarRed1(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);

/* 0x8006856C | size: 0x38 */
// Draw callback for red bar 0
u32 menuPcBoxBarRed0(struct tagWINDOW_WORK* work, struct tagSPRITE_WORK* sprite);
