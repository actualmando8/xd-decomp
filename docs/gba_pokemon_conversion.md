# GBA ↔ GameCube Pokémon Data Conversion

## gbaPokemonToGC Function Analysis

### Memory Layout Mapping
| GBA Field Offset | GC Field Offset | Conversion Needed |
|------------------|-----------------|-------------------|
| 0x00 (species)   | 0x00            | Species ID mapping |
| 0x02 (item)       | 0x02            | Item ID remapping |
| 0x04 (trainer ID) | 0x04            | Endian swap       |
| 0x08 (exp)        | 0x08            | Endian swap       |
| 0x0C (PID)        | 0x0C            | Direct copy       |
| 0x10 (IVs)       | 0x10            | Bitfield rearrangement |
| 0x14 (moves)     | 0x14            | Move ID remapping |
| 0x1C (PP)        | 0x1C            | PP value scaling  |

### Critical Conversion Steps

#### 1. Species ID Translation
```c
// GBA uses different numbering for XD-exclusive forms
if (gba_species == GBA_MEW) {
    gc_species = GC_MEWTWO; // Special handling
} else {
    gc_species = gba_species_table[gba_species];
}
```

#### 2. IV/EV Conversion
- GBA: 30-bit total (5 bits × 6 stats)
- GC: Separate 10-bit fields per stat
```c
for (int i = 0; i < 6; i++) {
    gc->ivs[i] = (gba_ivs >> (i*5)) & 0x1F;
    gc->evs[i] = gba_evs[i] * 4; // Scale 0-63 → 0-252
}
```

#### 3. Status Condition Handling
```c
// Translate GBA status byte to GC status word
switch(gba_status & 0x1F) {
    case 1: gc_status = STATUS_POISONED; break;
    case 2: gc_status = STATUS_BURNED; break;
    // ... other conditions
}
```

### Known Challenges
1. **Move Remapping**: GBA move IDs differ for XD-specific moves
   - Example: `FRUSTRATION` → `XD_FRUSTRATION`

2. **Ribbon Translation**: 8-bit GBA ribbon flags → 32-bit GC ribbon bitmask

3. **Personality Value**: Requires XOR folding for nature calculation

### Validation Approach
1. Compare known GBA/GC Pokémon dumps
2. Verify through in-game connectivity tests
3. Cross-reference with MusyX audio engine calls for battle data

> **Note**: Full implementation requires analysis of `gbaPokemonConditonToGC` (0x800279CC) for secondary status effects.