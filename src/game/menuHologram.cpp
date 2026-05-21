// menuHologram.cpp - Hologram Suite menu
// Address: 0x80087B14..0x8008A160 | size: 0x264C

#include "global.h"

/* Forward declarations */
struct CMetaMenu; struct CMenuGlobalState; struct Pokemon; struct GSpart;
struct GSvec { float x, y, z; };
typedef u32 GSpartMixType;
typedef s32 GSgfxLayerID;
extern struct relivehall_data *relivehall_data;
extern const u32 relivehallAisyou2ColorTbl[];
extern const u32 GSgfxColAu8_Black;
extern const u8 mtxIdent[0x30];
extern const u32 pcReliveHallSoundTbl[5];
extern void *__vt__9CMetaMenu;
static u8 init$2173, init$2318, init$2321, init$2324;
static float neckRotVec$2172[9];
static const u32 msgTbl$2067[2] = { 0xD1F9, 0xD1FA };
static const u32 msgTbl$2047[3] = { 0xD1F5, 0xD1F6, 0xD1F7 };

class CMenuHologram {
public:
    u32 field_0x278; u32 field_0x27C;
    u8 field_0x280[0x100];
    u32 m_stage; u32 m_cursor; u32 m_stagePtr; u8 m_animating;
    u32 m_lights[8]; u32 m_lightCount; u32 m_texture; u32 m_fileHandle;
    u8 m_seqLoaded; u8 m_offscreenFlag;
    u32 m_modelPlate; u32 m_seqNeck; u32 m_wazaSeq; u32 m_seqVisitor;
    u32 m_scriptModelVis; u32 m_modelVisitor; u32 m_seqVisitor2;
    u32 m_scriptModelDan; u32 m_modelDancer;
    u32 m_pkmnData[7][5]; u32 m_ceremonyPkmn;
    u32 m_infoWindow; u32 m_globalState;
    static GSgfxLayerID model_z_layer;
    void drawAll(); void stateReliveCeremony(); void stateMainProc();
    void setStage(int); void setStageToReliveReady(); void moveStageWait(int);
    void reloadDatas(bool); void unloadDatas();
    u32 pokemonToAisyouColor(Pokemon*, Pokemon*);
    void bgmStop(); void bgmKick();
    void stageAllModelLoad(); void stageAllModelUnLoad();
    void modelPokemonSetScale(long); void modelVisitorSetYPosition(long);
    long modelPokemonLoad(long); int actionYesNo(u32, bool);
    void loop(); void init(CMenuGlobalState&); void main(CMenuGlobalState&);
    void releaseOffscreenData(); void renderOffscreenData(); void initializeOffscreenData();
};
static CMenuHologram* pMenuHologram;
static const u32 localWindowTable[] = { 0x71, 0x72, 0x88, 0xD0, 0x87, 0 };
static const u32 plateIndexTbl[101] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,114 };
static const u32 colorLineIndexTbl[102] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,112 };
GSgfxLayerID CMenuHologram::model_z_layer = -1;

