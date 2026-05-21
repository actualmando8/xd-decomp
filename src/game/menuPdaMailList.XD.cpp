// Decompiled from: menuPdaMailList.XD.cpp
// Address range: 0x80043304..0x8004429C | size: 0xF98
// Functions: 30 | Data objects: 6

/*
  PDA Mail List menu for XD version.
  Handles mail list display, cursor navigation, and mail selection.
*/

#include "global.h"
#include <dolphin/types.h>

// Forward declarations
struct tagWINDOW_WORK;
struct tagSPRITE_WORK;
struct CURSOR {
    s16 field_0;
    s16 field_2;
};

// External function declarations
u32 mailGetNbMailInMailbox();
u32 mailGetMailIDInMailbox(u32 index);
u32 mailGetSortMode();
u32 mailGetSenderName(u32 mailId);
u32 mailGetSubject(u32 mailId);
void* GSmemAlloc(u32 size);
void GSmemFree(void* ptr);
void windowGetKeyInfo();
void windowGetKeyRepeat();
u32 windowGetActiveID();
void menuOpen(u32 menuId, u32 param2);
void menuClose(long menuId);
void menuCloseSync(long menuId, u32 param2);
void* menuItemBiosGetPtr(u32 type, u32 id);
void GSsndPlayNow(u32 soundId);
void* GSmsgGetGSchar(u32 msgId);
void* GSmsgGetRect(u32 msgId);
void msgctrlSetValue(u32 ctrlId, void* value);
void GSmsgPrint2(u32 layerId, u32 x, u32 y, u32 color, u32 param5, u32 msgId, u32 param7);
void spriteSetScissor(u32 layerId, s16 x, s16 y, s16 w, s16 h);
void spriteClearScissor(u32 layerId);
void winSeqCheckMove(tagWINDOW_WORK* work);
void winSeqSetMenu(tagWINDOW_WORK* work, u32 menuId);
void winSpriteSetDisp(tagSPRITE_WORK* spr, u32 disp);
void cursorBiosSetPos(u32 cursorId, u32 pos);
u32 cursorBiosGetPos(u32 cursorId);
void menuPdaSubCheckUpDownCursor(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, CURSOR* cursor, u32 maxItems, u32 param5, u32 isUp, u32 param7);
void menuPdaSubScrollBar(tagWINDOW_WORK* win, tagSPRITE_WORK* spr, u32 y, u32 h, u32 total, u32 cursor, u32 maxItems);
void menuPdaSubInitAlpha(float* alpha, u32 count, u32 param3);
void menuPdaSubCalcAlpha(float* alpha, u32 count, u32 param3);
void menuPdaMailXD(tagWINDOW_WORK* win, u32 param2, u32 param3);
void menuPdaMailListXD();

// Global data
static u16* _sortwork;
static struct {
    CURSOR cursor;
    float pos[5];
    float targetPos;
    u32 maxItems;
} _maillistwork;
static float _menuPdaMailAlpha[5];
static u32 gap_06_802EAA6C_rodata = 0;

// Jump table for callback dispatch
static const void* const callback_jump_table[] = {
    (void*)0x800436FC,  // 0x81: _pdaMailListCursor
    (void*)0x800436FC,  // 0x82: _pdaMailListCursor
    (void*)0x800436FC,  // 0x83: _pdaMailListCursor
    (void*)0x800436FC,  // 0x84: _pdaMailListCursor
    (void*)0x800436FC,  // 0x85: _pdaMailListCursor
    (void*)0x80043710,  // 0x86: NOP
    (void*)0x80043710,  // 0x87: NOP
    (void*)0x80043710,  // 0x88: NOP
    (void*)0x80043710,  // 0x89: NOP
    (void*)0x80043710,  // 0x8a: NOP
    (void*)0x80043704,  // 0x8b: _pdaMailListUpCursor
    (void*)0x8004370C,  // 0x8c: _pdaMailListDownCursor
    (void*)0x800436A4,  // 0x8d: _pdaMailListScrollBar
    (void*)0x80043710,  // 0x8e: NOP
    (void*)0x80043710,  // 0x8f: NOP
    (void*)0x80043710,  // 0x90: NOP
    (void*)0x80043710,  // 0x91: NOP
    (void*)0x80043710,  // 0x92: NOP
    (void*)0x80043710,  // 0x93: NOP
    (void*)0x80043710,  // 0x94: NOP
    (void*)0x800436C4,  // 0x95: _pdaMailListDraw
    (void*)0x800436CC,  // 0x96: Set alpha 0xF0
    (void*)0x800436E0,  // 0x97: Set color
    (void*)0x800436BC,  // 0x98: _pdaMailListPage
    (void*)0x800436B4,  // 0x99: _pdaMailListPageBunbo
    (void*)0x800436AC,  // 0x9a: _pdaMailListPageBunshi
};

