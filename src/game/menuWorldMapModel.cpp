// Decompiled from menuWorldMapModel.cpp (0x8009D6B8 - 0x8009E664)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// File size: 0xFAC bytes | 21 functions

#include "system.h"

// ============================================================
// Forward declarations for external functions
// ============================================================
extern void* GSgfxLayerFindByID(u32 id);
extern void SetClearFlags__10GSgfxLayerFbbb(void* layer, u8 flag1, u8 flag2, u8 flag3);
extern void SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(void* layer, void* texture, u8 flag, u8* param);
extern void Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(
    u32 configId, u32 layerId, u32 targetId, void* offset);
extern void GStextureFree(void* texture);
extern void* GStextureCreate(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5);
extern void beginSurface__10GSgfxLayerFUs(void* layer, u16 format);
extern void endSurface__10GSgfxLayerFv(void* layer);

extern void* GSgfxVFBuildTemp(u32 param1, u32 param2, u32 param3, u32 param4, u32 param5,
                               u32 param6, u32 param7, u32 param8);
extern void spriteSetOffset(u32 layerId, u32 offsetX, u32 offsetY);
extern void spriteClearScissor(u32 layerId);
extern void spriteSetEnv(u32 layerId);
extern void GSmtx44Ortho(float* matrix, float left, float right, float bottom, float top,
                         float near, float far);
extern void* memcpy(void* dest, const void* src, u32 size);

extern void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(
    void* layer, u8 func, u8 src, void* mtx, u8 param, void* mtx2);
extern void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(
    void* layer, u8 channel, u8 alpha, u8 src1, u8 src2, u32 param, void* light, u8 type,
    u8 diffuseFunc);

extern u32 floorReadMakeModelResID(u32 floorId);
extern u32 floorReadMakeLightResID(u32 floorId);
extern void* GSresGetResourceAllGroup(u32 baseId);
extern void GSresRegisterResource(void* data, u32 group, u32 id, void* unloadFunc);
extern void GSresFreeResource(u32 group, u32 id);
extern void* GSmodelLoad(u32 baseId, u32 param);
extern void GSmodelFree(void* model);
extern void GSmodelSetRenderLayer(void* model, u32 layer, void* layerIdPtr);
extern void GSmodelSetVisibility(void* model, u32 visible);
extern s32 GSmodelCanAnimate(void* model);
extern void GSmodelSetAnimIndex(void* model, s32 index);
extern void GSmodelSetAnimRate(void* model, float rate);
extern void GSmodelStartAnimation(void* model);
extern s32 GSmodelCanTexAnimate(void* model);
extern void GSmodelSetTexAnimIndex(void* model, s32 index);
extern void GSmodelSetTexAnimRate(void* model, float rate);
extern void GSmodelStartTexAnimation(void* model);
extern void* GSmodelGetPart(void* model, u32 partId);
extern void GSmodelAttachToGSpart(void* model, void* part, u32 mode, void* param1, u32 param2);
extern void GSmodelDetachFromGSpart(void* model, u32 param);
extern void GSpartFree(void* part);
extern void* GSlightLoad(u32 baseId);
extern void GSlightFree(void* light);
extern void GSlightSetType(void* light, u32 type);
extern void GSlightSetActive(void* light, u32 active);
extern s32 GSlightCanAnimate(void* light);
extern void GSlightSetAnimIndex(void* light, s32 index);
extern void GSlightSetAnimRate(void* light, float rate);
extern void GSlightStartAnimation(void* light);
extern void floorSetLightInfo(u32 lightId, u32 count);
extern void* GSparticleCreateGenerator(u32 param1, u32 param2, u32 param3);
extern void GSparticleAttachGeneratorToGSpart(void* generator, void* part, u32 param1, u32 param2,
                                               u32 param3, u32 param4);
extern void GSparticleDetachGeneratorFromGSpart(void* generator, u32 param);
extern void* HSD_ArchiveGetPublicAddress(void* archive, const char* name);

extern void GSlogWrite(const char* format, ...);

extern void* GSmodelGetAnimFrameCount(void* model, u32 param);
extern float GSmodelGetAnimFrame(void* model);
extern void GSmodelStopAnimation(void* model);
extern s32 GSmodelIsAnimating(void* model);
extern void GSmodelSetAnimFrame(void* model, float frame);
extern void GSmodelSetAnimType(void* model, u32 type);

