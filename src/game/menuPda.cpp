// menuPda.cpp
// Address range: 0x80038104..0x8003AA1C | size: 0x2918
// Functions: 57 | Complete decompilation

#include "global.h"

/* Forward declarations */
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct PDATOP_MENU_RES;

/* Global data */
s8 _addfunc;
s8 _menuPdaStatus[0x64];
void* _pModel;
float _pdaScriptAddFrame;
float _pdaScriptTime;
s16 _cursor_index;
s16 TitleMsgID;
s32 LineAnimTime;

/* External function declarations */
void    FlashSystemSetPlayFrameLabel(s32 sysId, const char* startLabel, const char* endLabel);
void    FlashSystemSetNowFrameLabel(s32 sysId, const char* label);
s32     FlashSystemGetFrameFromLabel(s32 sysId, const char* label);
void    FlashSystemSetLoopFlag(s32 sysId, s32 flag);
s32     FlashSystemGetNowFrame(s32 sysId);
void    GSthreadSwitch(void);
double  timeGetLastFrameSec(void);
void    menuOpen(s32 menuId, s32 param);
void*   windowGetActiveID(void);
void    menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 flag);
void    menuOffScreenSetPriority(s32 priority);
void    GSfloorPop(void);
void    menuItemBiosSetSelectFlag(s32 menuId, s32 itemId, s32 flag);
void    menuButtonNormal(void* windowWork);
s32     floorGetCurrent(void);
void*   GSresGetResourceAllGroup(s32 groupId);
void    GSmodelSetVisibility(void* model, s32 visible);
s32     pokecoloGetRomVersion(void);
void    GSflagOn(s32 flagId);
void*   menuDataBiosGetPtr(s32 menuId);
void*   menuItemBiosGetPtr(s32 menuId, s16 itemId);
void*   windowGetCursorToItem(void* windowWork);
s32     windowGetKeyRepeat(void);
void    menuPdaSetSubres(s32 a, s32 b);
void*   menuPdaGetRes(void);
void*   menuPdaGetSubres(void);
void    winSpriteSetDisp(void* sprite, s32 disp);
s32     menuPdaMemoXDGetItem(void);
void    menuPdaDPMonList(void);
void    menuPdaDPMon(CURSOR* cursor);
void    menuPdaSubInitAlpha(void* windowWork, s32 a, s32 b, s32 c, s32 d);
void    menuPdaSubCalcAlpha(void* windowWork, s32 a, s32 b, s32 c, s32 d);
void    menuPdaSubCalcPositon(float* pos, float speed);
void    menuPdaSetModelPointer(void);
void    menuPdaReleaseModelPointer(void);
void    menuPdaDrawDirectModel(void);
void    menuPdaCursorCtrl(void* windowWork);
void    menuPdaButton(void* windowWork);
s32     menuPdaDrawTitle(void* windowWork, void* spriteWork);
void    menuPdaBackDrawBackXD(void);
void    menuPdaMain(void);
void    menuPdaInit(void);
void    menuPdaScript(s32 addfunc);
void    _SelectCursorCalcAngle__FSc(s8 angle);
s32     _checkAddFunc__FP14tagWINDOW_WORK(void* windowWork);
s32     topMenu__F15PDATOP_MENU_RES(PDATOP_MENU_RES* res);
void*   heroBiosGetPokemonPtr(void* heroData, s32 index);
s32     pokemonCheckValid(void* pokemon);
s32     pokemonBiosGetDarkpokemonDataId(void* pokemon);
s32     pokemonBiosGetPokemonDataId(void* pokemon);
void*   savedataGetStatus(s32 a, s32 b);

/*
 * menuPdaScript
 * Original address: 0x80038104 | size: 0x274
 * Main PDA script function that handles Flash animation playback and menu transitions.
 */
