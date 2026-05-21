// dbgMenuPokemon.cpp - Debug Pokemon Edit Menu
// Address: 0x80008998..0x8000AD7C | size: 0x23E4

#include "global.h"

/* Forward declarations */
struct Pokemon;
u32* windowGetKeyInfo();
u32 pokemonCheckValid(Pokemon*);
void menuDataBiosGetPtr(u32);
u32 menuGetCursorItemID(u32);
u32 menuOpenCustom(u32, u32, u32, u32, u32, u32, u32*);
void menuCloseCustom(u32, u32, u32);
u32 menuOpen(u32, u32);
u32 menuSubOpenNumberInput(u32*, u32, u32, u32, u32);
void menuSubCloseNumberInput();
u32 gamedataGetStatus(u32, u32);
void pokemonCreate(Pokemon*, u32, u32, u32, u32, u32);
void pokemonSetCatchStatus(Pokemon*, u32, u32, u32, u32, u32);
u32 pokemonGetStatus(Pokemon*, u32, u32, u32);
void pokemonSetStatus(Pokemon*, u32, u32, u32, u32);
void pokemonSetTokuseiFlag(Pokemon*, u32);
u32 pokemonGetSoubiItemDataId(Pokemon*);
void pokemonDoItemSoubi(Pokemon*, u32, u32);
u32 pokemonCheckRare(Pokemon*);
u32 pokemonCreateRndFit(s32, s32, s32, s32);
u32 pokemonWazaCheckValid(Pokemon*, u32);
u32 wazaCheckDarkWaza(u32);
u32 pokemonWazaGetMaxPP(Pokemon*, u32);
void pokemonWazaCreate(Pokemon*, u32, u32);
void pokemonWazaInit(Pokemon*, u32);
void pokemonInit(Pokemon*);
u32 itemDataCheckValid(u32);
u32 pokemonBiosGetPokemonDataId(Pokemon*);
void pokemonBiosSetEventGetFlag(Pokemon*, u32);
u32 pokemonGetNowLevelToExp(Pokemon*);
void pokemonGrowBasisStatus(Pokemon*, u32);
u32 pokemonIsDarkPokemon(Pokemon*);
void pokemonWriteJoutaiDataId(Pokemon*, u32);
void pokemonInitJoutaiDataId(Pokemon*, u32);
u32 pokemonGetJoutaiDataId(Pokemon*);
void pokemonInitJoutai(Pokemon*);
u32 pokemonCheckWriteJoutaiDataId(Pokemon*, u32);
u32 pokemonGetKaisuuJoutaiDataId(Pokemon*, u32);
void pokemonSetKaisuuJoutaiDataId(Pokemon*, u32, s8);
u32 pokemonGetNowKaisuuJoutaiDataId(Pokemon*, u32);
void pokemonSetNowKaisuuJoutaiDataId(Pokemon*, u32, s8);
u32 pokemonGetCountAsJoutaiDataId(Pokemon*, u32);
u32 joutaiDataBiosGetMaxCount(u32);
void pokemonSetCountAsJoutaiDataId(Pokemon*, u32, s16);
void pokemonInitDarkPokemon(Pokemon*);
void pokemonSetDarkPokemonStatus(Pokemon*, u32);
u32 pokemonSeikakuGetStatus(Pokemon*, u32);
u32 fightTrainerGetStatus(u32, u32, u32);
void fightTrainerSetStatus(u32, u32, u32, u32);

/* Static data */
static const u16 effortStatusTbl1[] = { 0x93, 0x94, 0x95, 0x96, 0x97, 0x98 };
static const u16 effortStatusTbl2[] = { 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92 };
static u16 gRibbonStat[] = { 0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAA,0xAB,0xAC,0xAD,0xAE,0xAF,0xB0,0xB1,0xB2,0xB3,0xB4 };
static u32 gRibbonNum;
static u32 pokemon_edit_value;
static u32 gap_12_804EFC84_sbss2;
extern u32 pokemon_data_number;
extern u32 item_data_index_number;
extern u32 sex_data_number;
extern u32 pokemon_seikaku_data_number;
extern u32 darkPokemonList_number;
extern u32 fight_trainer_pokemon_part_data_number;