// External declarations (abbreviated)
void* GSmemAllocClr(int); void GSmemFree(void*);
void GSfsysReadWait(u32); void GSfsysFree(u32); void GSresFreeGroup(u32);
u32 GSresGetResourceAllGroup(u32); u32 scriptModelOpen(u32, u32*); void scriptModelClose(u32);
void GSmodelFree(u32); void GSmodelSetPosition(u32, float*); void GSmodelSetRotation(u32, float*);
void GSmodelSetScale(u32, float*); void GSmodelSetAnimIndex(u32, u32); void GSmodelSetAnimType(u32, u32);
void GSmodelStartAnimation(u32); u32 GSmodelHasAnimationEnded(u32);
void GSmodelGetAnimIndex(u32, u32*, u32); void GSmodelSetVisibility(u32, u32);
void GSmodelSetRenderLayer(u32, u32, u32); void GSmodelSetAnimRate(u32, float);
GSpart* GSmodelGetPart(u32, u32); void GSpartFree(GSpart*);
void GSmodelAttachToGSpart(u32, GSpart*, u32, u32, u32);
void GSmodelDisableModulation(u32);
void GSmodelSetForceUseFractionalFramesFlag(u32, u32);
void GSmodelSetSkipFractionalFramesFlag(u32, u32);
void GSpartRegisterAnimMix(GSpart*, u32, u32, void*, u32);
void GSmaterialSetModulate(void*, u32); void GSmaterialEnableExtension(void*, u32);
void GSlightFree(u32); u32 GSlightLoad(u32); void GSlightSetActive(u32, u32);
u32 GSlightCanAnimate(u32); void GSlightSetAnimIndex(u32, u32);
void GSlightSetAnimRate(u32, float); void GSlightStartAnimation(u32);
u32 GStextureCreate(u32, u32, u32, u32, u32); void GStextureFree(u32);
void* GSgfxLayerFindByID(u32);
void SetClearFlags__10GSgfxLayerFbbb(void*, u32, u32, u32);
void SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(void*, u32, u32, void*);
void Remove__16GSgfxLayerConfigF12GSgfxLayerID(u32);
void Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(u32, u32, u32);
void* Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset(const char*, u32, u32, u32, u32, u32, u32, u32, void*, u32);
void beginSurface__10GSgfxLayerFUs(void*, u16); void endSurface__10GSgfxLayerFv(void*);
void tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc13GSgfxTgenSrcP5GSmtxbP5GSmtx(void*, u8, u8, u8, void*, void*);
void cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(void*, u8, u8, u8, u8, u32, void*, u8, u8);
void GSgfxVFBuildTemp(u32, u32, u32, u32, u32, u32, u32);
void spriteSetOffset(u32, u32, u32); void spriteClearScissor(u32); void spriteSetEnv(u32);
void GSmtx44Ortho(float, float, float, float, float, float, float*);
void GSthreadSwitch(); u32 windowGetKeyTrg(); u32 windowGetKeyOn();
void GSflagSet(u32, u32); void menuPtPlayBgm__FUl(u32); void menuPtPlaySe__FUl(u32);
u32 floorGetCurrentGroupID(); void cameraPlayAnime(u32, u32, float, u32); void cameraSetType(u32);
void* getPointer__11CReliveHallFv(); u32 getStage__11CReliveHallFl(u32);
u32 isReliveReady__12CReliveStageFv(); u32 isReliveReadyPokemonExist__11CReliveHallFv();
u32 relivehallGetLastViewStage__Fv(); void relivehallSetLastViewStage__Fl(u32);
void* getVisitorPointer__12CReliveStageFv(); u32 getDancerQuantity__12CReliveStageFv();
Pokemon* getDancerPointer__12CReliveStageFl(u32);
u32 getState__12CReliveStageFv(); u32 getTempo__12CReliveStageFv();
u32 reliveCeremonyFromHologram__FP7PokemonUl(Pokemon*, u32);
void pickupVisitor__12CReliveStageFR7Pokemon(void*, Pokemon*);
void* getPointer__5PCBOXFv(); u32 isPokemonFull__5PCBOXFv();
void addPokemonLastWatchBox__5PCBOXFP7Pokemon(void*, Pokemon*);
const char* getNicknamePtr__7PokemonFv(Pokemon*); void GScharCpy(char*, const char*);
u32 reliveHallPokemonToAisyou__FP7PokemonP7Pokemon(Pokemon*, Pokemon*);
void relivehallDraw9StageNumber__Fi(int); void relivehallDraw9StageInfo__Fi(int);
void relivehallDrawStageInfoCursor__FliiP7Pokemonb(long, int, int, Pokemon*, u8);
u32 floorOpenObject(u32, u32, u32*, u32*); u32 floorReadMakeLightResID(u32, u32*);
void* peopleInfoBiosGetPtr(u32); s8 peopleInfoBiosGetNeckIndex(u32);
void* Sequence_CreateNull(); void* Sequence_LoadWaza(void*, u32, u32, u32);
void Sequence_SetPosition(void*, float*); void Sequence_SetRotation(void*, float*);
void Sequence_SetScale(void*, float*); void Sequence_SetVisibility(void*, u32);
void Sequence_Free(void*); void WazaSequence_Start(void*, u32); void WazaSequence_Free(void*);
u32 Sequence_GetGSmodel(void*); void Sequence_DoAnimation(void*, u32);
void* HSD_ArchiveGetPublicAddress(u32, const char*);
u32 getPokemonDataId__7PokemonCFv(const Pokemon*);
u32 isDarkPokemon__7PokemonCFv(const Pokemon*);
u32 pokemonIsJoutaiDataId(Pokemon*, u32);
void pokemonGetStatus(Pokemon*, u32, u32, u32, u32*);
void* Sequence_LoadPokemon(u16, u32, u32, u32);
// Sequence_LoadWaza declared above
void menuModelGetPkxRndFromPokemonForSeqenceLoad__FRUlRUsP7Pokemon(u32*, u16*, Pokemon*);
u32 menuModelGetPokemonAnimationIndexByPointer(Pokemon*);
void init__6CStateFv(void*); void update__6CStateFv(void*);
void init__11CInfoWindowFlUl(void*, float, u32);
void exec__11CInfoWindowFR9CMetaMenuUlb(void*, void*, u32, u32);
void draw__11CInfoWindowFv(void*); void setMsgCtrlValue__11CInfoWindowFUlUl(void*, u32, u32);
void open__11CInfoWindowFUlb(void*, u32, u32); void close__11CInfoWindowFv(void*);
void localWindowSetTable__9CMetaMenuFPl(void*, const u32*);
void localWindowCreateAll__9CMetaMenuFv(); void localWindowDeleteAll__9CMetaMenuFv();
void localWindowDrawAll__9CMetaMenuFv();
void systemFadeInKick__9CMetaMenuFv();
void systemFadeOutSetAndWait__9CMetaMenuFf(float);
void systemFadeOutKeepAfterFloorPush__9CMetaMenuFv();
void systemFadeWaitToEnd__9CMetaMenuFv();
u32* getKeyInfo__9CMetaMenuFv(); void aButtonWait__9CMetaMenuFv();
void waitAtTime__9CMetaMenuFv(float);
int actionMenu__9CMetaMenuFPUlill(u32*, u32, u32, u32, u32);
float calcAnimationTimeRate0to1__9CMetaMenuFf(float);
u32 soundGetBGMID(); void soundStop(u32, u32);
void menuDrawReliveUpdate(); u32 menuGetPokemonScale__FUli(u32, float);
static void _getNeckRotationCB(GSpart*, GSpartMixType, void*, GSvec*);
static void* _makeArchiveHeader(u32);