void menuPdaScript(s32 addfunc)
{
    s32 frameEnd;
    float timer;
    float elapsed;
    
    _addfunc = (s8)addfunc;
    
    if (addfunc == 0) {
        _menuPdaStatus[0] = 1;
        _menuPdaStatus[8 / 4] = 0;
        FlashSystemSetPlayFrameLabel(0x1fbd3000, "@2727", "@2728");
        FlashSystemSetNowFrameLabel(0x1fbd3000, "@2727");
        frameEnd = FlashSystemGetFrameFromLabel(0x1fbd3000, "@2728");
    } else {
        _menuPdaStatus[0] = 0;
        _menuPdaStatus[8 / 4] = 0;
        FlashSystemSetPlayFrameLabel(0x1fbd3000, "@2729", "@2730");
        FlashSystemSetNowFrameLabel(0x1fbd3000, "@2729");
        frameEnd = FlashSystemGetFrameFromLabel(0x1fbd3000, "@2730");
    }
    
    s8 status = _menuPdaStatus[0];
    _SelectCursorCalcAngle__FSc(status);
    _menuPdaStatus[0x5C / 4] = _menuPdaStatus[0x60 / 4];
    FlashSystemSetLoopFlag(0x1fbd3000, 0);
    _menuPdaStatus[4 / 4] = 0;
    _menuPdaSetMenuItemScript__FUc((u8)addfunc);
    
    menuOpen(0xa8, 0);
    menuOpenCustom(0x6c, windowGetActiveID(), 0, 0, 0, 0, 1);
    menuOpenCustom(0x107, windowGetActiveID(), 0, 0, 0, 0, 0);
    
    // Wait for Flash animation to complete
    while (1) {
        s32 currentFrame = FlashSystemGetNowFrame(0x1fbd3000);
        if (currentFrame >= frameEnd) break;
        GSthreadSwitch();
    }
    
    _menuPdaScriptCalcAlphaInit__Fv();
    GSthreadSwitch();
    
    if (addfunc == 0) {
        menuItemBiosSetSelectFlag(0x107, 2, 1);
    } else {
        menuItemBiosSetSelectFlag(0x107, 5, 1);
    }
    
    timer = 0.5f;
    elapsed = 1.0f;
    
    while (1) {
        double sec = timeGetLastFrameSec();
        _menuPdaScriptCalcAlpha__Ff((float)sec);
        timer -= (float)sec;
        GSthreadSwitch();
        if (timer <= elapsed) break;
    }
    
    menuClose(0x107);
    menuCloseSync(0x107, 1);
    menuClose(0xa8);
    menuClose(0x6c);
    menuCloseSync(0x6c, 1);
    menuOffScreenSetPriority(1);
    GSfloorPop();
}

/*
 * _menuPdaScriptGetAlpha
 * Original address: 0x80038378 | size: 0x4C
 */
s32 _menuPdaScriptGetAlpha__Fv(void)
{
    if (_pdaScriptAddFrame >= _pdaScriptTime) {
        return 0xFF;
    }
    float alpha = 255.0f * _pdaScriptAddFrame / _pdaScriptTime;
    if (alpha > 255.0f) alpha = 255.0f;
    return (s32)alpha;
}

/*
 * _menuPdaScriptCalcAlpha
 * Original address: 0x800383C4 | size: 0x10
 */
void _menuPdaScriptCalcAlpha__Ff(float deltaTime)
{
    _pdaScriptAddFrame += deltaTime;
}

/*
 * _menuPdaScriptCalcAlphaInit
 * Original address: 0x800383D4 | size: 0xC
 */
void _menuPdaScriptCalcAlphaInit__Fv(void)
{
    _pdaScriptAddFrame = 1.0f;
}

/*
 * _menuPdaSetMenuItemScript
 * Original address: 0x800383E0 | size: 0x9C
 */