/* Jump table for dbgMenuPokemonEditSub */
static void* jumpTbl_3095[] = {
    0, 0, // 0: HP, 1: placeholder
    (void*)0x80008DD4, (void*)0x8000A8E4, // 2-3
    (void*)0x80008E88, (void*)0x8000A8E4, // 4-5
    (void*)0x80008EE4, (void*)0x8000A8E4, // 6-7
    (void*)0x80008FA8, (void*)0x8000A8E4, // 8-9
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 10-11
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 12-13
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 14-15
    (void*)0x8000902C, (void*)0x800090A0, // 16-17
    (void*)0x800090E8, (void*)0x80009130, // 18-19
    (void*)0x80009178, (void*)0x800091C0, // 20-21
    (void*)0x80009208, (void*)0x80009264, // 22-23
    (void*)0x800092B0, (void*)0x800092FC, // 24-25
    (void*)0x80009348, (void*)0x80009394, // 26-27
    (void*)0x800093E0, (void*)0x80009454, // 28-29
    (void*)0x800094B8, (void*)0x8000951C, // 30-31
    (void*)0x80009580, (void*)0x800095E4, // 32-33
    (void*)0x8000A8E4, (void*)0x80009648, // 34-35
    (void*)0x800096AC, (void*)0x80009710, // 36-37
    (void*)0x80009774, (void*)0x800097D8, // 38-39
    (void*)0x80009878, (void*)0x80009918, // 40-41
    (void*)0x800099B8, (void*)0x80009A58, // 42-43
    (void*)0x80009B00, (void*)0x80009BA8, // 44-45
    (void*)0x80009C50, (void*)0x8000A8E4, // 46-47
    (void*)0x80009CF8, (void*)0x8000A8E4, // 48-49
    (void*)0x80009D78, (void*)0x8000A8E4, // 50-51
    (void*)0x80009DCC, (void*)0x80009E7C, // 52-53
    (void*)0x80009F44, (void*)0x8000A010, // 54-55
    (void*)0x8000A8E4, (void*)0x8000A0C0, // 56-57
    (void*)0x8000A8E4, (void*)0x8000A16C, // 58-59
    (void*)0x8000A8E4, (void*)0x8000A1B4, // 60-61
    (void*)0x8000A1FC, (void*)0x8000A280, // 62-63
    (void*)0x8000A370, (void*)0x8000A8E4, // 64-65
    (void*)0x8000A410, (void*)0x8000A8E4, // 66-67
    (void*)0x8000A490, (void*)0x8000A8E4, // 68-69
    (void*)0x8000A58C, (void*)0x8000A8E4, // 70-71
    (void*)0x8000A5DC, (void*)0x8000A8E4, // 72-73
    (void*)0x8000A6AC, (void*)0x8000A8E4, // 74-75
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 76-77
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 78-79
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 80-81
    (void*)0x8000A8E4, (void*)0x8000A8E4, // 82-83
    (void*)0x8000A714, (void*)0x8000A8E4, // 84-85
    (void*)0x8000A778, (void*)0x8000A8E4, // 86-87
    (void*)0x8000A8B4, (void*)0x8000A83C, // 88-89
    (void*)0x8000A8E4, (void*)0x8000A7E4, // 90-91
};

