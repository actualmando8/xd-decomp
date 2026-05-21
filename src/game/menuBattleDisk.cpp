// Decompiled from: menuBattleDisk.cpp
// Address range: 0x8009E664..0x800A1494 | size: 0x2E30
// Functions: 26 | Data objects: 6
// Platform: GameCube (Gekko PowerPC)
// Compiler: Metrowerks CodeWarrior

#include "global.h"

// Forward declarations
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct GSvec2;
struct Pokemon;
struct Hero;

// External globals
extern struct BattleDiskData {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
    s16 field_8;
    s16 field_a;
    s16 field_c;
    s16 field_e;
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
    u8 field_17;
    u8 padding_18;
    s16 field_18;
    s16 field_1a;
    s16 field_1c;
    f32 field_20;
    u32 item_data[8][8];  // 0x24 - item entries (0x18 bytes each)
    u32 field_4c;
    s16 field_9c;
    s16 field_9e;
    s16 field_a2;
} gBDisk;

// Local static data
static u32 mItemCurIdx__11cBattleDisk[8];
static u32 mContentsCurIdx__11cBattleDisk[0xf];
static s16 sRect[0xc][2];

// External function forward declarations (abbreviated)
int winSeqCheckMove(int);
void winSeqSetMenu(tagWINDOW_WORK*, int);
tagWINDOW_WORK* menuDataBiosGetPtr(tagWINDOW_WORK*);
int windowGetCursorToItem(tagWINDOW_WORK*);
void* windowGetKeyInfo(tagWINDOW_WORK*);
void* windowGetKeyInfo2(tagWINDOW_WORK*);
void* menuItemBiosGetPtr(tagWINDOW_WORK*, s16);
int windowGetActiveID(void);
void windowCreateCursorSprite(tagWINDOW_WORK*);
tagWINDOW_WORK* windowSearchID(int);
void menuPlaySe(tagWINDOW_WORK*, int);
void menuCursorNormal(tagWINDOW_WORK*, int);
int windowGetKeyRepeat(tagWINDOW_WORK*);
int winSpriteGetLayerID(tagWINDOW_WORK*, tagSPRITE_WORK*);
void winSpriteSetDisp(tagSPRITE_WORK*, int);
void windowDrawSprite(tagWINDOW_WORK*, tagSPRITE_WORK*, int, int, int, int);
void windowDrawSprite2(tagWINDOW_WORK*, tagSPRITE_WORK*, s16, s16, int, int, s16, s16, int, int);
void spriteSetScissor(tagSPRITE_WORK*, s16, s16, s16, s16);
void spriteClearScissor(tagSPRITE_WORK*);
int menuOpen(int, int);
int menuOpenCustom(int, int, int, int, int, int, int);
void menuClose(int);
void menuCloseCustom(int);
void menuCloseSync(int, int);
void menuSetPosition(int, s16, s16);
void menuOffScreenSetPriority(int);
int menuFaceDispFromID2(tagWINDOW_WORK*, tagSPRITE_WORK*, int, GSvec2*);
void menuFaceLoad(void*, void*);
int menuFaceCheckLoading(void);
void GSthreadSwitch(void);
f32 timeGetLastFrameSec(void);
void GSmsgPrint2(tagWINDOW_WORK*, tagSPRITE_WORK*, s16, s16, int, s16, s16);
void GSmsgPrintRect(tagWINDOW_WORK*, tagSPRITE_WORK*, s16, s16, int, s16, s16, s16, int, int);
char* GSmsgGetGSchar(int);
void msgctrlSetValue(int, void*);
Pokemon* getPokemonDataPtr__7PokemonCFv(Pokemon*);
int pokemonDataBiosGetZokuseiDataId(Pokemon*, int);
int zokuseiGetPokemonSpriteID(Pokemon*, int);
int zokuseiBiosGetSpriteID(int);
int pokemonGetStatus(Pokemon*, int, int, int);
int wazaGetStatus(Pokemon*, int, int, int);
Pokemon* getPokemon__4HeroFl(Hero*, int);
int heroGetPokeomCount(Hero*);
Pokemon* heroBiosGetPokemonPtr(Hero*, int);
char* heroBiosGetNamePtr(Hero*);
int menuSubGetPokemonSexForDisp(Pokemon*);
int pokemonGetSoubiItemDataId(Pokemon*);
void GSfloorPop(void);
void GSfloorPush(int);
void floorSetFadeScript(int, int);
void floorWaitForChange(void);
int fightEncount(int);
void* fightEncountDataBiosGetPtr(int);
void fightEncountDataBiosSetDiskId(void*, u8);
void fightTrainerCreateFightTrainerDataIdToHero(u16, Hero*, int, int, int);
u16 deckDataVirtualDB_GetAllyDeck__FUs(u16);
u16 deckDataVirtualDB_GetEnemyDeck__FUs(u16);
u16 deckDataVirtualDB_GetPokemonNum__FUs(u16);
char* deckDataVirtualDB_GetTitle__FUs(u16);
char* deckDataVirtualDB_GetExplanetion1__FUs(u16);
char* deckDataVirtualDB_GetExplanetion2__FUs(u16);
void* deckDataVirtualDB_GetFlagData__FUs(u16);
void menuItemBiosSetSelectFlag(int, u32, int);
int menuItemBiosGetSelectFlag(int, u32);
int itemCheckValid(void*);
int itemBiosGetItemDataId(void*);
void* itemDataBiosGetPtr(int);
char* itemDataBiosGetName(void*);
char* itemDataBiosGetDoc(void*);
Hero* getHeroPtr__4HeroFv(void);
void heroItemGetItemKindToItemAryPtr(Hero*, void**, int, int, int, int);
int fightReadResourceID(int, int);
void fightFreeResourceID(int, int);
int menuPdaSubScrollBar(int, s16, s16, int, s16, u16, u16, int);
int GSgfxVideoGetVsyncRate(void);
void menuCreateOffScreen(f32);
void menuOffScreenFadeSync(int);
void menuReleaseOffScreen(f32);
void winMsgOpen(int, char*, int, int);
void winMsgClose(int);
void* memcpy(void*, const void*, size_t);

// Local function declarations
static int getPanelIdx__FUlUc(unsigned long, unsigned char);
static void drawPkmPanel__FUlP14tagWINDOW_WORKP14tagSPRITE_WORK(unsigned long, tagWINDOW_WORK*, tagSPRITE_WORK*);
static void dispFace__FUlP6GSvec2P14tagWINDOW_WORKP14tagSPRITE_WORKP7Pokemon(unsigned long, GSvec2*, tagWINDOW_WORK*, tagSPRITE_WORK*, Pokemon*);
static void loadPkmFace__FPv(void*);

