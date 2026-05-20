// Decompiled from: menuMoveDemo.cpp
// Address range: 0x800A63DC..0x800A6D54 | size: 0x978

/* Forward declarations */
void    Release__14kyogreMoveDemoFv(void* thisptr);
void    Init__14kyogreMoveDemoFv(void* thisptr);
void    Main__14kyogreMoveDemoFv(void* thisptr);
s32     GetNextFloorID__14kyogreMoveDemoFv(void* thisptr);
void    cameraPlay__14kyogreMoveDemoFUllb(void* thisptr, u32 a, s32 b, bool c);
void    playBGM__14kyogreMoveDemoFUs(void* thisptr, u16 bgm);
void    releaseOffscreenData__13WorldMapModelFv(void* model);
void    DetachModelPartPaticle__13WorldMapModelFP14_GSparticleGenb(void* model, void* particle, bool b);
void    ModelDetach__13WorldMapModelFUl(void* model, u32 id);
void    SetModel__13WorldMapModelFUlUlb(void* thisptr, u32 modelId, u32 motionId, bool loop);
void    SetMotion__13WorldMapModelFUlsfb(void* thisptr, u32 modelId, s16 motion, f32 speed, bool loop);
void    ModelAttach__13WorldMapModelFUlUll12GSattachMode(void* thisptr, u32 parent, u32 child, u32 mode);
void    SetModelPartPaticle__13WorldMapModelFUlUll12GSattachModebbb(
            void* thisptr, u32 modelId, u32 particleId, u32 partId,
            u32 mode, bool a, bool b, bool c);
void    GSresGetResourceAllGroup(s32 group);
void    GSmodelSetBoundCheck(s32 a, s32 b);
s32     GetAnimeFrame__13WorldMapModelFUl(void* model, u32 id);
void    fadeSet(s32 type, f32 time);
s32     fadeCheck(s32 type);
void    GSthreadSwitch(void);
void    floorLink(s32 link);
void    floorSetFadeScript(s32 a, s32 script);
void    cameraSetType(s32 type);
void    cameraPlayAnime(void* camera, u32 a, s32 b);
void    GScameraGetPerspective(void* camera, f32* out);
void    GScameraSetPerspective(void* camera, f32 near, f32 far, f32 fov);
void    soundStopEnv(s32 id);
void    GSsndPlayNow(s32 id);
void    GSsndStopNow(s32 id);
s32     floorGetCurrentGroupID(void);
void    GSgfxVideoSetLockFrameRate(s32 rate);
void    floorChange(s32 floorId);
void    __ct__10glowEffectFv(void* thisptr);
void    Start__8GSeffectFv(void* thisptr);

/* SData */
static u8 _AnimeLoop = 1;
static u8 _testExitFlag = 1;
static f32 _glowstrngth = 1.0f;
static u8 _glowwidth = 0x14;
static u8 _glowblend = 1;
static u8 _glownormalize = 1;
static u8 _glowsamples = 1;
static f32 _fadeFrame = 40.0f;
static f32 _fadeTime = 0.7f;

/* SBSS */
extern void* pMDemo;
static s32 _movdemo_type;
static u8 _glowmethod;

/* SData2 */
static const f32 _Zero = 0.0f;
static const f32 _FarPlane = 50000.0f;
static const f64 _One = 1.0;

/*
  Address: 0x800A63DC | size: 0x74
  kyogreMoveDemo::~kyogreMoveDemo()
  Destructor for kyogreMoveDemo class.
*/
void kyogreMoveDemo::~kyogreMoveDemo() {
    Release__14kyogreMoveDemoFv(this);
    if (this && *(void**)this != 0) {
        releaseOffscreenData__13WorldMapModelFv(*(void**)this);
    }
}

/*
  Address: 0x800A6450 | size: 0x38
  kyogreMoveDemo::kyogreMoveDemo()
  Constructor for kyogreMoveDemo class.
*/
void kyogreMoveDemo::kyogreMoveDemo() {
    *(void**)this = 0;
    Init__14kyogreMoveDemoFv(this);
}

/*
  Address: 0x800A6488 | size: 0xE8
  kyogreMoveDemo::Release()
  Releases all resources for the move demo.
*/
void kyogreMoveDemo::Release() {
    if (pMDemo) {
        void* model = *(void**)((u8*)this + 8);
        if (model) {
            // Detach particle effects
            for (s32 i = 0; i < 4; i++) {
                s32 particle = *(s32*)((u8*)model + 0x2C + i * 4);
                if (particle != 0) {
                    DetachModelPartPaticle__13WorldMapModelFP14_GSparticleGenb(this, particle, 1);
                }
            }
            // Detach models
            ModelDetach__13WorldMapModelFUl(this, *(u32*)((u8*)model + 0x10));
            ModelDetach__13WorldMapModelFUl(this, 0x21AC1000);
        }
        // Cleanup glow effect
        void* glow = *(void**)((u8*)this + 4);
        if (glow) {
            void* vtable = *(void**)glow;
            if (vtable) {
                void* func = *(void**)((u8*)vtable + 0x1C);
                ((void(*)(void*, s32))func)(glow, 1);
            }
            ::operator delete(glow);
            *(void**)((u8*)this + 8) = 0;
        }
    }
}

