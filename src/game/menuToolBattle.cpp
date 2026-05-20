// Decompiled from: menuToolBattle.cpp
// Address range: 0x8004DB44..0x8004E54C | size: 0xA08

/* Forward declarations */
extern void* _CB;
extern void* _CB2;

void    _menuCB_FlashStart__Fb(bool a);
void    _menuCB_FlashEnd__Fv(void);
void    _menuCB_FlashStart_VS__Fb(bool a);
void    _menuCB_FlashEnd_VS__Fb(bool a);
void    _menuCB_FlashStart_WINLOSE__Fv(void);
void    _menuCB_FlashEnd_WINLOSE__Fv(void);

/*
  Address: 0x8004DB44 | size: 0x40
  _menuCB_FlashEnd_WINLOSE()
  Ends the win/lose flash animation.
*/
static void _menuCB_FlashEnd_WINLOSE(void) {
    if (menuIsCheck(0x110)) {
        menuCloseCustom(0x110, 0, 0);
    }
}

/*
  Address: 0x8004DB84 | size: 0x170
  _menuCB_FlashStart_WINLOSE()
  Starts the win/lose flash animation based on fight result.
*/
static void _menuCB_FlashStart_WINLOSE(void) {
    static const char* labels[] = {
        "winlose_start", "winlose_stop",
        "losewin_start", "losewin_stop",
        "draw_start", "draw_stop"
    };
    
    s16 result = fightGetFightResultId();
    
    if (result == 5 || result == 2) {
        // Draw
        FlashSystemSetPlayFrameLabel(0x21543000, labels[4], labels[5]);
        FlashSystemSetNowFrameLabel(0x21543000, labels[4]);
    } else if (result >= 5) {
        // Lose
        FlashSystemSetPlayFrameLabel(0x21543000, labels[2], labels[3]);
        FlashSystemSetNowFrameLabel(0x21543000, labels[2]);
    } else {
        // Win
        FlashSystemSetPlayFrameLabel(0x21543000, labels[0], labels[1]);
        FlashSystemSetNowFrameLabel(0x21543000, labels[0]);
    }
    
    FlashSystemSetLoopFlag(0x21543000, 0);
    ((s16*)_CB2)[-0x4E88] = 1;
    menuOpen(0x110, 0, (void*)((u8*)&_CB + 0x1000));
    menuCB_SE_Play(0x5E0);
    
    while (!FlashSystemIsLastFrame(0x21543000)) {
        GSthreadSwitch();
    }
    
    pauseIsPause();
    while (((s16*)_CB2)[-0x4E1C] > 0) {
        ((s16*)_CB2)[-0x4E1C]--;
        windowGetKeyInfo();
        if (((u8*)r3)[4] & 0x40) break;
        GSthreadSwitch();
    }
}

/*
  Address: 0x8004DCF4 | size: 0x64
  _menuCB_FlashEnd_VS(bool a)
  Ends the VS flash animation.
*/
static void _menuCB_FlashEnd_VS(bool a) {
    if (a) {
        menuOpen(0x113, 0, 0);
        while (!winSeqCheckMove(0x113)) {
            GSthreadSwitch();
        }
    } else {
        ((u32*)_CB2)[-0x4E8C] = 1;
    }
}

/*
  Address: 0x8004DD58 | size: 0x9C
  _menuCB_FlashStart_VS(bool a)
  Starts the VS flash animation.
*/
static void _menuCB_FlashStart_VS(bool a) {
    if (a) {
        FlashSystemSetPlayFrameLabel(0x21533000, "start", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "start");
    } else {
        FlashSystemSetPlayFrameLabel(0x21533000, "end_keep", "end_keep");
        FlashSystemSetNowFrameLabel(0x21533000, "end_keep");
    }
    ((u32*)_CB2)[-0x4E90] = 1;
    ((u32*)_CB2)[-0x4E8C] = 0;
}

/*
  Address: 0x8004DDF4 | size: 0x40
  _menuCB_FlashEnd()
  Ends the flash animation.
*/
static void _menuCB_FlashEnd(void) {
    if (menuIsCheck(0x105)) {
        menuCloseCustom(0x105, 0, 0);
    }
}

