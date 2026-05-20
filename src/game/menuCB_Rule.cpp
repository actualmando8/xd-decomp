// Decompiled from: menuCB_Rule.cpp
// Address range: 0x8004B7B4..0x8004D394 | size: 0x1BE0

/* Forward declarations */
static s32 _menuCBRule_IsTamagoPokemon(Pokemon* pkmn);

/* Global data */
static u8 oreRule[0x90] = {
    0x00, 0x01, 0x00, 0x64, 0x02, 0x58, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
    0x01, 0x01, 0x00, 0x01, 0xFF, 0xC4, 0xFF, 0xEC,
    0x01, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00,
    // ... rest zeroed
};

static u8 staRule[0x1B0] = {
    // Rule 0 (0x000)
    0x00, 0x01, 0x00, 0x64, 0x02, 0x58, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x00, 0x01, 0x01, 0xFF, 0xC4, 0xFF, 0xEC,
    0x01, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00,
    // ... rest zeroed
    // Rule 1 (0x090)
    0x00, 0x01, 0x00, 0x32, 0x01, 0x2C, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x00, 0x01, 0xFF, 0xC4, 0xFF, 0xEC,
    0x01, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00,
    // ... rest zeroed
    // Rule 2 (0x120)
    0x00, 0x01, 0x00, 0x64, 0x02, 0x58, 0x00, 0x06,
    0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x01, 0x00, 0x01, 0xFF, 0xC4, 0xFF, 0xEC,
    0x01, 0x01, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00,
    // ... rest zeroed
};

static u8 ruleTempBuff[0x90];

/* External data */
extern u16 legendPokemonData[];
extern u32 legendPokemonData_number;
extern u16 itemtoolbattle[];
extern u32 itemtoolbattle_number;

/*
  Address: 0x8004B7B4 | size: 0x94
  menuCBRule_ErrorFlagSetOkPushTiming(Hero* hero)
*/
void menuCBRule_ErrorFlagSetOkPushTiming(Hero* hero) {
    void* rule = menuCBBios_CurrentRule();
    for (s32 i = 0; i < 6; i++) {
        s32 result = menuCBRule_CheckTrainerRegulation(hero, rule, 3);
        // Set error flag bits based on result
    }
}

/*
  Address: 0x8004B848 | size: 0x158
  menuCBRule_ErrorFlagSetItemGetTiming(Hero* hero, Pokemon* pkmn, s32 slot)
*/
void menuCBRule_ErrorFlagSetItemGetTiming(Hero* hero, Pokemon* pkmn, s32 slot) {
    void* rule = menuCBBios_CurrentRule();
    u16 itemId = pokemonBiosGetItemDataId(pkmn);
    
    s32 result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 2);
    if (result == 0) {
        s32 ruleType = *(s32*)((u8*)rule + 8);
        if (ruleType >= 0 && ruleType < 3) {
            // Set regulation flag
        } else if (ruleType == 1) {
            // Set specific flag
        }
    }
    
    menuCBRule_CheckPokemonError(pkmn, 3);
}

/*
  Address: 0x8004B9A0 | size: 0x200
  menuCBRule_ErrorFlagSetPokemonGetTiming(Hero* hero, Pokemon* pkmn, s32 slot)
*/
void menuCBRule_ErrorFlagSetPokemonGetTiming(Hero* hero, Pokemon* pkmn, s32 slot) {
    void* rule = menuCBBios_CurrentRule();
    
    s32 result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 0);
    // Set error flags based on regulation check
    
    result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 1);
    // Set error flags
    
    menuCBRule_CheckPokemonError(pkmn, 0);
    menuCBRule_CheckPokemonError(pkmn, 1);
    menuCBRule_CheckPokemonError(pkmn, 2);
    menuCBRule_CheckPokemonError(pkmn, 5);
    
    s32 trainerResult = menuCBRule_CheckTrainerRegulation(hero, rule, 0);
    menuCBRule_CheckLegendPokemon(pkmn, rule);
    menuCBRule_CheckTrainerRegulationAt(hero, pkmn, rule, 1);
}

