// Decompiled from: gbaPokemon.cpp
// Address range: 0x80026898..0x80027E84 | size: 0x15EC

/* Forward declarations */
static u32 _swap32(u32 val);
static u16 _swap16(u16 val);
static void _rotatepp(u8* pp, u32 key);
static void _revrotatepp(u8* pp, u32 key);
static u16 gbaPokemonConditonFromGC(void* pokemon);
static u16 gbaPokemonConditonToGC(void* pokemon, u16 gbaCondition);

/* Jump tables for attestation version and language area conversion */
static void* sAttestVerTable[12] = {
    (void*)0x800269A4, // 0: Invalid -> set ver=0
    (void*)0x80026968, // 1: RSE -> ver=4
    (void*)0x8002697C, // 2: FRLG -> ver=5
    (void*)0x800269A4, // 3: Invalid -> set ver=0
    (void*)0x800269A4, // 4: Invalid -> set ver=0
    (void*)0x800269A4, // 5: Invalid -> set ver=0
    (void*)0x800269A4, // 6: Invalid -> set ver=0
    (void*)0x800269A4, // 7: Invalid -> set ver=0
    (void*)0x8002692C, // 8: R -> ver=1
    (void*)0x80026940, // 9: S -> ver=2
    (void*)0x80026954, // A: E -> ver=3
    (void*)0x80026990, // B: D -> ver=0xF
};

static void* sLangAreaTable[10] = {
    (void*)0x80026A40, // 0: Invalid -> set lang=0
    (void*)0x800269E0, // 1: J -> lang=1
    (void*)0x800269EC, // 2: U -> lang=2
    (void*)0x800269F8, // 3: G -> lang=5
    (void*)0x80026A04, // 4: F -> lang=3
    (void*)0x80026A10, // 5: I -> lang=4
    (void*)0x80026A1C, // 6: C -> lang=7
    (void*)0x80026A28, // 7: K -> lang=2
    (void*)0x80026A34, // 8: T -> lang=2
    (void*)0x80026A40, // 9: Invalid -> set lang=0
};

/* Reverse jump tables for GBA->GC conversion */
static void* sLangAreaRevTable[8] = {
    (void*)0x80027438, // 0: Invalid
    (void*)0x800273F0, // 1: J -> ver=1, lang=1
    (void*)0x800273FC, // 2: U -> ver=2, lang=2
    (void*)0x80027408, // 3: F -> ver=3, lang=4
    (void*)0x80027414, // 4: I -> ver=3, lang=5
    (void*)0x80027420, // 5: G -> ver=3, lang=3
    (void*)0x8002742C, // 6: C -> ver=3, lang=6
    (void*)0x80027438, // 7: Invalid
};

static void* sAttestVerRevTable[16] = {
    (void*)0x800273C8, // 0: Invalid
    (void*)0x80027398, // 1: R -> ver=8
    (void*)0x800273A0, // 2: S -> ver=9
    (void*)0x800273A8, // 3: E -> ver=0xA
    (void*)0x800273B0, // 4: FRLG -> ver=1
    (void*)0x800273B8, // 5: RSE -> ver=2
    (void*)0x800273C8, // 6: Invalid
    (void*)0x800273C8, // 7: Invalid
    (void*)0x800273C8, // 8: Invalid
    (void*)0x800273C8, // 9: Invalid
    (void*)0x800273C8, // A: Invalid
    (void*)0x800273C8, // B: Invalid
    (void*)0x800273C8, // C: Invalid
    (void*)0x800273C8, // D: Invalid
    (void*)0x800273C8, // E: Invalid
    (void*)0x800273C0, // F: D -> ver=0xB
};