/* 0x80087B14 */ void menuHologramReloadDatas() { if(pMenuHologram) pMenuHologram->reloadDatas(false); }
/* 0x80087B3C */ void menuHologramUnloadDatas() { if(pMenuHologram) pMenuHologram->unloadDatas(); }

/* 0x80087B60 */
void menuHologramExecFromPcBox__FR16CMenuGlobalState(CMenuGlobalState& state) {
    pMenuHologram = (CMenuHologram*)GSmemAllocClr(0x418);
    if (pMenuHologram) {
        *(void**)((u8*)pMenuHologram+0x330) = &__vt__9CMetaMenu;
        *(void**)((u8*)pMenuHologram+0x334) = (void*)0x803C7D9C;
        pMenuHologram->main(state);
    }
    if (pMenuHologram) { GSmemFree(pMenuHologram); pMenuHologram = 0; }
}

/* 0x80087C38 */
void CMenuHologram::drawAll() {
    if (m_modelPlate) {
        if (!init$2318) { neckRotVec$2172[0]=1; neckRotVec$2172[1]=1; neckRotVec$2172[2]=1; init$2318=1; }
        if (!init$2321) { neckRotVec$2172[3]=0.5f; neckRotVec$2172[4]=1; neckRotVec$2172[5]=0.5f; init$2321=1; }
        if (!init$2324) { neckRotVec$2172[6]=1; neckRotVec$2172[7]=1; neckRotVec$2172[8]=1; init$2324=1; }
        GSmodelSetPosition(m_modelPlate, neckRotVec$2172);
        GSmodelSetRotation(m_modelPlate, &neckRotVec$2172[3]);
        GSmodelSetScale(m_modelPlate, &neckRotVec$2172[6]);
    }
    renderOffscreenData();
    if (m_offscreenFlag) return;
    if (m_modelVisitor) {
        u32 idx=0; GSmodelGetAnimIndex(m_modelVisitor, &idx, 0);
        if ((idx==1||idx==3) && GSmodelHasAnimationEnded(m_modelVisitor)) {
            GSmodelSetAnimIndex(m_modelVisitor, idx+1); GSmodelSetAnimType(m_modelVisitor, 1); GSmodelStartAnimation(m_modelVisitor);
        }
    }
    if (m_modelDancer) {
        u32 idx=0; GSmodelGetAnimIndex(m_modelDancer, &idx, 0);
        if ((idx==1||idx==3) && GSmodelHasAnimationEnded(m_modelDancer)) {
            GSmodelSetAnimIndex(m_modelDancer, idx+1); GSmodelSetAnimType(m_modelDancer, 1); GSmodelStartAnimation(m_modelDancer);
        }
    }
    if (m_animating) {
        float r = calcAnimationTimeRate0to1__9CMetaMenuFf(2.0f);
        float rot[3] = {0, r*360.0f, 0}; GSmodelSetRotation(m_modelDancer, rot);
    }
    u32 stage = getStage__11CReliveHallFl(m_cursor);
    u32 tempo = getTempo__12CReliveStageFv();
    relivehallDraw9StageNumber__Fi((int)stage); relivehallDraw9StageInfo__Fi((int)stage);
    u8 show = (field_0x278==4||field_0x278==7)?0:1;
    Pokemon* vis = (Pokemon*)getVisitorPointer__12CReliveStageFv();
    relivehallDrawStageInfoCursor__FliiP7Pokemonb((long)stage,(int)tempo,(int)(u32)vis,vis,show);
    draw__11CInfoWindowFv((void*)m_infoWindow);
    localWindowDrawAll__9CMetaMenuFv(); menuDrawReliveUpdate();
}

