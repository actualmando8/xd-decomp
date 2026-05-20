// Decompiled from: flashmenuTest.cpp
// Address range: 0x8000FDA8..0x8000FFF0 | size: 0x248

s32     winSpriteGetLayerID(void* window, void* data);
void    winSpriteSetDisp(void* data, s32 disp);
void    windowDrawSprite(void* sprite, s32 layer, s16 spriteId, s32 flags, void* window, s32 layer2);
void    menuClose(s32 menuId);
void    menuOpen(s32 menuId, s32 param);
void    FlashSystemSetLoopFlag(s32 flag, s32 value);

/* Global data */
static f32 lbl_804E7E68[] = { 0.0f, 0.0f };
static const s16 lbl_804E7E70[] = { 0x02E1, 0x02E2, 0x02E3, 0x02E4 };
static const u8  lbl_804E7E78[] = { 0x01, 0x01, 0x01, 0x01 };
static const u8  lbl_804E7E7C = 0x01;
static u8        lbl_804EA6F0[8];

/*
  Address: 0x8000FDA8 | size: 0x1D0
  fn_8000FDA8(void* window, void* data)
  Flash menu test drawing function. Dispatches based on data->field_0x6 type.
  Types 0x68F-0x698 control various sprite display states.
  Type 0x698 draws 4 sprites with position from lbl_804E7E68.
*/
s32 fn_8000FDA8(void* window, void* data) {
    s32 layer = winSpriteGetLayerID(window, data);
    s16 type = data->field_0x6;
    
    if (type == 0x155) {
        winSpriteSetDisp(data, lbl_804E7E7C);
    }
    else if (type == 0x68F) {
        winSpriteSetDisp(data, lbl_804E7E78[0]);
    }
    else if (type == 0x691) {
        winSpriteSetDisp(data, lbl_804E7E78[2]);
    }
    else if (0x691 < type && type < 0x698) {
        winSpriteSetDisp(data, lbl_804E7E78[3]);
    }
    else if (type == 0x698) {
        if (lbl_804EA6F0[0]) {
            // Draw 4 sprites with positions from lbl_804E7E68
            for (s32 i = 0; i < 4; i++) {
                windowDrawSprite(
                    (void*)((s32)lbl_804E7E68 + i * 4),
                    layer, lbl_804E7E70[i], 0, window, layer
                );
            }
        }
    }
    else if (0x68F <= type && type < 0x691) {
        winSpriteSetDisp(data, lbl_804E7E78[1]);
    }
    
    return 0;
}

/*
  Address: 0x8000FF78 | size: 0x24
  fn_8000FF78()
  Closes menu 0x4E.
*/
s32 fn_8000FF78(void) {
    menuClose(0x4E);
    return 0;
}

/*
  Address: 0x8000FF9C | size: 0x28
  fn_8000FF9C()
  Opens menu 0x4E with param 1.
*/
s32 fn_8000FF9C(void) {
    menuOpen(0x4E, 1);
    return 0;
}

/*
  Address: 0x8000FFC4 | size: 0x2C
  menuFlashTestInit()
  Sets flash system loop flag for address 0x17883000.
*/
s32 menuFlashTestInit(void) {
    FlashSystemSetLoopFlag(0x17883000, 1);
    return 0;
}
