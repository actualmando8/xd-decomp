// Decompiled from menuTop.cpp (0x8002F308 - 0x80030330)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// Total size: 0x1028 bytes
//
// This module implements the title screen menu for Pokémon XD.
// It handles menu selection, load/save detection, and transitions
// to new game, continue, and options screens.

#include "global.h"

// ============================================================================
// Forward declarations for external functions
// ============================================================================
extern void menuOpen(u32 menuId, u32 param);
extern void winSeqSetMenu(void* win, u32 seqId);
extern s32 menuModelCheck(void* model, u32 p1, u32 p2, u32 p3, u32 p4);
extern void menuModelSetSize(void* model, s16 w, s16 h, s16 x, s16 y);
extern void menuModelAdjustCamera(void* model);
extern void menuModelRender(void* model);
extern void menuModelSetAngle(void* model, f32 angle);
extern void menuModelSetZoom(void* model, f32 zoom);
extern u32 pokecoloGetRomVersion(void);
extern s32 menuTitleGetSelect(void);
extern void GSmsgPrint2(void* msgWin, u32 p1, s32 p2, u32 msgId, s16 x, s16 y);
extern void winSpriteSetDisp(void* win, u32 disp);
extern void menuTitleCursorAnime(void);
extern void* GSmsgGetRect(u32 msgId);
extern void* menuItemBiosGetPtr(u32 menuId, s16 itemId);
extern void menuItemBiosSetSelectFlag(u32 menuId, u32 itemId, u32 flag);
extern u32 menuItemBiosGetSelectFlag(u32 menuId, u32 itemId);
extern u32 windowGetActiveID(void);
extern s32 menuOpenCustom(u32 menuId, void* win, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6);
extern void menuTitleSetSelect(s16 select, u32 p1);
extern void menuTopInit(void);
extern void menuTopExit(void);
extern void menuTitleCloseSelectAnime(void);
extern void menuTitleOpenSelectAnime(void);
extern void menuTitleOpenSelectAnime2(void);
extern void menuTitleOpenMenu(void);
extern s32 menuTitleBattlePreReadCheck(void);
extern void menuNameEntryOpen(u32 p1, u32 p2);
extern u16 menuNameEntryGetLastName(u16* out);
extern void cursorBiosInit(void);
extern void heroMoveSyncWithHero(void);
extern void soundOpenPlay(u32 soundId, u32 p1, u32 p2);
extern void floorLink(u32 floorId, u32 param);
extern void menuPokemonInitWork(void);
extern u32 gamedatasaveGetStatus(u32 p1, u32 p2);
extern void winMsgOpen(u32 p1, u32 msgId, u32 p2, u32 p3);
extern void winMsgClose(u32 p1);
extern s32 menuSubOpenYesNo(u32 p1, u32 p2, u32 p3);
extern u32 memcardIsMemCardValid(void);
extern void fadeSet(u32 p1, f32 speed);
extern void fadeCheck(u32 p1);
extern void menuTitleOption(void);
extern void menuTitlePreReadWait(void);
extern void menuTitleBattleSelectFree(void);
extern void GScharMakeFromSJIS(u8* out, u32 sjisStr);
extern u32 _menuTopLoadCheck__Fv(void);
extern void _menuTopSetLastCursor__Fv(void);
extern void _menuTopNewGame__FPUs(u16* name);
extern void _menuTopInitPokemon__Fss(s16 p1, s16 p2);
extern void _menuTopLoadPokemon__Fv(void);
extern void _menuTopClose__Fl(s32 menuId);
extern void _menuTopClose2__FlUl(s32 menuId, u32 param);

// ============================================================================
// Local static variables
// ============================================================================
static void* _menuTopWork;              // Menu work area
static void* _menuTopMenuModel;         // Menu 3D model
static u32 _menuTopMsgTable[8];         // Message table
static u32 _menuTopMsgTableBattleSelect[4];  // Battle select message table

// ============================================================================
// menuTopOpenFlashBack
// Address: 0x8002F308 | Size: 0x28
// Opens the flashback menu (menu ID 0x119).
// ============================================================================
void menuTopOpenFlashBack(void)
{
    menuOpen(0x119, 0);
}

// ============================================================================
// menuTopSelectCtrl
// Address: 0x8002F330 | Size: 0xA4
// Controls menu selection based on state flags.
// Args: r3 = work struct
// ============================================================================
void menuTopSelectCtrl(void* work)
{
    s8 state = *(u8*)((u8*)work + 1);
    void* win = *(void***)((u8*)work + 0x68);
    
    if (state == 3)
    {
        // State 3: Battle select
        if (*(u8*)((u8*)work + 2) == 0)
        {
            winSeqSetMenu(win, 0x17B);
            *(u8*)((u8*)work + 2) = 1;
        }
    }
    else if (state == 0)
    {
        // State 0: Normal menu
        if (*(u8*)((u8*)work + 2) == 0)
        {
            u8* menuPtr = (u8*)*(u32*)win;
            if (*menuPtr != 0)
            {
                winSeqSetMenu(*(void***)((u8*)work + 4), 0x24);
            }
            *(u8*)((u8*)work + 2) = 1;
        }
    }
}

