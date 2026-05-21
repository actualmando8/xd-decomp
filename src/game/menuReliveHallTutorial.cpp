// Decompiled from: menuReliveHallTutorial.cpp
// Address range: 0x80098108..0x80098B44 | size: 0xA3C

/*
  CMetaMenu tutorial management for Relive Hall.
  Contains a state machine with 26 states (0-25) for managing tutorial sequences.
*/

/* Forward declarations */
void    windowGetKeyInfo(void);
void    update__6CStateFv(void);
void    GSgfxVideoGetVsyncRate(void);
void    __cvt_fp2unsigned(void);
void    memset(void*, int, int);
void    exec__11CInfoWindowFR9CMetaMenuUlb(void*, void*, u32, s32);

/* Class method - virtual call through vtable */
class CMetaMenu {
public:
    void* vtable;              // 0x0
    void* field_0x04;          // 0x4
    // ... fields ...
    void* field_0x244;         // 0x244 - CInfoWindow pointer
    u16    field_0x274;        // 0x274 - Key code
    u8     field_0x328;        // 0x328 - State pointer
    u8     field_0x32c;        // 0x32c - Initialize flag
    u16    field_0x32e;        // 0x32e - Current state
    void*  field_0x330;        // 0x330 - Vtable for method calls
};

/* State structure */
struct CState {
    u32 state_id;              // 0x0
    u32 field_4;               // 0x4
    u32 field_8;               // 0x8
    u32 field_C;               // 0xC - Sub-state counter
    float field_10;            // 0x10 - Timer
    u32 field_14;              // 0x14
    u32 field_18;              // 0x18
    u8  field_1C[0x64];        // 0x1C - Padding/data
};

/* Static data tables */
static const s16 tbl_2009[] = { 0x0400, 0x0400, 0x0400, 0x0000 };
static const s16 tbl_2016[] = { 0x0010, 0x0000 };
static const s16 tbl_2024[] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0000 };
static const s16 tbl_2031[] = { 0x0002, 0x0002, 0x0002, 0x0002 };
static const s16 tbl_2040[] = { 0x0200, 0x0400, 0x0400 };
static const s16 tbl_2047[] = { 0x0200, 0x0000 };
static const s16 tbl_2054[] = { 0x0001, 0x0010, 0x0040, 0x0000 };
static const s16 tbl_2061[] = { 0x0100, 0x0008, 0x0008, 0x0008, 0x0020, 0x0000 };
static const s16 tbl_2068[] = { 0x0001, 0x0001, 0x0010 };
static const s16 tbl_2075[] = { 0x0002, 0x0010, 0x0000 };
static const s16 tbl_2080[] = { 0x0100, 0x0008, 0x0008, 0x0010, 0x0020 };
static const s16 tbl_2087[] = { 0x0001, 0x0008, 0x0000 };
static const s16 tbl_2092[] = { 0x0004, 0x0000 };
static const s16 tbl_2099[] = { 0x0008, 0x0010, 0x0000 };
static const s16 tbl_2104[] = { 0x0100, 0x0002, 0x0008, 0x0008, 0x0010, 0x0020 };
static const s16 tbl_2118[] = { 0x0100, 0x0010, 0x0020 };
static const s16 tbl_2125[] = { 0x0001, 0x0010, 0x0000 };
static const s16 tbl_2132[] = { 0x0040, 0x0000 };
static const s16 tbl_2139[] = { 0x0010, 0x0002, 0x0010, 0x000A, 0x0010 };
static const s16 tbl_2147[] = { 0x0020, 0x0002, 0x0000 };

/* Float constants */
static const float const_0_9 = 0.9f;
static const float const_0 = 0.0f;
static const double const_4503599627370496 = 4503599627370496.0;

/* Jump table for state machine - function pointers to case labels */
static void (*state_table[])(void) = {
    state_0,   state_1,   state_2,   state_3,
    state_4,   state_5,   state_6,   state_7,
    state_8,   state_9,   state_10,  state_11,
    state_12,  state_13,  state_14,  state_15,
    state_16,  state_17,  state_18,  state_19,
    state_20,  state_21,  state_22,  state_23,
    state_24,  state_25
};

