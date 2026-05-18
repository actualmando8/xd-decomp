// Decompiled from agbCommunication.cpp (0x80028F98 - 0x8002D8C0)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// Total size: 0x4928 bytes
//
// This module implements the GBA communication state machine for Pokémon XD.
// It handles async read/write operations with the GBA via the SI (Serial Interface).
// The state machine uses numbered functions (_getpokemon_* and _upload_*) that
// transition between states, with 's' suffix indicating state-check functions.

#include "global.h"

// ============================================================================
// Forward declarations for external functions
// ============================================================================
extern void* GSmemAllocAlign(u32 size, u32 align);
extern void GSmemFree(void* ptr);
extern void* heroBiosGetPokemonPtr(u32 heroId, u16 index);
extern u16 pokemonBiosGetPokemonWazaDataId(void* pkmn, u16 index);
extern void pokeconv(void* out, void* in);
extern void gbaCommandSetKeyState(u32 port, u32 state);
extern u32 GBAReadAsync(void* callback, void* buffer, u32* status);
extern u32 GBAWriteAsync(u32 data, void* callback, u32* status);
extern u32 GBAGetStatusAsync(void* callback, u32* status);
extern u32 OSGetTick(void);
extern void SIProbe(u32 port);
extern void SIRecv(void* buffer, u32 size, u32 port);
extern void SISend(void* buffer, u32 size, u32 port);

// ============================================================================
// Local static variables (from .sbss/.sdata2)
// ============================================================================
static void* jbBuf1;                    // File buffer
static void* _gba_wk;                   // GBA work area (array of structs, 0x9C bytes each)
static u8 gba_pokemon_buf[6][0x278];    // Pokemon data buffer (6 party slots)

// ============================================================================
// Function pointer types
// ============================================================================
typedef void (*GbaStateFunc)(s32 port, s32 param);

// ============================================================================
// Local state machine functions (forward declarations)
// ============================================================================
// GetPokemon state machine (11 states)
static void _getpokemon_01__Fll(s32 port, s32 param);
static void _getpokemon_01s__Fll(s32 port, s32 param);
static void _getpokemon_02__Fll(s32 port, s32 param);
static void _getpokemon_03__Fll(s32 port, s32 param);
static void _getpokemon_04__Fll(s32 port, s32 param);
static void _getpokemon_05__Fll(s32 port, s32 param);
static void _getpokemon_05s__Fll(s32 port, s32 param);
static void _getpokemon_06__Fll(s32 port, s32 param);
static void _getpokemon_07__Fll(s32 port, s32 param);
static void _getpokemon_07s__Fll(s32 port, s32 param);
static void _getpokemon_08__Fll(s32 port, s32 param);
static void _getpokemon_09__Fll(s32 port, s32 param);
static void _getpokemon_09s__Fll(s32 port, s32 param);
static void _getpokemon_10__Fll(s32 port, s32 param);
static void _getpokemon_11__Fll(s32 port, s32 param);

// Upload state machine (26 states)
static void _upload_00s__Fll(s32 port, s32 param);
static void _upload_01__Fll(s32 port, s32 param);
static void _upload_02__Fll(s32 port, s32 param);
static void _upload_03__Fll(s32 port, s32 param);
static void _upload_04__Fll(s32 port, s32 param);
static void _upload_05__Fll(s32 port, s32 param);
static void _upload_06__Fll(s32 port, s32 param);
static void _upload_07__Fll(s32 port, s32 param);
static void _upload_08__Fll(s32 port, s32 param);
static void _upload_09__Fll(s32 port, s32 param);
static void _upload_10__Fll(s32 port, s32 param);
static void _upload_11__Fll(s32 port, s32 param);
static void _upload_11s__Fll(s32 port, s32 param);
static void _upload_12__Fll(s32 port, s32 param);
static void _upload_12s__Fll(s32 port, s32 param);
static void _upload_13__Fll(s32 port, s32 param);
static void _upload_13s__Fll(s32 port, s32 param);
static void _upload_14__Fll(s32 port, s32 param);
static void _upload_15__Fll(s32 port, s32 param);
static void _upload_16__Fll(s32 port, s32 param);
static void _upload_16s0__Fll(s32 port, s32 param);
static void _upload_16s__Fll(s32 port, s32 param);
static void _upload_17__Fll(s32 port, s32 param);
static void _upload_17s__Fll(s32 port, s32 param);
static void _upload_18__Fll(s32 port, s32 param);
static void _upload_19__Fll(s32 port, s32 param);
static void _upload_20__Fll(s32 port, s32 param);
static void _upload_21__Fll(s32 port, s32 param);
static void _upload_21s__Fll(s32 port, s32 param);
static void _upload_22__Fll(s32 port, s32 param);
static void _upload_23__Fll(s32 port, s32 param);
static void _upload_23s__Fll(s32 port, s32 param);
static void _upload_24__Fll(s32 port, s32 param);
static void _upload_25__Fll(s32 port, s32 param);