// Item ID table for cursor positions
static const u32 item_id_table[] = {0x81, 0x82, 0x83, 0x84, 0x85};

/*
  Address: 0x80043304 | size: 0x38
  Exits the sort work area.
*/
void menuPdaMailListSortExit() {
    if (_sortwork != NULL) {
        GSmemFree(_sortwork);
        _sortwork = NULL;
    }
}

/*
  Address: 0x8004333C | size: 0x9C
  Initializes the sort work area and finds matching mail.
*/
s32 menuPdaMailListSortInit(u32 mailId) {
    u32 nbMail = mailGetNbMailInMailbox();
    if (nbMail > 0) {
        _sortwork = (u16*)GSmemAlloc(nbMail * 2);
    } else {
        _sortwork = NULL;
    }
    
    if (_sortwork == NULL) {
        return -1;
    }
    
    _pdaMailSort();
    
    for (u32 i = 0; i < nbMail; i++) {
        if (_sortwork[i] == mailId) {
            return i;
        }
    }
    return -1;
}

/*
  Address: 0x800433D8 | size: 0x90
  Button handler for mail list.
*/
void menuPdaMailListButtonXD(tagWINDOW_WORK* work) {
    if (work == NULL) {
        return;
    }
    
    u32 nbMail = mailGetNbMailInMailbox();
    if (winSeqCheckMove(work) & 0xFF000000) {
        return;
    }
    
    windowGetKeyInfo();
    if (nbMail == 0) {
        return;
    }
    
    u16 keys = work->keyInfo >> 16;
    // Check A button (bit 27)
    if (keys & 0x8000000) {
        work->field_a4 = 1;
        return;
    }
    // Check B button (bit 26)
    if (keys & 0x4000000) {
        work->field_a4 = 1;
        work->field_a5 = 1;
    }
}

/*
  Address: 0x80043468 | size: 0x208
  Cursor handler for mail list.
*/
void menuPdaMailListCursorXD(tagWINDOW_WORK* work) {
    windowGetKeyInfo();
    CURSOR cursor = _getCursor();
    s16 base = cursor.field_0;
    s16 offset = cursor.field_2;
    
    u32 nbMail = mailGetNbMailInMailbox();
    u32 maxVisible = 5;
    if (nbMail < 5) {
        maxVisible = nbMail;
    }
    
    windowGetKeyRepeat();
    if (maxVisible == 0) {
        goto done;
    }
    
    s32 dir = work->keyInfo >> 16;
    
    if (dir < 0) {
        // Move up
        if (offset != 0) {
            GSsndPlayNow(0x450);
        }
        offset--;
    } else if (dir > 0) {
        // Move down
        if (offset + base >= (s16)(nbMail - 1)) {
            // At bottom
        } else {
            GSsndPlayNow(0x450);
        }
        offset++;
    } else if ((dir >> 28) & 1) {
        // Page up
        offset -= maxVisible;
    } else if ((dir >> 29) & 1) {
        // Page down
        offset += maxVisible;
    }
    
    // Wrap cursor within bounds
    if (offset < 0) {
        base += offset;
        offset = 0;
        if (base < 0) {
            base = 0;
            offset = 0;
        }
    } else if (offset >= (s16)maxVisible) {
        base += offset - maxVisible + 1;
        offset = maxVisible - 1;
    }
    
done:
    _setCursor(CURSOR{base, offset});
    work->field_9c = base;
    work->field_9e = offset;
}

/*
  Address: 0x80043670 | size: 0xB4
  Callback dispatcher for mail list items.
*/
void menuPdaMailListCallBack(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u8 itemId = spr->field_6 - 0x81;
    if (itemId > 0x1a) {
        return;
    }
    
    void (*func)() = (void (*)())callback_jump_table[itemId];
    func();
}

