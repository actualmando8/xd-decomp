// Decompiled from: dbgMenuFightWaza.cpp
// Address range: 0x8000DBAC..0x8000DEE8 | size: 0x33C

void*   wazaDataBiosGetPtr(s32 wazaId);
s32     menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e);
s32     menuCloseCustom(s32 menuId, s32 a, s32 b);
s32     menuOpen(s32 menuId, s32 param);
s32     menuGetCursorItemID(s32 menuId);
s32     wazaGetStatus(s32 a, s32 wazaId, s32 b, s32 c);
s32     dbgMenuFightGetWazaTypeId(s32 type);
void    wazaSetStatus(s32 a, s32 wazaId, s32 b, s32 c, s32 value);
s32     menuSubOpenYesNo(s32 a, s32 b, s32 c);

/*
  Address: 0x8000DBAC | size: 0x33C
  dbgMenuFightWazaEditSub(s32 wazaId)
  Opens menu 0x20 for Waza editing. Handles cursor selection:
    0x89: Toggle status type 0x1A
    0x8A: Toggle status type 0x1A (second)
    0x8B: Toggle status type 0x1A (third)
    0x8C: Toggle status type 0x1B with yes/no confirmation
    0x8D: Unknown
  On cancel (-1): Saves edited data back to wazaDataBios.
  On back (-2): Opens menu 0x55 submenu.
*/
s32 dbgMenuFightWazaEditSub(s32 wazaId) {
    s32 result;
    s32 cursor;
    void* wazaData;
    s32 data[14];
    
    if (wazaId == 0 || 0x163 <= wazaId) {
        return 1;
    }
    
    wazaData = wazaDataBiosGetPtr(wazaId);
    
    // Load Waza data into local array
    data[0] = wazaData->field_0x0;
    data[1] = wazaData->field_0x4;
    data[2] = wazaData->field_0x8;
    data[3] = wazaData->field_0xC;
    data[4] = wazaData->field_0x10;
    data[5] = wazaData->field_0x14;
    data[6] = wazaData->field_0x18;
    data[7] = wazaData->field_0x1C;
    data[8] = wazaData->field_0x20;
    data[9] = wazaData->field_0x24;
    data[10] = wazaData->field_0x28;
    data[11] = wazaData->field_0x2C;
    data[12] = wazaData->field_0x30;
    data[13] = wazaData->field_0x34;
    
    while (1) {
        // Open edit menu
        s32 menuResult = menuOpenCustom(0x20, 0, 0, 0, 1, 1);
        
        if (menuResult == -1) {
            // Cancel - save data back
            menuCloseCustom(0x20, 0, 1);
            wazaData->field_0x0 = data[0];
            wazaData->field_0x4 = data[1];
            wazaData->field_0x8 = data[2];
            wazaData->field_0xC = data[3];
            wazaData->field_0x10 = data[4];
            wazaData->field_0x14 = data[5];
            wazaData->field_0x18 = data[6];
            wazaData->field_0x1C = data[7];
            wazaData->field_0x20 = data[8];
            wazaData->field_0x24 = data[9];
            wazaData->field_0x28 = data[10];
            wazaData->field_0x2C = data[11];
            wazaData->field_0x30 = data[12];
            wazaData->field_0x34 = data[13];
            break;
        }
        
        if (menuResult == -2) {
            // Back - open submenu
            s32 subResult = menuOpen(0x55, 1);
            if (subResult == 0) {
                menuCloseCustom(0x55, 0, 1);
            } else {
                menuCloseCustom(0x55, 0, 1);
                menuCloseCustom(0x20, 0, 1);
                result = 1;
                return result;
            }
            continue;
        }
        
        // Handle cursor selection
        cursor = menuGetCursorItemID(0x20);
        
        if (cursor == 0x89) {
            // Toggle status type 0x1A
            s32 status = wazaGetStatus(0, wazaId, 0x1A, 0);
            s32 typeId = dbgMenuFightGetWazaTypeId(status);
            if (typeId >= 0) {
                wazaSetStatus(0, wazaId, 0x1A, 0, typeId);
            }
        }
        else if (0x89 < cursor && cursor < 0x8D) {
            // Toggle status type 0x1B with confirmation
            s32 status = wazaGetStatus(0, wazaId, 0x1B, 0);
            s32 confirm = menuSubOpenYesNo(0x7F, -1, -1);
            if (confirm == 0) {
                wazaSetStatus(0, wazaId, 0x1B, 0, 1);
            } else if (confirm == 1) {
                wazaSetStatus(0, wazaId, 0x1B, 0, 0);
            }
        }
        else if (cursor == 0x8B) {
            // Toggle status type 0x1A (third)
            s32 status = wazaGetStatus(0, wazaId, 0x1A, 2);
            s32 typeId = dbgMenuFightGetWazaTypeId(status);
            if (typeId >= 0) {
                wazaSetStatus(0, wazaId, 0x1A, 2, typeId);
            }
        }
        else if (0x8B < cursor && cursor < 0x8D) {
            // Toggle status type 0x1A (second)
            s32 status = wazaGetStatus(0, wazaId, 0x1A, 1);
            s32 typeId = dbgMenuFightGetWazaTypeId(status);
            if (typeId >= 0) {
                wazaSetStatus(0, wazaId, 0x1A, 1, typeId);
            }
        }
    }
    
    result = 1;
    return result;
}
