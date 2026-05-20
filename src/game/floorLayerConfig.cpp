// Decompiled from: floorLayerConfig.cpp
// Address range: 0x8007E350..0x8007E5AC | size: 0x25C

/* Forward declarations */
void    Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(void* config);
s32     GSgfxLayerFindByName_C(const char* name);
s32     GSgfxLayerFindByID(s32 id);
void    SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(
            void* layer, s32 a, bool b, void* c, s32 d, void* e);
void    dbgMenuSetLayerID(s32 layerId);

/* SData */
static s32 g_empty_layer_config;
static s32 g_map_layer_config;
static s32 g_fight_layer_config;
static s32 g_menu_layer_config;
static s32 g_floor_layer_config_list;
static s32 g_floor_layer_config_count;

/* SBSS */
static s32 _menu_extra_layer_id;

/* Data - Layer names */
static const char* g_layer_names[] = {
    "background",
    "background distortion",
    "main",
    "main distortion",
    "secondary",
    "secondary distortion",
    "filter",
    "menu",
};

/* Data - Layer configs */
static const s32 _empty_layer_config[] = {
    0x00000002, 0x00000000, 0x00000000, 0x00000001,
    0x00050000, 0x00050000, 0x00000010, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

static const s32 _map_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00060000, 0x00030000, 0x00000010, 0x00000002,
    0x00000000, 0x00000000, 0x00000001, 0x00050000,
    0x00050000, 0x00000010, 0x00000004, 0x00000000,
    0x00000000, 0x00000101, 0x00010000, 0x00020000,
    0x00000010, 0x00000006, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00002000, 0x00000001,
    0x00000007, 0x00000000, 0x00000000, 0x00000001,
    0x00000000, 0x00018000, 0x00000008, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

static const s32 _fight_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00040000, 0x00040000, 0x00000010, 0x00000001,
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00020000, 0x00000010, 0x00000002, 0x00000000,
    0x00000000, 0x00000001, 0x00080000, 0x00050000,
    0x00000010, 0x00000003, 0x00000000, 0x00000001,
    0x00000000, 0x00000000, 0x00010000, 0x00000010,
    0x00000004, 0x00000000, 0x00000000, 0x00000101,
    0x00020000, 0x00084800, 0x00000010, 0x00000005,
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00014000, 0x00000010, 0x00000006, 0x00000000,
    0x00000000, 0x00000001, 0x00000000, 0x00004000,
    0x00000001, 0x00000007, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00020000, 0x00000010,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000,
};

static const s32 _menu_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00040000, 0x00040000, 0x00000020, 0x000000FF,
    "menu extra", 0x00000000, 0x00000101, 0x00020000,
    0x00040000, 0x00000010, 0x00000002, 0x00000000,
    0x00000000, 0x00000001, 0x00050000, 0x00050000,
    0x00000010, 0x00000004, 0x00000000, 0x00000000,
    0x00000101, 0x00010000, 0x00040000, 0x00000010,
    0x00000006, 0x00000000, 0x00000000, 0x00000001,
    0x00000000, 0x00002000, 0x00000001, 0x00000007,
    0x00000000, 0x00000000, 0x00000001, 0x00020000,
    0x00040000, 0x00000010, 0xFFFFFFFF, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

static const s32 _evolution_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00040000, 0x00040000, 0x00000020, 0x00000002,
    0x00000000, 0x00000000, 0x00000001, 0x00050000,
    0x00050000, 0x00000010, 0x00000004, 0x00000000,
    0x00000000, 0x00000101, 0x00040000, 0x00040000,
    0x00000010, 0x00000006, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00002000, 0x00000001,
    0x00000007, 0x00000000, 0x00000000, 0x00000001,
    0x00020000, 0x00040000, 0x00000010, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

static const s32 _M6_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00070000, 0x00030000, 0x00000010, 0x00000002,
    0x00000000, 0x00000000, 0x00000001, 0x00050000,
    0x00050000, 0x00000010, 0x00000004, 0x00000000,
    0x00000000, 0x00000101, 0x00010000, 0x00020000,
    0x00000010, 0x00000006, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00002000, 0x00000001,
    0x00000007, 0x00000000, 0x00000000, 0x00000001,
    0x00000000, 0x00018000, 0x00000008, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000,
};

