// Decompiled from: dbgMenuWaza.cpp
// Address range: 0x8000C0F4..0x8000C284 | size: 0x190

/* Forward declarations */
s32  menuIsCheck(s32 menuId);
void menuClose(s32 menuId);
void menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void menuSetPosition(s32 menuId, s32 x, s32 y);
void GSfloorPop(void);
void GSfloorPush(s32 floorId);
void GSthreadSwitch(void);

/* External data */
extern s32 wazaViewerData[];

/* Menu ID constants */
#define MENU_WAZA_DEBUG 0x15
#define MENU_POKEMON_DEBUG 0x26
#define MENU_WAZA_VIEWER 0x11

/*
  Address: 0x8000C0F4 | size: 0x38
  dbgMenuWazaDebugStop(void)
  Stops the waza viewer debug mode.
*/
s32 dbgMenuWazaDebugStop(void) {
    if (wazaViewerData[0x30 / 4] != 0) {
        GSfloorPop();
    }
    return 0;
}

/*
  Address: 0x8000C12C | size: 0x84
  dbgMenuPokemonDebugSelect(void)
  Toggles the Pokemon debug select menu.
*/
s32 dbgMenuPokemonDebugSelect(void) {
    if (menuIsCheck(MENU_POKEMON_DEBUG)) {
        menuClose(MENU_POKEMON_DEBUG);
    } else {
        wazaViewerData[0x16 / 4] = 0;
        wazaViewerData[0x17 / 4] = 0;
        menuOpenCustom(MENU_POKEMON_DEBUG, 0, 0, 0, 1, 0, 0);
        menuSetPosition(MENU_POKEMON_DEBUG, 0xC, 0xA);
    }
    return 0;
}

/*
  Address: 0x8000C1B0 | size: 0x70
  dbgMenuWazaDebugSelect(void)
  Toggles the waza debug select menu.
*/
s32 dbgMenuWazaDebugSelect(void) {
    if (menuIsCheck(MENU_WAZA_DEBUG)) {
        menuClose(MENU_WAZA_DEBUG);
    } else {
        menuOpenCustom(MENU_WAZA_DEBUG, 0, 0, 0, 1, 0, 0);
        menuSetPosition(MENU_WAZA_DEBUG, 0xC, 0xA);
    }
    return 0;
}

/*
  Address: 0x8000C220 | size: 0x5C
  dbgMenuWazaDebugStart(void)
  Starts the waza viewer debug mode.
*/
s32 dbgMenuWazaDebugStart(void) {
    if (menuIsCheck(MENU_WAZA_VIEWER)) {
        menuClose(MENU_WAZA_VIEWER);
    }
    if (wazaViewerData[0x30 / 4] == 0) {
        GSfloorPush(0x3E7);
        GSthreadSwitch();
    }
    return 0;
}

/*
  Address: 0x8000C27C | size: 0x8
  dbgMenuWazaMain(void)
  Main function - returns 1.
*/
s32 dbgMenuWazaMain(void) {
    return 1;
}
