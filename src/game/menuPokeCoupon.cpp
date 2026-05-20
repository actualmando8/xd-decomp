// Decompiled from: menuPokeCoupon.cpp
// Address range: 0x8000E5AC..0x8000E64C | size: 0xA0

/* Forward declarations */
void menuShopOpen(s32 shopId);
void GSfloorChange(s32 floorId);
void __assert(const char* file, s32 line, const char* msg);

/* SData */
static s32 _menuPokeCouponWork = -1;

/*
  Address: 0x8000E5AC | size: 0xC
  menuPokeCouponExit(void)
  Sets work state to -1 (invalid).
*/
void menuPokeCouponExit(void) {
    _menuPokeCouponWork = -1;
}

/*
  Address: 0x8000E5B8 | size: 0x54
  menuPokeCouponMain(void)
  Main function - opens shop based on work state, then changes floor.
*/
void menuPokeCouponMain(void) {
    switch (_menuPokeCouponWork) {
        case 0:
            menuShopOpen(9);
            break;
        case 1:
            menuShopOpen(10);
            break;
        default:
            break;
    }
    GSfloorChange(0x395);
}

/*
  Address: 0x8000E60C | size: 0x40
  menuPokeCouponInit(void)
  Initializes work state, with assert check for invalid state.
*/
void menuPokeCouponInit(void) {
    if (_menuPokeCouponWork == -1) {
        __assert("menuPokeCoupon.c", 0x3C, "POKECOUPONREFER_INVALID != _menuPokeCouponWork.m_eRefer");
    }
}
