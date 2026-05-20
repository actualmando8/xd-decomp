// Decompiled from: menuTool.cpp
// Address range: 0x8000C284..0x8000C298 | size: 0x14

/* SBSS */
static s32 _menuToolSelect;

/*
  Address: 0x8000C284 | size: 0x8
  menuToolSetSelect(s32 select)
  Sets the menu tool selection.
*/
void menuToolSetSelect(s32 select) {
    _menuToolSelect = select;
}

/*
  Address: 0x8000C28C | size: 0xC
  menuToolInit(void)
  Initializes the menu tool selection to 0.
*/
void menuToolInit(void) {
    _menuToolSelect = 0;
}