/* 0x8009E664 - size: 0x54 */
void fn_8009E664(tagWINDOW_WORK* work) {
    if (winSeqCheckMove(0xec) == 0) {
        fn_8009E6B8(work, 1);
    }
}

/* 0x8009E6B8 - size: 0x344
 * Searches through menu items in 4 directions (right, left, up, down)
 * finding the closest valid item within range limits.
 * Expands search range iteratively if no item found.
 */
void fn_8009E6B8(tagWINDOW_WORK* work, int flag) {
    void* menuData;
    int cursorItem;
    s16 bestDist;
    s16 itemIdx;
    u16 keyFlags;
    int dirRight, dirLeft, dirUp, dirDown;
    s16 rangeX, rangeY;
    void* item;
    void* cursorItemData;
    
    if (work == NULL) return;
    
    menuData = menuDataBiosGetPtr((tagWINDOW_WORK*)work + 1);
    cursorItem = windowGetCursorToItem(work);
    
    if (cursorItem == 0) {
        *(s16*)((u8*)work + 0x9e) = 0;
        return;
    }
    
    cursorItemData = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, cursorItem);
    
    rangeX = 0x10;
    rangeY = 0xc;
    keyFlags = *(u16*)((u8*)windowGetKeyInfo(work) + 6);
    
    if (flag != 0) {
        u16 high = *(u16*)windowGetKeyInfo(work);
        if ((high & 0xf000) == 0) {
            keyFlags |= *(u16*)((u8*)windowGetKeyInfo2(work) + 6);
        }
    }
    
    keyFlags &= 0xfffc;
    dirRight = (keyFlags >> 31) & 1;
    dirLeft = (keyFlags >> 30) & 1;
    dirUp = (keyFlags >> 29) & 1;
    dirDown = (keyFlags >> 28) & 1;
    
    while (1) {
        itemIdx = 0;
        item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)menuData + 6));
        
        // Search right (dirRight)
        if (dirRight != 0) {
            bestDist = 0x1e0;
            while (1) {
                if (((*(u8*)item) >> 1) & 0x80) {
                    s16 dy = *(s16*)((u8*)item + 8) - *(s16*)((u8*)cursorItemData + 8);
                    if (dy > 0) {
                        s16 dx = *(s16*)((u8*)item + 6) - *(s16*)((u8*)cursorItemData + 6);
                        if (dx < 0) dx = -dx;
                        if (dx < rangeX && dy > bestDist) {
                            bestDist = dy;
                            *(s16*)((u8*)work + 0x9e) = itemIdx;
                        }
                    }
                }
                if (((*(u8*)item) >> 1) & 0x40) break;
                item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)item + 0x18));
                itemIdx++;
            }
        }
        
        // Search left (dirLeft)
        if (dirLeft != 0) {
            bestDist = 0x1e0;
            itemIdx = 0;
            item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)menuData + 6));
            while (1) {
                if (((*(u8*)item) >> 1) & 0x80) {
                    s16 dy = *(s16*)((u8*)cursorItemData + 8) - *(s16*)((u8*)item + 8);
                    if (dy > 0) {
                        s16 dx = *(s16*)((u8*)item + 6) - *(s16*)((u8*)cursorItemData + 6);
                        if (dx < 0) dx = -dx;
                        if (dx < rangeX && dy > bestDist) {
                            bestDist = dy;
                            *(s16*)((u8*)work + 0x9e) = itemIdx;
                        }
                    }
                }
                if (((*(u8*)item) >> 1) & 0x40) break;
                item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)item + 0x18));
                itemIdx++;
            }
        }
        
        // Search up (dirUp) - different range limits
        if (dirUp != 0) {
            bestDist = 0x280;
            itemIdx = 0;
            item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)menuData + 6));
            while (1) {
                if (((*(u8*)item) >> 1) & 0x80) {
                    s16 dx = *(s16*)((u8*)item + 6) - *(s16*)((u8*)cursorItemData + 6);
                    if (dx > 0x1e) {
                        s16 dy = *(s16*)((u8*)item + 8) - *(s16*)((u8*)cursorItemData + 8);
                        if (dy < 0) dy = -dy;
                        if (dy < rangeY && dx > bestDist) {
                            bestDist = dx;
                            *(s16*)((u8*)work + 0x9e) = itemIdx;
                        }
                    }
                }
                if (((*(u8*)item) >> 1) & 0x40) break;
                item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)item + 0x18));
                itemIdx++;
            }
        }
        
        // Search down (dirDown)
        if (dirDown != 0) {
            bestDist = 0x280;
            itemIdx = 0;
            item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)menuData + 6));
            while (1) {
                if (((*(u8*)item) >> 1) & 0x80) {
                    s16 dx = *(s16*)((u8*)cursorItemData + 6) - *(s16*)((u8*)item + 6);
                    if (dx > 0x1e) {
                        s16 dy = *(s16*)((u8*)item + 8) - *(s16*)((u8*)cursorItemData + 8);
                        if (dy < 0) dy = -dy;
                        if (dy < rangeY && dx > bestDist) {
                            bestDist = dx;
                            *(s16*)((u8*)work + 0x9e) = itemIdx;
                        }
                    }
                }
                if (((*(u8*)item) >> 1) & 0x40) break;
                item = menuItemBiosGetPtr((tagWINDOW_WORK*)work + 1, *(s16*)((u8*)item + 0x18));
                itemIdx++;
            }
        }
        
        // Check if result changed - if so expand range and retry
        if (*(s16*)((u8*)work + 0xa2) != *(s16*)((u8*)work + 0x9e)) break;
        
        rangeX += 0x10;
        rangeY += 0xc;
        if (rangeX > 0x280) rangeX = 0x280;
        if (rangeY > 0x1e0) rangeY = 0x1e0;
        if (rangeX == 0x280 && rangeY == 0x1e0) break;
    }
}

/* 0x8009E9FC - size: 0x6C */
void fn_8009E9FC(tagWINDOW_WORK* work) {
    s8 state = work->state;
    if (state == 3) {
        s8 flag = work->flag;
        if (flag == 0) {
            winSeqSetMenu(work->window, 0x17b);
            work->flag = 1;
        }
    }
}

