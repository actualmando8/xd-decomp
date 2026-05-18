// Decompiled from pokecolo.cpp (0x8005C060 - 0x8005CC74)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// SDA21 relative addressing used for global variables

#include "system.h"

// ============================================================
// Global variables (SDA21 relative)
// ============================================================

// pokecolo_DVDETHMode - DVD/ETH mode flag
static u8 pokecolo_DVDETHMode;

// _pokecoloCurrentLanguage - Current language setting (0 = default to English)
static u32 _pokecoloCurrentLanguage;

// __pokecolo_CountPlayTime - Flag to enable play time counting
static u8 __pokecolo_CountPlayTime;

// _RomVer - ROM version
static u32 _RomVer;

// _frameTime - Frame time (64-bit value split into two 32-bit words)
static u64 _frameTime;

// pokecoloFrameCounter - Frame counter
static u32 pokecoloFrameCounter;

// pokecoloWaitVSync - Wait for VSync flag
static u8 pokecoloWaitVSync;

// Gapp handles
static u32 pokecoloGappRenderHandle;
static u32 pokecoloGappPadReadHandle;
static u32 pokecoloGappGBAReadHandle;
static u32 pokecoloGappThreadHandle;
static u32 pokecoloGappAntiActionReplayHandle;
static u32 pokecoloGappMainDeamonHandle;

// _AntiActionReplayTimer - Timer for anti-action replay checks
static u32 _AntiActionReplayTimer;

// _resettimer - Timer for reset tracking
static float _resettimer;

// init$2109 - Render initialization flag
static u8 init$2109;

// frame$2108 - Frame counter for rendering
static u32 frame$2108;

// _clearAddress - Array of address pairs for anti-action replay clearing
static u32 _clearAddress[0x40];

// floordata and floordata_number - Floor data pointers
extern u32 floordata;
extern u32 floordata_number;

// systemVars - System variables structure
extern u32 systemVars[];

