#include "pokeconv.h"
#include "hero_bios.h"
#include "pokemon.h"
#include "gba_pokemon.h"
#include "ribbons.h"

void pokeconv(void* hero_data, const GbaPokemonSave* gba_save) {
    // Extract region ID from GBA save (first 4 bytes)
    u32 region_id = *(u32*)gba_save;
    u8 region_type = (region_id >> 18) & 0xF; // Bits 18-21
    
    // Map region type to home place
    u8 home_place;
    switch(region_type) {
        case 1: case 2: home_place = 1; break;
        case 3: home_place = 2; break;
        case 5: home_place = 3; break;
        default: home_place = 0; break;
    }
    heroBiosSetHomePlace(hero_data, home_place);
    
    // Convert name
    char gc_name[8];
    GScharMakeFromGBA(gc_name, gba_save->name, 7);
    heroBiosSetNamePtr(hero_data, gc_name);
    
    // Set sex and RNG seed
    heroBiosSetSexDataId(hero_data, gba_save->gender);
    heroBiosSetRnd(hero_data, swap32(gba_save->rng_seed));
    
    // Convert party Pokemon
    for (int i = 0; i < 6; i++) {
        Pokemon* gc_pkmn = heroBiosGetPokemonPtr(hero_data, i);
        gbaPokemonToGC(gc_pkmn, &gba_save->party[i]);
        pokemonBiosSetFightTrainerPokemonDataId(hero_data, i, gc_pkmn->species);
    }
    
    // Process ribbons
    for (int i = 0; i < 11; i++) {
        exribbonSetNo(hero_data, i, gba_save->ribbons[i]);
    }
}

static inline u32 swap32(u32 val) {
    return ((val & 0xFF) << 24) |
           ((val & 0xFF00) << 8) |
           ((val & 0xFF0000) >> 8) |
           ((val & 0xFF000000) >> 24);
}
