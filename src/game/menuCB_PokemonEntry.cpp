// Decompiled from: menuCB_PokemonEntry.cpp
// Address range: 0x8004A0A8..0x8004B7B4 | size: 0x170C

/* Forward declarations */
void*   pokemonGetStatus(void* pokemon, s32 a, s16 b, s32 c);
s32     pokemon_GetSeikaku(void* pokemon);
s32     pokemonAdjustValueBySeikaku(s32 seikaku, s32 val, s32 a);
void    pokemonBiosSetPhyAtk(void* pokemon, s16 val);
void    pokemonBiosSetPhyDef(void* pokemon, s16 val);
void    pokemonBiosSetSpeAtk(void* pokemon, s16 val);
void    pokemonBiosSetSpeDef(void* pokemon, s16 val);
void    pokemonBiosSetNimbleness(void* pokemon, s16 val);
s32     menuCBRule_DEOKISISUCamouflage(s32 a);
s32     menuGBACGetRomVer(s32 a);
void    soundOpenPlay(s32 a, s32 b, s32 c, s32 d);
void    gba_SIProbe_ErrorCntClear(s32 a);
void    menuCB_SE_Play(s32 a);
void    menuOpen(s32 a, s32 b);
s32     windowGetActiveID(void);
void    menuOpenCustom(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void    menuCloseCustom(s32 a, s32 b, s32 c);
void    toolentryTaisenInitPokemonOrder(s32 a);
s32     toolentryTaisenGetBattleType(void);
s32     toolentryTaisenGetBattleVersus(void);
s32     toolentryTaisenEntryPokemon(s32 a);
void*   menuCBBios_GetTrainerImmediately(s32 a);
void*   heroBiosGetPokemonPtr(void* hero, s32 a);
s32     toolentryTaisenGetEntryPlayerNum(void);
void    toolentryTaisenGetHomePlace(s32 a);
s32     _menuCBPokemonEntryGetEntryFlag(s32 player);
s32     toolentryTaisenGetControlerType(s32 a);
void*   menuCBBios_GetTrainer(s32 a);
s32     gbaCommandIsConnected(s32 a);
void    toolentryTaisengetEtnryPokemonOrderNum(s32 a);
s32     _menuCBPokemonEntryPokemonNum(s32 a);
s32     GSinputButtonsChanged(s32 a);
s32     GSinputButtonsPressed(s32 a);
s32     toolentryTaisenGetBattlePlayerID(s32 a);
s32     pauseIsPause(void);
void    GSsndPlay(s32 a, s32 b, s32 c);
s32     gbaCommandEntryResult(s32 a, void* out);
void*   menuCBBios_GetTrainerFromVersusBattleID(s32 a);
s32     menuCBBios_ParticipationPokemonMax(void);
s32     toolentryTaisenGetPokemonNum(s32 a);
s32     menuCBTrainerBios_GetControlerID(void* trainer);
void*   menuCBBios_GetHeroImmediately(s32 a);
void    gbaCommandSendWazaText(s32 a, void* hero);
void    gbaCommandEntryRequest(s32 a, s32 b, s32 c);
void    toolentryTaisenSetEtnryPokemonOrder(s32 a, s32 b);
s32     toolentryTaisenDeleteEtnryPokemonOrder(s32 a);
s32     toolentryTaisenGetEntryPokemonNum(s32 a);
void    windowGetKeyInfo(void);
void    windowSearchID(s32 a);
s32     gbaCommandEntryPokemon(s32 a, void* out);
void    toolentryTaisenSetEtnryPokemonOrderGBA(s32 a, s32 b, void* data);
void    menuFaceLoad_Tool(s32 a, void* callback, s32 c);
s32     menuCBBattleStartGetStatus(void);
void*   toolentryTaisenGetPokemonPtr(s32 a, s32 b);
void*   toolentryTaisenGetEntryPokemonPtr(s32 a, s32 b);
s32     menuFaceGetID2(void* pokemon, s32 a);
void    menuFaceDispFromID(s32 a, s32 b, s32 c, s16 faceId);

/* External data */
extern s32 _CB[];
extern s32 _menuCBBattleStartWork[];
extern s32 pGCB;

/* BSS data */
static s32 _menuCBPokemonWork[0x234 / 4];
s16 uToolPokemon_faceId;

/* Data tables */
static const s32 _GBA_DeokisisuParamTable[] = {
    0x96, 0x32, 0x96, 0x32,
    0x96, 0xB4, 0x14, 0xB4,
    0x14, 0x96, 0x46, 0xA0,
    0x46, 0xA0, 0x5A, 0x5F,
    0x5A, 0x5F, 0x5A, 0xB4,
};
static const f32 float_0 = 0.0f;
static const f64 double_4503601774854144 = 4503601774854144.0;

/*
  Address: 0x8004A0A8 | size: 0x394
  _menuCB_DeoxysParamCustom__FP7PokemonUs(Pokemon* pokemon, u16 work)
  Customizes Deoxys params based on form selection.
*/
void _menuCB_DeoxysParamCustom__FP7PokemonUs(void* pokemon, u16 work) {
    // Get base stats
    s32 hp = pokemonGetStatus(pokemon, 0, 0x7A, 0);
    s32 seikaku = pokemon_GetSeikaku(pokemon);
    s32 atk = pokemonGetStatus(pokemon, 0, 0x94, 0);
    s32 def = pokemonGetStatus(pokemon, 0, 0x95, 0);
    s32 spa = pokemonGetStatus(pokemon, 0, 0x96, 0);
    s32 spd = pokemonGetStatus(pokemon, 0, 0x97, 0);
    s32 spe = pokemonGetStatus(pokemon, 0, 0x98, 0);
    s32 phyAtk = pokemonGetStatus(pokemon, 0, 0x8E, 0);
    s32 phyDef = pokemonGetStatus(pokemon, 0, 0x8F, 0);
    s32 speAtk = pokemonGetStatus(pokemon, 0, 0x90, 0);
    s32 speDef = pokemonGetStatus(pokemon, 0, 0x91, 0);
    s32 nimbleness = pokemonGetStatus(pokemon, 0, 0x92, 0);
    
    // Get Deoxys form selection
    s32 form = _menuCB_pokemonGetDeoxysSel__FUsb(work, 0);
    
    // Calculate new stats based on form
    s32 param0 = _GBA_DeokisisuParamTable[form * 5 + 0];
    s32 newPhyAtk = ((phyAtk >> 2) * param0 + atk * hp) >> 5;
    newPhyAtk = (newPhyAtk + (newPhyAtk >> 31)) + 5;
    
    s32 param1 = _GBA_DeokisisuParamTable[form * 5 + 1];
    s32 newPhyDef = ((phyDef >> 2) * param1 + def * hp) >> 5;
    newPhyDef = (newPhyDef + (newPhyDef >> 31)) + 5;
    
    s32 param2 = _GBA_DeokisisuParamTable[form * 5 + 2];
    s32 newSpeAtk = ((speAtk >> 2) * param2 + spa * hp) >> 5;
    newSpeAtk = (newSpeAtk + (newSpeAtk >> 31)) + 5;
    
    s32 param3 = _GBA_DeokisisuParamTable[form * 5 + 3];
    s32 newSpeDef = ((speDef >> 2) * param3 + spd * hp) >> 5;
    newSpeDef = (newSpeDef + (newSpeDef >> 31)) + 5;
    
    s32 param4 = _GBA_DeokisisuParamTable[form * 5 + 4];
    s32 newNimbleness = ((nimbleness >> 2) * param4 + spe * hp) >> 5;
    newNimbleness = (newNimbleness + (newNimbleness >> 31)) + 5;
    
    // Apply nature adjustments
    newPhyAtk = pokemonAdjustValueBySeikaku(seikaku, newPhyAtk, 0x88);
    newPhyDef = pokemonAdjustValueBySeikaku(seikaku, newPhyDef, 0x89);
    newSpeAtk = pokemonAdjustValueBySeikaku(seikaku, newSpeAtk, 0x8A);
    newSpeDef = pokemonAdjustValueBySeikaku(seikaku, newSpeDef, 0x8B);
    newNimbleness = pokemonAdjustValueBySeikaku(seikaku, newNimbleness, 0x8C);
    
    // Set new stats
    pokemonBiosSetPhyAtk(pokemon, newPhyAtk);
    pokemonBiosSetPhyDef(pokemon, newPhyDef);
    pokemonBiosSetSpeAtk(pokemon, newSpeAtk);
    pokemonBiosSetSpeDef(pokemon, newSpeDef);
    pokemonBiosSetNimbleness(pokemon, newNimbleness);
}

/*
  Address: 0x8004A43C | size: 0xEC
  _menuCB_pokemonGetDeoxysSel__FUsb(u16 work, bool a)
  Gets Deoxys form selection based on ROM version.
*/
s32 _menuCB_pokemonGetDeoxysSel__FUsb(u16 work, bool a) {
    s32* cb = &_CB[0];
    s32* cbHigh = &_CB[0x1000];
    s32 result = 0;
    
    if (cb[1] != 1) {
        s32 trainerIdx = ((s32*)cb)[0x3C / 4];
        result = trainerIdx - 1;
        
        s32 camouflage = menuCBRule_DEOKISISUCamouflage(result);
        if (camouflage != 0 && a == 0) {
            // Get ROM version and map to form
            s32 romVer = menuGBACGetRomVer(result);
            if (romVer == 1) result = 0;
            else if (romVer == 3) result = 1;
            else if (romVer == 4) result = 2;
            else if (romVer == 5) result = 3;
            else result = 0;
        }
    }
    
    return result;
}

/*
  Address: 0x8004A528 | size: 0x424
  menuCB_PokemonEntry(void)
  Main Pokemon entry function. Handles the entry flow for all players.
*/
s32 menuCB_PokemonEntry(void) {
    // Initialize
    _menuCBBattleStartWork[0x124 / 4] = 0x5DB;
    soundOpenPlay(0x5DB, 0, 0xFF, 0);
    _menuCBPokemonEntryWorkInit__Fv();
    gba_SIProbe_ErrorCntClear(-1);
    
    s32* cb = &_CB[0];
    s32* cbHigh = &_CB[0x1000];
    cbHigh[-0x4EFC / 4] = -1;
    cbHigh[-0x4EF8 / 4] = 0;
    ((s32*)cb)[-0x5020 / 4] = 0;
    cbHigh[-0x4FA0 / 4] = 0;
    cbHigh[-0x4EF0 / 4] = 2;
    cbHigh[-0x4E60 / 4] = 0;
    
    menuCB_SE_Play(0x14);
    menuOpen(0xC6, 0);
    menuOpen(0xC5, 0);
    
    s32* work = &_menuCBPokemonWork[0];
    s32 opened = 0;
    
    while (1) {
        // Main entry loop
        s32 state = cbHigh[-0x4EF8 / 4];
        if (state == 1) {
            if (opened == 0) {
                s32 activeWin = windowGetActiveID();
                menuOpenCustom(0xE2, activeWin, (s32)cb - 0x5020, 0, 0, 0);
                opened = 1;
            }
            
            if (cbHigh[-0x4FA0 / 4] != 0) {
                s32 entryFlag = ((s32*)cb)[-0x5020 / 4];
                if (entryFlag == 0) {
                    _menuCBPokemonEntrySetEntryFlag__Flb(0, 1);
                    cbHigh[-0x4EF8 / 4] = 2;
                } else {
                    toolentryTaisenInitPokemonOrder(0);
                    cbHigh[-0x4EF8 / 4] = 0;
                    menuCloseCustom(0xE2, 0, 0);
                    ((s32*)cb)[-0x5020 / 4] = 0;
                    cbHigh[-0x4FA0 / 4] = 0;
                    cbHigh[-0x4EF0 / 4] = 2;
                    opened = 0;
                }
            }
        }
        
        if (cbHigh[-0x4E60 / 4] == 1) {
            work[0x22C / 4] = 0;
        }
        
        s32 allEntry = _menuCBPokemonEntryAllPlayer__Fv();
        if (allEntry != 0) {
            cbHigh[-0x4EF8 / 4] = -1;
        }
        
        if (work[0x22C / 4] != 0) {
            cbHigh[-0x4EF8 / 4] = -1;
        }
        
        GSthreadSwitch();
        
        if (cbHigh[-0x4EF8 / 4] == -1) {
            break;
        }
    }
    
    // Cleanup
    if (work[0x22C / 4] == 0) {
        menuCB_SE_Play(0x15);
        menuCloseCustom(0xE2, 0, 0);
        menuCloseCustom(0xC5, 0, 0);
        menuCloseCustom(0xC6, 0, 1);
        menuCB_GBADisconnectedErrorJob();
        menuCBPokemonEntryPokemonFaceFree();
        menuCBBattleStartTrainerFaceFree();
        return 0xA9;
    }
    
    // Wait for entry to complete
    s32* cb2 = &_CB[0];
    while (1) {
        GSthreadSwitch();
        s32 total = 0;
        for (s32 i = 0; i < 4; i++) {
            s32* cbSlot = cb2 + i * 6;
            s32* cbSlot2 = cb2 + i * 12;
            if (cbSlotHigh[-0x4B78 / 4] == 1) {
                total += cbSlot2[-0x4BA8 / 4];
            }
        }
        if (total != 0) break;
    }
    
    GSthreadSwitch();
    GSthreadSwitch();
    GSthreadSwitch();
    
    // Entry Pokemon
    s32 battleType = toolentryTaisenGetBattleType();
    s32 battleVersus = toolentryTaisenGetBattleVersus();
    s32 maxPokemon;
    
    if (battleVersus == 4) {
        if (battleType >= 2) maxPokemon = 4;
        else if (battleType >= 0) maxPokemon = 2;
        else maxPokemon = 4;
    } else {
        if (battleType >= 2) maxPokemon = 1;
        else if (battleType >= 0) maxPokemon = 2;
        else maxPokemon = 1;
    }
    
    for (s32 i = 0; i < maxPokemon; i++) {
        toolentryTaisenEntryPokemon(i);
    }
    
    // Custom Deoxys params
    if (_CB[1] == 0) {
        for (s32 trainer = 0; trainer < maxPokemon; trainer++) {
            void* trainerData = menuCBBios_GetTrainerImmediately(trainer);
            for (s32 pokeIdx = 0; pokeIdx < 6; pokeIdx++) {
                void* pokemon = heroBiosGetPokemonPtr((s32*)trainerData + 0x2C, pokeIdx);
                s32 species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
                if (species == 0x19A) {
                    _menuCB_DeoxysParamCustom__FP7PokemonUs(pokemon, trainer);
                }
            }
        }
    }
    
    return 0xB1;
}

/*
  Address: 0x8004A94C | size: 0x1A8
  menuCBPokemonEntryButtonTask_20041006(void)
  Button task for Pokemon entry screen.
*/
void menuCBPokemonEntryButtonTask_20041006(void) {
    s32 playerNum = toolentryTaisenGetEntryPlayerNum();
    toolentryTaisenGetBattleType();
    toolentryTaisenGetHomePlace(0);
    toolentryTaisenGetHomePlace(1);
    toolentryTaisenGetHomePlace(2);
    toolentryTaisenGetHomePlace(3);
    
    s32* work = &_menuCBPokemonWork[0];
    s32 i = 0;
    
    while (i < playerNum) {
        s32 battleVersus = toolentryTaisenGetBattleVersus();
        if (battleVersus == 4 && _menuCBPokemonEntryGetEntryFlag__Fl(i) != 0) {
            s32 ctrlType = toolentryTaisenGetControlerType(i);
            void* trainer = menuCBBios_GetTrainer(i);
            s32 homePlace = ((s32*)trainer)[4 / 4];
            if (homePlace == 1 || homePlace == 2 || homePlace == 3) {
                s32 connected = gbaCommandIsConnected(ctrlType);
                if (connected == 0) {
                    work[0x230 / 4] = 0;
                    if (work[0x230 / 4] < 0) {
                        work[0x230 / 4] = ctrlType;
                    }
                }
            }
        }
        
        if (_menuCBPokemonEntryGetEntryFlag__Fl(i) == 0) {
            if (battleVersus == 4) {
                s32 ctrlType = toolentryTaisenGetControlerType(i);
                void* trainer = menuCBBios_GetTrainer(i);
                s32 homePlace = ((s32*)trainer)[4 / 4];
                if (homePlace == 1 || homePlace == 2 || homePlace == 3) {
                    _menuCBPokemonEntryEntCheckGBA__F13GSinputDevicel(ctrlType, i);
                } else {
                    _menuCBPokemonEntryEntCheck__F13GSinputDevicel(ctrlType, i);
                }
            } else {
                _menuCBPokemonEntryEntCheck__F13GSinputDevicel(ctrlType, i);
            }
            
            if (toolentryTaisenGetControlerType(i) == 1) {
                if (toolentryTaisenGetHomePlace(i) != 0) {
                    toolentryTaisengetEtnryPokemonOrderNum(i);
                    _menuCBPokemonEntryPokemonNum__Fl(i);
                }
            }
        }
        
        i++;
    }
}

/*
  Address: 0x8004AAF4 | size: 0x27C
  _menuCBPokemonEntryEntCheckGBA__F13GSinputDevicel(GSinputDevice ctrl, s32 player)
  Checks GBA entry results.
*/
void _menuCBPokemonEntryEntCheckGBA__F13GSinputDevicel(s32 ctrl, s32 player) {
    s32 battlePlayerId = toolentryTaisenGetBattlePlayerID(player);
    s32 result;
    gbaCommandEntryResult(ctrl, &result);
    
    // Handle result codes
    if (result == 0x100) {
        // Success - set entry order
        s32 orderNum = toolentryTaisengetEtnryPokemonOrderNum(player);
        s32 newOrder = toolentryTaisenSetEtnryPokemonOrder(player, orderNum);
        if (newOrder >= 0) {
            if (!pauseIsPause()) {
                GSsndPlay(0x19, 0, 0);
            }
            // Update display position
            // ... (floating point math for position)
            _menuCBPokemonEntryEntCheckDebug__Fl(player);
        }
    } else if (result == 0xFF00) {
        // Delete entry
        s32 orderNum = toolentryTaisengetEtnryPokemonOrderNum(player);
        s32 deleted = toolentryTaisenDeleteEtnryPokemonOrder(player);
        if (orderNum != deleted && !pauseIsPause()) {
            GSsndPlay(0x12, 0, 0);
        }
    } else if (result == 0) {
        // Pokemon entry
        s32 entryNum = toolentryTaisenGetEntryPokemonNum(player);
        u8 pokemonData[0x20];
        gbaCommandEntryPokemon(ctrl, pokemonData);
        if (entryNum > 0 && entryNum <= 8) {
            // Process Pokemon data
            toolentryTaisenSetEtnryPokemonOrderGBA(player, entryNum, pokemonData);
            _menuCBPokemonEntrySetEntryFlag__Flb(player, 1);
        }
    } else if (result == 0x300) {
        // Error handling
        _menuCBPokemonWork[0x22C / 4] = 0;
        if (_menuCBPokemonWork[0x230 / 4] < 0) {
            _menuCBPokemonWork[0x230 / 4] = player;
        }
    }
}

/*
  Address: 0x8004AD70 | size: 0x4
  _menuCBPokemonEntryEntCheckDebug__Fl(s32 player)
  Stub function for debug entry check.
*/
void _menuCBPokemonEntryEntCheckDebug__Fl(s32 player) {
    // Stub
}

/*
  Address: 0x8004AD74 | size: 0x294
  _menuCBPokemonEntryEntCheck__F13GSinputDevicel(GSinputDevice ctrl, s32 player)
  Checks button input for Pokemon entry.
*/
void _menuCBPokemonEntryEntCheck__F13GSinputDevicel(s32 ctrl, s32 player) {
    s32 buttonsChanged = GSinputButtonsChanged(ctrl);
    s32 buttonsPressed = GSinputButtonsPressed(ctrl);
    s32 pressed = buttonsPressed & buttonsChanged;
    toolentryTaisenGetBattlePlayerID(player);
    
    if (pauseIsPause()) return;
    if (windowGetKeyInfo() & (1 << 21)) return;
    if (windowSearchID(0xE2)) return;
    
    // Check for delete button (0x140)
    if (pressed & 0x140) {
        if (pressed & (1 << 25)) {
            // Delete entry
            s32 orderNum = toolentryTaisengetEtnryPokemonOrderNum(player);
            s32 deleted = toolentryTaisenDeleteEtnryPokemonOrder(player);
            if (orderNum != deleted) {
                GSsndPlay(0x12, 0, 0);
            }
        }
        if (pressed & (1 << 23)) {
            // Fill with empty slots
            void* trainer = menuCBBios_GetTrainerImmediately(player);
            s32 entryNum = toolentryTaisenGetEntryPokemonNum(player);
            s32 trainerPokemonNum = ((s32*)trainer)[0x20 / 4];
            s32 minNum = menuCBPokemonEntryPokemonNumMin(player);
            if (trainerPokemonNum >= minNum) {
                s32 slots = trainerPokemonNum - minNum;
                // Fill slots with 0xF
                // ...
                GSsndPlay(0x11, 0, 0);
            }
        }
        return;
    }
    
    // Check for entry buttons
    if (pressed & 0xC0F) {
        s32 pokemonIdx = _menuCBPokemonEntryButtonCheck__FUll(pressed, player);
        if (pokemonIdx >= 0) {
            s32 newOrder = toolentryTaisenSetEtnryPokemonOrder(player, pokemonIdx);
            if (newOrder >= 0) {
                GSsndPlay(0x19, 0, 0);
                // Update display position
                // ... (floating point math)
            }
        }
    }
}

/*
  Address: 0x8004B008 | size: 0xB4
  _menuCBPokemonEntryButtonCheck__FUll(u32 buttons, s32 player)
  Maps button presses to Pokemon indices.
*/
s32 _menuCBPokemonEntryButtonCheck__FUll(u32 buttons, s32 player) {
    s32 pokemonNum = toolentryTaisenGetPokemonNum(player);
    s32 result = -1;
    
    if (buttons & (1 << 31)) result = 0;
    if (buttons & (1 << 28)) result = 1;
    if (buttons & (1 << 20)) result = 2;
    if (buttons & (1 << 29)) result = 3;
    if (buttons & (1 << 30)) result = 4;
    if (buttons & (1 << 21)) result = 5;
    
    if (pokemonNum > result) {
        return -1;
    }
    return result;
}

/*
  Address: 0x8004B0BC | size: 0x90
  _menuCBPokemonEntryWork__Fv(void)
  Initializes Pokemon entry work data.
*/
void _menuCBPokemonEntryWork__Fv(void) {
    s32 trainerPtrs[4];
    for (s32 i = 0; i < 4; i++) {
        void* trainer = menuCBBios_GetTrainerFromVersusBattleID(i);
        trainerPtrs[i] = trainer;
        if (trainer) {
            _menuCBPokemonWork[i] = ((s8*)trainer)[0x28];
        } else {
            _menuCBPokemonWork[i] = -1;
        }
    }
}

/*
  Address: 0x8004B14C | size: 0x70
  menuCBPokemonEntryPokemonNumMin(s32 a)
  Gets minimum Pokemon number for entry.
*/
s32 menuCBPokemonEntryPokemonNumMin(s32 a) {
    s32* p = &pGCB;
    s32 idx = p[0xC / 4];
    s32* base = &p[idx * 0x90 + 0x1000];
    s16 val = base[-0x66CC / 4];
    s32 minNum = (val == 0) ? base[-0x66CE / 4] : 1;
    
    s32 entryNum = _menuCBPokemonEntryPokemonNum__Fl(a);
    return (entryNum >= minNum) ? entryNum : minNum;
}

/*
  Address: 0x8004B1BC | size: 0x54
  _menuCBPokemonEntryPokemonNum__Fl(s32 player)
  Gets Pokemon number for entry, clamped to max.
*/
s32 _menuCBPokemonEntryPokemonNum__Fl(s32 player) {
    s32 max = menuCBBios_ParticipationPokemonMax();
    s32 num = toolentryTaisenGetPokemonNum(player);
    return (num >= max) ? max : num;
}

/*
  Address: 0x8004B210 | size: 0x128
  _menuCBPokemonEntryWorkInit__Fv(void)
  Initializes Pokemon entry work.
*/
void _menuCBPokemonEntryWorkInit__Fv(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    s32 playerNum = toolentryTaisenGetEntryPlayerNum();
    
    _menuCBPokemonWork[0x22C / 4] = 1;
    _menuCBPokemonWork[0x230 / 4] = -1;
    _menuCBPokemonWork[0x220 / 4] = float_0;
    _menuCBPokemonWork[0x224 / 4] = 0;
    _menuCBPokemonWork[0x2C / 4] = 0;
    _menuCBPokemonWork[0x154 / 4] = 0;
    _menuCBPokemonWork[0x0 / 4] = 0;
    _menuCBPokemonWork[0xC / 4] = 0;
    
    for (s32 i = 0; i < playerNum; i++) {
        void* trainer = menuCBBios_GetTrainerImmediately(i);
        s32 ctrlId = menuCBTrainerBios_GetControlerID(trainer);
        void* hero = menuCBBios_GetHeroImmediately(i);
        _menuCBPokemonEntrySetEntryFlag__Flb(i, 0);
        
        s32 homePlace = ((s32*)trainer)[4 / 4];
        if (homePlace != 0) {
            gbaCommandSendWazaText(ctrlId, hero);
            s32 minPoke = (battleType == 1) ? 2 : 1;
            s32 minNum = menuCBPokemonEntryPokemonNumMin(i);
            s32 entryNum = _menuCBPokemonEntryPokemonNum__Fl(i);
            gbaCommandEntryRequest(ctrlId, minNum, minPoke);
        }
    }
    
    for (s32 i = 0; i < 4; i++) {
        toolentryTaisenInitPokemonOrder(i);
    }
    
    _menuCBPokemonEntryWork__Fv();
    _menuCBPokemonEntryDispPosition__Fv();
}

/*
  Address: 0x8004B338 | size: 0xC0
  menuCBPokemonEntryTexWorkInit(void)
  Initializes texture work data for Pokemon entry.
*/
void menuCBPokemonEntryTexWorkInit(void) {
    _menuCBPokemonWork[0x2C / 4] = 0;
    _menuCBPokemonWork[0x158 / 4] = 0;
    
    for (s32 i = 0; i < 2; i++) {
        s32* base = &_menuCBPokemonWork[0x30 / 4 + i * 0x48];
        for (s32 j = 0; j < 7; j++) {
            base[j * 0xC / 4 + 0] = 0;
            base[j * 0xC / 4 + 1] = 0;
        }
    }
}

/*
  Address: 0x8004B3F8 | size: 0x10
  menuCBPokemonEntryGetReadFlag(void)
  Gets read flag from work data.
*/
s32 menuCBPokemonEntryGetReadFlag(void) {
    return _menuCBPokemonWork[0x158 / 4];
}

/*
  Address: 0x8004B408 | size: 0x14
  _menuCBPokemonEntrySetEntryFlag__Flb(s32 player, bool flag)
  Sets entry flag for player.
*/
void _menuCBPokemonEntrySetEntryFlag__Flb(s32 player, bool flag) {
    _menuCBPokemonWork[player + 4 / 4] = flag;
}

/*
  Address: 0x8004B41C | size: 0x14
  _menuCBPokemonEntryGetEntryFlag__Fl(s32 player)
  Gets entry flag for player.
*/
s32 _menuCBPokemonEntryGetEntryFlag__Fl(s32 player) {
    return _menuCBPokemonWork[player + 4 / 4];
}

/*
  Address: 0x8004B430 | size: 0x70
  _menuCBPokemonEntryDispPosition__Fv(void)
  Sets display position based on battle type.
*/
void _menuCBPokemonEntryDispPosition__Fv(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    if (battleType == 0) {
        _menuCBPokemonWork[0x154 / 4] = 0x136;
    } else if (battleType == 2) {
        _menuCBPokemonWork[0x154 / 4] = 0;
    } else {
        _menuCBPokemonWork[0x154 / 4] = 0;
    }
}

/*
  Address: 0x8004B4A0 | size: 0xD0
  _menuCBPokemonEntryAllPlayer__Fv(void)
  Checks if all players have entered.
*/
s32 _menuCBPokemonEntryAllPlayer__Fv(void) {
    s32 battleVersus = toolentryTaisenGetBattleVersus();
    s32 battleType = toolentryTaisenGetBattleType();
    s32 maxPlayers;
    
    if (battleType == 0) {
        if (battleVersus == 4) {
            _menuCBPokemonWork[0x150 / 4] = 4;
            maxPlayers = 2;
        } else {
            _menuCBPokemonWork[0x150 / 4] = battleVersus;
            maxPlayers = 2;
        }
    } else if (battleType == 2) {
        _menuCBPokemonWork[0x150 / 4] = 4;
        maxPlayers = 4;
    } else {
        _menuCBPokemonWork[0x150 / 4] = 4;
        maxPlayers = 4;
    }
    
    s32 entered = 0;
    for (s32 i = 0; i < maxPlayers; i++) {
        if (_menuCBPokemonEntryGetEntryFlag__Fl(i) != 0) {
            entered++;
        }
    }
    
    return (entered == maxPlayers) ? 1 : 0;
}

/*
  Address: 0x8004B570 | size: 0x30
  menuCBPokemonEntryLoadTex(void)
  Loads textures for Pokemon entry screen.
*/
void menuCBPokemonEntryLoadTex(void) {
    menuFaceLoad_Tool(0, _menuCBPokemonEntryLoadCallBack__FPv, 0);
}

/*
  Address: 0x8004B5A0 | size: 0x16C
  _menuCBPokemonEntryLoadCallBack__FPv(void* data)
  Callback for loading Pokemon face textures.
*/
void _menuCBPokemonEntryLoadCallBack__FPv(void* data) {
    s32 playerNum = toolentryTaisenGetEntryPlayerNum();
    toolentryTaisenGetBattleType();
    
    if (data) {
        ((s8*)data)[0] = 1;
    }
    
    s32* work = &_menuCBPokemonWork[0];
    s32 done = 0;
    void* pokemon = data;
    
    while (1) {
        s32 counter = work[0x2C / 4];
        if (counter >= 0x18) {
            work[0x158 / 4] = 1;
            done = 1;
            pokemon = 0;
            break;
        }
        
        s32 player = ((counter * 0x2AAB) >> 16) * 6 - counter;
        s32 idx = counter;
        
        s32 status = menuCBBattleStartGetStatus();
        if (status == 0) {
            pokemon = toolentryTaisenGetPokemonPtr(player, idx);
        } else {
            s32 entryNum = toolentryTaisenGetEntryPokemonNum(player);
            if (entryNum > idx) {
                pokemon = toolentryTaisenGetEntryPokemonPtr(player, idx);
            } else {
                pokemon = 0;
            }
        }
        
        s32* faceBase = _menuCBPokemonEntryGetFaceBase__Fll(player, idx);
        s32 deoxysForm = _menuCB_pokemonGetDeoxysSel__FUsb(player, 1);
        s32 faceId = menuFaceGetID2(pokemon, deoxysForm);
        
        if (faceId != 0) {
            s32 species = pokemonGetStatus(pokemon, 0, 0x6E, 0);
            if (species != 0) {
                faceBase[0] = 1;
                faceBase[1] = faceId;
                uToolPokemon_faceId = faceId;
                work[0x2C / 4]++;
                break;
            }
        }
        
        faceBase[0] = 0;
        work[0x2C / 4]++;
    }
    
    if (done == 0) {
        // Continue loop
    }
}

/*
  Address: 0x8004B70C | size: 0x20
  _menuCBPokemonEntryGetFaceBase__Fll(s32 player, s32 idx)
  Gets base pointer for face data.
*/
s32* _menuCBPokemonEntryGetFaceBase__Fll(s32 player, s32 idx) {
    return (s32*)&_menuCBPokemonWork[player * 0x48 / 4 + idx * 0xC / 4 + 0x30 / 4];
}

/*
  Address: 0x8004B72C | size: 0x20
  menuCBPokemonEntryPokemonFaceFree(void)
  Frees Pokemon face textures.
*/
void menuCBPokemonEntryPokemonFaceFree(void) {
    menuCBPokemonEntryTexWorkInit();
}

/*
  Address: 0x8004B74C | size: 0x68
  menuCBPokemonEntryDispPokemonFace(s32 a, s32 b, s32 c, s32 d)
  Displays Pokemon face from ID.
*/
s32 menuCBPokemonEntryDispPokemonFace(s32 a, s32 b, s32 c, s32 d) {
    s32* faceBase = _menuCBPokemonEntryGetFaceBase__Fll(c, d);
    if (faceBase[0] != 0) {
        s16 faceId = faceBase[1];
        menuFaceDispFromID(a, b, c, faceId);
        return 1;
    }
    return 0;
}