// ============================================================
// External data references
// ============================================================
// sdata2 constants
static float const FLOAT_255 = 255.0f;    // @2258
static float const FLOAT_0 = 0.0f;        // @2259
static float const FLOAT_480 = 480.0f;    // @2260
static float const FLOAT_640 = 640.0f;    // @2261
static float const FLOAT_NEG30000 = -30000.0f; // @2262
static float const FLOAT_30000 = 30000.0f;     // @2263
static float const FLOAT_0_5 = 0.5f;              // @2310

// sbss2
static u32 s_unnamed_2097; // @2097

// rodata strings
static const char STR_ERROR_MODEL[] = "Error! %s: couldn't load model %d\n";
static const char STR_SCENE_DATA[] = "scene_data";
static const char STR_FUNCTION_SETMODEL[] = "SetModel";

// ============================================================
// WorldMapModel class methods
// ============================================================

/*
 * WorldMapModel::releaseOffscreenData()
 * Original address: 0x8009D6B8
 * Size: 0x88 bytes
 *
 * Releases offscreen rendering resources for WorldMapModel.
 * Clears texture copy flags and frees associated GStexture.
 */
void releaseOffscreenData__13WorldMapModelFv(void* self) {
    void* layer;

    layer = GSgfxLayerFindByID(2);
    SetClearFlags__10GSgfxLayerFbbb(layer, 0, 0, 0);
    SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, 0, 0, 0);
    Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(2, 4, 1, 0);

    if (self != 0) {
        GStextureFree(*(void**)self);
        *(void**)self = 0;
    }
}

/*
 * WorldMapModel::renderOffscreenData(float)
 * Original address: 0x8009D740
 * Size: 0x644 bytes
 *
 * Renders offscreen data for the world map model.
 * Sets up vertex format, projection matrix, and various GSgfxLayer configuration.
 * Contains extensive direct memory manipulation of GSgfxLayer internal state.
 *
 * Register usage:
 *   r28 (r3) -> self (WorldMapModel*)
 *   r29 (r3) -> GSgfxLayer* (layer ID 4)
 *   r30 -> floating point value from stack
 *   r31 -> vertex format pointer
 *   f1 -> delta time parameter
 */