/*
  Address: 0x800A6570 | size: 0xD8
  kyogreMoveDemo::Main()
  Main loop for the move demo.
*/
void kyogreMoveDemo::Main() {
    if (pMDemo) {
        while (1) {
            if (_testExitFlag) {
                u32 frame = GetAnimeFrame__13WorldMapModelFUl(*(u32*)((u8*)this + 8), *(u32*)((u8*)this + 0x18));
                f32 diff = *(f32*)((u8*)this + 0x24) - _fadeFrame;
                if (diff >= 0.0f || diff > 0.0f) break;
            }
            GSthreadSwitch();
        }
        fadeSet(3, _fadeTime);
        while (fadeCheck(0) == 0) {
            GSthreadSwitch();
        }
        s32 nextFloor = GetNextFloorID__14kyogreMoveDemoFv(this);
        if (nextFloor != 0) {
            s32 type = *(s32*)((u8*)this + 4);
            floorLink(type == 1 ? 0xA : 0);
            floorSetFadeScript(0, 0x596008);
        }
    }
}

/*
  Address: 0x800A6648 | size: 0x88
  kyogreMoveDemo::GetNextFloorID()
  Gets the next floor ID based on demo type and flags.
*/
s32 kyogreMoveDemo::GetNextFloorID() {
    s32 type = *(s32*)((u8*)this + 4);
    switch (type) {
        case 1:
            return *(s32*)((u8*)worldmapXD_data + 0x118);
        case 0: {
            s32 flagId = *(s32*)((u8*)worldmapXD_data + 0x1D8);
            s32 flagVal = GSflagGet(flagId);
            if (flagVal < 2) {
                GSflagSet(flagId, 2);
                return 0x56;
            }
            return *(s32*)((u8*)worldmapXD_data + 0x1F0);
        }
        default:
            return 0;
    }
}

/*
  Address: 0x800A66D0 | size: 0x50C
  kyogreMoveDemo::Init()
  Initializes the move demo with models, particles, and camera.
*/
void kyogreMoveDemo::Init() {
    *(void**)((u8*)this + 8) = ::operator new(0x3C);
    memset(*(void**)((u8*)this + 8), 0, 0x3C);
    *(void**)((u8*)this + 4) = ::operator new(0x18);
    if (*(void**)((u8*)this + 4)) {
        __ct__10glowEffectFv(*(void**)((u8*)this + 4));
    }
    
    *(s32*)((u8*)this + 4) = _movdemo_type;
    soundStopEnv(0x3E8);
    
    if (!*(s32*)((u8*)this + 4)) {
        playBGM__14kyogreMoveDemoFUs(this, 0x53D);
    }
    GSsndPlayNow(0x5B8);
    
    *(s32*)((u8*)this + 0xC) = 0x1B87400;
    *(s32*)((u8*)this + 0x10) = 0x21AC1000;
    *(s32*)((u8*)this + 8) = floorGetCurrentGroupID();
    GSgfxVideoSetLockFrameRate(1);
    
    // Setup models and motions based on type
    s32 type = *(s32*)((u8*)this + 4);
    // ... (model setup code)
    
    // Setup glow effect
    void* glow = *(void**)((u8*)this + 4);
    if (glow) {
        *(f32*)((u8*)glow + 0xC) = _glowstrngth;
        ((u8*)glow)[0x10] = _glowwidth;
        ((u8*)glow)[0x11] = _glowblend;
        ((u8*)glow)[0x12] = _glownormalize;
        ((u8*)glow)[0x13] = _glowmethod;
        ((u8*)glow)[0x14] = _glowsamples;
        Start__8GSeffectFv(glow);
    }
    
    // Load and attach models
    // ... (model loading code)
    
    // Setup camera
    f32 perspective[4];
    GScameraGetPerspective(*(void**)((u8*)this + 0x28), perspective);
    GScameraSetPerspective(*(void**)((u8*)this + 0x28), perspective[0], perspective[1], perspective[2], _FarPlane);
}

/*
  Address: 0x800A6BDC | size: 0x8C
  kyogreMoveDemo::cameraPlay(u32 camera, s32 a, bool loop)
  Plays camera animation.
*/
void kyogreMoveDemo::cameraPlay(u32 camera, s32 a, bool loop) {
    cameraSetType(4);
    f64 time = (loop & 0x8000) ? 0.0 : _One;
    cameraPlayAnime(*(void**)camera, a, loop);
    GSresGetResourceAllGroup(camera);
}

/*
  Address: 0x800A6C68 | size: 0x2C
  kyogreMoveDemo::playBGM(u16 bgm)
  Plays BGM for the demo.
*/
void kyogreMoveDemo::playBGM(u16 bgm) {
    soundOpenPlay(bgm, 0, 0x7F);
}

/*
  Address: 0x800A6C94 | size: 0x38
  menuMoveDemoExit(void)
  Exits the move demo menu.
*/
void menuMoveDemoExit(void) {
    GSsndStopNow(0x5B8);
    if (pMDemo) {
        kyogreMoveDemo::~kyogreMoveDemo(pMDemo);
        pMDemo = 0;
    }
}

/*
  Address: 0x800A6CCC | size: 0x24
  menuMoveDemoMain(void)
  Main function for move demo menu.
*/
void menuMoveDemoMain(void) {
    if (pMDemo) {
        Main__14kyogreMoveDemoFv(pMDemo);
    }
}

/*
  Address: 0x800A6CF0 | size: 0x3C
  menuMoveDemoInit(void)
  Initializes the move demo menu.
*/
void menuMoveDemoInit(void) {
    pMDemo = ::operator new(0xC);
    if (pMDemo) {
        kyogreMoveDemo::kyogreMoveDemo(pMDemo);
    }
}

/*
  Address: 0x800A6D2C | size: 0x28
  menuMoveDemo(s32 type)
  Entry point for the move demo.
*/
void menuMoveDemo(s32 type) {
    _movdemo_type = type;
    floorChange(0x3A9);
}
