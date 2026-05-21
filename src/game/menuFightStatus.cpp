// menuFightStatus.cpp - Battle Status Display
// Address: 0x80016178..0x800178FC | size: 0x1784
//
// Functions:
//   menuFightStatusWaitAnimeEXP  - Wait for EXP animation to complete
//   menuFightStatusStartAnimEXP  - Start EXP bar animation
//   menuFightStatusWaitAnimeHP   - Wait for HP animation to complete
//   menuFightStatusStartAnimHP   - Start HP bar animation
//   menuFightStatusSetActive     - No-op stub
//   menuFightStatusSetHP         - Set current HP value
//   menuFightDrawParam           - Main drawing function (jump table dispatch)
//   menuFightDrawDarkPanel       - Draw shadow pokemon panel (local)
//   menuFightDrawCheckDark       - Check and set dark panel visibility
//   menuFightStatusCtrl          - Main control function
//   menuUpdateStatusTime         - Accumulate status time (local)

#include "global.h"

/* Forward declarations - window/sprite system */
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct MENU_POKEMON_STATUS;
struct Pokemon;
struct GSgfxLayer;
struct GSgfxVF;

void* windowSearchID(u32 id);
void* windowGetFreeWork(void* win);
void* windowGetAllocPtr(void* win);
void windowAllocMemory(void* win, u32 size);
u32 winSpriteGetLayerID(void* win, void* sprite);
u32 winSpriteGetDisp(void* sprite);
void winSpriteSetDisp(void* sprite, u32 disp);
void windowDrawSprite2(u32, u32, s16, s16, s16, s16, u32, u32, u32, u32);

/* Graphics */
void GSthreadSwitch();
void GSsndPlayNow(u32 soundId);
void GSsndStopNow(u32 soundId);
struct GSgfxLayer* GSgfxLayerFindByID(u32 id);
void* GSgfxVFGetPredef(u32 type);
void* GSgfxVFBuildTemp(u32 numVerts);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(struct GSgfxLayer*, struct GSgfxVF*);
void beginSurface__10GSgfxLayerFUs(struct GSgfxLayer*, u32 mode);
void endSurface__10GSgfxLayerFv(struct GSgfxLayer*);

/* Message system */
void* GSmsgGetGSchar(u32 charId);
void msgctrlSetValue(u32 ctrlId, u32 value);
u32 GSmsgGetRect(u32 rectId);
void GSmsgPrint2(u32 layerId, s32 x, s32 y, u32 color, u32 msgId);

/* Fight system */
u32 fightKind_CheckFightKind(u32 kind);
void* menuFightGetStatus();
void menuFightSetSeq(void* status);
void menuFightSetStatus(u32 status);
void* menuSeqBiosGetPtr(u32 seqId);
void* fightFloorGetStatus(u32, u32, u32, u32);
void* fightFloorGetNowPtr();
void* fightFloorGetValidFightSidePtr(void* floor, u32 side);
void* fightSideGetValidFightTrainerPtr(void* side, u32 idx);
void* fightFloorGetFightTrainerFightOutPokemonPtrAry(void* floor, void* trainer, void* out, u32, u32, u32);
u32 fightTrainerIsGcHero(void* trainer);
void* fightOutPokemonGetPokemonPtr(void* outPkmn);

/* Pokemon */
u32 isDarkPokemon__7PokemonCFv(const struct Pokemon*);
struct Pokemon* getDarkPokemon__7PokemonFv(struct Pokemon*);
u32 getDarkPokemonID__11DarkPokemonCFv(const struct Pokemon*);
void* deckGetDeckDarkPokemon(u32 id);
u32 getPlayerLevel__15DeckDarkPokemonCFv(const void* deck);

/* Menu */
void* menuCBBios_CurrentlyWorkingToolBattle();
void menuFaceDispFromID(void* win, void* sprite, u16 faceId);
u32 menuCloseSync(u32 menuId);
u32 menuGetCursorItemID(u32 menuId);
u32 gamedataBiosGetFlag(u32 flagId, u32, u32);

/* Time */
float timeGetLastFrameSec();

/* Math */
float sinf(float);
u32 __cvt_fp2unsigned(float);

