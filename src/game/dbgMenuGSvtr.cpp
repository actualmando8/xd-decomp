// Decompiled from: dbgMenuGSvtr.cpp
// Address range: 0x8000B3F8..0x8000B620 | size: 0x228

s32     GSinputButtonsChanged(s32 type);
s32     GSinputButtonsPressed(s32 type);
void    soundOpenPlay(s32 a, s32 b, s32 c);
void    GSgfxCaptureMovieStart(s32 width);
void    GSgfxCaptureMovieStop(void);
void    GSgfxCaptureSetTarget(s32 target);
s32     GSvtrGetInfoDisp(void);
void    GSvtrSetInfoDisp(s32 disp);
void    GSvtrSlowPlay(void);
void    GSvtrSingleStep(void);
void    GSvtrPause(void);
void    GSvtrPlay(void);
s32     GSvtrIsActive(void);
void    GSvtrEnable(void);
void    GSvtrDisable(void);

/* Global state */
static u8 _vtrWantCapture;
static u8 _vtrIsCapturing;

/*
  Address: 0x8000B3F8 | size: 0xA8
  dbgMenuGSvtrCaptureUpdate()
  Handles VTR capture toggle on L+R button press.
  If not capturing and wantCapture is set: starts capture at 0x4650 width.
  If capturing: stops capture.
*/
s32 dbgMenuGSvtrCaptureUpdate(void) {
    s32 changed = GSinputButtonsChanged(1);
    s32 pressed = GSinputButtonsPressed(1);
    s32 both = changed & pressed;
    
    // Check bit 27 (L+R simultaneous?)
    if ((both >> 27) & 1) {
        if (_vtrIsCapturing == 0) {
            if (_vtrWantCapture) {
                soundOpenPlay(8, 0, 0);
                GSgfxCaptureMovieStart(0x4650);
                _vtrWantCapture = 0;
                _vtrIsCapturing = 1;
            }
        }
        else if (_vtrIsCapturing == 1) {
            GSgfxCaptureMovieStop();
            _vtrIsCapturing = 0;
        }
    }
    return 0;
}

/*
  Address: 0x8000B4A0 | size: 0x3C
  dbgMenuGSvtrCaptureSD()
  Sets capture target to SD (1) and enables info display.
*/
s32 dbgMenuGSvtrCaptureSD(void) {
    GSgfxCaptureSetTarget(1);
    _vtrWantCapture = 1;
    GSvtrGetInfoDisp();
    GSvtrSetInfoDisp(1);
    return 0;
}

/*
  Address: 0x8000B4DC | size: 0x3C
  dbgMenuGSvtrCaptureBBA()
  Sets capture target to BBA (0) and enables info display.
*/
s32 dbgMenuGSvtrCaptureBBA(void) {
    GSgfxCaptureSetTarget(0);
    _vtrWantCapture = 1;
    GSvtrGetInfoDisp();
    GSvtrSetInfoDisp(1);
    return 0;
}

/*
  Address: 0x8000B518 | size: 0x24
  dbgMenuGSvtrSlow()
  Triggers slow play mode.
*/
s32 dbgMenuGSvtrSlow(void) {
    GSvtrSlowPlay();
    return 0;
}

/*
  Address: 0x8000B53C | size: 0x24
  dbgMenuGSvtrStep()
  Triggers single frame step.
*/
s32 dbgMenuGSvtrStep(void) {
    GSvtrSingleStep();
    return 0;
}

/*
  Address: 0x8000B560 | size: 0x24
  dbgMenuGSvtrPause()
  Triggers pause.
*/
s32 dbgMenuGSvtrPause(void) {
    GSvtrPause();
    return 0;
}

/*
  Address: 0x8000B584 | size: 0x24
  dbgMenuGSvtrPlay()
  Triggers play.
*/
s32 dbgMenuGSvtrPlay(void) {
    GSvtrPlay();
    return 0;
}

/*
  Address: 0x8000B5A8 | size: 0x3C
  dbgMenuGSvtrChangeDisp()
  Toggles VTR info display based on wantCapture flag.
*/
s32 dbgMenuGSvtrChangeDisp(void) {
    s32 current = GSvtrGetInfoDisp();
    s32 wantCap = _vtrWantCapture;
    s32 cntlz = __builtin_clz(current);
    s32 new_val = (cntlz >> 5) & 0x07;
    GSvtrSetInfoDisp(new_val);
    return 0;
}

/*
  Address: 0x8000B5E4 | size: 0x3C
  dbgMenuGSvtrChangeActive()
  Toggles VTR active state.
*/
s32 dbgMenuGSvtrChangeActive(void) {
    if (!GSvtrIsActive()) {
        GSvtrEnable();
    }
    else {
        GSvtrDisable();
    }
    return 0;
}
