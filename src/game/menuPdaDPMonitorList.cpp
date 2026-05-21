// menuPdaDPMonitorList.cpp
// Address range: 0x80050A1C..0x80052CBC | size: 0x22A0
// 43 functions - Complete decompilation

#include "global.h"

/* Forward declarations */
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct CURSOR;
struct DarkPokemon;
struct SnatchSortBuff;
enum DPMSelSort { DPMSelSort };

/* Global data */
void* pDPMList;

/* External function declarations */
void*   menuItemBiosGetPtr(s32 type, s32 id);
void    msgctrlSetValue(s32 id, void* value);
void*   GSmsgGetGSchar(u32 msgId);
void    GSmsgPrint2(void* layer, s32 x, s32 y, u32 color, s32 param5, s32 msgId, s32 param7);
void    spriteSetScissor(void* layer, s16 x, s16 y, s16 width, s16 height);
void    spriteClearScissor(void* layer);
void    winSpriteSetDisp(void* sprite, s32 disp);
void*   windowGetKeyInfo(void);
s32     winSpriteGetLayerID(void* windowWork, void* spriteWork);
void    menuOpen(s32 menuId, s32 param);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 flag);
void*   windowGetActiveID(void);
void    menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void    menuPdaSubScrollBar(void* windowWork, void* spriteWork, void* cursor, s32 dpNum, s32 a, s32 b, s32 c);
void    menuPdaSubCheckUpDownCursor(void* windowWork, void* spriteWork, CURSOR* cursor, s32 dpNum, s32 a, s32 b, s32 c);
void    menuPdaSubInitAlpha(void* windowWork, s32 a, s32 b, s32 c, s32 d);
void    menuDrawReliveMeterByDarkPokemon(void* dp, void* windowWork, void* spriteWork, void* layer, s16 x, s16 y, s32 msgId);
void    menuDrawReliveUpdate(void);
void    windowDrawSprite2(void* layer, s32 x, s32 y, s32 spriteId, s32 a, s32 b, s32 c, s32 d, s32 e);
void    menuPlaySe(s32 menuId, s32 seId);
void    GSsndPlayNow(s32 soundId);
s32     GSinputButtonsPressed(s32 controller);
void*   __nw__FUl(s32 size);
void    __dl__FPv(void* ptr);
void    __dla__FPv(void* ptr);

/* DarkPokemon class methods */
s32     getStatus__11DarkPokemonCFv(void* dp);
s32     getDarkPoint__11DarkPokemonCFv(void* dp);
s32     getPokemonID__11DarkPokemonCFv(void* dp);
void    getPlace__11DarkPokemonCFR16darkPokemonWhereRUc(void* dp, s32* place, u8* type);
s32     isUpdate__11DarkPokemonCFv(void* dp);
void    setUpdate__11DarkPokemonFb(void* dp, s32 flag);
s32     isSnach__11DarkPokemonCFv(void* dp);
s32     getCatchBallID__11DarkPokemonCFv(void* dp);
void*   darkPokemonGetDarkPokemon(s32 id);

/* Other external functions */
void*   pokemonDataBiosGetPtr(s32 pokemonId);
void*   pokemonDataBiosGetName(void* pokemonData);
s32     mballBiosGetSpriteID(s32 ballId);
void    menuPdaDPMon(CURSOR* cursor);

/*
 * menuPdaDPMListDispRelive
 * Original address: 0x80050A1C | size: 0x114
 * Displays relive meter for Dark Pokemon in list.
 */
s32 menuPdaDPMListDispRelive(void* windowWork, void* spriteWork, void* layer,
    s16 x, s16 y, s32 msgId, s32 dpIndex)
{
    void* dp = menuPdaDPMListGetDPointer(dpIndex);
    s32 status = getStatus__11DarkPokemonCFv(dp);
    s32 darkPoint = getDarkPoint__11DarkPokemonCFv(dp);
    
    if (status == 3) {
        // Reliving - show relive meter
        void* itemBios = menuItemBiosGetPtr(0x74, 0x4a);
        s16 itemX = ((s16*)itemBios)[0xA / 2];
        s16 itemY = ((s16*)itemBios)[0xC / 2];
        menuDrawReliveMeterByDarkPokemon(dp, windowWork, spriteWork, layer, itemX, itemY, msgId);
    } else if (status >= 3) {
        if (status < 5) {
            // Snatched - show message
            void* msg = GSmsgGetGSchar(0x3c0b);
            msgctrlSetValue(0x37, msg);
            if (dpIndex != 0) {
                GSmsgPrint2(layer, x, y, dpIndex | 0xEE444400, 0, 0x4276, 0);
            } else {
                GSmsgPrint2(layer, x, y, dpIndex | 0xEE444400, 0, 0x4275, 0);
            }
        }
    } else if (status >= 0) {
        // Not dark - show message
        void* msg = GSmsgGetGSchar(0x3c0b);
        msgctrlSetValue(0x37, msg);
        if (dpIndex != 0) {
            GSmsgPrint2(layer, x, y, dpIndex | 0xEE444400, 0, 0x4276, 0);
        } else {
            GSmsgPrint2(layer, x, y, dpIndex | 0xEE444400, 0, 0x4275, 0);
        }
    }
    
    return 1;
}

/*
 * menuPdaDPMListGetDarkPokemonPlaceMsgID
 * Original address: 0x80050B30 | size: 0xA0
 * Gets message ID for Dark Pokemon place.
 */
