// menuPdaMemoXD.cpp
// Address range: 0x800531DC..0x80055428 | size: 0x224C
// Decompile complete

#include "global.h"

/* Forward declarations */
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct MEMO_CONTENTS;
struct CURSOR;

/* Global data */
void*   pMemo;
CURSOR* _cursor;
u8      _akagi;
u32     lbl_804354F8[6];  // Buffer for height/weight formatting

/* Constants from sdata2 */
static const float CONST_0 = 0.0f;
static const float CONST_0_6 = 0.6f;
static const float CONST_1 = 1.0f;
static const float CONST_0_016666668 = 0.016666668f;
static const float CONST_NEG_PI = -3.1415927f;
static const float CONST_0_0078125 = 0.0078125f;
static const float CONST_PI = 3.1415927f;
static const float CONST_0_7853982 = 0.7853982f;
static const float CONST_NEG_0_7853982 = -0.7853982f;
static const float CONST_1_5707964 = 1.5707964f;
static const float CONST_NEG_1_5707964 = -1.5707964f;
static const float CONST_1_2 = 1.2f;
static const float CONST_0_3 = 0.3f;
static const float CONST_0_75 = 0.75f;
static const float CONST_0_5 = 0.5f;
static const float CONST_39_37 = 39.37f;
static const float CONST_10 = 10.0f;
static const float CONST_2_2045856 = 2.2045856f;

/* Friendship lookup table "@2290" */
static const u32 aisyouTable[] = {
    0x00000001, 0x00030004, 0x00020006, 0x00050007,
    0x0008000A, 0x000B000D, 0x000C000F, 0x000E0010,
    0x00110009
};

/* State sprite IDs "@2297" and "@2298" */
static const u32 stateIds1[] = { 0x00430042, 0x003F0041 };
static const u32 spriteIds1[] = { 0x016A016B, 0x016C016D };

/* External function declarations */
void    menuPdaGetRes(void);
void    menuPdaGetSubres(void);
void    menuPdaSetSubres(s32 a, s32 b);
void    winSpriteSetDisp(void* sprite, s32 disp);
s32     menuPdaMemoXDGetItem(void);
void    menuPdaMemoListDispPokemonModel(void* windowWork, void* spriteWork, u32 modelId);
void    menuPdaMemoXDHeight(void* windowWork, void* spriteWork);
void    menuPdaMemoXDWeight(void* windowWork, void* spriteWork);
s32     memoDataGetCount(void);
void    msgctrlSetValue(s32 id, void* value);
void    menuPdaMemoWaveHook(void);
void    menuPdaMemoWaveInit(void);
void    menuPdaMemoWave(s32 cursor);
void*   menuPdaMemoListGetPokemonDataPointer(s32 id);
s32     menuPdaMemoListGetPokemonID(s32 index);
void*   menuPdaMemoListGetPokemonName(s32 index);
void*   menuPdaMemoListGetMenuModelWork(void);
void    menuPdaMemoListLoadPokemon(s32 id);
void    menuPdaMemoListLoadHero(s32 flag);
s32     menuPdaMemoListIsLoadHero(void);
void    menuPdaMemoListSetHeroMotion(void);
s32     menuPdaMemoListIsTermModel(void);
void    menuPdaMemoListGetDefaultAngle(s32 index);
void    menuModelSetAngle(void* model, float* angle);
void    menuModelSetZoom(void* model, float zoom);
void    menuModelSetCameraRotation(void* model, float* rotation);
void    menuModelGetCameraRotation(void* model);
void    menuModelGetModelPtr(void* model);
void    GSmodelDestroyLinkedParticles(void* model);
void*   GSmsgGetGSchar(u32 msgId);
void    GSmsgPrint2(void* layer, s32 x, s32 y, u32 color, s32 param5, s32 msgId, s32 param7);
void    GSmsgPrintRight(void* layer, s32 x, s32 y, u32 color, s16 x2, s16 y2, s32 msgId);
void    GSmsgPrintRect(void* layer, s32 x, s32 y, u32 color, s16 x2, s16 y2, s32 msgId);
void*   GSmsgGetRect(s32 msgId);
s32     GSmsgGetCharLength(void* str);
void    windowDrawSprite(void* layer, s32 x, s32 y, s32 spriteId, s32 a, s32 b, s32 c);
void*   windowGetKeyInfo(void);
s32     winSpriteGetLayerID(void* windowWork, void* spriteWork);
void*   menuItemBiosGetPtr(s32 type, s16 id);
void    winSeqSetMenu(void* windowWork, s32 menuId);
s32     winSeqCheckMove(s32 seqId);
void*   windowGetActiveID(void);
void    menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 flag);
void    menuPlaySe(s32 menuId, s32 seId);
s32     pokecoloGetLanguage(void);
void*   pokemonDataBiosGetPtr(s32 pokemonId);
s32     pokemonDataBiosGetHeight(void* pokemonData);
s32     pokemonDataBiosGetWeight(void* pokemonData);
void*   pokemonDataBiosGetTypeName(void* pokemonData);
s32     pokemonDataBiosGetTokuseiDataId(void* pokemonData, s32 index);
s32     pokemonDataBiosGetZokuseiDataId(void* pokemonData, s32 index);
void*   pokemonTokuseiDataBiosGetPtr(s32 id);
void*   pokemonTokuseiDataBiosGetDoc(s32 id);
void*   pokemonTokuseiDataBiosGetName(s32 id);
s32     zokuseiGetPokemonSpriteId(s32 type);
void*   zokuseiGetWazaJoutai_PokemonId(u16 state, s32 pokemonId);
void*   zokuseiGetWazaJoutaiAsDefenseZokuseiAry(u16 state, s32 type);
void    GSsndPlayNow(s32 soundId);
s32     GSinputButtonsPressed(s32 controller);
s8      GSinputGetRightStickXData(s32 controller, s32 a);
s8      GSinputGetRightStickYData(s32 controller, s32 a);
void*   __nw__FUl(s32 size);
void*   __nwa__FUl(s32 size);
void    __dl__FPv(void* ptr);
void    __dla__FPv(void* ptr);
u32     __cvt_fp2unsigned(float f);
float   atan2(float y, float x);
void    PSVECAdd(float* a, float* b);