/*
  Address: 0x80026898 | size: 0x974
  gbaPokemonFromGC(void* gcPkmn, void* gbaPkmn)
  Converts a GC Pokemon to GBA format.
*/
void gbaPokemonFromGC(void* gcPkmn, void* gbaPkmn) {
    memset(gbaPkmn, 0, 0x64);
    
    if (!pokemonCheckValid(gcPkmn)) {
        return;
    }
    
    // Copy encrypted data
    *(u32*)gbaPkmn = _swap32(pokemonBiosGetRnd(gcPkmn));
    *((u32*)gbaPkmn + 1) = _swap32(pokemonBiosGetCatchTrainerRnd(gcPkmn));
    
    // Handle attestation
    void* attest = pokemonBiosGetAttest(gcPkmn);
    s32 verId = gamedataAttestBiosGetVerId(attest);
    
    u8 ver = 0;
    if (verId <= 0xB) {
        // Jump table based on version
        // Sets ver in gbaPkmn[0x10] bits 21-24
        switch (verId) {
            case 8: ver = 1; break;  // R
            case 9: ver = 2; break;  // S
            case 0xA: ver = 3; break; // E
            case 0xB: ver = 0xF; break; // D
            default: ver = 0; break;
        }
    }
    *((u16*)gbaPkmn + 0x8) |= ver << 4;
    
    s32 langId = gamedataAttestBiosGetLangareaId(attest);
    u8 lang = 0;
    if (langId <= 0x9) {
        switch (langId) {
            case 1: lang = 1; break;  // J
            case 2: lang = 2; break;  // U
            case 3: lang = 5; break;  // G
            case 4: lang = 3; break;  // F
            case 5: lang = 4; break;  // I
            case 6: lang = 7; break;  // C
            case 7: lang = 2; break;  // K
            case 8: lang = 2; break;  // T
            default: lang = 0; break;
        }
    }
    ((u8*)gbaPkmn)[0x12] = lang;
    
    // Set flags
    ((u8*)gbaPkmn)[0x13] |= 1 << 30; // Nickname flag
    if (pokemonBiosGetTamagoFlag(gcPkmn)) {
        ((u8*)gbaPkmn)[0x13] |= 1 << 29; // Egg flag
    }
    ((u8*)gbaPkmn)[0x13] |= (pokemonBiosGetFlagAmari(gcPkmn) & 0xF) << 24;
    if (pokemonBiosGetFuseiFlag(gcPkmn)) {
        ((u8*)gbaPkmn)[0x13] |= 1 << 31; // Nicknamed flag
    }
    
    // Convert nickname
    s32 lang = gamedataAttestBiosGetLangareaId(attest);
    char* nick = pokemonBiosGetNicknameOrgPtr(gcPkmn);
    s32 nickLen = GBAMakeFromGSchar((u8*)gbaPkmn + 8, nick, lang, 0xA);
    if (nickLen < 0xA) {
        ((u8*)gbaPkmn)[8 + nickLen] = 0xFF;
        memset((u8*)gbaPkmn + 8 + nickLen + 1, 0, 0xA - nickLen - 1);
    }
    
    // Convert trainer name
    char* trainerName = pokemonBiosGetCatchTrainerNamePtr(gcPkmn);
    s32 trainerLen = GBAMakeFromGSchar((u8*)gbaPkmn + 0x14, trainerName, lang, 0x7);
    if (trainerLen < 0x7) {
        ((u8*)gbaPkmn)[0x14 + trainerLen] = 0xFF;
        memset((u8*)gbaPkmn + 0x14 + trainerLen + 1, 0, 0x7 - trainerLen - 1);
    }
    
    // Copy basic data
    ((u8*)gbaPkmn)[0x1B] = pokemonBiosGetPcboxMark(gcPkmn);
    *((u16*)(gbaPkmn) + 0x1E) = _swap16(pokemonBiosGetAmari(gcPkmn));
    *((u16*)(gbaPkmn) + 0x20) = _swap16(pokemonBiosGetPokemonDataId(gcPkmn));
    *((u16*)(gbaPkmn) + 0x22) = _swap16(pokemonBiosGetItemDataId(gcPkmn));
    *((u32*)(gbaPkmn) + 0x24) = _swap32(pokemonBiosGetExp(gcPkmn));
    ((u8*)gbaPkmn)[0x29] = pokemonBiosGetFriend(gcPkmn);
    *((u16*)(gbaPkmn) + 0x2A) = pokemonBiosGetPara1Amari(gcPkmn);
    ((u8*)gbaPkmn)[0x28] = 0;
    
    // Copy moves and PP
    for (s32 i = 0; i < 4; i++) {
        *((u16*)(gbaPkmn) + 0x2C + i) = _swap16(pokemonBiosGetPokemonWazaDataId(gcPkmn, i));
        u8 ppCount = pokemonBiosGetPokemonWazaPpCount(gcPkmn, i);
        ((u8*)gbaPkmn)[0x28] |= (ppCount & 0xF) << ((i & 1) ? 4 : 0);
        ((u8*)gbaPkmn)[0x34 + i] = pokemonBiosGetPokemonWazaPp(gcPkmn, i);
    }
    
    // Copy effort values
    ((u8*)gbaPkmn)[0x38] = pokemonBiosGetMaxHpEffort(gcPkmn);
    ((u8*)gbaPkmn)[0x39] = pokemonBiosGetPhyAtkEffort(gcPkmn);
    ((u8*)gbaPkmn)[0x3A] = pokemonBiosGetPhyDefEffort(gcPkmn);
    ((u8*)gbaPkmn)[0x3B] = pokemonBiosGetNimblenessEffort(gcPkmn);
    ((u8*)gbaPkmn)[0x3C] = pokemonBiosGetSpeAtkEffort(gcPkmn);
    ((u8*)gbaPkmn)[0x3D] = pokemonBiosGetSpeDefEffort(gcPkmn);
    
    // Copy contest stats
    ((u8*)gbaPkmn)[0x3E] = pokemonBiosGetStyle(gcPkmn);
    ((u8*)gbaPkmn)[0x3F] = pokemonBiosGetBeautiful(gcPkmn);
    ((u8*)gbaPkmn)[0x40] = pokemonBiosGetCute(gcPkmn);
    ((u8*)gbaPkmn)[0x41] = pokemonBiosGetClever(gcPkmn);
    ((u8*)gbaPkmn)[0x42] = pokemonBiosGetStrong(gcPkmn);
    ((u8*)gbaPkmn)[0x43] = pokemonBiosGetFur(gcPkmn);
    
    // Pack flags into GBA format
    // ... (bit packing for various flags)
    
    // Convert condition
    u32 condition = pokemonBiosGetConditionAmari(gcPkmn);
    u16 gbaCondition = gbaPokemonConditonFromGC(gcPkmn);
    *((u32*)gbaPkmn + 0x50) = _swap32(gbaCondition | (condition & 0xFFF000));
    
    // Copy level and stats
    ((u8*)gbaPkmn)[0x54] = pokemonBiosGetLevel(gcPkmn);
    ((u8*)gbaPkmn)[0x55] = pokemonBiosGetMailId(gcPkmn);
    *((u16*)(gbaPkmn) + 0x58) = _swap16(pokemonBiosGetMaxHp(gcPkmn));
    *((u16*)(gbaPkmn) + 0x56) = _swap16(pokemonBiosGetHp(gcPkmn));
    *((u16*)(gbaPkmn) + 0x5A) = _swap16(pokemonBiosGetPhyAtk(gcPkmn));
    *((u16*)(gbaPkmn) + 0x5C) = _swap16(pokemonBiosGetPhyDef(gcPkmn));
    *((u16*)(gbaPkmn) + 0x5E) = _swap16(pokemonBiosGetNimbleness(gcPkmn));
    *((u16*)(gbaPkmn) + 0x60) = _swap16(pokemonBiosGetSpeAtk(gcPkmn));
    *((u16*)(gbaPkmn) + 0x62) = _swap16(pokemonBiosGetSpeDef(gcPkmn));
    
    // Apply PP rotation encryption
    u32 key0 = _swap32(*(u32*)gbaPkmn);
    u32 key1 = _swap32(*((u32*)gbaPkmn + 1));
    _rotatepp((u8*)gbaPkmn + 0x20, key0 ^ key1);
}

