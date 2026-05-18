// Decompiled from gbaPokemon.cpp (0x80026898 - 0x80027E84)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r4 args, r3 return, LR saved on stack

#include "gba_pokemon.h"
#include "pokemon.h"
#include "hero_bios.h"
#include "gamedata.h"

// Forward declarations for external functions
extern void pokemonInit(u32 flags);
extern u32 pokemonCheckValid(Pokemon* pkmn);
extern u32 pokemonBiosGetRnd(Pokemon* pkmn);
extern u32 pokemonBiosGetCatchTrainerRnd(Pokemon* pkmn);
extern u32* pokemonBiosGetAttest(Pokemon* pkmn);
extern u32 pokemonBiosGetTamagoFlag(Pokemon* pkmn);
extern u32 pokemonBiosGetFlagAmari(Pokemon* pkmn);
extern u32 pokemonBiosGetFuseiFlag(Pokemon* pkmn);
extern u32 gamedataAttestBiosGetVerId(u32* attest);
extern u32 gamedataAttestBiosGetLangareaId(u32* attest);
extern const char* pokemonBiosGetNicknameOrgPtr(Pokemon* pkmn);
extern const char* pokemonBiosGetCatchTrainerNamePtr(Pokemon* pkmn);
extern u8 pokemonBiosGetPcboxMark(Pokemon* pkmn);
extern u16 pokemonBiosGetAmari(Pokemon* pkmn);
extern u16 pokemonBiosGetPokemonDataId(Pokemon* pkmn);
extern u16 pokemonBiosGetItemDataId(Pokemon* pkmn);
extern u32 pokemonBiosGetExp(Pokemon* pkmn);
extern u8 pokemonBiosGetFriend(Pokemon* pkmn);
extern u16 pokemonBiosGetPara1Amari(Pokemon* pkmn);
extern u16 pokemonBiosGetPokemonWazaDataId(Pokemon* pkmn, u32 index);
extern u8 pokemonBiosGetPokemonWazaPpCount(Pokemon* pkmn, u32 index);
extern u8 pokemonBiosGetPokemonWazaPp(Pokemon* pkmn, u32 index);
extern u8 pokemonBiosGetMaxHpEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetPhyAtkEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetPhyDefEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetNimblenessEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetSpeAtkEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetSpeDefEffort(Pokemon* pkmn);
extern u8 pokemonBiosGetStyle(Pokemon* pkmn);
extern u8 pokemonBiosGetBeautiful(Pokemon* pkmn);
extern u8 pokemonBiosGetCute(Pokemon* pkmn);
extern u8 pokemonBiosGetClever(Pokemon* pkmn);
extern u8 pokemonBiosGetStrong(Pokemon* pkmn);
extern u8 pokemonBiosGetFur(Pokemon* pkmn);
extern u8 pokemonBiosGetPokerus(Pokemon* pkmn);
extern u8 pokemonBiosGetCatchFloorId(Pokemon* pkmn);
extern u8 pokemonBiosGetCatchLevel(Pokemon* pkmn);
extern u8 pokemonBiosGetCatchBallId(Pokemon* pkmn);
extern u8 pokemonBiosGetCatchTrainerSex(Pokemon* pkmn);
extern u8 pokemonBiosGetMaxHpRnd(Pokemon* pkmn);
extern u8 pokemonBiosGetPhyAtkRnd(Pokemon* pkmn);
extern u8 pokemonBiosGetPhyDefRnd(Pokemon* pkmn);
extern u8 pokemonBiosGetNimblenessRnd(Pokemon* pkmn);
extern u8 pokemonBiosGetSpeAtkRnd(Pokemon* pkmn);
extern u8 pokemonBiosGetSpeDefRnd(Pokemon* pkmn);
extern u32 pokemonBiosGetTokuseiFlag(Pokemon* pkmn);
extern u8 pokemonBiosGetStyleMedal(Pokemon* pkmn);
extern u8 pokemonBiosGetBeautifulMedal(Pokemon* pkmn);
extern u8 pokemonBiosGetCuteMedal(Pokemon* pkmn);
extern u8 pokemonBiosGetCleverMedal(Pokemon* pkmn);
extern u8 pokemonBiosGetStrongMedal(Pokemon* pkmn);
extern u32 pokemonBiosGetChampRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetWinningRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetVictoryRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetBromideRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetGanbaRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetMarineRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetLandRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetSkyRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetCountryRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetNationalRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetEarthRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetWorldRibbon(Pokemon* pkmn);
extern u8 pokemonBiosGetAmariRibbon(Pokemon* pkmn);
extern u32 pokemonBiosGetEventGetFlag(Pokemon* pkmn);
extern u32 pokemonBiosGetConditionAmari(Pokemon* pkmn);
extern u8 pokemonBiosGetLevel(Pokemon* pkmn);
extern u8 pokemonBiosGetMailId(Pokemon* pkmn);
extern u16 pokemonBiosGetMaxHp(Pokemon* pkmn);
extern u16 pokemonBiosGetHp(Pokemon* pkmn);
extern u16 pokemonBiosGetPhyAtk(Pokemon* pkmn);
extern u16 pokemonBiosGetPhyDef(Pokemon* pkmn);
extern u16 pokemonBiosGetNimbleness(Pokemon* pkmn);
extern u16 pokemonBiosGetSpeAtk(Pokemon* pkmn);
extern u16 pokemonBiosGetSpeDef(Pokemon* pkmn);

