// Decompiled from sysvars.cpp (0x8000F820 - 0x8000FDA8)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r4 args, r3 return, LR saved on stack

#include "system.h"

// Forward declarations for GSprim/GSgfx functions
extern void GSgfxGPUSetMode(u32 mode);
extern void GSgfxRender(void);
extern void GSprimSetup2DRender(void* layer);
extern void GSprimDraw2DQuad(f32 x, f32 y, f32 w, f32 h);
extern void GSprimSetTextColor(u32 color);
extern void GSprimSetTextWidth(f32 width);
extern void GSprimSetTextSize(f32 size);
extern void GSprimWriteStr(f32 x, f32 y, const char* str, ...);

// Standard library functions
extern int stricmp(const char* s1, const char* s2);
extern char* strcpy(char* dest, const char* src);
extern int atoi(const char* str);
extern double atof(const char* str);

// System variables structure
struct SystemVars {
    u32 debugMenuFlag;      // 0x00
    u32 gsmemSize;          // 0x04 - GS memory size (0x18 or 0x30)
    u32 errortrap;          // 0x08
    u32 dispmemSize;        // 0x0C
    u32 btldbg_menuFlag;    // 0x10
    u32 btldbg_deckGrp;     // 0x14
    u32 btldbg_encountId;   // 0x18
    u32 btldbg_storyEncountId;   // 0x1C
    u32 btldbg_hundredEncountId; // 0x20
    u32 btldbg_imasuguEncountId; // 0x24
    u32 btldbg_virtualEncountId; // 0x28
    u32 btldbg_bingoEncountId;   // 0x2C
    u32 btldbg_colosseumEncountId; // 0x30
    u32 btldbg_itemset1;    // 0x34
    u32 btldbg_autoEncount; // 0x38
    u32 flddbg_pokedoru;    // 0x3C
    u32 flddbg_pokecoupon;  // 0x40
    char gamecubeIp[0x10];  // 0x44
    u32 serverPort;         // 0x54
    u32 outputPort;         // 0x58
    u32 hero_coli_disable_but; // 0x5C
};

// Function entry structure for sysvars
struct sysvarsFuncEntry {
    u32* func;          // 0x00 - Function pointer (or NULL for end of list)
    u32* param;         // 0x04 - Parameter pointer
    s32  type;          // 0x08 - Type: 0=bool, 1=int, 2=float, 3=str, 4=custom
    u32* data;          // 0x0C - Data pointer
    const char* name;   // 0x10 - Setting name
};

// Global system variables
extern struct SystemVars systemVars;

// Function list for sysvars processing
extern struct sysvarsFuncEntry _sysvarsFuncList[];

// SDA2 constants (from assembly)
// @2083, @2084 - GPU mode parameters
// @2119-@2132 - Various float constants for rendering
// @2129 - Y increment (0x11.0p-1 = 1.0625)
// @2187 - "off" string
// @2188 - "false" string
// @2189 - "no" string
// @2190 - "on" string
// @2191 - "true" string
// @2192 - "yes" string
// @2210 - "basic" string
// @2211 - "detailed" string
// @2218 - "24mb" string
// @2219 - "32mb" string

// Function pointer table for debug display
// Each entry: {func, param, type, data, name}
typedef void (*sysvarsFuncPtr)(void*, const char*);

struct sysvarsFuncEntry {
    sysvarsFuncPtr func;
    u32 type;
    u32 dummy;
    void* data;
    const char* name;
};

/*
 * sysvarsShowDebug
 * Original address: 0x8000F820
 * Size: 0x194 bytes
 * 
 * Displays debug information overlay on screen
 * Iterates through function list and displays each setting
 */
void sysvarsShowDebug(void) {
    struct sysvarsFuncEntry* entry;
    u32 i;
    f32 y;
    
    // Save GPU mode and switch to mode 1
    u32 prevMode = GSgfxGPUSetMode(1);
    
    // Initialize rendering parameters
    entry = _sysvarsFuncList;
    y = 1.0625f;  // Starting Y position
    i = 0x383;    // Loop counter (899 frames)
    
    do {
        // Setup 2D rendering
        GSprimSetup2DRender(0);
        
        // Draw background quad
        GSprimDraw2DQuad(0.0f, y, 1.0f, 0.0625f);
        
        // Set text color and properties
        GSprimSetTextColor(0xFFFFFF);
        GSprimSetTextWidth(1.0f);
        GSprimSetTextSize(0.05f);
        
        // Iterate through function entries
        f32 yPos = y;
        struct sysvarsFuncEntry* curr = entry;
        
        while (curr->func != 0 || curr->name != 0) {
            u32 type = curr->type;
            
            if (type == 0) {
                // Boolean type - display string from data
                GSprimWriteStr(yPos, 0.0f, (const char*)curr->data);
            } else if (type == 2) {
                // Float type - display float value
                GSprimWriteStr(yPos, 0.0f, (const char*)curr->data);
            } else if (type >= 0 && type < 4) {
                // Int or custom type - display value
                GSprimWriteStr(yPos, 0.0f, (const char*)curr->data);
            }
            
            yPos += 0.1171875f;  // Y increment
            curr++;
        }
        
        // Display frame counter
        GSprimWriteStr(yPos, 0.0f, i);
        
        // Render frame
        GSgfxRender();
        
        i--;
    } while (i != 0);
    
    // Restore GPU mode
    GSgfxGPUSetMode(2);
}

/*
 * sysvarsReadSettings
 * Original address: 0x8000F9B4
 * Size: 0x84 bytes
 * 
 * Reads and processes command line settings
 * 
 * @param argc  Argument count pointer
 * @param argv  Argument vector pointer
 */
