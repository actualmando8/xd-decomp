// Graphics system definitions based on symbol analysis
// References: Programming_The_PowerPC_1994.pdf, Metrowerks_Code_Worrior_Programming_1995.pdf

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

/**
 * Parameters for graphics initialization
 * Mangled name: _GSgfxInit__FP15_GSgfxInitParms
 * Size: 8 bytes (inferred from usage)
 */
typedef struct {
    uint32_t flags;        // Configuration flags (unused in initialization)
    uint8_t resolution;     // Video standard (0=PAL, 1=MPAL, 2=NTSC)
    uint8_t padding;        // Alignment padding
    uint16_t screenWidth;   // Horizontal resolution (0x1E0 = 480 pixels)
} GSgfxInitParms;

/**
 * Graphics layer structure
 * Mangled name: _GSgfxLayerRenderStats__FP10GSgfxLayer
 * Size: Inferred from symbol name (10 bytes minimum)
 */
typedef struct GSgfxLayer {
    void* vtable;           // Virtual function table
    uint32_t layerId;       // Unique layer identifier
    uint16_t width;         // Layer width
    uint16_t height;        // Layer height
    void* textureBuffer;    // Pointer to texture data
    void* zBuffer;          // Depth buffer pointer
} GSgfxLayer;

/**
 * Graphics context structure
 * Inferred from GSmemCreateHeap usage in main()
 */
typedef struct {
    GSgfxInitParms initParams;
    GSgfxLayer* activeLayers[4];
    uint32_t frameCounter;
    uint8_t isInitialized;
} GSgfxContext;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initializes graphics subsystem
 * 
 * @param params Initialization parameters
 * @return 0 on success
 */
extern int GSgfxInit(GSgfxInitParms* params);

/**
 * Shuts down graphics subsystem
 */
extern void GSgfxShutdown(void);

/**
 * Renders statistics for specified layer
 * 
 * @param layer Target graphics layer
 */
extern void GSgfxLayerRenderStats(GSgfxLayer* layer);

#ifdef __cplusplus
}
#endif

#endif // GRAPHICS_H