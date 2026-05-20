// Decompiled from: dbgMenuCamera.cpp
// Address range: 0x800056A4..0x80005798 | size: 0xF4

/* Forward declarations */
void cameraResetFloor(void);
void cameraSetType(s32 type);
s32  menuIsCheck(s32 menuId);
void menuClose(s32 menuId);
void menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void menuSetPosition(s32 menuId, s32 x, s32 y);

/* Menu ID constant */
#define MENU_CAMERA 6

/*
  Address: 0x800056A4 | size: 0x24
  dbgMenuCameraResetFloor(void)
  Resets the camera floor settings.
*/
s32 dbgMenuCameraResetFloor(void) {
    cameraResetFloor();
    return 0;
}

/*
  Address: 0x800056C8 | size: 0x70
  dbgMenuCameraChangeDisp(void)
  Toggles the camera debug menu display.
*/
s32 dbgMenuCameraChangeDisp(void) {
    if (menuIsCheck(MENU_CAMERA)) {
        menuClose(MENU_CAMERA);
    } else {
        menuOpenCustom(MENU_CAMERA, 0, 0, 0, 1, 0, 0);
        menuSetPosition(MENU_CAMERA, 0x14, 0x104);
    }
    return 0;
}

/*
  Address: 0x80005738 | size: 0x60
  dbgMenuCameraSetType(s32 type)
  Sets the camera type based on the menu selection.
  Mapping: 0 → 0, 1 → 5, 2 → 6, 3 → 6, else → 0
*/
s32 dbgMenuCameraSetType(s32 type) {
    if (type == 1) {
        cameraSetType(5);
    } else if (type >= 0 && type < 3) {
        cameraSetType(6);
    } else {
        cameraSetType(0);
    }
    return 0;
}
