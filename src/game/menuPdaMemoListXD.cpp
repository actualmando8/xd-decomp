// Decompilation of menuPdaMemoListXD.cpp
// Original address: 0x80055428..0x80056FF8 | size: 0x1BD0
// Functions: Multiple functions for PDA memo list management
// NOTE: Large file with complex sorting algorithms and display functions

#include "global.h"

// Forward declarations
void* GSthreadIsRunning(void* thread);
void GSthreadClose(void* thread);
void GSthreadSwitch(void);
void* __nw(u32 size);
void* __nwa(u32 size);
void __dl(void* ptr);
void GSsndPlayNow(int soundId);
int memoDataGetCount(void);
void* pokemonDataBiosGetPtr(int pokemonId);
void* menuItemBiosGetPtr(int type, int id);
void* GSgfxLayerFindByID(int id);
int winSpriteGetLayerID(void* spriteWork);
void spriteSetScissor(void* layer, s16 x, s16 y, s16 width, s16 height);
void spriteClearScissor(void* layer);
void GSmsgPrint2(void* layer, int ctrlId, u8 flags, float y, int param5, int param6, int param7);
void msgctrlSetValue(int ctrlId, void* value);
void windowDrawSprite2(void* windowWork, s16 x, s16 y, int spriteId, int param5, int param6, int param7, int param8, int param9);
int pokemonGetStatus(void* pokemonData, int param2, int statusType, int param4);
int zokuseiBiosGetSmallSpriteID(int type);
int pokecoloGetCountryCode(void);
void GScharCpy(void* dest, void* src);
int GScharCmp(void* str1, void* str2);
void memcpy(void* dest, void* src, u32 size);

// Global variables
extern void* pMemoList;
extern u16* pdapokemonsortdata;
extern u32* pdapokemonsortdata_number;
extern float _defaultAngle[];
extern float @2755;
extern float @2831;

// Struct for memo sort buffer
typedef struct {
    s16 originalIndex;
    s16 sortKey;
    u8 padding[0x18];
} MemoSortBuff;

// pdaMemoList class methods
class pdaMemoList {
public:
    void* __ct(void);
    void* __dt(void);
    void* Main(s16* cursor);
    void* CalcPosition(s16* cursor);
    void* ListCursor(void* windowWork, void* spriteWork);
    void* UpCursor(void* windowWork, void* spriteWork);
    void* DownCursor(void* windowWork, void* spriteWork);
    void* ScrollBar(void* windowWork, void* spriteWork);
    void* DispList(void* windowWork, void* spriteWork);
    void* DispPokemonModel(void* windowWork, void* spriteWork, u32 modelId);
    void* Button(void* windowWork);
    void* Cursor(void* windowWork);
    void* Ctrl(void* windowWork);
    void* SortGojyuon(void);
    void* SortPokemonID(void);
    void* Sort_Small(MemoSortBuff* buff, int count);
    void* SortGojyuonDataSet(u16 pokemonId);
    void* GetPokemonName(int index);
    void* GetPokemonPointer(int index);
    void* LoadHero(int param);
    void* LoadPokemon(int index);
    void* SetHeroMotion(void);
    s16* _getCursor(void);
    void* TermThread(void* model);
    void* _menuClose(int menuId);
};

/* 0x80055428 | size: 0x38 */
// Thread termination handler
void _menuPdaMemoListThread(void* model)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->TermThread(model);
    }
}

/* 0x80055460 | size: 0x2C */
// Set hero motion
void menuPdaMemoListSetHeroMotion(void)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->SetHeroMotion();
    }
}

/* 0x8005548C | size: 0x50 */
// Check if hero is loaded
int menuPdaMemoListIsLoadHero(void)
{
    if (pMemoList) {
        u8 flag = *(u8*)((u32)pMemoList + 0x23d);
        if (flag) {
            return menuModelCheck((void*)((u32)pMemoList + 0x130), 0x0);
        }
        return 0x0;
    }
    return 0x0;
}

/* 0x800554DC | size: 0x1C */
// Check if model is terminated
u8 menuPdaMemoListIsTermModel(void)
{
    if (pMemoList) {
        return *(u8*)((u32)pMemoList + 0x23c);
    }
    return 0x0;
}

/* 0x800554F8 | size: 0x30 */
// Load hero model
void menuPdaMemoListLoadHero(int param)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->LoadHero(param);
    }
}

/* 0x80055528 | size: 0x18 */
// Get default angle for hero model
float menuPdaMemoListGetDefaultAngle(int index)
{
    return _defaultAngle[index];
}