// Setter functions
extern void pokemonBiosSetRnd(Pokemon* pkmn, u32 rnd);
extern void pokemonBiosSetCatchTrainerRnd(Pokemon* pkmn, u32 rnd);
extern void pokemonBiosSetNicknamePtr(Pokemon* pkmn, const char* name);
extern void pokemonBiosSetFlagAmari(Pokemon* pkmn, u32 flag);
extern void pokemonBiosSetFuseiFlag(Pokemon* pkmn, u32 flag);
extern void pokemonBiosSetPcboxMark(Pokemon* pkmn, u8 mark);
extern void pokemonBiosSetAmari(Pokemon* pkmn, u16 amari);
extern void pokemonBiosSetPokemonDataId(Pokemon* pkmn, u16 species);
extern void pokemonBiosSetItemDataId(Pokemon* pkmn, u16 item);
extern void pokemonBiosSetExp(Pokemon* pkmn, u32 exp);
extern void pokemonBiosSetFriend(Pokemon* pkmn, u8 friend);
extern void pokemonBiosSetPara1Amari(Pokemon* pkmn, u16 para);
extern void pokemonBiosSetPokemonWazaDataId(Pokemon* pkmn, u32 index, u16 move);
extern void pokemonBiosSetPokemonWazaPpCount(Pokemon* pkmn, u32 index, u8 count);
extern void pokemonBiosSetPokemonWazaPp(Pokemon* pkmn, u32 index, u8 pp);
extern void pokemonBiosSetMaxHpEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetPhyAtkEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetPhyDefEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetNimblenessEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetSpeAtkEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetSpeDefEffort(Pokemon* pkmn, u8 effort);
extern void pokemonBiosSetStyle(Pokemon* pkmn, u8 style);
extern void pokemonBiosSetBeautiful(Pokemon* pkmn, u8 beautiful);
extern void pokemonBiosSetCute(Pokemon* pkmn, u8 cute);
extern void pokemonBiosSetClever(Pokemon* pkmn, u8 clever);
extern void pokemonBiosSetStrong(Pokemon* pkmn, u8 strong);
extern void pokemonBiosSetFur(Pokemon* pkmn, u8 fur);
extern void pokemonBiosSetPokerus(Pokemon* pkmn, u8 pokerus);
extern void pokemonBiosSetCatchFloorId(Pokemon* pkmn, u8 floor);
extern void pokemonBiosSetCatchLevel(Pokemon* pkmn, u8 level);
extern void pokemonBiosSetCatchBallId(Pokemon* pkmn, u8 ball);
extern void pokemonBiosSetCatchTrainerSex(Pokemon* pkmn, u8 sex);
extern void pokemonBiosSetMaxHpRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetPhyAtkRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetPhyDefRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetNimblenessRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetSpeAtkRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetSpeDefRnd(Pokemon* pkmn, u8 rnd);
extern void pokemonBiosSetTamagoFlag(Pokemon* pkmn, u32 flag);
extern void pokemonBiosSetTokuseiFlag(Pokemon* pkmn, u32 flag);
extern void pokemonBiosSetStyleMedal(Pokemon* pkmn, u8 medal);
extern void pokemonBiosSetBeautifulMedal(Pokemon* pkmn, u8 medal);
extern void pokemonBiosSetCuteMedal(Pokemon* pkmn, u8 medal);
extern void pokemonBiosSetCleverMedal(Pokemon* pkmn, u8 medal);
extern void pokemonBiosSetStrongMedal(Pokemon* pkmn, u8 medal);
extern void pokemonBiosSetChampRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetWinningRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetVictoryRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetBromideRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetGanbaRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetMarineRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetLandRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetSkyRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetCountryRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetNationalRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetEarthRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetWorldRibbon(Pokemon* pkmn, u32 ribbon);
extern void pokemonBiosSetAmariRibbon(Pokemon* pkmn, u8 amari);
extern void pokemonBiosSetEventGetFlag(Pokemon* pkmn, u32 flag);
extern void pokemonBiosSetConditionAmari(Pokemon* pkmn, u32 amari);
extern void pokemonBiosSetLevel(Pokemon* pkmn, u8 level);
extern void pokemonBiosSetMailId(Pokemon* pkmn, u8 mail);
extern void pokemonBiosSetMaxHp(Pokemon* pkmn, u16 hp);
extern void pokemonBiosSetHp(Pokemon* pkmn, u16 hp);
extern void pokemonBiosSetPhyAtk(Pokemon* pkmn, u16 atk);
extern void pokemonBiosSetPhyDef(Pokemon* pkmn, u16 def);
extern void pokemonBiosSetNimbleness(Pokemon* pkmn, u16 spd);
extern void pokemonBiosSetSpeAtk(Pokemon* pkmn, u16 atk);
extern void pokemonBiosSetSpeDef(Pokemon* pkmn, u16 def);

