# pokeconv Analysis

## Function Purpose
Converts GBA Pokémon data structure to GameCube internal format during XD↔GBA connectivity.

## Key Conversion Steps

### Region Detection
```c
u32 region_id = *(u32*)gba_save;
u8 region_type = (region_id >> 18) & 0xF;
```
- Extracts bits 18-21 from first 4 bytes of GBA save
- Maps to home location:
  | Region Type | Home Place |
  |-------------|------------|
  | 1, 2        | 1 (Orre)   |
  | 3           | 2 (Phenac) |
  | 5           | 3 (Pyrite) |
  | Other       | 0 (Default)|

### Name Conversion
- Uses `GScharMakeFromGBA` to convert GBA's 7-character name
- Handles GBA→GC character encoding differences

### Party Conversion
```c
for (int i = 0; i < 6; i++) {
    gbaPokemonToGC(gc_pkmn, &gba_save->party[i]);
}
```
- Processes all 6 party Pokémon
- Maintains species ID mapping via `pokemonBiosSetFightTrainerPokemonDataId`

### Ribbon Processing
- Handles 11 ribbon flags (matches GBA's 11 ribbon slots)
- Direct byte transfer via `exribbonSetNo`

## Critical Assumptions
1. `GbaPokemonSave` struct layout:
```c
struct GbaPokemonSave {
    u32 region_data;    // +0x00
    u8 name[7];         // +0x04
    u8 gender;          // +0x0C
    u32 rng_seed;       // +0x10
    GbaPokemon party[6];
    u8 ribbons[11];    // +0x26C
};
```
2. Byte-swapped RNG seed required for GC compatibility

## Validation Notes
- Matches assembly logic flow exactly
- Confirmed loop counters (6 Pokémon, 11 ribbons)
- Verified bitfield extraction matches `extrwi` instruction