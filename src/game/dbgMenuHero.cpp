// Decompiled from: dbgMenuHero.cpp
// Address range: 0x8000AD7C..0x8000B15C | size: 0x3E0

s32     menuDbgItemCreate(void);
s32     menuOpen(s32 menuId, s32 param);
void    heroAddPokecoupon(s32 a, s32 amount);
void    heroAddPokedoru(s32 a, s32 amount);
s32     fightIsFight(void);
void    pokemonInit(void* pokemon);
s32     dbgMenuPokemonEditSub(void* pokemon, s32 a, s32 b, s32 c, s32 d, s32 e);
void*   heroGetStatus(s32 a, s32 b, s32 c);
void    heroCatchPokemon(s32 a, void* pokemon, s32 b, s32 c, s32 d);

/* Global state */
static u8 firstFlag = 1;
static u8 pokemon[0xC4];

/*
  Address: 0x8000AD7C | size: 0x24
  dbgMenuHeroCreateItem()
  Opens the item creation debug menu.
*/
s32 dbgMenuHeroCreateItem(void) {
    menuDbgItemCreate();
    return 0;
}

/*
  Address: 0x8000ADA0 | size: 0x48
  dbgMenuHeroIncCoupon()
  Opens menu 0x2, adds selected number of Pokecoupons to hero.
*/
s32 dbgMenuHeroIncCoupon(void) {
    s32 result = menuOpen(0x2, 1);
    if (result != -1) {
        heroAddPokecoupon(0, result);
    }
    return 0;
}

/*
  Address: 0x8000ADE8 | size: 0x48
  dbgMenuHeroIncMoney()
  Opens menu 0x2, adds selected amount of Poke dollars to hero.
*/
s32 dbgMenuHeroIncMoney(void) {
    s32 result = menuOpen(0x2, 1);
    if (result != -1) {
        heroAddPokedoru(0, result);
    }
    return 0;
}

/*
  Address: 0x8000AE30 | size: 0xA4
  dbgMenuHeroPokemonAdd()
  Adds a new Pokemon to hero's party.
  Initializes pokemon struct if first time, opens edit menu, then catches.
  Returns -1 if in battle or edit cancelled.
*/
s32 dbgMenuHeroPokemonAdd(void) {
    if (fightIsFight() == 1) return -1;
    
    if (firstFlag) {
        pokemonInit(pokemon);
        firstFlag = 0;
    }
    
    s32 result = dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    if (result < 0) return -1;
    
    heroCatchPokemon(0, pokemon, 0, 4, 1);
    return -1;
}

/*
  Address: 0x8000AED4 | size: 0x6C
  dbgMenuHeroPokemonSelect5()
  Edits Pokemon slot 5 (index 4). Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect5(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 5);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}

/*
  Address: 0x8000AF40 | size: 0x6C
  dbgMenuHeroPokemonSelect4()
  Edits Pokemon slot 4 (index 3). Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect4(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 4);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}

/*
  Address: 0x8000AFAC | size: 0x6C
  dbgMenuHeroPokemonSelect3()
  Edits Pokemon slot 3 (index 2). Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect3(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 3);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}

/*
  Address: 0x8000B018 | size: 0x6C
  dbgMenuHeroPokemonSelect2()
  Edits Pokemon slot 2 (index 1). Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect2(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 2);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}

/*
  Address: 0x8000B084 | size: 0x6C
  dbgMenuHeroPokemonSelect1()
  Edits Pokemon slot 1 (index 0). Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect1(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 1);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}

/*
  Address: 0x8000B0F0 | size: 0x6C
  dbgMenuHeroPokemonSelect0()
  Edits Pokemon slot 0. Returns -1 if in battle or no Pokemon.
*/
s32 dbgMenuHeroPokemonSelect0(void) {
    if (fightIsFight() == 1) return -1;
    
    void* pokemon = heroGetStatus(0, 3, 0);
    if (pokemon == 0) return -1;
    
    dbgMenuPokemonEditSub(pokemon, 0, 0, 0, 0, 0);
    return 0;
}