// Status condition functions
extern u32 pokemonIsJoutaiDataId(Pokemon* pkmn, u32 dataId);
extern s16 pokemonGetCountAsJoutaiDataId(Pokemon* pkmn, u32 dataId);
extern s8 pokemonGetKaisuuJoutaiDataId(Pokemon* pkmn, u32 dataId);
extern void pokemonWriteJoutaiDataId(Pokemon* pkmn, u32 dataId, u32 count);
extern void pokemonSetCountAsJoutaiDataId(Pokemon* pkmn, u32 dataId, s16 count);
extern void pokemonSetKaisuuJoutaiDataId(Pokemon* pkmn, u32 dataId, s8 count);

// Game data functions
extern u32 gamedataAttestCreate(u32* attest, u32 param1, u32 param2, u32 param3, u32 param4);
extern u32* pokemonBiosGetAttest(Pokemon* pkmn);

// Character conversion functions
extern u8 GBAMakeFromGSchar(char* dest, const char* src, u8 maxLen);
extern u8 GScharMakeFromGBA(char* dest, const char* src, u8 maxLen);

// Helper functions for byte swapping
static inline u32 _swap32(u32 val) {
    return ((val & 0x000000FF) << 24) |
           ((val & 0x0000FF00) << 8)  |
           ((val & 0x00FF0000) >> 8)  |
           ((val & 0xFF000000) >> 24);
}

static inline u16 _swap16(u16 val) {
    return ((val & 0x00FF) << 8) | ((val & 0xFF00) >> 8);
}

// PP rotation functions
static void _rotatepp(u8* pp, u32 count);
static void _revrotatepp(u8* pp, u32 count);

// Status condition conversion functions
static u32 gbaPokemonConditonFromGC(Pokemon* pkmn);
static void gbaPokemonConditonToGC(Pokemon* pkmn, u32 gbaStatus);

// Function pointer tables for version/language dispatch
// These are jump tables stored in .data section
static void (*const gbaPokemonFromGC_verTable[12])(void);  // @2181
static void (*const gbaPokemonFromGC_langTable[10])(void); // @2182
static const u8 gbaPokemonToGC_verTable[16] = { 0x08, 0x01, 0x02, 0x03, 0x09, 0x0A, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 }; // @2236
static const u8 gbaPokemonToGC_langTable[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x00, 0x00 }; // @2237

/*
 * gbaPokemonFromGC
 * Original address: 0x80026898
 * Size: 0x974 bytes
 * 
 * Converts a GameCube Pokemon to GBA format
 */
