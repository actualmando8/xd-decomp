// Decompiled from: menuPdaMailXD.cpp
// Address range: 0x80042CD0..0x80043304 | size: 0x634

/* Forward declarations */
void    menuPdaSetSubres(s32 a, s32 b);
s32     menuOpen(s32 menuId, s32 param);
s32     windowGetActiveID(void);
s32     menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32* e);
s32     menuScriptCheckMailOpen(void);
void    menuButtonNormal(void* winWork);
void*   windowGetKeyInfo(void);
s32     winSeqCheckMove(void* winWork, s32 seq);
s32     pdaMailGetMailID(s32 cursor);
s32     menuPlaySe(void* winWork, s32 seId);
void    winSeqSetMenu(void* winWork, s32 seq);
s32     mailGetNbMailInMailbox(void);
s32     windowGetKeyRepeat(void);
void    GSsndPlayNow(s32 sndId);
s32     mailGetAttachFileGroup(s32 mailId);
void*   mailGetSenderName(s32 mailId);
void*   mailGetSubject(s32 mailId);
void*   mailGetContents(s32 mailId);
void*   GSmsgGetGSchar(void* str);
void    msgctrlSetValue(s32 ctrlId, void* value);
void    menuClose(s32 menuId);
void    menuCloseSync(s32 menuId, s32 sync);

/* Global state */
static s16 _cursor[2];

/*
  Address: 0x80042CD0 | size: 0x5C
  menuPdaMailCallBack(void* winWork, void* spriteWork)
  Callback for mail display. Dispatches based on sprite type (0xAA-0xAD).
*/
s32 menuPdaMailCallBack(void* winWork, void* spriteWork) {
    s16 spriteType = ((s16*)spriteWork)[3];
    
    switch (spriteType) {
        case 0xAA: // Mail contents
            _mailHonbun__FP14tagWINDOW_WORKP14tagSPRITE_WORK(winWork, spriteWork);
            break;
        case 0xAB: // Sender
            _mailSender__FP14tagWINDOW_WORKP14tagSPRITE_WORK(winWork, spriteWork);
            break;
        case 0xAC:
            _mailHonbun__FP14tagWINDOW_WORKP14tagSPRITE_WORK(winWork, spriteWork);
            break;
        case 0xAD: // Subject
            _mailSubject__FP14tagWINDOW_WORKP14tagSPRITE_WORK(winWork, spriteWork);
            break;
        default:
            break;
    }
    
    return 0;
}

/*
  Address: 0x80042D2C | size: 0xB8
  menuPdaMailXDScript(s16 cursor, s32 a, s32 b)
  Script handler for mail menu. Opens mail viewer and waits for completion.
*/
void menuPdaMailXDScript(s16 cursor, s32 a, s32 b) {
    _cursor[0] = cursor;
    _cursor[1] = 0;
    
    menuPdaSetSubres(2, 2);
    menuOpen(0x77, 0);
    
    while (1) {
        s32 result = menuOpenCustom(0x6F, 0, 0, 1, 1, 0);
        if (menuScriptCheckMailOpen() != 0) break;
        if (result == -1) break;
    }
    
    _menuClose__Fl(0x6F);
    _menuClose__Fl(0x77);
}

/*
  Address: 0x80042DE4 | size: 0x90
  menuPdaMailXD(void* winWork, s32 a, s32 b)
  Main mail viewer entry point.
*/
void menuPdaMailXD(void* winWork, s32 a, s32 b) {
    _cursor[1] = ((s16*)winWork)[1];
    _cursor[0] = ((s16*)winWork)[0];
    
    if (a == 0) {
        // Store param
    }
    
    while (1) {
        s32 result = menuOpenCustom(0x6F, 0, 0, 1, 1, 0);
        if (result == -1) break;
    }
    
    _menuClose__Fl(0x6F);
    _cursor[0] = 0;
}

/*
  Address: 0x80042E74 | size: 0xB4
  menuPdaMailContentsButtonXD(void* winWork)
  Handles button press on mail contents. Opens mail if conditions met.
*/
void menuPdaMailContentsButtonXD(void* winWork) {
    void* keyInfo = windowGetKeyInfo();
    void* data = ((void**)winWork)[0x68 / 4];
    
    if (winWork == 0) {
        data = ((void**)data)[0x8 / 4];
        s32 cursor = ((s16*)data)[1] + ((s16*)data)[0];
        
        if (cursor == 0) {
            menuButtonNormal(winWork);
            return;
        }
        
        if (winSeqCheckMove(winWork, 0) != 0) {
            return;
        }
        
        s32 mailId = pdaMailGetMailID(cursor);
        if (menuScriptCheckMailOpen() != 0) {
            menuButtonNormal(winWork);
            return;
        }
        
        if (mailGetAttachFileGroup(mailId) != 0) {
            menuButtonNormal(winWork);
            return;
        }
        
        // Check bit 5 of flags
        u16 flags = ((u16*)keyInfo)[0];
        if ((flags >> 5) & 0x1) {
            return;
        }
        
        menuButtonNormal(winWork);
    }
}

