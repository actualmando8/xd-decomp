// Decompiled from floorRead.cpp (0x8002D8C0 - 0x8002F308)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack

#include "system.h"

// ============================================================
// Forward declarations for external functions
// ============================================================
extern void* GSresGetResource(u32 group, u32 id);
extern void GSresUnlockResource(u32 group, u32 id);
extern void GSresLockResource(u32 group, u32 id);
extern void* GSresAllocResourceAlign(u32 size, u32 align, u32 group, u32 id, void* unloadFunc);
extern void GSresRegisterResource(void* data, u32 group, u32 id, void* unloadFunc);
extern void GSresFree(u32 group, u32 id);
extern void GSresFreeResource(u32 group, u32 id);
extern s32 GSresIsUniqueID(u32 group, u32 id, u32 flags);
extern void GSthreadSwitch(void);
extern s32 GSfsysReadIDEXWait(u32 group, u32 id, void* callback, u32 param, u32 flags);

extern u32 floorGetCurrentGroupID(void);
extern void floorAddResource(u32 group, u32 id);
extern void* floorDataBiosGetCurrentPtr(void);
extern void floorDataBiosSetMapResID(u32 id);
extern s32 floorIsPop(void);
extern s32 floorIsPush(void);
extern void floorMappingScript(void* data);
extern void floorUnmappingScript(void* data);
extern s32 floorSound_playEnvSound(u32 group, u32 id);
extern void soundStopEnv(void);
extern void floorExecSoundScript(u32 group, u32 id);
extern void floorSetLightInfo(u32 lightId, u32 count);
extern void floorInitMap(u32 group, u32 id);

extern void* HSD_ArchiveGetPublicAddress(void* archive, const char* name);
extern void* HSD_ArchiveParse(void* data, u32 size, u32 flags);
extern void* GScameraLoad(u32 group, u32 id);
extern void GScameraFree(u32 group, u32 id);
extern void* GSlightLoad(u32 group, u32 id);
extern void GSlightFree(u32 group, u32 id);
extern void* GStextureLoad(u32 group, u32 id);
extern void GStextureFree(u32 group, u32 id);
extern void* antReadPostFunc(void* data, u32 param);
extern void* antGetGStexture(void* data);
extern void* FlashSystemInit(void* data);
extern void FlashSystemRelease(u32 id);
extern void* GSparticleLoad(u32 group, u32 id);
extern void GSparticleFree(u32 group, u32 id);
extern void* GSlensFlareLoad(u32 group, u32 id);
extern void GSlensFlareFree(u32 group, u32 id);
extern void GScolsys2LoadCCD(u32 group, u32 id);
extern void GScolsys2UnloadCCD(u32 group, u32 id);
extern void GSmodelLinkToGSparticleBank(void* particle, void* model);
extern void GSmsgFontOpen(void* data);
extern void GSmsgFontClose(void* data);
extern void GSmsgOpen(void* data);
extern void GSmsgClose(void* data);
extern void GSfsysOSLinkPostFunc(u32 group, u32 id, void* param);
extern s32 pokecoloGetLanguage(void);
extern s32 fn_8010B208(void* data);

// WazaSequence and ModelSequence classes (C++ name mangling)
namespace WazaSequence {
    extern s32 Load(const char* data, u32 group, u32 id);
    extern void Unload(const char* data);
}
namespace ModelSequence {
    extern s32 Load(const char* data, u32 group, u32 id);
    extern void Unload(const char* data);
}

// ============================================================
// FloorPostCallManager - Deferred post-function manager
// ============================================================
struct FloorPostCallEntry {
    u32 active;
    u32 group;
    u32 id;
    u32 param;
    void* func;  // function pointer
};

struct FloorPostCallManager {
    FloorPostCallEntry entries[8];  // 0xA0 bytes total / 0x14 per entry = 8
    
    void update(void);
    void add(u32 group, u32 id, u32 param, void* func, void* data);
    FloorPostCallManager(void);
};

// Global post-function manager instance
extern FloorPostCallManager _postFuncManager;

// Global flag for resource reading
static u8 floorReadingResource;

// ============================================================
// Core resource reading functions
// ============================================================

/*
 * floorDelayPostFunc
 * Original address: 0x8002D8C0
 * Size: 0x28 bytes
 * 
 * Delayed post-function callback for floor resource loading
 */