/* Static variables */
static u8 init$2107;
static float cFlash$2106;
static float menuStatusTime;
static float menuStatusOldTime;

/* 0x80016178 | size: 0x78 */
// r3 = windowId, r4 = exp
// Waits until the EXP animation window is ready and free work is available
u32 menuFightStatusWaitAnimeEXP(u32 windowId, u32 exp) {
    while (1) {
        void* win = windowSearchID(windowId);
        if (win == 0) {
            return 0;
        }
        void* work = windowGetFreeWork(win);
        s16 animTimer = *(s16*)((u8*)work + 0xC);
        if (animTimer == 0) {
            return 0;
        }
        if (exp == 0) {
            return 1;
        }
        GSthreadSwitch();
    }
}

/* 0x800161F0 | size: 0xC8 */
// r3 = windowId, r4 = newExp
// Calculates animation speed based on EXP difference and starts the animation
void menuFightStatusStartAnimEXP(u32 windowId, u32 newExp) {
    void* win = windowSearchID(windowId);
    if (win == 0) {
        return;
    }
    void* alloc = windowGetAllocPtr(win);
    void* work = windowGetFreeWork(win);
    u32 oldExp = *(u32*)((u8*)alloc + 0x20);
    s32 diff = newExp >= oldExp ? newExp - oldExp : oldExp - newExp;
    u32 maxExp = *(u32*)((u8*)alloc + 0x1C);
    s16 speed = (s16)((diff * 0x64) / maxExp);
    if (speed < 0xF) {
        speed = 0xF;
    }
    *(s16*)((u8*)work + 0xC) = speed;
    *(u32*)((u8*)work + 0x8) = oldExp;
    *(u32*)((u8*)alloc + 0x20) = newExp;
    *(s16*)((u8*)work + 0xE) = 0;
    if (newExp == oldExp) {
        *(s16*)((u8*)work + 0x6) = 1;
    }
    GSsndPlayNow(0x24);
}

/* 0x800162B8 | size: 0x78 */
// r3 = windowId, r4 = hp
// Waits until the HP animation window is ready
u32 menuFightStatusWaitAnimeHP(u32 windowId, u32 hp) {
    while (1) {
        void* win = windowSearchID(windowId);
        if (win == 0) {
            return 0;
        }
        void* work = windowGetFreeWork(win);
        s16 animTimer = *(s16*)((u8*)work + 0x2);
        if (animTimer == 0) {
            return 0;
        }
        if (hp == 0) {
            return 1;
        }
        GSthreadSwitch();
    }
}

/* 0x80016330 | size: 0xAC */
// r3 = windowId, r4 = newHp (s16)
// Calculates animation speed based on HP difference
void menuFightStatusStartAnimHP(u32 windowId, s16 newHp) {
    void* win = windowSearchID(windowId);
    if (win == 0) {
        return;
    }
    void* alloc = windowGetAllocPtr(win);
    void* work = windowGetFreeWork(win);
    s16 oldHp = *(s16*)((u8*)alloc + 0x1A);
    s32 diff = oldHp - newHp;
    if (diff < 0) {
        diff = -diff;
    }
    u32 maxHp = *(u32*)((u8*)alloc + 0x18);
    s16 speed = (s16)((diff * 0x64) / maxHp);
    if (speed <= 0) {
        speed = 1;
    }
    *(s16*)((u8*)work + 0x2) = speed;
    *(s16*)((u8*)work + 0x0) = oldHp;
    *(s16*)((u8*)alloc + 0x1A) = newHp;
    *(s16*)((u8*)work + 0x4) = 0;
}

/* 0x800163DC | size: 0x4 */
// No-op function, possibly a placeholder or inline expansion point
void menuFightStatusSetActive() {
}

/* 0x800163E0 | size: 0x3C */
// r3 = windowId, r4 = hp (s16)
void menuFightStatusSetHP(u32 windowId, s16 hp) {
    void* win = windowSearchID(windowId);
    if (win != 0) {
        void* alloc = windowGetAllocPtr(win);
        *(s16*)((u8*)alloc + 0x1A) = hp;
    }
}

