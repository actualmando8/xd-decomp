// Decompiled from: menuCB_Debug.cpp
// Address range: 0x8004A090..0x8004A0A8 | size: 0x18

/* SData */
static u8 _DBG;

/*
  Address: 0x8004A090 | size: 0x18
  menuCBDebug_SkipAGBConnection(u32 value)
  Sets the _DBG flag based on the input value.
  Uses bit counting logic: clz → shift → mask to extract a single bit.
*/
void menuCBDebug_SkipAGBConnection(u32 value) {
    // This implements: _DBG = (value != 0) ? 1 : 0
    // But uses a more complex bit manipulation:
    // clrlwi r0, r3, 24  - mask to lower 8 bits
    // cntlzw r0, r0      - count leading zeros
    // srwi r0, r0, 5     - shift right by 5 (effectively: min(1, value))
    // clrlwi r0, r0, 24  - mask to lower 8 bits
    u8 result = (value != 0) ? 1 : 0;
    _DBG = result;
}
