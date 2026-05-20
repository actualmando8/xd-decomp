// Decompiled from: dbgMenuPeople.cpp
// Address range: 0x8000BC28..0x8000BD20 | size: 0xF8

/* Forward declarations */
s32  menuIsCheck(s32 menuId);
void menuClose(s32 menuId);
void menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void menuSetPosition(s32 menuId, s32 x, s32 y);
void GSfloorGetCurrent(void);
void floorDataBiosGetPtr(void);
s32  floorFieldCameraDataExist(void);
void floorFieldCameraEnable(void);
void floorUnblockMainScript(void);
void floorFieldCameraDisable(void);
void floorBlockMainScript(void);

/* Menu ID constants */
#define MENU_PARTY_INFO 0xC
#define MENU_PEOPLE_EDIT 0xA

/*
  Address: 0x8000BC28 | size: 0x70
  dbgMenuDispChangePartyInfo(void)
  Toggles the party info debug menu display.
*/
s32 dbgMenuDispChangePartyInfo(void) {
    if (menuIsCheck(MENU_PARTY_INFO)) {
        menuClose(MENU_PARTY_INFO);
    } else {
        menuOpenCustom(MENU_PARTY_INFO, 0, 0, 0, 1, 0, 0);
        menuSetPosition(MENU_PARTY_INFO, 0x190, 0x28);
    }
    return 0;
}

/*
  Address: 0x8000BC98 | size: 0x88
  dbgMenuPeopleOpenEdit(void)
  Opens or closes the people edit debug menu.
*/
s32 dbgMenuPeopleOpenEdit(void) {
    GSfloorGetCurrent();
    floorDataBiosGetPtr();
    
    if (menuIsCheck(MENU_PEOPLE_EDIT)) {
        if (floorFieldCameraDataExist()) {
            floorFieldCameraEnable();
        }
        menuClose(MENU_PEOPLE_EDIT);
        floorUnblockMainScript();
    } else {
        floorFieldCameraDisable();
        menuOpenCustom(MENU_PEOPLE_EDIT, 0, 0, 0, 0, 0, 0);
        floorBlockMainScript();
    }
    return 0;
}
