// Decompiled from time.cpp (0x8000E8CC - 0x8000E97C)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack

#include "system.h"

// ============================================================
// Global variables (sdata2)
// ============================================================

// Float constant: 0.0f (for pause return value)
static const float float_zero = 0.0f;

// Double constant: 2.0 (for vscale calculation)
static const double double_two = 2.0;

// Float constant: 0.5f (for frame time offset)
static const float float_half = 0.5f;

// ============================================================
// Forward declarations
// ============================================================
extern u32 pauseIsPause(void);
extern float GSgfxVideoGetLastRenderTime(void);
extern u32 GSgfxVideoGetVsyncRate(void);
extern u32 __cvt_fp2unsigned(float value);

// ============================================================
// Function implementations
// ============================================================

/*
 * timeGetLastFrameTime
 * Original address: 0x8000E8CC
 * Size: 0x44 bytes
 * 
 * Gets the time of the last frame in milliseconds.
 * Returns 0 if the game is paused.
 * 
 * @return  Last frame time in milliseconds
 */
u32 timeGetLastFrameTime(void) {
    if (pauseIsPause() != 0) {
        return 0;
    }
    
    float lastTime = GSgfxVideoGetLastRenderTime();
    lastTime += 0.5f;  // Add 0.5 for rounding
    
    return (u32)lastTime;
}

/*
 * timeGetLastFrameSec
 * Original address: 0x8000E910
 * Size: 0x6C bytes
 * 
 * Gets the time of the last frame in seconds.
 * Returns 0 if the game is paused.
 * 
 * Uses vsync rate to calculate frame duration.
 * 
 * @return  Last frame time in seconds (floating point)
 */
float timeGetLastFrameSec(void) {
    if (pauseIsPause() != 0) {
        return 0.0f;
    }
    
    u32 vsyncRate = GSgfxVideoGetVsyncRate();
    
    // Calculate: 2.0 / vsyncRate
    // The assembly stores vsyncRate and the constant 2.0, then subtracts to get divisor
    double vsyncDouble = (double)vsyncRate;
    double divisor = 2.0 - vsyncDouble;
    
    float lastTime = GSgfxVideoGetLastRenderTime();
    
    return (float)(2.0 / divisor);
}
