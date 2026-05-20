// Decompiled from: menuCB_BattleStart.cpp
// Address range: 0x80046D5C..0x800477F8 | size: 0xA9C

/* Forward declarations */
static void _menuCBBattleStartWorkInit(void);
static void _menuCBBattleStartSetIndex(void);
static void _menuCBBattleStartSetIndexSingle(s32 index, u16 num);
static void _menuCBBattleStartSetIndexDouble(s32 index, u16 num);
static void _menuCBBattleStartSetIndexMulti(s32 index, u16 num);
static void _menuCBBattleStartSetTrainerData(void);
static s32 _menuCBBattleCheckTrainer(s32 a, s32 b);
static s32 _menuCBBattleStartGetTrainerFaceSize(void);
static void _menuCBBattleStartDispTrainerTexCallBack(s32 id, void* data, s32 unused);

/* Global data */
extern void* _CB;
static u32 menuCBBattleStartDispWork[0x30];
static void* _menuCBBattleStartWork;
extern s32 menuCBBattleStartResID;

/* Static data tables */
static const s32 SingleOrder[6][5] = {
    {1, 2, 0, 3, 4},
    {2, 0, 1, 3, 4},
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
};

static const s32 DoubleOrder[6][5] = {
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
    {4, 0, 1, 5, 2},
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4},
};

/*
  Address: 0x80046D5C | size: 0x158
  _menuCBBattleStartSetIndex()
  Sets up the battle start index based on battle type.
*/
static void _menuCBBattleStartSetIndex(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    u16 nums[4];
    
    _menuCBBattleStartWorkInit();
    
    s32 mode = *((s32*)&_menuCBBattleStartWork + 1);
    
    if (mode == 0) {
        for (s32 i = 0; i < 4; i++) {
            nums[i] = toolentryTaisenGetPokemonNum(i);
        }
    } else if (mode == 1) {
        for (s32 i = 0; i < 4; i++) {
            nums[i] = toolentryTaisenGetEntryPokemonNum(i);
        }
    }
    
    if (battleType == 1) {
        for (s32 i = 0; i < 2; i++) {
            _menuCBBattleStartSetIndexDouble(i, nums[i]);
        }
    } else if (battleType >= 2 && battleType < 3) {
        for (s32 i = 0; i < 4; i++) {
            _menuCBBattleStartSetIndexMulti(i, nums[i]);
        }
    } else if (battleType == 0) {
        for (s32 i = 0; i < 2; i++) {
            _menuCBBattleStartSetIndexSingle(i, nums[i]);
        }
    }
}

/*
  Address: 0x80046EB4 | size: 0x8C
  _menuCBBattleStartSetIndexDouble(long index, unsigned short num)
  Sets index for double battle.
*/
static void _menuCBBattleStartSetIndexDouble(s32 index, u16 num) {
    s32* dest = &menuCBBattleStartDispWork[index * 6];
    s32 src[6];
    
    for (s32 i = 0; i < 6; i++) {
        src[i] = DoubleOrder[i][index];
    }
    
    if (num > 0) {
        s32 offset = (num - 1) * 6;
        for (s32 i = 0; i < 6; i++) {
            dest[i] = src[offset + i];
        }
    }
}

/*
  Address: 0x80046F40 | size: 0x8C
  _menuCBBattleStartSetIndexSingle(long index, unsigned short num)
  Sets index for single battle.
*/
static void _menuCBBattleStartSetIndexSingle(s32 index, u16 num) {
    s32* dest = &menuCBBattleStartDispWork[index * 6];
    s32 src[6];
    
    for (s32 i = 0; i < 6; i++) {
        src[i] = SingleOrder[i][index];
    }
    
    if (num > 0) {
        s32 offset = (num - 1) * 6;
        for (s32 i = 0; i < 6; i++) {
            dest[i] = src[offset + i];
        }
    }
}

/*
  Address: 0x80046FCC | size: 0x1B4
  _menuCBBattleStartSetIndexMulti(long index, unsigned short num)
  Sets index for multi battle.
*/
static void _menuCBBattleStartSetIndexMulti(s32 index, u16 num) {
    s32* dest = &menuCBBattleStartDispWork[index * 6];
    
    if (num <= 6) {
        for (s32 i = 0; i < num; i++) {
            dest[i] = i;
        }
        for (s32 i = num; i < 6; i++) {
            dest[i] = 0xFFFE;
        }
    } else if (num <= 8) {
        for (s32 i = 0; i < 6; i++) {
            dest[i] = i;
        }
        for (s32 i = 6; i < num; i++) {
            dest[i - 6] = i;
        }
    } else {
        s32 start = num - 6;
        for (s32 i = 0; i < 6; i++) {
            dest[i] = start + i;
        }
    }
}