/*
  Address: 0x80098108 | size: 0x974
  CMetaMenu::tutorialManagePrime()
  Main state machine for tutorial management.
  Manages 26 tutorial states with timers and transitions.
*/
s16 tutorialManagePrime__9CMetaMenuFv(CMetaMenu* this) {
    CState* state = (CState*)((u8*)this + 0x160);
    s16 nextState = 0x20;
    
    // Check initialization flag
    if (*(u8*)((u8*)this + 0x328 + 0x15d) != 0) {
        return 0x20;
    }
    
    // Check for key press
    windowGetKeyInfo();
    if (*(s16*)r3 == 0x20) {
        *(u8*)((u8*)this + 0x328 + 0x15d) = 1;
        *(u8*)((u8*)this + 0x328 + 0x15e) = 1;
        return 0x20;
    }
    
    // Increment timer and call virtual method
    state->field_8 += 1;
    ((void(*)())(*(u32**)this + 0x330 >> 2))(this);  // Virtual call at vtable[3]
    if (r3 == 0) {
        return 0;
    }
    
    // Calculate time threshold
    u32 vsync = GSgfxVideoGetVsyncRate();
    double time = (const_4503599627370496 - vsync) * const_0_9;
    u32 threshold = (u32)time;
    
    if (state->field_8 < threshold) {
        return 0;
    }
    
    // Reset timer and update state
    state->field_8 = 0;
    nextState = 0;
    update__6CStateFv();
    
    u32 currentState = state->state_id;
    if (currentState > 0x1A) {
        return 0x10;
    }
    
    // Dispatch to state handler
    state_table[currentState]();
    
    return nextState;
}

/* State 0 handler */
void state_0(void) {
    tutorialMessage__9CMetaMenuFUl(this, 0xD3B8);
    state->field_4 = state->state_id + 1;
    memset(state + 0x18, 0, 0x40);
}

/* State 1 handler - with timer check */
void state_1(void) {
    if (state->field_10 == const_0) {
        tutorialMessage__9CMetaMenuFUl(this, 0xD3B9);
    }
    if (state->field_C < 5) {
        nextState = tbl_2009[state->field_C];
    } else {
        state->field_4 = state->state_id + 1;
        memset(state + 0x18, 0, 0x40);
    }
}

/* States 2-25 follow similar patterns with different tables and message IDs */
// ... (omitted for brevity - each state checks timer, sends message, transitions)

/*
  Address: 0x80098A7C | size: 0xC
  CMetaMenu::tutorialManageUpdate()
  Resets the initialization flag.
*/
void tutorialManageUpdate__9CMetaMenuFv(CMetaMenu* this) {
    *(u8*)((u8*)this + 0x32c) = 0;
}

/*
  Address: 0x80098A88 | size: 0x50
  CMetaMenu::tutorialManage()
  Entry point. Initializes and runs tutorial state machine.
*/
s16 tutorialManage__9CMetaMenuFv(CMetaMenu* this) {
    if (*(u8*)((u8*)this + 0x32c) == 0) {
        *(u8*)((u8*)this + 0x32c) = 1;
        tutorialManagePrime__9CMetaMenuFv(this);
        *(u16*)((u8*)this + 0x32e) = r3;
    }
    return *(u16*)((u8*)this + 0x32e);
}

/*
  Address: 0x80098AD8 | size: 0x6C
  CMetaMenu::tutorialMessage(unsigned long msgId)
  Sends a tutorial message to the info window.
*/
void tutorialMessage__9CMetaMenuFUl(CMetaMenu* this, u32 msgId) {
    exec__11CInfoWindowFR9CMetaMenuUlb(
        (void*)((u8*)this + 0x244),
        this,
        msgId,
        1
    );
    if (*(u16*)((u8*)this + 0x274) == 0x20) {
        // Virtual call at vtable[4]
        ((void(*)())(*(u32**)this + 0x330 >> 2))(this);
        *(u8*)((u8*)this + 0x328 + 0x15d) = 1;
        *(u8*)((u8*)this + 0x328 + 0x15e) = 1;
    }
}