/* 0x8001641C | size: 0x10C4 */
// r3 = window, r4 = status
// Main drawing function with jump table dispatch based on field_6 of alloc
// Jump table @2757 has 40 entries (indices 0x00-0x27)
// Each handler draws a different status element (HP bar, EXP bar, level, face, etc.)
void menuFightDrawParam(tagWINDOW_WORK* window, MENU_POKEMON_STATUS* status) {
    // Initialize flash variable on first call
    if (!init$2107) {
        init$2107 = 1;
        cFlash$2106 = 0.0f;
    }

    void* alloc = windowGetAllocPtr(window);
    void* work = windowGetFreeWork(window);
    u32 r26 = 0;  // Flag for various conditions

    menuFightDrawCheckDark(window, status);

    u32 disp = winSpriteGetDisp(work);
    if (disp == 0) {
        goto end;  // Hidden, skip drawing
    }

    s16 field_6 = *(s16*)((u8*)alloc + 0x6);
    u32 idx = field_6 - 0xD0;
    u32 field_93 = *(u8*)((u8*)window + 0x93);
    u32 color = field_93 | 0xFFFFFF00;

    if (idx >= 0x28) {
        goto end;  // Out of range
    }

    // Jump table dispatch - each label handles a different status element
    // The jump table @2757 maps indices to handler labels
    // Using a switch for clarity; original uses bctr with jump table
    switch (field_6) {
        case 0xD0: { // Handler at .L_800164D8
            if (*(u8*)((u8*)status + 0x29) != 2) {
                winSpriteSetDisp(work, 0);
            }
            goto end;
        }

        case 0xD1: { // Handler at .L_800164F4
            if (*(u8*)((u8*)status + 0x29) == 2) {
                winSpriteSetDisp(work, 1);
            } else {
                winSpriteSetDisp(work, 0);
            }
            goto end;
        }

        case 0xD2: { // Handler at .L_80016520 - Draw face
            menuFaceDispFromID(window, work, *(u16*)((u8*)status + 0x26));
            goto end;
        }

        case 0xD3: // Handler at .L_80016534 - Set flag and draw HP/Level
            r26 = 1;
            // Fall through
        case 0xD4: { // Handler at .L_80016538 - Draw HP/Level
            void* fightStatus = fightFloorGetStatus(0, 0, 0x32, 0);
            if (fightStatus != 0 && r26 == 0) {
                goto end;
            }
            s16 currentHp = *(s16*)((u8*)work + 0x2);
            if (currentHp != 0) {
                s16 targetHp = *(s16*)((u8*)alloc + 0x1A);
                s16 oldHp = *(s16*)((u8*)work + 0x0);
                // Calculate HP ratio for bar drawing
                double hpRange = (double)targetHp;
                double hpDiff = (double)(targetHp - oldHp);
                double ratio = hpDiff / hpRange;
                double progress = ratio * (double)currentHp;
                s16 barPos = (s16)progress;
                if (barPos > 0) {
                    u32 layerId = winSpriteGetLayerID(window, work);
                    GSmsgPrint2(layerId, 0x20, 0, color, 0x42C2);
                    msgctrlSetValue(0x5F, barPos);
                    u32 rect = GSmsgGetRect(0x4272);
                    s16 rectH = (s16)(rect >> 16);
                    layerId = winSpriteGetLayerID(window, work);
                    GSmsgPrint2(layerId, rectH - 0x18, 1, color, 0x4272);
                    msgctrlSetValue(0x5F, *(s16*)((u8*)status + 0x18));
                    rect = GSmsgGetRect(0x4272);
                    rectH = (s16)(rect >> 16);
                    layerId = winSpriteGetLayerID(window, work);
                    s16 spriteY = *(s16*)((u8*)work + 0x54);
                    GSmsgPrint2(layerId, spriteY - rectH, 1, color, 0x4272);
                }
            } else {
                s16 maxHp = *(s16*)((u8*)status + 0x1A);
                u32 layerId = winSpriteGetLayerID(window, work);
                GSmsgPrint2(layerId, 0x20, 0, color, 0x42C2);
                msgctrlSetValue(0x5F, maxHp);
                u32 rect = GSmsgGetRect(0x4272);
                s16 rectH = (s16)(rect >> 16);
                layerId = winSpriteGetLayerID(window, work);
                GSmsgPrint2(layerId, rectH - 0x18, 1, color, 0x4272);
                msgctrlSetValue(0x5F, *(s16*)((u8*)status + 0x18));
                rect = GSmsgGetRect(0x4272);
                rectH = (s16)(rect >> 16);
                layerId = winSpriteGetLayerID(window, work);
                s16 spriteY = *(s16*)((u8*)work + 0x54);
                GSmsgPrint2(layerId, spriteY - rectH, 1, color, 0x4272);
            }
            goto end;
        }

        case 0xD5: { // Handler at .L_800166B8 - Toggle display based on field_2D
            winSpriteSetDisp(work, 1);
            if (*(u8*)((u8*)status + 0x2D) == 0) {
                winSpriteSetDisp(work, 0);
            }
            goto end;
        }

        case 0xD6: { // Handler at .L_800166E0 - Dark panel drawing
            if (*(u8*)((u8*)status + 0x2D) != 0) {
                goto end;
            }
            // Complex dark panel logic with fight trainer checks
            // ... (skeleton - needs more analysis)
            u8 level = *(u8*)((u8*)status + 0x17);
            msgctrlSetValue(0x5F, level);
            u32 rect = GSmsgGetRect(0x4272);
            s16 rectH = (s16)(rect >> 16);
            u32 layerId = winSpriteGetLayerID(window, work);
            s16 spriteY = *(s16*)((u8*)work + 0x54);
            GSmsgPrint2(layerId, spriteY - rectH, 1, color, 0x4272);
            goto end;
        }

        case 0xD7: { // Handler at .L_80016938 - Draw name
            msgctrlSetValue(0x37, status);
            u32 layerId = winSpriteGetLayerID(window, work);
            GSmsgPrint2(layerId, 0, 1, color, 0x4279);
            u32 rect = GSmsgGetRect(0x4279);
            s16 rectH = (s16)(rect >> 16) + 4;
            u8 field_28 = *(u8*)((u8*)status + 0x28);
            u32 msgId = 0;
            if (field_28 == 1) {
                msgId = 0x9C6;
            } else if (field_28 >= 1 && field_28 < 3) {
                msgId = 0;
            } else if (field_28 >= 0 && field_28 < 1) {
                msgId = 0x9C5;
            }
            if (msgId != 0) {
                void* gschar = GSmsgGetGSchar(msgId);
                msgctrlSetValue(0x37, gschar);
                layerId = winSpriteGetLayerID(window, work);
                GSmsgPrint2(layerId, rectH, 0, color, 0x4278);
            }
            goto end;
        }

        case 0xD8: { // Handler at .L_800169EC - Draw sprite2
            u32 layerId = winSpriteGetLayerID(window, work);
            s16 spriteW = *(s16*)((u8*)work + 0x54);
            s16 spriteH = *(s16*)((u8*)work + 0x56);
            u16 field_24 = *(u16*)((u8*)status + 0x24);
            windowDrawSprite2(0, 0, spriteW, spriteH, field_24, 0, color, window, 0, 0);
            goto end;
        }

        case 0xD9: { // Handler at .L_80016A24 - HP bar with GSgfxLayer rendering
            // Complex HP bar rendering using GSgfxLayer surface drawing
            // ... (skeleton - needs more analysis)
            u32 layerId = winSpriteGetLayerID(window, work);
            struct GSgfxLayer* layer = GSgfxLayerFindByID(layerId);
            if (layer == 0) {
                goto end;
            }
            // ... HP bar calculation and rendering
            goto end;
        }

        case 0xDA: { // Handler at .L_80016D44 - EXP bar drawing
            s16 expTimer = *(s16*)((u8*)work + 0xC);
            if (expTimer != 0) {
                s16 expStep = *(s16*)((u8*)work + 0xE);
                u32 oldExp = *(u32*)((u8*)work + 0x8);
                u32 targetExp = *(u32*)((u8*)status + 0x20);
                // Calculate EXP bar position
                double expRange = (double)targetExp;
                double expDiff = (double)(targetExp - oldExp);
                double ratio = expDiff / expRange;
                double progress = ratio * (double)expTimer;
                s16 barPos = (s16)progress;
                u32 maxFrames = *(u32*)((u8*)status + 0x1C);
                if (barPos > maxFrames) {
                    barPos = maxFrames;
                }
                if (maxFrames > 0) {
                    s16 frameIdx = (s16)(((barPos - 1) * (s32)maxFrames) / maxFrames);
                    if (frameIdx > 0) {
                        cFlash$2106 = 0.0f;
                        u32 layerId = winSpriteGetLayerID(window, work);
                        windowDrawSprite2(0, 0, *(s16*)((u8*)work + 0x54), *(s16*)((u8*)work + 0x56),
                                          frameIdx, 0, color, window, 0x92, 0);
                    } else {
                        u32 layerId = winSpriteGetLayerID(window, work);
                        windowDrawSprite2(0, 0, *(s16*)((u8*)work + 0x54), *(s16*)((u8*)work + 0x56),
                                          0, 0, color, window, 0x92, 0);
                        // Flash animation
                        layer = GSgfxLayerFindByID(layerId);
                        // ... flash rendering
                    }
                }
            } else {
                u32 layerId = winSpriteGetLayerID(window, work);
                windowDrawSprite2(0, 0, *(s16*)((u8*)work + 0x54), *(s16*)((u8*)work + 0x56),
                                  0, 0, color, window, 0x92, 0);
            }
            goto end;
        }

        case 0xDB: { // Handler at .L_80016FD4 - HP bar segment 1 (0.2 threshold)
            float currentHp = *(float*)((u8*)status + 0x20);
            float maxHp = *(float*)((u8*)status + 0x1C);
            float ratio = currentHp / maxHp;
            s16 barPos = 0;
            if (ratio < 0.2f) {
                float t = ratio / 0.2f;
                barPos = (s16)(t * *(s16*)((u8*)work + 0x54));
            } else {
                barPos = *(s16*)((u8*)work + 0x54);
            }
            if (barPos < 0) barPos = 0;
            u32 layerId = winSpriteGetLayerID(window, work);
            windowDrawSprite2(0, 0, barPos, *(s16*)((u8*)work + 0x56),
                              0, 0, color, window, 0x91, 0);
            goto end;
        }

        case 0xDC: { // Handler at .L_80017070 - HP bar segment 2 (0.4 threshold)
            float currentHp = *(float*)((u8*)status + 0x20);
            float maxHp = *(float*)((u8*)status + 0x1C);
            float ratio = currentHp / maxHp;
            s16 barPos = 0;
            if (ratio < 0.4f) {
                float t = (ratio - 0.2f) / 0.2f;
                barPos = (s16)(t * *(s16*)((u8*)work + 0x54));
            } else {
                barPos = *(s16*)((u8*)work + 0x54);
            }
            if (barPos < 0) barPos = 0;
            u32 layerId = winSpriteGetLayerID(window, work);
            windowDrawSprite2(0, 0, barPos, *(s16*)((u8*)work + 0x56),
                              0, 0, color, window, 0x91, 0);
            goto end;
        }

        case 0xDD: { // Handler at .L_80017114 - HP bar segment 3 (0.6 threshold)
            float currentHp = *(float*)((u8*)status + 0x20);
            float maxHp = *(float*)((u8*)status + 0x1C);
            float ratio = currentHp / maxHp;
            s16 barPos = 0;
            if (ratio < 0.6f) {
                float t = (ratio - 0.4f) / 0.2f;
                barPos = (s16)(t * *(s16*)((u8*)work + 0x54));
            } else {
                barPos = *(s16*)((u8*)work + 0x54);
            }
            if (barPos < 0) barPos = 0;
            u32 layerId = winSpriteGetLayerID(window, work);
            windowDrawSprite2(0, 0, barPos, *(s16*)((u8*)work + 0x56),
                              0, 0, color, window, 0x91, 0);
            goto end;
        }

        case 0xDE: { // Handler at .L_800171BC - HP bar segment 4 (0.8 threshold)
            float currentHp = *(float*)((u8*)status + 0x20);
            float maxHp = *(float*)((u8*)status + 0x1C);
            float ratio = currentHp / maxHp;
            s16 barPos = 0;
            if (ratio < 0.8f) {
                float t = (ratio - 0.6f) / 0.2f;
                barPos = (s16)(t * *(s16*)((u8*)work + 0x54));
            } else {
                barPos = *(s16*)((u8*)work + 0x54);
            }
            if (barPos < 0) barPos = 0;
            u32 layerId = winSpriteGetLayerID(window, work);
            windowDrawSprite2(0, 0, barPos, *(s16*)((u8*)work + 0x56),
                              0, 0, color, window, 0x91, 0);
            goto end;
        }

        case 0xDF: { // Handler at .L_80017264 - HP bar segment 5 (1.0 threshold)
            float currentHp = *(float*)((u8*)status + 0x20);
            float maxHp = *(float*)((u8*)status + 0x1C);
            float ratio = currentHp / maxHp;
            s16 barPos = 0;
            if (ratio < 1.0f) {
                float t = (ratio - 0.8f) / 0.2f;
                barPos = (s16)(t * *(s16*)((u8*)work + 0x54));
            } else {
                barPos = *(s16*)((u8*)work + 0x54);
            }
            if (barPos < 0) barPos = 0;
            u32 layerId = winSpriteGetLayerID(window, work);
            windowDrawSprite2(0, 0, barPos, *(s16*)((u8*)work + 0x56),
                              0, 0, color, window, 0x91, 0);
            goto end;
        }

        case 0xE0: { // Handler at .L_8001730C - Menu sync check
            winSpriteSetDisp(work, 0);
            u32 menu = menuCloseSync(0x5C);
            if (menu == 0) {
                goto end;
            }
            u32 cursorId = menuGetCursorItemID(0x5C);
            u32 field_4 = *(u32*)((u8*)window + 0x4);
            u32 r25 = 0;
            if (field_4 == 0x40 && cursorId == 0x139) {
                r25 = 1;
            } else if (field_4 >= 0x40 && field_4 < 0x42 && cursorId == 0x13B) {
                r25 = 1;
            } else if (field_4 == 0x38 && cursorId == 0x13A) {
                r25 = 1;
            } else if (field_4 >= 0x38 && field_4 < 0x40 && cursorId == 0x13B) {
                r25 = 1;
            } else if (field_4 >= 0x37 && field_4 < 0x38 && cursorId == 0x138) {
                r25 = 1;
            }
            // Sine wave animation for cursor position
            float timeVal = menuStatusTime * 100.0f;
            u32 timeInt = __cvt_fp2unsigned(timeVal);
            float angle = 0.01f * ((timeInt % 0x64) * 0x64 - timeInt) * 3.14f;
            float sineVal = sinf(angle) * 200.0f;
            s16 offset = (s16)sineVal;
            *(s8*)((u8*)work + 0x65) = (s8)offset;
            *(s8*)((u8*)work + 0x66) = (s8)offset;
            if (r25 == 0) {
                goto end;
            }
            if (r26 == 0) {
                void* fightStatus = fightFloorGetStatus(0, 0, 0x32, 0);
                if (fightStatus == 0) {
                    goto end;
                }
            }
            winSpriteSetDisp(work, 1);
            goto end;
        }

        case 0xE1: { // Handler at .L_80017344 - Set flag
            r26 = 1;
            // Fall through
        }
        default: { // Handler at .L_80017348 - Hide sprite
            winSpriteSetDisp(work, 0);
            r25 = 0;
            goto end;
        }
    }

end:
    // Restore saved registers and return
    return;
}