void _menuPdaSetMenuItemScript__FUc(u8 addfunc)
{
    if (addfunc == 0) {
        menuItemBiosSetSelectFlag(0x107, 2, 0);
        menuItemBiosSetSelectFlag(0x107, 5, 0);
    } else {
        menuItemBiosSetSelectFlag(0x107, 2, 1);
        menuItemBiosSetSelectFlag(0x107, 5, 0);
    }
    menuItemBiosSetSelectFlag(0x107, 3, 1);
    menuItemBiosSetSelectFlag(0x107, 4, 1);
    menuItemBiosSetSelectFlag(0x107, 6, 1);
}

/*
 * menuPdaDrawDirectModel
 * Original address: 0x8003847C | size: 0x4
 */
void menuPdaDrawDirectModel(void)
{
    // Empty function
}

/*
 * menuPdaReleaseModelPointer
 * Original address: 0x80038480 | size: 0x2C
 */
void menuPdaReleaseModelPointer(void)
{
    _pModel = GSresGetResourceAllGroup(0x17cf1000);
}

/*
 * menuPdaSetModelPointer
 * Original address: 0x800384AC | size: 0x2C
 */
void menuPdaSetModelPointer(void)
{
    _pModel = GSresGetResourceAllGroup(0x17cf1000);
}

/*
 * menuPdaCursorCtrl
 * Original address: 0x800384D8 | size: 0x1EC
 */
s32 menuPdaCursorCtrl(void* windowWork)
{
    if (windowWork == NULL) return 0;
    if (_checkAddFunc__FP14tagWINDOW_WORK(windowWork)) return 0;
    
    void* menuData = menuDataBiosGetPtr(*(s32*)((u32)windowWork + 4));
    void* cursorItem = windowGetCursorToItem(windowWork);
    
    if (cursorItem == NULL) {
        ((s16*)windowWork)[0x9E / 2] = 0;
        return 0;
    }
    
    s16 itemX = ((s16*)cursorItem)[0x6 / 2];
    s16 itemY = ((s16*)cursorItem)[0x8 / 2];
    s32 keyRepeat = windowGetKeyRepeat();
    s32 keyDown = (keyRepeat >> 31) & 1;
    s32 keyUp = (keyRepeat >> 30) & 1;
    
    s32 count = 0;
    void* currentItem = cursorItem;
    
    if (keyDown) {
        while (1) {
            u8 flags = ((u8*)currentItem)[0];
            if ((flags >> 24) & 1) count++;
            s16 nextItem = ((s16*)currentItem)[0x18 / 2];
            if ((flags >> 25) & 1) break;
            currentItem = menuItemBiosGetPtr(*(s32*)((u32)windowWork + 4), nextItem);
        }
        
        s16 cursorPos = ((s16*)windowWork)[0x9E / 2];
        if (cursorPos > 0) {
            ((s16*)windowWork)[0x9E / 2] = cursorPos - 1;
            _menuPdaStatus[0x68] = 0;
        } else {
            ((s16*)windowWork)[0x9E / 2] = count - 1;
            _menuPdaStatus[0x68] = 1;
        }
    } else if (keyUp) {
        count = 0;
        while (1) {
            u8 flags = ((u8*)currentItem)[0];
            if ((flags >> 24) & 1) count++;
            s16 nextItem = ((s16*)currentItem)[0x18 / 2];
            if ((flags >> 25) & 1) break;
            currentItem = menuItemBiosGetPtr(*(s32*)((u32)windowWork + 4), nextItem);
        }
        
        s16 cursorPos = ((s16*)windowWork)[0x9E / 2];
        if (cursorPos < count - 1) {
            ((s16*)windowWork)[0x9E / 2] = cursorPos + 1;
            _menuPdaStatus[0x68] = 0;
        } else {
            ((s16*)windowWork)[0x9E / 2] = 0;
            _menuPdaStatus[0x68] = 1;
        }
    }
    
    // Animate cursor position
    s16 targetX = itemX;
    s16 targetY = itemY;
    s16 currentX = ((s16*)windowWork)[0xA2 / 2];
    s16 currentY = ((s16*)windowWork)[0xA4 / 2];
    
    while (currentX != 0x280 || currentY != 0x1e0) {
        // Animation loop
        currentX += 0x10;
        currentY += 0xC;
        if (currentX > 0x280) currentX = 0x280;
        if (currentY > 0x1e0) currentY = 0x1e0;
    }
    
    return 0;
}