void renderOffscreenData__13WorldMapModelFf(void* self, float deltaTime) {
    void* layer;
    void* vf;
    u32 intAlpha;
    float matrix[16]; // Ortho matrix buffer on stack

    // Calculate integer alpha from delta time
    intAlpha = (u32)(FLOAT_255 * deltaTime);
    r30 = *(u32*)0x54; // Load from stack location

    if (intAlpha == 0) {
        return;
    }

    layer = GSgfxLayerFindByID(4);
    if (layer == 0) {
        return;
    }

    // Initialize local variables
    r0 = 0;
    r3 = 0;
    *(u32*)(sp + 0x8) = 0;

    // Build vertex format
    vf = GSgfxVFBuildTemp(0, 2, 0, 0, 1, 5, 1, 1);
    r31 = vf;

    // Configure sprite layer
    spriteSetOffset(4, 0, 0);
    spriteClearScissor(4);
    spriteSetEnv(4);

    // Setup orthographic projection matrix
    GSmtx44Ortho(matrix, FLOAT_0, FLOAT_480, FLOAT_640, FLOAT_NEG30000, FLOAT_30000, FLOAT_0);

    // Copy identity matrix to layer
    r0 = 1;
    memcpy((void*)((u32)layer + 0xd54), mtxIdent, 0x30);
    *(float*)((u32)layer + 0xd58) = matrix[0x10];
    *(float*)((u32)layer + 0xd5c) = matrix[0x1c];
    *(float*)((u32)layer + 0xd60) = matrix[0x24];
    *(float*)((u32)layer + 0xd64) = matrix[0x2c];
    *(float*)((u32)layer + 0xd68) = matrix[0x38];
    *(float*)((u32)layer + 0xd6c) = matrix[0x3c];

    // Copy vertex data from layer's vertex buffer
    r26 = *(void**)((u32)layer + 0x19a0);
    memcpy((void*)((u32)r26 + 4), (void*)((u32)r26 + 8), 4);

    // Configure layer rendering state
    r3 = *(u32*)((u32)r26 + 4);
    r0 = *(u32*)r3;
    r0 |= 1;
    *(u32*)r3 = r0;
    *(float*)((u32)layer + 0x1684) = FLOAT_0;
    *(float*)((u32)layer + 0x1688) = FLOAT_30000;

    // Check layer flags and configure rendering
    if (*(u8*)((u32)layer + 0x16a7) != 0) {
        if (*(u8*)((u32)layer + 0x16a6) != 0) {
            *(u32*)((u32)layer + 0x170c) |= 0x100;
            *(u32*)((u32)layer + 0x17c4) |= 0x100;
        }
        *(u32*)((u32)layer + 0x170c) |= 0x40;
        *(u32*)((u32)layer + 0x16a8) |= 0x40;
        *(u32*)((u32)layer + 0x17c4) |= 0x40;
        *(u32*)((u32)layer + 0x1760) |= 0x40;
    }

    // Configure texture generation and color unit settings
    // (Extensive direct memory manipulation of GSgfxLayer internal state)
    *(u32*)((u32)layer + 0x16ac) |= 0x20;
    tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(
        layer, 0, 1, 4, 0, 0);
    // ... additional layer configuration ...

    // Begin surface rendering
    *(u32*)((u32)layer + 0x16ac) |= 1;
    *(u32*)((u32)layer + 0x16a8) |= 1;
    *(u32*)((u32)layer + 0x1764) |= 1;
    *(u32*)((u32)layer + 0x1760) |= 1;
    tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc12GSgfxTgenSrcP5GSmtxbP5GSmtx(layer, ...);

    // Configure color unit
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(
        layer, ...);

    // ... more layer configuration ...

    // Write vertex data to offscreen surface
    // The vertex data is written directly to memory at 0xCC01 - 0x8000 = 0x4C01
    // This is a direct write to the GS command buffer
    r8 = 0;
    r7 = 0xCC01;
    *(u16*)(-0x8000 + r7) = 0;  // Position data
    r6 = 0xFF;
    r5 = 0x280;
    r4 = 1;
    *(u16*)(-0x8000 + r7) = 0;  // More position data
    r0 = 0x1E0;
    *(u8*)(-0x8000 + r7) = r6;  // Color/alpha data
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r30; // Alpha from calculated value
    *(u8*)(-0x8000 + r7) = r8;
    *(u8*)(-0x8000 + r7) = r8;
    *(u16*)(-0x8000 + r7) = r5;
    *(u16*)(-0x8000 + r7) = r8;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r30;
    *(u8*)(-0x8000 + r7) = r4;
    *(u8*)(-0x8000 + r7) = r8;
    *(u16*)(-0x8000 + r7) = r5;
    *(u16*)(-0x8000 + r7) = r0;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r30;
    *(u8*)(-0x8000 + r7) = r4;
    *(u8*)(-0x8000 + r7) = r4;
    *(u16*)(-0x8000 + r7) = r8;
    *(u16*)(-0x8000 + r7) = r0;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r6;
    *(u8*)(-0x8000 + r7) = r30;
    *(u8*)(-0x8000 + r7) = r8;
    *(u8*)(-0x8000 + r7) = r4;

    endSurface__10GSgfxLayerFv(layer);
}

/*
 * WorldMapModel::initializeOffscreenData()
 * Original address: 0x8009DD84
 * Size: 0x90 bytes
 *
 * Initializes offscreen rendering resources.
 * Creates a GStexture and configures the offscreen layer.
 */
void initializeOffscreenData__13WorldMapModelFv(void* self) {
    void* texture;
    void* layer;

    texture = GStextureCreate(0, 0, 0x45, 0, 0);
    *(void**)self = texture;

    if (texture != 0) {
        Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(2, 0, 1, 0);
        layer = GSgfxLayerFindByID(2);
        SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(layer, texture, 0, 0);
        SetClearFlags__10GSgfxLayerFbbb(layer, 1, 1, 1);
    }
}