/* 0x8009EA68 - size: 0x1B0 */
void fn_8009EA68(tagWINDOW_WORK* work) {
    s8 state = work->state;
    if (state == 0) {
        if (work->flag != 0) return;
        Hero* hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        u32 count = heroGetPokeomCount(hero);
        if (count < gBDisk.field_14) {
            winSeqSetMenu(work->window, 0x1ee);
        } else {
            winSeqSetMenu(work->window, 0x1e6);
        }
        work->flag = 1;
    } else if (state == 2) {
        if (gBDisk.field_0 != gBDisk.field_4) gBDisk.field_0 = gBDisk.field_4;
        if (gBDisk.field_2 != gBDisk.field_6) gBDisk.field_2 = gBDisk.field_6;
        if (winSeqCheckMove(0xec) != 0) return;
        Hero* hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        u32 count = heroGetPokeomCount(hero);
        if (count < gBDisk.field_14) {
            gBDisk.field_4 = 0x131;
            gBDisk.field_6 = 0;
        } else {
            gBDisk.field_4 = 0;
            gBDisk.field_6 = 0;
        }
        menuSetPosition(0xec, gBDisk.field_0, gBDisk.field_2);
    } else if (state == 4) {
        if (work->flag != 0) return;
        Hero* hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        u32 count = heroGetPokeomCount(hero);
        if (count < gBDisk.field_14) {
            winSeqSetMenu(work->window, 0x1f2);
        } else {
            winSeqSetMenu(work->window, 0x1ea);
        }
        work->flag = 1;
    }
}

/* 0x8009EC18 - size: 0x6C4
 * Displays Battle Disk status info based on Pokemon ID.
 * Uses binary search pattern to dispatch to handlers.
 */
void BattleDiskStatus(tagWINDOW_WORK* work, tagSPRITE_WORK* sprite) {
    int layerId;
    Hero* hero;
    Pokemon* pkm;
    s16 pokemonId;
    int statusVal;
    
    layerId = winSpriteGetLayerID(work, sprite);
    
    hero = (Hero*)((u8*)&gBDisk + 0x5c8);
    u32 count = heroGetPokeomCount(hero);
    if (count < gBDisk.field_14) {
        pkm = getPokemon__4HeroFl(hero, count);
    } else {
        hero = (Hero*)((u8*)&gBDisk + 0xf40);
        pkm = getPokemon__4HeroFl(hero, count - gBDisk.field_14);
    }
    
    pokemonId = sprite->field_6;
    
    // Binary search dispatch based on pokemonId
    if (pokemonId == 0x796) goto case_0x796;
    if (pokemonId >= 0x796) {
        if (pokemonId == 0x7a1) goto case_0x7a1;
        if (pokemonId >= 0x7a1) {
            if (pokemonId == 0x7fa) goto case_0x7fa;
            if (pokemonId == 0x7a3) goto case_0x7a3;
            return;
        }
        if (pokemonId == 0x79e) goto case_0x79e;
        if (pokemonId >= 0x79e) {
            if (pokemonId >= 0x79d) goto case_0x79d;
            if (pokemonId >= 0x798) return;
            goto case_0x798;
        }
        if (pokemonId >= 0x7a0) goto case_0x7a0;
        goto case_0x79f;
    }
    if (pokemonId == 0x790) goto case_0x790;
    if (pokemonId >= 0x790) {
        if (pokemonId == 0x793) goto case_0x793;
        if (pokemonId >= 0x793) {
            if (pokemonId >= 0x795) goto case_0x795;
            goto case_0x794;
        }
        if (pokemonId >= 0x792) goto case_0x792;
        goto case_0x791;
    }
    if (pokemonId == 0x78d) goto case_0x78d;
    if (pokemonId >= 0x78d) {
        if (pokemonId >= 0x78f) goto case_0x78f;
        goto case_0x78e;
    }
    if (pokemonId == 0x78b) goto case_0x78b;
    if (pokemonId >= 0x78b) goto case_0x78c;
    return;
    
case_0x78b: // Nature sprite
    {
        int spriteId = zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(pkm), 0);
        if (spriteId != 0) {
            windowDrawSprite(work, sprite, 0, 0, spriteId, 0);
        }
    }
    return;
case_0x78c: // Dual nature check
    {
        int type1 = pokemonDataBiosGetZokuseiDataId(getPokemonDataPtr__7PokemonCFv(pkm), 0);
        int type2 = pokemonDataBiosGetZokuseiDataId(getPokemonDataPtr__7PokemonCFv(pkm), 1);
        if (type1 != type2) {
            int spriteId = zokuseiGetPokemonSpriteID(getPokemonDataPtr__7PokemonCFv(pkm), 1);
            if (spriteId != 0) {
                windowDrawSprite(work, sprite, 0, 0, spriteId, 0);
            }
        }
    }
    return;
case_0x78d: case_0x78e: case_0x78f: // Move status with sprite
    {
        int moveId = pokemonGetStatus(pkm, 0, 0x7f, pokemonId - 0x78c);
        if (moveId >= 0x164) {
            if (moveId == 0x176) {
                windowDrawSprite(work, sprite, 0, 0, 0x7b, 0);
            }
        } else if (moveId > 0) {
            int type = wazaGetStatus(pkm, 0, moveId, 3);
            int spriteId = zokuseiBiosGetSpriteID(type);
            windowDrawSprite(work, sprite, 0, 0, spriteId, 0);
        }
    }
    return;
case_0x790: case_0x791: // HP display
    msgctrlSetValue(0x37, pokemonGetStatus(pkm, 0, 0x77, 0));
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4277);
    return;
case_0x792: // Sex display
    {
        int sex = menuSubGetPokemonSexForDisp(pkm);
        int msgId = 0;
        if (sex == 0) msgId = 0x9c5;
        else if (sex == 1) msgId = 0x9c6;
        if (msgId != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(msgId));
            GSmsgPrint2(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0x4276);
        }
    }
    return;
case_0x793: // Attack display
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, 0x7a, 0));
    GSmsgPrintRect(work, sprite, 0x24, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x426f);
    return;
case_0x794: case_0x795: // Move name display
    {
        int moveId = pokemonGetStatus(pkm, 0, 0x7f, pokemonId - 0x793);
        if (moveId != 0) {
            int name = wazaGetStatus(pkm, 0, moveId, 1);
            if (name != 0) {
                msgctrlSetValue(0x37, GSmsgGetGSchar(name));
                GSmsgPrintRect(work, sprite, 0, 0, *(u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4277);
            }
        }
    }
    return;
case_0x798: case_0x799: case_0x79a: case_0x79b: // Status displays 0x88-0x8b
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, pokemonId - 0x798 + 0x88, 0));
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4287);
    return;
case_0x79c: case_0x79d: // Defense display
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, 0x83, 0));
    GSmsgPrintRect(work, sprite, 0x24, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x426f);
    return;
case_0x79e: case_0x79f: // More status displays
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, pokemonId - 0x79e + 0x89, 0));
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4287);
    return;
case_0x7a0: case_0x7a1: // More status displays
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, pokemonId - 0x7a0 + 0x8a, 0));
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4287);
    return;