// ============================================================
// Forward declarations for external functions
// ============================================================
extern void* _getSaveSystemDataPtr__Fv(void);
extern void gamedatasaveBiosSetPlaytime(float time);
extern float gamedatasaveBiosGetPlaytime(void* data);
extern u32 GSflagGet(u32 flag);
extern float pokecoloGetFrameTime(void);
extern u32 savedataBiosGetNowSavedataPtr(void);
extern u32 savedataBiosGetGamedataPtr(void);
extern void* gamedatasaveBiosGetPtr(void);
extern u32 pokecoloGetRomVersion(void);
extern u32 menuIsCheck(u32 menuId);
extern u32 pauseIsPause(void);
extern void pauseOn(void);
extern void pauseOff(void);
extern u32 GSfsysGetDriveStatus(void);
extern void GSgfxRelocToScratch(u32* addr);
extern void GSgfxPerfbarSetRenderMode(u32 mode);
extern void GSthreadInit(u32 param);
extern void pauseInit(void);
extern void GStextureInit(u32 param);
extern void GSmodelInit(void);
extern void GSpartInit(u32 param);
extern void GSmaterialInit(void);
extern void GScameraInit(u32 param);
extern void GSlightInit(u32 param);
extern void shapeInit(u32 param);
extern void GSparticleInit(u32 param);
extern void GSinputInit(void);
extern void GSinputOpen(u32 port);
extern void GSinputSetClamping(u32 port, u32 value);
extern void GSinputSetSmoothingRate(u32 port, u32 rate);
extern void GSinputSetSmoothingFunc(u32 port, u32 func);
extern void GSgappInit(u32 param1, u32 param2);
extern void GSresInit(u32 param);
extern void GSfloorInit(u32 p1, u32 p2, u32 p3, u32 p4);
extern void GScolsys2Init(void);
extern void GSmsgInit(u32 p1, u32 p2);
extern void GSmsgSetCtrlFunc(void* func);
extern void GSnetworkInit(void);
extern void GSmsgFontOpen(void* data);
extern void GSmsgOpen(void* data);
extern void GSdvdSetErrorMsg(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5);
extern void GSvtrInit(void);
extern void GSlensFlareInit(void);
extern void GSmovieInit(void);
extern void menuInit(u32 param);
extern void GSgfxVideoSetLockFrameRate(u32 rate);
extern void GSgfxVideoSetLockFrameActive(u32 active);
extern u32 GSgappCreate(u32 p1, u32 p2, u32 p3, u32 p4, void* func);
extern void GSgappSetName(u32 handle, const char* name);
extern void GSgappSetPauseLevel(u32 handle, u32 level);
extern void GSvtrRegisterGSgapp(u32 handle);
extern void GSgfxResetEnable(void);
extern void GSgfxResetSetShutdownCallback(void* func);
extern void fadeInit(void);
extern void GSfilterInitialise(u32 param);
extern void GSeffectInitSystem(void);
extern void deckInit(void);
extern void GSthreadCreate(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, void* func);
extern void OSGetTime(u32* high, u32* low);
extern void GSgappUpdate(void);
extern void pokecoloCheckDiskTray(void);
extern u64 __div2u(u64 value);
extern void GSsndQuit(void);
extern void floorLayerConfig(u32 p1, u32 p2);
extern void menuNintendo(void);
extern void floorLayerConfigLoad(void);
extern void GSfloorSetData(void* data, u32 param);
extern void* GSresAllocResource(u32 group, u32 id, u32 size, u32 align);
extern void pokecoloSetPlayTime(float time);
extern void pokecoloStartCountPlayTime(u8 enable);
extern void* tableResBiosGetResPtr(u32 id);
extern void floorMappingCommonScript(void);
extern u32 OSGetTime(void);
extern u32 savedataBiosGetSavedataBufferPtr(void);
extern void savedataBiosSetNowSavedataPtr(u32 ptr);
extern void savedataCreate(u32 p1, u32 p2);
extern void fightInit(void);
extern u32 savedataGetStatus(u32 slot, u32 statusId);
extern void GSflagInit(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5);
extern void GSvtrLoadTexture(void);
extern void menuFaceAllocMemory(void);
extern void* GSresGetResourceAllGroup(u32 group);
extern void GSmodelSetMarukageTexture(void* texture);
extern void characterInit(void);
extern void cameraInit(void);
extern void lightInit(void);
extern void heroMoveAllInit(void);
extern void peopleInit(u32 param);
extern void floorFieldCameraInit(void);
extern void sodateyaHeroCallBackInit(void);
extern void reliveHallCallBackInit(void);
extern void esabaHeroCallBackInit(void);
extern void memcardInitialize(void);
extern void floorInit(void);
extern void _setSystemVars__Fv(void);
extern u32 OSGetProgressiveMode(void);
extern u32 OSGetResetCode(void);
extern void GSgfxVideoSetMode(u32 p1, u32 p2, u32 p3, u32 p4, u32 p5);
extern u32 GSinputIsConnected(u32 port);
extern void gbaCommandKeyRead(u32 port);
extern void GSinputReadStart(void);
extern u32 gbaCommandIsConnected(u32 port);
extern void GSinputRead(u32 port);
extern void GSinputReadEnd(void);
extern void GSgfxRender(void);
extern void dbgMenuGSvtrCaptureUpdate(void);
extern u32 GSvtrIsActive(void);
extern u32 dbgMenuIsOpen(void);
extern u32 GSinputButtonsChanged(u32 port);
extern u32 GSinputButtonsPressed(u32 port);
extern u32 GSvtrGetState(void);
extern void GSvtrSlowPlay(void);
extern void GSvtrPause(void);
extern void GSvtrPlay(void);
extern void GSvtrSingleStep(void);
extern u32 GSvtrGetInfoDisp(void);
extern void GSvtrSetInfoDisp(u32 mode);
extern void menuDaemon(void);
extern void GSmsgDaemon(void);
extern void _countPlayTime__Fv(void);
extern u32 GSgfxResetGetStatus(void);
extern void GSgfxReset(u32 param);
extern void GSthreadExecuteAll(void);
extern u32 menuFieldIsOpen(void);
extern u32 peopleIsBlock(void);
extern void peopleDaemon(u32 p1, u32 p2);
extern void peopleUpdateShadow(void);
extern u32 timeGetLastFrameSec(void);

// String resources
static const char* @2403 = "mainRender";
static const char* @2404 = "mainPadRead";
static const char* @2405 = "mainGBARead";
static const char* @2406 = "mainThread";
static const char* @2407 = "AntiActionReplay";
static const char* @2408 = "mainDeamon";