s32 menuPdaDPMListGetDarkPokemonPlaceMsgID(s32 dpIndex, s32* placeOut, u8* typeOut)
{
    s32 place = menuPdaDPMListGetDarkPokemonPlace(dpIndex, placeOut, typeOut);
    s32 msgId = 0;
    
    if (place == 0) {
        msgId = 0;
    } else if (place == 1) {
        msgId = 0x3c0c;
    } else if (place >= 1) {
        if (place == 2) {
            msgId = 0x3c0e;
        } else if (place >= 2) {
            if (place == 3) {
                msgId = 0x3c0d;
            } else if (place >= 3) {
                if (place == 5) {
                    msgId = 0x3b7a;
                } else if (place >= 5) {
                    if (place < 7) {
                        msgId = 0x3c0f;
                    }
                }
            }
        }
    }
    
    return msgId;
}

/*
 * menuPdaDPMListGetDarkPokemonPlace
 * Original address: 0x80050BD0 | size: 0xC0
 * Gets the place where Dark Pokemon was found.
 */
s32 menuPdaDPMListGetDarkPokemonPlace(s32 dpIndex, s32* placeOut, u8* typeOut)
{
    if (pDPMList == NULL) {
        return 0;
    }
    
    s32 dpId = GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
    void* dp = darkPokemonGetDarkPokemon(dpId);
    s32 status = getStatus__11DarkPokemonCFv(dp);
    
    if (status >= 3) {
        if (status < 5) {
            getPlace__11DarkPokemonCFR16darkPokemonWhereRUc(dp, placeOut, typeOut);
            return 1;
        }
    } else if (status >= 0) {
        *placeOut = 0;
        *typeOut = 0;
        return 1;
    }
    
    return 1;
}

/*
 * menuPdaDPMListGetDarkPokemonID
 * Original address: 0x80050C90 | size: 0x38
 */
s16 menuPdaDPMListGetDarkPokemonID(s32 dpIndex)
{
    if (pDPMList == NULL) {
        return 0;
    }
    return GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
}

/*
 * menuPdaDPMListGetPokemonID
 * Original address: 0x80050CC8 | size: 0x44
 */
s32 menuPdaDPMListGetPokemonID(s32 dpIndex)
{
    if (pDPMList == NULL) {
        return 0;
    }
    s32 dpId = GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
    void* dp = darkPokemonGetDarkPokemon(dpId);
    return getPokemonID__11DarkPokemonCFv(dp);
}

/*
 * menuPdaDPMListGetPokemonName
 * Original address: 0x80050D0C | size: 0x60
 */
void* menuPdaDPMListGetPokemonName(s32 dpIndex)
{
    if (pDPMList == NULL) {
        return NULL;
    }
    s32 dpId = GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
    void* dp = darkPokemonGetDarkPokemon(dpId);
    s32 pokemonId = getPokemonID__11DarkPokemonCFv(dp);
    void* pokemonData = pokemonDataBiosGetPtr(pokemonId);
    if (pokemonData == NULL) {
        return NULL;
    }
    void* name = pokemonDataBiosGetName(pokemonData);
    return GSmsgGetGSchar(name);
}

/*
 * menuPdaDPMListGetDarkpokemonID
 * Original address: 0x80050D6C | size: 0x38
 */
s16 menuPdaDPMListGetDarkpokemonID(s32 dpIndex)
{
    if (pDPMList == NULL) {
        return 0;
    }
    return GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
}

/*
 * menuPdaDPMListGetDPointer
 * Original address: 0x80050DA4 | size: 0x30
 */
void* menuPdaDPMListGetDPointer(s32 dpIndex)
{
    if (pDPMList == NULL) {
        return NULL;
    }
    s32 dpId = GetDarkPokemonID__14menuPdaDPMListFl(dpIndex);
    return darkPokemonGetDarkPokemon(dpId);
}

/*
 * menuPdaDPMListCallBack
 * Original address: 0x80050DD4 | size: 0xEC
 * Callback for menu item rendering.
 */
s32 menuPdaDPMListCallBack(void* windowWork, void* spriteWork)
{
    if (pDPMList == NULL) {
        return 0;
    }
    
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    
    if (itemIndex == 0x37) {
        ScrollBar__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
    } else if (itemIndex == 0x42) {
        // No action
    } else if (itemIndex >= 0x42) {
        if (itemIndex == 0x46) {
            UpCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
        } else if (itemIndex >= 0x46) {
            if (itemIndex == 0x47) {
                DownCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
            } else if (itemIndex >= 0x47) {
                if (itemIndex == 0x4b) {
                    DispList__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
                } else if (itemIndex >= 0x4b) {
                    if (itemIndex < 0x4f) {
                        SetItemColor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
                    }
                }
            }
        }
    } else if (itemIndex == 0x37) {
        ListCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
    } else if (itemIndex >= 0x37) {
        if (itemIndex == 0x4f) {
            // No action
        } else if (itemIndex >= 0x4f) {
            if (itemIndex == 0x1cd) {
                SortCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(windowWork, spriteWork);
            } else if (itemIndex >= 0x1cd) {
                if (itemIndex < 0x1d0) {
                    // No action
                }
            }
        }
    }
    
    return 0;
}

/*
 * menuPdaDPMListGetDPNum
 * Original address: 0x80050EC0 | size: 0x1C
 */
