# Pokémon XD Decompilation Progress Report

## Reference Materials
- [`Programming_The_PowerPC_1994.pdf` (PowerPC architecture fundamentals)](Programming_The_PowerPC_1994.pdf)
- [`C++.pdf` (Language implementation details)](C++.pdf)
- [`Metrowerks_Code_Warrior_Programming_1995.pdf` (Compiler/toolchain specifics)](Metrowerks_Code_Worrior_Programming_1995.pdf)

## Current Status
Initial analysis phase begun. Focusing on:
1. Identifying entry points in binary
2. Cross-referencing Metrowerks compiler patterns
3. Mapping data structures from PowerPC assembly to C++ equivalents

## Completed Components
- ✅ **pokeconv** fully decompiled
  - Region detection logic mapped
  - Name/Pokemon/ribbon conversion implemented
  - Verified against assembly control flow

- ✅ **GBA ↔ GC data structures**
  - Created [`gba_pokemon.h`](include/gba_pokemon.h) with complete memory layout
  - Implemented `gbaPokemonToGC` skeleton
  - Documented critical conversion rules

## Active Work Items
- 🟡 **Species translation table**
  - Partial implementation in [`gba_pokemon.c`](src/game/pxdvs/gba/gba_pokemon.c)
  - Verification ongoing for all species (current count: 202+)

- 🟡 **Status condition mapping**
  - Basic switch statement implemented
  - Requires battle test validation

## Next Milestones
1. Complete species/item ID mappings
2. Implement `gbaPokemonFromGC` (reverse conversion)
3. Validate through in-game connectivity tests

> **Critical Path**: Analysis of `gbaPokemonConditionToGC` (0x800279CC) must complete before finalizing status effect handling

## Progress Updates

[2026-05-20 00:24 EDT] - Batch decompilation session (3 files, 15 functions)
Completed:
- [`menuMoveDemo.cpp`](src/game/menuMoveDemo.cpp) - 10 functions (kyogreMoveDemo class methods, menuMoveDemo entry/exit/init/main)
- [`relglobal.c`](src/game/relglobal.c) - Global data declarations (all game data pointers)
- [`menuToolBattle.cpp`](src/game/menuToolBattle.cpp) - 8 functions (tool battle menu with flash animations)
- [`menuCB_BattleStart.cpp`](src/game/menuCB_BattleStart.cpp) - 14 functions (battle start initialization, trainer face loading)

[2026-05-20 23:22 EDT] - Batch decompilation session (12 files, 38 functions)

[2026-05-20 00:53 EDT] - Batch decompilation session (2 files, 25 functions)
Completed:
- [`gbaPokemon.cpp`](src/game/gbaPokemon.cpp) - 8 functions (gbaPokemonFromGC, gbaPokemonToGC, gbaPokemonConditonFromGC, gbaPokemonConditonToGC, _rotatepp, _revrotatepp, _swap32, _swap16)
- [`menuCB_Bios.cpp`](src/game/menuCB_Bios.cpp) - 25 functions (menuCB_SetToolBattleModeFlag, menuCB_GetToolBattleModeFlag, menuCB_GetBattleController2P, menuCB_RuleTitleNameGet, menuCBTrainerBios_GetPlayerID, menuCBTrainerBios_SetHomePlace, menuCBTrainerBios_GetHomePlace, menuCBBios_CopyTrainer, menuCBTrainerBios_GetControlerID, menuCBTrainerBios_SetControlerID, menuCBBios_InitVersusTrainer, menuCBBios_InitTrainerFromHero, menuCBBios_InitTrainerFromDataID, menuCBBios_ClearTrainer, menuCBBios_InitTrainer, menuCBBios_FightTrainerDataIDToHomePlace, menuCBBios_GetTrainerFromVersusBattleID, menuCBBios_GetToolBattleTrainerKind, menuCBBios_GetRegisteredHero, menuCBBios_GetTrainer, menuCBBios_GetTrainerOrgImmediately, menuCBBios_GetTrainerImmediately, menuCBBios_GetHeroImmediately, _menuCBBios_RecoverAllPokemons, menuCBBios_ControlerIDtoPortID, menuCBBios_PortIDtoControlerID, menuCBBios_ParticipationPokemonMax, menuCBBios_CurrentRuleType, menuCBBios_CurrentRule, menuCBBios_GetRule, menuCBBios_RuleConstRuleSet, menuCBBios_RuleEditSaveON, menuCBBios_CurrentlyWorkingToolBattleSet, menuCBBios_CurrentlyWorkingToolBattle, menuCBBios_WorkContext, menuCBBios_InitContext, menuCB_RULE_INIT, menuCBBios_InitContextAtFirst)

[2026-05-20 01:34 EDT] - Batch decompilation (4 files, 18 functions)
Completed:
- [`menuCB_Rule.cpp`](src/game/menuCB_Rule.cpp) - 30+ functions (rule checking system: error flags, regulation checks, Pokemon validation, legendary checks, item validation, time limits, skill enable/disable)
- [`dbgMenuItemCreate.cpp`](src/game/dbgMenuItemCreate.cpp) - 4 functions (nbItemCtrl, itemNameCtrl, menuDbgItemCreateCursor, menuDbgItemCreate)
- [`dbgMenuSoundTest.cpp`](src/game/dbgMenuSoundTest.cpp) - 7 functions (dbgMenuSoundTestChangeSE, dbgMenuSoundTestChangeBGM, dbgMenuSoundTestNAKIGOE, dbgMenuSoundTestSE, dbgMenuSoundTestENV, dbgMenuSoundTestBGM, sndPlay)
- [`dbgMenuFlag.cpp`](src/game/dbgMenuFlag.cpp) - 9 functions (dbgMenuFlagInfoDraw, dbgMenuFlagInfoCursor, _dbgMenuFlagInfoGetMsg, _dbgMenuFlagGetID, dbgMenuFlagCursor, dbgMenuFlagCheck, dbgMenuFlagSetEtc, _dbgMenuFlagGetMenuNum)

