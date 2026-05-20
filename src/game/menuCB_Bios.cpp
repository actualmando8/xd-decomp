// Decompiled from: menuCB_Bios.cpp
// Address range: 0x800477F8..0x80049DA4 | size: 0x25AC

/* Forward declarations */
static void _menuCBBios_RecoverAllPokemons(Hero* hero);
static void menuCBBios_InitContextAtFirst(_MENUCBWORK* work, _TOOL_SAVEDATA* save);

/* Global variables */
static u32 toolbattle_mode_flag;
static u32 staControlerMap[4];
static u16 sta$2095[4];
static _MENUCBWORK* pGCB;

/*
  Address: 0x800477F8 | size: 0x8
  menuCB_SetToolBattleModeFlag(u32 mode)
*/
void menuCB_SetToolBattleModeFlag(u32 mode) {
    toolbattle_mode_flag = mode;
}

/*
  Address: 0x80047800 | size: 0x8
  menuCB_GetToolBattleModeFlag()
*/
u32 menuCB_GetToolBattleModeFlag(void) {
    return toolbattle_mode_flag;
}

/*
  Address: 0x80047808 | size: 0x14
  menuCB_GetBattleController2P()
*/
u32 menuCB_GetBattleController2P(void) {
    return *_CB - 0x4F20;
}

/*
  Address: 0x8004781C | size: 0x1C
  menuCB_RuleTitleNameGet(s32 ruleType)
*/
void* menuCB_RuleTitleNameGet(s32 ruleType) {
    return (void*)_CB + ruleType * 0x90 - 0x66CA;
}

/*
  Address: 0x80047838 | size: 0x8
  menuCBTrainerBios_GetPlayerID(void* trainer)
*/
u16 menuCBTrainerBios_GetPlayerID(void* trainer) {
    return *(u16*)trainer;
}

/*
  Address: 0x80047840 | size: 0x8
  menuCBTrainerBios_SetHomePlace(void* trainer, u32 homePlace)
*/
void menuCBTrainerBios_SetHomePlace(void* trainer, u32 homePlace) {
    *(u32*)((u8*)trainer + 4) = homePlace;
}

/*
  Address: 0x80047848 | size: 0x8
  menuCBTrainerBios_GetHomePlace(void* trainer)
*/
u32 menuCBTrainerBios_GetHomePlace(void* trainer) {
    return *(u32*)((u8*)trainer + 4);
}

/*
  Address: 0x80047850 | size: 0x24
  menuCBBios_CopyTrainer(void* dest, void* src)
*/
void menuCBBios_CopyTrainer(void* dest, void* src) {
    memcpy(dest, src, 0x1320);
}

/*
  Address: 0x80047874 | size: 0x8
  menuCBTrainerBios_GetControlerID(void* trainer)
*/
u32 menuCBTrainerBios_GetControlerID(void* trainer) {
    return *(u32*)((u8*)trainer + 0x24);
}

/*
  Address: 0x8004787C | size: 0x8
  menuCBTrainerBios_SetControlerID(void* trainer, u32 id)
*/
void menuCBTrainerBios_SetControlerID(void* trainer, u32 id) {
    *(u32*)((u8*)trainer + 0x24) = id;
}

/*
  Address: 0x80047884 | size: 0x13C
  menuCBBios_InitVersusTrainer(void* trainer, void* hero)
  Initializes a versus trainer based on hero data.
*/
void menuCBBios_InitVersusTrainer(void* trainer, void* hero) {
    s32 homePlace = heroBiosGetHomePlace(hero);
    s32 sex = heroBiosGetSexDataId(hero);
    s32 trainerId;
    
    if (homePlace == 2) {
        // Orre Colosseum
        if (sex == 0) trainerId = 0x138B;
        else if (sex == 1) trainerId = 0x138C;
        else trainerId = 0;
    } else if (homePlace >= 1 && homePlace < 4) {
        // Saffron, Vermilion, Celadon
        if (sex == 0) trainerId = 0x138D;
        else if (sex == 1) trainerId = 0x138E;
        else trainerId = 0;
    } else if (homePlace == 0) {
        // Default
        if (sex == 0) trainerId = 0x1389;
        else if (sex == 1) trainerId = 0x138A;
        else trainerId = 0;
    } else {
        trainerId = 0x1388;
    }
    
    menuCBBios_InitTrainerFromHero(trainer, hero, trainerId);
}