/*
  Address: 0x80047180 | size: 0x90
  _menuCBBattleStartWorkInit()
  Initializes the battle start work buffer.
*/
static void _menuCBBattleStartWorkInit(void) {
    for (s32 i = 0; i < 4; i++) {
        menuCBBattleStartDispWork[i * 6 + 0] = 0;
        menuCBBattleStartDispWork[i * 6 + 1] = 1;
        menuCBBattleStartDispWork[i * 6 + 2] = 2;
        menuCBBattleStartDispWork[i * 6 + 3] = 3;
        menuCBBattleStartDispWork[i * 6 + 4] = 4;
        menuCBBattleStartDispWork[i * 6 + 5] = 5;
    }
}

/*
  Address: 0x80047210 | size: 0x3C
  menuCB_BattleStartSoundCheck()
  Checks if battle start sound is playing.
*/
s32 menuCB_BattleStartSoundCheck(void) {
    s32 status = GSsndGetStatus(*((s32*)&_menuCBBattleStartWork + 0x31));
    return (status == 2);
}

/*
  Address: 0x8004724C | size: 0x10
  menuCBBattleStartSetStatus(s32 status)
  Sets the battle start status.
*/
void menuCBBattleStartSetStatus(s32 status) {
    *((s32*)&_menuCBBattleStartWork + 1) = status;
}

/*
  Address: 0x8004725C | size: 0x10
  menuCBBattleStartGetStatus()
  Gets the battle start status.
*/
s32 menuCBBattleStartGetStatus(void) {
    return *((s32*)&_menuCBBattleStartWork + 1);
}

/*
  Address: 0x8004726C | size: 0xAC
  _menuCBBattleStartSetTrainerData()
  Sets up trainer data for battle.
*/
static void _menuCBBattleStartSetTrainerData(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    
    if (_menuCBBattleCheckTrainer(1, battleType)) {
        void* hero = toolentryTaisenGetHeroPtr(1);
        char* name = heroBiosGetNamePtr(hero);
        
        if (name) {
            GScharCpy((char*)&_menuCBBattleStartWork + 0x12C, name);
        } else {
            char* msgName = GSmsgGetGSchar(1);
            GScharCpy((char*)&_menuCBBattleStartWork + 0x12C, msgName);
        }
        
        s32 trainerId = toolentryTaisenGetTrainerDataID(1);
        trainerId = fightTrainerDB_GetKindDataId(trainerId);
        void* kindData = fightTrainerKindDataBiosGetPtr(trainerId);
        s32 prefixName = fightTrainerKindDataBiosGetPrefixName(kindData);
        *((s32*)&_menuCBBattleStartWork + 0x51) = prefixName;
    }
}

/*
  Address: 0x80047318 | size: 0x60
  _menuCBBattleCheckTrainer(long a, long b)
  Checks if trainer battle conditions are met.
*/
static s32 _menuCBBattleCheckTrainer(s32 a, s32 b) {
    s32 result = 1;
    s32 battleType = toolentryTaisenGetBattleType();
    
    if (b == 2) {
        if (battleType != 2) {
            result = 0;
        }
    } else {
        if (battleType == 2) {
            result = 0;
        }
    }
    
    return result;
}

/*
  Address: 0x80047378 | size: 0x144
  menuCBBattleStartInit(void* cb, s32 status)
  Initializes battle start sequence.
*/
void menuCBBattleStartInit(void* cb, s32 status) {
    _menuCBBattleStartSetTrainerData();
    _menuCBBattleStartWork = cb;
    *((s32*)&_menuCBBattleStartWork + 1) = status;
    _menuCBBattleStartSetIndex();
    
    if (status == 1) {
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        *((s32*)&_menuCBBattleStartWork + 0x31) = 0x5DB;
        soundOpenPlay(0x5DB, 0, 0xFF);
    } else {
        menuCBPokemonEntryTexWorkInit();
        menuCBPokemonEntryLoadTex();
        
        s32 randVal = HSD_Rand();
        s32 mod3 = (randVal * 0x55555556) >> 31;
        mod3 = (mod3 + randVal) * 3;
        mod3 = (randVal - mod3) % 3;
        
        switch (mod3) {
            case 0: *((s32*)&_menuCBBattleStartWork + 0x31) = 0x3D2; break;
            case 1: *((s32*)&_menuCBBattleStartWork + 0x31) = 0x3F5; break;
            case 2: *((s32*)&_menuCBBattleStartWork + 0x31) = 0x3F6; break;
            default: *((s32*)&_menuCBBattleStartWork + 0x31) = 0x3F7; break;
        }
        
        soundOpenPlay(*((s32*)&_menuCBBattleStartWork + 0x31), 0, 0xFF);
    }
}