/* 0x800174E0 | size: 0x12C */
// r3 = window, r4 = sprite, r5 = pokemon, r6 = status
// Draws the dark (shadow) pokemon panel showing "SHADOW" text and level
static u32 menuFightDrawDarkPanel__FP14tagWINDOW_WORKP14tagSPRITE_WORKP7PokemonP19MENU_POKEMON_STATUS(
    tagWINDOW_WORK* window, tagSPRITE_WORK* sprite, struct Pokemon* pkmn, MENU_POKEMON_STATUS* status) {
    if (pkmn == 0) {
        return 0;
    }
    if (!isDarkPokemon__7PokemonCFv(pkmn)) {
        return 0;
    }

    // Draw "SHADOW" text (GSchar 0x4443 = "SHADOW")
    void* gschar = GSmsgGetGSchar(0x4443);
    msgctrlSetValue(0x37, gschar);
    u32 rect = GSmsgGetRect(0x4278);
    s16 rectH = (s16)(rect >> 16);
    u32 layerId = winSpriteGetLayerID(window, sprite);
    s16 spriteY = *(s16*)((u8*)sprite + 0x54);
    s32 offsetY = rectH - spriteY;
    u8 field_93 = *(u8*)((u8*)window + 0x93);
    u32 color = field_93 | 0xFF00;
    GSmsgPrint2(layerId, offsetY, 0, color, 0x4278);

    // Draw Dark Pokemon level
    struct Pokemon* darkPkmn = getDarkPokemon__7PokemonFv(pkmn);
    u32 darkId = getDarkPokemonID__11DarkPokemonCFv(darkPkmn);
    void* deck = deckGetDeckDarkPokemon(darkId);
    u32 level = getPlayerLevel__15DeckDarkPokemonCFv(deck);
    msgctrlSetValue(0x5F, level);
    rect = GSmsgGetRect(0x4272);
    s16 rectH2 = (s16)(rect >> 16);
    layerId = winSpriteGetLayerID(window, sprite);
    s32 offsetY2 = rectH2 - spriteY - rectH2;
    GSmsgPrint2(layerId, offsetY2, 1, color, 0x4272);

    return 1;
}