/* 0x80087EEC */
void CMenuHologram::stateReliveCeremony() {
    GSflagSet(0x5A3, 1); m_animating = 0;
    while(1) { u32 i=0; if(m_modelDancer) GSmodelGetAnimIndex(m_modelDancer,&i,0); if(i==2) break; ((void(*)(void*))((u32*)*(u32**)((u8*)this+0x330))[4])(this); }
    aButtonWait__9CMetaMenuFv(); menuPtPlayBgm__FUl(0x5A8); menuPtPlaySe__FUl(0x5A7);
    cameraPlayAnime(floorGetCurrentGroupID()|0x1800, 0, 1.0f, 0); cameraSetType(4);
    if(m_modelVisitor){GSmodelSetAnimIndex(m_modelVisitor,3);GSmodelSetAnimType(m_modelVisitor,0);GSmodelStartAnimation(m_modelVisitor);}
    waitAtTime__9CMetaMenuFv(0.5f); GSmodelSetVisibility(m_modelPlate, 0); waitAtTime__9CMetaMenuFv(1.0f);
    Pokemon* vis = (Pokemon*)getVisitorPointer__12CReliveStageFv();
    m_offscreenFlag=1; m_ceremonyPkmn=(u32)reliveCeremonyFromHologram__FP7PokemonUl(vis,m_stage); m_offscreenFlag=0;
    systemFadeInKick__9CMetaMenuFv(); systemFadeWaitToEnd__9CMetaMenuFv();
    GScharCpy((char*)((u8*)this+0x290), getNicknamePtr__7PokemonFv((Pokemon*)m_ceremonyPkmn));
    while(1){GSthreadSwitch();u32 t=windowGetKeyTrg();u32 o=windowGetKeyOn();if((o|t)&0xFFFF0000)break;}
    setMsgCtrlValue__11CInfoWindowFUlUl((void*)m_infoWindow, 0x32, 0);
    exec__11CInfoWindowFR9CMetaMenuUlb((void*)m_infoWindow, this, 0x1000-0x2EA2, 1);
    pickupVisitor__12CReliveStageFR7Pokemon((void*)m_stagePtr, (Pokemon*)m_ceremonyPkmn);
    addPokemonLastWatchBox__5PCBOXFP7Pokemon(getPointer__5PCBOXFv(), (Pokemon*)m_ceremonyPkmn);
    if(isReliveReadyPokemonExist__11CReliveHallFv()){
        systemFadeInKick__9CMetaMenuFv();
        if(isPokemonFull__5PCBOXFv()){field_0x27C=7;memset((void*)((u8*)this+0x290),0,0x40);}
        else{
            if(actionYesNo(0x1000-0x2ECF,false)==0){systemFadeOutSetAndWait__9CMetaMenuFf(0.5f);setStageToReliveReady();reloadDatas(true);systemFadeInKick__9CMetaMenuFv();field_0x27C=4;}
            else{field_0x27C=7;}
            memset((void*)((u8*)this+0x290),0,0x40);
        }
    } else { field_0x27C=7; memset((void*)((u8*)this+0x290),0,0x40); }
}

/* 0x80088198 */
void CMenuHologram::stateMainProc() {
    while(1){
        u32* ki=(u32*)getKeyInfo__9CMetaMenuFv(); u16 t=ki[1]; u16 h=ki[2];
        if(t|h){
            if(h==0x200||h==0x400){s32 v=m_cursor;v=h==0x200?v-(8-v)/9:(v+1)/9;m_cursor=(u32)v;menuPtPlaySe__FUl(0x45F);}
            if(t==0x10){menuPtPlaySe__FUl(0x45A);field_0x27C=3;memset((void*)((u8*)this+0x290),0,0x40);}
            if(t==0x20){menuPtPlaySe__FUl(0x45B);field_0x27C=6;memset((void*)((u8*)this+0x290),0,0x40);}
        }
        ((void(*)(void*))((u32*)*(u32**)((u8*)this+0x330))[4])(this);
        if(field_0x27C!=-1) break;
    }
}

/* 0x80088310 */ void CMenuHologram::setStage(int s){ m_stage=s; m_cursor=s; m_stagePtr=getStage__11CReliveHallFl(s); }
/* 0x80088350 */
void CMenuHologram::setStageToReliveReady(){
    int i=0; while(i<9){if(isReliveReady__12CReliveStageFv())break;i++;}
    setStage(i>=9?(int)relivehallGetLastViewStage__Fv():i);
}
/* 0x800883D4 */
void CMenuHologram::moveStageWait(int s){ systemFadeOutSetAndWait__9CMetaMenuFf(0.5f); unloadDatas(); setStage(s); reloadDatas(true); systemFadeInKick__9CMetaMenuFv(); }
/* 0x80088434 */
void CMenuHologram::reloadDatas(bool f){
    stageAllModelLoad();
    if(m_modelVisitor){GSmodelSetAnimIndex(m_modelVisitor,2);GSmodelSetAnimType(m_modelVisitor,1);GSmodelStartAnimation(m_modelVisitor);}
    if(m_modelDancer){GSmodelSetAnimIndex(m_modelDancer,2);GSmodelSetAnimType(m_modelDancer,1);GSmodelStartAnimation(m_modelDancer);}
    localWindowCreateAll__9CMetaMenuFv(); if(f) bgmKick();
}
/* 0x800884D8 */ void CMenuHologram::unloadDatas(){ localWindowDeleteAll__9CMetaMenuFv(); stageAllModelUnLoad(); }
/* 0x8008850C */
u32 CMenuHologram::pokemonToAisyouColor(Pokemon* p, Pokemon* t){
    u32 a=reliveHallPokemonToAisyou__FP7PokemonP7Pokemon(p,t);
    return a==-1?GSgfxColAu8_Black:relivehallAisyou2ColorTbl[a];
}
/* 0x80088560 */ void CMenuHologram::bgmStop(){ soundStop(soundGetBGMID(), 0x32); }
/* 0x80088588 */
void CMenuHologram::bgmKick(){
    u32 t=getTempo__12CReliveStageFv(); u32 b=t<=0?0x5BB:t<=0x35?0x510:t<=0x5F?0x50F:0x50E;
    if(soundGetBGMID()!=b) menuPtPlayBgm__FUl(b);
}

