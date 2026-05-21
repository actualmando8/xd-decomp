// Decompilation of menuPdaMailXD.cpp
// Original address: 0x80042CD0..0x80043304 | size: 0x634
// Functions: 10

#include "global.h"

// Forward declarations
void menuPdaSetSubres(int param1, int param2);
void menuOpen(int menuId, int param2);
int windowGetActiveID(void);
int menuOpenCustom(int menuId, int param4, int param5, int param6, int param7, int param8, int param9);
int menuScriptCheckMailOpen(void);
void windowGetKeyInfo(void);
int winSeqCheckMove(int seqId);
void menuButtonNormal(void* windowWork);
u16 pdaMailGetMailID(void* cursor);
int menuPdaMemoListGetPokemonID(int index);
void* mailGetSenderName(int mailId);
void* mailGetSubject(int mailId);
void* mailGetContents(int mailId);
void* GSmsgGetGSchar(void* msg);
void msgctrlSetValue(int ctrlId, void* value);
void menuClose(int menuId);
void menuCloseSync(int menuId, int sync);
void GSsndPlayNow(int soundId);
int mailGetNbMailInMailbox(void);
int windowGetKeyRepeat(void);
void* mailGetAttachFileGroup(int mailId);
void menuPlaySe(int seqId, int seId);

// Global variable
static s16 _cursor[2];

/* 0x80042CD0 | size: 0x5C */
// Callback for mail content display based on sprite ID
// r3 = windowWork, r4 = spriteWork
void menuPdaMailCallBack(void* windowWork, void* spriteWork)
{
    s16 spriteId = *(s16*)((u32)spriteWork + 0x6);
    
    if (spriteId == 0xaa) {
        _mailHonbun(windowWork, spriteWork);
    } else if (spriteId == 0xab) {
        _mailSender(windowWork, spriteWork);
    } else if (spriteId >= 0xac && spriteId < 0xad) {
        _mailSubject(windowWork, spriteWork);
    }
}

/* 0x80042D2C | size: 0xB8 */
// Script-based mail menu with cursor tracking
// r3 = cursor (s16)
void menuPdaMailXDScript(s16 cursor)
{
    _cursor[0] = cursor;
    _cursor[1] = 0x2;
    
    menuPdaSetSubres(0x2, 0x2);
    menuOpen(0x77, 0x0);
    
    while (1) {
        int activeId = windowGetActiveID();
        int result = menuOpenCustom(0x6f, activeId, 0x0, 0x0, 0x1, 0x1, 0);
        if (menuScriptCheckMailOpen()) {
            break;
        }
        if (result != -1) {
            break;
        }
    }
    
    _menuClose(0x6f);
    _menuClose(0x77);
}

/* 0x80042DE4 | size: 0x90 */
// Main mail menu entry point
// r3 = cursor, r4 = param2, r5 = param3
void* menuPdaMailXD(s16* cursor, int param2, int param3)
{
    _cursor[0] = cursor[0];
    _cursor[1] = cursor[1];
    
    while (1) {
        int activeId = windowGetActiveID();
        int result = menuOpenCustom(0x6f, activeId, 0x0, 0x0, 0x1, 0x1, 0);
        if (result == -1) {
            break;
        }
    }
    
    _menuClose(0x6f);
    return (void*)_cursor;
}

/* 0x80042E74 | size: 0xB4 */
// Button handler for mail contents
// r3 = windowWork
void menuPdaMailContentsButtonXD(void* windowWork)
{
    void* keyInfo = windowGetKeyInfo();
    int* ptr = (int*)((u32)windowWork + 0x68);
    int* cursor = (int*)((u32)*ptr + 0x8);
    s16 cursorX = *(s16*)((u32)*cursor + 0x0);
    s16 cursorY = *(s16*)((u32)*cursor + 0x2);
    s16 total = cursorX + cursorY;
    
    if (!total) {
        menuButtonNormal(windowWork);
        return;
    }
    
    int seqId = *(int*)((u32)windowWork + 0x4);
    if (winSeqCheckMove(seqId)) {
        return;
    }
    
    int mailId = pdaMailGetMailID((void*)total);
    if (!menuScriptCheckMailOpen()) {
        if (!mailGetAttachFileGroup(mailId)) {
            u16 flag = *(u16*)((u32)keyInfo + 0x0);
            if (!(flag & 0x8000)) {
                menuButtonNormal(windowWork);
            }
        }
    }
}