// ============================================================================
// menuTopLoadHook
// Address: 0x8002F3D4 | Size: 0xB0
// Hook function for loading 3D model on title screen.
// ============================================================================
void menuTopLoadHook(void)
{
    f32 angleX = 0.0f;  // @2382
    f32 angleZ = 0.0f;  // @2383
    s16 w = *(s16*)0x804EA768;  // @2336
    s16 h = *(s16*)0x804EA76C;  // @2337
    
    if (menuModelCheck(_menuTopMenuModel, w, h, 0, 0) == 0)
    {
        menuModelSetSize(_menuTopMenuModel, w, h, 0, 0);
        menuModelAdjustCamera(_menuTopMenuModel);
        menuModelRender(_menuTopMenuModel);
        menuModelSetAngle(_menuTopMenuModel, angleX, angleZ);
        menuModelSetZoom(_menuTopMenuModel, 1.0f);  // @2384
    }
}

// ============================================================================
// menuTopHookMssageWindow
// Address: 0x8002F484 | Size: 0x7C
// Hook for message window display on title screen.
// ============================================================================
void menuTopHookMssageWindow(void* win)
{
    u32 romVer = pokecoloGetRomVersion();
    
    if (romVer != 1)
    {
        s16 select = *(s16*)((u8*)win + 0xA);
        if (select >= 0)
        {
            s16 menuSelect = menuTitleGetSelect();
            u32 msgId = _menuTopMsgTable[menuSelect];
            u8 langArea = *(u8*)((u8*)win + 0x93);
            
            GSmsgPrint2(*(void***)((u8*)win + 0x1C), 0, -0x100, msgId, -8, langArea | 0xFF00);
        }
    }
}

// ============================================================================
// menuTopHookMssageBattleSelectWindow
// Address: 0x8002F500 | Size: 0x5C
// Hook for battle select message window.
// ============================================================================
void menuTopHookMssageBattleSelectWindow(void* win)
{
    s16 select = *(s16*)((u8*)win + 0xA);
    if (select >= 0)
    {
        u32 msgId = _menuTopMsgTableBattleSelect[select];
        u8 langArea = *(u8*)((u8*)win + 0x93);
        
        GSmsgPrint2(*(void***)((u8*)win + 0x1C), 0, -0x100, msgId, -8, langArea | 0xFF00);
    }
}

// ============================================================================
// menuTopHook
// Address: 0x8002F55C | Size: 0x10C
// Main hook function for title screen events.
// Handles various event codes (0x70-0x77).
// ============================================================================
void menuTopHook(void* msg, void* win)
{
    s16 eventCode = *(s16*)((u8*)win + 6);
    
    switch (eventCode)
    {
        case 0x70:  // Menu open
        {
            s16 select = *(s16*)((u8*)win + 0xA);
            if (select == 0)
            {
                menuTitleCursorAnime();
                winSpriteSetDisp(win, 1);
            }
            else
            {
                winSpriteSetDisp(win, 0);
            }
            break;
        }
        case 0x71:  // Menu close
        {
            s16 select = *(s16*)((u8*)win + 0xA);
            if (select == 1)
            {
                menuTitleCursorAnime();
                winSpriteSetDisp(win, 1);
            }
            else
            {
                winSpriteSetDisp(win, 0);
            }
            break;
        }
        case 0x72:  // Option select
        {
            s16 select = *(s16*)((u8*)win + 0xA);
            if (select == 2)
            {
                menuTitleCursorAnime();
                winSpriteSetDisp(win, 1);
            }
            else
            {
                winSpriteSetDisp(win, 0);
            }
            break;
        }
        case 0x76:  // Battle select 1
            fn_8002F668(msg, win, 0x445A);
            break;
        case 0x77:  // Battle select 2
            fn_8002F668(msg, win, 0x4459);
            break;
    }
}