/*
  Address: 0x8004DE34 | size: 0xB8
  _menuCB_FlashStart(bool a)
  Starts the flash animation.
*/
static void _menuCB_FlashStart(bool a) {
    if (a) {
        FlashSystemSetPlayFrameLabel(0x20093000, "start", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "start");
    } else {
        FlashSystemSetPlayFrameLabel(0x20093000, "end", "end");
        FlashSystemSetNowFrameLabel(0x20093000, "end");
    }
    ((u32*)_CB2)[-0x4EC0] = 1;
    menuOpen(0x105, 0, (void*)((u8*)&_CB + 0x1000));
    
    while (!FlashSystemIsLastFrame(0x20093000)) {
        GSthreadSwitch();
    }
}

/*
  Address: 0x8004DEEC | size: 0x9C
  menuToolBattleExit()
  Exits the tool battle menu and cleans up resources.
*/
void menuToolBattleExit(void) {
    if (*((s32*)&_CB + 1) == 1) {
        if (!fightReadResourceID(0x842, 0x184F3400)) {
            fightFreeResourceID(0x842, 0x184F3400);
        }
    } else {
        if (!fightReadResourceID(0x842, 0x195F3400)) {
            fightFreeResourceID(0x842, 0x195F3400);
        }
    }
    GSfsysFree(0x14);
    GSresFreeGroup(0x14);
}

