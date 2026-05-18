// Decompiled from: menuGBAC.cpp
// Address range: 0x8004E54C..0x8004FB68 | size: 0x161C
// PowerPC 750CL / Gekko (GameCube)
// Compiler: Metrowerks CodeWarrior

/*
  Calling convention: r3-r7 args, r3 return
  SDA21 globals accessed via r2 base with small offsets
*/

#include <stddef.h>

// Forward declarations for external functions
void    AGB_FileBuffAlloc(void);
void    AGB_FileBuffFree(void);
void    AGB_Terminate_init(void);
s32     AGB_Prepare(const char* bin_name);
s32     AGB_Terminate(s32 channel);
s32     AGB_IsComplete(s32 channel);
s32     AGB_GetStatus(s32 channel);
s32     AGB_Upload(s32 channel, u32 param);
s32     AGB_GetPokemon(s32 channel, void* hero, void* out);
void    gbaCommandSetKeyState(s32 cmd, s32 state);
s32     gbaCommandIsConnected(s32 channel);
s32     gba_SIProbe(s32 channel);
s32     pokecoloGetCountryCode(void);
void    GSthreadSwitch(void);
void    GSsndPlayNow(s32 id);
s32     GSinputIsConnected(s32 port);
s32     GSgfxVideoGetVsyncRate(void);
float   GSgfxVideoGetLastRenderTime(void);
void    menuSetEnablePort(s32 port, s32 enable);
s32     menuGetEnablePort(void);
s32     menuIsCheck(s32 id);
void    menuCloseCustom(s32 id, s32 param0, s32 param1);
void    menuOpen(s32 id, s32 param);
void    menuCB_MessageDispOn(s32 id, s32 type);
void    menuCB_MessageDispOff(void);
s32     menuCB_MessageDispCheck(void);
void    menuCB_SE_Play(s32 id);
void    menuCBRule_CheckHero(void* hero);
void    menuCBRule_ErrorFlagSet(void* hero, s32 flag);
void    menuCB_Pokemon_ErrorDisp(void* hero, s32 flag);
void    msgctrlSetValue(s32 id, s32 value);
void*   windowGetKeyInfo(void);
void*   savedataGetStatus(s32 slot, s32 type);
void*   savedataBiosGetNowSavedataPtr(void);
void*   savedataBiosGetGamedataPtr(void);
void*   gamedataBiosGetGamedataAtttestPtr(void);
s32     gamedataAttestBiosGetLangareaId(void);
void    heroInit(void* src);
void    heroBiosCopy(void* dst, void* src);

// Type definitions
typedef enum _MENU_GBAC_TYPE {
    MENU_GBAC_TYPE_0 = 0,
    MENU_GBAC_TYPE_1 = 1,
    MENU_GBAC_TYPE_2 = 2,
    MENU_GBAC_TYPE_3 = 3,
    MENU_GBAC_TYPE_4 = 4,
} _MENU_GBAC_TYPE;

typedef enum _GBA_PHASE {
    GBA_PHASE_0 = 0,
    GBA_PHASE_1 = 1,
    GBA_PHASE_2 = 2,
    GBA_PHASE_3 = 3,
    GBA_PHASE_4 = 4,
    GBA_PHASE_5 = 5,
    GBA_PHASE_6 = 6,
    GBA_PHASE_7 = 7,
} _GBA_PHASE;

typedef enum _GBA_WAIT_FLAG {
    GBA_WAIT_FLAG_BIT29 = 0x20000000,  // bit 29
    GBA_WAIT_FLAG_BIT30 = 0x40000000,  // bit 30
    GBA_WAIT_FLAG_BIT31 = 0x80000000,  // bit 31
} _GBA_WAIT_FLAG;

typedef struct Hero Hero;