/*
  Address: 0x8002720C | size: 0x7C0
  gbaPokemonToGC(void* gbaPkmn, void* gcPkmn)
  Converts a GBA Pokemon to GC format.
*/
void gbaPokemonToGC(void* gbaPkmn, void* gcPkmn) {
    pokemonInit(gcPkmn);
    
    // Check validity flag
    if (!(((u8*)gbaPkmn)[0x13] >> 30 & 1) && !(((u8*)gbaPkmn)[0x13] >> 31 & 1)) {
        return;
    }
    
    // Reverse PP rotation
    u32 key0 = _swap32(*(u32*)gbaPkmn);
    u32 key1 = _swap32(*((u32*)gbaPkmn + 1));
    _revrotatepp((u8*)gbaPkmn + 0x20, key0 ^ key1);
    
    // Set basic data
    pokemonBiosSetRnd(gcPkmn, _swap32(*(u32*)gbaPkmn));
    pokemonBiosSetCatchTrainerRnd(gcPkmn, _swap32(*((u32*)gbaPkmn + 1)));
    
    // Extract version and language
    u8 ver = (((u16*)gbaPkmn)[8] >> 4) & 0xF;
    u8 lang = ((u8*)gbaPkmn)[0x12];
    
    s32 attestVer = 0;
    s32 attestLang = 0;
    if (ver <= 0xF) {
        switch (ver) {
            case 8: attestVer = 0x8; break;
            case 9: attestVer = 0x9; break;
            case 0xA: attestVer = 0xA; break;
            case 0xB: attestVer = 0xB; break;
            default: attestVer = 0; break;
        }
    }
    if (lang <= 7) {
        switch (lang) {
            case 1: attestLang = 1; break;
            case 2: attestLang = 2; break;
            case 3: attestLang = 4; break;
            case 4: attestLang = 5; break;
            case 5: attestLang = 3; break;
            case 6: attestLang = 6; break;
            default: attestLang = 0; break;
        }
    }
    
    // Create attestation
    pokemonBiosGetAttest(gcPkmn);
    gamedataAttestCreate(gcPkmn, attestVer, 3, attestLang, attestLang);
    
    // Convert nickname
    GScharMakeFromGBA((u8*)gcPkmn + 0x14, (u8*)gbaPkmn + 8, 0xA);
    pokemonBiosSetNicknamePtr(gcPkmn, (u8*)gcPkmn + 0x14);
    
    // Set flags
    pokemonBiosSetFlagAmari(gcPkmn, (((u8*)gbaPkmn)[0x13] >> 24) & 0xF);
    pokemonBiosSetFuseiFlag(gcPkmn, (((u8*)gbaPkmn)[0x13] >> 31) & 1);
    
    // Convert trainer name
    GScharMakeFromGBA((u8*)gcPkmn + 0x14, (u8*)gbaPkmn + 0x14, 0x7);
    
    // Set remaining data
    pokemonBiosSetPcboxMark(gcPkmn, ((u8*)gbaPkmn)[0x1B]);
    pokemonBiosSetAmari(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x1E)));
    pokemonBiosSetPokemonDataId(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x20)));
    pokemonBiosSetItemDataId(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x22)));
    pokemonBiosSetExp(gcPkmn, _swap32(*((u32*)gbaPkmn + 0x24)));
    pokemonBiosSetFriend(gcPkmn, ((u8*)gbaPkmn)[0x29]);
    pokemonBiosSetPara1Amari(gcPkmn, *((u16*)gbaPkmn + 0x2A));
    
    // Set moves and PP
    for (s32 i = 0; i < 4; i++) {
        pokemonBiosSetPokemonWazaDataId(gcPkmn, i, _swap16(*((u16*)gbaPkmn + 0x2C + i)));
        pokemonBiosSetPokemonWazaPpCount(gcPkmn, i, (((u8*)gbaPkmn)[0x28] >> ((i & 1) ? 4 : 0)) & 0xF);
        pokemonBiosSetPokemonWazaPp(gcPkmn, i, ((u8*)gbaPkmn)[0x34 + i]);
    }
    
    // Set effort values
    pokemonBiosSetMaxHpEffort(gcPkmn, ((u8*)gbaPkmn)[0x38]);
    pokemonBiosSetPhyAtkEffort(gcPkmn, ((u8*)gbaPkmn)[0x39]);
    pokemonBiosSetPhyDefEffort(gcPkmn, ((u8*)gbaPkmn)[0x3A]);
    pokemonBiosSetNimblenessEffort(gcPkmn, ((u8*)gbaPkmn)[0x3B]);
    pokemonBiosSetSpeAtkEffort(gcPkmn, ((u8*)gbaPkmn)[0x3C]);
    pokemonBiosSetSpeDefEffort(gcPkmn, ((u8*)gbaPkmn)[0x3D]);
    
    // Set contest stats
    pokemonBiosSetStyle(gcPkmn, ((u8*)gbaPkmn)[0x3E]);
    pokemonBiosSetBeautiful(gcPkmn, ((u8*)gbaPkmn)[0x3F]);
    pokemonBiosSetCute(gcPkmn, ((u8*)gbaPkmn)[0x40]);
    pokemonBiosSetClever(gcPkmn, ((u8*)gbaPkmn)[0x41]);
    pokemonBiosSetStrong(gcPkmn, ((u8*)gbaPkmn)[0x42]);
    pokemonBiosSetFur(gcPkmn, ((u8*)gbaPkmn)[0x43]);
    
    // Set condition
    gbaPokemonConditonToGC(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x50)));
    pokemonBiosSetConditionAmari(gcPkmn, _swap32(*((u32*)gbaPkmn + 0x50)) & 0xFFF000);
    
    // Set level and stats
    pokemonBiosSetLevel(gcPkmn, ((u8*)gbaPkmn)[0x54]);
    pokemonBiosSetMailId(gcPkmn, ((u8*)gbaPkmn)[0x55]);
    pokemonBiosSetMaxHp(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x58)));
    pokemonBiosSetHp(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x56)));
    pokemonBiosSetPhyAtk(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x5A)));
    pokemonBiosSetPhyDef(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x5C)));
    pokemonBiosSetNimbleness(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x5E)));
    pokemonBiosSetSpeAtk(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x60)));
    pokemonBiosSetSpeDef(gcPkmn, _swap16(*((u16*)gbaPkmn + 0x62)));
}