s32 menuPdaDPMListGetDPNum(void)
{
    if (pDPMList == NULL) {
        return 0;
    }
    return *(s32*)((u32)pDPMList + 0x0);
}

/*
 * menuPdaDPMListButton
 * Original address: 0x80050EDC | size: 0x30
 */
void menuPdaDPMListButton(void* windowWork)
{
    if (pDPMList != NULL) {
        Button__14menuPdaDPMListFP14tagWINDOW_WORK(pDPMList, windowWork);
    }
}

/*
 * menuPdaDPMListCursor
 * Original address: 0x80050F0C | size: 0x3C
 */
s32 menuPdaDPMListCursor(void* windowWork)
{
    if (pDPMList != NULL) {
        Cursor__14menuPdaDPMListFP14tagWINDOW_WORK(pDPMList, windowWork);
        return 0;
    }
    return 0;
}

/*
 * menuPdaDPMListCtrl
 * Original address: 0x80050F48 | size: 0x3C
 */
s32 menuPdaDPMListCtrl(void* windowWork)
{
    if (pDPMList != NULL) {
        Ctrl__14menuPdaDPMListFP14tagWINDOW_WORK(pDPMList, windowWork);
        return 0;
    }
    return 0;
}

/*
 * menuPdaDPMonList
 * Original address: 0x80050F84 | size: 0x128
 * Main entry point for DPMonitor list menu.
 */
void menuPdaDPMonList(void)
{
    s32 result = 0;
    void* thisObj = __nw__FUl(0x60);
    if (thisObj != NULL) {
        __ct__14menuPdaDPMListFv(thisObj);
    }
    pDPMList = thisObj;
    InitWork__14menuPdaDPMListFv(thisObj);
    CURSOR cursor = { 0, 0 };
    menuOpen(0x77, 0);
    
    while (1) {
        result = Main__14menuPdaDPMListFl(pDPMList, result, &cursor);
        if (result < 0) break;
        
        // Check for Dark Pokemon update
        s32 dpId = menuPdaDPMListGetDarkPokemonID(cursor[0] + cursor[1]);
        void* dp = darkPokemonGetDarkPokemon(dpId);
        if (isUpdate__11DarkPokemonCFv(dp)) {
            setUpdate__11DarkPokemonFb(dp, 0);
        }
        
        menuPdaDPMon(&cursor);
        cursor[1] = ((CURSOR*)cursor)[0];
        cursor[0] = 0;
        menuPdaSubInitAlpha(pDPMList + 0x4, 0xa, 0, 0, 0);
        CalcPosition__14menuPdaDPMListFP6CURSOR(pDPMList, &cursor);
        ((float*)pDPMList)[0x3C / 4] = ((float*)pDPMList)[0x34 / 4];
    }
    
    _menuClose__14menuPdaDPMListFl(pDPMList, 0x77);
    __dt__14menuPdaDPMListFv(pDPMList, 1);
    pDPMList = NULL;
}

/*
 * menuPdaDPMList::~menuPdaDPMList()
 * Original address: 0x800510AC | size: 0xB4
 */
void __dt__14menuPdaDPMListFv(void* this, s32 flag)
{
    if (this == NULL) return;
    
    void* ptr0 = *(void**)((u32)this + 0x4C);
    if (ptr0 != NULL) {
        __dla__FPv(ptr0);
        *(void**)((u32)this + 0x4C) = NULL;
    }
    void* ptr1 = *(void**)((u32)this + 0x50);
    if (ptr1 != NULL) {
        __dla__FPv(ptr1);
        *(void**)((u32)this + 0x50) = NULL;
    }
    void* ptr2 = *(void**)((u32)this + 0x54);
    if (ptr2 != NULL) {
        __dla__FPv(ptr2);
        *(void**)((u32)this + 0x54) = NULL;
    }
    void* ptr3 = *(void**)((u32)this + 0x58);
    if (ptr3 != NULL) {
        __dla__FPv(ptr3);
        *(void**)((u32)this + 0x58) = NULL;
    }
    
    if (flag > 0) {
        __dl__FPv(this);
    }
}

/*
 * menuPdaDPMList::menuPdaDPMList()
 * Original address: 0x80051160 | size: 0x20
 */
void __ct__14menuPdaDPMListFv(void* this)
{
    *(void**)((u32)this + 0x4C) = NULL;
    *(void**)((u32)this + 0x50) = NULL;
    *(void**)((u32)this + 0x54) = NULL;
    *(void**)((u32)this + 0x58) = NULL;
    *(s32*)((u32)this + 0x0) = 0;
    *(s32*)((u32)this + 0x5C) = 0;
}

/*
 * menuPdaDPMList::GetDarkPokemonID(long)
 * Original address: 0x80051180 | size: 0x14
 */
s16 GetDarkPokemonID__14menuPdaDPMListFl(void* this, s32 index)
{
    void* sortBuff = *(void**)((u32)this + 0x50);
    return ((s16*)sortBuff)[(index * 8 + 6) / 2];
}

/*
 * menuPdaDPMList::ScrollBar
 * Original address: 0x80051194 | size: 0x70
 */
void ScrollBar__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    s32 dpNum = *(s32*)((u32)this + 0x0);
    menuPdaSubScrollBar(windowWork, spriteWork, cursor, dpNum, 0x74, 0x37, 0xa);
}

/*
 * menuPdaDPMList::DispList
 * Original address: 0x80051204 | size: 0x2A4
 */