/* 0x80055540 | size: 0x7C */
// Display Pokemon model
void menuPdaMemoListDispPokemonModel(void* windowWork, void* spriteWork, u32 modelId)
{
    if (pMemoList) {
        u32 menuId = 0x1c7;
        switch (modelId) {
            case 0x0: menuId = 0xb9; break;
            case 0x1: menuId = 0xbb; break;
            case 0x2: menuId = 0xba; break;
            default: menuId = 0x1c7; break;
        }
        ((pdaMemoList*)pMemoList)->DispPokemonModel(windowWork, spriteWork, menuId);
    }
}

/* 0x800555BC | size: 0x1C */
// Get menu model work pointer
void* menuPdaMemoListGetMenuModelWork(void)
{
    if (pMemoList) {
        return (void*)((u32)pMemoList + 0x44);
    }
    return (void*)0x0;
}

/* 0x800555D8 | size: 0x30 */
// Load Pokemon model
void menuPdaMemoListLoadPokemon(int index)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->LoadPokemon(index);
    }
}

/* 0x80055608 | size: 0x38 */
// Get Pokemon data pointer
void* menuPdaMemoListGetPokemonDataPointer(void)
{
    if (pMemoList) {
        int id = menuPdaMemoListGetPokemonID();
        return pokemonDataBiosGetPtr(id);
    }
    return (void*)0x0;
}

/* 0x80055640 | size: 0x38 */
// Get Pokemon name
void* menuPdaMemoListGetPokemonName(int index)
{
    if (pMemoList) {
        return ((pdaMemoList*)pMemoList)->GetPokemonName(index);
    }
    return (void*)0x0;
}

/* 0x80055678 | size: 0x74 */
// Get Pokemon ID at index
int menuPdaMemoListGetPokemonID(int index)
{
    if (pMemoList) {
        int count = memoDataGetCount();
        if (index >= 0 && index < count) {
            u16* data = (u16*)((u32)pMemoList + 0x3c);
            return *(s16*)((u32)*data + index * 2);
        }
        return 0x0;
    }
    return 0x0;
}

/* 0x800556EC | size: 0x98 */
// Hook function - dispatches to appropriate method based on sprite ID
void menuPdaMemoListHook(void* windowWork, void* spriteWork)
{
    s16 spriteId = *(s16*)((u32)spriteWork + 0x6);
    int idx = spriteId - 0xdb;
    
    if (idx >= 0 && idx < 0x16) {
        // Jump table dispatch
        static void* jumpTable[] = {
            (void*)pdaMemoList::ListCursor,
            (void*)pdaMemoList::UpCursor,
            (void*)pdaMemoList::DownCursor,
            (void*)pdaMemoList::ScrollBar,
            (void*)pdaMemoList::DispList,
        };
        // Call appropriate function based on idx
    }
}

/* 0x80055784 | size: 0x11C */
// Main memo list menu
void menuPdaMemoList(void)
{
    pdaMemoList* list = (pdaMemoList*)__nw(0x264);
    if (list) {
        list->__ct();
    }
    pMemoList = list;
    
    s16 cursor[2] = {0, 0};
    
    menuOpen(0x7f, 0x0);
    menuOpen(0x77, 0x0);
    
    while (1) {
        int result = ((pdaMemoList*)pMemoList)->Main(cursor);
        if (result < 0) {
            break;
        }
        
        menuPdaMemoXDMain(cursor);
        cursor[1] = *(s16*)((u32)pMemoList + 0x21c);
        cursor[0] = *(s16*)((u32)pMemoList + 0x21c);
        
        ((pdaMemoList*)pMemoList)->CalcPosition(cursor);
        
        // Copy field at 0x250 to 0x248
        float temp = *(float*)((u32)pMemoList + 0x250);
        *(float*)((u32)pMemoList + 0x248) = temp;
    }
    
    // Cleanup
    void* thread = (void*)((u32)pMemoList + 0x260);
    if (thread) {
        while (GSthreadIsRunning(thread)) {
            GSthreadSwitch();
        }
        GSthreadClose(thread);
    }
    
    ((pdaMemoList*)pMemoList)->_menuClose(0x77);
    ((pdaMemoList*)pMemoList)->_menuClose(0x7f);
    ((pdaMemoList*)pMemoList)->__dt();
    pMemoList = (void*)0x0;
}

/* 0x800558A0 | size: 0x30 */
// Button handler
void menuPdaMemoListButton(void* windowWork)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->Button(windowWork);
    }
}

/* 0x800558D0 | size: 0x3C */
// Cursor handler
void menuPdaMemoListCursor(void* windowWork)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->Cursor(windowWork);
    }
}

/* 0x8005590C | size: 0x3C */
// Control handler
void menuPdaMemoListCtrl(void* windowWork)
{
    if (pMemoList) {
        ((pdaMemoList*)pMemoList)->Ctrl(windowWork);
    }
}