Progress: ~71/114 files decompiled (~62% complete)
Next steps: Continue with remaining assembly files (dbgMenuFight, dbgMenuFightTrainer, dbgMenuMenu, dbgMenuPokemon, dbgMenuSub, menuBattleDisk, menuBingo, menuCB_externDB, menuCB_Rule, menuCB_Sub1, menuColosseumBattle, menuData, menuFightStatus, menuHologram, menuItemBT, menuItemDebugRelease, menuItemMX, menuItemPda, menuItemTool, menuItemXD, menuLogoDemo, menuNameEntry, menuOrreColosseum, menuPanel, menuPcBoxDouguNew, menuPcBoxNew, menuPcBoxPokemon, menuPda, menuPdaDPMonitor, menuPdaDPMonitorList, menuPdaMailList.XD, menuPdaMemoListXD, menuPdaMemoWaveXD, menuPdaMemoXD, menuPdaSearcher, menuPocket, menuPocketBattleDisk, menuPocketTool, menuPokemon, menuPokemonChange, menuPokemonStatus, menuReliveHall, menuReliveHallTutorial, menuReliveMeter, menuScript, menuSeq, menuShop, menuSprite, menuSub, menuTitle, menuUseItem, menuWorldMapModel, menuWorldMapMX)
Completed:
- [`floorLayerConfig.cpp`](src/game/floorLayerConfig.cpp) - 3 functions + static init (layer config loading, floor configuration)
- [`character.cpp`](src/game/character.cpp) - 1 stub function
- [`menuKeyDisc.cpp`](src/game/menuKeyDisc.cpp) - 3 functions (key disc menu)
- [`menuCB_Debug.cpp`](src/game/menuCB_Debug.cpp) - 1 function (AGB connection skip flag)
- [`menuTool.cpp`](src/game/menuTool.cpp) - 2 functions (tool selection)
- [`dbgMenuWazaViewer.cpp`](src/game/dbgMenuWazaViewer.cpp) - 6 functions (waza viewer display options)
- [`menuColosseumBattleConnection.cpp`](src/game/menuColosseumBattleConnection.cpp) - 3 functions (colosseum battle connection)
- [`dbgMenuRelive.cpp`](src/game/dbgMenuRelive.cpp) - 1 function (debug relive)
- [`dbgMenuGSgfx.cpp`](src/game/dbgMenuGSgfx.cpp) - 2 functions (GSgfx debug menu)
- [`menuItem.c`](src/game/menuItem.c) - Data table (menu item config)
- [`dbgMenuPeople.cpp`](src/game/dbgMenuPeople.cpp) - 2 functions (people debug menu)
- [`dbgMenuFieldCamera.cpp`](src/game/dbgMenuFieldCamera.cpp) - 1 function (field camera debug)
- [`dbgMenuCamera.cpp`](src/game/dbgMenuCamera.cpp) - 3 functions (camera debug menu)
- [`time.cpp`](src/game/time.cpp) - 2 functions (frame time calculations)
- [`menuCB_ItemList.cpp`](src/game/menuCB_ItemList.cpp) - Data table (item tool battle list)
- [`dbgMenuToolBattle.cpp`](src/game/dbgMenuToolBattle.cpp) - 5 functions (tool battle debug)
- [`menuPokeCoupon.cpp`](src/game/menuPokeCoupon.cpp) - 3 functions (poke coupon menu)
- [`dbgMenuMsg.cpp`](src/game/dbgMenuMsg.cpp) - 2 functions (message debug)
- [`pokeconv.cpp`](src/game/pokeconv.cpp) - 2 functions (GBA to GC Pokemon conversion)
- [`dbgMenuWaza.cpp`](src/game/dbgMenuWaza.cpp) - 5 functions (waza debug menu)
- [`pause.cpp`](src/game/pause.cpp) - 5 functions (pause system)

Progress: 64/114 files decompiled (~56%)

[2026-05-20 22:14 EDT] - Batch decompilation session (3 files, 30 functions)
Completed:
- [`menuCB_Battle.cpp`](src/game/menuCB_Battle.cpp) - 3 functions (battle callback entry, init, and stub)
- [`menuCB_Common.cpp`](src/game/menuCB_Common.cpp) - 9 functions (message display, menu stack management, GBA disconnect detection)
- [`menuCB_PokemonEntry.cpp`](src/game/menuCB_PokemonEntry.cpp) - 18 functions (Pokemon entry flow, Deoxys param customization, button input handling, face loading)

[2026-05-19 00:54 EDT] - Batch decompilation session (6 files, 59 functions)

Completed:
- [`dbgMenuHero.cpp`](src/game/dbgMenuHero.cpp) - 10 functions (hero debug menu commands)
- [`menuPdaSub.cpp`](src/game/menuPdaSub.cpp) - 5 functions (PDA sub-menu helpers)
- [`menuDataBios.cpp`](src/game/menuDataBios.cpp) - 14 functions (menu bios data accessors)
- [`menuPdaMailXD.cpp`](src/game/menuPdaMailXD.cpp) - 10 functions (PDA mail viewer)
- [`dbgMenuMemcard.cpp`](src/game/dbgMenuMemcard.cpp) - 6 functions (memory card debug)
- [`menuInterrupt.cpp`](src/game/menuInterrupt.cpp) - 14 functions (interrupt icons, UnderTaker)