case_0x7fa: // Attack display (alt)
    msgctrlSetValue(0x34, pokemonGetStatus(pkm, 0, 0x83, 0));
    GSmsgPrintRect(work, sprite, 0x24, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x426f);
    return;
case_0x7a3: // Equipment display
    {
        int itemId = pokemonGetSoubiItemDataId(pkm);
        if (itemId != 0) {
            msgctrlSetValue(0x2d, pokemonGetSoubiItemDataId(pkm));
            GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x3ae7);
        } else {
            msgctrlSetValue(0x37, GSmsgGetGSchar(0x3c1a));
            GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4277);
        }
    }
    return;
}

/* 0x8009F2DC - size: 0x5C0
 * Draws Board A (Board/Ally) Pokemon faces and deck type indicators.
 * Dispatches based on sprite ID to draw different deck type sprites.
 */
void BattleDiskBorADraw(tagWINDOW_WORK* work, tagSPRITE_WORK* sprite) {
    s16 spriteId = sprite->field_6;
    int panelIdx = 0;
    s16 deckType = gBDisk.field_18;
    
    // Binary search dispatch on spriteId
    if (spriteId == 0x73a) { panelIdx = 1; goto check_draw; }
    if (spriteId >= 0x73a) {
        if (spriteId == 0x743) { panelIdx = 1; goto check_draw; }
        if (spriteId >= 0x743) {
            if (spriteId == 0x74c) goto case_0x74c;
            if (spriteId >= 0x74c) {
                if (spriteId == 0x7f3) goto case_0x7f3;
                if (spriteId >= 0x7f3) {
                    if (spriteId == 0x877) goto case_0x877;
                    if (spriteId >= 0x877) return;
                    goto case_0x87f;
                }
                if (spriteId == 0x7f2) goto case_0x7f2;
                if (spriteId >= 0x7f2) return;
                goto case_0x74e;
            }
            if (spriteId == 0x74e) goto case_0x74e;
            if (spriteId >= 0x74e) return;
            goto case_0x74a;
        }
        if (spriteId == 0x748) { panelIdx = 1; goto check_draw; }
        if (spriteId >= 0x748) {
            if (spriteId == 0x74a) goto case_0x74a;
            if (spriteId >= 0x74a) { panelIdx = 1; goto check_draw; }
            panelIdx = 1; goto check_draw;
        }
        if (spriteId == 0x746) { panelIdx = 1; goto check_draw; }
        if (spriteId >= 0x746) {
            if (spriteId == 0x745) { panelIdx = 1; goto check_draw; }
            if (spriteId >= 0x745) { panelIdx = 1; goto check_draw; }
            panelIdx = 1; goto check_draw;
        }
        panelIdx = 1; goto check_draw;
    }
    if (spriteId == 0x736) { panelIdx = 1; goto check_draw; }
    if (spriteId >= 0x736) {
        if (spriteId == 0x738) { panelIdx = 1; goto check_draw; }
        if (spriteId >= 0x738) {
            if (spriteId == 0x73f) { panelIdx = 1; goto check_draw; }
            if (spriteId >= 0x73f) {
                if (spriteId == 0x741) { panelIdx = 1; goto check_draw; }
                if (spriteId >= 0x741) { panelIdx = 1; goto check_draw; }
                panelIdx = 1; goto check_draw;
            }
            if (spriteId == 0x73d) { panelIdx = 1; goto check_draw; }
            if (spriteId >= 0x73d) { panelIdx = 1; goto check_draw; }
            if (spriteId == 0x73c) { panelIdx = 1; goto check_draw; }
            if (spriteId >= 0x73c) { panelIdx = 1; goto check_draw; }
            panelIdx = 1; goto check_draw;
        }
        if (spriteId == 0x734) { panelIdx = 1; goto check_draw; }
        if (spriteId >= 0x734) {
            if (spriteId == 0x733) { panelIdx = 1; goto check_draw; }
            if (spriteId >= 0x733) { panelIdx = 1; goto check_draw; }
            return;
        }
        panelIdx = 1; goto check_draw;
    }
    if (spriteId == 0x733) return;
    return;
    
case_0x74a: // Panel index 2
    panelIdx = 2;
    goto check_draw;
case_0x74e: // Panel index 3
    panelIdx = 3;
    goto check_draw;
case_0x7f2: // Panel index 4
    panelIdx = 4;
    goto check_draw;
case_0x7f3: // Panel index 5
    panelIdx = 5;
    goto check_draw;
case_0x877: // Explanation 2 text
    if (deckType >= 0x2 && deckType < 0x4) {
        u16 itemId = gBDisk.field_17 + 0x215;
        void* itemData = itemDataBiosGetPtr(itemId);
        *(int*)((u8*)sprite + 0x4c) = itemDataBiosGetName(itemData);
    } else {
        *(int*)((u8*)sprite + 0x4c) = deckDataVirtualDB_GetTitle__(gBDisk.field_17);
    }
    return;
case_0x87f: // Title text
    *(int*)((u8*)sprite + 0x4c) = deckDataVirtualDB_GetTitle__(gBDisk.field_17);
    return;
    
check_draw:
    {
        Hero* hero;
        if (panelIdx < 0x6) {
            hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        } else {
            hero = (Hero*)((u8*)&gBDisk + 0xf40);
            panelIdx -= 0x6;
        }
        u32 count = heroGetPokeomCount(hero);
        if (count > (u32)panelIdx) {
            Pokemon* pkm = heroBiosGetPokemonPtr(hero, panelIdx);
            dispFace__FUlP6GSvec2P14tagWINDOW_WORKP14tagSPRITE_WORKP7Pokemon(panelIdx, (GSvec2*)((u8*)sprite + 0x8), work, sprite, pkm);
        }
    }
}

/* 0x8009F89C - size: 0x2CC
 * Draws contents panel. Dispatches based on sprite ID to handle different content types.
 * Uses getPanelIdx to calculate panel index and calls drawPkmPanel.
 */