// Float constants
static const float float_0 = 0.0f;
static const float frameTimeDiv1 = 900.0f;
static const float frameTimeDiv2 = 900.0f;
static const float playTimeMax = 104.0f;
static const float resetTimerInit = 0.5f;
static const float resetTimerThreshold = 3.0f;

// Message resources
extern void* resident_fnt$2161;
extern void* common_fnt$2162;
extern void* common_tbl$2164;
extern u32 system_error_fnt$2165;
extern void* system_error_tbl$2166;
extern void* debug_menu_fnt$2163;
extern void* lbl_8038FBE0;
extern void* msgctrlcode;

// ============================================================
// Function implementations
// ============================================================

/*
 * pokecoloIsDVDETHMode
 * Original address: 0x8005C060
 * Size: 0x8 bytes
 * 
 * Returns the DVD/ETH mode flag
 */
u8 pokecoloIsDVDETHMode(void) {
    return pokecolo_DVDETHMode;
}

/*
 * fn_8005C068
 * Original address: 0x8005C068
 * Size: 0x8 bytes
 * 
 * Sets the current language
 */
void fn_8005C068(u32 language) {
    _pokecoloCurrentLanguage = language;
}

/*
 * pokecoloGetLanguage
 * Original address: 0x8005C070
 * Size: 0x14 bytes
 * 
 * Gets the current language (returns 2 if not set)
 */
u32 pokecoloGetLanguage(void) {
    if (_pokecoloCurrentLanguage != 0) {
        return _pokecoloCurrentLanguage;
    }
    return 2;  // Default to English
}

/*
 * pokecoloStartCountPlayTime
 * Original address: 0x8005C084
 * Size: 0x8 bytes
 * 
 * Enables/disables play time counting
 */
void pokecoloStartCountPlayTime(u8 enable) {
    __pokecolo_CountPlayTime = enable;
}

/*
 * pokecoloSetPlayTime
 * Original address: 0x8005C08C
 * Size: 0x3C bytes
 * 
 * Sets the play time in save data
 */
void pokecoloSetPlayTime(float time) {
    void* saveData = _getSaveSystemDataPtr__Fv();
    if (saveData != 0) {
        gamedatasaveBiosSetPlaytime(time);
    }
}

/*
 * pokecoloGetPlayTimeValue
 * Original address: 0x8005C0C8
 * Size: 0x24 bytes
 * 
 * Gets the play time as an unsigned integer
 */
u32 pokecoloGetPlayTimeValue(void) {
    float time = pokecoloGetPlayTime();
    return (u32)time;
}

/*
 * pokecoloGetPlayTime
 * Original address: 0x8005C0EC
 * Size: 0x34 bytes
 * 
 * Gets the play time from save data
 */
float pokecoloGetPlayTime(void) {
    void* saveData = _getSaveSystemDataPtr__Fv();
    if (saveData != 0) {
        return gamedatasaveBiosGetPlaytime(saveData);
    }
    return 0.0f;
}

/*
 * _countPlayTime
 * Original address: 0x8005C120
 * Size: 0x88 bytes
 * 
 * Counts and updates play time
 */
static void _countPlayTime__Fv(void) {
    void* saveData = _getSaveSystemDataPtr__Fv();
    if (saveData == 0) {
        return;
    }
    
    if (__pokecolo_CountPlayTime != 1) {
        return;
    }
    
    // Check flag 0x30D (play time disabled flag)
    if (GSflagGet(0x30D) != 0) {
        return;
    }
    
    float currentTime = gamedatasaveBiosGetPlaytime(saveData);
    float frameTime = pokecoloGetFrameTime();
    float newTime = currentTime + frameTime;
    
    // Cap at maximum play time
    if (newTime > 104.0f) {
        newTime = 104.0f;
    }
    
    gamedatasaveBiosSetPlaytime(newTime);
}

/*
 * _getSaveSystemDataPtr
 * Original address: 0x8005C1A8
 * Size: 0x40 bytes
 * 
 * Gets pointer to save system data
 */
static void* _getSaveSystemDataPtr__Fv(void) {
    u32 savedataPtr = savedataBiosGetNowSavedataPtr();
    if (savedataPtr == 0) {
        return 0;
    }
    
    u32 gamedataPtr = savedataBiosGetGamedataPtr();
    if (gamedataPtr == 0) {
        return 0;
    }
    
    return gamedatasaveBiosGetPtr();
}