/*
  _GBA_Connect_WORK structure (inferred from assembly offsets)
  Size: at least 0x50 bytes based on gbaConectGBA_Connect_WORK BSS size 0x4C
*/
typedef struct _GBA_Connect_WORK {
    u32 phase[4];         // +0x00: Phase for each of 4 channels
    u32 field_0x10;       // +0x10
    u32 field_0x14;       // +0x14
    u32 field_0x18;       // +0x18
    u32 field_0x1C;       // +0x1C
    u8  field_0x20;       // +0x20
    u8  channel;          // +0x21: GBA channel index
    u8  padding_0x22[0x02];
    u32 menu_type;        // +0x24: _MENU_GBAC_TYPE value
    u32 field_0x28;       // +0x28: Status/timeout flag
    u8  field_0x2C;       // +0x2C
    u8  field_0x2D;       // +0x2D
    u8  field_0x2E;       // +0x2E
    u8  field_0x2F;       // +0x2F
    u8  field_0x30;       // +0x30
    u8  field_0x31;       // +0x31
    u8  field_0x32;       // +0x32
    u8  field_0x33;       // +0x33
    u8  padding_0x34[0x1C];
    u32 field_0x50;       // +0x50
    u32 field_0x54;       // +0x54
    u32 field_0x58;       // +0x58
    u32 field_0x5C;       // +0x5C
} _GBA_Connect_WORK;

// SDA21-relative globals
static u16 GBA_ROM_VERSION_FLAG[4];  // .sdata offset 0x18
static u8  _menu_ports[4] = { 0x01, 0x02, 0x04, 0x08 };  // .sdata offset 0x0
static u8  chans[4] = { 0x01, 0x02, 0x03, 0x00 };        // .sdata offset 0x4
static u16 gba_player_number[4] = { 0x0001, 0x0002, 0x0003, 0x0000 };  // .sdata offset 0x8
static u8  _mes_flag_type;  // _mes_flag_type@sda21

// BSS globals
static _GBA_Connect_WORK gbaConectGBA_Connect_WORK;  // .bss size 0x4C

// ROData - Binary name tables
static const char* const gba_bin_name[2] = {
    "maxbtl.bin",   // "@2221"
    "maxcng.bin",   // "@2222"
};

// Language-specific binary names (indexed by country code)
static const char* const gba_bin_name_english[2] = {
    "maxbtl_english.bin",
    "maxcng_english.bin",
};
static const char* const gba_bin_name_france[2] = {
    "maxbtl_france.bin",
    "maxcng_france.bin",
};
static const char* const gba_bin_name_germany[2] = {
    "maxbtl_germany.bin",
    "maxcng_germany.bin",
};
static const char* const gba_bin_name_italy[2] = {
    "maxbtl_italy.bin",
    "maxcng_italy.bin",
};
static const char* const gba_bin_name_spain[2] = {
    "maxbtl_spain.bin",
    "maxcng_spain.bin",
};

// Array of pointers to language-specific binary name arrays
// lbl_8032EBD8 in .data
static const char* const (*const gba_bin_name_by_language[6])[2] = {
    gba_bin_name,
    gba_bin_name_english,
    gba_bin_name_france,
    gba_bin_name_germany,
    gba_bin_name_italy,
    gba_bin_name_spain,
};

// ROData - Initial phase table
// _initial_phase: 8 entries of 4 words each (for 4 channels)
// Format: [channel0, channel1, channel2, channel3] per menu type
static const u32 _initial_phase[8][4] = {
    { 0x00000008, 0x00000001, 0x00000000, 0x00000000 },  // type 0
    { 0x00000008, 0x00000001, 0x00000001, 0x00000000 },  // type 1
    { 0x00000008, 0x00000001, 0x00000001, 0x00000001 },  // type 2
    { 0x00000001, 0x00000001, 0x00000001, 0x00000001 },  // type 3
    { 0x00000001, 0x00000001, 0x00000001, 0x00000001 },  // type 4
    { 0x00000001, 0x00000001, 0x00000001, 0x00000001 },  // type 5
    { 0x00000001, 0x00000001, 0x00000001, 0x00000001 },  // type 6
    { 0x00000001, 0x00000001, 0x00000001, 0x00000001 },  // type 7
};