void gbaPokemonFromGC(Pokemon* gcPkmn, GbaPokemon* gbaPkmn) {
    u32* attest;
    u32 verId;
    u32 langId;
    u16 checksumSum;
    u32 i;
    
    // Clear output buffer
    memset(gbaPkmn, 0, 0x64);
    
    // Check if Pokemon is valid
    if (!pokemonCheckValid(gcPkmn)) {
        return;
    }
    
    // Copy RNG values with endian swap
    gbaPkmn->rnd = _swap32(pokemonBiosGetRnd(gcPkmn));
    gbaPkmn->catchTrainerRnd = _swap32(pokemonBiosGetCatchTrainerRnd(gcPkmn));
    
    // Get attest pointer and process version/language
    attest = pokemonBiosGetAttest(gcPkmn);
    verId = gamedataAttestBiosGetVerId(attest);
    
    // Dispatch based on version ID (0-11) using jump table
    if (verId <= 0xB) {
        switch (verId) {
            case 0:  gbaPkmn->version = 1; break;  // Ruby
            case 1:  gbaPkmn->version = 2; break;  // Sapphire
            case 2:  gbaPkmn->version = 3; break;  // FireRed
            case 3:  gbaPkmn->version = 4; break;  // LeafGreen
            case 4:  gbaPkmn->version = 5; break;  // Emerald
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 0xA: gbaPkmn->version = 0; break; // Unknown
            case 0xB: gbaPkmn->version = 0xF; break; // Colosseum/XD
        }
    } else {
        gbaPkmn->version = 0;
    }
    
    // Process language area ID
    langId = gamedataAttestBiosGetLangareaId(attest);
    if (langId <= 0x9) {
        switch (langId) {
            case 0:  gbaPkmn->langArea = 1; break;  // Japanese
            case 1:  gbaPkmn->langArea = 2; break;  // English
            case 2:  gbaPkmn->langArea = 5; break;  // French
            case 3:  gbaPkmn->langArea = 3; break;  // Italian
            case 4:  gbaPkmn->langArea = 4; break;  // German
            case 5:  gbaPkmn->langArea = 7; break;  // Spanish
            case 6:
            case 7:  gbaPkmn->langArea = 2; break;
            case 8:
            case 9:  gbaPkmn->langArea = 0; break;
        }
    } else {
        gbaPkmn->langArea = 0;
    }
    
    // Build flags byte
    gbaPkmn->flags = 0;
    if (pokemonBiosGetTamagoFlag(gcPkmn)) {
        gbaPkmn->flags |= 0x01;
    }
    if (pokemonBiosGetFuseiFlag(gcPkmn)) {
        gbaPkmn->flags |= 0x02;
    }
    gbaPkmn->flags |= (pokemonBiosGetFlagAmari(gcPkmn) & 1) << 2;
    
    // Convert nickname
    {
        const char* nickPtr = pokemonBiosGetNicknameOrgPtr(gcPkmn);
        u8 nickLen = GBAMakeFromGSchar(gbaPkmn->nickname, nickPtr, 0xA);
        if (nickLen < 0xA) {
            gbaPkmn->nickname[nickLen] = 0xFF;
            memset(&gbaPkmn->nickname[nickLen + 1], 0, 0xA - nickLen - 1);
        }
    }
    
    // Convert trainer name
    {
        const char* trainerNamePtr = pokemonBiosGetCatchTrainerNamePtr(gcPkmn);
        u8 nameLen = GBAMakeFromGSchar(gbaPkmn->trainerName, trainerNamePtr, 0x7);
        if (nameLen < 0x7) {
            gbaPkmn->trainerName[nameLen] = 0xFF;
            memset(&gbaPkmn->trainerName[nameLen + 1], 0, 0x7 - nameLen - 1);
        }
    }
    
    // Copy basic fields
    gbaPkmn->pcboxMark = pokemonBiosGetPcboxMark(gcPkmn);
    gbaPkmn->amari = _swap16(pokemonBiosGetAmari(gcPkmn));
    gbaPkmn->species = _swap16(pokemonBiosGetPokemonDataId(gcPkmn));
    gbaPkmn->item = _swap16(pokemonBiosGetItemDataId(gcPkmn));
    gbaPkmn->exp = _swap32(pokemonBiosGetExp(gcPkmn));
    gbaPkmn->friendship = pokemonBiosGetFriend(gcPkmn);
    gbaPkmn->para1Amari = pokemonBiosGetPara1Amari(gcPkmn);
    gbaPkmn->ppFlags = 0;
    
    // Copy moves and PP data
    for (i = 0; i < 4; i++) {
        gbaPkmn->moves[i] = _swap16(pokemonBiosGetPokemonWazaDataId(gcPkmn, i));
        gbaPkmn->ppCounts |= (pokemonBiosGetPokemonWazaPpCount(gcPkmn, i) & 0x1F) << (i * 5);
        gbaPkmn->pp[i] = pokemonBiosGetPokemonWazaPp(gcPkmn, i);
    }
    
    // Copy effort values
    gbaPkmn->hpEffort = pokemonBiosGetMaxHpEffort(gcPkmn);
    gbaPkmn->atkEffort = pokemonBiosGetPhyAtkEffort(gcPkmn);
    gbaPkmn->defEffort = pokemonBiosGetPhyDefEffort(gcPkmn);
    gbaPkmn->spdEffort = pokemonBiosGetNimblenessEffort(gcPkmn);
    gbaPkmn->spaEffort = pokemonBiosGetSpeAtkEffort(gcPkmn);
    gbaPkmn->spdEffort2 = pokemonBiosGetSpeDefEffort(gcPkmn);
    
    // Copy contest stats
    gbaPkmn->cool = pokemonBiosGetStyle(gcPkmn);
    gbaPkmn->beautiful = pokemonBiosGetBeautiful(gcPkmn);
    gbaPkmn->cute = pokemonBiosGetCute(gcPkmn);
    gbaPkmn->smart = pokemonBiosGetClever(gcPkmn);
    gbaPkmn->tough = pokemonBiosGetStrong(gcPkmn);
    gbaPkmn->feel = pokemonBiosGetFur(gcPkmn);
    
    // Copy Pokerus and catch data
    gbaPkmn->pokerus = pokemonBiosGetPokerus(gcPkmn);
    gbaPkmn->catchFloor = pokemonBiosGetCatchFloorId(gcPkmn);
    gbaPkmn->catchLevel = pokemonBiosGetCatchLevel(gcPkmn);
    gbaPkmn->catchBall = pokemonBiosGetCatchBallId(gcPkmn);
    gbaPkmn->catchTrainerSex = pokemonBiosGetCatchTrainerSex(gcPkmn);
    
    // Copy IVs (5-bit each)
    gbaPkmn->hpIv = pokemonBiosGetMaxHpRnd(gcPkmn) & 0x1F;
    gbaPkmn->atkIv = (pokemonBiosGetPhyAtkRnd(gcPkmn) >> 3) & 0x1F;
    gbaPkmn->defIv = (pokemonBiosGetPhyDefRnd(gcPkmn) >> 2) & 0x1F;
    gbaPkmn->spdIv = (pokemonBiosGetNimblenessRnd(gcPkmn) >> 12) & 0x1F;
    gbaPkmn->spaIv = (pokemonBiosGetSpeAtkRnd(gcPkmn) >> 3) & 0x1F;
    gbaPkmn->spdIv2 = (pokemonBiosGetSpeDefRnd(gcPkmn) >> 1) & 0x1F;
    
    // Pack flags
    if (pokemonBiosGetTamagoFlag(gcPkmn)) {
        gbaPkmn->packedFlags |= (1 << 5);
    }
    if (pokemonBiosGetTokuseiFlag(gcPkmn)) {
        gbaPkmn->packedFlags |= (1 << 6);
    }
    
    // Copy contest medals
    gbaPkmn->medalFlags = 0;
    gbaPkmn->medalFlags |= (pokemonBiosGetStyleMedal(gcPkmn) & 0x7) << 2;
    gbaPkmn->medalFlags |= (pokemonBiosGetBeautifulMedal(gcPkmn) & 0x7) << 5;
    gbaPkmn->medalFlags |= (pokemonBiosGetCuteMedal(gcPkmn) & 0x7) << 8;
    gbaPkmn->medalFlags |= (pokemonBiosGetCleverMedal(gcPkmn) & 0x7) << 11;
    gbaPkmn->medalFlags |= (pokemonBiosGetStrongMedal(gcPkmn) & 0x7) << 14;
    
    // Copy ribbons
    gbaPkmn->ribbons = 0;
    if (pokemonBiosGetChampRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 7);
    if (pokemonBiosGetWinningRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 31);
    if (pokemonBiosGetVictoryRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 30);
    if (pokemonBiosGetBromideRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 29);
    if (pokemonBiosGetGanbaRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 28);
    if (pokemonBiosGetMarineRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 27);
    if (pokemonBiosGetLandRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 26);
    if (pokemonBiosGetSkyRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 25);
    if (pokemonBiosGetCountryRibbon(gcPkmn)) gbaPkmn->ribbons |= (1 << 24);
    if (pokemonBiosGetNationalRibbon(gcPkmn)) gbaPkmn->ribbons2 |= (1 << 31);
    if (pokemonBiosGetEarthRibbon(gcPkmn)) gbaPkmn->ribbons2 |= (1 << 30);
    if (pokemonBiosGetWorldRibbon(gcPkmn)) gbaPkmn->ribbons2 |= (1 << 29);
    gbaPkmn->ribbons2 |= (pokemonBiosGetAmariRibbon(gcPkmn) & 0xF) << 24;
    if (pokemonBiosGetEventGetFlag(gcPkmn)) gbaPkmn->ribbons2 |= (1 << 24);
    
    // Convert status condition
    {
        u32 conditionAmari = pokemonBiosGetConditionAmari(gcPkmn);
        u32 gbaStatus = gbaPokemonConditonFromGC(gcPkmn);
        gbaPkmn->condition = _swap32(gbaStatus) | (conditionAmari & 0xFFF);
    }
    
    // Copy level and mail
    gbaPkmn->level = pokemonBiosGetLevel(gcPkmn);
    gbaPkmn->mailId = pokemonBiosGetMailId(gcPkmn);
    
    // Copy stats with endian swap
    gbaPkmn->maxHp = _swap16(pokemonBiosGetMaxHp(gcPkmn));
    gbaPkmn->hp = _swap16(pokemonBiosGetHp(gcPkmn));
    gbaPkmn->atk = _swap16(pokemonBiosGetPhyAtk(gcPkmn));
    gbaPkmn->def = _swap16(pokemonBiosGetPhyDef(gcPkmn));
    gbaPkmn->spd = _swap16(pokemonBiosGetNimbleness(gcPkmn));
    gbaPkmn->spa = _swap16(pokemonBiosGetSpeAtk(gcPkmn));
    gbaPkmn->spd2 = _swap16(pokemonBiosGetSpeDef(gcPkmn));
    
    // Calculate checksum
    checksumSum = 0;
    for (i = 0; i < 0x18; i++) {
        checksumSum += _swap16(((u16*)gbaPkmn)[i]);
    }
    gbaPkmn->checksum = _swap16(checksumSum);
    
    // Calculate PP checksum using XOR
    {
        u32 seed0 = gbaPkmn->rnd;
        u32 seed1 = gbaPkmn->catchTrainerRnd;
        u32* ppChecksum = gbaPkmn->ppChecksum;
        
        for (i = 0; i < 2; i++) {
            ppChecksum[0] = seed0 ^ seed1 ^ ppChecksum[0];
            ppChecksum[1] = seed0 ^ seed1 ^ ppChecksum[1];
            ppChecksum[2] = seed0 ^ seed1 ^ ppChecksum[2];
            ppChecksum[3] = seed0 ^ seed1 ^ ppChecksum[3];
            ppChecksum[4] = seed0 ^ seed1 ^ ppChecksum[4];
            ppChecksum[5] = seed0 ^ seed1 ^ ppChecksum[5];
            ppChecksum += 6;
        }
    }
    
    // Rotate PP data
    _rotatepp(gbaPkmn->pp, _swap32(gbaPkmn->rnd));
}