void floorDelayPostFunc(void) {
    _postFuncManager.update();
}

/*
 * floorReadResourceID
 * Original address: 0x8002D8E8
 * Size: 0xE8 bytes
 * 
 * Reads a resource by group ID and resource ID
 * 
 * @param group  Resource group ID (0 = current group)
 * @param id     Resource ID
 * @return       Resource pointer
 */
void* floorReadResourceID(u32 group, u32 id) {
    void* resource;
    
    if (group == 0) {
        group = floorGetCurrentGroupID();
    }
    
    // Check if resource already loaded
    resource = GSresGetResource(group, id);
    if (resource != 0) {
        return resource;
    }
    
    // Wait if another resource is being read
    while (floorReadingResource != 0) {
        GSthreadSwitch();
    }
    
    // Mark as reading
    floorReadingResource = 1;
    
    // Read resource from DVD
    while (GSfsysReadIDEXWait(group, id, 0, 0, 0) == 0) {
        GSthreadSwitch();
    }
    
    // Free temporary and add to resource manager
    GSfsysFree(group);
    floorAddResource(group, id);
    
    // Get and return resource
    resource = GSresGetResource(group, id);
    floorReadingResource = 0;
    
    return resource;
}

/*
 * _fsysLoadCallbak
 * Original address: 0x8002D9D0
 * Size: 0x4 bytes
 * 
 * Empty callback stub for file system loading
 */
void _fsysLoadCallbak(s32 param1, void* param2, s32 param3) {
    // Empty stub
}

/*
 * floorRegisterCamera
 * Original address: 0x8002D9D4
 * Size: 0x8C bytes
 * 
 * Registers a camera from floor resources
 * 
 * @param group  Resource group ID
 * @param id     Resource ID
 * @return       Scene descriptor pointer
 */
void* floorRegisterCamera(u32 group, u32 id) {
    void* resource;
    void* scene;
    
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        return 0;
    }
    
    scene = HSD_ArchiveGetPublicAddress(resource, "scene_data");
    if (scene == 0) {
        return 0;
    }
    
    return scene;
}

/*
 * floorRegisterLight
 * Original address: 0x8002DA60
 * Size: 0xC4 bytes
 * 
 * Registers lights from floor resources
 * 
 * @param group  Resource group ID
 * @param id     Resource ID
 * @return       Scene descriptor pointer
 */
void* floorRegisterLight(u32 group, u32 id) {
    void* resource;
    void* scene;
    u32* lightList;
    u32 i;
    u32 lightId;
    
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        return 0;
    }
    
    scene = HSD_ArchiveGetPublicAddress(resource, "scene_data");
    if (scene == 0) {
        return 0;
    }
    
    lightList = (u32*)*((u32*)scene + 2);
    if (lightList == 0) {
        return scene;
    }
    
    lightId = floorReadMakeLightResID(id);
    i = 0;
    
    while (lightList[i] != 0) {
        void* light = GSlightLoad(group, lightId | i);
        if (light != 0) {
            GSresRegisterResource(light, group, lightId | i, 0);
        }
        i++;
    }
    
    return scene;
}

// ============================================================
// Pre/Post function pairs for resource types
// ============================================================

/*
 * floorReadDeckPostFunc
 * Original address: 0x8002DB24
 * Size: 0x68 bytes
 * 
 * Post-function callback for deck resource loading
 */
void* floorReadDeckPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    
    if (resource != 0) {
        // deckRegister(group, id);  // External function
    }
    
    return resource;
}

/*
 * floorReadDeckPreFunc
 * Original address: 0x8002DB8C
 * Size: 0x6C bytes
 * 
 * Pre-function for deck resource allocation
 */
void* floorReadDeckPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadAntPostFunc
 * Original address: 0x8002DC24
 * Size: 0x6C bytes
 * 
 * Post-function callback for antenna texture loading
 */
void* floorReadAntPostFunc(u32 group, u32 id, void* data) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    antReadPostFunc(data, id);
    GStextureLoad(group, (u32)antGetGStexture(data));
    
    return resource;
}

/*
 * floorReadAntPreFunc
 * Original address: 0x8002DC90
 * Size: 0x6C bytes
 * 
 * Pre-function for antenna texture allocation
 */
void* floorReadAntPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadGSWPostFunc
 * Original address: 0x8002DD24
 * Size: 0x5C bytes
 * 
 * Post-function callback for GSW (Game Save Write) resource loading
 */
void* floorReadGSWPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    FlashSystemInit(resource);
    
    return resource;
}

/*
 * floorReadGSWPreFunc
 * Original address: 0x8002DD80
 * Size: 0x6C bytes
 * 
 * Pre-function for GSW resource allocation
 */
void* floorReadGSWPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadEncodeRelPostFunc
 * Original address: 0x8002DDEC
 * Size: 0x6C bytes
 * 
 * Post-function callback for encoded relation resource loading
 */
void* floorReadEncodeRelPostFunc(u32 group, u32 id, void* param) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    GSfsysOSLinkPostFunc(group, id, param);
    
    return resource;
}

/*
 * floorReadEncodeRelPreFunc
 * Original address: 0x8002DE58
 * Size: 0x7C bytes
 * 
 * Pre-function for encoded relation resource allocation
 */
void* floorReadEncodeRelPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    if (resource == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadGFLPostFunc
 * Original address: 0x8002DED4
 * Size: 0x88 bytes
 * 
 * Post-function callback for lens flare resource loading
 */
void* floorReadGFLPostFunc(u32 group, u32 id) {
    void* resource;
    u32 objId;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    
    objId = floorReadMakeObjResID(id);
    resource = GSresGetResource(group, objId);
    
    {
        void* flare = GSlensFlareLoad(group, objId);
        if (flare != 0) {
            GSresRegisterResource(flare, group, objId, 0);
        }
    }
    
    return resource;
}

/*
 * floorReadGFLPreFunc
 * Original address: 0x8002DF5C
 * Size: 0x7C bytes
 * 
 * Pre-function for lens flare resource allocation
 */
void* floorReadGFLPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    u32 objId;
    
    objId = floorReadMakeObjResID(id);
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, objId, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadBGMPostFunc
 * Original address: 0x8002DFD8
 * Size: 0x8 bytes
 * 
 * Post-function callback for BGM resource loading (no-op)
 */
void* floorReadBGMPostFunc(void) {
    return 0;
}

/*
 * floorReadBGMPreFunc
 * Original address: 0x8002DFE0
 * Size: 0x20 bytes
 * 
 * Pre-function for BGM resource allocation
 */
void* floorReadBGMPreFunc(u32 group, u32 id, u32 size) {
    floorReadNormalPreFunc(group, id, size);
    return 0;
}

/*
 * floorReadNotLinkedParticlePostFunc
 * Original address: 0x8002E000
 * Size: 0x7C bytes
 * 
 * Post-function callback for non-linked particle loading
 */
void* floorReadNotLinkedParticlePostFunc(u32 group, u32 id) {
    void* resource;
    u32 objId;
    
    GSresUnlockResource(group, id);
    objId = floorReadMakeObjResID(id);
    resource = GSresGetResource(group, objId);
    
    {
        void* particle = GSparticleLoad(group, objId);
        if (particle != 0) {
            GSresRegisterResource(particle, group, objId, 0);
        }
    }
    
    return resource;
}

/*
 * floorReadNotLinkedParticlePreFunc
 * Original address: 0x8002E07C
 * Size: 0x7C bytes
 * 
 * Pre-function for non-linked particle allocation
 */
void* floorReadNotLinkedParticlePreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    u32 objId;
    
    objId = floorReadMakeObjResID(id);
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, objId, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadParticlePostFunc
 * Original address: 0x8002E0F8
 * Size: 0x15C bytes
 * 
 * Post-function callback for particle loading with model linking
 */
void* floorReadParticlePostFunc(u32 group, u32 id, void* param) {
    void* resource;
    void* biosPtr;
    void* scene;
    u32* modelList;
    u32 modelBaseId;
    u32 i;
    u32 offset;
    
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        // Queue for later processing
        _postFuncManager.add(group, id, (u32)param, 
            (void*)floorReadParticlePostFunc, param);
        return 0;
    }
    
    GSresUnlockResource(group, id);
    modelBaseId = floorReadMakeObjResID(id);
    resource = GSresGetResource(group, modelBaseId);
    
    {
        void* particle = GSparticleLoad(group, modelBaseId);
        if (particle != 0) {
            GSresRegisterResource(particle, group, modelBaseId, 0);
        }
    }
    
    biosPtr = floorDataBiosGetCurrentPtr();
    floorGetCurrentGroupID();
    modelList = (u32*)*((u32*)biosPtr + 1);
    if (modelList == 0) {
        return resource;
    }
    
    scene = HSD_ArchiveGetPublicAddress(0, "scene_data");
    if (scene == 0) {
        return resource;
    }
    
    modelList = (u32*)*((u32*)scene);
    if (modelList == 0) {
        return resource;
    }
    
    modelBaseId = floorReadMakeModelResID(id);
    i = 0;
    offset = 0;
    
    while (1) {
        u32 modelId = modelBaseId | i;
        void* model = GSresGetResource(floorGetCurrentGroupID(), modelId);
        if (model != 0) {
            GSmodelLinkToGSparticleBank(param, model);
        }
        offset += 4;
        i++;
        
        u32 next = modelList[offset / 4];
        if (next == 0) {
            break;
        }
    }
    
    return resource;
}