/* 0x80088608 */
void CMenuHologram::stageAllModelLoad(){
    stageAllModelUnLoad(); initializeOffscreenData();
    u32 state=getState__12CReliveStageFv(); u32 dc=getDancerQuantity__12CReliveStageFv();
    u32 fh,sr,mr;
    if(state==0){fh=0x8E4;sr=0x18D9000;mr=0x18D9400;}
    else if(state==1){fh=0x8E5;sr=0x18DC000;mr=0x18DC400;}
    else if(state==2){fh=0x8E6;sr=0x18DF000;mr=0x18DF400;}
    else if(state==3){fh=0x8E7;sr=0x18E4000;mr=0x18E4400;}
    else{sr=0x18E0000;mr=0x18E0400;}
    m_fileHandle=fh; GSfsysReadWait(fh);
    memset((void*)((u8*)this+0x388),0,0xC); {u32 tmp; m_scriptModelVis=scriptModelOpen(sr,&tmp); m_modelVisitor=GSresGetResourceAllGroup(m_scriptModelVis); GSmodelSetRenderLayer(m_modelVisitor,1,tmp); if(m_modelVisitor){GSmodelSetAnimIndex(m_modelVisitor,1);GSmodelSetAnimType(m_modelVisitor,0);GSmodelStartAnimation(m_modelVisitor);}}
    memset((void*)((u8*)this+0x394),0,0xC); {u32 tmp; m_scriptModelDan=scriptModelOpen(sr+1,&tmp); m_modelDancer=GSresGetResourceAllGroup(m_scriptModelDan); GSmodelSetRenderLayer(m_modelDancer,1,tmp); if(m_modelDancer){GSmodelSetAnimIndex(m_modelDancer,1);GSmodelSetAnimType(m_modelDancer,0);GSmodelStartAnimation(m_modelDancer);}}
    Pokemon* vis=(Pokemon*)getVisitorPointer__12CReliveStageFv();
    if(vis){modelPokemonLoad(2); GSpart* p=GSmodelGetPart(m_modelDancer,plateIndexTbl[state*0x64+m_cursor]); GSmodelAttachToGSpart(m_pkmnData[2][1],p,7,0,1); GSpartFree(p); modelVisitorSetYPosition(2); modelPokemonSetScale(2);}
    for(int i=0;i<(int)dc;i++){modelPokemonLoad(i+3); u32 di=(i-m_cursor%dc+dc)%dc+1; GSpart* p=GSmodelGetPart(m_modelDancer,colorLineIndexTbl[state*0x64+di]); GSmodelAttachToGSpart(m_pkmnData[i+3][1],p,7,0,1); GSpartFree(p); modelPokemonSetScale(i+3);}
    u32 mat=m_modelDancer?*(u32*)((u8*)m_modelDancer+0x5E0):0; GSmodelDisableModulation(mat);
    if(dc){u32 vc=vis?pokemonToAisyouColor(vis,getDancerPointer__12CReliveStageFl(*(u8*)((u8*)m_stagePtr+0x3D4))):GSgfxColAu8_Black; u32 ci=colorLineIndexTbl[state*0x64+m_cursor]; u32 mi=(*(u8*)((u8*)relivehall_data+ci+6)-1)*0x34; GSmaterialSetModulate((void*)(mat+mi),vc); GSmaterialEnableExtension((void*)(mat+mi),1);}
    for(int i=0;i<(int)dc;i++){u32 dc2=pokemonToAisyouColor(getDancerPointer__12CReliveStageFl(i+1),getDancerPointer__12CReliveStageFl(i)); u32 ci=colorLineIndexTbl[state*0x64+(i-m_cursor%dc+dc)%dc+1]; u32 mi=(*(u8*)((u8*)relivehall_data+ci+6)-1)*0x34; GSmaterialSetModulate((void*)(mat+mi),dc2); GSmaterialEnableExtension((void*)(mat+mi),1);}
    cameraPlayAnime(fh,mr,1.0f,1); cameraSetType(4);
    u32* arch=(u32*)_makeArchiveHeader(mr); if(arch&&arch[2]){u32 lr=floorReadMakeLightResID(mr,arch); m_lightCount=0; for(int i=0;i<4;i++){if(!((u32*)arch[2])[i])break; u32 l=GSlightLoad(((u32*)arch[2])[i]); m_lights[m_lightCount++]=l; GSlightSetActive(l,1); if(GSlightCanAnimate(l)){GSlightSetAnimIndex(l,0);GSlightSetAnimRate(l,1.0f);GSlightStartAnimation(l);}}}
    u32 pt; m_modelPlate=floorOpenObject(0x16C9400,0,&pt,(u32*)((u8*)this+0x34));
    GSmodelSetAnimIndex(m_modelPlate,3); GSmodelSetAnimRate(m_modelPlate,1.0f); GSmodelStartAnimation(m_modelPlate);
    GSmodelSetVisibility(m_modelPlate,1); GSmodelSetAnimType(m_modelPlate,1); GSmodelSetRenderLayer(m_modelPlate,2,pt);
    peopleInfoBiosGetPtr(0x16C9400); s8 ni=peopleInfoBiosGetNeckIndex(0x16C9400);
    GSpart* np=GSmodelGetPart(m_modelPlate,ni); GSpartRegisterAnimMix(np,2,0x202,(void*)_getNeckRotationCB,0); GSpartFree(np);
    if(fh){m_seqNeck=(u32)Sequence_CreateNull(); Sequence_LoadWaza((void*)m_seqNeck,fh,4,0); m_wazaSeq=m_seqNeck; float z[6]={0}; Sequence_SetPosition((void*)m_seqNeck,z); Sequence_SetRotation((void*)m_seqNeck,z+3); WazaSequence_Start((void*)m_wazaSeq,0);}
    m_seqLoaded=1;
}

