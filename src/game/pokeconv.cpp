// Decompiled from: pokeconv.cpp
// Address range: 0x8006C184..0x8006C320 | size: 0x19C

/* Forward declarations */
void    heroBiosSetHomePlace(void* hero, s32 place);
void*   gamedataGetStatus(s32 a, s32 b);
void    GScharMakeFromGBA(s32* out, void* gbaData, s32 len);
void    heroBiosSetNamePtr(void* hero, const char* name);
void    heroBiosSetSexDataId(void* hero, s32 sex);
void    heroBiosSetRnd(void* hero, u32 rnd);
void*   heroBiosGetPokemonPtr(void* hero, s32 index);
void    gbaPokemonToGC(void* gcPokemon, const u8* gbaData);
void    pokemonBiosSetFightTrainerPokemonDataId(void* pokemon, s32 id);
void    exribbonSetNo(s32 ribbon, u8 value);

/*
  Address: 0x8006C2F8 | size: 0x28
  _swap32(u32 value)
  Swaps the byte order of a 32-bit value (big-endian to little-endian).
*/
u32 _swap32__FUl(u32 value) {
    return ((value & 0x000000FF) << 24) |
           ((value & 0x0000FF00) << 8)  |
           ((value & 0x00FF0000) >> 8)  |
           ((value & 0xFF000000) >> 24);
}

/*
  Address: 0x8006C184 | size: 0x174
  pokeconv(void* hero, const u8* gbaData)
  Converts GBA Pokemon data to GC format.
*/
void pokeconv(void* hero, const u8* gbaData) {
    // Extract home place from GBA data (bits 4-21 of first 4 bytes)
    u32 raw = (gbaData[0] << 24) | (gbaData[1] << 16) | (gbaData[2] << 8) | gbaData[3];
    s32 homePlace = (raw >> 4) & 0x3FFFF;
    
    // Set home place based on extracted value
    switch (homePlace) {
        case 1:
            heroBiosSetHomePlace(hero, 1);
            break;
        case 2:
            heroBiosSetHomePlace(hero, 2);
            break;
        case 3:
            heroBiosSetHomePlace(hero, 2);
            break;
        case 4:
            heroBiosSetHomePlace(hero, 2);
            break;
        case 5:
            heroBiosSetHomePlace(hero, 3);
            break;
        default:
            heroBiosSetHomePlace(hero, 1);
            break;
    }
    
    // Get game data status
    s32 status = (s32)gamedataGetStatus(0, 5);
    
    // Make character name from GBA data
    char name[8];
    GScharMakeFromGBA((s32*)name, (void*)(gbaData + 4), 7);
    heroBiosSetNamePtr(hero, name);
    
    // Set sex
    heroBiosSetSexDataId(hero, gbaData[0xC]);
    
    // Set random value (swap byte order)
    u32 rnd = _swap32__FUl(*(u32*)(gbaData + 0x10));
    heroBiosSetRnd(hero, rnd);
    
    // Convert 6 Pokemon
    const u8* gbaPokemonPtr = gbaData;
    for (s32 i = 0; i < 6; i++) {
        void* gcPokemon = heroBiosGetPokemonPtr(hero, i);
        gbaPokemonToGC(gcPokemon, gbaPokemonPtr + 0x14);
        pokemonBiosSetFightTrainerPokemonDataId(gcPokemon, i);
        gbaPokemonPtr += 0x64;
    }
    
    // Set exhibition ribbons
    for (s32 i = 0; i < 11; i++) {
        exribbonSetNo(i, gbaData[i + 0x26C]);
    }
}