/*
 * floorReadParticlePreFunc
 * Original address: 0x8002E254
 * Size: 0x7C bytes
 * 
 * Pre-function for particle resource allocation
 */
void* floorReadParticlePreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    u32 objId;
    
    objId = floorReadMakeObjResID(id);
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, objId, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadWZXPostFunc
 * Original address: 0x8002E2D0
 * Size: 0x84 bytes
 * 
 * Post-function callback for Waza sequence loading
 */
void* floorReadWZXPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        return 0;
    }
    
    {
        s32 result = WazaSequence::Load((const char*)resource, group, id);
        if (result != 0) {
            return resource;
        }
    }
    
    return 0;
}

/*
 * floorReadWZXPreFunc
 * Original address: 0x8002E354
 * Size: 0x6C bytes
 * 
 * Pre-function for Waza sequence allocation
 */
void* floorReadWZXPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadPKXPostFunc
 * Original address: 0x8002E3C0
 * Size: 0x84 bytes
 * 
 * Post-function callback for PKX (Pokémon model sequence) loading
 */
void* floorReadPKXPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        return 0;
    }
    
    {
        s32 result = ModelSequence::Load((const char*)resource, group, id);
        if (result != 0) {
            return resource;
        }
    }
    
    return 0;
}

/*
 * floorReadPKXPreFunc
 * Original address: 0x8002E444
 * Size: 0x90 bytes
 * 
 * Pre-function for PKX resource allocation
 */
void* floorReadPKXPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    if (resource == 0) {
        return 0;
    }
    GSresIsUniqueID(group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadTexPostFunc
 * Original address: 0x8002E4D4
 * Size: 0x50 bytes
 * 
 * Post-function callback for texture loading
 */
void* floorReadTexPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    GStextureLoad(group, id);
    
    return resource;
}

/*
 * floorReadTexPreFunc
 * Original address: 0x8002E524
 * Size: 0x6C bytes
 * 
 * Pre-function for texture resource allocation
 */
void* floorReadTexPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadColPostFunc
 * Original address: 0x8002E590
 * Size: 0x50 bytes
 * 
 * Post-function callback for collision system loading
 */
void* floorReadColPostFunc(u32 group, u32 id) {
    void* resource;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    GScolsys2LoadCCD(group, id);
    
    return resource;
}

/*
 * floorReadColPreFunc
 * Original address: 0x8002E5E0
 * Size: 0x6C bytes
 * 
 * Pre-function for collision system allocation
 */
void* floorReadColPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadCameraPostFunc
 * Original address: 0x8002E64C
 * Size: 0x74 bytes
 * 
 * Post-function callback for camera loading
 */
void* floorReadCameraPostFunc(u32 group, u32 id, void* scene) {
    u32 objId;
    void* archive;
    
    objId = floorReadMakeObjResID(id);
    archive = _makeArchiveHeader(group, objId, (u32)scene);
    _registerCamera(group, objId, archive);
    
    return archive;
}

/*
 * floorReadCameraPreFunc
 * Original address: 0x8002E6C0
 * Size: 0x8C bytes
 * 
 * Pre-function for camera resource allocation
 */
void* floorReadCameraPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    u32 objId;
    
    objId = floorReadMakeObjResID(id);
    resource = GSresAllocResourceAlign(size + 0x60, 0x20, group, objId, 0);
    if (resource == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    
    return (void*)((u32)resource + 0x60);
}

/*
 * floorReadObjPostFunc
 * Original address: 0x8002E74C
 * Size: 0x94 bytes
 * 
 * Post-function callback for object loading
 */
void* floorReadObjPostFunc(u32 group, u32 id) {
    void* archive;
    u32* modelList;
    u32 modelBaseId;
    u32 i;
    u32 offset;
    
    archive = _makeArchiveHeader(group, id, 0);
    if (archive == 0) {
        return 0;
    }
    
    modelList = (u32*)*((u32*)archive);
    if (modelList == 0) {
        return archive;
    }
    
    modelBaseId = floorReadMakeModelResID(id);
    i = 0;
    offset = 0;
    
    while (1) {
        GSresRegisterResource(0, group, modelBaseId | i, 0);
        offset += 4;
        i++;
        
        u32 next = modelList[offset / 4];
        if (next == 0) {
            break;
        }
    }
    
    return archive;
}

/*
 * floorReadObjPreFunc
 * Original address: 0x8002E7E0
 * Size: 0x84 bytes
 * 
 * Pre-function for object resource allocation
 */
void* floorReadObjPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign(size + 0x60, 0x20, group, id, 0);
    if (resource == 0) {
        return 0;
    }
    GSresLockResource(group, id);
    
    return (void*)((u32)resource + 0x60);
}

/*
 * floorReadMapPostFunc
 * Original address: 0x8002E864
 * Size: 0x16C bytes
 * 
 * Post-function callback for map loading (registers models, lights, cameras, fog)
 */
void* floorReadMapPostFunc(u32 group, u32 id) {
    void* archive;
    u32* modelList;
    u32* lightList;
    u32* fogList;
    u32 modelBaseId;
    u32 lightBaseId;
    u32 i;
    u32 offset;
    
    archive = _makeArchiveHeader(group, id, 0);
    if (archive == 0) {
        return 0;
    }
    
    // Register models
    modelList = (u32*)*((u32*)archive);
    if (modelList != 0) {
        modelBaseId = floorReadMakeModelResID(id);
        i = 0;
        offset = 0;
        
        while (1) {
            GSresRegisterResource(0, group, modelBaseId | i, 0);
            offset += 4;
            i++;
            
            u32 next = modelList[offset / 4];
            if (next == 0) {
                break;
            }
        }
    }
    
    // Load and register lights
    lightList = (u32*)*((u32*)archive + 2);
    if (lightList != 0) {
        lightBaseId = floorReadMakeLightResID(id);
        i = 0;
        offset = 0;
        
        while (1) {
            void* light = GSlightLoad(group, lightBaseId | i);
            if (light != 0) {
                GSresRegisterResource(light, group, lightBaseId | i, 0);
            }
            offset += 4;
            i++;
            
            u32 next = lightList[offset / 4];
            if (next == 0) {
                break;
            }
        }
        
        floorSetLightInfo(lightBaseId, i);
    } else {
        floorSetLightInfo(0, 0);
    }
    
    // Register camera
    {
        u32 cameraId = floorReadMakeCameraResID(id);
        _registerCamera(group, cameraId, archive);
    }
    
    // Register fog
    fogList = (u32*)*((u32*)archive + 3);
    if (fogList != 0) {
        u32* fogData = (u32*)*((u32*)fogList);
        if (fogData != 0) {
            u32 fogId = floorReadMakeFogResID(id);
            GSresRegisterResource(0, group, fogId, (void*)fogData);
        }
    }
    
    floorInitMap(group, id);
    
    return archive;
}

/*
 * floorReadMapPreFunc
 * Original address: 0x8002E9D0
 * Size: 0x8C bytes
 * 
 * Pre-function for map resource allocation
 */
void* floorReadMapPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F + 0x60, 0x20, group, id, 0);
    if (resource == 0) {
        return 0;
    }
    floorDataBiosGetCurrentPtr();
    floorDataBiosSetMapResID(id);
    GSresLockResource(group, id);
    
    return (void*)((u32)resource + 0x60);
}

