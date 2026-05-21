// Decompiled from: menuPdaDPMonitor.cpp
// Address range: 0x8004FB68..0x80050A1C | size: 0xEB4
// Functions: 25 | Data objects: 3

/*
  PDA Dark Pokemon Monitor menu.
  Displays information about Dark Pokemon including model, name, sex, ball, etc.
  Uses menuPdaDPM class with callback-based rendering.
*/

#include "global.h"
#include <dolphin/types.h>

// Forward declarations
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct DPM_CONTENTS;
struct CURSOR {
    s16 field_0;
    s16 field_2;
};
struct DarkPokemon;

// External data
/*
  Jump table for menuPdaDPMCallBack dispatch.
  Maps menu item IDs (0x61-0x6c) to display functions.
*/
static const void* const callback_jump_table[] = {
    (void*)0x8004FC10,  // 0x61: PokemonBall
    (void*)0x8004FBC8,  // 0x62: DarkPokemonRibbon
    (void*)0x8004FC18,  // 0x63: NOP
    (void*)0x8004FC18,  // 0x64: NOP
    (void*)0x8004FC18,  // 0x65: NOP
    (void*)0x8004FC18,  // 0x66: NOP
    (void*)0x8004FBE0,  // 0x67: DarkPokemonRelive
    (void*)0x8004FBBC,  // 0x68: DispPokemonModel
    (void*)0x8004FBD4,  // 0x69: DarkPokemonInfo
    (void*)0x8004FBEC,  // 0x6a: DarkPokemonPlace
    (void*)0x8004FC18,  // 0x6b: NOP
    (void*)0x8004FC04,  // 0x6c: PokemonSex
    (void*)0x8004FBF8,  // default: PokemonName
};

// Global state
static menuPdaDPM* _pDPM;
static CURSOR _cursor;

// Constants for model rendering
static const float ANGLE_MIN = 0.0f;
static const float ANGLE_MAX = 0.3f;
static const float ZOOM_VAL = 0.85f;
static const float ONE = 1.0f;

// Class declaration
class menuPdaDPM {
public:
    void* field_0;
    // ... other fields ...
    void* model;  // at offset 0xc8
    
    menuPdaDPM(CURSOR* cursor);
    ~menuPdaDPM();
    