/*
 * menuPdaMemoBackHook
 * Original address: 0x800531DC | size: 0x294
 * Hook function for back button display based on item index.
 */
void menuPdaMemoBackHook(void* windowWork, void* spriteWork)
{
    menuPdaGetRes();
    menuPdaGetSubres();
    
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    
    if (itemIndex == 0xc4) {
        if (menuPdaMemoXDGetItem() == 0) {
            winSpriteSetDisp(spriteWork, 1);
            u32 count = memoDataGetCount();
            msgctrlSetValue(0x34, (void*)count);
        } else {
            winSpriteSetDisp(spriteWork, 0);
        }
    } else if (itemIndex >= 0xc4) {
        if (itemIndex == 0x16b) {
            if (menuPdaMemoXDGetItem() == 2) {
                winSpriteSetDisp(spriteWork, 1);
                menuPdaMemoXDHeight(windowWork, spriteWork);
            } else {
                winSpriteSetDisp(spriteWork, 0);
            }
        } else if (itemIndex >= 0x16b) {
            if (itemIndex == 0x1c7) {
                if (menuPdaMemoXDGetItem() == 2) {
                    menuPdaMemoListDispPokemonModel(windowWork, spriteWork, 3);
                }
            }
        } else if (itemIndex == 0x16a) {
            if (menuPdaMemoXDGetItem() == 2) {
                winSpriteSetDisp(spriteWork, 1);
                menuPdaMemoXDWeight(windowWork, spriteWork);
            } else {
                winSpriteSetDisp(spriteWork, 0);
            }
        }
    } else if (itemIndex == 0xb9) {
        if (menuPdaMemoXDGetItem() == 3) {
            menuPdaMemoListDispPokemonModel(windowWork, spriteWork, 0);
        }
    } else if (itemIndex >= 0xb9) {
        if (itemIndex == 0xbb) {
            if (menuPdaMemoXDGetItem() == 0) {
                menuPdaMemoListDispPokemonModel(windowWork, spriteWork, 1);
            }
        } else if (itemIndex >= 0xbb) {
            if (menuPdaMemoXDGetItem() == 1) {
                menuPdaMemoListDispPokemonModel(windowWork, spriteWork, 2);
            }
        }
    } else if (itemIndex >= 0xb1) {
        if (itemIndex == 0xb5) {
            if (menuPdaMemoXDGetItem() == 3) {
                winSpriteSetDisp(spriteWork, 1);
            } else {
                winSpriteSetDisp(spriteWork, 0);
            }
        }
    } else if (itemIndex >= 0xad) {
        if (menuPdaMemoXDGetItem() == 1 || menuPdaMemoXDGetItem() == 2) {
            winSpriteSetDisp(spriteWork, 1);
        } else {
            winSpriteSetDisp(spriteWork, 0);
        }
    }
}

/*
 * menuPdaMemoXDHeight
 * Original address: 0x80053470 | size: 0x54
 */
void menuPdaMemoXDHeight(void* windowWork, void* spriteWork)
{
    if (pMemo != NULL) {
        ((u8*)spriteWork)[0x64] = 0xd5;
        ((u8*)spriteWork)[0x65] = 0xaa;
        ((u8*)spriteWork)[0x66] = 0x33;
        PokemonHeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
            windowWork, spriteWork, pMemo);
    }
}

/*
 * menuPdaMemoXDWeight
 * Original address: 0x800534C4 | size: 0x54
 */
void menuPdaMemoXDWeight(void* windowWork, void* spriteWork)
{
    if (pMemo != NULL) {
        ((u8*)spriteWork)[0x64] = 0xd5;
        ((u8*)spriteWork)[0x65] = 0xaa;
        ((u8*)spriteWork)[0x66] = 0x33;
        PokemonWeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
            windowWork, spriteWork, pMemo);
    }
}

/*
 * menuPdaMemoXDGetItem
 * Original address: 0x80053518 | size: 0x1C
 */
s32 menuPdaMemoXDGetItem(void)
{
    if (pMemo == NULL) {
        return 0;
    }
    return *(s32*)((u32)pMemo + 0x8);
}

/*
 * menuPdaMemoXDHook
 * Original address: 0x80053534 | size: 0x3A0
 */