/*
  Address: 0x8004BBA0 | size: 0x70
  menuCBRule_CheckLegendPokemon(Pokemon* pkmn, void* rule)
*/
s32 menuCBRule_CheckLegendPokemon(Pokemon* pkmn, void* rule) {
    u8 flag = *(u8*)((u8*)rule + 0x18);
    if (flag == 1) return 1;
    
    u16 species = pokemonBiosGetPokemonDataId(pkmn);
    for (u32 i = 0; i < legendPokemonData_number; i++) {
        if (legendPokemonData[i] == species) {
            return 0;
        }
    }
    return 1;
}

/*
  Address: 0x8004BC10 | size: 0x340
  menuCBRule_ErrorFlagSet(Hero* hero, s32 slot)
*/
void menuCBRule_ErrorFlagSet(Hero* hero, s32 slot) {
    void* rule = menuCBBios_CurrentRule();
    
    for (s32 i = 0; i < 6; i++) {
        Pokemon* pkmn = heroBiosGetPokemonPtr(hero, i);
        u16 itemId = pokemonBiosGetItemDataId(pkmn);
        toolBattleRuleErrorFlagClear(hero, i);
        
        s32 result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 0);
        // Set error flags
        
        result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 1);
        // Set error flags
        
        result = menuCBRule_CheckPokemonRegulation(pkmn, rule, 2);
        if (result == 0) {
            s32 ruleType = *(s32*)((u8*)rule + 8);
            if (ruleType >= 0 && ruleType < 3) {
                // Set regulation flag
            } else if (ruleType == 1) {
                // Set specific flag
            }
        }
        
        menuCBRule_CheckPokemonError(pkmn, 0);
        menuCBRule_CheckPokemonError(pkmn, 1);
        menuCBRule_CheckPokemonError(pkmn, 2);
        menuCBRule_CheckPokemonError(pkmn, 3);
        menuCBRule_CheckPokemonError(pkmn, 5);
        
        s32 trainerResult = menuCBRule_CheckTrainerRegulation(hero, rule, 0);
        menuCBRule_CheckTrainerRegulationAt(hero, pkmn, rule, 1);
        menuCBRule_CheckTrainerRegulationAt(hero, pkmn, rule, 2);
        menuCBRule_CheckTrainerRegulation(hero, rule, 3);
        menuCBRule_CheckLegendPokemon(pkmn, rule);
    }
}

/*
  Address: 0x8004BF50 | size: 0x68
  menuCBRule_CheckPokemonEventFlag(Pokemon* pkmn)
*/
s32 menuCBRule_CheckPokemonEventFlag(Pokemon* pkmn) {
    u16 species = pokemonBiosGetPokemonDataId(pkmn);
    if (species == 0x97 || species == 0x19A) {
        // Celebi or Jirachi
        if (pokemonBiosGetEventGetFlag(pkmn) != 0) {
            return 1;
        }
        return 0;
    }
    return 1;
}

/*
  Address: 0x8004BFB8 | size: 0x88
  menuCBRule_CheckErrorAll(Hero* hero)
*/
s32 menuCBRule_CheckErrorAll(Hero* hero) {
    if (menuCBRule_CheckTrainerErrorAll(hero) != 0) {
        for (s32 i = 0; i < 6; i++) {
            Pokemon* pkmn = heroBiosGetPokemonPtr(hero, i);
            if (menuCBRule_CheckPokemonErrorAll(pkmn) != 0) {
                return 1;
            }
        }
        return 1;
    }
    return 0;
}

/*
  Address: 0x8004C040 | size: 0x68
  menuCBRule_CheckTrainerErrorAll(Hero* hero)
*/
s32 menuCBRule_CheckTrainerErrorAll(Hero* hero) {
    for (s32 i = 0; i >= 0; i--) {
        if (menuCBRule_CheckTrainerError(hero, i) != 0) {
            return 1;
        }
    }
    return 1;
}

/*
  Address: 0x8004C0A8 | size: 0x8
  menuCBRule_CheckTrainerError(Hero* hero, s32 slot)
*/
s32 menuCBRule_CheckTrainerError(Hero* hero, s32 slot) {
    return 0;
}