/*
 * WorldMapModel::SetModel(unsigned long, unsigned long, bool)
 * Original address: 0x8009DE14
 * Size: 0x27C bytes
 *
 * Loads and configures models and lights for a floor.
 * Sets up animations and texture animations.
 *
 * Register usage:
 *   r23 (r3) -> self
 *   r24 (r4) -> floorId
 *   r25 (r5) -> groupId
 *   r26 -> model counter
 *   r27 -> model counter (backup)
 *   r28 -> archive header
 *   r29 -> model index
 *   r30 -> string pointer
 *   r31 -> model base ID
 */
void* SetModel__13WorldMapModelFUlUlb(void* self, u32 floorId, u32 groupId, bool animate) {
    void* archive;
    void* model;
    u32 modelBaseId;
    u32 lightBaseId;
    u32 i;
    u32* modelList;
    u32* lightList;

    archive = makeArchiveHeader__13WorldMapModelFUl(groupId);
    if (archive == 0) {
        return 0;
    }

    modelList = *(u32**)archive;
    if (modelList != 0) {
        modelBaseId = floorReadMakeModelResID(floorId);
        i = 0;
        do {
            model = GSmodelLoad(modelBaseId, 0);
            if (model == 0) {
                GSlogWrite(STR_FUNCTION_SETMODEL);
                GSlogWrite(STR_ERROR_MODEL);
            } else {
                GSresRegisterResource(model, self, modelBaseId | (i << 16),
                                       (void*)_unloadModel__FPvUlUl);
                GSmodelSetRenderLayer(model, 1, &s_unnamed_2097);
                GSmodelSetVisibility(model, 1);

                if (GSmodelCanAnimate(model)) {
                    GSmodelSetAnimIndex(model, 0);
                    GSmodelSetAnimRate(model, FLOAT_0_5);
                    GSmodelStartAnimation(model);
                }
                if (GSmodelCanTexAnimate(model)) {
                    GSmodelSetTexAnimIndex(model, 0);
                    GSmodelSetTexAnimRate(model, FLOAT_0_5);
                    GSmodelStartTexAnimation(model);
                }
            }
            i++;
        } while (modelList[i] != 0);
    }

    lightList = *(u32**)((u32)archive + 8);
    if (lightList != 0) {
        lightBaseId = floorReadMakeLightResID(floorId);
        i = 0;
        do {
            void* light = GSlightLoad(lightBaseId | (i << 16));
            if (light == 0) {
                GSlogWrite(STR_ERROR_LIGHT);
                GSlogWrite(STR_ERROR_LIGHT_DETAIL);
            } else {
                GSresRegisterResource(light, self, lightBaseId | (i << 16),
                                       (void*)_unloadLight__FPvUlUl);
                if (animate) {
                    if (i == 0) {
                        GSlightSetType(light, 0);
                    } else {
                        GSlightSetType(light, 1);
                    }
                    GSlightSetActive(light, 1);
                    if (GSlightCanAnimate(light)) {
                        GSlightSetAnimIndex(light, 0);
                        GSlightSetAnimRate(light, FLOAT_0_5);
                        GSlightStartAnimation(light);
                    }
                }
            }
            i++;
        } while (lightList[i] != 0);
    }

    return archive;
}

/*
 * WorldMapModel::UnloadModel(unsigned long, unsigned long)
 * Original address: 0x8009E090
 * Size: 0xEC bytes
 *
 * Unloads all models and lights for a floor.
 */
void UnloadModel__13WorldMapModelFUlUl(void* self, u32 floorId, u32 groupId) {
    void* archive;
    u32 modelBaseId;
    u32 lightBaseId;
    u32 i;
    u32* modelList;
    u32* lightList;

    archive = makeArchiveHeader__13WorldMapModelFUl(groupId);
    if (archive == 0) {
        return;
    }

    modelList = *(u32**)archive;
    if (modelList != 0) {
        modelBaseId = floorReadMakeModelResID(floorId);
        i = 0;
        do {
            GSresFreeResource(self, modelBaseId | (i << 16));
            i++;
        } while (modelList[i] != 0);
    }

    lightList = *(u32**)((u32)archive + 8);
    if (lightList != 0) {
        lightBaseId = floorReadMakeLightResID(floorId);
        i = 0;
        do {
            GSresFreeResource(self, lightBaseId | (i << 16));
            i++;
        } while (lightList[i] != 0);
        floorSetLightInfo(lightBaseId, i);
    } else {
        floorSetLightInfo(0, 0);
    }
}