/*
 * floorReadScriptPostFunc
 * Original address: 0x8002EA5C
 * Size: 0x8C bytes
 * 
 * Post-function callback for script loading
 */
void* floorReadScriptPostFunc(u32 group, u32 id) {
    void* resource;
    s32 isPop;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    
    isPop = floorIsPop();
    if (isPop == 0) {
        if (resource != 0) {
            floorMappingScript(resource);
        }
        {
            s32 soundResult = floorSound_playEnvSound(group, id);
            if (soundResult == 0) {
                soundStopEnv();
            }
        }
        floorExecSoundScript(group, id);
    }
    
    return resource;
}

/*
 * floorReadScriptPreFunc
 * Original address: 0x8002EAE8
 * Size: 0x90 bytes
 * 
 * Pre-function for script resource allocation
 */
void* floorReadScriptPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    s32 isPop;
    
    isPop = floorIsPop();
    if (isPop != 0) {
        return 0;
    }
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadFontPostFunc
 * Original address: 0x8002EB78
 * Size: 0x78 bytes
 * 
 * Post-function callback for font loading
 */
void* floorReadFontPostFunc(u32 group, u32 id) {
    void* resource;
    s32 isPop;
    
    isPop = floorIsPop();
    if (isPop != 0) {
        return 0;
    }
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    if (resource != 0) {
        GSmsgFontOpen(resource);
    }
    
    return resource;
}

/*
 * floorReadFontPreFunc
 * Original address: 0x8002EBF0
 * Size: 0x90 bytes
 *
 * Pre-function for font resource allocation
 */
void* floorReadFontPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    s32 isPop;
    
    isPop = floorIsPop();
    if (isPop != 0) {
        return 0;
    }
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadMsgPostFunc
 * Original address: 0x8002EC80
 * Size: 0xB8 bytes
 *
 * Post-function callback for message data loading
 */
void* floorReadMsgPostFunc(u32 group, u32 id) {
    void* resource;
    s32 isPop;
    s32 language;
    s32 msgLanguage;
    
    isPop = floorIsPop();
    if (isPop != 0) {
        return 0;
    }
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    
    language = pokecoloGetLanguage();
    msgLanguage = fn_8010B208(resource);
    if (msgLanguage != language) {
        GSresFreeResource(group, id);
        return resource;
    }
    
    if (resource != 0) {
        GSmsgOpen(resource);
    }
    
    return resource;
}

/*
 * floorReadMsgPreFunc
 * Original address: 0x8002ED38
 * Size: 0x90 bytes
 *
 * Pre-function for message data allocation
 */
void* floorReadMsgPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    s32 isPop;
    
    isPop = floorIsPop();
    if (isPop != 0) {
        return 0;
    }
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    GSresLockResource(group, id);
    
    return resource;
}

/*
 * floorReadNormalPreFunc
 * Original address: 0x8002EDC8
 * Size: 0x38 bytes
 *
 * Normal pre-function for resource allocation (no unload callback)
 */
void* floorReadNormalPreFunc(u32 group, u32 id, u32 size) {
    void* resource;
    
    resource = GSresAllocResourceAlign((size + 0x1F) & ~0x1F, 0x20, group, id, 0);
    
    return resource;
}

// ============================================================
// Helper functions
// ============================================================

/*
 * _registerCamera
 * Original address: 0x8002EE00
 * Size: 0x60 bytes
 *
 * Registers a camera resource with unload callback
 */
void _registerCamera(u32 group, u32 id, void* scene) {
    if (scene != 0) {
        u32 cameraId = *((u32*)scene + 1);
        void* camera = GScameraLoad(group, cameraId);
        if (camera != 0) {
            GSresRegisterResource(camera, group, id, 0);
        }
    }
}

/*
 * _makeArchiveHeader
 * Original address: 0x8002EE60
 * Size: 0x74 bytes
 *
 * Creates an archive header by parsing resource data
 */
void* _makeArchiveHeader(u32 group, u32 id, u32 size) {
    void* resource;
    void* archive;
    
    GSresUnlockResource(group, id);
    resource = GSresGetResource(group, id);
    archive = HSD_ArchiveParse(resource, (u32)resource + 0x60, size);
    return HSD_ArchiveGetPublicAddress(archive, "scene_data");
}