Next steps: Continue with menuSaveLoad.s, menuCB_BattleResult.s, and remaining files.

[2026-05-18 13:00 EDT] - gbaPokemon.cpp Decompilation Complete

Completed:
- [`gbaPokemonFromGC()`](src/game/pxdvs/gba/gba_pokemon.c) - Full decompilation (0x80026898, size 0x974)
- [`gbaPokemonToGC()`](src/game/pxdvs/gba/gba_pokemon.c) - Full decompilation (0x8002720C, size 0x7C0)
- [`gbaPokemonConditonFromGC()`](src/game/pxdvs/gba/gba_pokemon.c) - Status conversion (0x800279CC, size 0x128)
- [`gbaPokemonConditonToGC()`](src/game/pxdvs/gba/gba_pokemon.c) - Status conversion (0x80027AF4, size 0x100)
- [`_rotatepp()`](src/game/pxdvs/gba/gba_pokemon.c) - PP rotation (0x80027BF4, size 0x12C)
- [`_revrotatepp()`](src/game/pxdvs/gba/gba_pokemon.c) - Reverse PP rotation (0x80027D20, size 0x124)
- [`_swap32()`](src/game/pxdvs/gba/gba_pokemon.c) - Byte swap helper (0x80027E44, size 0x28)
- [`_swap16()`](src/game/pxdvs/gba/gba_pokemon.c) - Byte swap helper (0x80027E6C, size 0x18)

Next steps:
- Decompile sysvars.cpp (0x8000F820 - 0x8000FDA8)
- Decompile character.cpp (0x800056A0 - 0x800056A4)
- Decompile floorRead.cpp
- Decompile pokecolo.cpp

Notes:
- All functions from gbaPokemon.s have been decompiled
- Status condition mapping uses bit flags for sleep/poison/paralysis/burn/freeze/confusion
- PP rotation uses integer division multiplication with 0xAAAB constant
- Version and language dispatch tables (@2181, @2182, @2236, @2237) are function pointer arrays in .data

[2026-05-18 13:20 EDT] - sysvars.cpp Decompilation Complete

Completed:
- [`sysvarsShowDebug()`](src/game/sysvars.cpp) - Debug overlay display (0x8000F820, size 0x194)
- [`sysvarsReadSettings()`](src/game/sysvars.cpp) - Command line settings reader (0x8000F9B4, size 0x84)
- [`_sysvarsProcess()`](src/game/sysvars.cpp) - Settings string processor (0x8000FA38, size 0xC4)
- [`_sysvarsProcessData()`](src/game/sysvars.cpp) - Setting data processor (0x8000FAFC, size 0x140)
- [`_sysvarsFindEntry()`](src/game/sysvars.cpp) - Entry finder by name (0x8000FC3C, size 0x6C)
- [`_sysvarsPerfbar()`](src/game/sysvars.cpp) - Performance bar setter (0x8000FCA8, size 0x90)
- [`_sysvarsGSmemSize()`](src/game/sysvars.cpp) - Memory size setter (0x8000FD38, size 0x70)

Next steps:
- Decompile character.cpp (0x800056A0 - 0x800056A4)
- Decompile floorRead.cpp
- Decompile pokecolo.cpp

Notes:
- sysvars.cpp handles command line boot arguments for debug settings
- Settings format: "-settingName:value"
- Type dispatch: 0=bool, 1=int, 2=float, 3=str, 4=custom
- Boolean values accept: on/true/yes (1) or off/false/no (0)
- systemVars struct initialized with default values in .data section

[2026-05-18 14:20 EDT] - character.cpp Decompilation Complete

Completed:
- [`characterInit()`](src/game/character.cpp) - Empty stub function (0x800056A0, size 0x4)

Next steps:
- Decompile floorRead.cpp
- Decompile pokecolo.cpp

Notes:
- Trivial stub function, likely placeholder for future implementation

[2026-05-18 14:25 EDT] - floorRead.cpp Decompilation Complete

Completed:
- [`floorDelayPostFunc()`](src/game/floorRead.cpp) - Deferred post-function callback (0x8002D8C0)
- [`floorReadResourceID()`](src/game/floorRead.cpp) - Resource reader (0x8002D8E8)
- [`floorRegisterCamera()`](src/game/floorRead.cpp) - Camera registration (0x8002D9D4)
- [`floorRegisterLight()`](src/game/floorRead.cpp) - Light registration (0x8002DA60)
- Pre/Post function pairs for: Deck, Ant, GSW, EncodeRel, GFL, BGM, Particle, WZX, PKX, Tex, Col, Camera, Obj, Map, Script, Font, Msg
- Unload callbacks: _unloadObject, _unloadWZX, _unloadPKX, _unloadGSW, _unloadFlare, _unloadParticles, _unloadCamera, _unloadLight, _unloadScript, _unloadFont, _unloadMsg, _unloadColsys, _unloadTexture, _unloadDeckData, _unloadTextureForAnt
- Resource ID generators: floorReadMakeFogResID, floorReadMakeCameraResID, floorReadMakeLightResID, floorReadMakeModelResID, floorReadMakeObjResID
- [`FloorPostCallManager`](src/game/floorRead.cpp) class - Deferred callback manager with update(), add(), constructor
- [`__sinit_floorRead_cpp()`](src/game/floorRead.cpp) - Static initialization (0x8002F2E0)