// Callback function table (referenced as _CB and _CB+0x100)
// extern void (*const _CB[...])(void);  // Function pointer table

// ============================================================================
// Helper functions (local / static)
// ============================================================================

/*
  Address: 0x8004FAC0 | size: 0x40
  _message(unsigned long msgId, long typeOffset)
  Displays a message with type 0.
*/
static s32 _message(u32 msgId, s32 typeOffset) {
    msgctrlSetValue(0x2f, typeOffset + 1);
    return menuCB_MessageDispOn(msgId, 0);
}

/*
  Address: 0x8004FA80 | size: 0x40
  _message_type2(unsigned long msgId, long typeOffset)
  Displays a message with type 1.
*/
static s32 _message_type2(u32 msgId, s32 typeOffset) {
    msgctrlSetValue(0x2f, typeOffset + 1);
    return menuCB_MessageDispOn(msgId, 1);
}

/*
  Address: 0x8004F9D8 | size: 0xA8
  _menuWait(float seconds)
  Waits for the specified number of seconds using frame timing.
  Uses floating point registers f28-f31 (saved on stack).
*/
static void _menuWait(float seconds) {
    // TODO: Verify floating point constants "@2827" and "@2829"
    // "@2827" appears to be a small float increment
    // "@2829" appears to be a double-precision accumulator
    static const float field_@2827 = 0.0f;  // placeholder
    static const double field_@2829 = 0.0;   // placeholder

    double accumulator = field_@2829;
    float increment = field_@2827;
    float elapsed = 0.0f;

    while (elapsed < seconds) {
        GSthreadSwitch();
        s32 vsyncRate = GSgfxVideoGetVsyncRate();
        double timeBase = (double)vsyncRate;
        float lastRender = GSgfxVideoGetLastRenderTime();
        float delta = lastRender / (float)timeBase;
        increment += delta;
        elapsed = (float)accumulator;
    }
}

/*
  Address: 0x8004F74C | size: 0xC0
  _waitComplete(_GBA_Connect_WORK* work)
  Waits for GBA operation to complete. Returns status code.
  
  Return values:
    - Result of AGB_GetStatus() on completion
    - 4 on timeout or B-button press
    - 2 on B-button press during wait (before termination)
*/
static s32 _waitComplete(_GBA_Connect_WORK* work) {
    work->field_0x28 = 0;

    while (AGB_IsComplete(work->channel) == 0) {
        // Check for menu close request (id 0x2a)
        if (menuIsCheck(0x2a)) {
            GSthreadSwitch();
            continue;
        }

        // Check for B-button press
        void* keyInfo = windowGetKeyInfo();
        // TODO: Verify key info struct layout - offset 0x4, bit 26
        u16 keys = ((u16*)keyInfo)[2];
        if ((keys >> 26) & 1) {
            work->field_0x28 = 2;
            AGB_Terminate(work->channel);
            return 4;
        }

        // Check for timeout flag (field_0x28 == 8)
        if (work->field_0x28 == 8) {
            return 4;
        }

        GSthreadSwitch();
    }

    work->field_0x28 = 0;
    return AGB_GetStatus(work->channel);
}