void BattleDiskContentsDraw(tagWINDOW_WORK* work, tagSPRITE_WORK* sprite) {
    s16 spriteId = sprite->field_6;
    int panelIdx = 0;
    
    // Binary search dispatch on spriteId
    if (spriteId == 0x768) { panelIdx = 1; goto draw_panel; }
    if (spriteId >= 0x768) {
        if (spriteId == 0x779) goto case_0x779;
        if (spriteId >= 0x779) {
            if (spriteId == 0x7bc) goto case_0x7bc;
            if (spriteId >= 0x7bc) {
                if (spriteId == 0x7be) goto case_0x7be;
                if (spriteId >= 0x7be) return;
                goto case_0x7bb;
            }
            if (spriteId == 0x7bb) goto case_0x7bb;
            if (spriteId >= 0x7bb) {
                if (spriteId >= 0x7b6) return;
                goto case_0x7b6;
            }
        }
        if (spriteId == 0x76c) { panelIdx = 1; goto draw_panel; }
        if (spriteId >= 0x76c) {
            if (spriteId == 0x76e) { panelIdx = 1; goto draw_panel; }
            if (spriteId >= 0x76e) return;
            panelIdx = 1; goto draw_panel;
        }
        if (spriteId >= 0x76a) { panelIdx = 1; goto draw_panel; }
        panelIdx = 1; goto draw_panel;
    }
    if (spriteId == 0x761) { panelIdx = 1; goto draw_panel; }
    if (spriteId >= 0x761) {
        if (spriteId == 0x765) { panelIdx = 1; goto draw_panel; }
        if (spriteId >= 0x765) {
            if (spriteId == 0x767) { panelIdx = 1; goto draw_panel; }
            if (spriteId >= 0x767) { panelIdx = 1; goto draw_panel; }
            panelIdx = 1; goto draw_panel;
        }
        if (spriteId >= 0x763) { panelIdx = 1; goto draw_panel; }
        panelIdx = 1; goto draw_panel;
    }
    if (spriteId == 0x756) {
        if (gBDisk.field_16 == 0x2) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        return;
    }
    if (spriteId >= 0x756) {
        if (spriteId == 0x760) { panelIdx = 1; goto draw_panel; }
        if (spriteId >= 0x760) return;
        panelIdx = 1; goto draw_panel;
    }
    if (spriteId == 0x753) {
        if (gBDisk.field_16 == 0x1) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
        return;
    }
    if (spriteId >= 0x753) {
        if (spriteId == 0x751) return;
        panelIdx = 1; goto draw_panel;
    }
    if (spriteId == 0x751) return;
    return;
    
case_0x779: // Explanation 2 text
    *(int*)((u8*)sprite + 0x4c) = deckDataVirtualDB_GetExplanetion2__(gBDisk.field_17);
    return;
case_0x7bb: // Active menu check
    {
        int activeId = windowGetActiveID();
        int menuId = *(int*)((u8*)work + 0x4);
        if (menuId != activeId) {
            winSpriteSetDisp(sprite, 0);
        } else {
            winSpriteSetDisp(sprite, 1);
        }
    }
    return;
case_0x7bc: // Active menu check (inverse)
    {
        int activeId = windowGetActiveID();
        int menuId = *(int*)((u8*)work + 0x4);
        if (menuId == activeId) {
            *(int*)((u8*)sprite + 0x4c) = 0x1e2e2;
        } else {
            *(int*)((u8*)sprite + 0x4c) = 0x1e300;
        }
    }
    return;
case_0x7be: // Active menu check (display)
    {
        int activeId = windowGetActiveID();
        int menuId = *(int*)((u8*)work + 0x4);
        if (menuId != activeId) {
            winSpriteSetDisp(sprite, 1);
        } else {
            winSpriteSetDisp(sprite, 0);
        }
    }
    return;
    
draw_panel:
    {
        int idx = getPanelIdx__FUlUc(panelIdx, gBDisk.field_16);
        if (idx >= 0) {
            drawPkmPanel__FUlP14tagWINDOW_WORKP14tagSPRITE_WORK(idx, work, sprite);
        }
    }
}

/* 0x8009FB68 - size: 0x150 */
static int getPanelIdx__FUlUc(unsigned long panelIdx, unsigned char deckType) {
    if (panelIdx > 0xe) return -1;
    switch (panelIdx) {
        case 0: return 0;
        case 1: return (deckType == 2) ? 1 : -1;
        case 2: return (deckType == 1) ? 1 : -1;
        case 3: return 2;
        case 4: return 3;
        case 5: return 4;
        case 6: return 5;
        case 7: {
            if (deckType == 2) {
                Hero* h = (Hero*)((u8*)&gBDisk + 0xf40);
                return (heroGetPokeomCount(h) == 1) ? 6 : -1;
            }
            return 6;
        }
        case 8: {
            if (deckType == 2) {
                Hero* h = (Hero*)((u8*)&gBDisk + 0xf40);
                return (heroGetPokeomCount(h) == 1) ? 6 : -1;
            }
            return 6;
        }
        case 9: {
            if (deckType == 2) {
                Hero* h = (Hero*)((u8*)&gBDisk + 0xf40);
                return (heroGetPokeomCount(h) != 1) ? 7 : -1;
            }
            return 7;
        }
        case 10: return (deckType == 1) ? 7 : -1;
        case 11: return 8;
        case 12: return 9;
        case 13: return 10;
        case 14: return 11;
        default: return -1;
    }
}

/* 0x8009FCB8 - size: 0x454
 * Draws a Pokemon panel with face, HP, attack, defense, sex, and equipment.
 * Calculates position based on panel index and deck type.
 */
static void drawPkmPanel__FUlP14tagWINDOW_WORKP14tagSPRITE_WORK(unsigned long panelIdx, tagWINDOW_WORK* work, tagSPRITE_WORK* sprite) {
    int layerId = winSpriteGetLayerID(work, sprite);
    Hero* hero;
    Pokemon* pkm;
    s16 pkmIdx;
    u8 deckType;
    GSvec2 pos;
    
    if (layerId < 0x6) {
        deckType = 0;
        hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        f32 val = gBDisk.field_20 * 0.5f + 0.5f;
        pkmIdx = (s16)(f64)val;
    } else {
        deckType = 1;
        hero = (Hero*)((u8*)&gBDisk + 0xf40);
        f32 val = -gBDisk.field_20 * 0.5f + 0.5f;
        pkmIdx = (s16)(f64)val;
        layerId -= 0x6;
    }
    
    u32 count = heroGetPokeomCount(hero);
    if (count <= (u32)layerId) return;
    
    pos.x = *(s16*)&sRect[deckType * 2] + pkmIdx;
    pos.y = *(s16*)&sRect[deckType * 2 + 1];
    
    pkm = heroBiosGetPokemonPtr(hero, layerId);
    if (pkm == 0) return;
    
    int hp = pokemonGetStatus(pkm, 0, 0x77, 0);
    int def = pokemonGetStatus(pkm, 0, 0x83, 0);
    int atk = pokemonGetStatus(pkm, 0, 0x7a, 0);
    
    dispFace__FUlP6GSvec2P14tagWINDOW_WORKP14tagSPRITE_WORKP7Pokemon(panelIdx, &pos, work, sprite, pkm);
    
    windowDrawSprite2(work, sprite, pos.x, pos.y, *(u8*)((u8*)work + 0x93) | 0xff00, 0x2fc, 0, 0, 0x300);
    
    msgctrlSetValue(0x37, hp);
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4277);
    
    msgctrlSetValue(0x37, GSmsgGetGSchar(0x42d4));
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4276);
    
    msgctrlSetValue(0x34, atk);
    GSmsgPrintRect(work, sprite, 0x18, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x426f);
    
    msgctrlSetValue(0x37, GSmsgGetGSchar(0x42d5));
    GSmsgPrintRect(work, sprite, 0, 0x1c, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x4276);
    
    msgctrlSetValue(0x34, def);
    GSmsgPrintRect(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0, sprite->field_54, sprite->field_56, 0x426f);
    
    {
        int sex = menuSubGetPokemonSexForDisp(pkm);
        int msgId = 0;
        if (sex == 0) msgId = 0x9c5;
        else if (sex == 1) msgId = 0x9c6;
        if (msgId != 0) {
            msgctrlSetValue(0x37, GSmsgGetGSchar(msgId));
            GSmsgPrint2(work, sprite, 0, 0, *(u8*)((u8*)work + 0x93) | 0xff00, 0x4276);
        }
    }
    
    int itemId = pokemonGetSoubiItemDataId(pkm);
    if (itemId != 0) {
        windowDrawSprite2(work, sprite, pos.x, pos.y, *(u8*)((u8*)work + 0x93) | 0xff00, itemId, 0, 0, 0x14b);
    }
}

