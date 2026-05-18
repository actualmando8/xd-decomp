// Decompiled from: menuFight.cpp
// Address range: 0x800178FC..0x8001EC10 | size: 0x7314
// PowerPC 750CL / Gekko (GameCube)
// Compiler: Metrowerks CodeWarrior

/*
  Battle menu system - handles all in-battle UI including:
  - Turn counter, timer, countdown
  - Target selection, cursor management
  - Pokémon status display (player and secret/shadow)
  - Move (Waza) selection, PP, type display
  - Ball throwing for Waza capture
  - Command messages
  - GBA connection during battle
  - Menu open/close sequences
  
  NOTE: This is a large file (71 functions, 8980 lines of assembly).
  Full decompilation of drawing functions deferred due to size.
  Function signatures and smaller functions completed.
*/

// Forward declarations
typedef struct tagWINDOW_WORK tagWINDOW_WORK;
typedef struct tagSPRITE_WORK tagSPRITE_WORK;
typedef struct Pokemon Pokemon;
typedef struct GSinputDevice GSinputDevice;
typedef struct FIGHT_TRAINER FIGHT_TRAINER;

// MENU_WAZA_STATUS structure (inferred from usage)
typedef struct MENU_WAZA_STATUS {
    u16 field_0x00;
    u16 field_0x02;
    // ... more fields
} MENU_WAZA_STATUS;

// External function declarations
s32     fightFloor_GetTurnCount(void);
void    msgctrlSetValue(s32 id, s32 value);
void    GSmsgPrint2(void* msg, s16 x, s16 y, s16 z);
void    winSpriteSetDisp(tagSPRITE_WORK* sprite, s32 disp);
void    winSetSequence(tagSPRITE_WORK* sprite, s32 seq);
void    winSeqSetMenu(s32 seqId, s32 param);
s32     menuGetLastTime(void);
float   timeGetLastFrameSec(void);
void    GSthreadSwitch(void);
void    GSsndPlayNow(s32 id);
s32     menuIsCheck(s32 id);
void*   windowGetKeyInfo(void);
void    menuOpen(s32 id, s32 param);
s32     menuCloseCustom(s32 id, s32 param0, s32 param1);
void    menuClose(s32 id);
void    menuCloseSync(s32 id, s32 param);
s32     menuGetStatus(void);
void    menuSetStatus(s32 status);
s32     menuFightChkSeq(s32 seq);
void    menuFightSetSeq(s32 seq);
void    menuFightSetSeqOut(void);
s32     menuFightGetKeyWaitMenuId(void);
void    menuFightCloseAll(void);
s32     isImasugu(void);
void    menuPokemonCheckPokemonChange(void);
void    menuFightOpenGBAMain(void);
void    menuFightOpenGBAIrekae(void);
void    menuFightCloseTarget(void);
void    menuFightOpenTarget(void);
void    menuFightOpenPokemon(void);
void    menuFightCloseWaza(void);
void    menuFightOpenWaza(void);
void    menuFightCloseTop(void);
void    menuFightOpenTop(void);
s32     menuFightChkOpenBall(void);
void    floorEventExecScript(s32 event, s32 param);
Pokemon* pokemonGetPtr(s32 index);
s32     pokemonGetWaza(Pokemon* poke, s32 index);
s32     pokemonGetWazaPP(Pokemon* poke, s32 index);
s32     pokemonGetMaxPP(Pokemon* poke, s32 index);
s32     wazaGetNo(s32 wazaId);
s32     wazaGetType(s32 wazaId);
s32     pokecoloGetRomVersion(void);

// ============================================================================
// Global data
// ============================================================================

// SDA globals
static u32  lbl_804E7EB8 = 0x3C;
static u32  lbl_804E7EBC = 0x0D;
static u32  oldKeyInfo;
static u16  menu_item_waza_tbl[4] = { 0x0110, 0x0112, 0x0114, 0x0116 };
static u32  waza_no$2832[2] = { 0xFFFFFFFF, 0xFFFFFFFF };