/*
  Address: 0x8004C0B0 | size: 0x64
  menuCBRule_CheckPokemonErrorAll(Pokemon* pkmn)
*/
s32 menuCBRule_CheckPokemonErrorAll(Pokemon* pkmn) {
    for (s32 i = 0; i < 6; i++) {
        if (menuCBRule_CheckPokemonError(pkmn, i) != 0) {
            return 1;
        }
    }
    return 1;
}

/*
  Address: 0x8004C114 | size: 0x35C
  menuCBRule_CheckPokemonError(Pokemon* pkmn, s32 checkType)
*/
s32 menuCBRule_CheckPokemonError(Pokemon* pkmn, s32 checkType) {
    if (menuCBRule_IsBlankPokemon(pkmn)) return 1;
    
    switch (checkType) {
        case 0: {
            // Check stats vs reset basis
            if (menuCBRule_CheckPokemonError(pkmn, 2) != 0) return 1;
            if (menuCBRule_CheckPokemonEventFlag(pkmn) != 0) return 0;
            
            Pokemon tempPkmn;
            pokemonBiosCopy(&tempPkmn, pkmn);
            pokemonResetBasisStatus(&tempPkmn);
            
            u16 origMaxHp = pokemonBiosGetMaxHp(pkmn);
            u16 resetMaxHp = pokemonBiosGetMaxHp(&tempPkmn);
            if (resetMaxHp < origMaxHp) return 0;
            
            u16 origAtk = pokemonBiosGetPhyAtk(pkmn);
            u16 resetAtk = pokemonBiosGetPhyAtk(&tempPkmn);
            if (resetAtk < origAtk) return 0;
            
            // ... check all stats
            u16 totalEffort = pokemonBiosGetMaxHpEffort(pkmn)
                + pokemonBiosGetPhyAtkEffort(pkmn)
                + pokemonBiosGetPhyDefEffort(pkmn)
                + pokemonBiosGetSpeAtkEffort(pkmn)
                + pokemonBiosGetSpeDefEffort(pkmn)
                + pokemonBiosGetNimblenessEffort(pkmn);
            if (totalEffort > 0x1FE) return 0;
            
            // Check individual effort values <= 0xFF
            return 1;
        }
        case 1: return pokemonIsDarkPokemon(pkmn);
        case 2: return pokemonBiosGetTamagoFlag(pkmn);
        case 3: return menuCBRule_CheckValidItem(pkmn);
        case 4: {
            // Check moves
            for (s32 i = 0; i < 4; i++) {
                u16 status = pokemonGetStatus(pkmn, i, 0, 0x7F);
                if (status != 0) {
                    void* move1 = wazaDataBiosGetPtr(status);
                    void* move2 = wazaDataBiosGetPtr(status);
                    if (move1 == move2) return 0;
                }
            }
            return 1;
        }
        case 5: {
            u16 status = pokemonGetStatus(pkmn, 0, 0x6E, 0);
            return pokemonCheckValid(pkmn);
        }
        default: return 0;
    }
}

/*
  Address: 0x8004C470 | size: 0xD0
  menuCBRule_CheckRegulationAll(Hero* hero, void* rule)
*/
s32 menuCBRule_CheckRegulationAll(Hero* hero, void* rule) {
    if (menuCBRule_CheckTrainerRegulationAll(hero, rule) != 0) {
        s32 count = 0;
        for (s32 i = 0; i < 6; i++) {
            Pokemon* pkmn = heroBiosGetPokemonPtr(hero, i);
            if (pkmn == NULL) continue;
            if (!pokemonCheckValid(pkmn)) continue;
            
            if (menuCBRule_CheckPokemonRegulationAll(pkmn, rule) != 0) {
                if (menuCBRule_CheckLegendPokemon(pkmn, rule) != 0) {
                    count++;
                }
            }
        }
        // Check if count is even
        return ((-count) & count) >> 31;
    }
    return 0;
}