void DispList__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    s32 dpNum = *(s32*)((u32)this + 0x0);
    
    void* itemBios1 = menuItemBiosGetPtr(0x74, 0x4b);
    void* itemBios2 = menuItemBiosGetPtr(0x74, 0x4a);
    void* itemBios3 = menuItemBiosGetPtr(0x74, 0x49);
    void* itemBios4 = menuItemBiosGetPtr(0x74, 0x45);
    void* itemBios5 = menuItemBiosGetPtr(0x74, 0x48);
    
    s16 scissorX = ((s16*)itemBios5)[0x6 / 2] - ((s16*)itemBios1)[0x6 / 2];
    s16 scissorY = ((s16*)itemBios5)[0x8 / 2] - ((s16*)itemBios1)[0x8 / 2];
    s16 scissorW = ((s16*)itemBios5)[0xA / 2];
    s16 scissorH = ((s16*)itemBios5)[0xC / 2];
    
    s32 layerId = winSpriteGetLayerID(windowWork, spriteWork);
    spriteSetScissor(layerId, scissorX, scissorY, scissorW, scissorH);
    
    float yPos = ((float*)this)[0x34 / 4];
    menuDrawReliveUpdate();
    
    s32 startIdx = cursor[0] - 1;
    s32 endIdx = cursor[0] + 0xb;
    float yStep = 0.5f;
    
    for (s32 i = 0; i < dpNum; i++) {
        if (i < startIdx || i >= endIdx) continue;
        
        s32 dpId = GetDarkPokemonID__14menuPdaDPMListFl(this, i);
        void* dp = darkPokemonGetDarkPokemon(dpId);
        
        s32 color1 = -256;
        s32 color2 = -256;
        if (isUpdate__11DarkPokemonCFv(dp)) {
            color1 = 0xd5aa3300;
            color2 = 0xd5aa3300;
        }
        
        void* name = menuPdaDPMListGetPokemonName(i);
        if (name == NULL) {
            name = GSmsgGetGSchar(1);
        }
        
        s32 placeMsgId = menuPdaDPMListGetDarkPokemonPlaceMsgID(i, NULL, NULL);
        msgctrlSetValue(0x37, name);
        
        s32 yPosInt = (s32)yPos;
        GSmsgPrint2(layerId, 0, yPosInt, color1 | ((u8*)windowWork)[0x93] << 8, 0, 0x4277, 0);
        
        menuPdaDPMListDispRelive(windowWork, spriteWork, layerId,
            ((s16*)itemBios1)[0x6 / 2] - ((s16*)itemBios2)[0x6 / 2],
            yPosInt, i, dpId);
        
        if (placeMsgId != 0) {
            u8 langArea = ((u8*)windowWork)[0x10];
            msgctrlSetValue(0x2f, langArea + 1);
            GSmsgPrint2(layerId, ((s16*)itemBios3)[0x6 / 2] - ((s16*)itemBios2)[0x6 / 2],
                yPosInt, color2 | ((u8*)windowWork)[0x93] << 8, 0, placeMsgId, 0);
        }
        
        if (isSnach__11DarkPokemonCFv(dp)) {
            s32 ballId = getCatchBallID__11DarkPokemonCFv(dp);
            s32 spriteId = mballBiosGetSpriteID(ballId);
            if (spriteId != 0) {
                s32 xPos = ((s16*)itemBios4)[0x6 / 2] - ((s16*)itemBios2)[0x6 / 2];
                windowDrawSprite2(layerId, xPos, yPosInt, spriteId, 0, 0, 0,
                    ((u8*)windowWork)[0x93] | 0xFF00, 0);
            }
        }
        
        yPos += yStep;
    }
    
    spriteClearScissor(layerId);
}

/*
 * menuPdaDPMList::DownCursor
 * Original address: 0x800514A8 | size: 0x64
 */
void DownCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    s32 dpNum = *(s32*)((u32)this + 0x0);
    menuPdaSubCheckUpDownCursor(windowWork, spriteWork, cursor, dpNum, 0xa, 0, 0);
}

/*
 * menuPdaDPMList::UpCursor
 * Original address: 0x8005150C | size: 0x64
 */
void UpCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    s32 dpNum = *(s32*)((u32)this + 0x0);
    menuPdaSubCheckUpDownCursor(windowWork, spriteWork, cursor, dpNum, 0xa, 0, 1);
}

/*
 * menuPdaDPMList::ListCursor
 * Original address: 0x80051570 | size: 0x1A0
 */
void ListCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    s32 dpNum = *(s32*)((u32)this + 0x0);
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    s16 cursorPos = ((s16*)windowWork)[0x9E / 2];
    
    // Static array of cursor positions
    static const s32 cursorTable[] = { /* "@2394" data */ };
    
    s32 matchIdx = 0xa;
    if (dpNum != 0) {
        for (s32 i = 0; i < 10; i++) {
            if (itemIndex == cursorTable[i]) {
                matchIdx = i;
                break;
            }
        }
    }
    
    // Set alpha based on cursor position
    ((u8*)spriteWork)[0x67] = ((u8*)cursorTable)[matchIdx * 4 + 4];
    
    if (cursorPos != matchIdx) {
        if (/* alpha check */) {
            winSpriteSetDisp(spriteWork, 0);
        }
    } else {
        winSpriteSetDisp(spriteWork, 1);
    }
}

