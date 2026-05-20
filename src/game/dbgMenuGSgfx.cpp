// Decompiled from: dbgMenuGSgfx.cpp
// Address range: 0x8000B344..0x8000B3F8 | size: 0xB4

/* Forward declarations */
s32  menuIsCheck(s32 menuId);
void menuClose(s32 menuId);
void menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);
void menuSetPosition(s32 menuId, s32 x, s32 y);
s32  GSgfxLayerGetStatsRenderMode(void);
void GSgfxLayerSetStatsRenderMode(s32 mode);

/* Menu ID constant */
#define MENU_DBG_GSGFX 8

/*
  Address: 0x8000B344 | size: 0x70
  dbgMenuGSgfxChangeDisp(void)
  Toggles the GSgfx debug menu display.
*/
s32 dbgMenuGSgfxChangeDisp(void) {
    if (menuIsCheck(MENU_DBG_GSGFX)) {
        menuClose(MENU_DBG_GSGFX);
    } else {
        menuOpenCustom(MENU_DBG_GSGFX, 0, 0, 0, 1, 0, 0);
        menuSetPosition(MENU_DBG_GSGFX, 0x17c, 0x20);
    }
    return 0;
}

/*
  Address: 0x8000B3B4 | size: 0x44
  dbgMenuLayerFifoDisp(void)
  Toggles the layer FIFO stats render mode.
*/
s32 dbgMenuLayerFifoDisp(void) {
    s32 mode = GSgfxLayerGetStatsRenderMode();
    if (mode == 0) {
        GSgfxLayerSetStatsRenderMode(1);
    } else {
        GSgfxLayerSetStatsRenderMode(0);
    }
    return 0;
}