/*
  Address: 0x80043724 | size: 0x60
  Moves cursor down.
*/
void _pdaMailListDownCursor(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    CURSOR cursor = _getCursor();
    u32 nbMail = mailGetNbMailInMailbox();
    menuPdaSubCheckUpDownCursor(work, spr, &cursor, nbMail, 5, 0, 0);
}

/*
  Address: 0x80043784 | size: 0x60
  Moves cursor up.
*/
void _pdaMailListUpCursor(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    CURSOR cursor = _getCursor();
    u32 nbMail = mailGetNbMailInMailbox();
    menuPdaSubCheckUpDownCursor(work, spr, &cursor, nbMail, 5, 1, 0);
}

/*
  Address: 0x800437E4 | size: 0x104
  Sets cursor highlight based on item ID.
*/
void _pdaMailListCursor(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u32 nbMail = mailGetNbMailInMailbox();
    s16 cursorPos = work->field_9e;
    
    u32 itemId = spr->field_6;
    u32 index = 5;
    for (u32 i = 0; i < 5; i++) {
        if (itemId == item_id_table[i]) {
            index = i;
            break;
        }
    }
    
    float alpha = _menuPdaMailAlpha[index];
    spr->field_67 = (u8)alpha;
    
    if (cursorPos == (s16)index) {
        winSpriteSetDisp(spr, 1);
    } else {
        if (alpha != 1.0f) {
            winSpriteSetDisp(spr, 0);
        }
    }
}

/*
  Address: 0x800438E8 | size: 0x74
  Draws scroll bar.
*/
void _pdaMailListScrollBar(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u32 nbMail = mailGetNbMailInMailbox();
    CURSOR cursor = _getCursor();
    menuPdaSubScrollBar(work, spr, 0x6e, 0x8d, nbMail, cursor.field_0, 5);
}