/*
 * WorldMapModel::ObjectVisibility(unsigned long, bool)
 * Original address: 0x8009E17C
 * Size: 0x80 bytes
 *
 * Sets visibility for all models in a floor.
 */
void ObjectVisibility__13WorldMapModelFUlb(void* self, u32 floorId, u32 groupId, bool visible) {
    void* archive;
    u32 modelBaseId;
    u32 i;
    u32* modelList;

    archive = makeArchiveHeader__13WorldMapModelFUl(groupId);
    modelBaseId = floorReadMakeModelResID(floorId);

    modelList = *(u32**)archive;
    if (modelList != 0) {
        i = 0;
        do {
            Visibility__13WorldMapModelFUlb(self, modelBaseId | (i << 16), visible);
            i++;
        } while (modelList[i] != 0);
    }
}

/*
 * WorldMapModel::Visibility(unsigned long, bool)
 * Original address: 0x8009E1FC
 * Size: 0x40 bytes
 *
 * Sets visibility for a single model.
 */
void Visibility__13WorldMapModelFUlb(void* self, u32 modelId, bool visible) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model != 0) {
        GSmodelSetVisibility(model, visible);
    }
}

/*
 * WorldMapModel::ModelDetach(unsigned long)
 * Original address: 0x8009E23C
 * Size: 0x40 bytes
 *
 * Detaches a model from its GSpart parent.
 * Returns 1 on success, 0 if model not found.
 */
s32 ModelDetach__13WorldMapModelFUl(u32 modelId) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model == 0) {
        return 0;
    }
    GSmodelDetachFromGSpart(model, 1);
    return 1;
}

/*
 * WorldMapModel::ModelAttach(unsigned long, unsigned long, long, GSattachMode)
 * Original address: 0x8009E27C
 * Size: 0xA4 bytes
 *
 * Attaches a model to a parent model's GSpart.
 * Returns 1 on success, 0 if either model not found.
 */
s32 ModelAttach__13WorldMapModelFUlUll12GSattachMode(
    u32 childId, u32 parentId, s32 partId, u32 attachMode) {
    void* child;
    void* parent;
    void* part;

    child = GSresGetResourceAllGroup(childId);
    if (child == 0) {
        return 0;
    }
    parent = GSresGetResourceAllGroup(parentId);
    if (parent == 0) {
        return 0;
    }
    part = GSmodelGetPart(parent, partId);
    GSmodelAttachToGSpart(child, part, 7, 0, 1);
    GSpartFree(part);
    return 1;
}

/*
 * WorldMapModel::SetModelPartPaticle(unsigned long, unsigned long, long, GSattachMode, bool, bool, bool)
 * Original address: 0x8009E320
 * Size: 0x90 bytes
 *
 * Creates and attaches a particle generator to a model part.
 * Returns the particle generator pointer.
 */
void* SetModelPartPaticle__13WorldMapModelFUlUll12GSattachModebbb(
    u32 modelId, u32 particleId, s32 partId, u32 attachMode,
    bool param1, bool param2, bool param3) {
    void* model;
    void* part;
    void* generator;

    model = GSresGetResourceAllGroup(modelId);
    part = GSmodelGetPart(model, partId);
    generator = GSparticleCreateGenerator(particleId, 0, 0);
    GSparticleAttachGeneratorToGSpart(generator, part, attachMode, param1, param2, param3);
    GSpartFree(part);
    return generator;
}

/*
 * WorldMapModel::DetachModelPartPaticle(_GSparticleGen*, bool)
 * Original address: 0x8009E3B0
 * Size: 0x28 bytes
 *
 * Detaches a particle generator from its GSpart.
 */
void DetachModelPartPaticle__13WorldMapModelFP14_GSparticleGenb(void* generator, bool param) {
    GSparticleDetachGeneratorFromGSpart(generator, param);
}

/*
 * _unloadModel(void*, unsigned long, unsigned long)
 * Original address: 0x8009E3D8
 * Size: 0x24 bytes
 *
 * Callback function for GSresRegisterResource to unload models.
 */
s32 _unloadModel__FPvUlUl(void* model, u32 group, u32 id) {
    GSmodelFree(model);
    return 1;
}

/*
 * _unloadLight(void*, unsigned long, unsigned long)
 * Original address: 0x8009E3FC
 * Size: 0x24 bytes
 *
 * Callback function for GSresRegisterResource to unload lights.
 */