/*
 * gbaPokemonToGC
 * Original address: 0x8002720C
 * Size: 0x7C0 bytes
 * 
 * Converts a GBA Pokemon to GameCube format
 */
void gbaPokemonToGC(Pokemon* gcPkmn, const GbaPokemon* gbaPkmn) {
    u32 i;
    u32 verId;
    u32 langId;
    u16 checksumSum;
    
    // Initialize GC Pokemon
    pokemonInit(0);
    
    // Check if GBA Pokemon has valid flags
    if ((gbaPkmn->flags & 0x40000000) == 0) {
        if ((gbaPkmn->flags & 0x80000000) == 0) {
            return;
        }
    }
    
    // Reverse PP checksum XOR
    {
        u32 seed0 = gbaPkmn->rnd;
        u32 seed1 = gbaPkmn->catchTrainerRnd;
        u32* ppChecksum = (u32*)gbaPkmn->ppChecksum;
        
        for (i = 0; i < 2; i++) {
            ppChecksum[0] = seed0 ^ seed1 ^ ppChecksum[0];
            ppChecksum[1] = seed0 ^ seed1 ^ ppChecksum[1];
            ppChecksum[2] = seed0 ^ seed1 ^ ppChecksum[2];
            ppChecksum[3] = seed0 ^ seed1 ^ ppChecksum[3];
            ppChecksum[4] = seed0 ^ seed1 ^ ppChecksum[4];
            ppChecksum[5] = seed0 ^ seed1 ^ ppChecksum[5];
            ppChecksum += 6;
        }
    }
    
    // Reverse rotate PP
    _revrotatepp((u8*)gbaPkmn->pp, _swap32(gbaPkmn->rnd));
    
    // Calculate checksum
    checksumSum = 0;
    for (i = 0; i < 0x18; i++) {
        checksumSum += _swap16(((const u16*)gbaPkmn)[i]);
    }
    
    // Verify checksum
    if (_swap16(checksumSum) != gbaPkmn->checksum) {
        return;
    }
    
    // Set RNG values
    pokemonBiosSetRnd(gcPkmn, _swap32(gbaPkmn->rnd));
    pokemonBiosSetCatchTrainerRnd(gcPkmn, _swap32(gbaPkmn->catchTrainerRnd));
    
    // Dispatch based on version
    verId = gbaPkmn->version;
    if (verId <= 0xF) {
        verId = gbaPokemonToGC_verTable[verId];
    }
    
    langId = gbaPkmn->langArea;
    if (langId <= 0x7) {
        langId = gbaPokemonToGC_langTable[langId];
    } else {
        langId = 0;
    }
    
    u32 attest[4];
    u32 gcVer;
    u32 gcLang;
    
    switch (verId) {
        case 1: gcVer = 8; break;
        case 2: gcVer = 9; break;
        case 3: gcVer = 0xA; break;
        case 4: gcVer = 0xB; break;
        case 5: gcVer = 1; break;
        case 6: gcVer = 2; break;
        case 0xF: gcVer = 0; break;
        default: gcVer = 0; break;
    }
    
    switch (langId) {
        case 1: gcLang = 1; break;
        case 2: gcLang = 2; break;
        case 3: gcLang = 3; break;
        case 4: gcLang = 4; break;
        case 5: gcLang = 5; break;
        case 6: gcLang = 6; break;
        default: gcLang = 0; break;
    }
    
    gamedataAttestCreate(pokemonBiosGetAttest(gcPkmn), gcVer, 3, gcLang, 0);
    
    {
        char nickBuf[0x10];
        u8 nickLen = GScharMakeFromGBA(nickBuf, gbaPkmn->nickname, 0xA);
        pokemonBiosSetNicknamePtr(gcPkmn, nickBuf);
        if (nickLen == 1) {
            ((u16*)gcPkmn)[0x2C] = 0;
        }
    }
    
    pokemonBiosSetFlagAmari(gcPkmn, (gbaPkmn->flags >> 2) & 1);
    pokemonBiosSetFuseiFlag(gcPkmn, (gbaPkmn->flags >> 31) & 1);
    
    {
        char nameBuf[0x10];
        GScharMakeFromGBA(nameBuf, gbaPkmn->trainerName, 0x7);
    }
    
    pokemonBiosSetPcboxMark(gcPkmn, gbaPkmn->pcboxMark);
    pokemonBiosSetAmari(gcPkmn, _swap16(gbaPkmn->amari));
    pokemonBiosSetPokemonDataId(gcPkmn, _swap16(gbaPkmn->species));
    pokemonBiosSetItemDataId(gcPkmn, _swap16(gbaPkmn->item));
    pokemonBiosSetExp(gcPkmn, _swap32(gbaPkmn->exp));
    pokemonBiosSetFriend(gcPkmn, gbaPkmn->friendship);
    pokemonBiosSetPara1Amari(gcPkmn, gbaPkmn->para1Amari);
    
    for (i = 0; i < 4; i++) {
        pokemonBiosSetPokemonWazaDataId(gcPkmn, i, _swap16(gbaPkmn->moves[i]));
        pokemonBiosSetPokemonWazaPpCount(gcPkmn, i, (gbaPkmn->ppCounts >> (i * 5)) & 0x1F);
        pokemonBiosSetPokemonWazaPp(gcPkmn, i, gbaPkmn->pp[i]);
    }
    
    pokemonBiosSetMaxHpEffort(gcPkmn, gbaPkmn->hpEffort);
    pokemonBiosSetPhyAtkEffort(gcPkmn, gbaPkmn->atkEffort);
    pokemonBiosSetPhyDefEffort(gcPkmn, gbaPkmn->defEffort);
    pokemonBiosSetNimblenessEffort(gcPkmn, gbaPkmn->spdEffort);
    pokemonBiosSetSpeAtkEffort(gcPkmn, gbaPkmn->spaEffort);
    pokemonBiosSetSpeDefEffort(gcPkmn, gbaPkmn->spdEffort2);
    
    pokemonBiosSetStyle(gcPkmn, gbaPkmn->cool);
    pokemonBiosSetBeautiful(gcPkmn, gbaPkmn->beautiful);
    pokemonBiosSetCute(gcPkmn, gbaPkmn->cute);
    pokemonBiosSetClever(gcPkmn, gbaPkmn->smart);
    pokemonBiosSetStrong(gcPkmn, gbaPkmn->tough);
    pokemonBiosSetFur(gcPkmn, gbaPkmn->feel);
    
    pokemonBiosSetPokerus(gcPkmn, gbaPkmn->pokerus);
    pokemonBiosSetCatchFloorId(gcPkmn, gbaPkmn->catchFloor);
    pokemonBiosSetCatchLevel(gcPkmn, gbaPkmn->catchLevel);
    pokemonBiosSetCatchBallId(gcPkmn, gbaPkmn->catchBall);
    pokemonBiosSetCatchTrainerSex(gcPkmn, gbaPkmn->catchTrainerSex);
    
    pokemonBiosSetMaxHpRnd(gcPkmn, gbaPkmn->hpIv & 0x1F);
    pokemonBiosSetPhyAtkRnd(gcPkmn, (gbaPkmn->atkIv << 3) & 0x1F8);
    pokemonBiosSetPhyDefRnd(gcPkmn, (gbaPkmn->defIv << 2) & 0x1FC);
    pokemonBiosSetNimblenessRnd(gcPkmn, (gbaPkmn->spdIv << 12) & 0xF000);
    pokemonBiosSetSpeAtkRnd(gcPkmn, (gbaPkmn->spaIv << 3) & 0x1F8);
    pokemonBiosSetSpeDefRnd(gcPkmn, (gbaPkmn->spdIv2 << 1) & 0x1FE);
    
    pokemonBiosSetTamagoFlag(gcPkmn, (gbaPkmn->packedFlags >> 25) & 1);
    pokemonBiosSetTokuseiFlag(gcPkmn, (gbaPkmn->packedFlags >> 24) & 1);
    
    pokemonBiosSetStyleMedal(gcPkmn, gbaPkmn->medalFlags & 0x7);
    pokemonBiosSetBeautifulMedal(gcPkmn, (gbaPkmn->medalFlags >> 3) & 0x7);
    pokemonBiosSetCuteMedal(gcPkmn, (gbaPkmn->medalFlags >> 6) & 0x7);
    pokemonBiosSetCleverMedal(gcPkmn, (gbaPkmn->medalFlags >> 8) & 0x7);
    pokemonBiosSetStrongMedal(gcPkmn, (gbaPkmn->medalFlags >> 11) & 0x7);
    
    pokemonBiosSetChampRibbon(gcPkmn, (gbaPkmn->ribbons >> 24) & 1);
    pokemonBiosSetWinningRibbon(gcPkmn, (gbaPkmn->ribbons >> 31) & 1);
    pokemonBiosSetVictoryRibbon(gcPkmn, (gbaPkmn->ribbons >> 30) & 1);
    pokemonBiosSetBromideRibbon(gcPkmn, (gbaPkmn->ribbons >> 29) & 1);
    pokemonBiosSetGanbaRibbon(gcPkmn, (gbaPkmn->ribbons >> 28) & 1);
    pokemonBiosSetMarineRibbon(gcPkmn, (gbaPkmn->ribbons >> 27) & 1);
    pokemonBiosSetLandRibbon(gcPkmn, (gbaPkmn->ribbons >> 26) & 1);
    pokemonBiosSetSkyRibbon(gcPkmn, (gbaPkmn->ribbons >> 25) & 1);
    pokemonBiosSetCountryRibbon(gcPkmn, (gbaPkmn->ribbons >> 24) & 1);
    pokemonBiosSetNationalRibbon(gcPkmn, (gbaPkmn->ribbons2 >> 31) & 1);
    pokemonBiosSetEarthRibbon(gcPkmn, (gbaPkmn->ribbons2 >> 30) & 1);
    pokemonBiosSetWorldRibbon(gcPkmn, (gbaPkmn->ribbons2 >> 29) & 1);
    pokemonBiosSetAmariRibbon(gcPkmn, (gbaPkmn->ribbons2 >> 24) & 0xF);
    pokemonBiosSetEventGetFlag(gcPkmn, (gbaPkmn->ribbons2 >> 24) & 1);
    
    gbaPokemonConditonToGC(gcPkmn, _swap32(gbaPkmn->condition));
    pokemonBiosSetConditionAmari(gcPkmn, gbaPkmn->condition & 0xFFF);
    
    pokemonBiosSetLevel(gcPkmn, gbaPkmn->level);
    pokemonBiosSetMailId(gcPkmn, gbaPkmn->mailId);
    
    pokemonBiosSetMaxHp(gcPkmn, _swap16(gbaPkmn->maxHp));
    pokemonBiosSetHp(gcPkmn, _swap16(gbaPkmn->hp));
    pokemonBiosSetPhyAtk(gcPkmn, _swap16(gbaPkmn->atk));
    pokemonBiosSetPhyDef(gcPkmn, _swap16(gbaPkmn->def));
    pokemonBiosSetNimbleness(gcPkmn, _swap16(gbaPkmn->spd));
    pokemonBiosSetSpeAtk(gcPkmn, _swap16(gbaPkmn->spa));
    pokemonBiosSetSpeDef(gcPkmn, _swap16(gbaPkmn->spd2));
}