/*
 * pokecoloGetCountryCode
 * Original address: 0x8005C1E8
 * Size: 0x8 bytes
 * 
 * Returns the country code (always 1 for Colombia/Colosseum)
 */
u32 pokecoloGetCountryCode(void) {
    return 1;
}

/*
 * _pokecoloCheckExDisc
 * Original address: 0x8005C1F0
 * Size: 0x2C bytes
 * 
 * Checks if this is an expansion disk (returns 1 for XD)
 */
u32 _pokecoloCheckExDisc__Fv(void) {
    u32 version = pokecoloGetRomVersion();
    // Check if version == 4 (XD)
    u32 diff = version - 4;
    return ((~diff | diff) >> 31) & 1;
}

/*
 * pokecoloInitRomVersion
 * Original address: 0x8005C21C
 * Size: 0xC bytes
 * 
 * Initializes ROM version to 0
 */
void pokecoloInitRomVersion(void) {
    _RomVer = 0;
}

/*
 * pokecoloGetRomVersion
 * Original address: 0x8005C228
 * Size: 0x8 bytes
 * 
 * Gets the ROM version
 */
u32 pokecoloGetRomVersion(void) {
    return _RomVer;
}

/*
 * pokecoloGetFrameTime
 * Original address: 0x8005C230
 * Size: 0x34 bytes
 * 
 * Gets the frame time as a floating point value
 */
float pokecoloGetFrameTime(void) {
    u64 time = _frameTime;
    float timeF = (float)time;
    return timeF / 900.0f / 900.0f;
}

/*
 * pokecoloCheckDiskTray
 * Original address: 0x8005C264
 * Size: 0x98 bytes
 * 
 * Checks disk tray status and manages pause state
 */
void pokecoloCheckDiskTray(void) {
    // Check if menu 0x2A is active
    if (menuIsCheck(0x2A) != 0) {
        if (pauseIsPause() != 0) {
            return;
        }
        pauseOn();
        return;
    }
    
    u32 driveStatus = GSfsysGetDriveStatus();
    
    // Drive status 0xB = tray open, 0x7 = no disc
    if (driveStatus == 0xB || (driveStatus >= 0x3 && driveStatus < 0x7)) {
        if (pauseIsPause() == 0) {
            pauseOn();
        }
    } else if (driveStatus >= 0x7) {
        if (pauseIsPause() != 0) {
            pauseOff();
        }
    }
}

/*
 * pokecoloMain
 * Original address: 0x8005C2FC
 * Size: 0x400 bytes
 * 
 * Main entry point for the game - initializes systems and runs main loop
 */