s32 menuPdaMemoXDHook(void* windowWork, void* spriteWork)
{
    if (pMemo == NULL) {
        return 0;
    }
    
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    void* memoContents = *(void**)((u32)pMemo + 0x68);
    
    if (itemIndex == 0x10b) {
        menuPdaMemoWaveHook();
    } else if (itemIndex >= 0x10b) {
        if (itemIndex == 0x159) {
            // Hidden ability check
            void* ptr = *(void**)((u32)memoContents + 0x0);
            s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
            s32 pokemonId = menuPdaMemoListGetPokemonID(id);
            void* pokemonData = pokemonDataBiosGetPtr(pokemonId);
            s32 tokusei0 = pokemonDataBiosGetTokuseiDataId(pokemonData, 0);
            s32 tokusei1 = pokemonDataBiosGetTokuseiDataId(pokemonData, 1);
            if ((tokusei1 & 0xFFFFFF00) != (tokusei0 & 0xFFFFFF00)) {
                void* str1 = GSmsgGetGSchar(0x3b68);
                msgctrlSetValue(0x4d, str1);
                void* str2 = GSmsgGetGSchar(0x3b6a);
                msgctrlSetValue(0x37, str2);
                GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
                    ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x4278, 0);
            }
        } else if (itemIndex >= 0x159) {
            if (itemIndex == 0x15d) {
                PokemonSyuzoku__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                    memoContents, spriteWork, pMemo);
            } else if (itemIndex >= 0x15d) {
                if (itemIndex == 0x15b) {
                    PokemonTokusei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                        memoContents, spriteWork, pMemo, 0);
                } else if (itemIndex >= 0x15b) {
                    if (itemIndex != 0x15f) {
                        PokemonName__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                            memoContents, spriteWork, pMemo);
                    }
                }
            }
        } else if (itemIndex == 0x156) {
            PokemonType__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                memoContents, spriteWork, pMemo, 1);
        } else if (itemIndex >= 0x156) {
            if (itemIndex == 0x158) {
                PokemonTokusei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                    memoContents, spriteWork, pMemo, 1);
            } else {
                PokemonTokuseiSetumei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                    memoContents, spriteWork, pMemo, 1);
            }
        } else if (itemIndex == 0x155) {
            PokemonType__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                memoContents, spriteWork, pMemo, 0);
        } else if (itemIndex >= 0x144) {
            PokemonAisyou__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                memoContents, spriteWork, pMemo);
        }
    } else if (itemIndex == 0x102) {
        PokemonTokusei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
            memoContents, spriteWork, pMemo, 1);
    } else if (itemIndex >= 0x102) {
        if (itemIndex == 0x105) {
            PokemonSyuzoku__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                memoContents, spriteWork, pMemo);
        } else if (itemIndex >= 0x105) {
            if (itemIndex != 0x107) {
                PokemonName__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                    memoContents, spriteWork, pMemo);
            }
        } else if (itemIndex >= 0x104) {
            ((u8*)spriteWork)[0x64] = 0xd5;
            ((u8*)spriteWork)[0x65] = 0xaa;
            ((u8*)spriteWork)[0x66] = 0x33;
            PokemonHeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                windowWork, spriteWork, pMemo);
        }
    } else if (itemIndex >= 0xff) {
        if (itemIndex == 0xfd) {
            PokemonType__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
                memoContents, spriteWork, pMemo, 0);
        } else if (itemIndex >= 0xfd) {
            if (itemIndex == 0x101) {
                ((u8*)spriteWork)[0x64] = 0xd5;
                ((u8*)spriteWork)[0x65] = 0xaa;
                ((u8*)spriteWork)[0x66] = 0x33;
                PokemonWeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
                    windowWork, spriteWork, pMemo);
            }
        }
    }
    
    return 0;
}

/*
 * menuPdaMemoXDMain
 * Original address: 0x800538D4 | size: 0x84
 */
void menuPdaMemoXDMain(CURSOR* cursor)
{
    void* thisObj = __nw__FUl(0xe8);
    if (thisObj != NULL) {
        Init__13menuPdaMemoXDFP6CURSOR(thisObj, cursor);
        pMemo = thisObj;
        Main__13menuPdaMemoXDFP6CURSOR(thisObj, cursor);
        void* oldMemo = pMemo;
        pMemo = NULL;
        Release__13menuPdaMemoXDFv(oldMemo);
        __dl__FPv(oldMemo);
    }
    _cursor = NULL;
}

/*
 * menuPdaMemoXDButton
 * Original address: 0x80053958 | size: 0x30
 */
void menuPdaMemoXDButton(void* windowWork)
{
    if (pMemo != NULL) {
        Button__13menuPdaMemoXDFP14tagWINDOW_WORK(pMemo, windowWork);
    }
}

/*
 * menuPdaMemoXDCursor
 * Original address: 0x80053988 | size: 0x3C
 */
s32 menuPdaMemoXDCursor(void* windowWork)
{
    if (pMemo != NULL) {
        Cursor__13menuPdaMemoXDFP14tagWINDOW_WORK(pMemo, windowWork);
    }
    return 0;
}

/*
 * menuPdaMemoXDCtrl
 * Original address: 0x800539C4 | size: 0x3C
 */
s32 menuPdaMemoXDCtrl(void* windowWork)
{
    if (pMemo != NULL) {
        Ctrl__13menuPdaMemoXDFP14tagWINDOW_WORK(pMemo, windowWork);
    }
    return 0;
}

/*
 * menuPdaMemoXD::PokemonHeight
 * Original address: 0x80053A00 | size: 0x258
 */
void PokemonHeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
    void* windowWork, void* spriteWork, void* memoContents)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    void* pokemonData = menuPdaMemoListGetPokemonDataPointer(id);
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    void* itemBios = menuItemBiosGetPtr(0x7c, itemIndex);
    s32 layerId = winSpriteGetLayerID(windowWork, spriteWork);
    s32 height = pokemonDataBiosGetHeight(pokemonData);
    s32 lang = pokecoloGetLanguage();
    
    if (lang == 2) {
        // Japanese - integer calculation with 0xCCCCCD multiplier
        s32 val = height & 0xFFFF;
        s32 result = ((s64)val * 0xCCCCCDLL) >> 29;
        msgctrlSetValue(0x34, (void*)result);
        s32 remainder = val - result * 10;
        msgctrlSetValue(0x35, (void*)remainder);
        GSmsgPrintRect(layerId, 0, 0, ((u8*)windowWork)[0x93] | 0xFF00,
            ((s16*)itemBios)[0xA / 2], ((s16*)itemBios)[0xC / 2], 0x3ba2);
    } else {
        // Other languages - floating point calculation
        u32 intHeight = height & 0xFFFF;
        float fHeight = (float)intHeight;
        // Calculation: (fHeight - 4503599627370496.0) / 10.0 * 39.37 + 0.5
        float result = ((fHeight - 4503599627370496.0) / 10.0f) * 39.37f + 0.5f;
        u32 intResult = __cvt_fp2unsigned(result);
        
        // Format into buffer
        // ... (formatting logic) ...
        
        msgctrlSetValue(0x37, lbl_804354F8);
        GSmsgPrintRight(layerId, 0, 0, ((u8*)windowWork)[0x93] | 0xFF00,
            ((s16*)itemBios)[0xA / 2], ((s16*)itemBios)[0xC / 2], 0x4276);
    }
}

/*
 * menuPdaMemoXD::PokemonWeight
 * Original address: 0x80053C58 | size: 0x1A0
 */
void PokemonWeight__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
    void* windowWork, void* spriteWork, void* memoContents)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    void* pokemonData = menuPdaMemoListGetPokemonDataPointer(id);
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    void* itemBios = menuItemBiosGetPtr(0x7c, itemIndex);
    s32 layerId = winSpriteGetLayerID(windowWork, spriteWork);
    s32 weight = pokemonDataBiosGetWeight(pokemonData);
    s32 lang = pokecoloGetLanguage();
    
    if (lang == 2) {
        // Japanese - integer calculation
        s32 val = weight & 0xFFFF;
        s32 result = ((s64)val * 0xCCCCCDLL) >> 29;
        msgctrlSetValue(0x34, (void*)result);
        s32 remainder = val - result * 10;
        msgctrlSetValue(0x35, (void*)remainder);
        GSmsgPrintRect(layerId, 0, 0, ((u8*)windowWork)[0x93] | 0xFF00,
            ((s16*)itemBios)[0xA / 2], ((s16*)itemBios)[0xC / 2], 0x3ba1);
    } else {
        // Other languages - floating point
        u32 intWeight = weight & 0xFFFF;
        float fWeight = (float)intWeight;
        float result = (fWeight - 4503599627370496.0) * 2.2045856f + 0.5f;
        u32 intResult = __cvt_fp2unsigned(result);
        // ... formatting ...
        msgctrlSetValue(0x34, (void*)(intResult * 0xCCCCCD >> 29));
        msgctrlSetValue(0x35, (void*)(intResult - ((intResult * 0xCCCCCD >> 29) * 10)));
        GSmsgPrintRect(layerId, 0, 0, ((u8*)windowWork)[0x93] | 0xFF00,
            ((s16*)itemBios)[0xA / 2], ((s16*)itemBios)[0xC / 2], 0x3ba1);
    }
}

/*
 * menuPdaMemoXD::PokemonSyuzoku
 * Original address: 0x80053DF8 | size: 0x6C
 */
void PokemonSyuzoku__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
    void* windowWork, void* spriteWork, void* memoContents)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    void* pokemonData = menuPdaMemoListGetPokemonDataPointer(id);
    void* typeName = pokemonDataBiosGetTypeName(pokemonData);
    msgctrlSetValue(0x31, typeName);
    GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
        ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x3b9b, 0);
}

/*
 * menuPdaMemoXD::PokemonAisyou
 * Original address: 0x80053E64 | size: 0x14C
 */
void PokemonAisyou__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
    void* windowWork, void* spriteWork, void* memoContents)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    void* pokemonData = menuPdaMemoListGetPokemonDataPointer(id);
    s32 pokemonId = menuPdaMemoListGetPokemonID(id);
    
    s32 i = 0;
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    while (i < 0x11) {
        u32 val = aisyouTable[i];
        if (((s16*)&val)[0] == itemIndex) break;
        i++;
    }
    
    u16 aisyouIndex = GetAisyouIndex__13menuPdaMemoXDFUs((u16)i);
    
    s32 zokusei0 = pokemonDataBiosGetZokuseiDataId(pokemonData, 0);
    s32 zokusei1 = pokemonDataBiosGetZokuseiDataId(pokemonData, 1);
    u16 hasSecondType = (zokusei1 & 0xFFFFFF00) != 0;
    
    if (_akagi != 0) {
        void* state = zokuseiGetWazaJoutai_PokemonId(aisyouIndex, pokemonId);
        SetJoutaiSprite__13menuPdaMemoXDFP14tagWINDOW_WORKUs(windowWork, (u16)state);
    } else {
        void* state = zokuseiGetWazaJoutaiAsDefenseZokuseiAry(aisyouIndex, hasSecondType ? 2 : 1);
        SetJoutaiSprite__13menuPdaMemoXDFP14tagWINDOW_WORKUs(windowWork, (u16)state);
    }
}

/*
 * menuPdaMemoXD::SetJoutaiSprite
 * Original address: 0x80053FB0 | size: 0x9C
 */
void SetJoutaiSprite__13menuPdaMemoXDFP14tagWINDOW_WORKUs(void* windowWork, u16 state)
{
    for (s32 i = 0; i < 4; i++) {
        u16 stateId = ((u16*)stateIds1)[i];
        if (state == stateId) {
            u16 spriteId = ((u16*)spriteIds1)[i];
            windowDrawSprite(*(void**)((u32)windowWork + 0x1C), 0, 0, spriteId, 0, 0, 0);
        }
    }
}