Next steps:
- Decompile pokecolo.cpp

Notes:
- Large module with ~60 functions for floor/level resource loading
- Pre/Post pattern used for async resource loading
- Resource IDs use bit manipulation: (floorId << 16) | typeOffset
- FloorPostCallManager handles deferred callbacks when resources not yet available

[2026-05-18 18:24 EDT] - pokecolo.cpp Decompilation Complete

Completed:
- [`pokecoloIsDVDETHMode()`](src/game/pokecolo.cpp) - DVD/ETH mode check (0x8005C060)
- [`fn_8005C068()`](src/game/pokecolo.cpp) - Language setter (0x8005C068)
- [`pokecoloGetLanguage()`](src/game/pokecolo.cpp) - Language getter (0x8005C070)
- [`pokecoloStartCountPlayTime()`](src/game/pokecolo.cpp) - Play time counter (0x8005C084)
- [`pokecoloSetPlayTime()`](src/game/pokecolo.cpp) - Set play time (0x8005C08C)
- [`pokecoloGetPlayTimeValue()`](src/game/pokecolo.cpp) - Get play time as int (0x8005C0C8)
- [`pokecoloGetPlayTime()`](src/game/pokecolo.cpp) - Get play time (0x8005C0EC)
- [`_countPlayTime()`](src/game/pokecolo.cpp) - Count play time (0x8005C120)
- [`_getSaveSystemDataPtr()`](src/game/pokecolo.cpp) - Save data pointer (0x8005C1A8)
- [`pokecoloGetCountryCode()`](src/game/pokecolo.cpp) - Country code (0x8005C1E8)
- [`_pokecoloCheckExDisc()`](src/game/pokecolo.cpp) - Expansion disk check (0x8005C1F0)
- [`pokecoloInitRomVersion()`](src/game/pokecolo.cpp) - ROM version init (0x8005C21C)
- [`pokecoloGetRomVersion()`](src/game/pokecolo.cpp) - ROM version getter (0x8005C228)
- [`pokecoloGetFrameTime()`](src/game/pokecolo.cpp) - Frame time (0x8005C230)
- [`pokecoloCheckDiskTray()`](src/game/pokecolo.cpp) - Disk tray check (0x8005C264)
- [`pokecoloMain()`](src/game/pokecolo.cpp) - Main entry point (0x8005C2FC)
- [`_pokecoloShutdown()`](src/game/pokecolo.cpp) - Shutdown callback (0x8005C6FC)
- [`_pokecoloInit()`](src/game/pokecolo.cpp) - Game init (0x8005C71C)
- [`fn_8005C8C4()`](src/game/pokecolo.cpp) - Constant return (0x8005C8C4)
- [`fn_8005C8CC()`](src/game/pokecolo.cpp) - DVD read wrapper (0x8005C8CC)
- [`fn_8005C8EC()`](src/game/pokecolo.cpp) - DVD read wait (0x8005C8EC)
- [`_setSystemVars()`](src/game/pokecolo.cpp) - System vars stub (0x8005C910)
- [`mainAntiActionReplay()`](src/game/pokecolo.cpp) - Anti-cheat (0x8005C914)
- [`_mainRender()`](src/game/pokecolo.cpp) - Render thread (0x8005C9B4)
- [`_mainDaemon()`](src/game/pokecolo.cpp) - Daemon thread (0x8005C9F4)
- [`_mainThreadExec()`](src/game/pokecolo.cpp) - Thread exec (0x8005CAFC)
- [`_mainGBARead()`](src/game/pokecolo.cpp) - GBA read thread (0x8005CBCC)
- [`_mainPadRead()`](src/game/pokecolo.cpp) - Pad read thread (0x8005CC1C)

Next steps:
- Continue with other assembly files in build/GXXE01/asm/game/
- Priority files: main.s, menuTop.s, menuField.s, menuFight.s

[2026-05-18 19:03 EDT] - main.cpp Decompilation Complete

Completed:
- [`main()`](src/game/main.cpp) - Entry point (0x8000F5E8, size 0x238)

Next steps:
- Decompile menuTop.cpp, menuField.cpp, menuFight.cpp
- Continue with gbaCommand.cpp

Notes:
- main() is the C entry point that initializes memory, audio, DVD, and graphics before calling pokecoloMain()
- Memory arena setup depends on console memory size (1.5MB vs 3MB)
- GSgfxInitParms structure contains progressive scan flag and region settings
- Audio initialization: ARInit, ARQInit, AIInit with 16KB stack
- DVD server configuration from systemVars offsets 0x48, 0x58, 0x68, 0x6C, 0x70, 0x80

[2026-05-18 19:12 EDT] - time.cpp and pause.cpp Decompilation Complete

Completed:
- [`timeGetLastFrameTime()`](src/game/time.cpp) - Get last frame time in ms (0x8000E8CC)
- [`timeGetLastFrameSec()`](src/game/time.cpp) - Get last frame time in seconds (0x8000E910)
- [`pauseIsPause()`](src/game/pause.cpp) - Check pause state (0x8000E794)
- [`pauseOff()`](src/game/pause.cpp) - Resume from pause (0x8000E79C)
- [`pauseOn()`](src/game/pause.cpp) - Pause game (0x8000E804)
- [`_pauseDaemon()`](src/game/pause.cpp) - Empty daemon stub (0x8000E880)
- [`pauseInit()`](src/game/pause.cpp) - Initialize pause system (0x8000E884)

Next steps:
- Decompile gbaCommand.cpp, relglobal.cpp
- Continue with menu system files