/* 0x800A010C - size: 0xA0
 * Displays Pokemon face sprite. Gets face menu sprite ID and draws it.
 */
static void dispFace__FUlP6GSvec2P14tagWINDOW_WORKP14tagSPRITE_WORKP7Pokemon(unsigned long panelIdx, GSvec2* pos, tagWINDOW_WORK* work, tagSPRITE_WORK* sprite, Pokemon* pkm) {
    int spriteId = pokemonDataBiosGetStatusFaceMenuSpriteId(getPokemonDataPtr__7PokemonCFv(pkm), 0);
    void* buf = (void*)((u8*)sprite + 0x8);
    memcpy(buf, sprite, 0x78);
    sprite->field_54 = 0x2a;
    sprite->field_56 = 0x2a;
    if (panelIdx < 0x6) {
        sprite->field_54 = -sprite->field_54;
    }
    menuFaceDispFromID2(work, sprite, pos, spriteId);
    memcpy(sprite, buf, 0x78);
}

/* 0x800A01AC - size: 0xF8
 * Callback for face loading. Iterates through Pokemon and gets pointers for face loading.
 */
static void loadPkmFace__FPv(void* param) {
    int* counter = (int*)param;
    int idx = *counter;
    Pokemon* pkm = 0;
    
    if (idx < 0x6) {
        Hero* hero = (Hero*)((u8*)&gBDisk + 0x5c8);
        u32 count = heroGetPokeomCount(hero);
        if (idx < count) {
            pkm = heroBiosGetPokemonPtr(hero, idx);
        } else {
            *counter = 0x6;
        }
    } else if (idx < 0xc) {
        Hero* hero = (Hero*)((u8*)&gBDisk + 0xf40);
        int adjusted = idx - (((idx * 0xaaab5555ul) >> 34) * 6);
        u32 count = heroGetPokeomCount(hero);
        if (adjusted < count) {
            pkm = heroBiosGetPokemonPtr(hero, adjusted);
        }
    }
    
    *counter = idx + 1;
}

/* 0x800A02A4 - size: 0x414
 * Draws item selection panel with scroll bar and item info.
 */
void BattleDiskItemDraw(tagWINDOW_WORK* work, tagSPRITE_WORK* sprite) {
    s16 spriteId = sprite->field_6;
    int counter = 0;
    
    if (spriteId == 0x6ef) {
        winSpriteSetDisp(sprite, gBDisk.field_0c == 0);
        return;
    }
    if (spriteId == 0x6ee) {
        winSpriteSetDisp(sprite, gBDisk.field_0a - 8 < gBDisk.field_0c);
        return;
    }
    if (spriteId >= 0x6ee) return;
    if (spriteId == 0x6f8) {
        winSpriteSetDisp(sprite, counter < gBDisk.field_12);
        return;
    }
    if (spriteId == 0x6fb) return;
    if (spriteId >= 0x6fb) { counter++; goto check_list; }
    if (spriteId == 0x6fa) { counter++; goto check_list; }
    if (spriteId == 0x6fd) return;
    if (spriteId == 0x702) { counter++; goto check_list; }
    if (spriteId == 0x704) { counter++; goto check_list; }
    if (spriteId == 0x700) { counter++; goto check_list; }
    if (spriteId >= 0x700) return;
    counter++; goto check_list;
    if (spriteId == 0x6f6) { counter++; goto check_list; }
    if (spriteId == 0x717) return;
    if (spriteId == 0x729) {
        *(int*)((u8*)sprite + 0x4c) = deckDataVirtualDB_GetExplanetion1__FUs(gBDisk.field_17);
        return;
    }
    if (spriteId == 0x856) {
        menuPdaSubScrollBar(work, sprite, gBDisk.field_9c, gBDisk.field_0c, gBDisk.field_9e, gBDisk.field_0a, 0x856, 8);
        return;
    }
    if (spriteId == 0x727) {
        *(int*)((u8*)sprite + 0x4c) = deckDataVirtualDB_GetTitle__FUs(gBDisk.field_17);
        return;
    }
    if (spriteId == 0x715) { counter++; goto check_list; }
    if (spriteId == 0x714) {
        winSpriteSetDisp(sprite, work->field_9e == counter);
        return;
    }
    if (spriteId == 0x70a) return;
    if (spriteId == 0x708) {
        s16 scrollPos = gBDisk.field_10;
        s16 listPos = gBDisk.field_0e;
        if (listPos < scrollPos) gBDisk.field_10 = scrollPos - 6;
        else if (listPos > scrollPos) gBDisk.field_10 = scrollPos + 6;
        spriteSetScissor(sprite, *(s16*)((u8*)sprite + 0x6) - sprite->field_50, *(s16*)((u8*)sprite + 0x8) - sprite->field_52, *(s16*)((u8*)sprite + 0xa), *(s16*)((u8*)sprite + 0xc));
        for (int i = 0; i < gBDisk.field_0a; i++) {
            s16 y = gBDisk.field_10 + i * 0x1e;
            if (y > -0x40 && y < 0x1e0) {
                GSmsgPrint2(work, sprite, 0, y, *(u8*)((u8*)work + 0x93) | 0xff00, *(u32*)((u8*)&gBDisk + i * 0x18 + 0x2c));
                u16 itemId = *(u16*)((u8*)&gBDisk + i * 0x18 + 0x2a) - 0x215;
                if (deckDataVirtualDB_GetFlagData__FUs(itemId) != 0) {
                    windowDrawSprite2(work, sprite, y + 3, 0xb2, *(u8*)((u8*)work + 0x93) | 0xff00, 0x16, 0xd, 0, 0x300);
                }
            }
        }
        spriteClearScissor(sprite);
        return;
    }
    if (spriteId >= 0x708) {
        void* itemPtr = &gBDisk + (gBDisk.field_12 + gBDisk.field_0c) * 0x18;
        *(int*)((u8*)sprite + 0x4c) = *(int*)((u8*)itemPtr + 0x3c);
        return;
    }
    return;
    
check_list:
    winSpriteSetDisp(sprite, counter == work->field_9e);
}

