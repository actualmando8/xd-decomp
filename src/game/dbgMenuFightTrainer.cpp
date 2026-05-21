// dbgMenuFightTrainer.cpp - Debug Menu: Fight Trainer AI Data Editing
// Address: 0x8000C2C0..0x8000DBAC | size: 0x18EC
//
// Functions for editing fight trainer AI parameters through debug menus:
//   - Combo, Item, Move selection, Defense Pokemon, Switching AI
//   - Pokemon party data editing
//   - AI data editing with menu-based input
//   - Helper functions for digit/flag input

#include "global.h"

/* Forward declarations */
void* fightTrainerAiValueAddsubDataBiosGetPtr(u32 id);
void* fightTrainerAiDataBiosGetPtr(u32 id);
void* fightTrainerGetStatus(u32 trainer, u32, u32 status, u32);
void fightTrainerSetStatus(u32 trainer, u32, u32 status, u32 value);
u32 menuOpenCustom(u32 menuId, u32, u32, u32, u32, u32);
u32 menuCloseCustom(u32 menuId, u32, u32);
u32 menuOpen(u32 menuId, u32, u32);
u32 menuGetCursorItemID(u32 menuId);
u32 menuSubOpenNumberInput(u32, u32, u32, u32, u32, u32);
void menuSubCloseNumberInput();
void menuSubOpenYesNo(u32, u32, u32, u32);

/* Static data - old_fight_trainer_ai_value_addsub_data */
// Array of 0x2D7 entries, each 0x14 bytes (5 u32s)
static u32 _old_fight_trainer_ai_value_addsub_data[0x2D7][5];