/*
  Address: 0x800479C0 | size: 0x80
  menuCBBios_InitTrainerFromHero(void* trainer, Hero* hero, s32 trainerId)
*/
void menuCBBios_InitTrainerFromHero(void* trainer, Hero* hero, s32 trainerId) {
    Hero localHero;
    heroBiosCopy(&localHero, hero);
    heroBiosSetHizukiFlag(&localHero, 0);
    _menuCBBios_RecoverAllPokemons(&localHero);
    menuCBBios_ClearTrainer(trainer);
    heroBiosCopy((void*)((u8*)trainer + 0x2C), &localHero);
    heroBiosCopy((void*)((u8*)trainer + 0x9A4), &localHero);
    *(u16*)trainer = trainerId;
    *(u32*)((u8*)trainer + 4) = menuCBBios_FightTrainerDataIDToHomePlace(trainerId);
}

/*
  Address: 0x80047A40 | size: 0xAC
  menuCBBios_InitTrainerFromDataID(void* trainer, s32 dataId, s32 controllerId)
*/
void menuCBBios_InitTrainerFromDataID(void* trainer, s32 dataId, s32 controllerId) {
    Hero localHero;
    heroBiosCopy(&localHero, (void*)((u8*)trainer + 0x9A4));
    u32 ctrlId = menuCBBios_PortIDtoControlerID(0);
    fightTrainerCreateFightTrainerDataIdToHero(&localHero, trainer, ctrlId, controllerId);
    heroBiosSetHizukiFlag(&localHero, 0);
    _menuCBBios_RecoverAllPokemons(&localHero);
    menuCBBios_ClearTrainer(trainer);
    heroBiosCopy((void*)((u8*)trainer + 0x2C), &localHero);
    heroBiosCopy((void*)((u8*)trainer + 0x9A4), &localHero);
    *(u16*)trainer = *(u16*)((u8*)trainer + 0x2C);
    *(u32*)((u8*)trainer + 4) = menuCBBios_FightTrainerDataIDToHomePlace(*(u16*)trainer);
}

/*
  Address: 0x80047AEC | size: 0x3C
  menuCBBios_ClearTrainer(void* trainer)
*/
void menuCBBios_ClearTrainer(void* trainer) {
    u16 playerId = menuCBTrainerBios_GetPlayerID(trainer);
    menuCBBios_InitTrainer(trainer, playerId);
}

/*
  Address: 0x80047B28 | size: 0x44
  menuCBBios_InitTrainer(void* trainer, u16 playerId)
*/
void menuCBBios_InitTrainer(void* trainer, u16 playerId) {
    memset(trainer, 0, 0x1320);
    *(u16*)trainer = playerId;
}

/*
  Address: 0x80047B6C | size: 0x6C
  menuCBBios_FightTrainerDataIDToHomePlace(u16 trainerId)
*/
u32 menuCBBios_FightTrainerDataIDToHomePlace(u16 trainerId) {
    if (trainerId == 0x1388) return 0;
    if (trainerId >= 0x1389 && trainerId <= 0x138A) return 0;
    if (trainerId >= 0x138B && trainerId <= 0x138C) return 2;
    if (trainerId >= 0x138D && trainerId <= 0x138E) return 1;
    if (trainerId >= 1 && trainerId < 6) return 1;
    return 0;
}

/*
  Address: 0x80047BD8 | size: 0x90
  menuCBBios_GetTrainerFromVersusBattleID(u32 id, s32 index)
*/
void* menuCBBios_GetTrainerFromVersusBattleID(u32 id, s32 index) {
    u32 battleType = *(_CB + 8);
    
    if (battleType <= 2 && battleType >= 0) {
        if (index >= 0 && index <= 1) {
            return (void*)_CB + index * 0x1320 + 0x18;
        }
    } else {
        for (s32 i = 0; i < 4; i++) {
            if (*(_CB + 0x40 + i * 0x1320) == id) {
                return (void*)_CB + i * 0x1320 + 0x18;
            }
        }
    }
    return NULL;
}

