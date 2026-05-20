// Decompiled from: menuKeyDisc.cpp
// Address range: 0x8000E71C..0x8000E74C | size: 0x30

/* Forward declarations */
s32 floorGetCurrentGroupID(void);
void GSresGetResource(s32 a, s32 b);

/*
  Address: 0x8000E71C | size: 0x4
  menuKeyDiscExit(void)
  Stub function for menu exit.
*/
void menuKeyDiscExit(void) {
    // Stub
}

/*
  Address: 0x8000E720 | size: 0x28
  menuKeyDiscMain(void)
  Main function for the key disc menu.
*/
void menuKeyDiscMain(void) {
    s32 group = floorGetCurrentGroupID();
    GSresGetResource(group, 0x117f);
}

/*
  Address: 0x8000E748 | size: 0x4
  menuKeyDiscInit(void)
  Stub function for menu initialization.
*/
void menuKeyDiscInit(void) {
    // Stub
}