/*
  Address: 0x800279CC | size: 0x128
  gbaPokemonConditonFromGC(void* pokemon)
  Converts GC condition status to GBA format.
*/
static u16 gbaPokemonConditonFromGC(void* pokemon) {
    u16 result = 0;
    
    if (pokemonIsJoutaiDataId(pokemon, 4)) {
        s32 count = pokemonGetCountAsJoutaiDataId(pokemon, 4);
        result = (count << 8) | 0x80;
    } else if (pokemonIsJoutaiDataId(pokemon, 5)) {
        result |= 0x40;
    } else if (pokemonIsJoutaiDataId(pokemon, 7)) {
        result |= 0x20;
    } else if (pokemonIsJoutaiDataId(pokemon, 6)) {
        result |= 0x10;
    } else if (pokemonIsJoutaiDataId(pokemon, 3)) {
        result |= 0x8;
    } else if (pokemonIsJoutaiDataId(pokemon, 8)) {
        s32 toxicCount = pokemonGetKaisuuJoutaiDataId(pokemon, 8);
        result = toxicCount & 0xFF;
    }
    
    return result;
}

/*
  Address: 0x80027AF4 | size: 0x100
  gbaPokemonConditonToGC(void* pokemon, u16 gbaCondition)
  Converts GBA condition status to GC format.
*/
static void gbaPokemonConditonToGC(void* pokemon, u16 gbaCondition) {
    if (gbaCondition & 0x80) {
        pokemonWriteJoutaiDataId(pokemon, 4, 0);
        s32 count = (gbaCondition >> 8) & 0xF;
        pokemonSetCountAsJoutaiDataId(pokemon, 4, count);
    } else if (gbaCondition & 0x40) {
        pokemonWriteJoutaiDataId(pokemon, 5, 0);
    } else if (gbaCondition & 0x20) {
        pokemonWriteJoutaiDataId(pokemon, 7, 0);
    } else if (gbaCondition & 0x10) {
        pokemonWriteJoutaiDataId(pokemon, 6, 0);
    } else if (gbaCondition & 0x8) {
        pokemonWriteJoutaiDataId(pokemon, 3, 0);
    } else if (gbaCondition & 0x1F) {
        pokemonWriteJoutaiDataId(pokemon, 8, 0);
        pokemonSetKaisuuJoutaiDataId(pokemon, 8, gbaCondition & 0x1F);
    }
}