/*
  Address: 0x80047C68 | size: 0x8
  menuCBBios_GetToolBattleTrainerKind()
*/
s32 menuCBBios_GetToolBattleTrainerKind(void) {
    return 0;
}

/*
  Address: 0x80047C70 | size: 0x8
  menuCBBios_GetRegisteredHero()
*/
s32 menuCBBios_GetRegisteredHero(void) {
    return 0;
}

/*
  Address: 0x80047C78 | size: 0x44
  menuCBBios_GetTrainer(s32 portId)
*/
void* menuCBBios_GetTrainer(s32 portId) {
    s32 idx = menuCBBios_ControlerIDtoPortID(portId);
    if (idx < 0) return NULL;
    return (void*)_CB + idx * 0x1320 + 0x18;
}

/*
  Address: 0x80047CBC | size: 0x30
  menuCBBios_GetTrainerOrgImmediately(s32 index)
*/
void* menuCBBios_GetTrainerOrgImmediately(s32 index) {
    if (index < 0 || index >= 4) return NULL;
    return (void*)_CB + index * 0x1320 + 0x4C98;
}

/*
  Address: 0x80047CEC | size: 0x30
  menuCBBios_GetTrainerImmediately(s32 index)
*/
void* menuCBBios_GetTrainerImmediately(s32 index) {
    if (index < 0 || index >= 4) return NULL;
    return (void*)_CB + index * 0x1320 + 0x18;
}

/*
  Address: 0x80047D1C | size: 0x30
  menuCBBios_GetHeroImmediately(s32 index)
*/
void* menuCBBios_GetHeroImmediately(s32 index) {
    if (index < 0 || index >= 4) return NULL;
    return (void*)_CB + index * 0x1320 + 0x44;
}

/*
  Address: 0x80047D4C | size: 0x78
  _menuCBBios_RecoverAllPokemons(Hero* hero)
  Recovers all fainted Pokemon for a Hero.
*/
static void _menuCBBios_RecoverAllPokemons(Hero* hero) {
    for (s32 i = 0; i < 6; i++) {
        void* pkmn = heroBiosGetPokemonPtr(hero, i);
        if (!menuCBRule_IsBlankPokemon(pkmn)) {
            pokemonAllKaihuku(pkmn);
        }
    }
}

/*
  Address: 0x80047DC4 | size: 0x6C
  menuCBBios_ControlerIDtoPortID(u32 controllerId)
*/
s32 menuCBBios_ControlerIDtoPortID(u32 controllerId) {
    for (s32 i = 0; i < 4; i++) {
        if (staControlerMap[i] == controllerId) {
            return i;
        }
    }
    return -1;
}

/*
  Address: 0x80047E30 | size: 0x14
  menuCBBios_PortIDtoControlerID(s32 portId)
*/
u32 menuCBBios_PortIDtoControlerID(s32 portId) {
    return staControlerMap[portId];
}

/*
  Address: 0x80047E44 | size: 0x20
  menuCBBios_ParticipationPokemonMax()
*/
s32 menuCBBios_ParticipationPokemonMax(void) {
    return menuCBRule_ParticipationPokemonMax();
}

/*
  Address: 0x80047E64 | size: 0x10
  menuCBBios_CurrentRuleType()
*/
s32 menuCBBios_CurrentRuleType(void) {
    return *(_CB + 0xC);
}

/*
  Address: 0x80047E74 | size: 0x78
  menuCBBios_CurrentRule()
*/
void* menuCBBios_CurrentRule(void) {
    void* rule = menuCB_OreRule();
    if (rule != NULL) return rule;
    
    s32 ruleType = menuCBBios_CurrentRuleType();
    void* constantRule = menuCBRule_ConstantRule2(ruleType);
    
    if (ruleType >= 0 && ruleType < 3 && constantRule != NULL) {
        return constantRule;
    }
    
    return menuCBBios_GetRule(ruleType);
}