/*
  Address: 0x8004F80C | size: 0x1CC
  _waitAction(_GBA_Connect_WORK* work, _GBA_WAIT_FLAG flags)
  Waits for GBA action with configurable flags.
  
  Flags (extracted from bits 29-31 of flags parameter):
    - bit 31 (GBA_WAIT_FLAG_BIT31): Check message display / A-button
    - bit 30 (GBA_WAIT_FLAG_BIT30): Check SI probe status
    - bit 29 (GBA_WAIT_FLAG_BIT29): Additional SI probe check

  Return values:
    - 0 on various error conditions
    - 1 on successful completion
*/
static s32 _waitAction(_GBA_Connect_WORK* work, u32 flags) {
    s32 siProbeOk = 1;

    // Initial SI probe check
    if (work->channel >= 0) {
        s32 probeResult = gba_SIProbe(work->channel);
        if (probeResult - 4 != 0) {
            siProbeOk = 0;
        }
    }

    u32 flag_bit29 = (flags >> 29) & 1;
    u32 flag_bit31 = flags >> 31;
    u32 flag_bit30 = (flags >> 30) & 1;

    while (1) {
        // Check for menu close request
        if (menuIsCheck(0x2a)) {
            GSthreadSwitch();
            continue;
        }

        // B-button check (only if bit 30 set)
        if (flag_bit30) {
            void* keyInfo = windowGetKeyInfo();
            u16 keys = ((u16*)keyInfo)[2];
            if ((keys >> 26) & 1) {
                work->field_0x28 = 2;
                return 0;
            }
        }

        // Timeout check (field_0x28 == 8)
        if (work->field_0x28 == 8) {
            return 0;
        }

        // Check phase values for disconnection (value == 7)
        if (work->phase[0] == 7) return 0;
        if (work->phase[1] == 7) return 0;
        if (work->phase[2] == 7) return 0;
        if (work->phase[3] == 7) return 0;

        // Message display / A-button check (only if bit 31 set)
        if (flag_bit31) {
            s32 msgResult = menuCB_MessageDispCheck();
            s8 msgByte = (s8)msgResult;
            if (msgByte != 0) {
                work->field_0x28 = 1;
                return 1;
            }
            // Check A-button (bit 27 of key info)
            void* keyInfo = windowGetKeyInfo();
            u16 keys = ((u16*)keyInfo)[2];
            if ((keys >> 27) & 1) {
                if (msgByte == -1) {
                    work->field_0x28 = 1;
                    return 1;
                }
            }
        }

        // SI probe check (only if bit 29 set)
        if (flag_bit29) {
            s32 probeResult = gba_SIProbe(work->channel);
            if (probeResult == 0x80) {
                // Error condition, continue looping
            } else if (siProbeOk) {
                if (probeResult - 4 != 0) {
                    // Probe failed
                } else {
                    work->field_0x28 = 4;
                    return 1;
                }
            } else {
                if (probeResult - 4 != 0) {
                    siProbeOk = 1;
                }
            }
        }

        GSthreadSwitch();
    }
}

/*
  Address: 0x8004F6A0 | size: 0xAC
  _checkDisconnect(_GBA_Connect_WORK* work)
  Checks if any GBA has disconnected.
  
  Returns 1 if disconnection detected, 0 otherwise.
  Sets phase to 7 and field_0x28 to 8 when disconnection found.
*/
static s32 _checkDisconnect(_GBA_Connect_WORK* work) {
    s32 disconnected = 0;
    const u8* ports = _menu_ports;
    _GBA_Connect_WORK* workPtr = work;

    for (s32 i = 0; i < 3; i++) {
        u32 phase = workPtr->phase[0];
        if (phase != 5 && phase != 4) {
            // Check connection
            s32 channel = i + 1;
            if (!gbaCommandIsConnected(channel)) {
                s32 enabled = menuGetEnablePort();
                u8 portMask = ports[0];
                enabled &= ~portMask;
                menuSetEnablePort(enabled & 0xFFFFFF);
                workPtr->phase[0] = 7;
                work->field_0x28 = 8;
            }
        }
        if (workPtr->phase[0] == 7) {
            disconnected = 1;
        }
        workPtr = (_GBA_Connect_WORK*)((u32)workPtr + 4);
        ports++;
    }

    return disconnected;
}