    void Release();
    void LoadPokemon(CURSOR* cursor);
    void Init(CURSOR* cursor);
    void Main(CURSOR* cursor);
    void Button(tagWINDOW_WORK* work);
    void Ctrl(tagWINDOW_WORK* work);
    void Cursor(tagWINDOW_WORK* work);
    void SetViewFlag(CURSOR* cursor);
    void DispPokemonModel(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void DarkPokemonRelive(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void DarkPokemonRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void DarkPokemonInfo(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void DarkPokemonPlace(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void PokemonName(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void PokemonSex(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void PokemonBall(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content);
    void _menuClose(long menuId);
    void* GetPokemonPointer(long param);
};

// External function declarations
void windowGetKeyInfo();
void windowGetKeyRepeat();
u32 windowGetActiveID();
void menuOpenCustom(u32 menuId, tagWINDOW_WORK* work, u32 param4, u32 param5, u32 param6, u32 param7, u32 param8);
void menuCloseCustom(u32 menuId, u32 param2, u32 param3);
void menuClose(long menuId);
void menuCloseSync(long menuId, u32 param2);
void* menuItemBiosGetPtr(u32 type, u32 id);
void menuModelInit(void* model, u16 param2, u16 param3);
void menuModelLoadPokemon(void* model, void* pokemon);
void menuModelTerm(void* model);
u32 menuModelCheck(void* model, u32 param2);
void menuModelAdjustCamera(void* model, void* bios);
void menuModelSetAngle(void* model, float* angles);
void menuModelSetSize(void* model, u16 param2, u16 param3, u16 param4, u16 param5);
void menuModelSetZoom(void* model, float zoom);
void* menuModelRender(void* model);
void menuPlaySe(tagWINDOW_WORK* work, u32 seId);
void winSeqCheckMove(tagWINDOW_WORK* work);
void winSeqSetMenu(tagWINDOW_WORK* work, u32 menuId);
u32 winSpriteGetLayerID(tagWINDOW_WORK* win, tagSPRITE_WORK* spr);
void windowDrawSprite(u32 param1, u32 param2, u32 param3, tagSPRITE_WORK* spr, u32 param5, u32 param6, u32 param7);
void GSsndPlayNow(u32 soundId);
void* GSgfxLayerFindByID(u32 id);
void* GSgfxVFGetPredef(u32 type, u32 param2);
void setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(void* layer, void* vf);
void beginSurface__10GSgfxLayerFUs(void* layer, u16 param2);
void endSurface__10GSgfxLayerFv(void* layer);
void* GSmsgGetGSchar(u32 msgId);
void msgctrlSetValue(u32 ctrlId, void* value);
void GSmsgPrint2(u32 layerId, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6, u32 param7);
void* __nw__FUl(u32 size);
void __dl__FPv(void* ptr);
void* gamedataGetStatus(u32 id, u32 param2);
void pokemonCreate(void* out, u32 species, u32 param3);
void pokemonSetCatchStatus(void* pokemon, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
u32 pokemonCheckValid(void* pokemon);
u32 pokemonGetStatus(void* pokemon, u32 param2, u32 param3, u32 param4);
void pokemonBiosSetRnd(void* pokemon, u32 rnd);
u32 pokemonGetSex(void* pokemon);
void pokemonCreateRndFit(void* out, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
void pokemonBiosSetDarkpokemonDataId(void* pokemon, u32 dataId);

// DarkPokemon class methods
DarkPokemon* darkPokemonGetDarkPokemon(u32 id);
u32 isUpdate__11DarkPokemonCFv(DarkPokemon* dp);
void setUpdate__11DarkPokemonFb(DarkPokemon* dp, u8 flag);
u32 getStatus__11DarkPokemonCFv(const DarkPokemon* dp);
u32 getCatchFloorId__11DarkPokemonCFv(const DarkPokemon* dp);
u32 getPokemonID__11DarkPokemonCFv(const DarkPokemon* dp);
void* getOrgTrainer__11DarkPokemonCFv(const DarkPokemon* dp);
void* getTrainerName__11DarkPokemonCFv(const DarkPokemon* dp);
u32 getRnd__11DarkPokemonCFv(const DarkPokemon* dp);
u32 isSnach__11DarkPokemonCFv(const DarkPokemon* dp);
u32 getCatchBallID__11DarkPokemonCFv(const DarkPokemon* dp);
u32 getDarkPointDirect__11DarkPokemonCFv(const DarkPokemon* dp);
u32 isRelive__11DarkPokemonCFv(const DarkPokemon* dp);

// menuPdaDPMList functions
void menuPdaDPMListDispRelive(u32 index, u32 param2, u32 param3, u32 param4, u32 param5, u32 param6);
u32 menuPdaDPMListGetDPNum();
u32 menuPdaDPMListGetDarkPokemonID(u32 index);
u32 menuPdaDPMListGetDPointer(u32 index);
u32 menuPdaDPMListGetPokemonID(u32 index);
void* menuPdaDPMListGetPokemonName(u32 index);
u32 menuPdaDPMListGetDarkpokemonID(u32 index);
u32 menuPdaDPMListGetDarkPokemonPlaceMsgID(u32 index, u32* out);
u32 menuPdaDPMListGetDarkPokemonPlace(u32 index);

// Other external functions
u32 floorGetPlaceName(u32 floorId);
u32 mballBiosGetSpriteID(u32 ballId);
void menuPdaSetSubres(u32 param1, u32 param2);
void menuDrawReliveUpdate();

/*
  Address: 0x8004FB68 | size: 0xC4
  Callback dispatcher for PDA Dark Pokemon Monitor.
  Uses jump table to dispatch to appropriate display function based on menu item ID.
*/
void menuPdaDPMCallBack(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    if (_pDPM == NULL) {
        return;
    }
    
    u8 itemId = spr->field_2 - 0x61;
    if (itemId > 0xc) {
        return;
    }
    
    // Dispatch using jump table
    void (*func)() = (void (*)())callback_jump_table[itemId];
    func();
}

/*
  Address: 0x8004FC2C | size: 0x30
  Button handler wrapper.
*/
void menuPdaDPMButton(tagWINDOW_WORK* work) {
    if (_pDPM != NULL) {
        _pDPM->Button(work);
    }
}

/*
  Address: 0x8004FC5C | size: 0x3C
  Cursor handler wrapper.
*/
u32 menuPdaDPMCursor(tagWINDOW_WORK* work) {
    if (_pDPM == NULL) {
        return 0;
    }
    _pDPM->Cursor(work);
    return 0;
}

/*
  Address: 0x8004FC98 | size: 0x3C
  Control handler wrapper.
*/
u32 menuPdaDPMCtrl(tagWINDOW_WORK* work) {
    if (_pDPM == NULL) {
        return 0;
    }
    _pDPM->Ctrl(work);
    return 0;
}

/*
  Address: 0x8004FCD4 | size: 0x70
  Main entry point for PDA Dark Pokemon Monitor.
  Allocates menuPdaDPM, runs Main(), then destructs and frees.
*/
void menuPdaDPMon(CURSOR* cursor) {
    menuPdaDPM* instance = (menuPdaDPM*)__nw__FUl(0x1b4);
    if (instance != NULL) {
        instance->menuPdaDPM(cursor);
    }
    _pDPM = instance;
    if (instance != NULL) {
        instance->Main(cursor);
    }
    instance->~menuPdaDPM();
    _cursor.field_0 = 0;
    _pDPM = NULL;
}

/*
  Address: 0x8004FD44 | size: 0x58
  Destructor for menuPdaDPM.
  Calls Release() and conditionally deletes the object.
*/
menuPdaDPM::~menuPdaDPM() {
    if (this != NULL) {
        this->Release();
    }
    // Second parameter is delete flag
    // If non-zero and positive, delete the object
}

/*
  Address: 0x8004FD9C | size: 0x30
  Constructor for menuPdaDPM.
  Calls Init() with the cursor parameter.
*/
menuPdaDPM::menuPdaDPM(CURSOR* cursor) {
    this->Init(cursor);
}

/*
  Address: 0x8004FDCC | size: 0x24
  Release() - Terminates the Pokemon model.
*/
void menuPdaDPM::Release() {
    menuModelTerm(this->model);
}

/*
  Address: 0x8004FDF0 | size: 0x48
  LoadPokemon() - Loads the Pokemon model from cursor position.
*/
void menuPdaDPM::LoadPokemon(CURSOR* cursor) {
    u32 index = cursor->field_0 + cursor->field_2;
    void* pokemon = this->GetPokemonPointer(index);
    menuModelLoadPokemon(this->model, pokemon);
}

/*
  Address: 0x8004FE38 | size: 0x60
  Init() - Initializes the menuPdaDPM instance.
  Gets menu item bios, initializes model, and loads Pokemon.
*/
void menuPdaDPM::Init(CURSOR* cursor) {
    void* bios = menuItemBiosGetPtr(0x75, 0x68);
    u16 sizeW = ((u16*)bios)[5];
    u16 sizeH = ((u16*)bios)[6];
    menuModelInit(this->model, sizeW, sizeH);
    this->LoadPokemon(cursor);
}

/*
  Address: 0x8004FE98 | size: 0x88
  Main() - Main loop for PDA Dark Pokemon Monitor.
  Runs menuOpenCustom in a loop until -1 is returned, then closes.
*/
void menuPdaDPM::Main(CURSOR* cursor) {
    _cursor.field_2 = cursor->field_2;
    _cursor.field_0 = cursor->field_0;
    
    while (1) {
        u32 activeId = windowGetActiveID();
        s32 result = menuOpenCustom(0x75, (tagWINDOW_WORK*)(_cursor + 0x8), 
                                     activeId, 0, 0, 1, 1, 0);
        if (result == -1) {
            break;
        }
    }
    this->_menuClose(0x75);
    _cursor.field_0 = 0;
}

/*
  Address: 0x8004FF20 | size: 0x64
  Button() - Handles button input.
  Checks for sequence move and B button press.
*/
void menuPdaDPM::Button(tagWINDOW_WORK* work) {
    if (work == NULL) {
        return;
    }
    if (winSeqCheckMove(work) & 0xFF000000) {
        return;
    }
    windowGetKeyInfo();
    // Check for B button press (bit 26)
    if (work->field_26 & 0x4000000) {
        work->field_a4 = 1;
        work->field_a5 = 1;
    }
}

/*
  Address: 0x8004FF84 | size: 0xB4
  Ctrl() - Control/state machine for the menu.
  Handles menu state transitions based on work->field_1.
*/
void menuPdaDPM::Ctrl(tagWINDOW_WORK* work) {
    s8 state = work->field_1;
    
    if (state == 2) {
        menuDrawReliveUpdate();
        return;
    }
    
    if (state >= 0) {
        if (state == 0) {
            if (work->field_2 == 0) {
                winSeqSetMenu(work, 0x132);
                work->field_2 = 1;
                menuPdaSetSubres(0, 2);
            }
            return;
        }
        if (state < 4) {
            if (work->field_2 == 0) {
                winSeqSetMenu(work, 0x136);
                work->field_2 = 1;
            }
        }
    } else {
        if (state == -1) {
            // Handle negative state
        }
    }
}

/*
  Address: 0x80050038 | size: 0x17C
  Cursor() - Handles cursor movement and Pokemon selection.
  Manages cursor position within bounds and loads Pokemon on change.
*/
void menuPdaDPM::Cursor(tagWINDOW_WORK* work) {
    windowGetKeyInfo();
    u32 dpNum = menuPdaDPMListGetDPNum();
    windowGetKeyRepeat();
    
    CURSOR* cursor = &work->cursor;
    s16 index = cursor->field_0 + cursor->field_2;
    u32 maxIndex = dpNum;
    if (index >= (s16)dpNum) {
        maxIndex = 0xa;
    }
    
    // Handle cursor direction from key info
    s32 dir = work->keyInfo >> 16;
    
    if (dir < 0) {
        // Move up/left
        if (index != 0) {
            GSsndPlayNow(0x450);
        }
        cursor->field_2--;
    } else if (dir > 0) {
        // Move down/right
        if (index != 0) {
            GSsndPlayNow(0x450);
        }
        cursor->field_2++;
    }
    
    // Wrap cursor within bounds
    if (cursor->field_2 < 0) {
        cursor->field_0 += cursor->field_2;
        cursor->field_2 = 0;
        if (cursor->field_0 < 0) {
            cursor->field_0 += maxIndex;
            cursor->field_2 = maxIndex - 1;
        }
    } else if (cursor->field_2 >= (s16)maxIndex) {
        cursor->field_0 += cursor->field_2 - maxIndex + 1;
        cursor->field_2 = maxIndex - 1;
    }
    
    // Check if cursor changed
    if (index != (cursor->field_0 + cursor->field_2)) {
        this->SetViewFlag(cursor);
        this->LoadPokemon(cursor);
        menuPlaySe(work, 1);
    }
}

/*
  Address: 0x800501B4 | size: 0x5C
  SetViewFlag() - Sets the update flag for the Dark Pokemon.
*/
void menuPdaDPM::SetViewFlag(CURSOR* cursor) {
    u32 index = cursor->field_0 + cursor->field_2;
    u32 dpId = menuPdaDPMListGetDarkPokemonID(index);
    DarkPokemon* dp = darkPokemonGetDarkPokemon(dpId);
    if (isUpdate__11DarkPokemonCFv(dp)) {
        setUpdate__11DarkPokemonFb(dp, 0);
    }
}

/*
  Address: 0x80050210 | size: 0x214
  DispPokemonModel() - Renders the Pokemon model to the layer surface.
  Handles camera, angle, size, zoom, and vertex rendering.
*/
void menuPdaDPM::DispPokemonModel(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    float angles[2] = {ANGLE_MIN, ANGLE_MAX};
    
    if (menuModelCheck(this->model, 0) != 0) {
        return;
    }
    
    void* bios = menuItemBiosGetPtr(0x75, 0x68);
    menuModelAdjustCamera(this->model, bios);
    menuModelSetAngle(this->model, angles);
    
    u16 posW = ((u16*)bios)[3];
    u16 posH = ((u16*)bios)[4];
    u16 sizeW = ((u16*)bios)[5];
    u16 sizeH = ((u16*)bios)[6];
    menuModelSetSize(this->model, posW, posH, sizeW, sizeH);
    menuModelSetZoom(this->model, ZOOM_VAL);
    
    void* modelResult = menuModelRender(this->model);
    if (modelResult == NULL) {
        return;
    }
    
    u32 layerId = spr->field_1c;
    void* layer = GSgfxLayerFindByID(layerId);
    if (layer == NULL) {
        return;
    }
    
    // Set up layer rendering
    ((u32*)layer)[0x1998 >> 2] = 0x98;
    void* vf = GSgfxVFGetPredef(7, 0);
    setRenderStateAndSelect__10GSgfxLayerFP7GSgfxVF(layer, vf);
    
    // Check if model changed
    if (layer != modelResult) {
        ((u32*)layer)[0x1740 >> 2] = (u32)modelResult;
        ((u32*)layer)[0x173c >> 2] |= 1;
        ((u32*)layer)[0x17f8 >> 2] = (u32)modelResult;
        ((u32*)layer)[0x17f4 >> 2] |= 1;
    } else if (content->field_7 == 0) {
        // No change needed
    } else {
        ((u32*)layer)[0x1740 >> 2] = (u32)modelResult;
        ((u32*)layer)[0x173c >> 2] |= 1;
        ((u32*)layer)[0x17f8 >> 2] = (u32)modelResult;
        ((u32*)layer)[0x17f4 >> 2] |= 1;
    }
    
    beginSurface__10GSgfxLayerFUs(layer, 4);
    
    // Render vertices with colors
    u8 alpha = spr->field_93;
    u16 param54 = content->field_54;
    u16 param56 = content->field_56;
    
    // Vertex 1
    ((u16*)0xCC018000)[-0x8000 >> 1] = 0;
    ((u8*)0xCC018000)[-0x8000] = 0xFF;
    ((float*)0xCC018000)[-0x8000 >> 2] = ANGLE_MIN;
    ((u16*)0xCC018000)[-0x8000 >> 1] = param54;
    
    // Vertex 2
    ((u16*)0xCC018000)[-0x8000 >> 1] = 0;
    ((u8*)0xCC018000)[-0x8000] = 0xFF;
    ((float*)0xCC018000)[-0x8000 >> 2] = ANGLE_MIN;
    ((u16*)0xCC018000)[-0x8000 >> 1] = param56;
    
    // Vertex 3
    ((u16*)0xCC018000)[-0x8000 >> 1] = param54;
    ((u8*)0xCC018000)[-0x8000] = 0xFF;
    ((float*)0xCC018000)[-0x8000 >> 2] = ONE;
    ((u16*)0xCC018000)[-0x8000 >> 1] = param56;
    
    // Vertex 4
    ((u16*)0xCC018000)[-0x8000 >> 1] = 0;
    ((u8*)0xCC018000)[-0x8000] = 0xFF;
    ((float*)0xCC018000)[-0x8000 >> 2] = ONE;
    ((u16*)0xCC018000)[-0x8000 >> 1] = param54;
    
    endSurface__10GSgfxLayerFv(layer);
}

/*
  Address: 0x80050424 | size: 0x48
  DarkPokemonRelive() - Displays relive information.
*/
void menuPdaDPM::DarkPokemonRelive(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u8 alpha = spr->field_93;
    u32 index = cursor->field_0 + cursor->field_2;
    menuPdaDPMListDispRelive(index, alpha, 0, 0, 1, 0);
}

/*
  Address: 0x8005046C | size: 0x6C
  DarkPokemonRibbon() - Shows/hides ribbon indicator based on Dark Pokemon status.
*/
void menuPdaDPM::DarkPokemonRibbon(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    DarkPokemon* dp = menuPdaDPMListGetDPointer(index);
    u32 status = getStatus__11DarkPokemonCFv(dp);
    
    if (status >= 4) {
        content->field_4 |= 2;
    } else {
        content->field_4 &= ~0x7;  // Clear bits 0-2
    }
}

/*
  Address: 0x800504D8 | size: 0x114
  DarkPokemonInfo() - Displays Dark Pokemon information including trainer and place.
*/
void menuPdaDPM::DarkPokemonInfo(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    DarkPokemon* dp = menuPdaDPMListGetDPointer(index);
    u32 floorId = getCatchFloorId__11DarkPokemonCFv(dp);
    u32 status = getStatus__11DarkPokemonCFv(dp);
    u32 layerId = winSpriteGetLayerID(win, spr);
    u32 pokemonId = getPokemonID__11DarkPokemonCFv(dp);
    
    u32 msgId = 0;
    if (pokemonId == 0xaf) {
        msgId = 0x3c2f;
    } else if (status >= 3) {
        msgId = 0x3b63;
    } else {
        msgId = 0x3b65;
    }
    
    if (floorId == 0xb5) {
        msgId = 0x3c30;
    }
    
    if (msgId != 0) {
        void* trainer = getOrgTrainer__11DarkPokemonCFv(dp);
        u32 placeName = floorGetPlaceName(floorId);
        if (placeName == 0) {
            placeName = 0x3ba8;
        }
        void* placeStr = GSmsgGetGSchar(placeName);
        msgctrlSetValue(0x4d, placeStr);
        
        void* trainerName = getTrainerName__11DarkPokemonCFv(dp);
        msgctrlSetValue(0x57, trainerName);
        
        GSmsgPrint2(layerId, 0, 0, alpha | 0xFF00, 0, msgId, 0);
    }
}

/*
  Address: 0x800505EC | size: 0x9C
  DarkPokemonPlace() - Displays the place where Dark Pokemon was caught.
*/
void menuPdaDPM::DarkPokemonPlace(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    u32 placeMsgId;
    u32 msgId = menuPdaDPMListGetDarkPokemonPlaceMsgID(index, &placeMsgId);
    
    if (msgId != 0) {
        u8 alpha = spr->field_93;
        msgctrlSetValue(0x2f, placeMsgId + 1);
        void* msgStr = GSmsgGetGSchar(msgId);
        msgctrlSetValue(0x37, msgStr);
        
        u32 layerId = spr->field_1c;
        GSmsgPrint2(layerId, 0, 0, alpha | 0xFF00, 0, 0x4275, 0);
    }
}

/*
  Address: 0x80050688 | size: 0x78
  PokemonName() - Displays the Pokemon name.
*/
void menuPdaDPM::PokemonName(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    void* name = menuPdaDPMListGetPokemonName(index);
    
    if (name == 0) {
        name = GSmsgGetGSchar(1);
    }
    msgctrlSetValue(0x37, name);
    
    u8 alpha = spr->field_93;
    u32 layerId = spr->field_1c;
    GSmsgPrint2(layerId, 0, 0, alpha | 0xFF00, 0, 0x4275, 0);
}

/*
  Address: 0x80050700 | size: 0x164
  PokemonSex() - Displays the Pokemon sex indicator.
*/
void menuPdaDPM::PokemonSex(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    DarkPokemon* dp = menuPdaDPMListGetDPointer(index);
    void* pokemon = this->GetPokemonPointer(index);
    
    u32 rnd = getRnd__11DarkPokemonCFv(dp);
    pokemonBiosSetRnd(pokemon, rnd);
    u32 sex = pokemonGetSex(pokemon);
    pokemonBiosSetRnd(pokemon, rnd);  // Restore RNG
    
    void* sexStr;
    if (sex == 0x80) {
        sexStr = GSmsgGetGSchar(1);  // Genderless
    } else if (sex == 1) {
        sexStr = GSmsgGetGSchar(0x9c6);  // Female
    } else if (sex == 0) {
        sexStr = GSmsgGetGSchar(0x9c5);  // Male
    } else if (sex >= 1 && sex <= 3) {
        sexStr = GSmsgGetGSchar(1);
    } else {
        sexStr = GSmsgGetGSchar(0x9c6);
    }
    
    u32 floorId = getCatchFloorId__11DarkPokemonCFv(dp);
    if (floorId == 0xb5 && sex == 2) {
        sexStr = GSmsgGetGSchar(0x9c7);
    }
    
    msgctrlSetValue(0x37, sexStr);
    u8 alpha = spr->field_93;
    u32 layerId = spr->field_1c;
    GSmsgPrint2(layerId, 0, 0, alpha | 0xFF00, 0, 0x4275, 0);
}

/*
  Address: 0x80050864 | size: 0x8C
  PokemonBall() - Displays the ball used to catch the Dark Pokemon.
*/
void menuPdaDPM::PokemonBall(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, DPM_CONTENTS* content) {
    CURSOR* cursor = (CURSOR*)content->field_0;
    u32 index = cursor->field_0 + cursor->field_2;
    DarkPokemon* dp = menuPdaDPMListGetDPointer(index);
    
    if (isSnach__11DarkPokemonCFv(dp)) {
        u32 ballId = getCatchBallID__11DarkPokemonCFv(dp);
        u32 spriteId = mballBiosGetSpriteID(ballId);
        if (spriteId != 0) {
            u32 layerId = spr->field_1c;
            windowDrawSprite(0, 0, 0, spr, spriteId, 0, 0);
        }
    }
}

/*
  Address: 0x800508F0 | size: 0x3C
  _menuClose() - Closes the menu and synchronizes.
*/
void menuPdaDPM::_menuClose(long menuId) {
    menuClose(menuId);
    menuCloseSync(menuId, 1);
}

/*
  Address: 0x8005092C | size: 0xF0
  GetPokemonPointer() - Gets or creates a Pokemon pointer for display.
  Handles both relived and captured Dark Pokemon.
*/
void* menuPdaDPM::GetPokemonPointer(long index) {
    u32 pokemonId = menuPdaDPMListGetPokemonID(index);
    void* status = gamedataGetStatus(0, 1);
    void* pokemon = ((void**)(this + 1))[0];  // Offset 0x4 from this
    pokemonCreate(&pokemon, pokemonId, 0xa);
    
    DarkPokemon* dp = menuPdaDPMListGetDPointer(index);
    u32 darkId = menuPdaDPMListGetDarkpokemonID(index);
    u32 darkPoint = getDarkPointDirect__11DarkPokemonCFv(dp);
    
    void* result = pokemonCreateRndFit(&pokemon, -1, -1, 0, 0, darkPoint);
    ((void**)this)[0] = result;
    pokemonBiosSetRnd(&pokemon, result);
    
    if (!isRelive__11DarkPokemonCFv(dp)) {
        pokemonBiosSetDarkpokemonDataId(&pokemon, darkId);
    } else {
        pokemonBiosSetDarkpokemonDataId(&pokemon, 0);
    }
    
    return ((void**)this)[0];
}

/* Data: gap_07_8032EC7C_data (global) */
u32 gap_07_8032EC7C_data = 0;

/* Data: _pDPM (global) */
menuPdaDPM* _pDPM;

/* Data: _cursor (local) */
CURSOR _cursor;