/*
  Address: 0x80047EEC | size: 0x34
  menuCBBios_GetRule(s32 ruleType)
*/
void* menuCBBios_GetRule(s32 ruleType) {
    if (ruleType < 0 || ruleType >= 6) return NULL;
    return (void*)_CB + ruleType * 0x90 - 0x66E8;
}

/*
  Address: 0x80047F20 | size: 0x500
  menuCBBios_RuleConstRuleSet()
  Copies constant rules to save data status.
*/
void menuCBBios_RuleConstRuleSet(void) {
    void* status = savedataGetStatus(0, 0xE);
    if (status == NULL) return;
    
    // Copy rule 0
    void* rule = menuCBRule_ConstantRule(0);
    memcpy(status, rule, 0x90);
    
    // Copy rule 1
    rule = menuCBRule_ConstantRule(1);
    memcpy((u8*)status + 0x90, rule, 0x90);
    
    // Copy rule 2
    rule = menuCBRule_ConstantRule(2);
    memcpy((u8*)status + 0x120, rule, 0x90);
    
    // Copy rule 3
    rule = menuCBRule_ConstantRule(3);
    memcpy((u8*)status + 0x1B0, rule, 0x90);
    
    // Copy rule 4
    rule = menuCBRule_ConstantRule(4);
    memcpy((u8*)status + 0x240, rule, 0x90);
    
    // Copy rule 5
    rule = menuCBRule_ConstantRule(5);
    memcpy((u8*)status + 0x2D0, rule, 0x90);
}

/*
  Address: 0x80048420 | size: 0x94
  menuCBBios_RuleEditSaveON(void* status, s32 on)
*/
void menuCBBios_RuleEditSaveON(void* status, s32 on) {
    void* saveStatus = savedataGetStatus(0, 0xE);
    if (saveStatus == NULL) return;
    
    if (on == 1) {
        *(u16*)((u8*)saveStatus + 0x50) = 0x9124;
        *(u16*)((u8*)saveStatus + 0xE0) = 0xA2D4;
        *(u16*)((u8*)saveStatus + 0x170) = 0xB51C;
        *(u16*)((u8*)saveStatus + 0x200) = 0x47FD;
        *(u16*)((u8*)saveStatus + 0x290) = 0x7422;
        *(u16*)((u8*)saveStatus + 0x320) = 0x5633;
    } else {
        *(u16*)((u8*)saveStatus + 0x320) = 0;
        *(u16*)((u8*)saveStatus + 0x290) = 0;
        *(u16*)((u8*)saveStatus + 0x200) = 0;
        *(u16*)((u8*)saveStatus + 0x170) = 0;
        *(u16*)((u8*)saveStatus + 0xE0) = 0;
        *(u16*)((u8*)saveStatus + 0x50) = 0;
    }
}

/*
  Address: 0x800484B4 | size: 0x38
  menuCBBios_CurrentlyWorkingToolBattleSet(s32 value)
*/
void menuCBBios_CurrentlyWorkingToolBattleSet(s32 value) {
    void* status = savedataGetStatus(0, 0xE);
    if (status != NULL) {
        *(u8*)((u8*)status + 0x360) = value;
    }
}

/*
  Address: 0x800484EC | size: 0x3C
  menuCBBios_CurrentlyWorkingToolBattle()
*/
s32 menuCBBios_CurrentlyWorkingToolBattle(void) {
    void* status = savedataGetStatus(0, 0xE);
    if (status == NULL) return 0;
    return *(u8*)((u8*)status + 0x360);
}

/*
  Address: 0x80048528 | size: 0xC
  menuCBBios_WorkContext()
*/
_MENUCBWORK* menuCBBios_WorkContext(void) {
    return _CB;
}