u32 gbaPokemonConditonFromGC(Pokemon* pkmn) {
    u32 gbaStatus = 0;
    
    if (pokemonIsJoutaiDataId(pkmn, 4)) {
        s16 count = pokemonGetCountAsJoutaiDataId(pkmn, 4);
        gbaStatus = ((count & 0xFF) << 8) | 0x80;
        return gbaStatus;
    }
    
    if (pokemonIsJoutaiDataId(pkmn, 5)) {
        gbaStatus |= 0x40;
        return gbaStatus;
    }
    
    if (pokemonIsJoutaiDataId(pkmn, 7)) {
        gbaStatus |= 0x20;
        return gbaStatus;
    }
    
    if (pokemonIsJoutaiDataId(pkmn, 6)) {
        gbaStatus |= 0x10;
        return gbaStatus;
    }
    
    if (pokemonIsJoutaiDataId(pkmn, 3)) {
        gbaStatus |= 0x08;
        return gbaStatus;
    }
    
    if (pokemonIsJoutaiDataId(pkmn, 8)) {
        s8 count = pokemonGetKaisuuJoutaiDataId(pkmn, 8);
        gbaStatus = count & 0x7;
        return gbaStatus;
    }
    
    return gbaStatus;
}

void gbaPokemonConditonToGC(Pokemon* pkmn, u32 gbaStatus) {
    u32 statusByte = gbaStatus & 0xFF;
    
    if ((statusByte & 0x01) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 4, 0);
        s16 count = ((gbaStatus >> 16) & 0xFF) >> 8;
        pokemonSetCountAsJoutaiDataId(pkmn, 4, count);
        return;
    }
    
    if ((statusByte & 0x02) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 5, 0);
        return;
    }
    
    if ((statusByte & 0x04) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 7, 0);
        return;
    }
    
    if ((statusByte & 0x08) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 6, 0);
        return;
    }
    
    if ((statusByte & 0x10) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 3, 0);
        return;
    }
    
    if ((statusByte & 0xE0) != 0) {
        pokemonWriteJoutaiDataId(pkmn, 8, 0);
        s8 count = statusByte >> 5;
        pokemonSetKaisuuJoutaiDataId(pkmn, 8, count);
        return;
    }
}