/* 0x80088F30 */
static void _getNeckRotationCB(GSpart* p, GSpartMixType t, void* d, GSvec* o){
    if(!init$2173){neckRotVec$2172[0]=1.5f;neckRotVec$2172[1]=0;neckRotVec$2172[2]=0;init$2173=1;}
    o->x=neckRotVec$2172[0]; o->y=neckRotVec$2172[1]; o->z=neckRotVec$2172[2];
}

/* 0x80088F8C */
void CMenuHologram::releaseOffscreenData(){
    void* l=GSgfxLayerFindByID(2);
    SetClearFlags__10GSgfxLayerFbbb(l, 0, 0, 0);
    SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(l, 0, 0, 0);
    if(model_z_layer!=-1){Remove__16GSgfxLayerConfigF12GSgfxLayerID(model_z_layer);model_z_layer=-1;}
    Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(2,4,1);
    if(m_texture){GStextureFree(m_texture);m_texture=0;}
}

/* 0x8008902C */
void CMenuHologram::renderOffscreenData(){
    if(!m_texture) return;
    void* l=GSgfxLayerFindByID(6);
    if(!l) return;
    GSgfxVFBuildTemp(6,0,0,0,1,5,1);
    spriteSetOffset(6,0,0); spriteClearScissor(6); spriteSetEnv(6);
    float proj[16]; GSmtx44Ortho(0.0f,640.0f,480.0f,0.0f,-1.0f,1.0f,proj);
    *(u32*)((u8*)l+0xD54)=1; memcpy((u8*)l+0xD58,mtxIdent,0x30);
    tgenFunc__10GSgfxLayerFUc13GSgfxTgenFunc13GSgfxTgenSrcP5GSmtxbP5GSmtx(l,0,5,6,0,0);
    cunitChannelGen__10GSgfxLayerFUc15GSgfxCunitAlpha13GSgfxCunitSrc13GSgfxCunitSrcUlPP10GSgfxLight14GSgfxLightType16GSgfxDiffuseFunc(l,0,3,5,4,0,0,0,0);
    beginSurface__10GSgfxLayerFUs(l,4);
    endSurface__10GSgfxLayerFv(l);
}

/* 0x80089670 */
void CMenuHologram::initializeOffscreenData(){
    m_texture=GStextureCreate(0,0,0x45,0,0);
    if(m_texture){
        Move__16GSgfxLayerConfigF12GSgfxLayerID12GSgfxLayerID16GSgfxLayerOffset(2,0,1);
        if(model_z_layer==-1){
            model_z_layer=(GSgfxLayerID)(u32)Add__16GSgfxLayerConfigFPcUlUlUl14GSgfxLayerTypebbb12GSgfxLayerID16GSgfxLayerOffset("model z layer",2,1,0x2000,8,0,0,0,&model_z_layer,0);
            if(GSgfxLayerFindByID(model_z_layer)) SetClearFlags__10GSgfxLayerFbbb(GSgfxLayerFindByID(model_z_layer),1,1,0);
        }
        void* l=GSgfxLayerFindByID(2);
        SetTextureCopy__10GSgfxLayerFP9GStexturebPUc(l,m_texture,0,0);
        SetClearFlags__10GSgfxLayerFbbb(l,1,1,1);
    }
}

/* 0x80089768 */
static void* _makeArchiveHeader(u32 r){
    u32 a=GSresGetResourceAllGroup(r);
    return HSD_ArchiveGetPublicAddress(a,"scene_data");
}