void pokecoloMain(void) {
    u32 clearAddr = (u32)_clearAddress;
    GSgfxRelocToScratch(&clearAddr);
    
    // Reset frame counter
    pokecoloFrameCounter = 0;
    
    // Set performance bar render mode based on systemVars
    {
        s32 mode = (s32)systemVars[2];
        if (mode == 0) {
            GSgfxPerfbarSetRenderMode(0);
        } else if (mode == 1) {
            GSgfxPerfbarSetRenderMode(1);
        } else if (mode == 2) {
            GSgfxPerfbarSetRenderMode(2);
        } else if (mode >= 3) {
            // Invalid mode
        }
    }
    
    GSthreadInit(0x14);
    fn_8005C068(2);  // Set language to English
    
    u32 isProgressive = 0;
    
    if (_pokecoloCheckExDisc__Fv() == 1) {
        // XD - check progressive mode
        if (OSGetProgressiveMode() == 1) {
            isProgressive = 1;
        }
    } else {
        // Colosseum - check progressive mode and reset code
        if (OSGetProgressiveMode() == 1) {
            u32 resetCode = OSGetResetCode();
            if ((resetCode & 0x80000000) != 0) {
                if (OSGetResetCode() == 1) {
                    isProgressive = 1;
                }
            }
        }
    }
    
    // Set video mode for progressive scan
    if (isProgressive != 0) {
        GSgfxVideoSetMode(0, 1, 0, 0, 1);
    }
    
    // Initialize systems
    pauseInit();
    GStextureInit(0x10);
    GSmodelInit();
    GSpartInit(8);
    GSmaterialInit();
    GScameraInit(0x20);
    GSlightInit(0x20);
    shapeInit(0x20);
    GSparticleInit(0x20);
    GSinputInit();
    
    // Initialize input for all 4 ports
    for (u32 i = 1; i <= 4; i++) {
        GSinputOpen(i);
        GSinputSetClamping(i, 2);
        GSinputSetSmoothingRate(i, 7);
        GSinputSetSmoothingFunc(i, 1);
    }
    
    GSgappInit(0x14, 4);
    GSresInit(0x15E);
    GSfloorInit(4, 0x10, 0x10, 0x10);
    GScolsys2Init();
    GSmsgInit(2, 5);
    GSmsgSetCtrlFunc(msgctrlcode);
    GSnetworkInit();
    
    // Open message fonts and tables
    GSmsgFontOpen(resident_fnt$2161);
    GSmsgFontOpen(common_fnt$2162);
    GSmsgOpen(common_tbl$2164);
    GSmsgFontOpen((void*)system_error_fnt$2165);
    GSmsgOpen(system_error_tbl$2166);
    GSmsgFontOpen(debug_menu_fnt$2163);
    GSmsgOpen(lbl_8038FBE0);
    
    // Set DVD error messages
    GSdvdSetErrorMsg(0x65, 0x66, 0x67, 0x68, 0x69);
    
    GSvtrInit();
    GSlensFlareInit();
    GSmovieInit();
    menuInit(0x18);
    GSgfxVideoSetLockFrameRate(0);
    GSgfxVideoSetLockFrameActive(1);
    
    // Create GAPP threads
    {
        u32 handle = GSgappCreate(1, 0xFF, 0, 0, _mainRender__FUlUl);
        pokecoloGappRenderHandle = handle;
        GSgappSetName(handle, @2403);
    }
    
    {
        u32 handle = GSgappCreate(1, 0, 0, 0, _mainPadRead__FUlUl);
        pokecoloGappPadReadHandle = handle;
        GSgappSetName(handle, @2404);
    }
    
    {
        u32 handle = GSgappCreate(1, 1, 0, 0, _mainGBARead__FUlUl);
        pokecoloGappGBAReadHandle = handle;
        GSgappSetName(handle, @2405);
    }
    
    {
        u32 handle = GSgappCreate(1, 0xA, 0, 0, _mainThreadExec__FUlUl);
        pokecoloGappThreadHandle = handle;
        GSgappSetName(handle, @2406);
        GSgappSetPauseLevel(handle, 1);
        GSvtrRegisterGSgapp(handle);
    }
    
    {
        u32 handle = GSgappCreate(1, 0xFD, 0, 0, mainAntiActionReplay);
        pokecoloGappAntiActionReplayHandle = handle;
        GSgappSetName(handle, @2407);
    }
    
    {
        u32 handle = GSgappCreate(1, 0xFE, 0, 0, _mainDaemon__FUlUl);
        pokecoloGappMainDeamonHandle = handle;
        GSgappSetName(handle, @2408);
    }
    
    GSgfxResetEnable();
    GSgfxResetSetShutdownCallback(_pokecoloShutdown__Fv);
    fadeInit();
    GSfilterInitialise(8);
    GSeffectInitSystem();
    deckInit();
    
    // Create initialization thread
    GSthreadCreate(0, 0x3E8, 1, 0x4000, 1, _pokecoloInit__Fv);
    
    // Main loop
    u32 timeHigh, timeLow;
    OSGetTime(&timeHigh, &timeLow);
    u32 prevTimeHigh = timeHigh;
    u32 prevTimeLow = timeLow;
    
    const u32 divConst = 0x431C - 0x217D;  // Precomputed constant
    
    while (1) {
        GSgappUpdate();
        pokecoloCheckDiskTray();
        
        OSGetTime(&timeHigh, &timeLow);
        
        // Calculate frame time
        {
            u32 dh = prevTimeHigh - timeHigh;
            u32 dl = prevTimeLow - timeLow;
            // 64-bit division to get frame time
            u64 time64 = ((u64)dh << 32) | dl;
            u64 result = __div2u(time64);
            _frameTime = result;
        }
        
        OSGetTime(&timeHigh, &timeLow);
        prevTimeHigh = timeHigh;
        prevTimeLow = timeLow;
        
        pokecoloFrameCounter++;
    }
}

/*
 * _pokecoloShutdown
 * Original address: 0x8005C6FC
 * Size: 0x20 bytes
 * 
 * Shutdown callback - quits sound system
 */
