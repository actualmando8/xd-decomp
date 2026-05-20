// Decompiled from: menuCB_Battle.cpp
// Address range: 0x8004D394..0x8004DB44 | size: 0x7B0

/* Forward declarations */
void    GSflagOff(s32 flag);
s32     soundGetBGMID(void);
void    soundStop(s32 bgmId);
void    menuTitleBattleSelectFree(void);
void    menuCB_SetToolBattleModeFlag(s32 mode);
s32     fightEncount(s32 encountId);
void    menuTitleReadWazaSelectMenu(void);
s32     HSD_Rand(void);
void*   fightEncountDataBiosGetPtr(s32 id);
void    fightEncountDataBiosSetBgmSndId(void* data, s32 bgmId);
void    fightEncountDataBiosSetFightFloorDataId(void* data, s32 floorId);
void    fightEncountDataBiosSetFightKind(void* data, s32 kind);
void    fightEncountDataBiosSetSyoukaiWzxDataId(void* data, s32 id);
void    fightEncountDataBiosSetFightType(void* data, s32 type);
void    fightEncountDataBiosSetFightTrainerDataId(void* data, s32 slot, s32 id);
void    fightEncountDataBiosSetGSInputDevice(void* data, s32 slot, s32 device);
void    menuCBBios_InitTrainerFromDataID(void* trainer, s32 dataId, s32 a, s32 b);
s32     menuCBBios_PortIDtoControlerID(s32 portId);
void    fightTrainerCreateFightTrainerDataIdToHero(s32 dataId, void* hero, s32 a, s32 b);
void    heroBiosSetNamePtr(void* hero, const void* name);
void    menuCBBios_InitTrainerFromHero(void* trainer, void* hero, s32 size);
void    menuCBTrainerBios_SetControlerID(void* trainer, s32 ctrlId);
void    menuCBTrainerBios_SetHomePlace(void* trainer, s32 homePlace);
void    menuCBBios_CopyTrainer(void* dest, void* src);
void*   GSmsgGetGSchar(const char* str);

/* Data tables */
static const s32 VS_TRAINER_RANK_NUMBER[] = {
    0x00010002, 0x00030004, 0x00050006, 0x00070008,
    0x0009000A, 0x000B000C, 0x000D000E, 0x000F0010,
    0x00110012, 0x00130014, 0x00150016, 0x00170018,
    0x0019001A, 0x001B001C, 0x001D001E, 0x001F0020,
    0x00210022, 0x00230024, 0x00250026, 0x00270028,
};
static const s32 VS_TRAINER_RANK_SELECT_TBL[] = {
    0x051E2305, 0x1E1E0514, 0x19051414,
    0x050A0F05, 0x0A0A0500, 0x05050000,
};
static const s32 VS_TRAINER_RANK_ENCOUNT_DATA[] = {
    0x000F0010, 0x00110012, 0x00130014, 0x00150016,
    0x00170018, 0x0019001A, 0x001B001C, 0x001D001E,
    0x001F0020, 0x00210022, 0x00230024, 0x00250026,
    0x00270028, 0x0029002A, 0x002B002C, 0x002D002E,
    0x002F0030, 0x00310032, 0x00330034, 0x00350036,
};
static const s32 staBGM_imasugu[] = { 0x4F2, 0x4F2, 0x4F2 };
static const s32 staBGM_tunaide[] = { 0x4F3, 0x4F3, 0x4F3 };
static const s32 staColosseum[] = { 0x24, 0x26, 0x25, 0x3C, 0x3D, 0x3E };
static const s32 staColosseum_imasugu[] = { 0x24, 0x26, 0x25, 0x3C, 0x3D, 0x3E };
static const s8 staDefaultNameID[] = { ';', ';', ';', '!', ';', '"' };

/* External _CB struct */
extern s32 _CB[];

/*
  Address: 0x8004D394 | size: 0xC8
  menuCB_Battle(_MENUCBWORK* work)
  Entry point for battle. Sets up encounter based on battle mode and type.
*/
s32 menuCB_Battle(void* work) {
    s32* cb = &_CB[0];
    s32 encountId;
    
    if (cb[1] == 1) {
        // VS mode - use trainer rank
        s16 rank = ((s16*)work)[0x2654 / 2];
        encountId = ((s16*)VS_TRAINER_RANK_ENCOUNT_DATA)[rank];
    } else {
        s32 battleType = ((s32*)work)[8 / 4];
        if (battleType == 0) {
            encountId = 5;
        } else if (battleType == 1) {
            encountId = 7;
        } else if (battleType >= 2 && battleType < 3) {
            encountId = 8;
        } else {
            encountId = 0;
        }
    }
    
    GSflagOff(0x323);
    s32 bgmId = soundGetBGMID();
    soundStop(bgmId);
    menuTitleBattleSelectFree();
    
    menuCB_SetToolBattleModeFlag(1);
    s32 result = fightEncount(encountId);
    menuCB_SetToolBattleModeFlag(0);
    menuTitleReadWazaSelectMenu();
    
    return result;
}