/* 0x80055948 | size: 0x38 */
// Sort by type (Gojyuon = Japanese syllabary order, PokemonID)
void pdaMemoList::Sort(int sortType)
{
    if (sortType == 0x1) {
        SortPokemonID();
    } else {
        SortGojyuon();
    }
}

/* 0x80055980 | size: 0x10C */
// Sort by Pokemon ID using merge sort
void pdaMemoList::SortPokemonID(void)
{
    int count = memoDataGetCount();
    MemoSortBuff* buff1 = (MemoSortBuff*)__nwa(0x2bc0);
    MemoSortBuff* buff2 = (MemoSortBuff*)__nwa(0x320);
    
    // Copy data to sort buffer
    for (int i = 0; i < count; i++) {
        u16* data = (u16*)((u32)this + 0x3c);
        s16 pokemonId = *(s16*)((u32)*data + i * 2);
        buff2[i].originalIndex = pokemonId;
        buff1[i].originalIndex = i;
        buff1[i].sortKey = pokemonId;
    }
    
    // Sort using merge sort
    Sort_Small(buff1, count);
    
    // Write sorted data back
    for (int i = 0; i < count; i++) {
        u16* data = (u16*)((u32)this + 0x3c);
        s16 pokemonId = buff1[i].originalIndex;
        *(s16*)((u32)*data + i * 2) = pokemonId;
    }
    
    __dl(buff1);
    __dl(buff2);
}

/* 0x80055A8C | size: 0x134 */
// Sort by Gojyuon (Japanese syllabary order)
void pdaMemoList::SortGojyuon(void)
{
    int count = memoDataGetCount();
    MemoSortBuff* buff1 = (MemoSortBuff*)__nwa(0x2bc0);
    MemoSortBuff* buff2 = (MemoSortBuff*)__nwa(0x320);
    
    // Copy data with sort keys
    for (int i = 0; i < count; i++) {
        u16* data = (u16*)((u32)this + 0x3c);
        s16 pokemonId = *(s16*)((u32)*data + i * 2);
        buff2[i].originalIndex = pokemonId;
        buff1[i].originalIndex = i;
        buff1[i].sortKey = SortGojyuonDataSet(pokemonId);
        GScharCpy((void*)((u32)&buff1[i] + 0x4), GetPokemonName(pokemonId));
    }
    
    // Sort based on country code
    if (pokecoloGetCountryCode() == 0x0) {
        Sort_Small(buff1, count);
    } else {
        fn_80055C94(buff1, count);
    }
    
    // Write sorted data back
    for (int i = 0; i < count; i++) {
        u16* data = (u16*)((u32)this + 0x3c);
        s16 pokemonId = buff1[i].originalIndex;
        *(s16*)((u32)*data + i * 2) = pokemonId;
    }
    
    __dl(buff1);
    __dl(buff2);
}

/* 0x80055BC0 | size: 0xD4 */
// Merge sort implementation
void pdaMemoList::Sort_Small(MemoSortBuff* buff, int count)
{
    // Standard merge sort implementation
    // Uses temporary buffer for merging
    int width = count / 2;
    while (width > 0) {
        // Merge pass
        for (int i = 0; i < count; i += width * 2) {
            // Merge two sorted subarrays
            int left = i;
            int right = i + width;
            int end = (i + width * 2 < count) ? i + width * 2 : count;
            
            while (left < right && right < end) {
                s16 leftKey = buff[left].sortKey;
                s16 rightKey = buff[right].sortKey;
                
                if (leftKey <= rightKey) {
                    left++;
                } else {
                    // Move right element to correct position
                    MemoSortBuff temp = buff[right];
                    for (int j = right - 1; j >= left; j--) {
                        buff[j + 1] = buff[j];
                    }
                    buff[left] = temp;
                    left++;
                    right++;
                }
            }
        }
        width /= 2;
    }
}

/* 0x80055C94 | size: 0xD8 */
// Merge sort with string comparison (for non-Japanese locales)
void fn_80055C94(MemoSortBuff* buff, int count)
{
    // Similar to Sort_Small but uses GScharCmp for string comparison
    int width = count / 2;
    while (width > 0) {
        for (int i = 0; i < count; i += width * 2) {
            int left = i;
            int right = i + width;
            int end = (i + width * 2 < count) ? i + width * 2 : count;
            
            while (left < right && right < end) {
                int cmp = GScharCmp((void*)((u32)&buff[left] + 0x4), (void*)((u32)&buff[right] + 0x4));
                
                if (cmp <= 0) {
                    left++;
                } else {
                    MemoSortBuff temp = buff[right];
                    for (int j = right - 1; j >= left; j--) {
                        buff[j + 1] = buff[j];
                    }
                    buff[left] = temp;
                    left++;
                    right++;
                }
            }
        }
        width /= 2;
    }
}