/*
  Address: 0x80027BF4 | size: 0x12C
  _rotatepp(u8* pp, u32 key)
  Rotates PP data for encryption.
*/
static void _rotatepp(u8* pp, u32 key) {
    s32 div = (key * 0x55555556) >> 4;
    div = (key - div * 0x18);
    s32 numFull = (div * 0x55555556) >> 2;
    
    if (numFull > 0) {
        u8 temp[0xC];
        memcpy(temp, pp + numFull * 0xC, 0xC);
        memmove(pp, pp + 0xC, numFull * 0xC);
        memcpy(pp + numFull * 0xC, temp, 0xC);
    }
    
    s32 remainder = (div * 0x55555556) >> 2;
    remainder = div - remainder * 6;
    s32 half = remainder >> 1;
    
    if (half > 0) {
        u8 temp[0xC];
        memcpy(temp, pp + half * 0xC + 0xC, 0xC);
        memmove(pp + 0x18, pp + 0xC, half * 0xC);
        memcpy(pp + 0xC, temp, 0xC);
    }
    
    if (remainder & 1) {
        u8 temp[0xC];
        memcpy(temp, pp + 0x24, 0xC);
        memcpy(pp + 0x24, pp + 0x18, 0xC);
        memcpy(pp + 0x18, temp, 0xC);
    }
}