/*
  Address: 0x8004C540 | size: 0x74
  menuCBRule_CheckTrainerRegulationAll(Hero* hero, void* rule)
*/
s32 menuCBRule_CheckTrainerRegulationAll(Hero* hero, void* rule) {
    for (s32 i = 0; i < 4; i++) {
        if (menuCBRule_CheckTrainerRegulation(hero, rule, i) != 0) {
            return 1;
        }
    }
    return 1;
}

/*
  Address: 0x8004C5B4 | size: 0x240
  menuCBRule_CheckTrainerRegulationAt(Hero* hero, Pokemon* pkmn, void* rule, s32 checkType)
*/
s32 menuCBRule_CheckTrainerRegulationAt(Hero* hero, Pokemon* pkmn, void* rule, s32 checkType) {
    switch (checkType) {
        case 0: return menuCBRule_CheckTrainerRegulation(hero, rule, 0);
        case 1: {
            if (*(u8*)((u8*)rule + 0xC) != 0) return 1;
            if (menuCBRule_IsBlankPokemon(pkmn)) return 1;
            if (_menuCBRule_IsTamagoPokemon(pkmn)) return 1;
            
            for (s32 i = 0; i < 6; i++) {
                Pokemon* other = heroBiosGetPokemonPtr(hero, i);
                if (other == pkmn) continue;
                if (menuCBRule_IsBlankPokemon(other)) continue;
                if (_menuCBRule_IsTamagoPokemon(other)) continue;
                
                if (pokemonBiosGetPokemonDataId(pkmn) == pokemonBiosGetPokemonDataId(other)) {
                    return 0;
                }
            }
            return 1;
        }
        case 2: {
            if (*(u8*)((u8*)rule + 0xD) != 0) return 1;
            if (menuCBRule_IsBlankPokemon(pkmn)) return 1;
            if (_menuCBRule_IsTamagoPokemon(pkmn)) return 1;
            if (pokemonBiosGetItemDataId(pkmn) == 0) return 1;
            
            for (s32 i = 0; i < 6; i++) {
                Pokemon* other = heroBiosGetPokemonPtr(hero, i);
                if (other == pkmn) continue;
                if (menuCBRule_IsBlankPokemon(other)) continue;
                if (_menuCBRule_IsTamagoPokemon(other)) continue;
                
                if (pokemonBiosGetItemDataId(pkmn) == pokemonBiosGetItemDataId(other)) {
                    return 0;
                }
            }
            return 1;
        }
        case 4: {
            s32 result = menuCBRule_CheckTrainerRegulation(hero, rule, 3);
            if (result != 0) {
                if (!menuCBRule_IsBlankPokemon(pkmn)) {
                    return 1;
                }
            }
            return result;
        }
        default: return 0;
    }
}

/*
  Address: 0x8004C7F4 | size: 0x250
  menuCBRule_CheckTrainerRegulation(Hero* hero, void* rule, s32 checkType)
*/
s32 menuCBRule_CheckTrainerRegulation(Hero* hero, void* rule, s32 checkType) {
    s32 totalLevel = 0;
    s32 hasItem = 1;
    s32 hasSpecies = 1;
    s32 count = 0;
    
    for (s32 i = 0; i < 6; i++) {
        Pokemon* pkmn = heroBiosGetPokemonPtr(hero, i);
        if (menuCBRule_IsBlankPokemon(pkmn)) continue;
        if (_menuCBRule_IsTamagoPokemon(pkmn)) continue;
        
        totalLevel += pokemonBiosGetLevel(pkmn);
        
        for (s32 j = i + 1; j < 6; j++) {
            Pokemon* other = heroBiosGetPokemonPtr(hero, j);
            if (menuCBRule_IsBlankPokemon(other)) continue;
            if (_menuCBRule_IsTamagoPokemon(other)) continue;
            
            u16 item1 = pokemonBiosGetItemDataId(pkmn);
            u16 item2 = pokemonBiosGetItemDataId(other);
            if (item1 != 0 && item2 != 0) {
                hasItem &= (item1 != item2);
            }
            
            hasSpecies &= (pokemonBiosGetPokemonDataId(pkmn) != pokemonBiosGetPokemonDataId(other));
        }
    }
    
    switch (checkType) {
        case 0: return totalLevel >= *(u16*)((u8*)rule);
        case 1: return hasSpecies;
        case 2: return hasItem;
        case 3: {
            count = 0;
            for (s32 i = 0; i < 6; i++) {
                Pokemon* pkmn = heroBiosGetPokemonPtr(hero, i);
                if (!menuCBRule_IsBlankPokemon(pkmn)) count++;
            }
            return count >= *(u16*)((u8*)rule + 0x1A);
        }
        case 4: return count >= *(u16*)((u8*)rule + 0x1C);
        default: return 0;
    }
}