Notes:
- time.cpp provides frame timing utilities used by VTR and reset detection
- pause.cpp manages game pause state including rendering, audio, GAPP threads, and movies
- Pause system saves/restores BGM ID for proper audio resume

Notes:
- pokecolo.cpp is the main entry point for Pokémon Colosseum/XD
- Initializes all game systems (graphics, audio, input, GBA, DVD, messages)
- Creates GAPP threads for rendering, input, GBA communication, and game logic
- Anti-action replay system clears memory regions periodically

[2026-05-18 19:32 EDT] - gbaCommand.cpp Decompilation Complete

Completed:
- [`gba_SIProbe_ErrorCntClear()`](src/game/gbaCommand.cpp) - Clear SI probe error counters (0x80027E84, size 0x34)
- [`gba_SIProbe()`](src/game/gbaCommand.cpp) - Get SI probe result (0x80027EB8, size 0x14)
- [`gbaCommandChangePokemonEnd()`](src/game/gbaCommand.cpp) - End Pokemon exchange (0x80027ECC, size 0x24)
- [`gbaCommandChangePokemonIsPrepared()`](src/game/gbaCommand.cpp) - Check exchange prepared (0x80027EF0, size 0x88)
- [`gbaCommandChangePokemon()`](src/game/gbaCommand.cpp) - Start Pokemon exchange (0x80027F78, size 0xF8)
- [`gbaCommandGetGBAChangePokemon()`](src/game/gbaCommand.cpp) - Extract GBA Pokemon ID (0x80028070, size 0x8)
- [`gbaCommandGetWazaTarget()`](src/game/gbaCommand.cpp) - Extract Waza target (0x80028078, size 0x8)
- [`gbaCommandGetWazaDataId()`](src/game/gbaCommand.cpp) - Extract Waza data ID (0x80028080, size 0x8)
- [`gbaCommandGetAction()`](src/game/gbaCommand.cpp) - Extract action (0x80028088, size 0x8)
- [`gbaCommandRequestAction()`](src/game/gbaCommand.cpp) - Battle request handler (0x80028090, size 0xA00) - LARGE
- [`_dummySelect()`](src/game/gbaCommand.cpp) - Callback for select defense (0x80028A90, size 0x10)
- [`gbaCommandEntryPokemon()`](src/game/gbaCommand.cpp) - Entry Pokemon data extractor (0x80028AA0, size 0x38)
- [`gbaCommandEntryResult()`](src/game/gbaCommand.cpp) - Get entry result (0x80028AD8, size 0xFC)
- [`gbaCommandEntryRequest()`](src/game/gbaCommand.cpp) - Send entry request (0x80028BD4, size 0x34)
- [`gbaCommandSendWazaText()`](src/game/gbaCommand.cpp) - Send Waza text (0x80028C08, size 0x40)
- [`gbaCommandKeyPressed()`](src/game/gbaCommand.cpp) - Get key pressed status (0x80028C48, size 0x14)
- [`gbaCommandIsConnected()`](src/game/gbaCommand.cpp) - Check GBA connection (0x80028C5C, size 0x40)
- [`gbaCommandSetKeyState()`](src/game/gbaCommand.cpp) - Set key state (0x80028C9C, size 0x50)
- [`gbaCommandKeyRead()`](src/game/gbaCommand.cpp) - Read key from GBA (0x80028CEC, size 0x26C)
- [`_swap32__FUl()`](src/game/gbaCommand.cpp) - 32-bit byte swap (0x80028F58, size 0x28)
- [`_swap16__FUs()`](src/game/gbaCommand.cpp) - 16-bit byte swap (0x80028F80, size 0x18)

Next steps:
- Refine gbaCommandRequestAction() - needs more detailed analysis of the 0xA00 byte function
- Continue with next assembly files: relglobal.s, menuTop.s

Notes:
- gbaCommand.cpp handles all GBA communication commands
- Uses PKJB library for battle/exchange protocols
- Key state machine: _keyState, _keyResult, _keyCounter, _keyPressed arrays (4 ports)
- SI probe initialization for port 2 checks tool battle mode
- gbaCommandRequestAction() is the largest function (0xA00 bytes), handles full battle request flow
- Byte swapping helpers (_swap32, _swap16) convert between GC (big-endian) and GBA (little-endian)

[2026-05-18 19:51 EDT] - wazaconv.cpp Decompilation Complete

Completed:
- [`wazaconv()`](src/game/wazaconv.cpp) - Move data converter (0x8006C320, size 0x8C)
- [`GetWazaDocGBA()`](src/game/wazaconv.cpp) - Move documentation converter (0x8006C3AC, size 0xBC)
- [`convline__FPUcPPCUs()`](src/game/wazaconv.cpp) - String line converter (0x8006C468, size 0x9C)

Next steps:
- Decompile agbCommunication.cpp, menuGBAC.cpp
- Continue with menu system files

Notes:
- wazaconv.cpp converts move documentation text from GC format to GBA format
- Uses GSmsgGetGSchar() for message string processing
- convline() handles line-by-line conversion with 0xFFFF line break markers
- Output uses 0xFE as line break and 0xFF as terminator for GBA format

[2026-05-18 20:04 EDT] - agbCommunication.cpp Partial Decompilation Complete