/*
  Address: 0x800474BC | size: 0x8C
  menuCBBattleStartDispTrainerInit()
  Initializes trainer display data.
*/
void menuCBBattleStartDispTrainerInit(void) {
    *((u8*)&_menuCBBattleStartWork + 0x34) = 0;
    *((s32*)&_menuCBBattleStartWork + 0xB) = 0;
    
    s32 size = _menuCBBattleStartGetTrainerFaceSize();
    if (size == 0) {
        *((s32*)&_menuCBBattleStartWork + 0xC) = 4;
    } else {
        *((s32*)&_menuCBBattleStartWork + 0xC) = 2;
    }
    
    for (s32 i = 0; i < 8; i++) {
        *((s32*)&_menuCBBattleStartWork + 0x4 + i * 2) = 0;
    }
}

/*
  Address: 0x80047548 | size: 0x40
  menuCBBattleStartTrainerLoadTex()
  Loads trainer face textures.
*/
void menuCBBattleStartTrainerLoadTex(void) {
    _menuCBBattleStartGetTrainerFaceSize();
    *((u8*)&_menuCBBattleStartWork + 0x34) = 1;
    _menuCBBattleStartDispTrainerTexCallBack(0, 0, 0);
}

/*
  Address: 0x80047588 | size: 0x30
  _menuCBBattleStartGetTrainerFaceSize()
  Gets trainer face size (returns 0 for large, 1 for small).
*/
static s32 _menuCBBattleStartGetTrainerFaceSize(void) {
    s32 battleType = toolentryTaisenGetBattleType();
    return (battleType == 2);
}

/*
  Address: 0x800475B8 | size: 0x168
  _menuCBBattleStartDispTrainerTexCallBack(long id, void* data, long unused)
  Callback for loading trainer face textures.
*/
static void _menuCBBattleStartDispTrainerTexCallBack(s32 id, void* data, s32 unused) {
    if (data) {
        s32 resId = *((s32*)data + 1);
        GSresGetResourceAllGroup(resId);
        *((s32*)data) = resId;
    }
    
    s32 done = 1;
    
    while (done) {
        s32 idx = *((s32*)&_menuCBBattleStartWork + 0xB);
        s32 count = *((s32*)&_menuCBBattleStartWork + 0xC);
        
        if (idx == count) {
            done = 0;
            break;
        }
        
        s32 isLarge = _menuCBBattleStartGetTrainerFaceSize();
        
        s32 resId;
        if (isLarge) {
            s32 sign = (idx >> 31);
            s32 absVal = idx & 0x7FFFFFFF;
            s32 adjusted = absVal - sign;
            if (adjusted == 0) {
                resId = toolentryGetTrainerBicFaceResID(1, 0);
            } else {
                resId = toolentryGetTrainerBicFaceResID(0, 1);
            }
        } else {
            if (idx < 2) {
                resId = toolentryGetTrainerSamllFaceResID(1);
            } else {
                resId = toolentryGetTrainerSamllFaceResID(0);
            }
        }
        
        s32 isReady = _menuCBBattleStartGetTrainerFaceSize();
        s32 fsysId = isReady ? 0x5C3 : 0x5C4;
        
        s32* entry = (s32*)&_menuCBBattleStartWork + 0x3 + idx * 2;
        *entry = resId;
        GSresGetResourceAllGroup(resId);
        
        if (*entry != 0) {
            *((s32*)&_menuCBBattleStartWork + 0xB) = idx + 1;
            break;
        }
        
        GSfsysReadIDEX(fsysId, resId, entry, resId, _menuCBBattleStartDispTrainerTexCallBack);
        *((s32*)&_menuCBBattleStartWork + 0xB) = idx + 1;
        done = 0;
    }
}

/*
  Address: 0x80047720 | size: 0xD4
  menuCBBattleStartTrainerFaceFree()
  Frees trainer face textures.
*/
void menuCBBattleStartTrainerFaceFree(void) {
    s32 isLarge = _menuCBBattleStartGetTrainerFaceSize();
    s32 fsysId = isLarge ? 0x5C3 : 0x5C4;
    
    GSfsysFree(fsysId);
    GSresFreeGroup(fsysId);
    
    s32* entry = (s32*)&_menuCBBattleStartWork + 0x3;
    isLarge = _menuCBBattleStartGetTrainerFaceSize();
    
    s32 count = isLarge ? 4 : 2;
    *((s32*)&_menuCBBattleStartWork + 0xC) = count;
    
    for (s32 i = 0; i < count; i++) {
        s32 resId = *entry;
        GSresFreeResource(fsysId, resId);
        entry += 2;
    }
    
    menuCBBattleStartDispTrainerInit();
}

/*
  Address: 0x800477F4 | size: 0x4
  __sinit_menuCB_BattleStart_cpp()
  Static initializer (empty).
*/
static void __sinit_menuCB_BattleStart_cpp(void) {
    // Empty initializer
}

// Register static initializer
#ifdef MWERKS
#pragma section ".ctors"
#endif
void (*__sinit_menuCB_BattleStart_cpp_ptr)(void) = __sinit_menuCB_BattleStart_cpp;
#ifdef MWERKS
#pragma section
#endif