/*
  Address: 0x8004F524 | size: 0x17C
  _showDisconnected(_GBA_Connect_WORK* work)
  Shows disconnection message and waits for user acknowledgment.
  
  Returns 1 on success, 0 on failure.
  Sets field_0x28 to 8 on completion.
*/
static s32 _showDisconnected(_GBA_Connect_WORK* work) {
    s32 foundChannel = 0;
    _mes_flag_type = 0;

    // Wait for disconnect to be confirmed (up to 0xf iterations)
    s32 timeout = 0;
    while (_checkDisconnect(work) == 0) {
        GSthreadSwitch();
        timeout++;
        if (timeout >= 0xf) break;
    }

    GSsndPlayNow(0x13);

    // Find which channel has phase == 7
    foundChannel = 0;
    if (work->phase[0] == 7) { foundChannel = 1; }
    else if (work->phase[1] == 7) { foundChannel = 2; }
    else if (work->phase[2] == 7) { foundChannel = 3; }
    else if (work->phase[3] == 7) { foundChannel = 4; }

    if (foundChannel > 3) {
        // Check timeout flag
        if ((work->field_0x28 >> 28) & 1) {
            return 0;
        }
    } else {
        s32 enabled = menuGetEnablePort();
        menuSetEnablePort((enabled | 1) & 0xFFFFFF);

        s32 msgId;
        if (foundChannel == 0) {
            msgId = 0x4438;
        } else {
            if (work->menu_type == 3) {
                if (GSinputIsConnected(1)) {
                    msgId = 0x442b;
                } else {
                    msgId = 0x442d;
                }
            } else {
                msgId = 0x442b;
            }
        }

        _mes_flag_type = 1;
        msgctrlSetValue(0x2f, foundChannel + 1);
        menuCB_MessageDispOn(msgId, 1);

        // Wait for acknowledgment if message is 0x4438 or 0x442d
        if (msgId == 0x4438 || msgId == 0x442d) {
            while (1) {
                GSthreadSwitch();
                if (GSinputIsConnected(1)) break;
            }
        }

        work->field_0x28 = 8;
        return 1;
    }

    return 0;
}

/*
  Address: 0x8004F44C | size: 0xD8
  _error(_GBA_Connect_WORK* work, unsigned long msgId, _GBA_PHASE phase)
  Displays an error message and handles error recovery.
  
  Returns 0 on success, 1 on failure/loop continuation.
*/
static s32 _error(_GBA_Connect_WORK* work, u32 msgId, _GBA_PHASE phase) {
    s32 showResult = _showDisconnected(work);
    if (showResult != 0) {
        // Extract bit 28-28 from menu_type, compute sign bit trick
        s32 bit28 = (work->menu_type >> 28) & 1;
        s32 val = (-bit28) | bit28;  // Metrowerks idiom for conditional negation
        s32 result = val >> 31;
        return result;
    }

    work->phase[work->channel] = phase;
    _message(msgId, work->channel);

    if ((work->menu_type >> 28) & 1) {
        // Wait with flag 0x7
        s32 waitResult = _waitAction(work, 7);
        if (waitResult != 0) {
            return 1;
        }
    } else {
        // Wait with flag 0x1
        _waitAction(work, 1);
    }

    AGB_Terminate(work->channel);
    return 0;
}

/*
  Address: 0x8004F350 | size: 0xFC
  _poweroff(_GBA_Connect_WORK* work, _GBA_PHASE phase)
  Powers off GBA connection and shows disconnection message.
  
  Returns 0 on success.
*/
static s32 _poweroff(_GBA_Connect_WORK* work, _GBA_PHASE phase) {
    s32 enabled = menuGetEnablePort();
    menuSetEnablePort((enabled | 1) & 0xFFFFFF);

    s32 showResult = _showDisconnected(work);
    if (showResult == 0) {
        work->phase[work->channel] = phase;
    }

    if (_mes_flag_type != 1) {
        if (work->menu_type == 3) {
            s32 msgId;
            if (GSinputIsConnected(1)) {
                msgId = 0x442c;
            } else {
                msgId = 0x442d;
            }

            menuCB_MessageDispOn(msgId, 1);

            if (msgId == 0x442d) {
                while (1) {
                    GSthreadSwitch();
                    if (GSinputIsConnected(1)) break;
                }
            }
        } else {
            menuCB_MessageDispOn(0x442c, 1);
        }

        AGB_Terminate(work->channel);
        return 0;
    }

    AGB_Terminate(work->channel);
    return 0;
}

