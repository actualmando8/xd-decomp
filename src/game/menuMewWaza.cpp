// Decompiled from: menuMewWaza.cpp
// Address range: 0x800A6138..0x800A63DC | size: 0x2A4

void*   windowGetFreeWork(void);
s32     winSpriteGetLayerID(void* window, void* sprite);
void*   GSgfxLayerFindByID(s32 id);
void    spriteSetOffset(s32 layer, s32 x, s32 y);
void    spriteSetEnv(s32 layer);
s32     _GetMewWazaName__Fl(s32 index);
const char* GSmsgGetGSchar(s32 id);
void    msgctrlSetValue(s32 a, const char* str);
void    GSmsgPrint2(s32 layer, s32 a, s32 b, s32 c);
void    menuSubDrawMsgWindow2(s32 layer, s32 a, s32 b, s32 c, s32 d);
void    GSmsgMain(s32 layer, s32 a, s32 b, s32 c);
void*   mewWazaGet(s32 index);
void*   wazaDataBiosGetPtr(void);
const char* wazaDataBiosGetName(void);

/*
  Address: 0x800A6138 | size: 0x8
  menuMewWazaGetMenuDataID()
  Returns menu data ID 0x10C.
*/
s32 menuMewWazaGetMenuDataID(void) {
    return 0x10C;
}

/*
  Address: 0x800A6140 | size: 0x274
  menuMewWazaDraw(void* window, void* data)
  Draws Mew Waza information. Dispatches based on data[0x6]:
    0x2B: Draw message window with position from data
    0x2C: Print Mew Waza name 0 with msg ID 0x38D3
    0x2D: Print Mew Waza name 1 with msg ID 0x38D2
    0x2E: Print Mew Waza name 2 with msg ID 0x38D1
    0x2F: Print Mew Waza name 3 with msg ID 0x38D0
    Other: No-op
  Also handles GSmsgMain based on window flags.
*/
s32 menuMewWazaDraw(void* window, void* data) {
    s32 result;
    void* work = windowGetFreeWork();
    s32 layer = winSpriteGetLayerID(window, data);
    void* gfxLayer = GSgfxLayerFindByID(layer);
    
    s16 posZ = data->field_0x56;
    s16 posX = data->field_0x52;
    s16 posY = data->field_0x50;
    s16 offsetZ = data->field_0x8C;
    s16 offsetX = data->field_0x8E;
    s16 spriteX = data->field_0x54;
    
    spriteSetOffset(layer, (s32)(posX + (posZ - (posZ << 1))), (s32)(posY + offsetZ + offsetX));
    spriteSetEnv(layer);
    
    s16 type = data->field_0x6;
    
    if (type == 0x2B) {
        menuSubDrawMsgWindow2(layer, 0, -2, spriteX, posZ);
        GSmsgPrint2(layer, 0, 0, data->field_0x93 | -256, 0, 0x1, -0x38DE);
        
        s8 flag = window->field_0x1;
        if (flag != 3 && flag >= 2 && flag < 5) {
            if (window->field_0x4 != 0x14) {
                s8 type2 = window->field_0x0;
                s32 bool_val = (type2 != 0);
                s32 cntlz = __builtin_clz(bool_val);
                GSmsgMain(layer, work->field_0x0, work->field_0x8, (cntlz >> 5) & 1);
                work->field_0x8 = 0;
            }
        }
    }
    else if (type == 0x2C) {
        const char* name = GSmsgGetGSchar(_GetMewWazaName__Fl(0));
        msgctrlSetValue(0x4D, name);
        GSmsgPrint2(layer, 0, 0, data->field_0x93 | -256, 0, 0x1, -0x38D3);
    }
    else if (type == 0x2D) {
        const char* name = GSmsgGetGSchar(_GetMewWazaName__Fl(1));
        msgctrlSetValue(0x4D, name);
        GSmsgPrint2(layer, 0, 0, data->field_0x93 | -256, 0, 0x1, -0x38D2);
    }
    else if (type == 0x2E) {
        const char* name = GSmsgGetGSchar(_GetMewWazaName__Fl(2));
        msgctrlSetValue(0x4D, name);
        GSmsgPrint2(layer, 0, 0, data->field_0x93 | -256, 0, 0x1, -0x38D1);
    }
    else if (type == 0x2F) {
        const char* name = GSmsgGetGSchar(_GetMewWazaName__Fl(3));
        msgctrlSetValue(0x4D, name);
        GSmsgPrint2(layer, 0, 0, data->field_0x93 | -256, 0, 0x1, -0x38D0);
    }
    
    result = 0;
    return result;
}

/*
  Address: 0x800A63B4 | size: 0x28
  _GetMewWazaName__Fl(s32 index)
  Gets Mew Waza name by index. Calls mewWazaGet, wazaDataBiosGetPtr, wazaDataBiosGetName.
  Metrowerks mangled name: _GetMewWazaName(long)
*/
s32 _GetMewWazaName__Fl(s32 index) {
    mewWazaGet(index);
    wazaDataBiosGetPtr();
    wazaDataBiosGetName();
    return 0;
}
