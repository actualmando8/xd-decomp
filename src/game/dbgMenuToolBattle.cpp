// Decompiled from: dbgMenuToolBattle.cpp
// Address range: 0x8000E64C..0x8000E71C | size: 0xD0

/* Forward declarations */
s32  menuOpen(s32 a, s32 b);
void menuClose(s32 a);
void menuCBDebug_SkipAGBConnection(u32 value);

/* SBSS */
s32 dbgMenuGBAAddCoupon_value;
s32 dbgMenuGBAResetCoupon_on;
s32 dbgMenuGBASetClearFlag_on;
s32 dbgMenuGBAClearCouponFlag_on;

/*
  Address: 0x8000E64C | size: 0x1C
  dbgMenuGBAClearCouponFlag(void)
  Increments the clear coupon flag counter and resets the set clear flag counter.
*/
s32 dbgMenuGBAClearCouponFlag(void) {
    dbgMenuGBAClearCouponFlag_on++;
    dbgMenuGBASetClearFlag_on = 0;
    return 0;
}

/*
  Address: 0x8000E668 | size: 0x14
  dbgMenuGBASetClearFlag(void)
  Increments the set clear flag counter.
*/
s32 dbgMenuGBASetClearFlag(void) {
    dbgMenuGBASetClearFlag_on++;
    return 0;
}

/*
  Address: 0x8000E67C | size: 0x1C
  dbgMenuGBAResetCoupon(void)
  Increments the reset coupon counter and resets the add coupon value.
*/
s32 dbgMenuGBAResetCoupon(void) {
    dbgMenuGBAResetCoupon_on++;
    dbgMenuGBAAddCoupon_value = 0;
    return 0;
}

/*
  Address: 0x8000E698 | size: 0x54
  dbgMenuGBAAddCoupon(void)
  Opens menu 2, and if the result is >= 0, adds it to the coupon value.
*/
s32 dbgMenuGBAAddCoupon(void) {
    s32 result = menuOpen(2, 1);
    menuClose(2);
    if (result >= 0) {
        dbgMenuGBAAddCoupon_value += result;
    }
    return 0;
}

/*
  Address: 0x8000E6EC | size: 0x30
  dbgToolBattleDebugSetAGBConnectionMode(s32 mode)
  Sets the AGB connection mode. Uses bit manipulation to convert to boolean.
*/
s32 dbgToolBattleDebugSetAGBConnectionMode(s32 mode) {
    // cntlzw + srwi + clrlwi implements: (mode != 0) ? 1 : 0
    u32 result = (mode != 0) ? 1 : 0;
    menuCBDebug_SkipAGBConnection(result);
    return 0;
}