/*
 * menuPdaDPMList::SortCursor
 * Original address: 0x80051710 | size: 0x10C
 */
void SortCursor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    s32 sortType = *(s32*)((u32)this + 0x48);
    
    if (itemIndex == 0x1cd) {
        if (sortType == 0) {
            winSpriteSetDisp(spriteWork, 1);
            *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
        } else {
            winSpriteSetDisp(spriteWork, 0);
            *(s32*)((u32)spriteWork + 0x64) = -1;
        }
    } else if (itemIndex == 0x1ce) {
        if (sortType == 1) {
            winSpriteSetDisp(spriteWork, 1);
            *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
        } else {
            winSpriteSetDisp(spriteWork, 0);
            *(s32*)((u32)spriteWork + 0x64) = -1;
        }
    } else if (itemIndex >= 0x1ce) {
        if (itemIndex < 0x1d0) {
            if (sortType == 2) {
                winSpriteSetDisp(spriteWork, 1);
                *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
            } else {
                winSpriteSetDisp(spriteWork, 0);
                *(s32*)((u32)spriteWork + 0x64) = -1;
            }
        }
    }
}

/*
 * menuPdaDPMList::SetItemColor
 * Original address: 0x8005181C | size: 0xA0
 */
void SetItemColor__14menuPdaDPMListFP14tagWINDOW_WORKP14tagSPRITE_WORK(void* this, void* windowWork, void* spriteWork)
{
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    s32 sortType = *(s32*)((u32)this + 0x48);
    
    if (itemIndex == 0x4c) {
        if (sortType == 2) {
            *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
        } else {
            *(s32*)((u32)spriteWork + 0x64) = -1;
        }
    } else if (itemIndex == 0x4d) {
        if (sortType == 1) {
            *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
        } else {
            *(s32*)((u32)spriteWork + 0x64) = -1;
        }
    } else if (itemIndex >= 0x4d) {
        if (itemIndex < 0x4f) {
            if (sortType == 0) {
                *(s32*)((u32)spriteWork + 0x64) = 0xffb4ff;
            } else {
                *(s32*)((u32)spriteWork + 0x64) = -1;
            }
        }
    }
}

/*
 * menuPdaDPMList::SortPlace
 * Original address: 0x800518BC | size: 0x518
 */
s32 SortPlace__14menuPdaDPMListFv(void* this)
{
    s32 dpNum = Sort__14menuPdaDPMListF10DPMSelSort(this, 2);
    *(s32*)((u32)this + 0x5C) = 0;
    s32 snatchCount = 0;
    s32 place;
    u8 type;
    
    for (s32 i = 0; i < dpNum; i++) {
        s16 dpId = GetDarkPokemonID__14menuPdaDPMListFl(this, i);
        void* dp = darkPokemonGetDarkPokemon(dpId);
        getPlace__11DarkPokemonCFR16darkPokemonWhereRUc(dp, &place, &type);
        if (isSnach__11DarkPokemonCFv(dp) && place == 1) {
            s32 pokemonId = getPokemonID__11DarkPokemonCFv(dp);
            s32 temochiIdx = getTemochiIndex__14menuPdaDPMListFUsUs(pokemonId, dpId);
            ((SnatchSortBuff*)*(void**)((u32)this + 0x54))[snatchCount].field_0 = temochiIdx;
            ((SnatchSortBuff*)*(void**)((u32)this + 0x54))[snatchCount].pokemonId = pokemonId;
            ((SnatchSortBuff*)*(void**)((u32)this + 0x54))[snatchCount].dpId = dpId;
            snatchCount++;
        }
    }
    if (snatchCount > 0) {
        SortSub__14menuPdaDPMListFP14SnatchSortBufflb(
            (SnatchSortBuff*)*(void**)((u32)this + 0x54), snatchCount, 1);
        SortSetTemp__14menuPdaDPMListFP14SnatchSortBuffP14SnatchSortBuffl(
            this, (SnatchSortBuff*)*(void**)((u32)this + 0x54),
            (SnatchSortBuff*)*(void**)((u32)this + 0x58), snatchCount);
    }
    // ... additional sorting by place values 2-8, then 5/6, then non-snatched
    *(s32*)((u32)this + 0x5C) = 0;
    SortSetTemp__14menuPdaDPMListFP14SnatchSortBuffP14SnatchSortBuffl(
        this, (SnatchSortBuff*)*(void**)((u32)this + 0x50),
        (SnatchSortBuff*)*(void**)((u32)this + 0x58), dpNum);
    return dpNum;
}

/*
 * menuPdaDPMList::getTemochiIndex
 * Original address: 0x80051DD4 | size: 0xA0
 */
s32 getTemochiIndex__14menuPdaDPMListFUsUs(u16 pokemonId, u16 dpId)
{
    void* heroData = savedataGetStatus(0, 2);
    s32 dpIdClean = dpId & 0xFFFF;
    for (s32 i = 0; i < 6; i++) {
        void* pokemon = heroBiosGetPokemonPtr(heroData, i);
        if (!pokemonCheckValid(pokemon)) continue;
        s32 darkId = pokemonBiosGetDarkpokemonDataId(pokemon);
        if ((darkId & 0xFFFF) == dpIdClean) return i;
    }
    return 0;
}

/*
 * menuPdaDPMList::SortDP
 * Original address: 0x80051E74 | size: 0x2E0
 */
