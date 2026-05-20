// Decompiled from: time.cpp
// Address range: 0x8000E8CC..0x8000E97C | size: 0xB0

/* Forward declarations */
s32   pauseIsPause(void);
f32   GSgfxVideoGetLastRenderTime(void);
s32   GSgfxVideoGetVsyncRate(void);
u32   __cvt_fp2unsigned(f32 f);

/* SData2 */
static const f32 _Zero = 0.0f;
static const f64 _One = 1.0;
static const f32 _Half = 0.5f;

/*
  Address: 0x8000E8CC | size: 0x44
  timeGetLastFrameTime(void)
  Returns the last frame time in milliseconds.
  If paused, returns 0. Otherwise, adds 0.5 to render time and converts to unsigned int.
*/
u32 timeGetLastFrameTime(void) {
    if (pauseIsPause()) {
        return 0;
    }
    f32 renderTime = GSgfxVideoGetLastRenderTime();
    return __cvt_fp2unsigned(renderTime + _Half);
}

/*
  Address: 0x8000E910 | size: 0x6C
  timeGetLastFrameSec(void)
  Returns the last frame time in seconds.
  If paused, returns 0. Otherwise, calculates 1.0 / (vsyncRate - lastRenderTime).
*/
f32 timeGetLastFrameSec(void) {
    if (pauseIsPause()) {
        return _Zero;
    }
    s32 vsyncRate = GSgfxVideoGetVsyncRate();
    f64 renderTime = GSgfxVideoGetLastRenderTime();
    f64 diff = (f64)vsyncRate - renderTime;
    return 1.0f / (f32)diff;
}