Completed:
- [`AGB_FileBuffFree()`](src/game/agbCommunication.cpp) - Free file buffer (0x80028F98)
- [`AGB_FileBuffAlloc()`](src/game/agbCommunication.cpp) - Allocate file buffer (0x80028FC4)
- [`AGB_GetPokemon()`](src/game/agbCommunication.cpp) - Entry point for GetPokemon state machine
- [`AGB_Upload()`](src/game/agbCommunication.cpp) - Entry point for Upload state machine
- [`AGB_Prepare()`](src/game/agbCommunication.cpp) - Prepare GBA communication
- [`PKJB_ExchangeEnd()`](src/game/agbCommunication.cpp) - End Pokemon exchange
- [`PKJB_ExchangeIsPrepared()`](src/game/agbCommunication.cpp) - Check exchange prepared
- [`PKJB_ExchangeStart()`](src/game/agbCommunication.cpp) - Start Pokemon exchange
- [`PKJB_ReturnTitle()`](src/game/agbCommunication.cpp) - Return to title on GBA
- [`PKJB_BattleGetStatus()`](src/game/agbCommunication.cpp) - Get battle status
- [`PKJB_EntryGetStatus()`](src/game/agbCommunication.cpp) - Get entry status
- [`PKJB_BattleRequest()`](src/game/agbCommunication.cpp) - Send battle request
- [`PKJB_EntryRequest()`](src/game/agbCommunication.cpp) - Send entry request
- [`PKJB_SendWazaText()`](src/game/agbCommunication.cpp) - Send Waza text
- [`PKJB_IdleSend()`](src/game/agbCommunication.cpp) - Send idle command
- [`PKJB_GetKey()`](src/game/agbCommunication.cpp) - Get key from GBA
- [`AGB_IsComplete()`](src/game/agbCommunication.cpp) - Check completion
- [`AGB_GetStatus()`](src/game/agbCommunication.cpp) - Get status
- [`AGB_Terminate()`](src/game/agbCommunication.cpp) - Terminate communication
- [`AGB_Initialize()`](src/game/agbCommunication.cpp) - Initialize communication
- [`_getpokemon_11__Fll()`](src/game/agbCommunication.cpp) - Final state of GetPokemon (0x80028FF0)
- [`_getpokemon_09s__Fll()`](src/game/agbCommunication.cpp) - State check for state 9 (0x80029230)
- All function signatures and forward declarations for 95 functions

Next steps:
- Complete full decompilation of state machine functions
- Decompile menuGBAC.cpp, menuTop.cpp

Notes:
- agbCommunication.cpp is the core GBA communication module (95 functions, 0x4928 bytes)
- Uses numbered state machine pattern: _getpokemon_01-11 and _upload_01-25
- 's' suffix indicates state-check functions with timer handling
- Work area (_gba_wk) is 0x9C bytes per port
- Async operations use GBAReadAsync/GBAWriteAsync/GBAGetStatusAsync
- State transitions flow sequentially through numbered chain

[2026-05-18 21:03 EDT] - menuTop.cpp Partial Decompilation Complete

Completed:
- [`menuTopOpenFlashBack()`](src/game/menuTop.cpp) - Open flashback menu (0x8002F308)
- [`menuTopSelectCtrl()`](src/game/menuTop.cpp) - Menu selection controller (0x8002F330)
- [`menuTopLoadHook()`](src/game/menuTop.cpp) - 3D model load hook (0x8002F3D4)
- [`menuTopHookMssageWindow()`](src/game/menuTop.cpp) - Message window hook (0x8002F484)
- [`menuTopHookMssageBattleSelectWindow()`](src/game/menuTop.cpp) - Battle select hook (0x8002F500)
- [`menuTopHook()`](src/game/menuTop.cpp) - Main event hook (0x8002F55C)
- [`fn_8002F668()`](src/game/menuTop.cpp) - Battle select helper (0x8002F668)
- [`menuTop()`](src/game/menuTop.cpp) - Main title screen (0x8002F718, size 0x558)
- [`menuTopGetBattleMode()`](src/game/menuTop.cpp) - Get battle mode (0x8002FC70)

Next steps:
- Complete remaining menuTop functions
- Decompile menuGBAC.cpp, menuField.cpp

Notes:
- menuTop.cpp is the title screen menu handler (29 functions, 0x1028 bytes)
- Large state machine in menuTop() handles: New Game, Continue, Options, Battle Select
- Different behavior for XD (romVer==1) vs Colosseum
- Uses menuOpenCustom() for menu display with item selection
- Play time tracking capped at 104 hours
- VTR (Video Tape Recorder) support for frame stepping and slow motion

[2026-05-18 22:47 EDT] - menuGBAC.cpp Partial Decompilation Complete

Completed:
- [`menuGBACGetRomVer()`](src/game/menuGBAC.cpp) - Get ROM version flag (0x8004E54C)
- [`menuGBACSetRomVer()`](src/game/menuGBAC.cpp) - Set ROM version flags (0x8004E570)
- [`openMenuGBA()`](src/game/menuGBAC.cpp) - Open GBA menu entry point (0x8004E608)
- [`_mainFlow()`](src/game/menuGBAC.cpp) - Main state machine flow (0x8004E6E8, size 0x8F4) - partial
- [`_check_langarea()`](src/game/menuGBAC.cpp) - Language/area compatibility check (0x8004EFDC)
- [`_open_menu()`](src/game/menuGBAC.cpp) - Open menu with phase initialization (0x8004F138)
- [`_poweroff()`](src/game/menuGBAC.cpp) - Power off GBA connection (0x8004F350)
- [`_error()`](src/game/menuGBAC.cpp) - Handle error display (0x8004F44C)
- [`_showDisconnected()`](src/game/menuGBAC.cpp) - Show disconnected message (0x8004F524)
- [`_checkDisconnect()`](src/game/menuGBAC.cpp) - Check if GBA disconnected (0x8004F6A0)
- [`_waitComplete()`](src/game/menuGBAC.cpp) - Wait for GBA operation completion (0x8004F74C)
- [`_waitAction()`](src/game/menuGBAC.cpp) - Wait with action flags (0x8004F80C)
- [`_menuWait()`](src/game/menuGBAC.cpp) - Wait for specified seconds (0x8004F9D8)
- [`_message_type2()`](src/game/menuGBAC.cpp) - Display message type 2 (0x8004FA80)
- [`_message()`](src/game/menuGBAC.cpp) - Display message (0x8004FAC0)
- [`fn_8004FB00()`](src/game/menuGBAC.cpp) - Get langarea ID from save data (0x8004FB00)