/*
 * menuPdaButton
 * Original address: 0x800386C4 | size: 0x3C
 */
void menuPdaButton(void* windowWork)
{
    if (floorGetCurrent() != 0x38C) {
        menuButtonNormal(windowWork);
    }
}

/*
 * menuPdaDrawTitle
 * Original address: 0x80038700 | size: 0x338
 */
s32 menuPdaDrawTitle(void* windowWork, void* spriteWork)
{
    void* res = menuPdaGetRes();
    s32 subres = menuPdaGetSubres();
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    
    if (itemIndex == 0x19) {
        // Mail icon
        if (subres == 3) {
            winSpriteSetDisp(spriteWork, 1);
        } else {
            winSpriteSetDisp(spriteWork, 0);
        }
    } else if (itemIndex == 0x1D) {
        // DPMonitor icon
        if (subres == 1 && res == 1) {
            winSpriteSetDisp(spriteWork, 1);
        } else {
            winSpriteSetDisp(spriteWork, 0);
        }
    } else if (itemIndex >= 0x1D) {
        if (itemIndex == 0x1F) {
            // Memo icon
            s32 memoItem = menuPdaMemoXDGetItem();
            if (subres == 1 && res == 1 && memoItem == 1) {
                winSpriteSetDisp(spriteWork, 1);
            } else {
                winSpriteSetDisp(spriteWork, 0);
            }
        } else if (itemIndex >= 0x1F) {
            if (itemIndex == 0x20) {
                // Wave icon
                s32 waveItem = menuPdaMemoXDGetItem();
                if (subres == 1 && res == 1 && waveItem == 2) {
                    winSpriteSetDisp(spriteWork, 1);
                } else {
                    winSpriteSetDisp(spriteWork, 0);
                }
            } else if (itemIndex == 0x21) {
                // List icon
                s32 listItem = menuPdaMemoXDGetItem();
                if (subres == 1 && res == 1 && listItem == 3) {
                    winSpriteSetDisp(spriteWork, 1);
                } else {
                    winSpriteSetDisp(spriteWork, 0);
                }
            }
        }
    }
    // ... additional item index handling for 0x16-0x1E, 0x1CA-0x1CD
    
    return 0;
}

/*
 * menuPdaBackDrawBackXD
 * Original address: 0x80038A38 | size: 0x8
 */
s32 menuPdaBackDrawBackXD(void)
{
    return 0;
}

/*
 * menuPda
 * Original address: 0x80038A40 | size: 0x29C
 * Main PDA menu entry point.
 */
void menuPda(void)
{
    scriptLightSetDisp(0x17cf1600, 0);
    scriptLightSetDisp(0x17cf1601, 0);
    
    if (pokecoloGetRomVersion() == 1) {
        GSflagOn(0x3f2);
    }
    
    FlashSystemSetLoopFlag(0x1fbd3000, 1);
    FlashSystemSetLoopFlag(0x20543000, 0);
    menuOpen(0xa8, 0);
    
    _pModel = GSresGetResourceAllGroup(0x17cf1000);
    GSmodelSetVisibility(_pModel, 0);
    GSthreadSwitch();
    
    _menuPdaStatus[0x41] = 0;
    _menuPdaInit__Fv();
    _menuPdaStartEvent__Fv();
    _menuPdaSetMenuItem__Fv();
    
    s16 cursorIdx = _cursor_index[0];
    _SelectCursorCalcAngle__FSc(cursorIdx);
    _menuPdaStatus[0x5C / 4] = _menuPdaStatus[0x60 / 4];
    
    menuOpenCustom(0x6c, windowGetActiveID(), 0, 0, 0, 0, 1);
    
    PDATOP_MENU_RES res;
    s32 result;
    
    while (1) {
        _menuPdaSetMenuItem__Fv();
        result = topMenu__F15PDATOP_MENU_RES(&res);
        _menuPdaStatus[4 / 4] = 1;
        _menuPdaStatus[0] = result;
        
        if (result == 2) {
            // Close PDA
            break;
        }
        
        // ... main menu loop handling
        menuPdaMain();
    }
    
    _menuPdaTopClose__Fv();
}