/* 0x800A06B8 - size: 0x208
 * Handles list button navigation with scroll offset calculation.
 * Processes right, left, up, down directional input.
 */
void menuBdisk_selectL_Btn(tagWINDOW_WORK* work) {
    int keyInfo = windowGetKeyRepeat();
    u32 keyFlags = keyInfo & 0xffff;
    s16 listIdx = work->field_9e;
    
    gBDisk.field_12 = listIdx;
    s16 maxItems = gBDisk.field_0c;
    
    // Right button (bit 31)
    if ((keyFlags >> 31) & 1) {
        if (gBDisk.field_10 == gBDisk.field_0e && listIdx == 0x7 && maxItems < gBDisk.field_0a - 8) {
            gBDisk.field_0c = maxItems + 1;
            menuPlaySe(work, 1);
            gBDisk.field_0e = maxItems;
            gBDisk.field_10 = maxItems - 6;
        }
        menuCursorNormal(work, 1);
        return;
    }
    
    // Left button (bit 30)
    if ((keyFlags >> 30) & 1) {
        if (gBDisk.field_10 == gBDisk.field_0e && listIdx == 0 && maxItems > 0) {
            gBDisk.field_0c = maxItems - 1;
            menuPlaySe(work, 1);
            gBDisk.field_0e = maxItems - 1;
        }
        menuCursorNormal(work, 1);
        return;
    }
    
    // Up button (bit 29)
    if ((keyFlags >> 29) & 1) {
        s16 newIdx = maxItems - 8;
        if (newIdx < 0) {
            newIdx = 0;
            gBDisk.field_9e = 0;
            gBDisk.field_12 = 0;
            gBDisk.field_0c = 0;
        }
        if (maxItems != newIdx) {
            menuPlaySe(work, 6);
        }
        gBDisk.field_0e = newIdx;
        gBDisk.field_10 = newIdx;
        menuCursorNormal(work, 1);
        return;
    }
    
    // Down button (bit 28)
    if ((keyFlags >> 28) & 1) {
        s16 totalItems = gBDisk.field_0a;
        if (totalItems < 8) {
            gBDisk.field_0c = 0;
            gBDisk.field_9e = totalItems - 1;
            gBDisk.field_12 = totalItems - 1;
        } else {
            s16 newIdx = maxItems + 8;
            if (newIdx >= totalItems) {
                newIdx = totalItems - 1;
                gBDisk.field_9e = 7;
                gBDisk.field_12 = 7;
            }
            if (maxItems != newIdx) {
                menuPlaySe(work, 6);
            }
            gBDisk.field_0e = newIdx;
            gBDisk.field_10 = newIdx;
        }
        menuCursorNormal(work, 1);
        return;
    }
    
    menuCursorNormal(work, 1);
}

/* 0x800A08C0 - size: 0x98 */
void fn_800A08C0(tagWINDOW_WORK* work) {
    s8 state = work->state;
    if (state == 0) {
        if (work->flag != 0) return;
        winSeqSetMenu(work->window, 0x24);
        work->flag = 1;
    } else if (state == 3) {
        if (work->flag != 0) return;
        winSeqSetMenu(work->window, 0x17b);
        work->flag = 1;
    }
}

/* 0x800A0958 - size: 0x8 */
void menuBattleDiskCtrl(void) {
    // Stub - returns 0
}

/* 0x800A0960 - size: 0x2C */
void menuBattleDiskExit(void) {
    fightFreeResourceID(0x842, 0x18513400);
}

/* 0x800A098C - size: 0x700
 * Main loop for Battle Disk menu.
 * Handles state machine, menu transitions, battle encounters.
 */