static void _pokecoloShutdown__Fv(void) {
    GSsndQuit();
}

/*
 * _pokecoloInit
 * Original address: 0x8005C71C
 * Size: 0x1A8 bytes
 * 
 * Game initialization function (runs in separate thread)
 */
static void _pokecoloInit__Fv(void) {
    floorLayerConfig(0, 5);
    menuNintendo();
    floorLayerConfigLoad();
    
    // Set floor data
    GSfloorSetData((void*)floordata, *(u32*)floordata_number);
    
    // Allocate resource and initialize play time
    {
        void* resource = GSresAllocResource(2, 0, 2, 0);
        float zero = 0.0f;
        *(u8*)resource = 0;
        *((u8*)resource + 1) = 0;
        pokecoloWaitVSync = 0;
        pokecoloSetPlayTime(zero);
        pokecoloStartCountPlayTime(0);
    }
    
    // Open message resources
    GSmsgFontOpen(tableResBiosGetResPtr(0));
    GSmsgOpen(tableResBiosGetResPtr(1));
    
    // Set DVD error messages
    GSdvdSetErrorMsg(0x65, 0x66, 0x67, 0x68, 0x69);
    
    floorMappingCommonScript();
    
    // Setup save data
    {
        u32 time;
        OSGetTime(&time);
        u32 saveSlot = (time >> 11) & 0x1F;
        u32 bufferPtr = savedataBiosGetSavedataBufferPtr();
        savedataBiosSetNowSavedataPtr(bufferPtr + saveSlot);
    }
    
    savedataCreate(0, 0);
    fightInit();
    
    // Get save status for all slots
    u32 status5 = savedataGetStatus(0, 5);
    u32 status6 = savedataGetStatus(0, 6);
    u32 status7 = savedataGetStatus(0, 7);
    u32 status8 = savedataGetStatus(0, 8);
    u32 status9 = savedataGetStatus(0, 9);
    u32 status4 = savedataGetStatus(0, 4);
    
    GSflagInit(status9, status8, status7, status6, status5);
    
    GSvtrLoadTexture();
    menuFaceAllocMemory();
    GSmodelSetMarukageTexture(GSresGetResourceAllGroup(0x1F3A1200));
    
    characterInit();
    cameraInit();
    lightInit();
    heroMoveAllInit();
    peopleInit(0x30);
    floorFieldCameraInit();
    sodateyaHeroCallBackInit();
    reliveHallCallBackInit();
    esabaHeroCallBackInit();
    memcardInitialize();
    floorInit();
    _setSystemVars__Fv();
    
    // Clear memory region
    memset((void*)0x80001803, 0, 0x17FD);
}

/*
 * fn_8005C8C4
 * Original address: 0x8005C8C4
 * Size: 0x8 bytes
 *
 * Returns constant value 2
 */
u32 fn_8005C8C4(void) {
    return 2;
}

/*
 * fn_8005C8CC
 * Original address: 0x8005C8CC
 * Size: 0x20 bytes
 *
 * Wrapper for fn_8005C8EC
 */
void fn_8005C8CC(void) {
    fn_8005C8EC();
}

/*
 * fn_8005C8EC
 * Original address: 0x8005C8EC
 * Size: 0x24 bytes
 *
 * Waits for DVD read completion
 */
void fn_8005C8EC(void) {
    GSfsysReadWait(0xA);
}

/*
 * _setSystemVars
 * Original address: 0x8005C910
 * Size: 0x4 bytes
 *
 * Empty stub for setting system variables
 */
static void _setSystemVars__Fv(void) {
    // Empty stub
}

/*
 * mainAntiActionReplay
 * Original address: 0x8005C914
 * Size: 0xA0 bytes
 *
 * Anti-action replay check - clears memory regions periodically
 */
void mainAntiActionReplay(void) {
    if (_AntiActionReplayTimer != 0) {
        goto decrement_timer;
    }
    
    // Clear address pairs
    {
        u32 i = 0;
        u32* clearPtr = _clearAddress;
        while (i < 0x20) {
            u32 addr = clearPtr[0];
            u32 size = clearPtr[1];
            memset((void*)(addr | 0x80000000), 0, size);
            clearPtr += 2;
            i++;
        }
    }
    
    // Clear additional memory region
    memset((void*)0x80001801, 0, 0x17FF);
    
    _AntiActionReplayTimer = 0x64;
    
decrement_timer:
    _AntiActionReplayTimer--;
}