/*
  Address: 0x8004395C | size: 0xAC
  Control/state machine for mail list.
*/
u32 menuPdaMailListCtrlXD(tagWINDOW_WORK* work) {
    s8 state = work->field_1;
    
    if (state == 2) {
        _menuPdaMailListMain(work);
        return 0;
    }
    
    if (state >= 0) {
        if (state == 0) {
            if (work->field_2 == 0) {
                winSeqSetMenu(work, 0x132);
                work->field_2 = 1;
            }
            return 0;
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
    return 0;
}

/*
  Address: 0x80043A08 | size: 0xC0
  Sub-menu for mail selection.
*/
s32 menuPdaMailListSubXD(CURSOR* outCursor) {
    CURSOR cursor;
    cursor.field_0 = outCursor->field_0;
    cursor.field_2 = outCursor->field_2;
    
    while (1) {
        s32 result = menuOpen(0x6e, 1);
        CURSOR current = _getCursor();
        
        if (result == -1) {
            break;
        }
        if (current.field_2 >= 5) {
            continue;
        }
        break;
    }
    
    _menuClose(0x6e);
    
    if (result == -1) {
        u32 nbMail = mailGetNbMailInMailbox();
        if (nbMail == 0) {
            return -1;
        }
    }
    
    outCursor->field_2 = cursor.field_2;
    outCursor->field_0 = cursor.field_0;
    return cursor.field_0 + cursor.field_2;
}

/*
  Address: 0x80043AC8 | size: 0x114
  Main entry point for mail list.
*/
void menuPdaMailListXD() {
    u32 nbMail = mailGetNbMailInMailbox();
    s32 selectedMail = 0;
    
    if (nbMail > 0) {
        _sortwork = (u16*)GSmemAlloc(nbMail * 2);
    } else {
        _sortwork = NULL;
    }
    
    _menuPdaMailListXDInit();
    _pdaMailSort();
    
    CURSOR cursor = {0, 0};
    menuOpen(0x77, 0);
    
    while (1) {
        selectedMail = menuPdaMailListSubXD(&cursor);
        if (selectedMail < 0) {
            break;
        }
        
        menuPdaMailXD(&cursor, 1, 0);
        cursor.field_2 = 5;
        menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, 0);
        _menuPdaMailListCalcPosition(&cursor);
        _maillistwork.targetPos = _maillistwork.pos[0];
    }
    
    _menuClose(0x77);
    
    if (nbMail > 0 && _sortwork != NULL) {
        GSmemFree(_sortwork);
        _sortwork = NULL;
    }
}

/*
  Address: 0x80043BDC | size: 0x78
  Initializes mail list state.
*/
void _menuPdaMailListXDInit() {
    u32 nbMail = mailGetNbMailInMailbox();
    
    _maillistwork.cursor.field_0 = 0;
    _maillistwork.cursor.field_2 = 0;
    for (u32 i = 0; i < 5; i++) {
        _maillistwork.pos[i] = 1.0f;
    }
    _maillistwork.maxItems = nbMail < 5 ? nbMail : 5;
    
    menuPdaSubInitAlpha(_menuPdaMailAlpha, 5, 0);
}

/*
  Address: 0x80043C54 | size: 0x44
  Main loop for mail list.
*/
void _menuPdaMailListMain(tagWINDOW_WORK* work) {
    CURSOR cursor = _getCursor();
    _menuPdaMailListPosition();
    _menuPdaMailListCalcPosition(&cursor);
    menuPdaSubCalcAlpha(_menuPdaMailAlpha, 5, work->field_a);
}

/*
  Address: 0x80043C98 | size: 0x40
  Calculates position based on cursor.
*/
void _menuPdaMailListCalcPosition(CURSOR* cursor) {
    s16 base = cursor->field_0;
    // Fixed-point arithmetic for position calculation
    u32 pos = 0x43300000 - (u32)(-base) * 0x2f;
    pos ^= 0x80000000;
    _maillistwork.targetPos = (float)(0x43300000 - pos);
}

/*
  Address: 0x80043CD8 | size: 0x64
  Updates mail list position.
*/
void _menuPdaMailListPosition() {
    if (_maillistwork.pos[0] != _maillistwork.pos[2]) {
        _menuPdaMailCalc(&_maillistwork.pos[0], _maillistwork.pos[2], 0.1f);
    }
    if (_maillistwork.pos[1] != _maillistwork.pos[3]) {
        _menuPdaMailCalc(&_maillistwork.pos[1], _maillistwork.pos[3], 0.1f);
    }
}

/*
  Address: 0x80043D3C | size: 0x20
  Calculates position with smoothing.
*/
void _menuPdaMailCalc(float* current, float target, float speed) {
    menuPdaSubCalcPositon(current, target, speed);
}

/*
  Address: 0x80043D5C | size: 0x210
  Draws mail list items.
*/
void _pdaMailListDraw(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    CURSOR cursor = _getCursor();
    u32 nbMail = mailGetNbMailInMailbox();
    u8 alpha = work->field_93;
    
    u32 color1 = (alpha << 24) | (0xD5 << 16) | (0xAA << 8) | 0x33;
    u32 color2 = (alpha << 24) | (0xF0 << 16) | (0xF0 << 8) | 0xF0;
    
    void* bios1 = menuItemBiosGetPtr(0x6e, 0x70);
    void* bios2 = menuItemBiosGetPtr(0x6e, spr->field_6);
    
    spriteSetScissor(work->field_1c,
        ((s16*)bios2)[3] - ((s16*)bios1)[3],
        ((s16*)bios2)[4] - ((s16*)bios1)[4],
        ((s16*)bios1)[5],
        ((s16*)bios1)[6]);
    
    s32 startMail = cursor.field_0 - 1;
    s32 endMail = cursor.field_0 + 6;
    s32 i = 0;
    
    for (s32 mailIdx = startMail; mailIdx < (s32)nbMail; mailIdx++) {
        if (mailIdx < 0 || mailIdx >= endMail) {
            i++;
            continue;
        }
        
        // Draw subject
        u32 subject = _getSubject(mailIdx);
        if (subject != 0) {
            void* subjectStr = GSmsgGetGSchar(subject);
            msgctrlSetValue(0x37, subjectStr);
            GSmsgPrint2(work->field_1c, 0, 0, color1 | (alpha << 8), 0, 0x4276, 0);
        } else {
            GSmsgPrint2(work->field_1c, 0, 0, color1 | (alpha << 8), 0, 0, 0);
        }
        
        // Draw sender name
        u32 sender = _getSenderName(mailIdx);
        if (sender != 0) {
            void* senderStr = GSmsgGetGSchar(sender);
            msgctrlSetValue(0x37, senderStr);
            GSmsgPrint2(work->field_1c, 0, 0, color2 | (alpha << 8), 0, 0x4276, 0);
        } else {
            GSmsgPrint2(work->field_1c, 0, 0, color2 | (alpha << 8), 0, 0, 0);
        }
        
        i++;
    }
    
    spriteClearScissor(work->field_1c);
}

/*
  Address: 0x80043F6C | size: 0x80
  Draws mail count (bottom).
*/
void _pdaMailListPageBunbo(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u32 nbMail = mailGetNbMailInMailbox();
    if (nbMail == 0) {
        return;
    }
    
    msgctrlSetValue(0x34, nbMail);
    void* rect = GSmsgGetRect(0x426f);
    s16 y = spr->field_54 - ((u32)rect >> 16);
    GSmsgPrint2(work->field_1c, 0, y, work->field_93 | 0xFF00, 0, 0x426f, 0);
}

/*
  Address: 0x80043FEC | size: 0x8C
  Draws mail count (top).
*/
void _pdaMailListPageBunshi(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u32 nbMail = mailGetNbMailInMailbox();
    if (nbMail == 0) {
        return;
    }
    
    msgctrlSetValue(0x34, work->field_9c + work->field_9e + 1);
    void* rect = GSmsgGetRect(0x426f);
    s16 y = spr->field_54 - ((u32)rect >> 16);
    GSmsgPrint2(work->field_1c, 0, y, work->field_93 | 0xFF00, 0, 0x426f, 0);
}

/*
  Address: 0x80044078 | size: 0x50
  Shows/hides page indicator.
*/
void _pdaMailListPage(tagWINDOW_WORK* work, tagSPRITE_WORK* spr) {
    u32 nbMail = mailGetNbMailInMailbox();
    if (nbMail != 0) {
        winSpriteSetDisp(spr, 1);
    } else {
        winSpriteSetDisp(spr, 0);
    }
}

/*
  Address: 0x800440C8 | size: 0x38
  Closes menu with sync.
*/
void _menuClose(long menuId) {
    menuClose(menuId);
    menuCloseSync(menuId, 1);
}

/*
  Address: 0x80044100 | size: 0x5C
  Receives mail IDs into sort work area.
*/
void _sortReceive(u16* out) {
    u32 nbMail = mailGetNbMailInMailbox();
    for (s32 i = nbMail - 1; i >= 0; i--) {
        u32 mailId = mailGetMailIDInMailbox(i);
        *out++ = (u16)mailId;
    }
}

/*
  Address: 0x8004415C | size: 0x34
  Sorts mail list.
*/
void _pdaMailSort() {
    u16* work = _sortwork;
    u32 sortMode = mailGetSortMode();
    _sortReceive(work);
}

/*
  Address: 0x80044190 | size: 0x30
  Sets cursor position.
*/
void _setCursor(CURSOR cursor) {
    cursorBiosSetPos(0xa, cursor.field_0);
}

/*
  Address: 0x800441C0 | size: 0x24
  Gets cursor position.
*/
CURSOR _getCursor() {
    return (CURSOR){cursorBiosGetPos(0xa), 0};
}

/*
  Address: 0x800441E4 | size: 0x24
  Gets sender name for mail.
*/
u32 _getSenderName(long mailIdx) {
    u32 mailId = _getMailID(mailIdx);
    return mailGetSenderName(mailId);
}

/*
  Address: 0x80044208 | size: 0x24
  Gets subject for mail.
*/
u32 _getSubject(long mailIdx) {
    u32 mailId = _getMailID(mailIdx);
    return mailGetSubject(mailId);
}

/*
  Address: 0x8004422C | size: 0x20
  Gets mail ID for index.
*/
u32 _getMailID(long mailIdx) {
    return pdaMailGetMailID(mailIdx);
}

/*
  Address: 0x8004424C | size: 0x50
  Gets mail ID from sorted list.
*/
u32 pdaMailGetMailID(s32 index) {
    if (index < 0) {
        return -1;
    }
    
    u32 nbMail = mailGetNbMailInMailbox();
    if (index >= (s32)nbMail) {
        return -1;
    }
    
    if (_sortwork != NULL) {
        return _sortwork[index * 2];
    }
    return 0;
}