/* 0x80089794 */
void CMenuHologram::stageAllModelUnLoad(){
    if(m_seqLoaded){
        if(m_seqVisitor){Sequence_SetVisibility((void*)m_seqVisitor,0);Sequence_Free((void*)m_seqVisitor);m_seqVisitor=0;}
        if(m_wazaSeq){WazaSequence_Free((void*)m_wazaSeq);Sequence_Free((void*)m_seqNeck);}
        m_wazaSeq=0; m_seqNeck=0;
    }
    releaseOffscreenData();
    for(int i=0;i<7;i++){
        u32* e=&m_pkmnData[i][0];
        if(e[1]){Sequence_SetVisibility((void*)e[1],0);Sequence_Free((void*)e[1]);}
        else if(e[0]) GSmodelSetVisibility(e[0],0);
        scriptModelClose(e[0]);
    }
    memset((void*)m_pkmnData,0,0x54);
    for(int i=0;i<(int)m_lightCount;i++) GSlightFree(m_lights[i]);
    memset((void*)m_lights,0,0x20); m_lightCount=0;
    if(m_fileHandle){GSfsysFree(m_fileHandle);GSresFreeGroup(m_fileHandle);m_fileHandle=0;}
    cameraSetType(3);
    if(m_modelPlate){GSmodelFree(m_modelPlate);m_modelPlate=0;}
    m_seqLoaded=0;
}

/* 0x80089918 */
void CMenuHologram::modelPokemonSetScale(long idx){
    u32* e=&m_pkmnData[idx][0];
    Pokemon* p=idx==2?(Pokemon*)getVisitorPointer__12CReliveStageFv():getDancerPointer__12CReliveStageFl(idx-3);
    if(!p) return;
    u32 id=getPokemonDataId__7PokemonCFv(p);
    float s=menuGetPokemonScale__FUli(id,1.0f);
    u16 h=*(u16*)((u8*)relivehall_data+4);
    double r=s*(27315.0-(double)h)/100.0;
    float sv[3]={(float)r,(float)r,(float)r};
    Sequence_SetScale((void*)e[2],sv);
}

/* 0x800899D4 */
void CMenuHologram::modelVisitorSetYPosition(long idx){
    u32* e=&m_pkmnData[idx][0];
    Pokemon* p=(Pokemon*)getVisitorPointer__12CReliveStageFv();
    u32 id=getPokemonDataId__7PokemonCFv(p);
    float y=0.0f;
    if(id==0x16)y=0.3f;else if(id==0x0F)y=0.4f;else if(id==0x0C)y=0.5f;
    else if(id>=0x10&&id<=0x14)y=0.4f;else if(id>=0x17&&id<=0x15)y=0.3f;
    else if(id==0x31)y=0.5f;else if(id==0x46)y=0.6f;else if(id>=0x32&&id<=0x45)y=0.5f;
    else if(id>=0x47&&id<=0x48)y=0.4f;else if(id==0x52)y=0.3f;else if(id>=0x53&&id<=0xA4)y=0.4f;
    else if(id==0xA5)y=0.6f;else if(id>=0x84&&id<=0x82)y=0.5f;else if(id>=0x83&&id<=0xA6)y=0.4f;
    else if(id>=0xA8&&id<=0x149)y=0.5f;else if(id==0x14A||id==0x14B)y=0.6f;
    else if(id>=0x14C&&id<=0x168)y=0.5f;else if(id==0x15D||id==0x169)y=0.4f;
    else if(id>=0x16A&&id<=0x16B)y=0.5f;else if(id==0x83)y=0.5f;
    float pos[3]={0.0f,y,0.0f};
    Sequence_SetPosition((void*)e[2],pos);
}

/* 0x80089B64 */
long CMenuHologram::modelPokemonLoad(long idx){
    u32* e=&m_pkmnData[idx][0]; memset(e,0,0xC);
    Pokemon* p=idx==2?(Pokemon*)getVisitorPointer__12CReliveStageFv():getDancerPointer__12CReliveStageFl(idx-3);
    if(!p) return 0;
    u16 id=(u16)getPokemonDataId__7PokemonCFv(p);
    u32 w=0;
    if(isDarkPokemon__7PokemonCFv(p)){
        if(!isReliveReady__12CReliveStageFv()){
            w=0x3E; if(pokemonIsJoutaiDataId(p,0x3E)==1) w=0x87; else w=0x25;
        }
    }
    u32 rnd; u16 gender;
    menuModelGetPkxRndFromPokemonForSeqenceLoad__FRUlRUsP7Pokemon(&rnd,&gender,p);
    u32 status; pokemonGetStatus(p,0,0xC1,0,&status);
    s32 abs=status<0?-status:status; u32 sign=status>>31;
    void* seq=Sequence_LoadPokemon(id,gender,rnd,abs|sign);
    e[2]=(u32)seq; e[1]=Sequence_GetGSmodel(seq); Sequence_SetVisibility(seq,1);
    if(w){void* ws=Sequence_LoadWaza(seq,w,4,0); if(ws) WazaSequence_Start(ws,0);}
    u32 ai=menuModelGetPokemonAnimationIndexByPointer(p);
    Sequence_DoAnimation(seq,ai);
    GSmodelSetForceUseFractionalFramesFlag(e[1],1); GSmodelSetSkipFractionalFramesFlag(e[1],1);
    return (long)e;
}