/*
  Address: 0x8004CA44 | size: 0x74
  menuCBRule_CheckPokemonRegulationAll(Pokemon* pkmn, void* rule)
*/
s32 menuCBRule_CheckPokemonRegulationAll(Pokemon* pkmn, void* rule) {
    for (s32 i = 0; i < 3; i++) {
        if (menuCBRule_CheckPokemonRegulation(pkmn, rule, i) != 0) {
            return 1;
        }
    }
    return 1;
}

/*
  Address: 0x8004CAB8 | size: 0xD8
  menuCBRule_CheckPokemonRegulation(Pokemon* pkmn, void* rule, s32 checkType)
*/
s32 menuCBRule_CheckPokemonRegulation(Pokemon* pkmn, void* rule, s32 checkType) {
    if (menuCBRule_IsBlankPokemon(pkmn)) return 1;
    
    switch (checkType) {
        case 0: return pokemonBiosGetLevel(pkmn) >= *(u16*)rule;
        case 1: return pokemonBiosGetLevel(pkmn) <= *(u16*)((u8*)rule + 2);
        case 2: return menuCBRule_CheckRegulationItem(pkmn, rule);
        case 3: return 1;
        default: return 0;
    }
}

/*
  Address: 0x8004CB90 | size: 0x68
  menuCBRule_CheckHero(Hero* hero)
*/
s32 menuCBRule_CheckHero(Hero* hero) {
    s32 hasError = menuCBRule_CheckErrorAll(hero);
    if (hasError != 0) {
        void* rule = menuCBBios_CurrentRule();
        if (menuCBRule_CheckRegulationAll(hero, rule) != 0) {
            return 1;
        }
    }
    return 0;
}

/*
  Address: 0x8004CBF8 | size: 0x7C
  _menuCBRule_IsTamagoPokemon(Pokemon* pkmn)
*/
static s32 _menuCBRule_IsTamagoPokemon(Pokemon* pkmn) {
    if (menuCBRule_IsBlankPokemon(pkmn)) return 0;
    if (pokemonBiosGetTamagoFlag(pkmn)) return 1;
    if (!pokemonCheckValid(pkmn)) return 1;
    return 0;
}

/*
  Address: 0x8004CC74 | size: 0x3C
  menuCB_OreRule()
*/
void* menuCB_OreRule(void) {
    if (menuCBBios_CurrentlyWorkingToolBattle() != 0) {
        return NULL;
    }
    return oreRule;
}

/*
  Address: 0x8004CCB0 | size: 0x50
  menuCBRule_IsBlankPokemon(Pokemon* pkmn)
*/
s32 menuCBRule_IsBlankPokemon(Pokemon* pkmn) {
    if (pkmn == NULL) return 1;
    u16 status = pokemonGetStatus(pkmn, 0, 0x6E, 0);
    return (status == 0);
}

/*
  Address: 0x8004CD00 | size: 0x24
  menuCBRule_EnableSkill_SonicBoom()
*/
s32 menuCBRule_EnableSkill_SonicBoom(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0x13);
}

/*
  Address: 0x8004CD24 | size: 0x24
  menuCBRule_EnableSkill_Michidure()
*/
s32 menuCBRule_EnableSkill_Michidure(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0x12);
}

