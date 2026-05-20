// Decompiled from: dbgMenuMemcard.cpp
// Address range: 0x8000B620..0x8000BAE4 | size: 0x4C4

/* Forward declarations */
s32     GSdvdOpenTest(const char* filename);
s32     GSdvdOpen(const char* filename);
void    GSdvdClose(s32 handle);
void    GSdvdRead(s32 handle, void* buffer, s32 size);
void    GSdvdWrite(s32 handle, void* buffer, s32 size);
s32     GSdvdCreate(const char* filename);
void*   GSmemAllocAlign(s32 size, s32 alignment);
void    GSmemFree(void* ptr);
void    memcard_debug_Load(void* data);
void    memcard_debug_Load2(void);
void    memcard_debug_Save(void* data);
void*   memcardMemAllocForSavedata(void);
void    memcardMemFreeForSavedata(void* ptr);
s32     memcardTaskCall(s32 task, s32 a, s32 b);
void*   savedataGetStatus(s32 a, s32 b);
void    gamedataSetStatus(void* saveData, s32 slot, s32 status);
s32     pokecoloGetCountryCode(void);
void    winMsgOpen(s32 menuId, s32 msgId, s32 a, s32 b);
void    winMsgClose(s32 menuId);
void    __assert(const char* file, s32 line, const char* msg);
void*   memcpy(void* dest, const void* src, s32 size);

/* Save file names for slots 0-9 (5 regular + 5 HD) */
static const char* saveFileName[] = {
    "HDSaveData1.DSV1",
    "HDSaveData2.DSV1",
    "HDSaveData3.DSV1",
    "HDSaveData4.DSV1",
    "HDSaveData5.DSV1",
    "HDSaveData_1.DSV2",
    "HDSaveData_2.DSV2",
    "HDSaveData_3.DSV2",
    "HDSaveData_4.DSV2",
    "HDSaveData_5.DSV2",
};

/* Global state */
static void* dbgMenuSaveData;
static void* bk_savedataPtr;
extern void* now_savedata_ptr;

/*
  Address: 0x8000B620 | size: 0x24
  _memcard_debug_type_check(s32 slot)
  Returns 1 if slot is 0-4 (regular save), 0 otherwise (HD save).
*/
static s32 _memcard_debug_type_check(s32 slot) {
    if (slot >= 0 && slot < 5) {
        return 1;
    }
    return 0;
}

/*
  Address: 0x8000B644 | size: 0x20C
  dbgMenuMemcardDebugLoad(s32 slot)
  Loads save data from DVD for debug purposes.
  For regular saves (slot 0-4): Reads to temp buffer, calls memcard_debug_Load.
  For HD saves (slot 5-9): Reads directly to now_savedata_ptr.
  Sets game data status based on country code.
*/
s32 dbgMenuMemcardDebugLoad(s32 slot) {
    s32 handle = GSdvdOpen(saveFileName[slot]);
    
    if (handle == 0) {
        return 0;
    }
    
    if (_memcard_debug_type_check(slot)) {
        // Regular save - allocate temp buffer
        void* buffer = GSmemAllocAlign(0x8000, 0x20);
        dbgMenuSaveData = buffer;
        
        GSdvdRead(handle, buffer, 0);
        GSdvdClose(handle);
        
        memcard_debug_Load((u8*)dbgMenuSaveData + 8);
        
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = 0;
    } else {
        // HD save - read directly
        GSdvdRead(handle, now_savedata_ptr, 0);
        GSdvdClose(handle);
        memcard_debug_Load2();
    }
    
    // Set game data status based on country
    void* saveData = savedataGetStatus(0, 1);
    s32 country = pokecoloGetCountryCode();
    
    switch (country) {
        case 0: // US
            gamedataSetStatus(saveData, 2, 0xB);
            gamedataSetStatus(saveData, 3, 0x3);
            gamedataSetStatus(saveData, 4, 0x1);
            gamedataSetStatus(saveData, 5, 0x1);
            break;
        case 1: // Japan
            gamedataSetStatus(saveData, 2, 0xB);
            gamedataSetStatus(saveData, 3, 0x3);
            gamedataSetStatus(saveData, 4, 0x2);
            gamedataSetStatus(saveData, 5, 0x2);
            break;
        case 2: // Europe
        case 3:
            gamedataSetStatus(saveData, 2, 0xB);
            gamedataSetStatus(saveData, 3, 0x3);
            gamedataSetStatus(saveData, 4, 0x3);
            gamedataSetStatus(saveData, 5, 0x8);
            break;
        default:
            break;
    }
    
    return 0;
}