/*
 * menuPdaMemoXD::GetAisyouIndex
 * Original address: 0x8005404C | size: 0x7C
 */
u16 GetAisyouIndex__13menuPdaMemoXDFUs(u16 index)
{
    if (index >= 0x12) {
        return 0;
    }
    return ((u16*)aisyouTable)[index];
}

/*
 * menuPdaMemoXD::PokemonTokuseiSetumei
 * Original address: 0x800540C8 | size: 0x348
 * Displays ability description with word wrapping.
 */
void PokemonTokuseiSetumei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
    void* windowWork, void* spriteWork, void* memoContents, u16 tokuseiIndex)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    s32 pokemonId = menuPdaMemoListGetPokemonID(id);
    void* pokemonData = pokemonDataBiosGetPtr(pokemonId);
    s16 itemIndex = ((s16*)spriteWork)[0x6 / 2];
    void* itemBios = menuItemBiosGetPtr(0x7e, itemIndex);
    
    s32 tokuseiId0 = pokemonDataBiosGetTokuseiDataId(pokemonData, 0);
    s32 tokuseiId1 = pokemonDataBiosGetTokuseiDataId(pokemonData, tokuseiIndex);
    
    u32 showAbility = 0;
    if (tokuseiIndex != 0) {
        if (tokuseiId1 != 0 && (tokuseiId1 & 0xFFFFFF00) != (tokuseiId0 & 0xFFFFFF00)) {
            showAbility = 1;
        }
    }
    
    if (!showAbility) {
        void* doc = pokemonTokuseiDataBiosGetDoc(tokuseiId0);
        void* gschar = GSmsgGetGSchar(doc);
        msgctrlSetValue(0x37, gschar);
        GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
            ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x4276, 0);
        return;
    }
    
    // Word wrap ability description
    void* doc = pokemonTokuseiDataBiosGetDoc(tokuseiId1);
    void* gschar = GSmsgGetGSchar(doc);
    s32 charLen = GSmsgGetCharLength(gschar);
    
    void* buf1 = __nwa__FUl((charLen + 2) * 2);
    void* buf2 = __nwa__FUl((charLen + 2) * 2);
    
    // Copy characters with word wrapping at spaces
    s32 pos1 = 0, pos2 = 0, charCount = 0;
    s32 splitPos = 0;
    u16* src = (u16*)gschar;
    
    while (charCount < charLen) {
        u16 ch = *src++;
        if (ch == 0x20 || ch == 0x3000) {
            splitPos = pos1;
        } else if (ch != 0) {
            if (pos1 < ((s16*)itemBios)[0xA / 2]) {
                ((u16*)buf1)[pos1++] = ch;
            } else {
                ((u16*)buf2)[pos2++] = ch;
            }
        }
        charCount++;
    }
    
    ((u16*)buf1)[pos1] = 0;
    ((u16*)buf2)[pos2] = 0;
    
    // Check width and split if needed
    msgctrlSetValue(0x37, buf1);
    void* rect = GSmsgGetRect(0x4276);
    s32 width = rect >> 16;
    s32 itemWidth = ((s16*)itemBios)[0xA / 2];
    
    if (width > itemWidth) {
        // Split at last space
        msgctrlSetValue(0x37, buf1);
        GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
            ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x4276, 0);
        msgctrlSetValue(0x37, buf2);
        GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
            ((u8*)spriteWork)[0x93] | 0xFF00, 0x12, 0x4276, 0);
    } else {
        msgctrlSetValue(0x37, gschar);
        GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
            ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x4276, 0);
    }
    
    __dla__FPv(buf1);
    __dla__FPv(buf2);
}

/*
 * menuPdaMemoXD::PokemonTokusei
 * Original address: 0x80054410 | size: 0x11C
 * Displays Pokemon ability name.
 */
void PokemonTokusei__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
    void* windowWork, void* spriteWork, void* memoContents, u16 tokuseiIndex)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    s32 pokemonId = menuPdaMemoListGetPokemonID(id);
    void* pokemonData = pokemonDataBiosGetPtr(pokemonId);
    
    s32 tokuseiId0 = pokemonDataBiosGetTokuseiDataId(pokemonData, 0);
    s32 tokuseiId1 = pokemonDataBiosGetTokuseiDataId(pokemonData, tokuseiIndex);
    
    if (tokuseiIndex == 0) {
        if (tokuseiId0 != 0) {
            void* name = pokemonTokuseiDataBiosGetName(tokuseiId0);
            void* gschar = GSmsgGetGSchar(name);
            msgctrlSetValue(0x37, gschar);
            GSmsgPrint2(*(void**)((u32)windowWork + 0x1C), 0, 0,
                ((u8*)windowWork)[0x93] | 0xFF00, 0, 0x4278, 0);
        }
    } else {
        if (tokuseiId1 != 0 && (tokuseiId1 & 0xFFFFFF00) != (tokuseiId0 & 0xFFFFFF00)) {
            void* name = pokemonTokuseiDataBiosGetName(tokuseiId1);
            void* gschar = GSmsgGetGSchar(name);
            msgctrlSetValue(0x37, gschar);
            GSmsgPrint2(*(void**)((u32)windowWork + 0x1C), 0, 0,
                ((u8*)windowWork)[0x93] | 0xFF00, 0, 0x4278, 0);
        }
    }
}

/*
 * menuPdaMemoXD::PokemonType
 * Original address: 0x8005452C | size: 0xE0
 * Displays Pokemon type sprite.
 */