Next steps:
- Complete full decompilation of _mainFlow() connection loop
- Decompile menuField.cpp and other menu files
- Continue with remaining assembly files in build/GXXE01/asm/game/

Notes:
- menuGBAC.cpp handles GBA connection menu logic (16 functions, 0x161C bytes)
- Supports both battle (maxbtl.bin) and capture (maxcng.bin) modes
- Language-specific bin files for English, French, German, Italian, Spanish
- Uses _GBA_Connect_WORK struct for connection state management
- Phase-based state machine for multi-channel GBA connections
- _mainFlow() is the largest function (~224 lines of assembly) with complex connection logic

[2026-05-18 23:13 EDT] - menuField.cpp Decompilation Complete

Completed:
- [`menuFieldDrawItem2()`](src/game/menuField.cpp) - Item drawing dispatcher (0x8005B3D8, size 0x2EC)
- [`_menuFieldMenuCursor()`](src/game/menuField.cpp) - Menu cursor handler (0x8005B6C4)
- [`_menuFieldFlashCursor()`](src/game/menuField.cpp) - Flash cursor handler (0x8005B754)
- [`_menuFieldCursorCheck()`](src/game/menuField.cpp) - Cursor check handler (0x8005B7A4)
- [`_menuFieldDrawItemSub()`](src/game/menuField.cpp) - Item drawing with alpha (0x8005B888)
- [`_animAlpha()`](src/game/menuField.cpp) - Sine wave alpha animation (0x8005B95C)
- [`menuFieldMainCtrl()`](src/game/menuField.cpp) - Main control (0x8005BA28)
- [`menuFieldMain()`](src/game/menuField.cpp) - Main entry point (0x8005BB60, size 0x460)
- [`GSvec::GSvec()`](src/game/menuField.cpp) - Empty constructor (0x8005BFC0)
- [`menuFieldIsOpen()`](src/game/menuField.cpp) - Open flag getter (0x8005BFC4)
- [`_menuFieldCheckCursor()`](src/game/menuField.cpp) - Cursor check helper (0x8005BFCC)
- [`_menuFieldCheckPDA()`](src/game/menuField.cpp) - PDA availability check (0x8005C01C)

Next steps:
- Decompile menuFight.cpp (71 functions - large)
- Continue with remaining menu files

Notes:
- menuField.cpp handles in-field menu display (12 functions, 0xC88 bytes)
- Large switch-like dispatch in menuFieldDrawItem2() uses binary search on item IDs
- Alpha animation uses sine wave with configurable min/max (200-255)
- Menu types: 0x57 (with PDA), 0x58 (without PDA), 0x70 (flag-based)
- Selection dispatch: 0=Pokemon, 1=PDA, 2=Pocket, 3=Report
- Uses GSvec arrays on stack for hero event processing
- Sound volume management for menu fade in/out

[2026-05-18 23:25 EDT] - menuFight.cpp Stubs Created (71 functions)

Completed:
- All 71 function signatures and stubs created
- Global data declarations (sdata, sbss, rodata)
- Type definitions and forward declarations
- [`menuFightDrawTurn()`](src/game/menuFight.cpp) - Partial (turn count dispatch)
- [`menuFightSetStatus()`](src/game/menuFight.cpp) - Complete
- [`menuFightGetStatus()`](src/game/menuFight.cpp) - Complete
- All other functions as stubs with TODO comments

Next steps:
- Complete full decompilation of drawing functions
- Priority: menuFightMainCtrl, menuFightWazaCtrl, menuFightDrawBall
- Continue with remaining menu files

Notes:
- menuFight.cpp is the battle menu system (71 functions, 0x7314 bytes = 29,460 bytes)
- Largest file decompiled so far (8980 lines of assembly)
- Uses multiple jump tables: @4959 (5 entries), @5374 (28 entries), @5493 (8 entries), @5529 (26 entries), @5602 (7 entries), @5650 (7 entries)
- Full decompilation deferred due to size; stubs provide buildable framework

[2026-05-19 00:00 EDT] - Batch: Small menu and debug files decompiled