/* Jump table for dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub */
// 17 entries for move selection categories
static void* jumpTbl_1876[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Jump table for dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub */
// 17 entries for switch-out AI categories
static void* jumpTbl_1964[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Jump table for dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub */
// 24 entries for switch-in AI categories
static void* jumpTbl_2043[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* Jump table for dbgMenuFightTrainerPokemonPartDataEditSub */
// 10 entries for pokemon party slots
static void* jumpTbl_2087[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* 0x8000C2C0 | size: 0x178 */
// Saves and restores AI addsub data for combo editing
// Backs up all 0x2D7 entries, opens menu 0x1B, then restores
void dbgMenuFightTrainerAiAddsubDataComboEditSub() {
    // Save all AI addsub data
    for (u32 i = 0; i < 0x2D7; i++) {
        void* data = fightTrainerAiValueAddsubDataBiosGetPtr(i);
        _old_fight_trainer_ai_value_addsub_data[i][0] = *(u32*)((u8*)data + 0);
        _old_fight_trainer_ai_value_addsub_data[i][1] = *(u32*)((u8*)data + 4);
        _old_fight_trainer_ai_value_addsub_data[i][2] = *(u32*)((u8*)data + 8);
        _old_fight_trainer_ai_value_addsub_data[i][3] = *(u32*)((u8*)data + 12);
        _old_fight_trainer_ai_value_addsub_data[i][4] = *(u32*)((u8*)data + 16);
    }

    // Open combo editing menu
    u32 result = menuOpenCustom(0x1B, 0, 0, 0, 1, 0);
    if (result == -1) {
        // Menu confirmed - restore data
        menuCloseCustom(0x1B, 0, 1);
        for (u32 i = 0; i < 0x2D7; i++) {
            void* data = fightTrainerAiValueAddsubDataBiosGetPtr(i);
            *(u32*)((u8*)data + 0) = _old_fight_trainer_ai_value_addsub_data[i][0];
            *(u32*)((u8*)data + 4) = _old_fight_trainer_ai_value_addsub_data[i][1];
            *(u32*)((u8*)data + 8) = _old_fight_trainer_ai_value_addsub_data[i][2];
            *(u32*)((u8*)data + 12) = _old_fight_trainer_ai_value_addsub_data[i][3];
            *(u32*)((u8*)data + 16) = _old_fight_trainer_ai_value_addsub_data[i][4];
        }
        result = -1;
    } else if (result == -2) {
        // Menu cancelled - open menu 0x55
        u32 menu55 = menuOpen(0x55, 1);
        if (menu55 == 0) {
            menuCloseCustom(0x55, 0, 1);
        } else {
            menuCloseCustom(0x55, 0, 1);
        }
        result = 0x1B;
    }
    // ... (return handling)
}

/* 0x8000C3CC | size: 0xAC */
// Similar pattern for item editing
void dbgMenuFightTrainerAiAddsubDataItemEditSub() {
    // Save, open menu, restore pattern
    // ... (skeleton)
}

/* 0x8000C478 | size: 0x258 */
// Move selection AI editing with jump table @1876
// 17 handlers for different move categories
void dbgMenuFightTrainerAiAddsubDataWazaUsewazaEditSub() {
    // Save AI data
    // Open menu 0x1B
    // Jump table dispatch based on menu selection
    // Restore AI data
    // ... (skeleton - jump table pattern)
}

/* 0x8000C6D0 | size: 0xB4 */
// Defense Pokemon AI editing
void dbgMenuFightTrainerAiAddsubDataWazaDefpokemonEditSub() {
    // Save, open menu, restore pattern
    // ... (skeleton)
}

/* 0x8000C784 | size: 0x19C */
// Switch-out AI editing with jump table @1964
// 17 handlers for different switch-out conditions
void dbgMenuFightTrainerAiAddsubDataIrekaeDasuEditSub() {
    // Save AI data
    // Open menu 0x1B
    // Jump table dispatch based on menu selection
    // Restore AI data
    // ... (skeleton - jump table pattern)
}

/* 0x8000C920 | size: 0x1B4 */
// Switch-in AI editing with jump table @2043
// 24 handlers for different switch-in conditions
void dbgMenuFightTrainerAiAddsubDataIrekaeModosuEditSub() {
    // Save AI data
    // Open menu 0x1B
    // Jump table dispatch based on menu selection
    // Restore AI data
    // ... (skeleton - jump table pattern)
}

/* 0x8000AD7C | size: 0x1DC */
// Pokemon party data editing with jump table @2087
// 10 handlers for party slots 0-9
void dbgMenuFightTrainerPokemonPartDataEditSub() {
    // Opens menu for editing trainer's pokemon party
    // Each handler calls dbgMenuFightTrainerDataStatusInputDigit
    // with different status IDs (0x4-0xD) for various pokemon parameters
    // ... (skeleton - jump table pattern)
}

/* 0x8000D53C | size: 0x51C */
// AI data editing - opens menu 0x18 for AI parameter editing
// Saves 8 u32 values from AI data, opens menu, restores
void dbgMenuFightTrainerAiDataEditSub(u32 trainerId) {
    if (trainerId == 0) {
        return;
    }
    void* aiData = fightTrainerAiDataBiosGetPtr(trainerId);
    // Save AI data fields 0x0-0x1C (8 u32s)
    u32 saved[8];
    for (int i = 0; i < 8; i++) {
        saved[i] = *(u32*)((u8*)aiData + i * 4);
    }

    // Open AI editing menu
    u32 result = menuOpenCustom(0x18, 0, 0, 0, 1, 1);
    if (result == -1) {
        // Menu confirmed - restore data
        menuCloseCustom(0x18, 0, 1);
        for (int i = 0; i < 8; i++) {
            *(u32*)((u8*)aiData + i * 4) = saved[i];
        }
    } else {
        menuCloseCustom(0x18, 0, 1);
    }
}

/* 0x8000DA58 | size: 0xA8 */
// Opens number input dialog for editing trainer status
// r3 = trainer, r4 = status_id, r5 = ?, r6 = min, r7 = max
void dbgMenuFightTrainerDataStatusInputDigit(u32 trainer, u32 statusId, u32 param2,
                                              u32 minVal, u32 maxVal) {
    u32 current = fightTrainerGetStatus(trainer, 0, statusId, param2);
    u32 value = current;
    u32 result = menuSubOpenNumberInput(0, &value, 0, 0x32, 0x32, 0);
    if (result == 1) {
        // Clamp to range
        if (value > maxVal) value = maxVal;
        if (value < minVal) value = minVal;
        fightTrainerSetStatus(trainer, 0, statusId, value);
    }
    menuSubCloseNumberInput();
}

/* 0x8000DB04 | size: 0xA8 */
// Opens Yes/No dialog for toggling trainer status flag
// r3 = trainer, r4 = status_id
void dbgMenuFightTrainerDataStatusInputFlag(u32 trainer, u32 statusId) {
    u32 current = fightTrainerGetStatus(trainer, 0, statusId, 0);
    u32 inverted = ~current;
    u8 result = (s8)menuSubOpenYesNo(0x7F, inverted, current, 0);
    if (result == 0) {
        fightTrainerSetStatus(trainer, 0, statusId, 1);
    } else if (result == 1) {
        fightTrainerSetStatus(trainer, 0, statusId, 0);
    }
}