/* 0x80008998 | size: 0x210 */
void dbgMenuPokemonEditButton(void* self) {
    if (self == 0) return;
    s32* p68 = (s32*)((u8*)self + 0x68);
    s32* p6C = (s32*)((u8*)self + 0x6C);
    if (*p68 == 0) return;

    u32* ki = windowGetKeyInfo();
    u16 trg = ki[1];
    u32* ki2 = windowGetKeyInfo();
    u16 hold = ki2[1];
    u16 trgLow = ki2[0];

    // B button - exit
    if (trg & 0x40) {
        *(s32*)((u8*)self + 0x88) = -1;
        *(u8*)((u8*)self + 0xA4) = 1;
        return;
    }
    // X button - cancel
    if (trg & 0x80) {
        *(s32*)((u8*)self + 0x88) = -2;
        *(u8*)((u8*)self + 0xA4) = 1;
        return;
    }
    // No valid pokemon
    if (*p68 == 0) {
        *(s32*)((u8*)self + 0x88) = -1;
        *(u8*)((u8*)self + 0xA4) = 1;
        return;
    }

    s32 delta = 0;
    u16 upTrg = (trg >> 24) & 1;
    u16 upHold = (hold >> 24) & 1;
    u16 downTrg = (trg >> 25) & 1;
    u16 downHold = (hold >> 25) & 1;
    u16 rightTrg = (trg >> 23) & 1;
    u16 leftTrg = (trg >> 26) & 1;

    // D-pad up + L/R = +/-100
    if (upTrg && ((trgLow == 0x400) || (trgLow == 0x200))) delta = 100;
    else if (upHold && ((trgLow == 0x400) || (trgLow == 0x200))) delta = 100;
    else if (downTrg && ((trgLow == 0x400) || (trgLow == 0x200))) delta = -100;
    else if (downHold && ((trgLow == 0x400) || (trgLow == 0x200))) delta = -100;
    // D-pad up = +10
    else if (upTrg && (trgLow == 0x400)) delta = 10;
    else if (downTrg && (trgLow == 0x400)) delta = -10;
    // D-pad up alone = +1
    else if (upTrg) delta = 1;
    else if (downTrg) delta = -1;
    // Right = +256 (overflow)
    else if (rightTrg && (trgLow == 0x400)) delta = 0x10000 - 1;
    else if (rightTrg) delta = 0x10000 - 1;

    if (delta != 0) {
        if (pokemonCheckValid((Pokemon*)*p68)) {
            menuDataBiosGetPtr(*(u32*)((u8*)self + 4));
            u32 itemId = menuGetCursorItemID(*(u32*)((u8*)self + 4));
            if (*p6C) *p6C = delta;
            *(s32*)((u8*)self + 0x88) = itemId;
            *(u8*)((u8*)self + 0xA4) = 1;
        } else {
            *(u16*)((u8*)self + 0x9E) = 0;
            *(s32*)((u8*)self + 0x88) = 0x16;
        }
    }
}

/* 0x8000ACBC | size: 0xC0 */
static u32 dbgMenuPokemonEditSubGetTotalEffort(Pokemon* pkmn) {
    u32 total = pokemonGetStatus(pkmn, 0, 0x8D, 0); // HP effort
    total += pokemonGetStatus(pkmn, 0, 0x8E, 0); // Atk effort
    total += pokemonGetStatus(pkmn, 0, 0x8F, 0); // Def effort
    total += pokemonGetStatus(pkmn, 0, 0x90, 0); // SpA effort
    total += pokemonGetStatus(pkmn, 0, 0x91, 0); // SpD effort
    total += pokemonGetStatus(pkmn, 0, 0x92, 0); // Spe effort
    return total;
}

