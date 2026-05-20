// Decompiled from: dbgMenuMsg.cpp
// Address range: 0x8000BAE4..0x8000BC28 | size: 0x144

/* Forward declarations */
void fadeSet(s32 type, f32 time);
void fadeCheck(s32 type);
void winMsgOpenError(s32 a, s32 b, s32 c);
void winMsgClose(s32 type);
void winMsgCloseFight(s32 type);
void winMsgCloseError(s32 type);
void GSthreadSwitch(void);
void msgctrlSetValue(s32 a, s32 b);
s32  GSinputButtonsPressed(s32 controller);
s32  menuSubOpenNumberInputDigit(s32 a, s32* out);
void winMsgOpenField(s32 a, s32 b, s32 c);
void menuSubKeyWait(void);
void winMsgCloseField(s32 type);

/* SData2 */
static const f32 _FadeTime = 0.5f;

/*
  Address: 0x8000BAE4 | size: 0xCC
  dbgMenuMsgTest(s32 test)
  Runs various message test scenarios based on test number.
*/
s32 dbgMenuMsgTest(s32 test) {
    switch (test) {
        case 0:
            fadeSet(3, _FadeTime);
            fadeCheck(1);
            winMsgOpenError(1, 1, 0);
            winMsgClose(1);
            fadeSet(2, _FadeTime);
            fadeCheck(1);
            break;
        case 1:
            winMsgCloseFight(1);
            winMsgCloseError(1);
            break;
        case 2:
            GSthreadSwitch();
            GSthreadSwitch();
            GSthreadSwitch();
            winMsgCloseFight(0);
            GSthreadSwitch();
            GSthreadSwitch();
            break;
        case 3:
            msgctrlSetValue(0x31, 0x7DA);
            break;
        default:
            break;
    }
    return 0;
}

/*
  Address: 0x8000BBB0 | size: 0x78
  dbgMenuMsgCheck(void)
  Checks for Start button press, opens number input, displays field message.
*/
s32 dbgMenuMsgCheck(void) {
    s32 buttons = GSinputButtonsPressed(1);
    // Check Start button (bit 26)
    if (buttons & (1 << 26)) {
        s32 input;
        s32 result = menuSubOpenNumberInputDigit(0, &input);
        if (result != 0) {
            return -1;
        }
        winMsgOpenField(input, 1, 0);
        menuSubKeyWait();
        winMsgCloseField(1);
        return 0;
    }
    return 1;
}