// ============================================================
// Unload callbacks
// ============================================================

/*
 * _unloadObject
 * Original address: 0x8002EED4
 * Size: 0xAC bytes
 *
 * Unload callback for object resources - frees all sub-models
 */
void _unloadObject(void* data, u32 group, u32 id) {
    void* resource;
    void* scene;
    u32* modelList;
    u32 modelBaseId;
    u32 i;
    u32 offset;
    
    resource = GSresGetResource(group, id);
    if (resource == 0) {
        return;
    }
    
    scene = HSD_ArchiveGetPublicAddress(resource, "scene_data");
    modelList = (u32*)*((u32*)scene);
    if (modelList == 0) {
        return;
    }
    
    modelBaseId = floorReadMakeModelResID(id);
    i = 0;
    offset = 0;
    
    while (1) {
        GSresFreeResource(group, modelBaseId | i);
        offset += 4;
        i++;
        
        u32 next = modelList[offset / 4];
        if (next == 0) {
            break;
        }
    }
}

/*
 * _unloadWZX
 * Original address: 0x8002EF80
 * Size: 0x24 bytes
 *
 * Unload callback for Waza sequence resources
 */
void _unloadWZX(void* data, u32 group, u32 id) {
    WazaSequence::Unload((const char*)data);
}

/*
 * _unloadPKX
 * Original address: 0x8002EFA4
 * Size: 0x2C bytes
 *
 * Unload callback for PKX (Pokémon model sequence) resources
 */
void _unloadPKX(void* data, u32 group, u32 id) {
    if (data != 0) {
        ModelSequence::Unload((const char*)data);
    }
}

/*
 * _unloadGSW
 * Original address: 0x8002EFD0
 * Size: 0x28 bytes
 *
 * Unload callback for GSW (Game Save Write) resources
 */
void _unloadGSW(void* data, u32 group, u32 id) {
    FlashSystemRelease(id);
}

/*
 * _unloadFlare
 * Original address: 0x8002EFF8
 * Size: 0x24 bytes
 *
 * Unload callback for lens flare resources
 */
void _unloadFlare(void* data, u32 group, u32 id) {
    GSlensFlareFree(group, id);
}

/*
 * _unloadParticles
 * Original address: 0x8002F01C
 * Size: 0x24 bytes
 *
 * Unload callback for particle resources
 */
void _unloadParticles(void* data, u32 group, u32 id) {
    GSparticleFree(group, id);
}

/*
 * _unloadCamera
 * Original address: 0x8002F040
 * Size: 0x24 bytes
 *
 * Unload callback for camera resources
 */
void _unloadCamera(void* data, u32 group, u32 id) {
    GScameraFree(group, id);
}

/*
 * _unloadLight
 * Original address: 0x8002F064
 * Size: 0x24 bytes
 *
 * Unload callback for light resources
 */
void _unloadLight(void* data, u32 group, u32 id) {
    GSlightFree(group, id);
}

/*
 * _unloadScript
 * Original address: 0x8002F088
 * Size: 0x4C bytes
 *
 * Unload callback for script resources
 */
void _unloadScript(void* data, u32 group, u32 id) {
    s32 isPush = floorIsPush();
    if (isPush == 0) {
        floorUnmappingScript(data);
    }
}

/*
 * _unloadFont
 * Original address: 0x8002F0D4
 * Size: 0x4C bytes
 *
 * Unload callback for font resources
 */
void _unloadFont(void* data, u32 group, u32 id) {
    s32 isPush = floorIsPush();
    if (isPush == 0) {
        GSmsgFontClose(data);
    }
}

/*
 * _unloadMsg
 * Original address: 0x8002F120
 * Size: 0x4C bytes
 *
 * Unload callback for message resources
 */
void _unloadMsg(void* data, u32 group, u32 id) {
    s32 isPush = floorIsPush();
    if (isPush == 0) {
        GSmsgClose(data);
    }
}

/*
 * _unloadColsys
 * Original address: 0x8002F16C
 * Size: 0x24 bytes
 *
 * Unload callback for collision system resources
 */
void _unloadColsys(void* data, u32 group, u32 id) {
    GScolsys2UnloadCCD(group, id);
}