void sysvarsReadSettings(int* argc, char*** argv) {
    int i;
    
    // Skip if argc < 2
    if (*argc < 2) {
        return;
    }
    
    // Process each argument starting from argv[1]
    for (i = 1; i < *argc; i++) {
        _sysvarsProcess((*argv)[i]);
    }
    
    // Decrement argc to mark settings as processed
    *argc = *argc - 1;
}

/*
 * _sysvarsProcess
 * Original address: 0x8000FA38
 * Size: 0xC4 bytes
 * 
 * Processes a single command line setting string
 * Format: "-settingName:value"
 * 
 * @param str  Setting string to process
 */
void _sysvarsProcess(const char* str) {
    const char* p = str;
    struct sysvarsFuncEntry* entry;
    
    // Skip leading characters until '-' or null
    while (*p != 0 && *p != '-') {
        p++;
    }
    
    // Check if we found '-'
    if (*p != '-') {
        return;
    }
    
    // Null-terminate at '-'
    *p = 0;
    p++;
    
    // Find entry by name
    entry = _sysvarsFindEntry(p);
    
    // Skip to ':' or null
    while (*p != 0 && *p != ':') {
        p++;
    }
    
    // Check if we found ':'
    if (*p != ':') {
        if (entry != 0) {
            _sysvarsProcessData(entry, p);
        }
        return;
    }
    
    // Null-terminate at ':'
    *p = 0;
    p++;
    
    // Process data if entry found
    if (entry != 0) {
        _sysvarsProcessData(entry, p);
    }
}

/*
 * _sysvarsProcessData
 * Original address: 0x8000FAFC
 * Size: 0x140 bytes
 * 
 * Processes the value part of a setting and applies it
 * 
 * @param entry  Function entry structure
 * @param value  Value string
 */
void _sysvarsProcessData(struct sysvarsFuncEntry* entry, const char* value) {
    s32 type = entry->type;
    
    // If func pointer is non-null, call it directly
    if (entry->func != 0) {
        entry->func(entry->data, value);
        return;
    }
    
    // Dispatch based on type
    if (type == 0) {
        // Boolean type - check for on/true/yes or off/false/no
        if (stricmp(value, "off") == 0 || stricmp(value, "false") == 0 || stricmp(value, "no") == 0) {
            *(u32*)entry->data = 0;
        } else if (stricmp(value, "on") == 0 || stricmp(value, "true") == 0 || stricmp(value, "yes") == 0) {
            *(u32*)entry->data = 1;
        }
    } else if (type == 1) {
        // Integer type
        *(u32*)entry->data = atoi(value);
    } else if (type == 2) {
        // Float type
        *(f32*)entry->data = (f32)atof(value);
    } else if (type >= 0 && type < 4) {
        // String type
        strcpy((char*)entry->data, value);
    }
}

/*
 * _sysvarsFindEntry
 * Original address: 0x8000FC3C
 * Size: 0x6C bytes
 * 
 * Finds a function entry by name in the function list
 * 
 * @param name  Name to search for
 * @return      Pointer to entry, or NULL if not found
 */
struct sysvarsFuncEntry* _sysvarsFindEntry(const char* name) {
    struct sysvarsFuncEntry* entry = _sysvarsFuncList;
    
    while (entry->name != 0) {
        if (stricmp(name, entry->name) == 0) {
            return entry;
        }
        entry++;
    }
    
    return 0;
}

/*
 * _sysvarsPerfbar
 * Original address: 0x8000FCA8
 * Size: 0x90 bytes
 * 
 * Sets performance bar mode from string
 * 
 * @param data  Pointer to u32 for mode value
 * @param value  String: "off", "basic", or "detailed"
 */
void _sysvarsPerfbar(void* data, const char* value) {
    if (stricmp(value, "off") == 0) {
        *(u32*)data = 0;
    } else if (stricmp(value, "basic") == 0) {
        *(u32*)data = 1;
    } else if (stricmp(value, "detailed") == 0) {
        *(u32*)data = 2;
    }
}

/*
 * _sysvarsGSmemSize
 * Original address: 0x8000FD38
 * Size: 0x70 bytes
 * 
 * Sets GS memory size from string
 * 
 * @param data  Pointer to u32 for size value
 * @param value  String: "24mb" or "32mb"
 */
void _sysvarsGSmemSize(void* data, const char* value) {
    if (stricmp(value, "24mb") == 0) {
        *(u32*)data = 0x18;  // 24MB
    } else if (stricmp(value, "32mb") == 0) {
        *(u32*)data = 0x30;  // 32MB
    }
}

// Global system variables instance
struct SystemVars systemVars = {
    0,                    // debugMenuFlag
    0x18,                 // gsmemSize (24MB default)
    0,                    // errortrap
    1,                    // dispmemSize
    0,                    // btldbg_menuFlag
    0xFFFFFFFF,           // btldbg_deckGrp
    0xFFFFFFFF,           // btldbg_encountId
    0xFFFFFFFF,           // btldbg_storyEncountId
    0xFFFFFFFF,           // btldbg_hundredEncountId
    0xFFFFFFFF,           // btldbg_imasuguEncountId
    0xFFFFFFFF,           // btldbg_virtualEncountId
    0xFFFFFFFF,           // btldbg_bingoEncountId
    0xFFFFFFFF,           // btldbg_colosseumEncountId
    0,                    // btldbg_itemset1
    0,                    // btldbg_autoEncount
    0,                    // flddbg_pokedoru
    0,                    // flddbg_pokecoupon
    {0},                  // gamecubeIp
    0,                    // serverPort
    0,                    // outputPort
    0,                    // hero_coli_disable_but
};
