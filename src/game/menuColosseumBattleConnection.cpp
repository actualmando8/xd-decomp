// Decompiled from: menuColosseumBattleConnection.cpp
// Address range: 0x8000C298..0x8000C2C0 | size: 0x28

/* SBSS */
static u8 _menuMainExec;

/*
  Address: 0x8000C298 | size: 0x4
  menuColosseumBattleConnectionExit(void)
  Stub function for menu exit.
*/
void menuColosseumBattleConnectionExit(void) {
    // Stub
}

/*
  Address: 0x8000C29C | size: 0x18
  menuColosseumBattleConnectionMain(void)
  Main function - sets _menuMainExec to 1 and returns the previous value minus 1.
*/
s32 menuColosseumBattleConnectionMain(void) {
    u8 prev = _menuMainExec;
    _menuMainExec = 1;
    return (s32)prev - 1;
}

/*
  Address: 0x8000C2B4 | size: 0xC
  menuColosseumBattleConnectionInit(void)
  Initializes _menuMainExec to 0.
*/
void menuColosseumBattleConnectionInit(void) {
    _menuMainExec = 0;
}