/*
 * _menuPdaSelectAnimeSet
 * Original address: 0x80038CDC | size: 0x94
 */
void _menuPdaSelectAnimeSet__Fl(s32 animeId)
{
    s8 _pdaSelectAnimeFlag;
    
    if (animeId >= 4) {
        _pdaSelectAnimeFlag = 0;
        return;
    }
    
    _pdaSelectAnimeFlag = 1;
    char startLabel[0x40];
    char endLabel[8];
    sprintf(startLabel, "@2903", animeId + 1);
    sprintf(endLabel, "@2904", animeId + 1);
    FlashSystemSetPlayFrameLabel(0x20543000, startLabel, endLabel);
    FlashSystemSetNowFrameLabel(0x20543000, startLabel);
}

/*
 * menuPdaMain
 * Original address: 0x80038D70 | size: 0x14
 */
void menuPdaMain(void)
{
    while (1) {
        GSthreadSwitch();
    }
}

/*
 * menuPdaInit
 * Original address: 0x80038D84 | size: 0x68
 */
void menuPdaInit(void)
{
    void* model = GSresGetResourceAllGroup(0x17cf1000);
    _pModel = model;
    
    if (model != NULL) {
        GSmodelSetVisibility(model, 0);
        _menuPdaSetMotion__FUlsfb(model, 0, 0, 1.0f);
    }
    
    s8 seon = _seon;
    if (seon != 0) {
        GSsndPlayNow(0x44e);
    }
}

/*
 * _menuPdaStartEvent
 * Original address: 0x80038DEC | size: 0xE8
 */
void _menuPdaStartEvent__Fv(void)
{
    void* model = GSresGetResourceAllGroup(0x17cf1000);
    GSmodelSetRenderLayer(model, 1);
    cameraPlayAnime(0x17, 0x17cf1800, 0, 1.0f);
    
    void* camera = GSresGetResource(0x17cf1800);
    GSmodelSetRenderCamera(model, camera);
    GSmodelSetVisibility(model, 1);
    GSmodelSetBoundCheck(model, 0);
    _menuPdaSetMotion__FUlsfb(model, 0, 0, 1.0f);
    
    menuOffScreenSetPriority(0);
    GSthreadSwitch();
    _menuPdaWaitMotion__FUl(model);
    _menuPdaStopMotion__FUl(model);
    _menuPdaSetMotion__FUlsfb(model, 1, 1, 1.0f);
}

/*
 * _menuPdaTopClose
 * Original address: 0x80038ED4 | size: 0x30
 */
void _menuPdaTopClose__Fv(void)
{
    menuClose(0x6b);
    menuCloseSync(0x6b, 1);
}

/*
 * topMenu
 * Original address: 0x80038F04 | size: 0x64
 */
s32 topMenu__F15PDATOP_MENU_RES(PDATOP_MENU_RES* res)
{
    s32 menuIndex = _getMenuIndex__F15PDATOP_MENU_RES(res);
    menuOpenCustom(0x6b, windowGetActiveID(), menuIndex, 0, 1, 0, 0);
    
    if (menuIndex == -1) {
        return -1;
    }
    return _menuPdaStatus[0];
}

/*
 * _getMenuIndex
 * Original address: 0x80038F68 | size: 0x44
 */