static const s32 _M6_out_bf_layer_config[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000001,
    0x00050000, 0x00040000, 0x00000010, 0x00000001,
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00020000, 0x00000010, 0x00000002, 0x00000000,
    0x00000000, 0x00000001, 0x00080000, 0x00050000,
    0x00000010, 0x00000003, 0x00000000, 0x00000001,
    0x00000000, 0x00000000, 0x00010000, 0x00000010,
    0x00000004, 0x00000000, 0x00000000, 0x00000101,
    0x00020000, 0x00084800, 0x00000010, 0x00000005,
    0x00000000, 0x00000001, 0x00000000, 0x00000000,
    0x00014000, 0x00000010, 0x00000006, 0x00000000,
    0x00000000, 0x00000001, 0x00000000, 0x00004000,
    0x00000001, 0x00000007, 0x00000000, 0x00000000,
    0x00000001, 0x00000000, 0x00020000, 0x00000010,
    0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000,
};

static const s32 _floor_layer_config_list[] = {
    (s32)&_M6_layer_config, 0x99,
    (s32)&_M6_out_bf_layer_config, 0x21E,
    (s32)&_evolution_layer_config, 0x386,
};

/*
  Address: 0x8007E350 | size: 0x4
  floorLayerConfigLoad(void)
  Stub function for loading floor layer config.
*/
void floorLayerConfigLoad(void) {
    // Stub
}

/*
  Address: 0x8007E354 | size: 0x8
  floorGetMenuLayerID(void)
  Returns the menu extra layer ID.
*/
s32 floorGetMenuLayerID(void) {
    return _menu_extra_layer_id;
}

/*
  Address: 0x8007E35C | size: 0x148
  floorLayerConfig(s32 floorId, s32 mode)
  Configures the layer setup based on floor ID and mode.
*/
void floorLayerConfig(s32 floorId, s32 mode) {
    // Search floor config list
    s32* list = (s32*)g_floor_layer_config_list;
    s32 count = g_floor_layer_config_count;
    
    for (s32 i = 0; i < count; i++) {
        if (list[i * 2 + 1] == floorId) {
            s32* config = (s32*)list[i * 2];
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData(config);
            s32 layer = GSgfxLayerFindByName_C("debug menu");
            dbgMenuSetLayerID(layer);
            return;
        }
    }
    
    // Handle mode-based config
    switch (mode) {
        case 1:
            // Map mode
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData((void*)g_map_layer_config);
            s32 layer0 = GSgfxLayerFindByID(0);
            s32 layer2 = GSgfxLayerFindByID(2);
            SetPassRedirect__10GSgfxLayerF14GSgfxLayerPassbP10GSgfxLayer14GSgfxLayerPass16GSgfxLayerOffset(
                layer0, 1, 1, layer2, 0, 2);
            break;
        case 2:
        case 4:
            // Fight mode
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData((void*)g_fight_layer_config);
            break;
        case 3:
        case 5:
        case 6:
            // Menu mode
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData((void*)g_menu_layer_config);
            s32 menuLayer = GSgfxLayerFindByName_C("menu extra");
            _menu_extra_layer_id = menuLayer;
            break;
        case 7:
            // Menu mode (alternate)
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData((void*)g_menu_layer_config);
            s32 menuLayer2 = GSgfxLayerFindByName_C("menu");
            _menu_extra_layer_id = menuLayer2;
            break;
        default:
            // Empty config
            Setup__16GSgfxLayerConfigFP15_GSgfxLayerData((void*)g_empty_layer_config);
            break;
    }
    
    s32 debugLayer = GSgfxLayerFindByName_C("debug menu");
    dbgMenuSetLayerID(debugLayer);
}

/*
  Address: 0x8007E4A4 | size: 0x108
  __sinit_floorLayerConfig_cpp(void)
  Static initializer for floorLayerConfig.cpp.
*/
void __sinit_floorLayerConfig_cpp(void) {
    // Initialize global layer config pointers
    g_empty_layer_config = (s32)&_empty_layer_config;
    g_map_layer_config = (s32)&_map_layer_config;
    g_fight_layer_config = (s32)&_fight_layer_config;
    g_menu_layer_config = (s32)&_menu_layer_config;
    g_floor_layer_config_list = (s32)&_floor_layer_config_list;
    g_floor_layer_config_count = 3;
}