/*
  Address: 0x8004EFDC | size: 0x15C
  _check_langarea(unsigned char langareaId)
  Checks if the given language/area ID matches the current save data.
  
  Returns 1 if match, 0 if no match or error.
  
  Uses jump tables for language area mapping.
  The jump table maps language area IDs to expected values:
    0 -> 1, 1 -> 2, 2 -> 4, 3 -> 5, 4 -> 3, 5 -> 6, 6 -> 1, 7 -> 6
*/
static s32 _check_langarea(u8 langareaId) {
    s32 countryCode = pokecoloGetCountryCode();

    if (countryCode < 0 || countryCode >= 3) {
        // Out of range country code - use fn_8004FB00 for comparison
        if (langareaId > 7) {
            return 0;
        }

        // Jump table for non-standard countries
        // jumptable_8032EC08 maps langareaId to expected values
        static const s32 langarea_map[8] = { 1, 2, 4, 5, 3, 6, 1, 6 };
        s32 expected = langarea_map[langareaId];

        s32 actual = fn_8004FB00();
        return (actual == expected) ? 1 : 0;
    }

    if (countryCode == 0) {
        // Country code 0: use direct jump table
        if (langareaId > 7) {
            return 0;
        }

        // "@2658" jump table - maps to return values directly
        static const s32 direct_map[8] = { 1, 2, 4, 5, 3, 6, 1, 6 };
        s32 expected = direct_map[langareaId];

        void* savePtr = savedataBiosGetNowSavedataPtr();
        if (savePtr == 0) return 0;

        void* gamePtr = savedataBiosGetGamedataPtr();
        if (gamePtr == 0) return 0;

        void* attestPtr = gamedataBiosGetGamedataAtttestPtr();
        if (attestPtr == 0) return 0;

        s32 actual = gamedataAttestBiosGetLangareaId();
        actual &= 0xFFFFFF;
        return (actual == expected) ? 1 : 0;
    }

    // countryCode >= 1 and <= 2: use gba_bin_name_by_language
    if (langareaId > 7) {
        return 0;
    }

    static const s32 langarea_map2[8] = { 1, 2, 4, 5, 3, 6, 1, 6 };
    s32 expected = langarea_map2[langareaId];

    void* savePtr = savedataBiosGetNowSavedataPtr();
    if (savePtr == 0) return 0;

    void* gamePtr = savedataBiosGetGamedataPtr();
    if (gamePtr == 0) return 0;

    void* attestPtr = gamedataBiosGetGamedataAtttestPtr();
    if (attestPtr == 0) return 0;

    s32 actual = gamedataAttestBiosGetLangareaId();
    actual &= 0xFFFFFF;
    return (actual == expected) ? 1 : 0;
}

/*
  Address: 0x8004F138 | size: 0x218
  _open_menu(_MENU_GBAC_TYPE type, unsigned long flags, long channel)
  Opens the GBA menu with the specified type and initializes phase table.
  
  Returns the work struct pointer (as s32 for compatibility).
*/
static _GBA_Connect_WORK* _open_menu(_MENU_GBAC_TYPE type, u32 flags, s32 channel) {
    u8 chanByte = chans[channel];
    _GBA_Connect_WORK* work = &gbaConectGBA_Connect_WORK;

    work->menu_type = flags;
    work->channel = chanByte;

    // Set up phase values based on menu type
    if (type == 0) {
        work->field_0x30 = 1;
        work->field_0x31 = 2;
        work->field_0x32 = 0;
        work->field_0x33 = 0;
    } else if (type == 1) {
        work->field_0x30 = 2;
        work->field_0x31 = 4;
        work->field_0x32 = 4;
        work->field_0x33 = 0;
    } else if (type == 2) {
        work->field_0x30 = 1;
        work->field_0x31 = 2;
        work->field_0x32 = 0;
        work->field_0x33 = 0;
    } else if (type >= 0 && type < 4) {
        work->field_0x30 = 4;
        work->field_0x31 = 0;
        work->field_0x32 = 0;
        work->field_0x33 = 0;
    }

    // Initialize phase table from _initial_phase
    const u32* phaseTable = &_initial_phase[type][0];
    for (s32 i = 0; i < 4; i++) {
        u8 chanIdx = chans[i];
        s32 chanSigned = (s8)chanIdx;
        s32 idx = chanSigned * 4;

        if (chanSigned >= 0) {
            work->phase[chanSigned] = phaseTable[idx];
        } else {
            s32 currentVal = work->phase[chanSigned];
            if (currentVal == 1) {
                work->phase[chanSigned] = 5;
            }
        }

        // Set completion flags
        if (i == 0) work->field_0x48 = 0;
        if (i == 1) work->field_0x49 = 0;
        if (i == 2) work->field_0x4A = 0;
        if (i == 3) work->field_0x4B = 0;

        chans++;
    }

    menuCB_SE_Play(0x14);
    menuOpen(0xb0, 0);
    menuCB_MessageDispOn(1, 0);

    return work;
}