/* 0x80008BA8 | size: 0x2114 */
void dbgMenuPokemonEditSub(Pokemon* pkmn, u32* pTrainer, u8* flag1, u8* flag2, u8* flag3, u8* flag4) {
    u16 effortBuf1[6];
    u16 effortBuf2[6];
    u32 changed = 0;

    // Save effort values
    if (flag1) *flag1 = 0;
    if (flag2) *flag2 = 0;
    if (flag3) *flag3 = 0;
    if (flag4) *flag4 = 0;

    for (int i = 0; i < 6; i++) {
        effortBuf1[i] = *(u16*)((u8*)&effortStatusTbl1[i]);
        effortBuf2[i] = *(u16*)((u8*)&effortStatusTbl2[i]);
    }

    if (!pokemonCheckValid(pkmn)) {
        u32 species = gamedataGetStatus(0, 1);
        pokemonCreate(pkmn, species, 0x115, 1, 0, 2);
        pokemonSetCatchStatus(pkmn, 0, 1, 0, 2, 0);
    }

    s32 level = pokemonGetStatus(pkmn, 0, 0xC9, 0);
    u32 delta;

loop_start:
    pokemon_edit_value = 0;
    u32 result = menuOpenCustom(0xD, 0, 0, 0, 0, 1, &pokemon_edit_value);
    delta = pokemon_edit_value;

    if (result == -1) {
        menuCloseCustom(0xD, 0, 1);
        // Restore effort values
        for (int i = 0; i < 6; i++) {
            effortBuf1[i] = effortStatusTbl1[i];
            effortBuf2[i] = effortStatusTbl2[i];
        }
        *(u32*)((u8*)&effortBuf1 + 0xC) = (u32)pkmn;
        goto exit;
    }

    if (result == -2) {
        menuOpen(0x55, 1);
        if (result == 0) goto loop_restart;
        menuCloseCustom(0x55, 0, 1);
        goto loop_start;
    }

    if (delta == 0) goto loop_start;

    // Jump table dispatch
    u32 idx = result - 0x16;
    if (idx >= 0x5A) goto loop_start;
    void* handler = jumpTbl_3095[idx];
    goto *handler;

    // Handler for HP (0x8DD4)
handler_hp:
    {
        u32 hp = pokemonGetStatus(pkmn, 0, 0x6E, 0);
        s32 newHp = hp + delta;
        if (newHp < 0) newHp = 0;
        u32 maxHp = *pokemon_data_number;
        if (newHp >= maxHp) newHp = maxHp - 1;
        pokemonSetStatus(pkmn, 0, 0x6E, 0, newHp);
        u32 hpLow = newHp & 0xFFFF;
        pokemonGetStatus(pkmn, 0, 0, 0); // TODO: GSmsgGetGSchar
        pokemonSetStatus(pkmn, 0, 0x77, 0, hpLow);
        pokemonSetTokuseiFlag(pkmn, 0);
        if (flag1) *flag1 = 1;
        if (flag2) *flag2 = 1;
    }
    goto loop_start;

    // Handlers for IVs (0x8E88 - 0x95E4) - similar pattern
    // Each gets current value, adds delta, clamps to [0, max], sets new value
    // IVs: Attack(0x7A), Defense(0x79), SpAtk(0x88), SpDef(0x89), Speed(0x8C), SpDef2(0x8A), SpDef3(0x8B)
    // Natures: Hardy(0x93), Lonely(0x94), Brave(0x95), Bold(0x96), Docile(0x97)
    // Each clamped to [0, 0x1F] for nature, [0, 0x3E7] for IVs

    // Effort values (0x93E0 - 0x9644) with total check <= 0x1FE
    // HP(0x8D), Atk(0x8E), Def(0x8F), SpA(0x90), SpD(0x91), Spe(0x92)
    // Each clamped to [0, 0xFF]

    // Move slots (0x9648 - 0x9C54)
    // Check valid, get current, add delta, clamp to [0, 0x175], create move
    // Also handle PP (0x9878 - 0x9C54)

    // Friendship (0x9CF8) - clamp to [0, 0xFF]
    // Pokéball (0x9D78) - clamp to [0, 0x0C]
    // Item (0x9DCC) - get item, add delta, clamp to valid range

    // Nickname (0x9E7C) - number input for nickname
    // Gender (0x9E7C) - clamp to sex_data_number
    // Nature (0x9F44) - clamp to pokemon_seikaku_data_number
    // Shiny (0xA010) - random fit generation
    // OT Name (0xA0C0) - number input

    // Ribbons (0xA83C) - get from gRibbonStat, clamp to [0, 4]
    // Ribbon count (0xA8B4) - increment gRibbonNum, clamp to [0, 0x11]

    // Status conditions (0xA1FC - 0xA370)
    // Dark Pokemon status (0xA410 - 0xA5DC)
    // Level/Exp (0xA5DC - 0xA6AC)

    // Trainer sync (0xA714 - 0xA7E4)
    // Copy pokemon stats to fight trainer

    // Loop restart
loop_restart:
    menuCloseCustom(0x55, 0, 1);
    menuCloseCustom(0xD, 0, 1);

    // Check for Mew/Mewtwo event flag
    u32 species = pokemonBiosGetPokemonDataId(pkmn);
    if (species == 0x97 || species == 0x19A) {
        u32 form = pokemonGetStatus(pkmn, 0, 0x73, 0);
        if (form == 0 || form == 4) {
            pokemonBiosSetEventGetFlag(pkmn, 1);
        } else {
            pokemonBiosSetEventGetFlag(pkmn, 0);
        }
    }

    // Validate and fix pokemon
    if (!pokemonCheckValid(pkmn)) {
        pokemonInit(pkmn);
    } else {
        u32 item = pokemonGetSoubiItemDataId(pkmn);
        if (!itemDataCheckValid(item)) {
            pokemonDoItemSoubi(pkmn, 0, 0);
        }
    }

    // Sync with trainer if applicable
    if (pTrainer && *flag3) {
        // Copy stats to trainer
        u32 level = pokemonGetStatus(pkmn, 0, 0x6E, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x15, level);
        u32 form = pokemonGetStatus(pkmn, 0, 0x1, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0xE, form);
        u32 friendship = pokemonGetStatus(pkmn, 0, 0x7A, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x11, friendship);

        // Copy IVs
        for (int i = 0; i < 6; i++) {
            u16 iv = effortBuf1[i];
            u32 val = pokemonGetStatus(pkmn, 0, iv, 0);
            fightTrainerSetStatus(*pTrainer, 0, 0xF, val, i);
        }
        for (int i = 0; i < 6; i++) {
            u16 iv = effortBuf2[i];
            u32 val = pokemonGetStatus(pkmn, 0, iv, 0);
            fightTrainerSetStatus(*pTrainer, 0, 0x10, val, i);
        }

        // Copy more stats
        u32 tokusei = pokemonGetStatus(pkmn, 0, 0xB7, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x14, tokusei);
        u32 item = pokemonGetSoubiItemDataId(pkmn);
        fightTrainerSetStatus(*pTrainer, 0, 0x16, item);
        u32 friendship2 = pokemonGetStatus(pkmn, 0, 0x99, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x19, friendship2);
        u32 gender = pokemonGetStatus(pkmn, 0, 0xBA, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x1A, gender);
        u32 nature = pokemonGetStatus(pkmn, 0, 0xBF, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x1B, nature);

        // Copy moves
        for (int i = 0; i < 4; i++) {
            u32 move = pokemonGetStatus(pkmn, 0, 0x7F, i);
            fightTrainerSetStatus(*pTrainer, 0, 0x17, move, i);
            u32 pp = pokemonGetStatus(pkmn, 0, 0x81, i);
            fightTrainerSetStatus(*pTrainer, 0, 0x18, pp, i);
        }

        u32 darkId = pokemonGetStatus(pkmn, 0, 0xC3, 0);
        fightTrainerSetStatus(*pTrainer, 0, 0x13, darkId);
    }

exit:
    return 1;
}

/* Data objects */
// gRibbonStat - Ribbon status table
// gRibbonNum - Ribbon count
// pokemon_edit_value - Menu selection value
// gap_12_804EFC84_sbss2 - Unnamed static data