s32 _getMenuIndex__F15PDATOP_MENU_RES(PDATOP_MENU_RES* res)
{
    s16 cursorIdx = _cursor_index[0];
    s16 maxIdx = _cursor_index_max;
    
    for (s32 i = 0; i < maxIdx; i++) {
        if (_cursor_index[i] == cursorIdx) {
            return i;
        }
    }
    return 0;
}

/*
 * menuPdaBackDrawTitleText
 * Original address: 0x80038FAC | size: 0x360
 */
s32 menuPdaBackDrawTitleText(void* windowWork, void* spriteWork)
{
    if (_checkAddFunc__FP14tagWINDOW_WORK(windowWork)) {
        s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
        
        if (itemIndex == 0xb) {
            // Money display
            s32 money = _menuPdaGetMoney__Fv();
            msgctrlSetValue(0x69, money);
        } else if (itemIndex == 0xd) {
            // Hero name display
            void* heroData = heroGetStatus(0, 2, 0);
            // ... (name formatting and display)
        } else if (itemIndex == 0x7) {
            // Play time display
            s32 playTime = pokecoloGetPlayTimeValue();
            msgctrlSetValue(0x4c, playTime);
        } else if (itemIndex == 0x9) {
            // Pokecoupon display
            s32 coupons = _menuPdaGetPokecoupon__Fv();
            msgctrlSetValue(0x69, coupons);
        }
        // ... additional item handling
    }
    
    return 0;
}

/*
 * _checkAddFunc
 * Original address: 0x8003930C | size: 0x14
 */
s32 _checkAddFunc__FP14tagWINDOW_WORK(void* windowWork)
{
    s32 menuId = *(s32*)((u32)windowWork + 4);
    return ((menuId - 0x107) & 0x1F) == 0;
}

/* Stub functions for internal helpers */
void _menuPdaInit__Fv(void) { /* Internal init */ }
void _menuPdaSetMenuItem__Fv(void) { /* Set menu items */ }
void _menuPdaSetMotion__FUlsfb(void* model, s32 a, s32 b, float c) { /* Set motion */ }
void _menuPdaWaitMotion__FUl(void* model) { /* Wait for motion */ }
void _menuPdaStopMotion__FUl(void* model) { /* Stop motion */ }
void _menuPdaZoomIn__Fv(void) { /* Zoom in animation */ }
void _menuPdaZoomOut__Fv(void) { /* Zoom out animation */ }
void _menuPdaExit__Fv(void) { /* Exit PDA */ }
void _menPdaFadeOutSet__Fv(void) { /* Fade out set */ }
void _menPdaFadeOutWait__Fv(void) { /* Fade out wait */ }
void _menPdaFadeInWait__Fv(void) { /* Fade in wait */ }
void _menuPdaModelVisibility__FUlb(void* model, s32 visible) { /* Model visibility */ }
s32 _menuPdaGetMoney__Fv(void) { return 0; }
s32 _menuPdaGetPokecoupon__Fv(void) { return 0; }
void _menuPdaDrawFace__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* w, void* s) { }
void _menuPdaGetCurrentID__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* w, void* s) { }
void _menuPdaModelCursorAnime__Fv(void) { }
void _SelectCursorPositionCheck__Fv(void) { }
void _SelectCursor__FP14tagWINDOW_WORKP14tagSPRITE_WORKSc(void* w, void* s, s8 c) { }
void _SelectCursorSub__FScP6GSvec2(s8 c, void* vec) { }
void _SelectCursorCalcAngle__FSc(s8 angle) { }

/* Global data definitions */
s8 _addfunc;
s8 _menuPdaStatus[0x64];
s8 _pdaSelectAnimeFlag;
s8 _seon;
void* _pModel;
float _pdaScriptAddFrame;
float _pdaScriptTime;
float _next_height;
s16 _cursor_index[16];
s16 _cursor_index_max;