/*
  Address: 0x8004FB00 | size: 0x68
  fn_8004FB00()
  Gets the language/area ID from current save data attestation.
  Returns 0xFF if no valid save data found, otherwise the langarea ID.
  Special case: if langarea ID == 8, returns 2.
*/
s32 fn_8004FB00(void) {
    s32 result = 0xFF;

    void* savePtr = savedataBiosGetNowSavedataPtr();
    if (savePtr == 0) return result;

    void* gamePtr = savedataBiosGetGamedataPtr();
    if (gamePtr == 0) return result;

    void* attestPtr = gamedataBiosGetGamedataAtttestPtr();
    if (attestPtr == 0) return result;

    s32 langareaId = gamedataAttestBiosGetLangareaId();
    result = langareaId;

    // Special case: langareaId == 8 maps to 2
    if (langareaId == 8) {
        result = 2;
    }

    return result;
}

// ============================================================================
// Public API functions (global)
// ============================================================================

/*
  Address: 0x8004E54C | size: 0x24
  menuGBACGetRomVer(u32 index)
  Gets the ROM version flag at the given index (0-3).
  Returns 0 if index is out of range.
*/
u16 menuGBACGetRomVer(u32 index) {
    if (index > 3) {
        return 0;
    }
    return GBA_ROM_VERSION_FLAG[index];
}

/*
  Address: 0x8004E570 | size: 0x98
  menuGBACSetRomVer(u16 value, u32 channel)
  Sets ROM version flags.
  
  If channel is 0-3: sets GBA_ROM_VERSION_FLAG[channel] = value
  If channel is 0xFFFF: resets key states for channels 1-4
  Otherwise: clears all ROM version flags
*/
void menuGBACSetRomVer(u16 value, u32 channel) {
    if (channel < 4) {
        if (channel >= 0) {
            GBA_ROM_VERSION_FLAG[channel] = value;
        }
    } else {
        GBA_ROM_VERSION_FLAG[0] = 0;
        GBA_ROM_VERSION_FLAG[1] = 0;
        GBA_ROM_VERSION_FLAG[2] = 0;
        GBA_ROM_VERSION_FLAG[3] = 0;
    }

    // Reset key states if channel == 0xFFFF
    if (channel == 0xFFFF) {
        gbaCommandSetKeyState(1, 0);
        gbaCommandSetKeyState(2, 0);
        gbaCommandSetKeyState(3, 0);
        gbaCommandSetKeyState(4, 0);
    }
}