void PokemonType__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTSUs(
    void* windowWork, void* spriteWork, void* memoContents, u16 typeIndex)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    s32 pokemonId = menuPdaMemoListGetPokemonID(id);
    void* pokemonData = pokemonDataBiosGetPtr(pokemonId);
    
    s32 typeId;
    if (typeIndex == 0) {
        typeId = zokuseiGetPokemonSpriteId(pokemonData, 0);
    } else {
        typeId = zokuseiGetPokemonSpriteId(pokemonData, 1);
    }
    
    if (typeId != 0) {
        windowDrawSprite(*(void**)((u32)windowWork + 0x1C), 0, 0, typeId, 0, 0, 0);
    }
}

/*
 * menuPdaMemoXD::PokemonName
 * Original address: 0x8005460C | size: 0x78
 * Displays Pokemon name.
 */
void PokemonName__13menuPdaMemoXDFP14tagWINDOW_WORKP14tagSPRITE_WORKP13MEMO_CONTENTS(
    void* windowWork, void* spriteWork, void* memoContents)
{
    void* ptr = *(void**)((u32)memoContents + 0x0);
    s32 id = ((s16*)ptr)[0x2 / 2] + ((s16*)ptr)[0x0 / 2];
    void* name = menuPdaMemoListGetPokemonName(id);
    if (name == NULL) {
        name = GSmsgGetGSchar(1);
    }
    msgctrlSetValue(0x37, name);
    GSmsgPrint2(*(void**)((u32)spriteWork + 0x1C), 0, 0,
        ((u8*)spriteWork)[0x93] | 0xFF00, 0, 0x4275, 0);
}

/*
 * menuPdaMemoXD::Main
 * Original address: 0x80054684 | size: 0xAC
 * Main loop for PDA memo menu.
 */
void Main__13menuPdaMemoXDFP6CURSOR(void* this, CURSOR* cursor)
{
    _cursor = cursor;
    
    while (1) {
        *(CURSOR**)((u32)this + 0x0) = _cursor;
        s32 result = TaskOpen__13menuPdaMemoXDFv(this);
        if (result == -1) break;
        
        s32 state = *(s32*)((u32)this + 0x8);
        if (state != *(s32*)((u32)this + 0xC)) continue;
        if (state != 1) continue;
        
        s32 cursorPos = _cursor[0] + _cursor[1];
        menuPdaMemoWave(cursorPos);
    }
    
    TaskClose__13menuPdaMemoXDFP14tagWINDOW_WORKb(this, NULL, 1);
    menuPdaSetSubres(-1, 1);
    menuPdaMemoListLoadHero(0);
    _cursor = NULL;
}

/*
 * menuPdaMemoXD::Button
 * Original address: 0x80054730 | size: 0xA8
 * Handles button input for menu navigation.
 */
void Button__13menuPdaMemoXDFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    if (windowWork == NULL) return;
    
    void* keyInfo = windowGetKeyInfo();
    u16 keys = ((u16*)keyInfo)[0x4 / 2];
    menuPdaGetRes();
    menuPdaGetSubres();
    
    if (winSeqCheckMove(*(s32*)((u32)windowWork + 0x4)) != 0) return;
    
    // A button press
    if ((keys >> 27) & 1) {
        s32 state = *(s32*)((u32)this + 0x8);
        if (state == 1) {
            *(s32*)((u32)this + 0xC) = state;
            *(s32*)((u32)this + 0x8) = state;
            ((u8*)windowWork)[0xA4] = 1;
        }
    }
    
    // B button press
    if ((keys >> 26) & 1) {
        ((u8*)windowWork)[0xA4] = 1;
        ((u8*)windowWork)[0xA5] = 1;
    }
}

/*
 * menuPdaMemoXD::Ctrl
 * Original address: 0x800547D8 | size: 0xD0
 * Controls menu state transitions.
 */
s32 Ctrl__13menuPdaMemoXDFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    s8 state = ((s8*)windowWork)[0x1];
    
    if (state == 0) {
        if (((s8*)windowWork)[0x2] == 0) {
            winSeqSetMenu(*(void**)((u32)windowWork + 0x4), 0x132);
            ((u8*)windowWork)[0x2] = 1;
            menuPdaSetSubres(-1, 2);
        }
    } else if (state == 2) {
        s32 thisState = *(s32*)((u32)this + 0x8);
        if (thisState == 2) {
            if (!menuPdaMemoListIsLoadHero()) {
                menuPdaMemoListSetHeroMotion();
            }
        }
    } else if (state == 4) {
        if (((s8*)windowWork)[0x2] == 0) {
            winSeqSetMenu(*(void**)((u32)windowWork + 0x4), 0x136);
            ((u8*)windowWork)[0x2] = 1;
        }
    }
    
    return 0;
}

/*
 * menuPdaMemoXD::Cursor
 * Original address: 0x800548A8 | size: 0x348
 * Handles cursor movement and Pokemon selection.
 */