s32 SortDP__14menuPdaDPMListFv(void* this)
{
    s32 dpNum = Sort__14menuPdaDPMListF10DPMSelSort(this, 1);
    *(s32*)((u32)this + 0x5C) = 0;
    // Sort by Dark Point percentage, then reliving, then normal
    // ... (sorting logic)
    *(s32*)((u32)this + 0x5C) = 0;
    SortSetTemp__14menuPdaDPMListFP14SnatchSortBuffP14SnatchSortBuffl(
        this, (SnatchSortBuff*)*(void**)((u32)this + 0x50),
        (SnatchSortBuff*)*(void**)((u32)this + 0x58), dpNum);
    return dpNum;
}

/*
 * menuPdaDPMList::SortPokemon
 * Original address: 0x80052154 | size: 0xF4
 */
s32 SortPokemon__14menuPdaDPMListFv(void* this)
{
    s32 count = 0;
    for (s32 i = 1; i < 0x80; i++) {
        void* dp = darkPokemonGetDarkPokemon(i);
        s32 pokemonId = getPokemonID__11DarkPokemonCFv(dp);
        if (pokemonId == 0) continue;
        if (getStatus__11DarkPokemonCFv(dp) < 1) continue;
        ((s16*)*(void**)((u32)this + 0x4C))[count] = pokemonId;
        ((s16*)*(void**)((u32)this + 0x4C))[count + 1] = i;
        s32 snatchIdx = getSnatchIndex__11DarkPokemonCFv(dp);
        ((SnatchSortBuff*)*(void**)((u32)this + 0x50))[count].field_0 = snatchIdx;
        ((SnatchSortBuff*)*(void**)((u32)this + 0x50))[count].pokemonId = pokemonId;
        ((SnatchSortBuff*)*(void**)((u32)this + 0x50))[count].dpId = i;
        count++;
    }
    if (count > 0) {
        SortSub__14menuPdaDPMListFP14SnatchSortBufflb(
            (SnatchSortBuff*)*(void**)((u32)this + 0x50), count, 1);
    }
    return count;
}

/*
 * menuPdaDPMList::Button
 * Original address: 0x80052248 | size: 0x90
 */
void Button__14menuPdaDPMListFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    if (windowWork == NULL) return;
    s32 dpNum = menuPdaDPMListGetDPNum();
    winSeqCheckMove(windowWork);
    if (dpNum == 0) return;
    void* keyInfo = windowGetKeyInfo();
    u16 keys = ((u16*)keyInfo)[0x4 / 2];
    if ((keys >> 27) & 1) {
        ((u8*)windowWork)[0xA4] = 1;
    }
    if ((keys >> 26) & 1) {
        ((u8*)windowWork)[0xA4] = 1;
        ((u8*)windowWork)[0xA5] = 1;
    }
}

/*
 * menuPdaDPMList::Cursor
 * Original address: 0x800522D8 | size: 0x25C
 */
void Cursor__14menuPdaDPMListFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    CURSOR localCursor;
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    localCursor[0] = ((s16*)windowWork)[0x9C / 2];
    localCursor[1] = ((s16*)windowWork)[0x9E / 2];
    s32 dpNum = menuPdaDPMListGetDPNum();
    s32 maxCursor = dpNum > 0xa ? 0xa : dpNum;
    s32 keyRepeat = windowGetKeyRepeat();
    s32 sortType = *(s32*)((u32)this + 0x48);
    
    if ((keyRepeat >> 21) & 1) {
        sortType = (sortType + 1) % 3;
        Sort__14menuPdaDPMListF10DPMSelSort(this, sortType);
    }
    if ((keyRepeat >> 22) & 1) {
        sortType = (sortType + 2) % 3;
        Sort__14menuPdaDPMListF10DPMSelSort(this, sortType);
    }
    *(s32*)((u32)this + 0x48) = sortType;
    
    if (maxCursor == 0) {
        _setCursor__14menuPdaDPMListF6CURSOR(this, &localCursor);
        ((s16*)windowWork)[0x9C / 2] = localCursor[0];
        ((s16*)windowWork)[0x9E / 2] = localCursor[1];
        return;
    }
    
    // Handle cursor movement with sound effects
    if ((keyRepeat >> 31) & 1) {
        if (localCursor[0] + localCursor[1] != 0) GSsndPlayNow(0x450);
        localCursor[1]--;
    }
    if ((keyRepeat >> 30) & 1) {
        if (localCursor[0] + localCursor[1] != dpNum - 1) GSsndPlayNow(0x450);
        localCursor[1]++;
    }
    if ((keyRepeat >> 28) & 1) {
        if (localCursor[0] + localCursor[1] != dpNum - 1) GSsndPlayNow(0x453);
        localCursor[1] += maxCursor;
    }
    if ((keyRepeat >> 29) & 1) {
        if (localCursor[0] + localCursor[1] != 0) GSsndPlayNow(0x453);
        localCursor[1] -= maxCursor;
    }
    
    // Clamp cursor
    if (localCursor[1] < 0) {
        localCursor[0] += localCursor[1];
        localCursor[1] = 0;
        if (localCursor[0] < 0) { localCursor[0] = 0; localCursor[1] = 0; }
    } else if (localCursor[1] >= maxCursor) {
        s32 overflow = localCursor[1] - (maxCursor - 1);
        localCursor[0] += overflow;
        localCursor[1] = maxCursor - 1;
        if (localCursor[0] + localCursor[1] >= dpNum) {
            localCursor[1] = dpNum - maxCursor;
            localCursor[0] = dpNum - maxCursor;
        }
    }
    
    _setCursor__14menuPdaDPMListF6CURSOR(this, &localCursor);
    ((s16*)windowWork)[0x9C / 2] = localCursor[0];
    ((s16*)windowWork)[0x9E / 2] = localCursor[1];
}