/*
  Address: 0x80048534 | size: 0xEC
  menuCBBios_InitContext(_MENUCBWORK* work)
*/
void menuCBBios_InitContext(_MENUCBWORK* work) {
    pGCB = _CB;
    
    if (!menuCBBios_ContextIsLocked()) {
        for (s32 i = 0; i < 4; i++) {
            u16 dataId = sta$2095[i];
            menuCBBios_InitTrainerFromDataID((void*)((u8*)_CB + 0x18 + i * 0x1320), dataId, 0);
            menuCBTrainerBios_SetControlerID(
                (void*)((u8*)_CB + 0x18 + i * 0x1320),
                menuCBBios_PortIDtoControlerID(i)
            );
            *(u16*)((u8*)_CB + 0x1A + i * 0x1320) = i;
            menuCBBios_CopyTrainer((void*)((u8*)_CB + 0x4C98 + i * 0x1320), (void*)((u8*)_CB + 0x18 + i * 0x1320));
        }
        
        if (*(u32*)((u8*)work + 4) == 1) {
            menuCB_InitMenu(0xA4);
            *(u32*)((u8*)work + 0x14) = 0;
        } else {
            menuCB_InitMenu(0xA9);
            *(u32*)((u8*)work + 0x14) = 4;
        }
    }
    
    menuCBBios_UnlockContext();
}

/*
  Address: 0x80048620 | size: 0xCE8
  menuCB_RULE_INIT(_TOOL_SAVEDATA* saveData)
  Initializes rules from save data.
*/
void menuCB_RULE_INIT(_TOOL_SAVEDATA* saveData) {
    // Check magic numbers
    if (*(u16*)((u8*)saveData + 0x50) == 0x9124 &&
        *(u16*)((u8*)saveData + 0xE0) == 0xA2D4 &&
        *(u16*)((u8*)saveData + 0x170) == 0xB51C &&
        *(u16*)((u8*)saveData + 0x200) == 0x47FD &&
        *(u16*)((u8*)saveData + 0x290) == 0x7422 &&
        *(u16*)((u8*)saveData + 0x320) == 0x5633) {
        menuCBBios_RuleConstRuleSet();
        return;
    }
    
    // Initialize from default rules
    memset(saveData, 0, 0x364);
    
    // Copy rules 0-5
    for (s32 i = 0; i < 6; i++) {
        void* rule = menuCBRule_ConstantRule(i);
        memcpy((u8*)saveData + i * 0x90, rule, 0x90);
    }
    
    // Set tool battle items
    for (s32 i = 0; i < itemtoolbattle_number; i++) {
        s32 itemId = menuCBRule_RegulationItemID(i);
        if (itemId == 0xBF) {
            *(u8*)((u8*)saveData + i * 0x90 + 0xE2) = 1;
            *(u8*)((u8*)saveData + i * 0x90 + 0x172) = 1;
            *(u8*)((u8*)saveData + i * 0x90 + 0x202) = 1;
            *(u8*)((u8*)saveData + i * 0x90 + 0x292) = 1;
            *(u8*)((u8*)saveData + i * 0x90 + 0x322) = 1;
        }
    }
    
    // Copy message strings
    char* msg = GSmsgGetGSchar(0x438A);
    for (s32 i = 0; i < 7; i++) {
        // Parse and copy message data
    }
    
    msg = GSmsgGetGSchar(0x438B);
    for (s32 i = 0; i < 7; i++) {
        // Parse and copy message data
    }
    
    msg = GSmsgGetGSchar(0x438C);
    for (s32 i = 0; i < 7; i++) {
        // Parse and copy message data
    }
    
    menuCBBios_InitContextAtFirst(_CB, saveData);
    *(u8*)((u8*)saveData + 0x360) = 0;
}

/*
  Address: 0x80049308 | size: 0xA7C
  menuCBBios_InitContextAtFirst(_MENUCBWORK* work, _TOOL_SAVEDATA* saveData)
*/
static void menuCBBios_InitContextAtFirst(_MENUCBWORK* work, _TOOL_SAVEDATA* saveData) {
    menuCBBios_UnlockContext();
    memset(work, 0, 0xB5F4);
    
    // Copy rules from save data to work context
    for (s32 i = 0; i < 6; i++) {
        memcpy((u8*)work + 0x1 - 0x66E8 + i * 0x90, (u8*)saveData + i * 0x90, 0x90);
    }
    
    menuCBBios_LockContext();
}