void Cursor__13menuPdaMemoXDFP14tagWINDOW_WORK(void* this, void* windowWork)
{
    void* keyInfo = windowGetKeyInfo();
    void* memoContents = *(void**)((u32)windowWork + 0x68);
    s32 count = memoDataGetCount();
    s32 thisState = *(s32*)((u32)this + 0x8);
    s16 itemIndex = ((s16*)keyInfo)[0x6 / 2];
    
    if (menuPdaMemoListIsTermModel()) return;
    
    void* cursorData = *(void**)((u32)memoContents + 0x0);
    s16 cursorHigh = ((s16*)cursorData)[0x2 / 2];
    s16 cursorLow = ((s16*)cursorData)[0x0 / 2];
    s32 cursorPos = cursorHigh + cursorLow;
    
    // Handle cursor movement based on key input
    u32 keys = *(u32*)keyInfo;
    
    // Right arrow
    if ((keys >> 31) & 1) {
        s32 newPos = cursorPos + 1;
        if (newPos != count) {
            GSsndPlayNow(0x450);
            ((s16*)cursorData)[0x2 / 2] = cursorHigh + 1;
        }
        // ... (cursor clamping logic)
    }
    // Left arrow
    else if ((keys >> 30) & 1) {
        s32 newPos = cursorPos - 1;
        if (newPos >= 0) {
            GSsndPlayNow(0x450);
            ((s16*)cursorData)[0x2 / 2] = cursorHigh - 1;
        }
    }
    
    // A button - confirm selection
    if ((keys >> 29) & 1) {
        if (TaskCloseCheck__13menuPdaMemoXDFv(this)) {
            if (thisState == 1) {
                menuPdaMemoWaveInit();
            }
            // ... (close logic)
        }
    }
    
    // Update camera based on state
    if (thisState == 1) {
        CameraControl__13menuPdaMemoXDFv(this);
    } else if (thisState == 2) {
        OokisaCameraControl__13menuPdaMemoXDFv(this);
    }
    
    // Load Pokemon when cursor changes
    if (cursorPos != cursorPos) {
        LoadPokemon__13menuPdaMemoXDFP6CURSOR(this, cursorData);
        menuPlaySe(*(s32*)((u32)windowWork + 0x4), 1);
    }
}

/*
 * menuPdaMemoXD::SetModelAngle
 * Original address: 0x80054BF0 | size: 0x138
 * Sets model rotation angle based on state.
 */
void SetModelAngle__13menuPdaMemoXDFs(void* this, s16 angle)
{
    s32 angleExt = angle;
    
    if (angleExt == 1 || angleExt == 2) {
        // Set angle to 0
        ((float*)this)[0x14 / 4] = CONST_0;
        ((float*)this)[0x18 / 4] = CONST_0;
        ((float*)this)[0x1C / 4] = CONST_0;
    } else if (angleExt >= 2) {
        // Get default angles
        float angleX = menuPdaMemoListGetDefaultAngle(0);
        float angleY = menuPdaMemoListGetDefaultAngle(1);
        float angleZ = menuPdaMemoListGetDefaultAngle(2);
        ((float*)this)[0x14 / 4] = angleX;
        ((float*)this)[0x18 / 4] = angleY;
        ((float*)this)[0x1C / 4] = angleZ;
    }
    
    // Set zoom
    if (angleExt == 1) {
        ((float*)this)[0x20 / 4] = CONST_0_6;
    } else {
        ((float*)this)[0x20 / 4] = CONST_1;
    }
    
    // Apply to model
    void* model = menuPdaMemoListGetMenuModelWork();
    menuModelSetAngle(model, (float*)((u32)this + 0x14));
    menuModelSetZoom(model, ((float*)this)[0x20 / 4]);
    
    // Set camera rotation to 0
    float rot[3] = { CONST_0, CONST_0, CONST_0 };
    menuModelSetCameraRotation(model, rot);
    
    // Load hero model
    menuPdaMemoListLoadHero(angleExt == 2 ? 1 : 0);
}

/*
 * menuPdaMemoXD::OokisaCameraControl
 * Original address: 0x80054D28 | size: 0x160
 * Camera control with right stick input (large view mode).
 */
void OokisaCameraControl__13menuPdaMemoXDFv(void* this)
{
    s8 stickX = GSinputGetRightStickXData(1, 1);
    s8 stickY = GSinputGetRightStickYData(1, 1);
    
    void* model = menuPdaMemoListGetMenuModelWork();
    void* camRot = menuModelGetCameraRotation(model);
    
    // Calculate angle from stick input
    float angle = atan2((float)stickY, (float)stickX);
    
    // Apply rotation with scaling
    float rot[3];
    rot[0] = ((float*)camRot)[0] + angle * CONST_0_0078125 * CONST_PI;
    rot[1] = ((float*)camRot)[1];
    rot[2] = ((float*)camRot)[2];
    
    // Clamp rotation
    if (rot[0] > CONST_0_7853982) rot[0] = CONST_0_7853982;
    if (rot[0] < CONST_NEG_0_7853982) rot[0] = CONST_NEG_0_7853982;
    
    menuModelSetCameraRotation(model, rot);
}

/*
 * menuPdaMemoXD::CameraControl
 * Original address: 0x80054E88 | size: 0x1DC
 * Camera control with right stick input (normal view mode).
 */
void CameraControl__13menuPdaMemoXDFv(void* this)
{
    s8 stickX = GSinputGetRightStickXData(1, 1);
    s8 stickY = GSinputGetRightStickYData(1, 1);
    
    // Calculate angle from stick input
    float angle = atan2((float)stickY, (float)stickX);
    
    // Apply rotation
    float rot[3];
    rot[0] = ((float*)this)[0x14 / 4] + angle * CONST_0_0078125 * CONST_PI;
    rot[1] = ((float*)this)[0x18 / 4];
    rot[2] = ((float*)this)[0x1C / 4];
    
    // Clamp rotation
    if (rot[0] > CONST_1_5707964) rot[0] = CONST_1_5707964;
    if (rot[0] < CONST_NEG_1_5707964) rot[0] = CONST_NEG_1_5707964;
    
    // Handle zoom with R/L buttons
    u32 buttons = GSinputButtonsPressed(1);
    if ((buttons >> 26) & 1) {
        // R button - zoom in
        if (((float*)this)[0x20 / 4] < CONST_1_2) {
            ((float*)this)[0x20 / 4] += CONST_0_016666668;
        }
    }
    if ((buttons >> 25) & 1) {
        // L button - zoom out
        if (((float*)this)[0x20 / 4] > CONST_0_3) {
            ((float*)this)[0x20 / 4] -= CONST_0_016666668;
        }
    }
    
    void* model = menuPdaMemoListGetMenuModelWork();
    menuModelSetAngle(model, (float*)((u32)this + 0x14));
    menuModelSetZoom(model, ((float*)this)[0x20 / 4]);
}