/* 0x8001760C | size: 0xD0 */
// r3 = windowId, r4 = param (display flag)
// Checks the status type and conditionally shows/hides the dark panel sprite
// Uses jump table @2817 for dispatching based on field_6 range
void menuFightDrawCheckDark(u32 windowId, u32 param) {
    void* win = windowSearchID(windowId);
    void* alloc = windowGetAllocPtr(win);
    s16 field_6 = *(s16*)((u8*)alloc + 0x6);
    u8 field_16 = *(u8*)((u8*)win + 0x16);
    u32 disp = param;

    u32 idx = field_6 - 0xD3;
    if (idx >= 0x1C) {
        goto set_disp;
    }

    // Jump table @2817 dispatches based on status type
    // Handlers check field_29 of window for visibility conditions
    void* jumpTbl_2817[] = {
        (void*)0x80017654, (void*)0x80017654,  // 0xD3, 0xD4
        (void*)0x80017670, (void*)0x80017670,  // 0xD5, 0xD6
        (void*)0x80017688, (void*)0x80017688,  // 0xD7, 0xD8
        (void*)0x80017688, (void*)0x80017688,  // 0xD9, 0xDA
        (void*)0x80017654, (void*)0x80017654,  // 0xDB, 0xDC
        (void*)0x80017670, (void*)0x80017670,  // 0xDD, 0xDE
        (void*)0x80017670, (void*)0x80017670,  // 0xDF, 0xE0
        (void*)0x80017670, (void*)0x80017670,  // 0xE1, 0xE2
        (void*)0x80017670, (void*)0x80017670,  // 0xE3, 0xE4
        (void*)0x80017670, (void*)0x80017670,  // 0xE5, 0xE6
        (void*)0x80017688, (void*)0x80017688,  // 0xE7, 0xE8
        (void*)0x80017688, (void*)0x80017688,  // 0xE9, 0xEA
        (void*)0x80017688, (void*)0x80017688,  // 0xEB, 0xEC
        (void*)0x80017688, (void*)0x80017688,  // 0xED, 0xEE
        (void*)0x80017654, (void*)0x80017670,  // 0xEF, 0xF0
    };

    // ASM: Jump table dispatch - simplified to if/else for readability
    // Original uses: lwzx r0, r5, r0; mtctr r0; bctr
    u8 field_29 = *(u8*)((u8*)win + 0x29);

    if (idx <= 1) {
        // Handler at .L_80017654: Check field_29 == 0
        if (field_29 != 0) {
            disp = 0;
        }
    } else if (idx <= 3) {
        // Handler at .L_80017670: Check field_29 != 0
        if (field_29 != 0) {
            disp = 1;
        } else {
            disp = 0;
        }
    }
    // Indices 4-31 fall through to set_disp

set_disp:
    // Special cases for certain status types
    if (field_6 == 0xD6) {
        if (field_16 == 1) {
            disp = 0;
        }
    } else if (field_6 >= 0xDB && field_6 < 0xE7) {
        if (field_6 >= 0xDB && field_6 < 0xE7) {
            if (field_16 == 1) {
                disp = 0;
            }
        }
    }

    winSpriteSetDisp(win, disp);
}