// SBSS globals
static u32  menuFightStatus;
static u32  waza_no$3039;
static u8   init$3040;
static u32  pokemon_no$3245;
static u8   init$3246;
static u32  oldTime$3906;
static u8   init$3907;

// ROData constants
static const float const_0_5    = 0.5f;
static const float const_0      = 0.0f;
static const float const_pi_4   = 0.7853982f;   // pi/4
static const float const_3pi_4  = 2.3561945f;   // 3pi/4
static const double const_dbl1  = 4503601774854144.0;
static const float const_8      = 8.0f;
static const float const_50     = 50.0f;
static const double const_dbl2  = 4503599627370496.0;  // 2^52
static const float const_2_5    = 2.5f;

// ============================================================================
// Drawing functions (stubs - full decompilation deferred)
// ============================================================================

/*
  Address: 0x800178FC | size: 0x168
  menuFightDrawTurn(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws turn counter display. Dispatches based on sprite item ID.
  Item IDs: 0x2 = turn count, 0x27c-0x27e = turn-related, 0x295,0x297 = special
*/
void menuFightDrawTurn(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    s16 id = sprite->field_0x6;
    if (id == 2) {
        s32 turn = fightFloor_GetTurnCount();
        msgctrlSetValue(0x5f, turn & 0xFFFF);
        // ... draw turn number
    }
    // TODO: Complete dispatch for item IDs 0x27c-0x297, 0x2d3-0x2d5
}