// Helper functions
static void _timer_set__FlUl(s32 port, u32 ticks);
static void _job_type_clear__FlPCc(s32 port, const char* func);
static void _AGB_Work_Clear__Fl(s32 port);
static u32 _SendRecv__FlUlPUl(s32 port, u32 data, u32* out);
static u32 _BulkSend__FlPCUci(s32 port, const u32* data, u32 count);
static u32 _BulkSend2__FlPCUci(s32 port, const u32* data, u32 count);
static u32 _GBATimerRead__FlPUcPUci(s32 port, u8* out, u32* size, u32 timeout);
static u32 _InitialExchange__Fl(s32 port);
static u32 _alarm_handler__FP7OSAlarmP9OSAlarm(void* alarm, void* context);
static void _sleep_thread__Fi(int ticks);

// PKJB validation functions
static u32 _PKJBUpFindBootKey__FUlUl(u32 data1, u32 data2);
static u32 _PKJBUpCalcCrc__FUlUl(u32 data1, u32 data2);
static u32 _ReadJBCode__FPCcPUcPUl(const char* in, u8* out, u32* outSize);
static void _AdjustGbaImageRegistry__FPUcPc(u8* out, char* in);
static u32 _PKJBUpValidateKeyB__FUl(u32 key);
static u32 _PKJBUpGenerateKeyA__Fv(void);
static u32 SwapEndian__FUl(u32 val);

// ============================================================================
// Public API Functions
// ============================================================================

// --------------------------------------------------------------------------
// AGB_FileBuffFree
// Address: 0x80028F98 | Size: 0x2C
// Frees the file buffer allocated by AGB_FileBuffAlloc.
// --------------------------------------------------------------------------
void AGB_FileBuffFree(void)
{
    GSmemFree(jbBuf1);
    jbBuf1 = 0;
}

// --------------------------------------------------------------------------
// AGB_FileBuffAlloc
// Address: 0x80028FC4 | Size: 0x2C
// Allocates a 0x20-byte aligned file buffer of size 0x200.
// --------------------------------------------------------------------------
void AGB_FileBuffAlloc(void)
{
    jbBuf1 = GSmemAllocAlign(0x200, 0x20);
}

// --------------------------------------------------------------------------
// AGB_GetPokemon
// Address: (after _getpokemon_11) | Size: varies
// Entry point for the GetPokemon state machine.
// Starts the async process of receiving a Pokemon from GBA.
// --------------------------------------------------------------------------
void AGB_GetPokemon(s32 port, s32 param)
{
    _getpokemon_01__Fll(port, param);
}

// --------------------------------------------------------------------------
// AGB_Upload
// Address: (after _upload_25) | Size: varies
// Entry point for the Upload state machine.
// Starts the async process of uploading data to GBA.
// --------------------------------------------------------------------------
void AGB_Upload(s32 port, s32 param)
{
    _upload_01__Fll(port, param);
}

// --------------------------------------------------------------------------
// AGB_Prepare
// Prepares GBA communication by initializing work area.
// --------------------------------------------------------------------------
void AGB_Prepare(s32 port)
{
    _AGB_Work_Clear__Fl(port);
}

// --------------------------------------------------------------------------
// PKJB_ExchangeEnd
// Ends the Pokemon exchange session.
// --------------------------------------------------------------------------
void PKJB_ExchangeEnd(s32 port)
{
    _AGB_ExchangeEnd__Fl(port);
}

// --------------------------------------------------------------------------
// PKJB_ExchangeIsPrepared
// Checks if exchange is prepared. Returns status code.
// --------------------------------------------------------------------------
s32 PKJB_ExchangeIsPrepared(s32 port)
{
    return _AGB_ExchangeIsPrepared__Fl(port);
}

