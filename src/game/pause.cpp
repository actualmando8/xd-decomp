// Decompiled from pause.cpp (0x8000E794 - 0x8000E8CC)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack

#include "system.h"

// ============================================================
// Global variables (sbss)
// ============================================================

// _pauseFlag - Current pause state (0 = running, 1 = paused)
static u8 _pauseFlag;

// _enablePauseFlag - Enable/disable pause functionality
static u8 _enablePauseFlag;

// _sound_id - Currently playing sound ID (for pause/resume)
static u32 _sound_id;

// _gappPadReadHandle - GAPP handle for pause daemon
static u32 _gappPadReadHandle;

// ============================================================
// Forward declarations
// ============================================================
extern void GSgfxRenderUnpause(void);
extern void GSsndPopVolumeALL(u32 p1, u32 p2, u32 p3);
extern void GSgappPauseOff(void);
extern void GSsndContinue(u32 id, u32 p2, u32 p3);
extern void GSmovieAllContinue(void);
extern void GSgfxRenderPause(void);
extern void GSsndPushVolumeALL(u32 p1, u32 p2, u32 p3, u32 p4);
extern void GSgappPauseOn(void);
extern u32 soundGetBGMID(void);
extern void GSsndPause(u32 id, u32 p2, u32 p3);
extern void GSmovieAllPause(void);
extern u32 GSgappCreate(u32 p1, u32 p2, u32 p3, void* func);

// ============================================================
// Function implementations
// ============================================================

/*
 * pauseIsPause
 * Original address: 0x8000E794
 * Size: 0x8 bytes
 * 
 * Returns the current pause state.
 * 
 * @return  0 if running, non-zero if paused
 */
u8 pauseIsPause(void) {
    return _pauseFlag;
}

/*
 * pauseOff
 * Original address: 0x8000E79C
 * Size: 0x68 bytes
 * 
 * Resumes the game from paused state.
 * Restores rendering, sound volume, GAPP threads, BGM, and movies.
 */
void pauseOff(void) {
    if (_pauseFlag == 0) {
        return;
    }
    
    _pauseFlag = 0;
    GSgfxRenderUnpause();
    GSsndPopVolumeALL(0, 0, 1);
    GSgappPauseOff();
    
    // Resume BGM if valid sound ID
    if ((_sound_id & 0xFFFF0000) != 0xFFFF0000) {
        GSsndContinue(_sound_id, 0x32, 0);
    }
    
    GSmovieAllContinue();
}

/*
 * pauseOn
 * Original address: 0x8000E804
 * Size: 0x7C bytes
 * 
 * Pauses the game.
 * Saves BGM ID, pauses rendering, sound, GAPP threads, and movies.
 */
void pauseOn(void) {
    if (_pauseFlag != 0) {
        return;
    }
    
    if (_enablePauseFlag == 0) {
        return;
    }
    
    _pauseFlag = 1;
    GSgfxRenderPause();
    GSsndPushVolumeALL(0, 0, 0, 1);
    GSgappPauseOn();
    
    // Save and pause BGM
    _sound_id = soundGetBGMID();
    if ((_sound_id & 0xFFFF0000) != 0xFFFF0000) {
        GSsndPause(_sound_id, 0x32, 0);
    }
    
    GSmovieAllPause();
}

/*
 * _pauseDaemon
 * Original address: 0x8000E880
 * Size: 0x4 bytes
 * 
 * Empty stub for pause daemon thread
 */
static void _pauseDaemon__FUlUl(u32 param1, u32 param2) {
    // Empty stub
}

/*
 * pauseInit
 * Original address: 0x8000E884
 * Size: 0x48 bytes
 * 
 * Initializes the pause system.
 * Creates a GAPP thread for the pause daemon.
 */
void pauseInit(void) {
    _pauseFlag = 0;
    _enablePauseFlag = 1;
    
    _gappPadReadHandle = GSgappCreate(1, 0, 0, _pauseDaemon__FUlUl);
}