/*
 * menuPdaDPMList::Sort
 * Original address: 0x80051BEC | size: 0x124
 */
void Sort__14menuPdaDPMListF10DPMSelSort(void* this, DPMSelSort sortType)
{
    s32 dpNum;
    if (sortType == 0) {
        dpNum = SortPokemon__14menuPdaDPMListFv(this);
    } else if (sortType == 1) {
        dpNum = SortDP__14menuPdaDPMListFv(this);
    } else if (sortType >= 1) {
        if (sortType == 2) {
            dpNum = SortPlace__14menuPdaDPMListFv(this);
        } else {
            dpNum = 0;
        }
    } else {
        dpNum = 0;
    }
    *(s32*)((u32)this + 0x0) = dpNum;
    return dpNum;
}

/*
 * menuPdaDPMList::SortSetTemp
 * Original address: 0x800525A4 | size: 0x70
 */
void SortSetTemp__14menuPdaDPMListFP14SnatchSortBuffP14SnatchSortBuffl(
    void* this, SnatchSortBuff* src, SnatchSortBuff* dst, s32 count)
{
    s32 i = 0;
    while (i < count) {
        s32 idx = *(s32*)((u32)this + 0x5C);
        memcpy(dst + (idx * 8) / 8, src, 8);
        *(s32*)((u32)this + 0x5C) = idx + 1;
        dst++;
        i++;
    }
}

/*
 * menuPdaDPMList::SortSub2
 * Original address: 0x80052614 | size: 0x154
 * Insertion sort (ascending order based on first field comparison)
 */
void SortSub2__14menuPdaDPMListFP14SnatchSortBufflb(
    SnatchSortBuff* buff, s32 count, s32 ascending)
{
    s32 i, j;
    SnatchSortBuff temp;
    
    if (ascending) {
        for (i = 1; i < count; i++) {
            memcpy(&temp, buff + i, 8);
            j = i - 1;
            while (j >= 0) {
                s32 valJ = buff[j].field_0;
                s32 valTemp = temp.field_0;
                if (valJ <= valTemp) break;
                memcpy(buff + (j + 1), buff + j, 8);
                j--;
            }
            memcpy(buff + (j + 1), &temp, 8);
        }
    } else {
        for (i = 1; i < count; i++) {
            memcpy(&temp, buff + i, 8);
            j = i - 1;
            while (j >= 0) {
                s32 valJ = buff[j].field_0;
                s32 valTemp = temp.field_0;
                if (valJ >= valTemp) break;
                memcpy(buff + (j + 1), buff + j, 8);
                j--;
            }
            memcpy(buff + (j + 1), &temp, 8);
        }
    }
}

/*
 * menuPdaDPMList::SortSub
 * Original address: 0x80052768 | size: 0x18C
 * Merge sort implementation
 */
void SortSub__14menuPdaDPMListFP14SnatchSortBufflb(
    SnatchSortBuff* buff, s32 count, s32 ascending)
{
    s32 left, right, mid, i, j;
    SnatchSortBuff temp;
    
    if (ascending) {
        left = count >> 1;
        while (left > 0) {
            right = count;
            while (right > 0) {
                mid = (left + right) >> 1;
                i = 0;
                j = mid;
                while (i < left && j < right) {
                    s32 valI = buff[i].field_0;
                    s32 valJ = buff[j].field_0;
                    if (valI <= valJ) {
                        i++;
                    } else {
                        memcpy(&temp, buff + j, 8);
                        memmove(buff + (i + 1), buff + i, (j - i) * 8);
                        memcpy(buff + i, &temp, 8);
                        i++;
                        j++;
                        left++;
                        right++;
                    }
                }
                right--;
            }
            left = left >> 1;
        }
    } else {
        right = count >> 1;
        while (right > 0) {
            left = count;
            while (left > 0) {
                mid = (left + right) >> 1;
                i = 0;
                j = mid;
                while (i < left && j < right) {
                    s32 valI = buff[i].field_0;
                    s32 valJ = buff[j].field_0;
                    if (valI >= valJ) {
                        i++;
                    } else {
                        memcpy(&temp, buff + j, 8);
                        memmove(buff + (i + 1), buff + i, (j - i) * 8);
                        memcpy(buff + i, &temp, 8);
                        i++;
                        j++;
                        left++;
                        right++;
                    }
                }
                left--;
            }
            right = right >> 1;
        }
    }
}

/*
 * menuPdaDPMList::Ctrl
 * Original address: 0x800528F4 | size: 0xB4
 */
void Ctrl__14menuPdaDPMListFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    s8 state = ((u8*)windowWork)[1];
    
    if (state == 0) {
        if (((u8*)windowWork)[2] == 0) {
            winSeqSetMenu(windowWork, 0x132);
            menuPdaSetSubres(0, 1);
            ((u8*)windowWork)[2] = 1;
        }
    } else if (state == 2) {
        ListMain__14menuPdaDPMListFP14tagWINDOW_WORK(this, windowWork);
    } else if (state >= 2) {
        if (state == 3) {
            if (((u8*)windowWork)[2] == 0) {
                winSeqSetMenu(windowWork, 0x136);
                ((u8*)windowWork)[2] = 1;
            }
        }
    }
}