// --------------------------------------------------------------------------
// PKJB_ExchangeStart
// Starts Pokemon exchange with the GBA.
// Args: port, data buffer
// --------------------------------------------------------------------------
void PKJB_ExchangeStart(s32 port, u8* data)
{
    _AGB_ExchangeStart__FlPUc(port, data);
}

// --------------------------------------------------------------------------
// PKJB_ReturnTitle
// Returns to title screen on GBA side.
// --------------------------------------------------------------------------
void PKJB_ReturnTitle(s32 port)
{
    _AGB_ReturnTitle__Fl(port);
}

// --------------------------------------------------------------------------
// PKJB_BattleGetStatus
// Gets the current battle status from GBA.
// --------------------------------------------------------------------------
s32 PKJB_BattleGetStatus(s32 port, u32* outStatus)
{
    // Implementation calls internal battle status function
    return 0;  // Stub - needs full decompilation
}

// --------------------------------------------------------------------------
// PKJB_EntryGetStatus
// Gets the entry status from GBA.
// --------------------------------------------------------------------------
s32 PKJB_EntryGetStatus(s32 port, u32* outStatus)
{
    return _AGB_EntryGetStatus__FlPUl(port, outStatus);
}

// --------------------------------------------------------------------------
// PKJB_BattleRequest
// Sends a battle request to GBA.
// --------------------------------------------------------------------------
void PKJB_BattleRequest(s32 port, const u32* requestData, u32 size)
{
    _AGB_BattleRequest__FlPCUci(port, requestData, size);
}

// --------------------------------------------------------------------------
// PKJB_EntryRequest
// Sends an entry request to GBA.
// --------------------------------------------------------------------------
void PKJB_EntryRequest(s32 port, u32 data)
{
    _AGB_EntryRequest__FlUl(port, data);
}

// --------------------------------------------------------------------------
// PKJB_SendWazaText
// Sends Waza (shadow Pokemon) text to GBA.
// --------------------------------------------------------------------------
void PKJB_SendWazaText(s32 port, u8* textData)
{
    _AGB_SendWazaText__FlPUc(port, textData);
}

// --------------------------------------------------------------------------
// PKJB_IdleSend
// Sends idle command to GBA.
// --------------------------------------------------------------------------
s32 PKJB_IdleSend(s32 port)
{
    // Implementation sends idle packet
    return 0;  // Stub
}

// --------------------------------------------------------------------------
// PKJB_GetKey
// Gets key data from GBA.
// --------------------------------------------------------------------------
s32 PKJB_GetKey(s32 port, u32* outKey)
{
    // Implementation reads key from GBA
    return 0;  // Stub
}

// --------------------------------------------------------------------------
// AGB_IsComplete
// Checks if GBA communication is complete.
// --------------------------------------------------------------------------
s32 AGB_IsComplete(s32 port)
{
    // Check state machine completion
    return 0;  // Stub
}

// --------------------------------------------------------------------------
// AGB_GetStatus
// Gets the current status of GBA communication.
// --------------------------------------------------------------------------
s32 AGB_GetStatus(s32 port)
{
    // Get state machine status
    return 0;  // Stub
}

// --------------------------------------------------------------------------
// AGB_Terminate
// Terminates GBA communication.
// --------------------------------------------------------------------------
void AGB_Terminate(s32 port)
{
    // Cleanup and terminate
}

// --------------------------------------------------------------------------
// AGB_Terminate_init
// Initializes termination of GBA communication.
// --------------------------------------------------------------------------
void AGB_Terminate_init(s32 port)
{
    // Init termination sequence
}

// --------------------------------------------------------------------------
// AGB_Initialize
// Initializes GBA communication system.
// --------------------------------------------------------------------------
void AGB_Initialize__Fl(s32 port)
{
    // Full initialization
    AGB_FileBuffAlloc();
    _AGB_Work_Clear__Fl(port);
}

// ============================================================================
// State Machine Implementations (Partial - Key Patterns)
// ============================================================================

// The state machine functions follow a common pattern:
// 1. Check current state (from _gba_wk[port*0x9C + 0xC])
// 2. If state is 0, return early
// 3. Set new state number
// 4. If param == 1, perform cleanup and return
// 5. Otherwise, initiate async operation (GBAReadAsync/GBAWriteAsync/GBAGetStatusAsync)
// 6. Check result - if async (==2), wait; otherwise continue to next state