/*
  Address: 0x8004CD48 | size: 0x24
  menuCBRule_ProhibitionSuicide()
*/
s32 menuCBRule_ProhibitionSuicide(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0x11);
}

/*
  Address: 0x8004CD6C | size: 0x24
  menuCBRule_EnableSkillSwap()
*/
s32 menuCBRule_EnableSkillSwap(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0x10);
}

/*
  Address: 0x8004CD90 | size: 0x24
  menuCBRule_EnableSbToIceed()
*/
s32 menuCBRule_EnableSbToIceed(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0xF);
}

/*
  Address: 0x8004CDB4 | size: 0x24
  menuCBRule_EnableSbToSleep()
*/
s32 menuCBRule_EnableSbToSleep(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0xE);
}

/*
  Address: 0x8004CDD8 | size: 0x24
  menuCBRule_DEOKISISUCamouflage()
*/
s32 menuCBRule_DEOKISISUCamouflage(void) {
    return *(u8*)((u8*)menuCBBios_CurrentRule() + 0x19);
}

/*
  Address: 0x8004CDFC | size: 0x24
  menuCBRule_GetCommandTimeLimit()
*/
u16 menuCBRule_GetCommandTimeLimit(void) {
    return *(u16*)((u8*)menuCBBios_CurrentRule() + 0x16);
}

/*
  Address: 0x8004CE20 | size: 0x28
  menuCBRule_GetBattleTimeLimit()
*/
u16 menuCBRule_GetBattleTimeLimit(void) {
    return *(u16*)((u8*)menuCBBios_CurrentRule() + 0x14) * 0x3C;
}

/*
  Address: 0x8004CE48 | size: 0x4C
  menuCBRule_CheckValidItem(u16 itemId)
*/
s32 menuCBRule_CheckValidItem(u16 itemId) {
    if (itemId == 0xAF) return 0;
    if (itemId == 0) return 1;
    if (itemId >= 0xAF) return itemDataCheckValid(itemId);
    return itemDataCheckValid(itemId);
}

/*
  Address: 0x8004CE94 | size: 0xEC
  menuCBRule_CheckRegulationItem(Pokemon* pkmn, void* rule)
*/
s32 menuCBRule_CheckRegulationItem(Pokemon* pkmn, void* rule) {
    if (!menuCBRule_CheckValidItem(pkmn)) return 0;
    
    s32 ruleType = *(s32*)((u8*)rule + 8);
    if (ruleType == 0) {
        return 1;
    } else if (ruleType >= 1 && ruleType < 3) {
        return menuCBRule_RegulationItems();
    } else if (ruleType == 1) {
        return (pokemonBiosGetPokemonDataId(pkmn) == 0);
    }
    
    s32 count = menuCBRule_RegulationItems();
    for (s32 i = 0; i < count; i++) {
        if (itemtoolbattle[i] == pkmn) {
            return *(u8*)((u8*)rule + 0x52 + i);
        }
    }
    return 1;
}

/*
  Address: 0x8004CF80 | size: 0x54
  menuCBRule_RegulationItemID(s32 index)
*/
u16 menuCBRule_RegulationItemID(s32 index) {
    if (index < 0 || index >= menuCBRule_RegulationItems()) {
        return 0;
    }
    return itemtoolbattle[index];
}

/*
  Address: 0x8004CFD4 | size: 0xC
  menuCBRule_RegulationItems()
*/
s32 menuCBRule_RegulationItems(void) {
    return itemtoolbattle_number - 1;
}

/*
  Address: 0x8004CFE0 | size: 0xD4
  menuCBRule_ParticipationPokemonMax2()
*/
s32 menuCBRule_ParticipationPokemonMax2(void) {
    s32 ruleType = *(_CB + 0xC);
    
    switch (ruleType) {
        case 0: {
            u16 flag = *(u16*)(_CB - 0x66CC);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x66CE);
        }
        case 1: {
            u16 flag = *(u16*)(_CB - 0x663C);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x663E);
        }
        case 2: {
            u16 flag = *(u16*)(_CB - 0x65AC);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x65AE);
        }
        case 3: {
            u16 flag = *(u16*)(_CB - 0x651C);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x651E);
        }
        case 4: {
            u16 flag = *(u16*)(_CB - 0x648C);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x648E);
        }
        case 5: {
            u16 flag = *(u16*)(_CB - 0x63FC);
            if (flag != 0) return 6;
            return *(u16*)(_CB - 0x63FE);
        }
        default: return 6;
    }
}

