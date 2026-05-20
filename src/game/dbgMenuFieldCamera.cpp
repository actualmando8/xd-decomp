// Decompiled from: dbgMenuFieldCamera.cpp
// Address range: 0x8000E154..0x8000E1F4 | size: 0xA0

/* Forward declarations */
s32  menuIsCheck(s32 menuId);
void menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void menuSetPosition(s32 menuId, s32 x, s32 y);
void* GSfloorGetCurrent(void);
s32   floorFieldCameraEditorGetFloorID(void);
void  floorInitFieldCameraEditor(void* floor);

/* SBSS */
static s32 gSelected_row;
static s32 gSelected_column;
static s32 gSelectedMenu_column;
static u8  gSaveResult;

/* Menu ID constant */
#define MENU_FIELD_CAMERA 0x23

/*
  Address: 0x8000E154 | size: 0xA0
  dbgMenuFieldCameraChangeDisp(void)
  Toggles the field camera debug menu.
*/
s32 dbgMenuFieldCameraChangeDisp(void) {
    if (menuIsCheck(MENU_FIELD_CAMERA)) {
        return 0;
    }
    
    void* floor = GSfloorGetCurrent();
    if (floorFieldCameraEditorGetFloorID() != (s32)floor) {
        floorInitFieldCameraEditor(floor);
        gSelected_row = 0;
        gSelected_column = 0;
        gSelectedMenu_column = 0;
    }
    gSaveResult = 0;
    menuOpenCustom(MENU_FIELD_CAMERA, 0, 0, 0, 1, 0, 0);
    menuSetPosition(MENU_FIELD_CAMERA, 0xC, 0xA);
    return 0;
}
