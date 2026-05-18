#ifndef GBA_POKEMON_H
#define GBA_POKEMON_H

#include <stdint.h>
#include "types.h"

// GBA Pokémon data structure (Game Boy Advance → GameCube conversion)
typedef struct {
    uint32_t region_data;     // Region identification (bits 18-21 used)
    char name[7];             // 7-character name (GBA format)
    uint8_t gender;            // Gender byte (0=male, 1=female)
    uint32_t rng_seed;        // RNG seed (requires endian swap)
    uint8_t unknown1[4];        // Padding/unknown
    
    // 6-party Pokémon data
    struct {
        uint16_t species;      // GBA species ID
        uint16_t item;         // Held item
        uint32_t trainer_id;    // Trainer ID (requires endian swap)
        uint32_t exp;         // Experience (requires endian swap)
        uint32_t pid;         // Personality ID
        uint32_t ivs;          // IVs (bit-packed)
        uint16_t moves[4];    // Moves
        uint8_t pp[4];         // PP values
        uint8_t pp_ups[4];    // PP Ups
        uint8_t friendship;    // Happiness value
        uint8_t condition;    // Status condition
        uint8_t level;         // Current level
        uint8_t pokerus;      // Pokérus status
        uint8_t caught_data[4];// Caught location/data
        uint8_t coolness;     // Contest stats
        uint8_t beauty;
        uint8_t cuteness;
        uint8_t smartness;
        uint8_t toughness;
        uint8_t feel;
    } party[6];
    
    uint8_t unknown2[0x1A0];  // Unknown padding
    
    // Ribbon data (11 bytes)
    uint8_t ribbons[11];
    
    uint8_t unknown3[0x51];   // Final padding to match observed size
} GbaPokemonSave;

#endif // GBA_POKEMON_H
```