s32 _unloadLight__FPvUlUl(void* light, u32 group, u32 id) {
    GSlightFree(light);
    return 1;
}

/*
 * WorldMapModel::makeArchiveHeader(unsigned long)
 * Original address: 0x8009E420
 * Size: 0x30 bytes
 *
 * Gets the scene_data archive for a resource group.
 */
void* makeArchiveHeader__13WorldMapModelFUl(u32 groupId) {
    void* archive;
    void* resource;

    resource = GSresGetResourceAllGroup(groupId);
    archive = HSD_ArchiveGetPublicAddress(resource, STR_SCENE_DATA);
    return archive;
}

/*
 * WorldMapModel::GetAnimeFrameCount(unsigned long, unsigned long)
 * Original address: 0x8009E450
 * Size: 0x48 bytes
 *
 * Gets the animation frame count for a model.
 * Returns 0.0f if model not found.
 */
u32 GetAnimeFrameCount__13WorldMapModelFUlUl(u32 modelId, u32 animIndex) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model == 0) {
        return FLOAT_0;
    }
    return GSmodelGetAnimFrameCount(model, animIndex);
}

/*
 * WorldMapModel::GetAnimeFrame(unsigned long)
 * Original address: 0x8009E498
 * Size: 0x38 bytes
 *
 * Gets the current animation frame for a model.
 * Returns 0.0f if model not found.
 */
float GetAnimeFrame__13WorldMapModelFUl(u32 modelId) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model == 0) {
        return FLOAT_0;
    }
    return GSmodelGetAnimFrame(model);
}

/*
 * WorldMapModel::StopMotion(unsigned long)
 * Original address: 0x8009E4D0
 * Size: 0x30 bytes
 *
 * Stops animation on a model.
 */
void StopMotion__13WorldMapModelFUl(u32 modelId) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model != 0) {
        GSmodelStopAnimation(model);
    }
}

/*
 * WorldMapModel::CheckMotion(unsigned long)
 * Original address: 0x8009E500
 * Size: 0x48 bytes
 *
 * Checks if a model is currently animating.
 * Returns 1 if animating, 0 otherwise.
 */
s32 CheckMotion__13WorldMapModelFUl(u32 modelId) {
    void* model;
    s32 result;

    model = GSresGetResourceAllGroup(modelId);
    if (model == 0) {
        return 0;
    }
    result = GSmodelIsAnimating(model);
    result &= 0xFF; // clrlwi r3, r3, 24
    // Convert to boolean: (result | -result) >> 31 gives 1 if non-zero
    result = -result | result;
    return (s32)(result >> 31) ^ 1;
}

/*
 * WorldMapModel::SetMotion(unsigned long, short, float, bool)
 * Original address: 0x8009E548
 * Size: 0xB4 bytes
 *
 * Sets animation on a model with index, frame, rate, and loop flag.
 */
void SetMotion__13WorldMapModelFUlsfb(u32 modelId, s16 animIndex, float frame, bool loop) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model != 0) {
        GSmodelSetAnimIndex(model, animIndex);
        GSmodelSetAnimFrame(model, frame);
        GSmodelSetAnimRate(model, FLOAT_0_5);
        GSmodelSetAnimType(model, loop ? 1 : 0);
        GSmodelStartAnimation(model);
    }
}

/*
 * WorldMapModel::SetLayerID(unsigned long, long, GSgfxLayerID*)
 * Original address: 0x8009E5FC
 * Size: 0x44 bytes
 *
 * Sets the render layer for a model.
 */
void SetLayerID__13WorldMapModelFUllP12GSgfxLayerID(u32 modelId, s32 layer, void* layerIdPtr) {
    void* model;

    model = GSresGetResourceAllGroup(modelId);
    if (model != 0) {
        GSmodelSetRenderLayer(model, 1, layerIdPtr);
    }
}

/*
 * WorldMapModel::GetModelPtr(unsigned long)
 * Original address: 0x8009E640
 * Size: 0x24 bytes
 *
 * Gets a direct pointer to a model by resource ID.
 */
void* GetModelPtr__13WorldMapModelFUl(u32 modelId) {
    return GSresGetResourceAllGroup(modelId);
}