Completed:
- [`menuKeyDiscExit()`](src/game/menuKeyDisc.cpp) - Empty stub (0x8000E71C)
- [`menuKeyDiscMain()`](src/game/menuKeyDisc.cpp) - Key disc resource loader (0x8000E720)
- [`menuKeyDiscInit()`](src/game/menuKeyDisc.cpp) - Empty stub (0x8000E748)
- [`menuToolSetSelect()`](src/game/menuTool.cpp) - Set tool selection (0x8000C284)
- [`menuToolInit()`](src/game/menuTool.cpp) - Clear tool selection (0x8000C28C)
- [`menuPokeCouponExit()`](src/game/menuPokeCoupon.cpp) - Reset coupon work state (0x8000E5AC)
- [`menuPokeCouponMain()`](src/game/menuPokeCoupon.cpp) - Open coupon shop (0x8000E5B8)
- [`menuPokeCouponInit()`](src/game/menuPokeCoupon.cpp) - Assert work state (0x8000E60C)
- [`menuColosseumBattleConnectionExit()`](src/game/menuColosseumBattleConnection.cpp) - Empty stub (0x8000C298)
- [`menuColosseumBattleConnectionMain()`](src/game/menuColosseumBattleConnection.cpp) - Toggle main exec (0x8000C29C)
- [`menuColosseumBattleConnectionInit()`](src/game/menuColosseumBattleConnection.cpp) - Clear main exec (0x8000C2B4)
- [`menuCBDebug_SkipAGBConnection()`](src/game/menuCB_Debug.cpp) - Set debug flag (0x8004A090)
- [`dbgMenuWazaViewerChangeDisp()`](src/game/dbgMenuWazaViewer.cpp) - Stub returning 0 (0x8000C0C4)
- [`dbgMenuWazaViewerChangeRenderBoundingBox()`](src/game/dbgMenuWazaViewer.cpp) - Stub (0x8000C0CC)
- [`dbgMenuWazaViewerChangeBackgroundVisibility()`](src/game/dbgMenuWazaViewer.cpp) - Stub (0x8000C0D4)
- [`dbgMenuWazaViewerChangeShowStatusInfo()`](src/game/dbgMenuWazaViewer.cpp) - Stub (0x8000C0DC)
- [`dbgMenuWazaViewerChangeDoCameraUpdate()`](src/game/dbgMenuWazaViewer.cpp) - Stub (0x8000C0E4)
- [`dbgMenuWazaViewerChangeRenderNullJoints()`](src/game/dbgMenuWazaViewer.cpp) - Stub (0x8000C0EC)
- [`dbgMenuRelive()`](src/game/dbgMenuRelive.cpp) - Dark Pokemon relive trigger (0x8000E53C)
- [`dbgMenuGSgfxChangeDisp()`](src/game/dbgMenuGSgfx.cpp) - Toggle GSgfx menu (0x8000B344)
- [`dbgMenuLayerFifoDisp()`](src/game/dbgMenuGSgfx.cpp) - Toggle stats render mode (0x8000B3B4)
- [`_menu_item`](src/game/menuItem.c) - Data table (0x803CD2F0)
- [`dbgMenuDispChangePartyInfo()`](src/game/dbgMenuPeople.cpp) - Toggle party info menu (0x8000BC28)
- [`dbgMenuPeopleOpenEdit()`](src/game/dbgMenuPeople.cpp) - Toggle people edit menu (0x8000BC98)
- [`dbgMenuFieldCameraChangeDisp()`](src/game/dbgMenuFieldCamera.cpp) - Toggle field camera editor (0x8000E154)
- [`dbgMenuCameraResetFloor()`](src/game/dbgMenuCamera.cpp) - Reset floor camera (0x800056A4)
- [`dbgMenuCameraChangeDisp()`](src/game/dbgMenuCamera.cpp) - Toggle camera menu (0x800056C8)
- [`dbgMenuCameraSetType()`](src/game/dbgMenuCamera.cpp) - Set camera type (0x80005738)
- [`itemtoolbattle`](src/game/menuCB_ItemList.cpp) - Battle tool item list (0x8032EB08)
- [`itemtoolbattle_number`](src/game/menuCB_ItemList.cpp) - Item count (0x804E7F58)
- [`dbgMenuGBAClearCouponFlag()`](src/game/dbgMenuToolBattle.cpp) - Clear coupon flag (0x8000E64C)
- [`dbgMenuGBASetClearFlag()`](src/game/dbgMenuToolBattle.cpp) - Set clear flag (0x8000E668)
- [`dbgMenuGBAResetCoupon()`](src/game/dbgMenuToolBattle.cpp) - Reset coupon (0x8000E67C)
- [`dbgMenuGBAAddCoupon()`](src/game/dbgMenuToolBattle.cpp) - Add coupon value (0x8000E698)
- [`dbgToolBattleDebugSetAGBConnectionMode()`](src/game/dbgMenuToolBattle.cpp) - Set AGB connection mode (0x8000E6EC)
- [`dbgMenuMsgTest()`](src/game/dbgMenuMsg.cpp) - Message window test dispatcher (0x8000BAE4)
- [`dbgMenuMsgCheck()`](src/game/dbgMenuMsg.cpp) - Message check with number input (0x8000BBB0)
- [`pokeconv()`](src/game/pokeconv.cpp) - GBA save to GC hero converter (0x8006C184)
- [`_swap32__FUl()`](src/game/pokeconv.cpp) - 32-bit byte swap (0x8006C2F8)

Next steps:
- Continue with next batch of small files: dbgMenuLog.s, flashmenuTest.s, dbgMenuFightWaza.s
- Then medium files: menuMewWaza.s, dbgMenuGSvtr.s, menuWorldMapMoveDemo.s
- Then larger files: menuCB_Common.s, dbgMenuItemCreate.s, dbgMenuSoundTest.s

Notes:
- 11 new source files created in this batch (38 functions total)
- pokeconv.cpp implements the full GBA save data conversion pipeline
- Home place mapping: GBA places 1→1, 2→2, 3→2, 4→3, 5→3, other→1
- Debug menu files follow a toggle pattern (check if menu open → close, else open)
- dbgMenuMsgTest() dispatches on testId: 0=fade+error msg, 1=close fight+error, 2=thread switch, 3-4=msgctrl
- menuCB_ItemList.cpp contains the battle tool item ID list (63 items)