void _rotatepp(u8* pp, u32 count) {
    u32 num;
    u32 num2;
    u8 temp[0x10];
    
    num = ((u64)0xAAAB * count >> 4) * 0x18;
    num = count - num;
    
    num2 = ((u64)0xAAAB * num >> 2);
    if (num2 != 0) {
        memcpy(temp, pp, 0xC);
        memmove(pp, pp + num2 * 0xC, (0x18 - num2 * 0xC));
        memcpy(pp + (0x18 - num2 * 0xC), temp, 0xC);
    }
    
    num2 = num - ((u64)0xAAAB * num >> 2) * 0x6;
    num2 >>= 1;
    if (num2 != 0) {
        memcpy(temp, pp + 0xC, 0xC);
        memmove(pp + 0x18, pp + 0xC, num2 * 0xC);
        memcpy(pp + 0xC + num2 * 0xC, temp, 0xC);
    }
    
    if ((num & 0x80000000) != 0) {
        memcpy(temp, pp + 0x24, 0xC);
        memcpy(pp + 0x24, pp + 0x18, 0xC);
        memcpy(pp + 0x18, temp, 0xC);
    }
}

void _revrotatepp(u8* pp, u32 count) {
    u32 num;
    u32 num2;
    u8 temp[0x10];
    
    if ((count & 0x80000000) != 0) {
        memcpy(temp, pp + 0x18, 0xC);
        memcpy(pp + 0x18, pp + 0x24, 0xC);
        memcpy(pp + 0x24, temp, 0xC);
    }
    
    num = count >> 1;
    num2 = num - ((u64)0xAAAB * num >> 1) * 0x3;
    if (num2 != 0) {
        memcpy(temp, pp + 0xC, 0xC);
        memmove(pp + 0xC, pp + 0x18, num2 * 0xC);
        memcpy(pp + 0xC + num2 * 0xC, temp, 0xC);
    }
    
    num = ((u64)0xAAAB * count >> 2) >> 30;
    if (num != 0) {
        memcpy(temp, pp, 0xC);
        memmove(pp, pp + 0xC, num * 0xC);
        memcpy(pp + num * 0xC, temp, 0xC);
    }
}