/* 0x80089D04 */
int CMenuHologram::actionYesNo(u32 msgId, bool exec){
    if(exec) exec__11CInfoWindowFR9CMetaMenuUlb((void*)m_infoWindow,this,msgId,0);
    else open__11CInfoWindowFUlb((void*)m_infoWindow,msgId,0);
    int r=actionMenu__9CMetaMenuFPUlill((u32*)msgTbl$2067,2,0x1FE,0x7F,0);
    close__11CInfoWindowFv((void*)m_infoWindow);
    return r;
}

/* 0x80089D90 */
void CMenuHologram::loop(){
    field_0x27C=1; memset((void*)((u8*)this+0x290),0,0x40);
    while(1){
        update__6CStateFv((void*)((u8*)this+0x278));
        if(field_0x278>8) continue;
        switch(field_0x27C){
            case 0:
                if(isReliveReady__12CReliveStageFv()){field_0x27C=4;memset((void*)((u8*)this+0x290),0,0x40);}
                else{field_0x27C=2;memset((void*)((u8*)this+0x290),0,0x40);}
                break;
            case 1:
                m_animating=1; stateMainProc(); break;
            case 2:
                {int sel=actionMenu__9CMetaMenuFPUlill((u32*)msgTbl$2047,3,0x1B8,0x78,0);
                if(sel==1){moveStageWait((int)m_cursor);field_0x27C=2;}
                else if(sel>=2&&sel<3) field_0x27C=2;
                else if(sel==0) field_0x27C=5;}
                break;
            case 3: moveStageWait((int)m_cursor); field_0x27C=2; break;
            case 4: stateReliveCeremony(); break;
            case 5:
                relivehallSetLastViewStage__Fl(m_stage);
                systemFadeOutSetAndWait__9CMetaMenuFf(0.5f);
                {u32* ptr=(u32*)((u8*)this+0x410);u32 prev=ptr[2];ptr[1]=prev;ptr[2]=2;}
                goto exit;
            case 6:
                {int r=actionYesNo(0x1000-0x2EA4,false);
                if(r!=0) field_0x27C=8; else field_0x27C=2;}
                break;
            case 7: case 8:
                relivehallSetLastViewStage__Fl(m_stage);
                systemFadeOutSetAndWait__9CMetaMenuFf(0.5f);
                {u32* ptr=(u32*)((u8*)this+0x410);u32 prev=ptr[2];ptr[1]=prev;ptr[2]=0;}
                goto exit;
        }
        memset((void*)((u8*)this+0x290),0,0x40);
    }
exit:;
}

/* 0x80089FC0 */
void CMenuHologram::init(CMenuGlobalState& state){
    m_globalState=(u32)&state;
    memset((void*)((u8*)this+0x278),0,4); init__6CStateFv((void*)((u8*)this+0x278));
    memset((void*)this,0,4); memset((void*)((u8*)this+0x1C),0,0x100);
    memset((void*)((u8*)this+0x11C),0,0x100);
    if(pcReliveHallSoundTbl) memcpy((void*)((u8*)this+8),pcReliveHallSoundTbl,0x14);
    memset((void*)((u8*)this+0x220),0,0x1A); m_animating=0;
    memset((void*)((u8*)this+0x348),0,0x20);
    m_stage=0; m_cursor=0; m_stagePtr=0; m_lightCount=0; m_texture=0;
    m_seqLoaded=0; m_seqNeck=0; m_wazaSeq=0; m_seqVisitor=0;
    localWindowSetTable__9CMetaMenuFPl(this,localWindowTable);
    init__11CInfoWindowFlUl((void*)((u8*)this+0x3DC),0xD0,0x5DA);
    m_infoWindow=(u32)((u8*)this+0x3DC);
    setStageToReliveReady(); reloadDatas(true);
}

/* 0x8008A100 */
void CMenuHologram::main(CMenuGlobalState& state){
    systemFadeOutKeepAfterFloorPush__9CMetaMenuFv();
    init(state);
    systemFadeInKick__9CMetaMenuFv();
    loop();
    unloadDatas();
    systemFadeInKick__9CMetaMenuFv();
}

// Vtable for CMenuHologram - TODO: Complete when structure is verified
// static const u32 __vt__26unnamed_menuHologram_cpp13CMenuHologram[] = {
//     0, 0,  // thisFree / base vtable pointers
//     (u32)&CMenuHologram::drawAll,
//     (u32)&CMenuHologram::stateReliveCeremony,
//     (u32)&CMenuHologram::stateMainProc,
//     // ... additional vtable entries
// };