/* 0x80042F28 | size: 0x190 */
// Cursor movement handler for mail contents
// r3 = windowWork
void menuPdaMailContentsCursorXD(void* windowWork)
{
    int* ptr = (int*)((u32)windowWork + 0x68);
    int* cursor = (int*)((u32)*ptr + 0x8);
    u8 state = *(u8*)((u32)*ptr + 0x0);
    
    if (!state) {
        return;
    }
    
    int nbMail = mailGetNbMailInMailbox();
    s16 cursorX = *(s16*)((u32)*cursor + 0x0);
    s16 cursorY = *(s16*)((u32)*cursor + 0x2);
    s16 maxVisible = 0x5;
    if (nbMail < maxVisible) {
        maxVisible = nbMail;
    }
    
    int keyRepeat = windowGetKeyRepeat();
    int direction = keyRepeat & 0x8000;
    
    if (direction < 0) {
        // Up
        s16 newCursorY = cursorY - 1;
        if (cursorX + newCursorY > 0) {
            GSsndPlayNow(0x450);
        }
        cursorY = newCursorY;
    } else if (direction & 0x4000) {
        // Down
        s16 newCursorY = cursorY + 1;
        if (cursorX + newCursorY < nbMail - maxVisible) {
            GSsndPlayNow(0x450);
        }
        cursorY = newCursorY;
    }
    
    // Clamp cursor values
    if (cursorY < 0) {
        cursorX = cursorX + cursorY;
        cursorY = 0;
        if (cursorX < 0) {
            cursorX = 0;
            cursorY = 0;
        }
    } else if (cursorY >= maxVisible) {
        int overflow = cursorY - (maxVisible - 1);
        cursorX = cursorX + overflow;
        cursorY = maxVisible - 1;
        if (cursorX + cursorY >= nbMail) {
            cursorY = nbMail - cursorX - 1;
        }
    }
    
    *(s16*)((u32)*cursor + 0x0) = cursorX;
    *(s16*)((u32)*cursor + 0x2) = cursorY;
    
    if (cursorX + cursorY != *(s16*)((u32)windowWork + 0x68)) {
        menuPlaySe(*(int*)((u32)windowWork + 0x4), 0x1);
    }
}

/* 0x800430B8 | size: 0xB0 */
// Main control for mail menu
// r3 = windowWork
void menuPdaMailCtrlXD(void* windowWork)
{
    s8 state = *(s8*)((u32)windowWork + 0x1);
    u8 flag = *(u8*)((u32)windowWork + 0x2);
    int seqId = *(int*)((u32)windowWork + 0x4);
    
    if (state == 0x0) {
        if (!flag) {
            winSeqSetMenu(seqId, 0x132);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
    } else if (state == 0x1) {
        menuScriptCheckMailOpen();
    } else if (state >= 0x2 && state < 0x4) {
        if (!flag) {
            winSeqSetMenu(seqId, 0x136);
            *(u8*)((u32)windowWork + 0x2) = 0x1;
        }
    }
}

/* 0x80043168 | size: 0x88 */
// Displays sender name in mail
// r3 = windowWork, r4 = spriteWork
void _mailSender(void* windowWork, void* spriteWork)
{
    int* ptr = (int*)((u32)windowWork + 0x68);
    int* cursor = (int*)((u32)*ptr + 0x8);
    s16 cursorX = *(s16*)((u32)*cursor + 0x0);
    s16 cursorY = *(s16*)((u32)*cursor + 0x2);
    int mailId = pdaMailGetMailID((void*)(cursorX + cursorY));
    
    void* senderName = mailGetSenderName(mailId);
    if (senderName) {
        void* gschar = GSmsgGetGSchar(senderName);
        msgctrlSetValue(0x37, gschar);
        *(u32*)((u32)spriteWork + 0x4c) = 0x4276;
    } else {
        *(u32*)((u32)spriteWork + 0x4c) = 0x0;
    }
    
    *(u8*)((u32)spriteWork + 0x64) = 0xf0;
    *(u8*)((u32)spriteWork + 0x65) = 0x0;
    *(u8*)((u32)spriteWork + 0x66) = 0x0;
}

/* 0x800431F0 | size: 0x90 */
// Displays subject in mail
// r3 = windowWork, r4 = spriteWork
void _mailSubject(void* windowWork, void* spriteWork)
{
    int* ptr = (int*)((u32)windowWork + 0x68);
    int* cursor = (int*)((u32)*ptr + 0x8);
    s16 cursorX = *(s16*)((u32)*cursor + 0x0);
    s16 cursorY = *(s16*)((u32)*cursor + 0x2);
    int mailId = pdaMailGetMailID((void*)(cursorX + cursorY));
    
    void* subject = mailGetSubject(mailId);
    if (subject) {
        void* gschar = GSmsgGetGSchar(subject);
        msgctrlSetValue(0x37, gschar);
        *(u32*)((u32)spriteWork + 0x4c) = 0x4276;
    } else {
        *(u32*)((u32)spriteWork + 0x4c) = 0x0;
    }
    
    *(u8*)((u32)spriteWork + 0x64) = 0xd5;
    *(u8*)((u32)spriteWork + 0x65) = 0xaa;
    *(u8*)((u32)spriteWork + 0x66) = 0x33;
}

/* 0x80043280 | size: 0x4C */
// Displays mail contents
// r3 = windowWork, r4 = spriteWork
void _mailHonbun(void* windowWork, void* spriteWork)
{
    int* ptr = (int*)((u32)windowWork + 0x68);
    int* cursor = (int*)((u32)*ptr + 0x8);
    s16 cursorX = *(s16*)((u32)*cursor + 0x0);
    s16 cursorY = *(s16*)((u32)*cursor + 0x2);
    int mailId = pdaMailGetMailID((void*)(cursorX + cursorY));
    
    *(u32*)((u32)spriteWork + 0x4c) = (u32)mailGetContents(mailId);
}

/* 0x800432CC | size: 0x38 */
// Helper function to close menu with sync
// r3 = menuId
void _menuClose(int menuId)
{
    menuClose(menuId);
    menuCloseSync(menuId, 0x1);
}