/*
  Address: 0x8004D0B4 | size: 0x20
  menuCBRule_ParticipationPokemonMax()
*/
s32 menuCBRule_ParticipationPokemonMax(void) {
    return menuCBRule_ParticipationPokemonMax2();
}

/*
  Address: 0x8004D0D4 | size: 0x240
  menuCBRule_ConstantRule2(s32 ruleType)
*/
void* menuCBRule_ConstantRule2(s32 ruleType) {
    s32 ruleIdx;
    if (ruleType >= 0 && ruleType < 3) ruleIdx = ruleType;
    else if (ruleType >= 3 && ruleType < 6) ruleIdx = 2;
    else ruleIdx = 0;
    
    memset(ruleTempBuff, 0, 0x90);
    memcpy(ruleTempBuff, staRule + ruleIdx * 0x90, 0x90);
    
    if (ruleType >= 3 && ruleType < 6) {
        *(u16*)(ruleTempBuff + 0x1A) = 4;
        *(u16*)(ruleTempBuff + 0x1C) = 0;
    }
    
    if (ruleType != 0) {
        for (s32 i = 0; i < itemtoolbattle_number; i++) {
            u16 itemId = menuCBRule_RegulationItemID(i);
            if (itemId == 0xBF) {
                *(u8*)(ruleTempBuff + 0x52 + i) = 1;
            }
        }
    }
    
    // Copy message strings
    char* msg = NULL;
    if (ruleType == 3) {
        msg = GSmsgGetGSchar(0x438A);
    } else if (ruleType == 4) {
        msg = GSmsgGetGSchar(0x438B);
    } else if (ruleType >= 5 && ruleType < 6) {
        msg = GSmsgGetGSchar(0x438C);
    }
    
    // Copy message characters to ruleTempBuff + 0x1E
    u8* dst = ruleTempBuff + 0x1E;
    for (s32 i = 0; i < 7; i++) {
        if (msg != NULL) {
            u16 ch = *(u16*)msg;
            if (ch == 0xFFFF) {
                msg += 4;
            }
            *(u16*)dst = ch;
            if (ch != 0) {
                msg += 2;
            }
        } else {
            *(u16*)dst = 0;
        }
        dst += 2;
        
        if (msg != NULL) {
            u16 ch = *(u16*)msg;
            if (ch == 0xFFFF) {
                msg += 4;
            }
            *(u16*)dst = ch;
            if (ch != 0) {
                msg += 2;
            }
        } else {
            *(u16*)dst = 0;
        }
        dst += 2;
        
        if (msg != NULL) {
            u16 ch = *(u16*)msg;
            if (ch == 0xFFFF) {
                msg += 4;
            }
            *(u16*)dst = ch;
            if (ch != 0) {
                msg += 2;
            }
        } else {
            *(u16*)dst = 0;
        }
    }
    
    return ruleTempBuff;
}

/*
  Address: 0x8004D314 | size: 0x30
  menuCBRule_ConstantRule(s32 ruleType)
*/
void* menuCBRule_ConstantRule(s32 ruleType) {
    if (ruleType >= 0 && ruleType < 3) {
        return staRule + ruleType * 0x90;
    }
    return NULL;
}

/*
  Address: 0x8004D344 | size: 0x24
  menuCBRule_Copy(void* dst, void* src)
*/
void menuCBRule_Copy(void* dst, void* src) {
    memcpy(dst, src, 0x90);
}

/*
  Address: 0x8004D368 | size: 0x2C
  menuCBRule_IsEquals(void* rule1, void* rule2)
*/
s32 menuCBRule_IsEquals(void* rule1, void* rule2) {
    return memcmp(rule1, rule2, 0x90) == 0;
}
