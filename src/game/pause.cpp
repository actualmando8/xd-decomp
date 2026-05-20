// Decompiled from: pause.cpp
// Address range: 0x8000E794..0x8000E8CC | size: 0x138

/* Forward declarations */
void GSgfxRenderUnpause(void);
void GSsndPopVolumeALL(s32 a, s32 b, s32 c);
void GSgappPauseOff(void);
void GSsndContinue(s32 id, s32 a, s32 b);
void GSmovieAllContinue(void);
void GSgfxRenderPause(void);
void GSsndPushVolumeALL(s32 a, s32 b, s32 c, s32 d);
void GSgappPauseOn(void);
s32  soundGetBGMID(void);
void GSsndPause(s32 id, s32 a, s32 b);
void GSmovieAllPause(void);
s32  GSgappCreate(s32 a, void* b, s32 c, void* d);

/* SBSS */
static u8 _pauseFlag;
static u8 _enablePauseFlag;
static s32 _sound_id;
static s32 _gappPadReadHandle;

/*
  Address: 0x8000E880 | size: 0x4
  pauseDaemon(u32, u32)
  Stub daemon function for pause system.
*/
void pauseDaemon__FUlUl(u32, u32) {
    // Stub
}

/*
  Address: 0x8000E794 | size: 0x8
  pauseIsPause(void)
  Returns the current pause flag.
*/
u8 pauseIsPause(void) {
    return _pauseFlag;
}

/*
  Address: 0x8000E79C | size: 0x68
  pauseOff(void)
  Turns off pause mode, resuming rendering, sound, and movies.
*/
void pauseOff(void) {
    if (_pauseFlag) {
        _pauseFlag = 0;
        GSgfxRenderUnpause();
        GSsndPopVolumeALL(0, 0, 1);
        GSgappPauseOff();
        if (_sound_id + 1 != 0xFFFF) {
            GSsndContinue(_sound_id, 0x32, 0);
        }
        GSmovieAllContinue();
    }
}

/*
  Address: 0x8000E804 | size: 0x7C
  pauseOn(void)
  Turns on pause mode, pausing rendering, sound, and movies.
*/
void pauseOn(void) {
    if (!_pauseFlag && _enablePauseFlag) {
        _pauseFlag = 1;
        GSgfxRenderPause();
        GSsndPushVolumeALL(0, 0, 0, 1);
        GSgappPauseOn();
        _sound_id = soundGetBGMID();
        if (_sound_id + 1 != 0xFFFF) {
            GSsndPause(_sound_id, 0x32, 0);
        }
        GSmovieAllPause();
    }
}

/*
  Address: 0x8000E884 | size: 0x48
  pauseInit(void)
  Initializes the pause system.
*/
void pauseInit(void) {
    _pauseFlag = 0;
    _enablePauseFlag = 1;
    _gappPadReadHandle = GSgappCreate(1, pauseDaemon__FUlUl, 0, 0);
}