/* 0x800176DC | size: 0x1E4 */
// r3 = window
// Main control function for battle status display
// Handles initialization, state transitions, and animation timers
void menuFightStatusCtrl(tagWINDOW_WORK* window) {
    void* work = windowGetFreeWork(window);
    u8 field_1 = *(u8*)((u8*)window + 0x1);
    s32 state = (s8)field_1;
    u32 allocPtr = 0;

    if (state == 0) {
        // Initialization state
        allocPtr = (u32)windowAllocMemory(window, 0x30);
        if (allocPtr == 0) {
            goto common;
        }
        memcpy((void*)allocPtr, (void*)((u8*)window + 0x68), 0x30);
        // Check for special fight kinds that set flag at offset 0x16
        if (fightKind_CheckFightKind(0xD)) {
            *(u8*)((u8*)allocPtr + 0x16) = 1;
        }
        if (fightKind_CheckFightKind(0xE)) {
            *(u8*)((u8*)allocPtr + 0x16) = 1;
        }
        if (fightKind_CheckFightKind(0xF)) {
            *(u8*)((u8*)allocPtr + 0x16) = 1;
        }
        void* status = menuFightGetStatus();
        if (status != 0) {
            menuFightSetSeq(status);
        }
    } else if (state == 1) {
        // Transition state - check if sequence completed
        void* status = menuFightGetStatus();
        if (status == 0) {
            goto common;
        }
        void* seq1A5 = menuSeqBiosGetPtr(0x1A5);
        void* seq1A9 = menuSeqBiosGetPtr(0x1A9);
        u32 field_2C = *(u32*)((u8*)window + 0x2C);
        if (field_2C == (u32)seq1A5) {
            allocPtr = 1;
        }
        if (field_2C == (u32)seq1A9) {
            allocPtr = 1;
        }
        if (allocPtr) {
            menuFightSetStatus(0);
        }
    }

common:
    allocPtr = (u32)windowGetAllocPtr(window);
    // HP animation timer update
    s16 hpTimer = *(s16*)((u8*)work + 0x2);
    if (hpTimer != 0) {
        float dt = timeGetLastFrameSec() * 60.0f;
        s16 step = *(s16*)((u8*)work + 0x4);
        step += (s16)dt;
        *(s16*)((u8*)work + 0x4) = step;
        if (step > hpTimer) {
            *(s16*)((u8*)work + 0x2) = 0;
        }
    }
    // EXP animation timer update
    s16 expTimer = *(s16*)((u8*)work + 0xC);
    if (expTimer != 0) {
        float dt = timeGetLastFrameSec() * 60.0f;
        s16 step = *(s16*)((u8*)work + 0xE);
        step += (s16)dt;
        *(s16*)((u8*)work + 0xE) = step;
        if (step > expTimer) {
            *(s16*)((u8*)work + 0xC) = 0;
            GSsndStopNow(0x24);
        }
    }
    menuUpdateStatusTime__Fv();
}

/* 0x800178C0 | size: 0x3C */
// Local function - accumulates time for status animations
// Uses global variables menuStatusTime and menuStatusOldTime
static void menuUpdateStatusTime__Fv() {
    float dt = timeGetLastFrameSec();
    if (dt != menuStatusOldTime) {
        menuStatusTime += dt;
        menuStatusOldTime = dt;
    }
}