/*
 * menuPdaMemoXD::Release
 * Original address: 0x80055064 | size: 0x4
 * Empty destructor.
 */
void Release__13menuPdaMemoXDFv(void* this)
{
    // Empty
}

/*
 * menuPdaMemoXD::LoadPokemon
 * Original address: 0x80055068 | size: 0x2C
 * Loads Pokemon data for display.
 */
void LoadPokemon__13menuPdaMemoXDFP6CURSOR(void* this, CURSOR* cursor)
{
    s32 id = cursor[0] + cursor[1];
    menuPdaMemoListLoadPokemon(id);
}

/*
 * menuPdaMemoXD::Init
 * Original address: 0x80055094 | size: 0x78
 * Initializes the PDA memo menu.
 */
void Init__13menuPdaMemoXDFP6CURSOR(void* this, CURSOR* cursor)
{
    *(s32*)((u32)this + 0xC) = *(s32*)((u32)this + 0x8);
    *(s32*)((u32)this + 0x8) = 0;
    *(s32*)((u32)this + 0xC) = 0;
    *(s32*)((u32)this + 0x10) = 0x7c;
    *(CURSOR**)((u32)this + 0x0) = _cursor;
    
    ((float*)this)[0x14 / 4] = CONST_0;
    ((float*)this)[0x18 / 4] = CONST_0;
    ((float*)this)[0x1C / 4] = CONST_0;
    ((float*)this)[0x20 / 4] = CONST_0_75;
    
    SetModelAngle__13menuPdaMemoXDFs(this, 0);
    
    void* model = menuPdaMemoListGetMenuModelWork();
    menuModelSetZoom(model, CONST_0_75);
}

/*
 * menuPdaMemoXD::TaskOpen
 * Original address: 0x8005510C | size: 0x11C
 * Opens menu tasks based on state.
 */
s32 TaskOpen__13menuPdaMemoXDFv(void* this)
{
    s32 state = *(s32*)((u32)this + 0x8);
    
    if (state == 0) {
        menuCloseSync(0x7c, 1);
        s32 activeId = (s32)windowGetActiveID();
        menuOpenCustom(0x7c, activeId, 0, 0, 1, 1, 0);
    } else if (state == 1 || state == 2) {
        s32 activeId = (s32)windowGetActiveID();
        menuOpenCustom(0x7d, activeId, 0, 0, 1, 1, 0);
    } else if (state == 4) {
        menuCloseSync(0x7e, 1);
        s32 activeId = (s32)windowGetActiveID();
        menuOpenCustom(0x7e, activeId, 0, 0, 1, 1, 0);
    }
    
    return 0;
}

/*
 * menuPdaMemoXD::TaskClose
 * Original address: 0x80055228 | size: 0x12C
 * Closes menu tasks based on state.
 */
void TaskClose__13menuPdaMemoXDFP14tagWINDOW_WORKb(void* this, void* windowWork, s32 flag)
{
    if (windowWork != NULL) {
        ((u8*)windowWork)[0xA4] = 1;
    }
    
    void* model = menuPdaMemoListGetMenuModelWork();
    void* modelPtr = menuModelGetModelPtr(model);
    if (modelPtr != NULL) {
        GSmodelDestroyLinkedParticles(modelPtr);
    }
    
    s32 state = *(s32*)((u32)this + 0x8);
    
    if (state == 0) {
        if (winSeqCheckMove(0x7c) == 0) {
            _menuClose__13menuPdaMemoXDFlb(0x7c, flag);
        }
    } else if (state == 1 || state == 2) {
        if (winSeqCheckMove(0x7d) == 0) {
            _menuClose__13menuPdaMemoXDFlb(0x7d, flag);
            if (state == 1) {
                menuPdaMemoWaveInit();
            }
        }
    } else if (state == 4) {
        if (winSeqCheckMove(0x7e) == 0) {
            _menuClose__13menuPdaMemoXDFlb(0x7e, flag);
        }
    }
}

/*
 * menuPdaMemoXD::TaskCloseCheck
 * Original address: 0x80055354 | size: 0x8C
 * Checks if menu can be closed.
 */
s32 TaskCloseCheck__13menuPdaMemoXDFv(void* this)
{
    s32 state = *(s32*)((u32)this + 0x8);
    s32 menuId = 0;
    
    if (state == 0) {
        menuId = 0x7c;
    } else if (state == 1 || state == 2) {
        menuId = 0x7d;
    } else if (state == 4) {
        menuId = 0x7e;
    }
    
    if (menuId == 0) return 1;
    
    s32 result = winSeqCheckMove(menuId);
    return (result == 0) ? 1 : 0;
}

/*
 * menuPdaMemoXD::_menuClose
 * Original address: 0x800553E0 | size: 0x48
 * Helper function to close menus.
 */
void _menuClose__13menuPdaMemoXDFlb(s32 menuId, s32 flag)
{
    menuClose(menuId);
    menuCloseSync(menuId, flag);
}