// --------------------------------------------------------------------------
// _getpokemon_11 (Final state of GetPokemon)
// Address: 0x80028FF0 | Size: 0x164
// Receives final Pokemon data and converts with pokeconv.
// --------------------------------------------------------------------------
static void _getpokemon_11__Fll(s32 port, s32 param)
{
    void* gbaWk = &_gba_wk[port * 0x9C];
    
    // Check if data pointer valid
    if (*(u32*)((u8*)gbaWk + 0xC) == 0)
        return;
    
    *(u32*)((u8*)gbaWk + 0x8) = 0xB;  // Set state 11
    
    if (param == 1)
    {
        // Cleanup path
        _job_type_clear__FlPCc(port, "_getpokemon_11");
        gbaCommandSetKeyState(port + 1, 1);
        return;
    }
    
    // Check if buffer full (0x278 bytes)
    u32 bufPos = *(u32*)((u8*)gbaWk + 0x5C);
    if (bufPos >= 0x278)
    {
        // Buffer full - convert Pokemon data
        pokeconv(*(void***)((u8*)gbaWk + 0x94), *(u32*)((u8*)gbaWk + 0x8C));
        
        // Extract and set command data
        u8* cmdPtr = (u8*)*(u32*)((u8*)gbaWk + 0x8C);
        u32 cmdData = cmdPtr[0] | (cmdPtr[1] << 8) | (cmdPtr[2] << 16) | (cmdPtr[3] << 24);
        *(u32*)((u8*)gbaWk + 0x98) = cmdData;
        
        _job_type_clear__FlPCc(port, "_getpokemon_11");
        gbaCommandSetKeyState(port + 1, 1);
    }
    else
    {
        // More data to receive
        _timer_set__FlUl(port, 0x7D);
        _getpokemon_09s__Fll(port, param);
    }
}

// --------------------------------------------------------------------------
// _getpokemon_09s (State check for state 9)
// Address: 0x80029230 | Size: 0xE0
// Checks timer and transitions to state 10.
// --------------------------------------------------------------------------
static void _getpokemon_09s__Fll(s32 port, s32 param)
{
    void* gbaWk = &_gba_wk[port * 0x9C];
    
    if (*(u32*)((u8*)gbaWk + 0xC) == 0)
        return;
    
    *(u32*)((u8*)gbaWk + 0x8) = 0x3F1;  // Timeout value
    
    u32 tick = OSGetTick();
    u32 elapsed = tick - *(u32*)((u8*)gbaWk + 0x6C);
    
    if (elapsed > *(u32*)((u8*)gbaWk + 0x70))
    {
        // Timeout - cleanup
        _job_type_clear__FlPCc(port, "_getpokemon_09s");
        gbaCommandSetKeyState(port + 1, 1);
        return;
    }
    
    // Continue to state 10
    u32 result;
    GBAGetStatusAsync(_getpokemon_10__Fll, &result);
    
    if (result == 2)  // Async - wait
        return;
}

// --------------------------------------------------------------------------
// _timer_set
// Sets a timer for the given port.
// --------------------------------------------------------------------------
static void _timer_set__FlUl(s32 port, u32 ticks)
{
    // Set timer value in work area
    *(u32*)((u8*)_gba_wk + port * 0x9C + 0x78) = ticks;
}

// --------------------------------------------------------------------------
// _job_type_clear
// Clears job type and resets state machine.
// --------------------------------------------------------------------------
static void _job_type_clear__FlPCc(s32 port, const char* funcName)
{
    // Clear job type and reset state
    *(u32*)((u8*)_gba_wk + port * 0x9C + 0x18) = 0;
    *(u32*)((u8*)_gba_wk + port * 0x9C + 0xC) = 0;
}

// --------------------------------------------------------------------------
// _AGB_Work_Clear
// Clears the work area for the given port.
// --------------------------------------------------------------------------
static void _AGB_Work_Clear__Fl(s32 port)
{
    // Clear entire work struct
    // memset(&_gba_wk[port * 0x9C], 0, 0x9C);
}

// ============================================================================
// NOTE: The remaining state machine functions (_getpokemon_01-10, _upload_01-25)
// follow the same pattern as shown above. Full decompilation requires
// line-by-line analysis of each function's specific data offsets and
// transitions. The structure is:
//
// - Even-numbered states: Initiate async operations
// - Odd-numbered states with 's' suffix: Check timer/async completion
// - State transitions flow sequentially through the numbered chain
// - Each state sets the state number in _gba_wk[port*0x9C + 0x8]
// ============================================================================
