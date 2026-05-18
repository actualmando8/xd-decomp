// Decompiled main function based on PowerPC assembly analysis
// References: Programming_The_PowerPC_1994.pdf, Metrowerks_Code_Worrior_Programming_1995.pdf

#include "system.h"
#include "memory.h"
#include "graphics.h"
#include "pokecolo.h"

// Updated based on GSgfxInit symbol analysis
typedef struct {
    /* 0x0 */ uint32_t flags;      // Configuration flags (unused in this context)
    /* 0x4 */ uint8_t resolution;    // Screen resolution index (2 = NTSC)
    /* 0x5 */ uint8_t padding;     // Alignment padding
    /* 0x6 */ uint16_t screenWidth; // Screen width (0x1E0 = 480 pixels)
} GSgfxInitParms;

int main(int argc, char** argv) {
    // Stack frame setup (r1 -= 0x30)
    pokecoloInitRomVersion();
    
    // Clear memory region (0x80001800, size 0x1800)
    memset((void*)0x80001800, 0, 0x1800);
    
    // Load system settings
    sysvarsReadSettings(&argc, &argv);
    
    // Memory configuration based on console type
    u32 memSize = OSGetConsoleSimulatedMemSize();
    if (memSize >= 0x180) {
        if (systemVars->romType == 0x18) {
            OSSetArenaHi(0x817FD780);  // GameCube memory configuration
        } else if (systemVars->romType == 0x30) {
            OSSetArenaHi(0x82DFD720);  // Alternative configuration
        }
    }
    
    // Memory heap initialization sequence
    u32 arenaLo = OSGetArenaLo();
    u32 arenaHi = OSGetArenaHi();
    GSmemInit(arenaLo, arenaHi, 4);
    OSSetArenaLo(GSfsysCreateLocalHeap());
    GSfsysCreateCacheHeap();
    floorCreateLocalHeap();
    
    // Configure floor heap
    arenaLo = OSGetArenaLo();
    arenaHi = OSGetArenaHi();
    g_hFloorHeap = GSmemCreateHeap(arenaLo, arenaHi, 4);
    GSmemSetCurrentHeap(g_hFloorHeap);
    g_hSysdolphineHeap = g_hFloorHeap;
    GSmemInitSysdolAllocator();
    
    // Determine country code handling
    int countryCode = pokecoloGetCountryCode();
    systemVars->isPAL = (countryCode == 2) ? 1 : 
                      (countryCode >= 0 && countryCode <= 1) ? 0 : 
                      0;
    
    // Graphics initialization
    GSgfxInitParms gfxParams = { 
        .flags = 0,
        .resolution = 2, 
        .screenWidth = 0x1E0 
    };
    GSgfxInit(&gfxParams);
    
    // Debug mode activation
    if (systemVars->debugMode == 1) {
        sysvarsShowDebug();
    }
    
    // Audio subsystem initialization
    ARInit(aramMemArray, 2);
    ARQInit();
    AIInit(aiStackMem + 0x3FF8);
    ARQSetChunkSize(0x8000);
    
    // Logging and scratch buffer setup
    GSlogInit(0);
    GSscratchInit();
    
    // DVD subsystem configuration
    GSdvdSetDVDServer(&systemVars->dvdServer);
    GSdvdSetReportServer(&systemVars->reportServer);
    GSdvdSetGCClient(&systemVars->clientConfig);
    
    // Entry to game logic
    return pokecoloMain(argc, argv);
}