/*
 * _unloadTexture
 * Original address: 0x8002F190
 * Size: 0x24 bytes
 *
 * Unload callback for texture resources
 */
void _unloadTexture(void* data, u32 group, u32 id) {
    GStextureFree(group, id);
}

/*
 * _unloadDeckData
 * Original address: 0x8002DBF8
 * Size: 0x2C bytes
 *
 * Unload callback for deck resources
 */
void _unloadDeckData(void* data, u32 group, u32 id) {
    // deckUnRegister(group, id);  // External function
}

/*
 * _unloadTextureForAnt
 * Original address: 0x8002DCFC
 * Size: 0x28 bytes
 *
 * Unload callback for antenna textures
 */
void _unloadTextureForAnt(void* data, u32 group, u32 id) {
    GStextureFree(group, (u32)antGetGStexture(data));
}

// ============================================================
// Resource ID generation functions
// ============================================================

/*
 * floorReadMakeFogResID
 * Original address: 0x8002F1B4
 * Size: 0xC bytes
 *
 * Creates a fog resource ID from floor ID
 */
u32 floorReadMakeFogResID(u32 floorId) {
    return (floorId << 16) | 0x1A00;
}

/*
 * floorReadMakeCameraResID
 * Original address: 0x8002F1C0
 * Size: 0xC bytes
 *
 * Creates a camera resource ID from floor ID
 */
u32 floorReadMakeCameraResID(u32 floorId) {
    return (floorId << 16) | 0x1800;
}

/*
 * floorReadMakeLightResID
 * Original address: 0x8002F1CC
 * Size: 0xC bytes
 *
 * Creates a light resource ID from floor ID
 */
u32 floorReadMakeLightResID(u32 floorId) {
    return (floorId << 16) | 0x1600;
}

/*
 * floorReadMakeModelResID
 * Original address: 0x8002F1D8
 * Size: 0xC bytes
 *
 * Creates a model resource ID from floor ID
 */
u32 floorReadMakeModelResID(u32 floorId) {
    return (floorId << 16) | 0x1000;
}

/*
 * floorReadMakeObjResID
 * Original address: 0x8002F1E4
 * Size: 0xC bytes
 *
 * Creates an object resource ID from floor ID
 */
u32 floorReadMakeObjResID(u32 floorId) {
    return (floorId << 16) | 0x0400;
}

// ============================================================
// FloorPostCallManager implementation
// ============================================================

/*
 * FloorPostCallManager::update
 * Original address: 0x8002F1F0
 * Size: 0x78 bytes
 *
 * Updates all pending post-call entries
 */
void FloorPostCallManager::update(void) {
    for (FloorPostCallEntry* entry = this->entries;
         entry != &this->entries[8];
         entry++) {
        if (entry->active != 0) {
            void (*func)(u32, u32, u32, void*) =
                (void (*)(u32, u32, u32, void*))entry->func;
            func(entry->group, entry->id, entry->param, this);
            memset(entry, 0, 0x14);
        }
    }
}

/*
 * FloorPostCallManager::add
 * Original address: 0x8002F268
 * Size: 0x40 bytes
 *
 * Adds a new post-call entry to the manager
 */
void FloorPostCallManager::add(u32 group, u32 id, u32 param, void* func, void* data) {
    for (FloorPostCallEntry* entry = this->entries;
         entry != &this->entries[8];
         entry++) {
        if (entry->active == 0) {
            entry->active = 1;
            entry->group = group;
            entry->id = id;
            entry->param = param;
            entry->func = func;
            return;
        }
    }
    // No space available - function returns without adding
}

/*
 * FloorPostCallManager::FloorPostCallManager
 * Original address: 0x8002F2A8
 * Size: 0x38 bytes
 *
 * Constructor - initializes manager with zeros
 */
FloorPostCallManager::FloorPostCallManager(void) {
    memset(this, 0, 0xA0);
}

// Global post-function manager instance
FloorPostCallManager _postFuncManager;

/*
 * __sinit_floorRead_cpp
 * Original address: 0x8002F2E0
 * Size: 0x28 bytes
 *
 * Static initialization function for floorRead.cpp
 * Called at program startup via .ctors section
 */
static void __sinit_floorRead_cpp(void) {
    _postFuncManager.FloorPostCallManager();
}
