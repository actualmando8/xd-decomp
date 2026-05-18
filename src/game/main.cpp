// Decompiled from main.cpp (0x8000F5E8 - 0x8000F820)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack

#include "system.h"

// ============================================================
// Global variables (BSS/SDA21)
// ============================================================

// AI stack memory (16KB)
static u8 aiStackMem[0x4000];

// ARAM memory array (8 bytes)
static u8 aramMemArray[8];

// Heap handles
extern u32 g_hFloorHeap;
extern u32 g_hSysdolphineHeap;

// systemVars structure (from sysvars.cpp)
extern u32 systemVars[];

// ============================================================
// Forward declarations
// ============================================================
extern void pokecoloInitRomVersion(void);
extern void sysvarsReadSettings(char** argv, char** envp);
extern u32 OSGetConsoleSimulatedMemSize(void);
extern void OSSetArenaHi(void* addr);
extern void* OSGetArenaLo(void);
extern void* OSGetArenaHi(void);
extern void GSmemInit(void* lo, void* hi, u32 flags);
extern void OSSetArenaLo(void* addr);
extern void GSfsysCreateLocalHeap(void);
extern void GSfsysCreateCacheHeap(void);
extern void floorCreateLocalHeap(void);
extern u32 GSmemCreateHeap(void* lo, void* hi, u32 flags);
extern void GSmemSetCurrentHeap(u32 heap);
extern void GSmemInitSysdolAllocator(void);
extern u32 pokecoloGetCountryCode(void);
extern void GSgfxInit__FP15_GSgfxInitParms(void* params);
extern void sysvarsShowDebug(void);
extern void ARInit(void* mem, u32 count);
extern void ARQInit(void);
extern void AIInit(void* stack);
extern void ARQSetChunkSize(u32 size);
extern void GSlogInit(u32 flags, u32 param);
extern void GSscratchInit(u32 param);
extern void GSdvdSetDVDServer(void* server, u32 flags);
extern void GSdvdSetReportServer(void* server, u32 flags);
extern void GSdvdSetGCClient(void* p1, void* p2, void* p3, u32 flags);
extern void pokecoloMain(void);

// ============================================================
// GSgfxInitParms structure
// ============================================================
struct GSgfxInitParms {
    u8 progressive;
    u8 pad1;
    u16 pad2;
    u16 unknown;  // 0x1E0
};

// ============================================================
// Function implementations
// ============================================================

/*
 * main
 * Original address: 0x8000F5E8
 * Size: 0x238 bytes
 * 
 * Entry point for the game. Initializes memory, systems, and calls pokecoloMain().
 * 
 * @param argc  Argument count
 * @param argv  Argument vector
 */
extern "C" void main(int argc, char** argv) {
    char** saved_argv = argv;
    char** saved_envp = &(argv[argc]);
    
    // Initialize ROM version
    pokecoloInitRomVersion();
    
    // Clear systemVars area
    memset((void*)0x80001800, 0, 0x1800);
    
    // Read command line settings
    sysvarsReadSettings(saved_argv, saved_envp);
    
    // Check memory size and set arena
    {
        u32 memSize = OSGetConsoleSimulatedMemSize();
        if (memSize > 0x180000) {  // > 1.5MB
            s32 memType = (s32)systemVars[1];
            if (memType == 0x18) {
                OSSetArenaHi((void*)0x817FD880);
            } else if (memType == 0x30) {
                OSSetArenaHi((void*)0x82DFD720);
            }
        }
    }
    
    // Initialize memory heap
    {
        void* arenaLo = OSGetArenaLo();
        void* arenaHi = OSGetArenaHi();
        GSmemInit(arenaLo, arenaHi, 4);
        OSSetArenaLo(arenaLo);
    }
    
    // Create file system heaps
    GSfsysCreateLocalHeap();
    GSfsysCreateCacheHeap();
    floorCreateLocalHeap();
    
    // Create floor heap
    {
        void* arenaLo = OSGetArenaLo();
        void* arenaHi = OSGetArenaHi();
        g_hFloorHeap = GSmemCreateHeap(arenaLo, arenaHi, 0);
        GSmemSetCurrentHeap(g_hFloorHeap);
        OSSetArenaLo(arenaHi);
        g_hSysdolphineHeap = g_hFloorHeap;
        GSmemInitSysdolAllocator();
    }
    
    // Determine region and setup GSgfxInitParms
    {
        s32 countryCode = (s32)pokecoloGetCountryCode();
        u32 padValue = systemVars[3];
        
        GSgfxInitParms params;
        memset(&params, 0, sizeof(params));
        
        // Check if country code indicates NTSC-J (0) or NTSC-U (2)
        if (countryCode >= 0 && countryCode <= 2) {
            params.progressive = (countryCode == 2) ? 1 : 0;
        }
        
        params.progressive = 2;  // Default to NTSC
        params.unknown = 0x1E0;
        
        // Determine from padValue sign
        if ((padValue & 0x80000000) != 0) {
            params.progressive = 1;
        }
        
        GSgfxInit__FP15_GSgfxInitParms(&params);
    }
    
    // Show debug overlay if enabled
    if (systemVars[0] == 1) {
        sysvarsShowDebug();
    }
    
    // Initialize audio system
    ARInit(aramMemArray, 2);
    ARQInit();
    AIInit((void*)((u32)aiStackMem + 0x3FF8));
    ARQSetChunkSize(0x01800000);  // 24MB chunk size
    
    // Initialize logging
    GSlogInit(0x01800000, 2);
    
    // Initialize scratch memory
    GSscratchInit(0);
    
    // Setup DVD server
    {
        u32 dvdServerFlags = systemVars[0x68 / 4] & 0xFFFF;
        GSdvdSetDVDServer((void*)systemVars[0x48 / 4], dvdServerFlags);
        
        u32 reportServerFlags = systemVars[0x6C / 4] & 0xFFFF;
        GSdvdSetReportServer((void*)systemVars[0x48 / 4], reportServerFlags);
        
        GSdvdSetGCClient(
            (void*)systemVars[0x58 / 4],
            (void*)systemVars[0x70 / 4],
            (void*)systemVars[0x80 / 4],
            1
        );
    }
    
    // Call main game loop
    pokecoloMain();
}