/*
  Address: 0x8004D45C | size: 0x6E4
  menuCB_InitBattle(_MENUCBWORK* work)
  Initializes battle data including trainer data, BGM, floor data, and fight type.
  Large function with complex setup logic.
*/
s32 menuCB_InitBattle(void* work) {
    s32* cb = &_CB[0];
    s32* cbHigh = &_CB[0x1000];
    s32 rank = 0;
    
    // Read trainer rank from work struct
    s8 nameIdx = cbHigh[-0x4B5F / 4];
    
    if (nameIdx == -1) {
        // Random name selection
        s32 randVal = HSD_Rand();
        s32 idx = randVal % 6;
        nameIdx = staDefaultNameID[idx];
        cbHigh[-0x4B5F / 4] = nameIdx;
        
        // Copy name to work struct
        void* gsChar = GSmsgGetGSchar((const char*)&staDefaultNameID[nameIdx]);
        // ... name copy logic ...
    }
    
    // Determine encount ID based on battle mode
    if (cb[1] == 1) {
        s16 rankVal = ((s16*)work)[0x2654 / 2];
        rank = ((s16*)VS_TRAINER_RANK_NUMBER)[rankVal];
    } else {
        s32 battleType = ((s32*)work)[8 / 4];
        if (battleType == 0) {
            rank = 5;
        } else if (battleType == 1) {
            rank = 7;
        } else if (battleType >= 2 && battleType < 3) {
            rank = 8;
        }
    }
    
    // Get encounter data
    void* encountData = fightEncountDataBiosGetPtr(rank);
    
    // Increment counter
    cbHigh[-0x6384 / 4]++;
    
    // Calculate BGM ID using LCG
    s32 counter = cbHigh[-0x6384 / 4];
    counter = (counter * 0x5555) >> 16;
    counter = counter * 3 - counter;
    cbHigh[-0x6384 / 4] = counter;
    
    s32 bgmIdx = counter % 3;
    s32 bgmId;
    
    if (cb[1] == 1) {
        bgmId = staBGM_imasugu[bgmIdx];
    } else {
        bgmId = staBGM_tunaide[bgmIdx];
    }
    
    fightEncountDataBiosSetBgmSndId(encountData, bgmId);
    
    // Calculate floor data ID
    s32 floorIdx;
    if (cbHigh[-0x5004 / 4] == 6) {
        s32 randVal = HSD_Rand();
        floorIdx = randVal % 6;
    } else {
        s32 randVal = HSD_Rand();
        floorIdx = randVal % 6;
    }
    ((s32*)work)[0x10 / 4] = floorIdx;
    
    s32 floorId = staColosseum[floorIdx];
    fightEncountDataBiosSetFightFloorDataId(encountData, floorId);
    
    // Set fight kind
    s32 mode = ((s32*)work)[4 / 4];
    if (mode == 0) {
        fightEncountDataBiosSetFightKind(encountData, 0xB);
        fightEncountDataBiosSetSyoukaiWzxDataId(encountData, 0);
    } else {
        s32 extra = ((s32*)work)[0x502C / 4];
        if (extra == 0) {
            fightEncountDataBiosSetFightKind(encountData, 0x11);
        } else {
            fightEncountDataBiosSetFightKind(encountData, 0xA);
        }
        fightEncountDataBiosSetSyoukaiWzxDataId(encountData, 0);
    }
    
    // Set fight type
    if (mode == 0) {
        s32 battleType = ((s32*)work)[8 / 4];
        if (battleType == 1) {
            fightEncountDataBiosSetFightType(encountData, 0x18);
        } else if (battleType >= 2 && battleType < 3) {
            fightEncountDataBiosSetFightType(encountData, 0x24);
        } else {
            fightEncountDataBiosSetFightType(encountData, 0x17);
        }
    } else {
        fightEncountDataBiosSetFightType(encountData, 0x10);
    }
    
    // Initialize trainer data
    if (mode == 0) {
        s16 trainerDataId1 = ((s16*)work)[0x2654 / 2];
        s16 trainerDataId2 = ((s16*)work)[0x1334 / 2];
        
        s32 dataId1 = VS_TRAINER_RANK_NUMBER[trainerDataId1];
        s32 dataId2 = VS_TRAINER_RANK_NUMBER[trainerDataId2];
        
        menuCBBios_InitTrainerFromDataID((s16*)work + 0x1338 / 2, dataId1, rank, 0);
        ((s16*)work)[0x1338 / 2] = dataId1;
        
        // Set controller ID
        s32 ctrlId = menuCBBios_PortIDtoControlerID(0);
        menuCBTrainerBios_SetControlerID((s16*)work + 0x1338 / 2, ctrlId);
        
        // Delete items
        _menuCBBattle_DeleteAllItem__FP4Hero((s32*)work + 0x1364 / 4);
        _menuCBBattle_DeleteAllItem__FP4Hero((s32*)work + 0x1CDC / 4);
        
        // Create trainer hero
        fightTrainerCreateFightTrainerDataIdToHero(dataId2, (s32*)work + 8 / 4, ctrlId, 0);
        
        // Set name if needed
        if (cbHigh[-0x4F20 / 4] == 0) {
            heroBiosSetNamePtr((s32*)work + 8 / 4, (const void*)(cbHigh - 0x4B5E));
        }
        
        _menuCBBattle_DeleteAllItem__FP4Hero((s32*)work + 8 / 4);
        
        // Initialize from hero
        menuCBBios_InitTrainerFromHero((s32*)work + 0x18 / 4, (s32*)work + 8 / 4, 0x1388);
        
        if (cbHigh[-0x4F20 / 4] != 0) {
            ((s16*)work)[0x18 / 4] = dataId2;
        }
        
        menuCBTrainerBios_SetControlerID((s32*)work + 0x18 / 4, ctrlId);
        menuCBTrainerBios_SetHomePlace((s32*)work + 0x18 / 4, 0);
    } else if (mode >= 1) {
        // Copy trainer data for multi-player
        s32 srcIdx = ((s32*)work)[0x4CC0 / 4];
        menuCBBios_CopyTrainer((s32*)work + 0x18 / 4, (s32*)work + srcIdx * 0x1320 / 4 + 0x4C98 / 4);
        
        s32 srcIdx2 = ((s32*)work)[0x5FE0 / 4];
        menuCBBios_CopyTrainer((s32*)work + 0x1338 / 2, (s32*)work + srcIdx2 * 0x1320 / 4 + 0x4C98 / 4);
        
        s32 srcIdx3 = ((s32*)work)[0x7300 / 4];
        menuCBBios_CopyTrainer((s32*)work + 0x2658 / 2, (s32*)work + srcIdx3 * 0x1320 / 4 + 0x4C98 / 4);
        
        s32 srcIdx4 = cbHigh[-0x79E0 / 4];
        menuCBBios_CopyTrainer((s32*)work + 0x3978 / 2, (s32*)work + srcIdx4 * 0x1320 / 4 + 0x4C98 / 4);
    }
    
    // Set trainer data IDs
    if (mode >= 2) {
        fightEncountDataBiosSetFightTrainerDataId(encountData, 2, ((s16*)work)[0x2658 / 2]);
        fightEncountDataBiosSetFightTrainerDataId(encountData, 3, ((s16*)work)[0x3978 / 2]);
        fightEncountDataBiosSetGSInputDevice(encountData, 2, ((s32*)work)[0x267C / 4]);
        fightEncountDataBiosSetGSInputDevice(encountData, 3, ((s32*)work)[0x399C / 4]);
    }
    
    fightEncountDataBiosSetFightTrainerDataId(encountData, 0, ((s16*)work)[0x18 / 2]);
    fightEncountDataBiosSetFightTrainerDataId(encountData, 1, ((s16*)work)[0x1338 / 2]);
    fightEncountDataBiosSetGSInputDevice(encountData, 0, ((s32*)work)[0x3C / 4]);
    fightEncountDataBiosSetGSInputDevice(encountData, 1, ((s32*)work)[0x135C / 4]);
    
    return 0;
}

/*
  Address: 0x8004DB40 | size: 0x4
  _menuCBBattle_DeleteAllItem__FP4Hero(Hero* hero)
  Stub - deletes all items from hero.
*/
void _menuCBBattle_DeleteAllItem__FP4Hero(void* hero) {
    // Stub - actual implementation elsewhere
}