/*
 * menuPdaDPMList::ListMain
 * Original address: 0x800529A8 | size: 0x54
 */
void ListMain__14menuPdaDPMListFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    CURSOR* cursor = _getCursor__14menuPdaDPMListFv(this);
    ListPosition__14menuPdaDPMListFv(this);
    CalcPosition__14menuPdaDPMListFP6CURSOR(this, cursor);
    menuPdaSubCalcAlpha(this + 4, 0xa, 0, 0, 0);
}

/*
 * menuPdaDPMList::CalcPosition
 * Original address: 0x800529FC | size: 0x38
 */
void CalcPosition__14menuPdaDPMListFP6CURSOR(void* this, CURSOR* cursor)
{
    s16 cursorY = cursor[0];
    float target = (float)(-cursorY * 23);
    float current = ((float*)this)[0x3C / 4];
    ((float*)this)[0x3C / 4] = current - target;
}

/*
 * menuPdaDPMList::ListPosition
 * Original address: 0x80052A34 | size: 0x60
 */
void ListPosition__14menuPdaDPMListFv(void* this)
{
    float pos0 = ((float*)this)[0x30 / 4];
    float pos1 = ((float*)this)[0x38 / 4];
    if (pos0 != pos1) {
        menuPdaSubCalcPositon(this + 0x30, 1.0f);
    }
    float pos2 = ((float*)this)[0x34 / 4];
    float pos3 = ((float*)this)[0x3C / 4];
    if (pos2 != pos3) {
        menuPdaSubCalcPositon(this + 0x34, 1.0f);
    }
}

/*
 * menuPdaDPMList::Main
 * Original address: 0x80052A94 | size: 0xD4
 */
s32 Main__14menuPdaDPMListFlP6CURSOR(void* this, s32 result, CURSOR* cursor)
{
    CURSOR localCursor;
    localCursor[0] = cursor[0];
    localCursor[1] = cursor[1];
    _setCursor__14menuPdaDPMListF6CURSOR(this, &localCursor);
    
    while (1) {
        s32 menuResult = menuOpen(0x74, 1);
        CURSOR* newCursor = _getCursor__14menuPdaDPMListFv(this);
        localCursor[0] = newCursor[0];
        localCursor[1] = newCursor[1];
        
        if (menuResult == -1) {
            break;
        }
        if (localCursor[1] >= 0xa) {
            continue;
        }
        break;
    }
    
    _menuClose__14menuPdaDPMListFl(this, 0x74);
    
    if (menuResult == -1 || *(s32*)((u32)this + 0x0) == 0) {
        cursor[0] = localCursor[0];
        cursor[1] = localCursor[1];
        return -1;
    }
    
    cursor[0] = localCursor[0];
    cursor[1] = localCursor[1];
    return localCursor[0] + localCursor[1];
}

/*
 * menuPdaDPMList::InitWork
 * Original address: 0x80052B68 | size: 0xC4
 */
void InitWork__14menuPdaDPMListFv(void* this)
{
    s32 dpNum = *(s32*)((u32)this + 0x0);
    s32 meetNum = darkPokemonGetMeetNum();
    
    ((s16*)this)[0x2E / 2] = 0;
    ((s16*)this)[0x2C / 2] = 0;
    *(s32*)((u32)this + 0x48) = 0;
    ((float*)this)[0x30 / 4] = 0.0f;
    ((float*)this)[0x34 / 4] = 0.0f;
    ((float*)this)[0x38 / 4] = 0.0f;
    ((float*)this)[0x3C / 4] = 0.0f;
    *(s32*)((u32)this + 0x40) = 0;
    
    if (meetNum >= 0xa) {
        *(s32*)((u32)this + 0x44) = 0xa;
    } else {
        *(s32*)((u32)this + 0x44) = meetNum;
    }
    
    *(void**)((u32)this + 0x4C) = __nwa__FUl(0x200);
    *(void**)((u32)this + 0x50) = __nwa__FUl(0x400);
    *(void**)((u32)this + 0x54) = __nwa__FUl(0x400);
    *(void**)((u32)this + 0x58) = __nwa__FUl(0x400);
    
    Sort__14menuPdaDPMListF10DPMSelSort(this, *(s32*)((u32)this + 0x48));
    menuPdaSubInitAlpha(this + 4, 0xa, 0, 0, 0);
}

/*
 * menuPdaDPMList::_setCursor
 * Original address: 0x80052C2C | size: 0x30
 */
void _setCursor__14menuPdaDPMListF6CURSOR(void* this, CURSOR* cursor)
{
    cursorBiosSetPos(0xc, cursor[0]);
}

/*
 * menuPdaDPMList::_getCursor
 * Original address: 0x80052C5C | size: 0x24
 */
CURSOR* _getCursor__14menuPdaDPMListFv(void* this)
{
    return (CURSOR*)cursorBiosGetPos(0xc);
}

/*
 * menuPdaDPMList::_menuClose
 * Original address: 0x80052C80 | size: 0x3C
 */
s32 _menuClose__14menuPdaDPMListFl(void* this, s32 menuId)
{
    menuClose(menuId);
    return menuCloseSync(menuId, 1);
}

// Static data
static const u32 cursorTable[] = {
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41
};

// Global data
void* pDPMList;