/*
  Address: 0x80027D20 | size: 0x124
  _revrotatepp(u8* pp, u32 key)
  Reverses PP rotation encryption.
*/
static void _revrotatepp(u8* pp, u32 key) {
    if (key & 0x80000000) {
        u8 temp[0xC];
        memcpy(temp, pp + 0x18, 0xC);
        memcpy(pp + 0x18, pp + 0x24, 0xC);
        memcpy(pp + 0x24, temp, 0xC);
    }
    
    s32 div = ((key >> 1) * 0x55555556) >> 1;
    div = ((key >> 1) - div * 3);
    
    if (div > 0) {
        u8 temp[0xC];
        memcpy(temp, pp + 0xC, 0xC);
        memmove(pp + 0xC, pp + 0x18, div * 0xC);
        memcpy(pp + div * 0xC + 0xC, temp, 0xC);
    }
    
    s32 numFull = ((key * 0x55555556) >> 2) & 0x80000000;
    if (numFull) {
        u8 temp[0xC];
        memcpy(temp, pp, 0xC);
        memmove(pp, pp + 0xC, numFull * 0xC);
        memcpy(pp + numFull * 0xC, temp, 0xC);
    }
}

/*
  Address: 0x80027E44 | size: 0x28
  _swap32(u32 val)
  Swaps byte order of a 32-bit value.
*/
static u32 _swap32(u32 val) {
    return ((val >> 24) & 0xFF) |
           ((val >> 8) & 0xFF00) |
           ((val << 8) & 0xFF0000) |
           ((val << 24) & 0xFF000000);
}

/*
  Address: 0x80027E6C | size: 0x18
  _swap16(u16 val)
  Swaps byte order of a 16-bit value.
*/
static u16 _swap16(u16 val) {
    return ((val >> 8) & 0xFF) | ((val << 8) & 0xFF00);
}