/*
  Address: 0x80042F28 | size: 0x190
  menuPdaMailContentsCursorXD(void* winWork)
  Handles cursor movement in mail list. Manages scrolling with sound effects.
*/
s32 menuPdaMailContentsCursorXD(void* winWork) {
    void* data = ((void**)winWork)[0x68 / 4];
    void* keyInfo = windowGetKeyInfo();
    void* cursorData = ((void**)data)[0x8 / 4];
    u8 mode = ((u8*)data)[0];
    
    if (mode != 0) {
        return 0;
    }
    
    s32 totalMails = mailGetNbMailInMailbox();
    s16 cursorY = ((s16*)cursorData)[1];
    s16 cursorX = ((s16*)cursorData)[0];
    s32 maxVisible = 5;
    s32 combined = cursorY + cursorX;
    s32 keyRepeat = windowGetKeyRepeat();
    
    if (totalMails < maxVisible) {
        maxVisible = totalMails;
    }
    
    // Check for negative movement (up)
    if (keyRepeat < 0) {
        s32 newCursor = cursorY + cursorX;
        if (newCursor != 0) {
            GSsndPlayNow(0x450);
        }
        cursorY--;
    } else {
        // Check for positive movement (down)
        if ((keyRepeat >> 30) & 0x1) {
            s32 newCursor = cursorY + cursorX;
            if (totalMails - 1 != newCursor) {
                GSsndPlayNow(0x450);
            }
            cursorY++;
        }
    }
    
    // Clamp cursorY
    if (cursorY < 0) {
        cursorX += cursorY;
        cursorY = 0;
        if (cursorX < 0) {
            cursorX = 0;
            cursorY = 0;
        }
    } else {
        s32 total = cursorX + cursorY;
        if (cursorY >= maxVisible) {
            s32 overflow = cursorY - (maxVisible - 1);
            cursorX += overflow;
            cursorY = maxVisible - 1;
            s32 newTotal = cursorX + cursorY;
            if (newTotal >= totalMails) {
                cursorY = ((s8)(totalMails - maxVisible));
                cursorX = totalMails - maxVisible;
            }
        }
    }
    
    ((s16*)cursorData)[1] = cursorY;
    ((s16*)cursorData)[0] = cursorX;
    
    s32 finalCursor = cursorY + cursorX;
    if (combined != finalCursor) {
        menuPlaySe(winWork, 1);
    }
    
    return 0;
}

/*
  Address: 0x800430B8 | size: 0xB0
  menuPdaMailCtrlXD(void* winWork)
  Controls mail menu state machine based on mode byte.
*/
s32 menuPdaMailCtrlXD(void* winWork) {
    s8 mode = ((s8*)winWork)[1];
    
    switch (mode) {
        case 0: {
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x132);
                ((s8*)winWork)[2] = 1;
            }
            break;
        }
        case 1:
            menuScriptCheckMailOpen();
            break;
        case 3: {
            if (((s8*)winWork)[2] == 0) {
                winSeqSetMenu(winWork, 0x136);
                ((s8*)winWork)[2] = 1;
            }
            break;
        }
        default:
            break;
    }
    
    return 0;
}

/*
  Address: 0x80043168 | size: 0x88
  _mailSender__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork)
  Displays sender name for current mail.
*/
void _mailSender__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork) {
    void* data = ((void**)winWork)[0x68 / 4];
    void* cursorData = ((void**)data)[0x8 / 4];
    s32 cursor = ((s16*)cursorData)[1] + ((s16*)cursorData)[0];
    
    s32 mailId = pdaMailGetMailID(cursor);
    void* name = mailGetSenderName(mailId);
    
    if (name != 0) {
        void* gsChar = GSmsgGetGSchar(name);
        msgctrlSetValue(0x37, gsChar);
        ((u32*)spriteWork)[0x4C / 4] = 0x4276;
    } else {
        ((u32*)spriteWork)[0x4C / 4] = 0;
    }
    
    ((u8*)spriteWork)[0x64] = 0xF0;
    ((u8*)spriteWork)[0x65] = 0;
    ((u8*)spriteWork)[0x66] = 0;
}

/*
  Address: 0x800431F0 | size: 0x90
  _mailSubject__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork)
  Displays subject for current mail.
*/
void _mailSubject__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork) {
    void* data = ((void**)winWork)[0x68 / 4];
    void* cursorData = ((void**)data)[0x8 / 4];
    s32 cursor = ((s16*)cursorData)[1] + ((s16*)cursorData)[0];
    
    s32 mailId = pdaMailGetMailID(cursor);
    void* subject = mailGetSubject(mailId);
    
    if (subject != 0) {
        void* gsChar = GSmsgGetGSchar(subject);
        msgctrlSetValue(0x37, gsChar);
        ((u32*)spriteWork)[0x4C / 4] = 0x4276;
    } else {
        ((u32*)spriteWork)[0x4C / 4] = 0;
    }
    
    ((u8*)spriteWork)[0x64] = 0xD5;
    ((u8*)spriteWork)[0x65] = 0xAA;
    ((u8*)spriteWork)[0x66] = 0x33;
}

/*
  Address: 0x80043280 | size: 0x4C
  _mailHonbun__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork)
  Displays mail contents/body.
*/
void _mailHonbun__FP14tagWINDOW_WORKP14tagSPRITE_WORK(void* winWork, void* spriteWork) {
    void* data = ((void**)winWork)[0x68 / 4];
    void* cursorData = ((void**)data)[0x8 / 4];
    s32 cursor = ((s16*)cursorData)[1] + ((s16*)cursorData)[0];
    
    s32 mailId = pdaMailGetMailID(cursor);
    void* contents = mailGetContents(mailId);
    ((u32*)spriteWork)[0x4C / 4] = (u32)contents;
}

/*
  Address: 0x800432CC | size: 0x38
  _menuClose__Fl(s32 menuId)
  Closes menu with synchronization.
*/
void _menuClose__Fl(s32 menuId) {
    menuClose(menuId);
    menuCloseSync(menuId, 1);
}