/*
  Address: after menuFightDrawTurn
  menuFightDrawKane(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws "kane" (bell/chime) display elements.
*/
void menuFightDrawKane(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  getKane() - local helper
  Gets current kane state.
*/
static s32 getKane(void) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightDrawTimer(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws battle timer display.
*/
void menuFightDrawTimer(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightCtrlTimer()
  Controls timer logic (start/stop/update).
*/
void menuFightCtrlTimer(void) {
    // TODO: Full decompilation
}

/*
  menuFightButtonTimeOutCheck()
  Checks for button timeout conditions.
*/
void menuFightButtonTimeOutCheck(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseCheckTotalTimer()
  Checks total timer for close conditions.
*/
void menuFightCloseCheckTotalTimer(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseTotalTimer()
  Closes total timer display.
*/
void menuFightCloseTotalTimer(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenTotalTimer()
  Opens total timer display.
*/
void menuFightOpenTotalTimer(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseCheckCountDown()
  Checks countdown for close conditions.
*/
void menuFightCloseCheckCountDown(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseCountDown()
  Closes countdown display.
*/
void menuFightCloseCountDown(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenCountDown()
  Opens countdown display.
*/
void menuFightOpenCountDown(void) {
    // TODO: Full decompilation
}

/*
  menuFightButtonSecretKousan()
  Handles secret operation button input.
*/
void menuFightButtonSecretKousan(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenTimeup()
  Opens time-up display.
*/
void menuFightOpenTimeup(void) {
    // TODO: Full decompilation
}

/*
  menuFightDrawTargetSecret(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret target selection.
*/
void menuFightDrawTargetSecret(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightButtonTargetSecret()
  Handles secret target button input.
*/
void menuFightButtonTargetSecret(void) {
    // TODO: Full decompilation
}

/*
  menuFightDrawTargetCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws target selection cursor.
*/
void menuFightDrawTargetCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightCtrlTarget()
  Controls target selection logic.
*/
void menuFightCtrlTarget(void) {
    // TODO: Full decompilation
}

/*
  menuFightDrawIPokemonStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws player Pokémon status in battle.
*/
void menuFightDrawIPokemonStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawIwaitStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws wait status display.
*/
void menuFightDrawIwaitStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  _menuFightDrawIwaitStatusWaza(tagWINDOW_WORK*, tagSPRITE_WORK*, Pokemon*, u8, u32)
  Draws wait status with move information.
*/
static void _menuFightDrawIwaitStatusWaza(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite,
                                           Pokemon* poke, u8 slot, u32 flags) {
    // TODO: Full decompilation
}

/*
  menuFightDrawTargetI(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws player target selection.
*/
void menuFightDrawTargetI(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawSecretPokemonStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret/shadow Pokémon status.
*/
void menuFightDrawSecretPokemonStatus(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawSecretPokemon(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret Pokémon selection.
*/
void menuFightDrawSecretPokemon(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightButtonSecretPokemonTop()
  Handles secret Pokémon top button input.
*/
void menuFightButtonSecretPokemonTop(void) {
    // TODO: Full decompilation
}

/*
  menuFightCtrlSecretPokemonTop()
  Controls secret Pokémon top menu.
*/
void menuFightCtrlSecretPokemonTop(void) {
    // TODO: Full decompilation
}

/*
  menuFightDrawSecretSelect(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret selection menu.
*/
void menuFightDrawSecretSelect(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  _menuFightGetPokemonPtr(FIGHT_TRAINER*, u32)
  Gets Pokémon pointer from trainer data.
*/
static Pokemon* _menuFightGetPokemonPtr(FIGHT_TRAINER* trainer, u32 index) {
    // TODO: Full decompilation
    return NULL;
}

/*
  menuFightDrawSecretWazaDoc(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret move documentation.
*/
void menuFightDrawSecretWazaDoc(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawSecretWazaSelect(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws secret move selection. Uses jump table @4959.
*/
void menuFightDrawSecretWazaSelect(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation - uses jump table with 5 targets
}

/*
  menuFightButtonSecretWazaTop()
  Handles secret move top button input.
*/
void menuFightButtonSecretWazaTop(void) {
    // TODO: Full decompilation
}

/*
  menuFightButtonIwaza1p()
  Handles 1P move button input.
*/
void menuFightButtonIwaza1p(void) {
    // TODO: Full decompilation
}

/*
  menuFightCurIkousan()
  Current player operation handler.
*/
void menuFightCurIkousan(void) {
    // TODO: Full decompilation
}

/*
  menuFightCtrlSecretWazaTop()
  Controls secret move top menu.
*/
void menuFightCtrlSecretWazaTop(void) {
    // TODO: Full decompilation
}

/*
  menuFightButtonSecretMain()
  Handles secret main button input.
*/
void menuFightButtonSecretMain(void) {
    // TODO: Full decompilation
}

/*
  menuFightCtrlSecretMain()
  Controls secret main menu.
*/
void menuFightCtrlSecretMain(void) {
    // TODO: Full decompilation
}

/*
  menuFightDrawBall(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws ball throwing animation. Uses jump table @5374 (28 entries).
*/
void menuFightDrawBall(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation - large jump table for ball states
}

/*
  menuFightCtrlBall()
  Controls ball throwing logic.
*/
void menuFightCtrlBall(void) {
    // TODO: Full decompilation
}

/*
  _menuFightIsUse(MENU_WAZA_STATUS*, u16)
  Checks if a move can be used.
*/
static s32 _menuFightIsUse(MENU_WAZA_STATUS* status, u16 wazaId) {
    // TODO: Full decompilation
    return 1;
}

/*
  menuFightDrawPP(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws PP display for moves.
*/
void menuFightDrawPP(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawType(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws type display for moves.
*/
void menuFightDrawType(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawWaza(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws move name selection. Uses jump table @5493 (8 entries).
*/
void menuFightDrawWaza(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation - jump table for move types
}

/*
  menuFightDrawNew(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws new move indicator.
*/
void menuFightDrawNew(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation
}

/*
  menuFightDrawCmdMsg(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite)
  Draws command messages. Uses jump table @5529 (26 entries).
*/
void menuFightDrawCmdMsg(tagWINDOW_WORK* win, tagSPRITE_WORK* sprite) {
    // TODO: Full decompilation - large jump table for command types
}

/*
  menuFightWazaButton()
  Handles move selection button input.
*/
void menuFightWazaButton(void) {
    // TODO: Full decompilation
}

/*
  menuFightWazaCtrl()
  Controls move selection menu. Uses jump table @5602 (7 entries).
*/
void menuFightWazaCtrl(void) {
    // TODO: Full decompilation
}

/*
  menuFightMainCtrl()
  Main battle menu controller. Uses jump table @5650 (7 entries).
*/
void menuFightMainCtrl(void) {
    // TODO: Full decompilation
}

/*
  _menuFightGetRightStickInfo(f, bool)
  Gets right stick input information.
*/
static s32 _menuFightGetRightStickInfo(float f, s32 flag) {
    // TODO: Full decompilation
    return 0;
}

/*
  _menuFightGetLeftKeyInfo(f)
  Gets left key input information.
*/
static s32 _menuFightGetLeftKeyInfo(float f) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightOpenGBAMain()
  Opens GBA menu during battle.
*/
void menuFightOpenGBAMain(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenGBAIrekae()
  Opens GBA replacement menu.
*/
void menuFightOpenGBAIrekae(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseTarget()
  Closes target selection menu.
*/
void menuFightCloseTarget(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenTarget()
  Opens target selection menu.
*/
void menuFightOpenTarget(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenPokemon()
  Opens Pokémon selection menu.
*/
void menuFightOpenPokemon(void) {
    // TODO: Full decompilation
}

/*
  menuFightCloseWaza()
  Closes move selection menu.
*/
void menuFightCloseWaza(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenWaza()
  Opens move selection menu.
*/
void menuFightOpenWaza(void) {
    // TODO: Full decompilation
}

/*
  chkWazaNew(MENU_WAZA_STATUS*, u8)
  Checks if a move is new.
*/
static s32 chkWazaNew(MENU_WAZA_STATUS* status, u8 slot) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightCloseTop()
  Closes top battle menu.
*/
void menuFightCloseTop(void) {
    // TODO: Full decompilation
}

/*
  menuFightOpenTop()
  Opens top battle menu.
*/
void menuFightOpenTop(void) {
    // TODO: Full decompilation
}

/*
  _menuFightKeyWait(GSinputDevice*)
  Waits for key input from device.
*/
static void _menuFightKeyWait(GSinputDevice* device) {
    // TODO: Full decompilation
}

/*
  _menuFightCheckTimeOut()
  Checks for timeout conditions.
*/
static s32 _menuFightCheckTimeOut(void) {
    // TODO: Full decompilation
    return 0;
}

/*
  isImasugu()
  Checks if immediate action is available.
*/
s32 isImasugu(void) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightGetKeyWaitMenuId()
  Gets the menu ID for key wait.
*/
s32 menuFightGetKeyWaitMenuId(void) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightCloseAll()
  Closes all battle menus.
*/
void menuFightCloseAll(void) {
    // TODO: Full decompilation
}

/*
  menuFightSetSeqOut()
  Sets sequence output.
*/
void menuFightSetSeqOut(void) {
    // TODO: Full decompilation
}

/*
  menuFightSetSeq(s32 seq)
  Sets battle sequence.
*/
void menuFightSetSeq(s32 seq) {
    // TODO: Full decompilation
}

/*
  menuFightChkSeq(s32 seq)
  Checks battle sequence.
*/
s32 menuFightChkSeq(s32 seq) {
    // TODO: Full decompilation
    return 0;
}

/*
  menuFightSetStatus(s32 status)
  Sets battle menu status.
*/
void menuFightSetStatus(s32 status) {
    menuFightStatus = status;
}

/*
  menuFightGetStatus()
  Gets battle menu status.
*/
s32 menuFightGetStatus(void) {
    return menuFightStatus;
}

/*
  menuFightChkOpenBall()
  Checks if ball throwing is open.
*/
s32 menuFightChkOpenBall(void) {
    // TODO: Full decompilation
    return 0;
}