/*
  Address: 0x8004DF88 | size: 0x568
  menuToolBattleMain()
  Main loop for tool battle menu.
*/
void menuToolBattleMain(void) {
    bool loop = true;
    _menuCB_FlashStart(true);
    
    u8* status = savedataGetStatus(0, 2);
    u8 backup = status[0x959];
    status[0x959] = 0;
    
    while (loop) {
        menuCBBios_CurrentlyWorkingToolBattleSet(1);
        menuCBBattleStartInit(&_CB, 0);
        ((u32*)_CB2)[-0x4E64] = 0;
        ((s16*)_CB2)[-0x4E1C] = 0xF;
        
        menuCBPokemonEntryPokemonFaceFree();
        menuCBPokemonEntryLoadTex();
        menuCBpokemonFaceReadWait();
        menuCBBattleStartTrainerFaceFree();
        menuCBBattleStartTrainerLoadTex();
        menuCBtrainerFaceReadWait();
        
        s32 fightType = *((s32*)&_CB + 2);
        
        if (fightType == 2) {
            menuOpen(0xB1, 0, 0);
            _menuCB_FlashStart_VS(true);
            menuOpen(0x103, 0, 0);
            menuOpen(0xB2, 1, 0);
            _menuCB_FlashEnd_VS(false);
            menuCloseCustom(0xB2, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else {
            s32 entryNum = menuCB_BattleBA_PokemonEntryNum();
            if (entryNum) {
                menuOpen(0xB1, 0, 0);
                _menuCB_FlashStart_VS(true);
                menuOpen(0x103, 0, 0);
                menuOpen(0xB3, 1, 0);
                _menuCB_FlashEnd_VS(false);
                menuCloseCustom(0xB3, 0, 0);
                menuCloseCustom(0x103, 0, 0);
                menuCloseCustom(0xB1, 0, 1);
            } else {
                menuOpen(0xB1, 0, 0);
                _menuCB_FlashStart_VS(true);
                menuOpen(0x103, 0, 0);
                menuOpen(0xB4, 1, 0);
                if (*((s32*)&_CB + 1) != 1) {
                    _menuCB_FlashEnd_VS(false);
                    menuCloseCustom(0xB4, 0, 0);
                    menuCloseCustom(0x103, 0, 0);
                    menuCloseCustom(0xB1, 0, 1);
                }
            }
        }
        
        if (((u32*)_CB2)[-0x4E64] != 0) {
            menuCB_GBADisconnectedErrorJob();
            menuCB_MenuRollback(0xA9);
            break;
        }
        
        s32 result;
        if (*((s32*)&_CB + 1) == 1) {
            result = 0;
        } else {
            result = menuCB_PokemonEntry(&_CB);
        }
        
        if (result < 0xB1 || result == 0xA9) {
            if (result == 0xA9) {
                menuCB_MenuRollback(0xA9);
            }
            break;
        }
        
        GSfsysFree(0x14);
        GSresFreeGroup(0x14);
        ((u32*)_CB2)[-0x4E7C] = 1;
        menuCB_Battle(&_CB);
        *((s32*)&_CB) = result;
        ((u32*)_CB2)[-0x4E7C] = 0;
        _menuCB_FlashStart(false);
        menuCBBattleEndSetPokemonHP();
        menuCBBattleStartInit(&_CB, 1);
        ((u32*)_CB2)[-0x4E64] = 0;
        ((s16*)_CB2)[-0x4E1C] = 0xB4;
        
        menuCBPokemonEntryPokemonFaceFree();
        menuCBPokemonEntryLoadTex();
        menuCBpokemonFaceReadWait();
        menuCBBattleStartTrainerFaceFree();
        menuCBBattleStartTrainerLoadTex();
        menuCBtrainerFaceReadWait();
        menuCB_SE_Play(0x14);
        
        if (fightType == 2) {
            menuOpen(0xB1, 0, 0);
            _menuCB_FlashStart_VS(false);
            menuOpen(0x103, 0, 0);
            menuOpen(0xB2, 1, 0);
            _menuCB_FlashStart_WINLOSE();
            result = menuCB_BattleResult(&_CB);
            _menuCB_FlashEnd_VS(true);
            _menuCB_FlashEnd_WINLOSE();
            if (result != 0xB1) {
                _menuCB_FlashEnd();
            }
            menuCloseCustom(0xB2, 0, 0);
            menuCloseCustom(0x103, 0, 0);
            menuCloseCustom(0xB1, 0, 1);
        } else {
            s32 entryNum = menuCB_BattleBA_PokemonEntryNum();
            if (entryNum) {
                menuOpen(0xB1, 0, 0);
                _menuCB_FlashStart_VS(false);
                menuOpen(0x103, 0, 0);
                menuOpen(0xB3, 1, 0);
                _menuCB_FlashStart_WINLOSE();
                result = menuCB_BattleResult(&_CB);
                _menuCB_FlashEnd_VS(true);
                _menuCB_FlashEnd_WINLOSE();
                if (result != 0xB1) {
                    _menuCB_FlashEnd();
                }
                menuCloseCustom(0xB3, 0, 0);
                menuCloseCustom(0x103, 0, 0);
                menuCloseCustom(0xB1, 0, 1);
            } else {
                menuOpen(0xB1, 0, 0);
                _menuCB_FlashStart_VS(false);
                menuOpen(0x103, 0, 0);
                menuOpen(0xB4, 1, 0);
                _menuCB_FlashStart_WINLOSE();
                result = menuCB_BattleResult(&_CB);
                _menuCB_FlashEnd_VS(true);
                _menuCB_FlashEnd_WINLOSE();
                if (result != 0xB1) {
                    _menuCB_FlashEnd();
                }
                menuCloseCustom(0xB4, 0, 0);
                menuCloseCustom(0x103, 0, 0);
                menuCloseCustom(0xB1, 0, 1);
            }
        }
        
        if (result == 0xB1 || result == 0xAC) {
            if (*((s32*)&_CB + 1) != 1) {
                if (((s32*)_CB2)[-0x5004] == 6) {
                    menuCB_InitBattle(&_CB);
                }
            } else {
                menuCB_InitBattle(&_CB);
            }
        }
        
        if (((u32*)_CB2)[-0x4E64] != 0) {
            menuCB_GBADisconnectedErrorJob();
            menuCB_MenuRollback(0xA9);
            break;
        }
        
        if (result == 0xAC || result >= 0xAC || result == 0xA9 || result >= 0xA9 || result == -1) {
            if (result == 0xB1) {
                toolentryCopyHero();
            } else {
                menuCB_MenuRollback(result);
                loop = false;
            }
        }
    }
    
    _menuCB_FlashEnd();
    menuCBBattleStartTrainerFaceFree();
    status = savedataGetStatus(0, 2);
    status[0x959] = backup;
    
    if (GSfloorIsFloorPushed()) {
        GSfloorPop();
    } else {
        GSfloorPop();
    }
}

/*
  Address: 0x8004E4F0 | size: 0x5C
  menuToolBattleInit()
  Initializes the tool battle menu by loading resources.
*/
void menuToolBattleInit(void) {
    if (*((s32*)&_CB + 1) == 1) {
        fightReadResourceID(0x842, 0x184F3400);
    } else {
        fightReadResourceID(0x842, 0x195F3400);
    }
    GSfsysReadWait(0x14);
}
