// Decompiled from: dbgMenuRelive.cpp
// Address range: 0x8000E53C..0x8000E5AC | size: 0x70

/* Forward declarations */
void* heroGetStatus(s32 a, s32 b, s32 c);
s32    pokemonIsDarkPokemon(void* pokemon);
void   pokemonSetDp(void* pokemon, f32 dp);
void   preReliveSetParameter(s32 a, s32 b, s32 c);

/* SData2 */
static const f32 _DP_Zero = 0.0f;

/*
  Address: 0x8000E53C | size: 0x70
  dbgMenuRelive(void)
  Debug function to relive a Pokemon. Checks if the Pokemon is dark,
  and if so, sets DP to 0 and calls preReliveSetParameter.
*/
s32 dbgMenuRelive(void) {
    void* pokemon = heroGetStatus(0, 3, 0);
    
    if (pokemonIsDarkPokemon(pokemon)) {
        pokemonSetDp(pokemon, _DP_Zero);
        preReliveSetParameter(0, 0, 1);
    }
    
    return 0;
}