/*
  Address: 0x8004E608 | size: 0xE0
  openMenuGBA(_MENU_GBAC_TYPE type, u32 flags, Hero** heroOut)
  Main entry point for opening the GBA connection menu.
  
  Allocates file buffer, calls main flow, cleans up.
  Returns the result of mainFlow, or -1 if heroOut was NULL, 0 otherwise.
*/
s32 openMenuGBA(_MENU_GBAC_TYPE type, u32 flags, Hero** heroOut) {
    s32 portEnabled = menuSetEnablePort(1);
    AGB_FileBuffAlloc();

    s32 result = _mainFlow(type, flags, heroOut);

    menuCB_MessageDispOn(0, 0);  // Placeholder for winMsgClose(0)
    s32 checkResult = menuIsCheck(0xb0);
    if (checkResult) {
        menuCB_MessageDispOff();
        menuCB_SE_Play(0x15);
        menuCloseCustom(0xb0, 0, 1);
    }

    menuSetEnablePort(portEnabled);
    portEnabled = 0;

    // Call AGB_Terminate 3 times (for cleanup)
    for (s32 i = 0; i < 3; i++) {
        AGB_Terminate(portEnabled);
        portEnabled++;
    }

    AGB_FileBuffFree();

    return (heroOut != 0) ? result : -1;
}

/*
  Address: 0x8004E6E8 | size: 0x8F4
  _mainFlow(_MENU_GBAC_TYPE type, unsigned long flags, Hero** heroOut)
  Main state machine for GBA connection flow.
  
  Handles:
  - GBA preparation and bin file loading
  - Menu opening and player selection
  - Pokemon data retrieval
  - Language/area validation
  - Hero data initialization and copying
  - Multiplayer connection management
*/
s32 _mainFlow(_MENU_GBAC_TYPE type, u32 flags, Hero** heroOut) {
    _GBA_Connect_WORK* work;
    s32 bin_index = 0;
    s32 retry_counter = 0;

    AGB_Terminate_init();

    // Extract flag bits
    s32 flag_bit31 = (flags >> 31) & 1;
    s32 flag_bit30 = (flags >> 30) & 1;

    if (flag_bit31 == 1) {
        bin_index = 1;
    }
    if (flag_bit30 == 2) {
        bin_index = 0;
    }

    // Load GBA bin file based on country code
    s32 countryCode = pokecoloGetCountryCode();
    const char** bin_names = gba_bin_name;

    if (countryCode == 1) {
        bin_names = (const char**)gba_bin_name_by_language[bin_index];
    } else if (countryCode >= 0 && countryCode < 1) {
        bin_names = gba_bin_name;
    }

    // Prepare GBA communication
    if (bin_names != NULL) {
        while (1) {
            s32 prepResult = AGB_Prepare(bin_names[bin_index]);
            if (prepResult != 0) break;
            GSthreadSwitch();
        }
    }

    // Open menu
    work = _open_menu(type, flags, 0);

    s32* work_phases = work->phase;
    s32 flag_bit27 = (flags >> 27) & 1;

    if (flag_bit27) {
        if (type == 0 || type == 2) {
            void* saveStatus = savedataGetStatus(0, 2);
            s32 is_special = (flag_bit30 != 0);

            work->field_0x21 = 0;
            work->field_0x28 = (is_special) ? 8 : 0;

            if (saveStatus) {
                _message(0x4437, 0);
                _menuWait(1.0f);

                if (!menuCBRule_CheckHero(saveStatus)) {
                    menuCBRule_ErrorFlagSet(saveStatus, 0);
                    menuCB_MessageDispOff();
                    menuCB_SE_Play(0x15);
                    menuCloseCustom(0xb0, 0, 1);
                    menuCB_Pokemon_ErrorDisp(saveStatus, 0);
                    return 0;
                }
            }

            if (heroOut != 0 && *heroOut != 0) {
                heroBiosCopy(*heroOut, saveStatus);
            }

            work->phase[0] = 0xa;
        }

        menuGBACSetRomVer(0, -1);

        const u8* chanPtr = chans;
        s32 playerCounter = 0;
        const u16* playerNumPtr = gba_player_number;

        // Main connection loop - simplified placeholder
        // TODO: Complete full decompilation of main flow loop
        while (playerCounter < 4) {
            // ... existing connection logic ...
            chanPtr++;
            playerCounter++;
            playerNumPtr += 2;
        }
    }

    return 1;
}