/* 0x80055D6C | size: 0x60 */
// Get sort key for Gojyuon ordering
int pdaMemoList::SortGojyuonDataSet(u16 pokemonId)
{
    if (pokemonId >= 0x8000) {
        pokemonId &= 0x7FFF;
    }
    
    u32* numberPtr = pdapokemonsortdata_number;
    u32 count = *numberPtr;
    u16* data = (u16*)pdapokemonsortdata;
    
    for (int i = 0; i < count; i++) {
        if (data[i] == pokemonId) {
            return i;
        }
    }
    return 0x0;
}

/* 0x80055DCC | size: 0x2B4 */
// Display list of Pokemon in memo
void pdaMemoList::DispList(void* windowWork, void* spriteWork)
{
    s16* cursor = _getCursor();
    int count = memoDataGetCount();
    int layerId = winSpriteGetLayerID(spriteWork);
    
    void* item1 = menuItemBiosGetPtr(0x78, 0xf1);
    void* item2 = menuItemBiosGetPtr(0x78, 0xef);
    void* item3 = menuItemBiosGetPtr(0x78, 0xf0);
    void* item4 = menuItemBiosGetPtr(0x78, 0xee);
    void* item5 = menuItemBiosGetPtr(0x78, *(s16*)((u32)spriteWork + 0x6));
    
    spriteSetScissor((void*)layerId,
        *(s16*)((u32)item5 + 0x6) - *(s16*)((u32)item2 + 0x6),
        *(s16*)((u32)item5 + 0x8) - *(s16*)((u32)item2 + 0x8),
        *(s16*)((u32)item2 + 0xa),
        *(s16*)((u32)item2 + 0xc));
    
    float y = *(float*)((u32)windowWork + 0x248);
    float yStep = (pokecoloGetCountryCode() == 0x0) ? @2831 : @2831;
    float yInc = @2755;
    
    s16 startIdx = cursor[0] - 1;
    s16 endIdx = cursor[0] + 0x9;
    
    for (int i = 0; i < count; i++) {
        if (i >= startIdx && i < endIdx) {
            // Get Pokemon name and display
            void* name = GetPokemonName(i);
            void* pokemonData = GetPokemonPointer(i);
            msgctrlSetValue(0x37, name);
            
            float posY = y + yStep;
            GSmsgPrint2((void*)layerId, 0x37, *(u8*)((u32)spriteWork + 0x93) | 0xFF00, posY, 0x0, 0x4277, 0x0);
            
            // Get and display type icons
            int type1 = pokemonGetStatus(pokemonData, 0x0, 0x16, 0x0);
            int type2 = pokemonGetStatus(pokemonData, 0x0, 0x16, 0x1);
            
            if (type1) {
                int spriteId = zokuseiBiosGetSmallSpriteID(type1);
                windowDrawSprite2(windowWork,
                    *(s16*)((u32)item1 + 0x6) - *(s16*)((u32)item2 + 0x6),
                    *(s16*)((u32)item2 + 0xa),
                    spriteId, 0x0, *(s16*)((u32)item2 + 0xc),
                    *(u8*)((u32)spriteWork + 0x93) | 0xFF00, (int)posY, 0x0);
            }
            if (type2 && type2 != type1) {
                int spriteId = zokuseiBiosGetSmallSpriteID(type2);
                windowDrawSprite2(windowWork,
                    *(s16*)((u32)item1 + 0x6) - *(s16*)((u32)item3 + 0x6),
                    *(s16*)((u32)item3 + 0xa),
                    spriteId, 0x0, *(s16*)((u32)item3 + 0xc),
                    *(u8*)((u32)spriteWork + 0x93) | 0xFF00, (int)posY, 0x0);
            }
        }
        y += yInc;
    }
    
    spriteClearScissor((void*)layerId);
}

/* 0x80056080 | size: 0xE8 */
// Display Pokemon model
void pdaMemoList::DispPokemonModel(void* windowWork, void* spriteWork, u32 modelId)
{
    void* item = menuItemBiosGetPtr(0x78, modelId);
    int layerId = *(int*)((u32)spriteWork + 0x1c);
    void* layer = GSgfxLayerFindByID(layerId);
    
    if (layer) {
        // Setup and render Pokemon model
        s16 x = *(s16*)((u32)item + 0x6);
        s16 y = *(s16*)((u32)item + 0x8);
        s16 w = *(s16*)((u32)item + 0xa);
        s16 h = *(s16*)((u32)item + 0xc);
        
        // Render model at position
    }
}