/*
 * _mainRender
 * Original address: 0x8005C9B4
 * Size: 0x40 bytes
 *
 * Render thread function
 */
static void _mainRender__FUlUl(u32 param1, u32 param2) {
    if (init$2109 == 0) {
        frame$2108 = 0;
        init$2109 = 1;
    }
    
    GSgfxRender();
}

/*
 * _mainDaemon
 * Original address: 0x8005C9F4
 * Size: 0x108 bytes
 *
 * Main daemon thread function - handles VTR controls and daemon tasks
 */
static void _mainDaemon__FUlUl(u32 param1, u32 param2) {
    dbgMenuGSvtrCaptureUpdate();
    
    if (GSvtrIsActive() == 0) {
        goto do_daemon;
    }
    
    if (dbgMenuIsOpen() != 0) {
        goto do_daemon;
    }
    
    // Check for VTR controls (L+R button press)
    {
        u32 changed = GSinputButtonsChanged(1);
        u32 pressed = GSinputButtonsPressed(1);
        u32 both = changed & pressed;
        
        if ((both & 0x20000) != 0) {  // L+R pressed
            u32 state = GSvtrGetState();
            if (state == 2) {
                GSvtrSlowPlay();
            } else if (state == 4) {
                GSvtrPause();
            } else {
                GSvtrPlay();
            }
        }
    }
    
    // Check for single step (L+Z button press)
    {
        u32 changed = GSinputButtonsChanged(1);
        u32 pressed = GSinputButtonsPressed(1);
        u32 both = changed & pressed;
        
        if ((both & 0x8000000) != 0) {  // L+Z pressed
            GSvtrSingleStep();
        }
    }
    
    // Check for info display toggle (R+Z button press)
    {
        u32 changed = GSinputButtonsChanged(1);
        u32 pressed = GSinputButtonsPressed(1);
        u32 both = changed & pressed;
        
        if ((both & 0x10000000) != 0) {  // R+Z pressed
            u32 infoDisp = GSvtrGetInfoDisp();
            u32 newMode = ((~infoDisp | infoDisp) >> 31) & 1;
            GSvtrSetInfoDisp(newMode);
        }
    }
    
do_daemon:
    menuDaemon();
    GSmsgDaemon();
    _countPlayTime__Fv();
}

/*
 * _mainThreadExec
 * Original address: 0x8005CAFC
 * Size: 0xD0 bytes
 *
 * Main thread execution function - handles game thread and reset
 */
static void _mainThreadExec__FUlUl(u32 param1, u32 param2) {
    u32 resetStatus = GSgfxResetGetStatus();
    
    // Check for reset (Start+Select press)
    {
        u32 pressed = GSinputButtonsPressed(1);
        if ((pressed & 0x1600) == 0x1600) {  // Start+Select
            if (resetStatus != 0) {
                float lastFrameSec = timeGetLastFrameSec();
                float nextReset = _resettimer + 0.5f;
                
                if (nextReset >= 3.0f) {
                    GSgfxReset(0);
                }
            } else {
                _resettimer = 0.5f;
            }
        }
    }
    
    GSthreadExecuteAll();
    
    if (menuFieldIsOpen() != 0) {
        peopleUpdateShadow();
    } else if (peopleIsBlock() == 0) {
        peopleDaemon(param1, param2);
    } else {
        peopleUpdateShadow();
    }
}

/*
 * _mainGBARead
 * Original address: 0x8005CBCC
 * Size: 0x50 bytes
 *
 * GBA reading thread function
 */
static void _mainGBARead__FUlUl(u32 param1, u32 param2) {
    for (u32 port = 1; port <= 4; port++) {
        if (GSinputIsConnected(port) == 0) {
            gbaCommandKeyRead(port);
        }
    }
}

/*
 * _mainPadRead
 * Original address: 0x8005CC1C
 * Size: 0x58 bytes
 *
 * Pad reading thread function
 */
static void _mainPadRead__FUlUl(u32 param1, u32 param2) {
    GSinputReadStart();
    
    for (u32 port = 1; port <= 4; port++) {
        if (gbaCommandIsConnected(port) == 0) {
            GSinputRead(port);
        }
    }
    
    GSinputReadEnd();
}