// ============================================================================
// fn_8002F668
// Address: 0x8002F668 | Size: 0xB0
// Helper function for battle select message positioning.
// ============================================================================
void fn_8002F668(void* msg, void* win, u32 msgId)
{
    u32 rect = GSmsgGetRect(msgId);
    s16 rectY = (s16)(rect >> 16);
    s16 rectX = (s16)(rect & 0xFFFF);
    
    void* item = menuItemBiosGetPtr(*(u32*)((u8*)msg + 4), *(s16*)((u8*)win + 6));
    s16 itemH = *(s16*)((u8*)item + 0xA);
    s16 itemW = *(s16*)((u8*)item + 0xC);
    
    s32 dx = rectX - itemH;
    s32 dy = rectY - itemW;
    
    // Center text
    dx = (dx >> 31) + dx;  // Handle negative
    dy = (dy >> 31) + dy;
    
    u8 langArea = *(u8*)((u8*)msg + 0x93);
    
    GSmsgPrint2(*(void***)((u8*)msg + 0x1C), 0, -0x100, msgId, dy / 2, langArea | 0xFF00);
}

// ============================================================================
// menuTop
// Address: 0x8002F718 | Size: 0x558
// Main title screen function. Large state machine handling:
// - State 0: Initial/No save
// - State 1: Menu select
// - State 2: Continue
// - State 3: Load check
// - State 4: Menu item select
// - State 5: Fade/Transition
// - State 0x64: New game/Continue
// - State 0x6: Close menu
// ============================================================================
s32 menuTop(void)
{
    s32 state = 0;
    s32 loopFlag = 1;
    void* gbaWk = _menuTopWork;
    
    menuTopInit();
    
    *(u32*)((u8*)gbaWk + 4) = 1;
    *(u8*)((u8*)gbaWk + 8) = 0;
    
    while (loopFlag)
    {
        if (state == 4)
        {
            // State 4: Exit
            break;
        }
        else if (state >= 4)
        {
            if (state == 0x64)
            {
                // State 0x64: Set last cursor
                _menuTopSetLastCursor__Fv();
                loopFlag = 0;
                continue;
            }
            if (state >= 0x64)
                break;
            if (state >= 6)
                break;
            
            // State 6: Close menu
            _menuTopClose__Fl(0x116);
            menuTitleCloseSelectAnime();
            
            // Check for save data
            u32 romVer = pokecoloGetRomVersion();
            if (romVer == 1)
            {
                // XD version - check save
                u32 hasSave = gamedatasaveGetStatus(0, 4) != 0;
                s32 result;
                
                if (hasSave)
                {
                    winMsgOpen(2, 0x8B, 1, 1);  // "Continue?"
                }
                else
                {
                    winMsgOpen(2, 0x42D9, 1, 1);  // "New Game?"
                }
                
                result = menuSubOpenYesNo(0, 0x3C, 0xA6);
                winMsgClose(1);
                
                if (result == 0)
                {
                    menuTopExit();
                    if (menuTitleBattlePreReadCheck())
                    {
                        menuNameEntryOpen(0, 0);
                        u16 nameBuf[0x20];
                        u16 name = menuNameEntryGetLastName(nameBuf);
                        
                        if (name != 0)
                        {
                            cursorBiosInit();
                            _menuTopNewGame__FPUs(&name);
                            heroMoveSyncWithHero();
                            soundOpenPlay(8, 0x3E8, 0xFF);
                            floorLink(0xB6, 0);
                            state = 0x64;
                        }
                        else
                        {
                            state = 1;
                            menuTitleOpenMenu();
                            menuTitleOpenSelectAnime2();
                        }
                    }
                }
                else
                {
                    state = 1;
                    *(u8*)((u8*)gbaWk + 8) = 1;
                    menuTitleOpenSelectAnime();
                }
            }
            else
            {
                // Colosseum version
                pokecoloStartCountPlayTime(0);
                
                if (gamedatasaveGetStatus(0, 4) != 0)
                {
                    state = 3;  // Has save - continue
                    continue;
                }
                
                // No save - check memory card
                _menuTopClose__Fl(0x116);
                menuTitleCloseSelectAnime();
                
                if (memcardIsMemCardValid() == 0)
                {
                    winMsgOpen(2, 0x82, 1, 0);  // "Insert Memory Card"
                }
                else
                {
                    winMsgOpen(2, 0x98, 1, 0);  // "No Save Data"
                }
                winMsgClose(1);
                
                state = 1;
                menuTitleOpenMenu();
                menuTitleOpenSelectAnime();
            }
        }
        else if (state == 3)
        {
            // State 3: Load saved game
            u32 romVer = pokecoloGetRomVersion();
            if (romVer == 1)
            {
                // XD - load with default name
                u8 nameBuf[0x20];
                GScharMakeFromSJIS(nameBuf, "@2531");  // Default name
                cursorBiosInit();
                menuPokemonInitWork();
                _menuTopNewGame__FPUs((u16*)nameBuf);
                soundOpenPlay(8, 0x3E8, 0xFF);
                floorLink(0x47, 0);
                state = 0x64;
            }
            else
            {
                // Colosseum - check save
                pokecoloStartCountPlayTime(0);
                if (gamedatasaveGetStatus(0, 4) != 0)
                {
                    state = 3;
                    continue;
                }
                // ... (same as above)
            }
        }
        else if (state == 2)
        {
            // State 2: Continue from save
            state = 2;
            // Load check
            _menuTopClose__Fl(0x116);
            menuTitleCloseSelectAnime();
            fadeSet(3, 0.5f);  // @2532
            fadeCheck(1);
            _menuTopClose__Fl(0x11);
            _menuTopInitPokemon__Fss(0x280, 0x1E0);
            menuTitlePreReadWait();
            _menuTopLoadPokemon__Fv();
            
            if (_menuTopLoadCheck__Fv() == 0)
            {
                cursorBiosInit();
                menuTitleBattleSelectFree();
            }
            else
            {
                state = 1;
                menuTitleOpenMenu();
                menuTitleOpenSelectAnime2();
                fadeSet(2, 0.5f);
            }
        }
        else if (state == 1)
        {
            // State 1: Menu selection
            // Setup menu items
            u32 menuItems[5];
            menuItems[0] = *(u32*)0x802A8A80;  // @2201
            menuItems[1] = *(u32*)0x802A8A84;
            menuItems[2] = *(u32*)0x802A8A88;
            menuItems[3] = *(u32*)0x802A8A8C;
            menuItems[4] = *(u32*)0x802A8A90;
            
            *(u32*)((u8*)gbaWk + 4) = 1;
            
            // Set select flags for all menu items
            for (u32 i = 0; i < 5; i++)
            {
                menuItemBiosSetSelectFlag(0x116, menuItems[i], 1);
            }
            
            // XD version: Hide certain menu items
            if (pokecoloGetRomVersion() == 1)
            {
                menuItemBiosSetSelectFlag(0x116, 0x44, 0);
                menuItemBiosSetSelectFlag(0x116, 0x46, 0);
                menuItemBiosSetSelectFlag(0x116, 0x47, 0);
            }
            
            // Check which items are selectable
            for (u32 i = 0; i < 5; i++)
            {
                if (menuItemBiosGetSelectFlag(0x116, menuItems[i]))
                {
                    menuTitleSetSelect((s16)i, 0);
                }
            }
            
            // Open menu
            s32 result = menuOpenCustom(0x116,
                *(void***)((u8*)_menuTopWork + 0), 0, 1, 1,
                (u8*)_menuTopWork + 8, 0);
            
            *(u8*)((u8*)_menuTopWork + 8) = 0;
            
            if (result >= 0)
            {
                s16 select = menuTitleGetSelect();
                *(s16*)_menuTopWork = select;
            }
            else
            {
                *(s16*)_menuTopWork = -1;
            }
            
            if (result == 0)
            {
                state = 5;  // Fade out
                fadeCheck(1);
            }
            else
            {
                s16 select = *(s16*)_menuTopWork;
                if (select == 2)
                {
                    // Battle select
                    s32 battleResult = _menuTopSelectBattle__Fv();
                    if (battleResult >= 0)
                    {
                        state = 0x64;
                        *(u8*)((u8*)gbaWk + 8) = 1;
                    }
                    else
                    {
                        *(u8*)((u8*)gbaWk + 8) = 0;
                    }
                }
                else if (select == 0)
                {
                    // New game / Title
                    state = 0;
                }
                else if (select >= 0)
                {
                    // Continue
                    state = 2;
                }
                else if (select >= 4)
                {
                    // Options
                    *(u32*)((u8*)gbaWk + 4) = 4;
                    state = 4;
                }
                else
                {
                    // Start status
                    menuTitleSetStartStatus(1);
                    state = 0x64;
                }
            }
        }
        else if (state == 0)
        {
            // State 0: Initial - transition to menu
            state = 1;
            *(u8*)((u8*)gbaWk + 8) = 1;
            menuTitleOpenSelectAnime();
        }
        else if (state == 5)
        {
            // State 5: Fade/Transition
            fadeCheck(1);
        }
    }
    
    menuTopExit();
    return *(s16*)_menuTopWork;
}

// ============================================================================
// menuTopGetBattleMode
// Address: 0x8002FC70 | Size: 0x10
// Returns the current battle mode from work area.
// ============================================================================
u32 menuTopGetBattleMode(void)
{
    return *(u32*)_menuTopWork;
}

// ============================================================================
// NOTE: The remaining functions (menuTopBattleSelectCtrl, menuTopPlayToolBGM,
// _menuTopSelectBattle, menuTopExit, menuTopMain, menuTopInit, etc.) follow
// similar patterns and can be decompiled on demand.
// ============================================================================
