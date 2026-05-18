// System-level definitions based on PowerPC/GameCube SDK analysis
// References: Programming_The_PowerPC_1994.pdf, Metrowerks_Code_Worrior_Programming_1995.pdf

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Memory arena management
 * GameCube memory is divided into low/high regions
 */
typedef uint32_t OSHeapHandle;

extern uint32_t OSGetConsoleSimulatedMemSize(void);
extern uint32_t OSGetArenaLo(void);
extern uint32_t OSGetArenaHi(void);
extern void OSSetArenaLo(uint32_t addr);
extern void OSSetArenaHi(uint32_t addr);

/**
 * Memory heap management
 * Based on GSmem* functions referenced in main()
 */
extern void GSmemInit(uint32_t lo, uint32_t hi, uint32_t alignment);
extern OSHeapHandle GSmemCreateHeap(uint32_t lo, uint32_t hi, uint32_t alignment);
extern void GSmemSetCurrentHeap(OSHeapHandle heap);
extern void GSmemInitSysdolAllocator(void);

/**
 * Audio subsystem interfaces
 * Inferred from main() initialization sequence
 */
extern void ARInit(void* memArray, int numBlocks);
extern void ARQInit(void);
extern void AIInit(void* stackEnd);
extern void ARQSetChunkSize(uint32_t size);

/**
 * DVD subsystem interfaces
 * Used for game disc operations
 */
extern void GSdvdSetDVDServer(void* serverConfig);
extern void GSdvdSetReportServer(void* reportConfig);
extern void GSdvdSetGCClient(void* clientConfig);

/**
 * Logging and scratch buffer
 */
extern void GSlogInit(int flags);
extern void GSscratchInit(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_H