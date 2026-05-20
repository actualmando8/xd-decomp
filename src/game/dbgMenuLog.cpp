// Decompiled from: dbgMenuLog.cpp
// Address range: 0x8000DEE8..0x8000E154 | size: 0x26C

void*   windowGetKeyInfo(void);
s32     windowGetParam(void* window, s32 param);
void    windowSetParam(void* window, s32 param, s32 value);
void    GSgfxZCompare(s32 a, s32 b);
void    menuSubDrawTile(s32 tile, s32 x, s32 y, s32 w, s32 h, s32 z, s32* work);
s32     GSlogGetLineCount(void);
const char* GSlogGetLine(s32 line);
void    GSprint(s32 tile, s32 x, s32 y, s32 z, const char* str);
s32     menuIsCheck(s32 menuId);
void    menuClose(s32 menuId);
void    menuOpenCustom(s32 menuId, s32 a, s32 b, s32 c, s32 d, s32 e);

/* Global state */
static s32 _viewStartLine;
static u8  _calcStartLine;

/*
  Address: 0x8000DEE8 | size: 0x204
  dbgMenuLogDraw(void* window)
  Draws the debug log window. Handles page navigation with D-pad.
  Sets position/size based on param 0 (0=small, 1=large, 2-3=medium, other=default).
*/
s32 dbgMenuLogDraw(void* window) {
    s32 i;
    s32 lineCount;
    s32 viewEnd;
    void* keyInfo = windowGetKeyInfo();
    
    // Handle page mode switching
    if (keyInfo->field_0x4 & (1 << 23)) {
        s32 param = windowGetParam(window, 0);
        param++;
        if (param >= 3) param = 0;
        windowSetParam(window, 0, param);
    }
    
    // Set position/size based on current param
    s32 param = windowGetParam(window, 0);
    s32 lines, startY, endY;
    if (param == 0) {
        lines = 0xA; startY = 0x82; endY = 0x145;
    } else if (param == 1) {
        lines = 0xA; startY = 0x82; endY = 0x27;
    } else if (0 < param && param < 3) {
        lines = 0x1; startY = 0xD; endY = 0x1BA;
    } else {
        lines = 0xA; startY = 0x82; endY = 0x145;
    }
    
    GSgfxZCompare(0, 7);
    menuSubDrawTile(0, 0xF, startY, 0x25D, window->field_0x1C, endY - 5, 0x12 + startY, 0);
    
    // Calculate start line on first draw
    if (_calcStartLine) {
        lineCount = GSlogGetLineCount();
        _viewStartLine = lineCount - lines;
        _calcStartLine = 0;
    }
    
    // Handle D-pad navigation
    if (keyInfo->field_0x6 & 0x80000000) { // Up
        _viewStartLine--;
    }
    if (keyInfo->field_0x6 & 0x40000000) { // Down
        _viewStartLine++;
    }
    if (keyInfo->field_0x6 & 0x10000000) { // Page down
        _viewStartLine += lines;
    }
    if (keyInfo->field_0x6 & 0x20000000) { // Page up
        _viewStartLine -= lines;
    }
    
    // Clamp viewStartLine
    lineCount = GSlogGetLineCount();
    viewEnd = lineCount - lines;
    if (_viewStartLine < 0) _viewStartLine = 0;
    if (_viewStartLine > viewEnd) _viewStartLine = viewEnd;
    
    // Draw log lines
    s32 y = 0xC0C10000; // Initial Y position (encoded in r31)
    for (i = 0; i < lines; i++) {
        s32 lineIdx = i + _viewStartLine;
        if (lineIdx >= 0) {
            const char* line = GSlogGetLine(lineIdx);
            GSprint(window->field_0x1C, 0x14, y, 0xC0C10000 - 0x3F01, line);
        }
        y += 0xD;
    }
    
    return 0;
}

/*
  Address: 0x8000E0EC | size: 0x68
  dbgMenuLogChangeDisp()
  Toggles menu 0x22 (debug log display).
*/
s32 dbgMenuLogChangeDisp(void) {
    if (menuIsCheck(0x22)) {
        menuClose(0x22);
    }
    else {
        _calcStartLine = 1;
        menuOpenCustom(0x22, 0, 0, 0, 1, 0);
    }
    return 0;
}