void menuBattleDiskMain(void) {
    s16 state = gBDisk.field_8;
    Hero* allyHero = (Hero*)((u8*)&gBDisk + 0x5c8);
    Hero* enemyHero = (Hero*)((u8*)&gBDisk + 0xf40);
    int result;
    
    if (state == 0) {
        // Initial state - check Pokeom count
        u32 count = heroGetPokeomCount(allyHero);
        if (count < gBDisk.field_14) {
            gBDisk.field_31 = 1;
        } else {
            gBDisk.field_31 = 0;
        }
        goto main_loop;
    }
    if (state == 1) {
        // Open Battle Disk menu
        menuOpenCustom(0xe7, 0, 0x12, 0, 0, 1, 0, 0, 0);
        GSthreadSwitch();
        menuOpen(0xe8, 1);
        
        // Set up encounter data
        void* encountData = fightEncountDataBiosGetPtr(0xe);
        fightEncountDataBiosSetDiskId(encountData, gBDisk.field_27);
        
        // Create trainer data for ally/enemy
        fightTrainerCreateFightTrainerDataIdToHero(
            deckDataVirtualDB_GetAllyDeck__FUs(gBDisk.field_27), allyHero, 0, 0xe, 0);
        fightTrainerCreateFightTrainerDataIdToHero(
            deckDataVirtualDB_GetEnemyDeck__FUs(gBDisk.field_27), enemyHero, 0, 0xe, 0);
        
        // Load faces
        menuFaceLoad(loadPkmFace__FPv, (void*)&gBDisk.field_8);
        gBDisk.field_16 = deckDataVirtualDB_GetPokemonNum__FUs(gBDisk.field_27);
        gBDisk.field_17 = gBDisk.field_27;
        
        // Set select flags
        for (int i = 0; i < 0xf; i++) {
            menuItemBiosSetSelectFlag(0x109, mContentsCurIdx__11cBattleDisk[i], 0);
        }
        
        // Wait for face loading
        while (menuFaceCheckLoading() == 0) {
            GSthreadSwitch();
        }
        
        menuClose(0xe7);
        menuClose(0xe8);
        
        result = gBDisk.field_22;
        if (result == 0) {
            gBDisk.field_31 = 0;
            goto main_loop;
        }
        if (result == 1) {
            // Open battle menu
            gBDisk.field_20 = 0.0f;
            menuOpen(0xeb, 0);
            while (timeGetLastFrameSec() < gBDisk.field_20) {
                GSthreadSwitch();
                gBDisk.field_20 += timeGetLastFrameSec();
            }
            menuClose(0xeb);
            
            // Main selection loop
            while (1) {
                // Update panel selection
                for (int i = 0; i < 0xf; i++) {
                    int panelIdx = getPanelIdx__FUlUc(i, gBDisk.field_16);
                    int valid = 1;
                    if (panelIdx >= 0x6) {
                        if (heroGetPokeomCount(enemyHero) <= panelIdx - 0x6) valid = 0;
                    } else {
                        if (heroGetPokeomCount(allyHero) <= panelIdx) valid = 0;
                    }
                    menuItemBiosSetSelectFlag(0x109, mContentsCurIdx__11cBattleDisk[i], valid);
                }
                
                menuOpen(0x109, 1);
                int running = 1;
                while (running) {
                    GSthreadSwitch();
                    int keyInfo = windowGetKeyInfo();
                    if ((keyInfo >> 27) & 1) {
                        // A button - select
                        menuOpen(0xec, 0);
                        // ... selection handling ...
                        menuClose(0xec);
                        menuCloseSync(0xec, 1);
                        menuOpen(0x109, 0);
                        running = 0;
                    }
                    if ((keyInfo >> 26) & 1) {
                        // B button - cancel
                        menuPlaySe(0x109, 3);
                        menuClose(0xec);
                        menuCloseSync(0xec, 1);
                        menuOpen(0x109, 0);
                        running = 0;
                    }
                }
                menuClose(0x109);
                menuCloseSync(0x109, 1);
                break;
            }
        }
        if (result == 2) {
            // Explanation view
            while (1) {
                GSthreadSwitch();
                int keyInfo = windowGetKeyInfo();
                if (keyInfo == 0x40) {
                    winMsgOpen(2, deckDataVirtualDB_GetExplanetion1__FUs(gBDisk.field_17), 1, 1);
                    while (1) {
                        GSthreadSwitch();
                        if ((windowGetKeyInfo() >> 25) & 1) break;
                    }
                    winMsgClose(1);
                }
                if (keyInfo == 0x10) break;
            }
            result = fightEncount(0xe);
            gBDisk.field_18 = result;
        }
        if (result == 3) {
            // Doc view
            menuOpenCustom(0xe9, windowGetActiveID(), 0, 2, 0, 0, 0);
            menuOpenCustom(0x8f, 0, 0, 1, 0, 0, 0);
            *(u32*)((u8*)&gBDisk + 0x24) = 0x8f;
            menuCloseCustom(0x8f);
            menuClose(0xe9);
            menuCloseSync(0xe9, 1);
        }
        menuOffScreenSetPriority(1);
    }
    
main_loop:
    GSfloorPop();
    s16 exitState = gBDisk.field_8;
    if (exitState != 0 && exitState != 2) {
        floorSetFadeScript(0, 0);
    }
}

/* 0x800A108C - size: 0x164
 * Initializes Battle Disk data, loads items from hero inventory, sets up arrays.
 */
void menuBattleDiskInit(void) {
    Hero* hero = getHeroPtr__4HeroFv();
    void* itemArray;
    heroItemGetItemKindToItemAryPtr(hero, &itemArray, 0x7, 0, 0, 0);
    
    fightReadResourceID(0x842, 0x18513400);
    
    int itemCount = 0;
    int i = 0;
    while (i < *(int*)((u8*)&itemArray - 0x8)) {
        void* item = *(void**)((u8)itemArray + i * 4);
        if (itemCheckValid(item)) {
            u16 itemId = itemBiosGetItemDataId(item);
            void* entry = &gBDisk.item_data[itemCount];
            ((u16*)entry)[0] = itemId;
            
            void* itemData = itemDataBiosGetPtr(itemId);
            ((u32*)entry)[2] = itemDataBiosGetName(itemData);
            ((u32*)entry)[3] = itemDataBiosGetDoc(itemData);
            
            u16 flagId = itemId - 0x215;
            ((u32*)entry)[4] = deckDataVirtualDB_GetExplanetion1__FUs(flagId);
            ((u32*)entry)[5] = deckDataVirtualDB_GetExplanetion2__FUs(flagId);
            ((u32*)entry)[6] = deckDataVirtualDB_GetTitle__FUs(flagId);
            
            itemCount++;
        }
        i++;
    }
    
    gBDisk.field_a = itemCount;
    
    // Set up item selection flags
    for (int j = 0; j < 8; j++) {
        if (j < itemCount) {
            menuItemBiosSetSelectFlag(0xe8, mItemCurIdx__11cBattleDisk[j], 1);
        } else {
            menuItemBiosSetSelectFlag(0xe8, mItemCurIdx__11cBattleDisk[j], 0);
        }
    }
}

/* 0x800A11F0 - size: 0x24 */
void menuBattleDiskCloseDoc(void) {
    menuClose(0xe9);
}

/* 0x800A1214 - size: 0x4C */
void menuBattleDiskOpenDoc(s8 deckType) {
    gBDisk.field_17 = deckType;
    int activeId = windowGetActiveID();
    menuOpenCustom(0xe9, activeId, 0, 2, 0, 0, 0);
}

/* 0x800A1260 - size: 0xD0 */
void menuBattleDiskOpenDocPush(s8 deckType) {
    gBDisk.field_17 = deckType;
    gBDisk.field_8 = 2;
    int vsyncRate = GSgfxVideoGetVsyncRate();
    f32 duration = /* calculate from vsync */;
    menuCreateOffScreen(duration);
    menuOffScreenSetPriority(0);
    menuOffScreenFadeSync(1);
    GSfloorPush(0x38d);
    floorSetFadeScript(0, 0);
    floorWaitForChange();
    vsyncRate = GSgfxVideoGetVsyncRate();
    duration = /* calculate */;
    menuReleaseOffScreen(duration);
    gBDisk.field_8 = 1;
}

/* 0x800A1330 - size: 0x10 */
void* menuBattleDiskGetResult(void) {
    return &gBDisk;
}

/* Additional functions need decomposition */
void menuBattleDiskGetSelectID(void) { /* TODO */ }
void menuBattleDiskOpenFight(void) { /* TODO */ }
void menuBattleDiskOpen(void) { /* TODO */ }
void __sinit_menuBattleDisk_cpp(void) { /* TODO */ }