/*
  Address: 0x8000B850 | size: 0x1E8
  dbgMenuMemcardDebugSave(s32 slot)
  Saves current save data to DVD for debug purposes.
  For regular saves: Serializes to temp buffer, writes to DVD.
  For HD saves: Copies from save data pointer, writes to DVD.
*/
s32 dbgMenuMemcardDebugSave(s32 slot) {
    const char* assertFile = "dbgMenuMemcard.c";
    
    if (_memcard_debug_type_check(slot)) {
        // Regular save
        dbgMenuSaveData = GSmemAllocAlign(0x8000, 0x20);
        memcard_debug_Save((u8*)dbgMenuSaveData + 8);
        
        s32 handle = GSdvdOpenTest(saveFileName[slot]);
        if (handle == 0) {
            handle = GSdvdCreate(saveFileName[slot]);
        } else {
            handle = GSdvdOpen(saveFileName[slot]);
        }
        
        if (handle != 0) {
            GSdvdWrite(handle, dbgMenuSaveData, 0);
            GSdvdClose(handle);
        }
        
        GSmemFree(dbgMenuSaveData);
        dbgMenuSaveData = 0;
    } else {
        // HD save
        bk_savedataPtr = memcardMemAllocForSavedata();
        if (bk_savedataPtr == 0) {
            __assert(assertFile, 0x1F5, "bk_savedataPtr & \83\81[\95\73\91\xAB\x22");
        }
        
        void* saveData = savedataGetStatus(0, 0);
        memcpy(bk_savedataPtr, saveData, 0x7FD0 - 0x20000);
        
        s32 result = memcardTaskCall(2, 2, 0);
        if (result == 3) {
            s32 handle = GSdvdOpenTest(saveFileName[slot]);
            if (handle == 0) {
                handle = GSdvdCreate(saveFileName[slot]);
            } else {
                handle = GSdvdOpen(saveFileName[slot]);
            }
            
            if (handle != 0) {
                GSdvdWrite(handle, now_savedata_ptr, 0);
                GSdvdClose(handle);
            }
        }
        
        saveData = savedataGetStatus(0, 0);
        memcpy(saveData, bk_savedataPtr, 0x7FD0 - 0x20000);
        
        s32 freeResult = memcardMemFreeForSavedata(bk_savedataPtr);
        bk_savedataPtr = (void*)freeResult;
        if (freeResult != 0) {
            __assert(assertFile, 0x216, "bk_savedataPtr & \83\81[\89\xF0\95\xFA\x8E\xB8\94\73\x22");
        }
    }
    
    return 0;
}

/*
  Address: 0x8000BA38 | size: 0x30
  dbgMenuMemcardDelete()
  Deletes save data from memory card (task 0xC).
*/
s32 dbgMenuMemcardDelete(void) {
    memcardTaskCall(0xC, 2, 0);
    return 0;
}

/*
  Address: 0x8000BA68 | size: 0x4C
  dbgMenuMemcardLoad()
  Loads save data from memory card and shows completion message.
*/
s32 dbgMenuMemcardLoad(void) {
    memcardTaskCall(2, 2, 0);
    winMsgOpen(2, 0xF2, 1, 1);
    winMsgClose(1);
    return 0;
}

/*
  Address: 0x8000BAB4 | size: 0x30
  dbgMenuMemcardSave()
  Saves current data to memory card (task 0xB).
*/
s32 dbgMenuMemcardSave(void) {
    memcardTaskCall(0xB, 2, 0);
    return 0;
}
