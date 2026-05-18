// Decompiled from gbaCommand.cpp (0x80027E84 - 0x80028F98)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r7 args, r3 return, LR saved on stack
// Total size: 0x1114 bytes

#include "global.h"

// Forward declarations for external functions
extern void PKJB_ExchangeEnd(u32 port);
extern s32 PKJB_ExchangeIsPrepared(s32 port);
extern void PKJB_ExchangeStart(s32 port, void* data);
extern void PKJB_BattleRequest(s32 port, void* reqData, u32 size);
extern s32 PKJB_BattleGetStatus(s32 port, u32* out);
extern void PKJB_ReturnTitle(s32 port);
extern s32 PKJB_EntryGetStatus(s32 port, u32* out);
extern void PKJB_EntryRequest(s32 port, u32 data);
extern void PKJB_SendWazaText(s32 port, void* data);
extern s32 PKJB_GetKey(s32 port, u32* out);
extern void PKJB_IdleSend(s32 port);

extern void SIProbe(u32 port);
extern s32 gbaPokemonFromGC(void* out, void* pkmn);
extern u16 gbaPokemonConditonFromGC(void* pkmn);
extern u32 _swap32__FUl(u32 val);
extern u16 _swap16__FUs(u16 val);

// Battle/Fight system functions
extern s32 fightFloorGetStatus(s32 p0, s32 p1, u32 p2, s32 p3);
extern void* fightTypeDataBiosGetPtr(u32 floorId);
extern u32 fightTypeDataBiosGetTrainerNum(void* typeData);
extern u32 fightTypeDataBiosGetEntryPokemonNum(void* typeData);
extern u32 fightTypeDataBiosGetFightoutPokemonNum(void* typeData);
extern void* fightTargetGetPtr(u32 targetId, u32 floorId);
extern void* fightTrainerGetValidFightOutPokemonPtr(void* trainer, u32 index);
extern s32 fightTrainerBiosGetControllerId(void* trainer);
extern void* fightTrainerGetValidFightPokemonPtr(void* trainer, u32 index);
extern void* fightPokemonGetPokemonPtr(void* fightPokemon);
extern u16 fightPokemonGetSoubiItemDataId(void* fightPokemon);
extern s32 fightTrainerCheckCanIrekaeFightPokemon(void* trainer, void* fightPokemon);
extern void* fightOutPokemonGetPokemonPtr(void* fightOutPokemon);
extern s32 fightOutPokemonGetTokuseiDataId(void* fightOutPokemon);
extern void fightOutPokemonGetRndStatus(void* fightOutPokemon, u32* out1, u32* out2);
extern u32 fightOutPokemonBiosGetZokuseiDataId(void* fightOutPokemon, u32 p1);
extern s32 fightOutPokemonCheckFightActionWazaSelect(void* fightOutPokemon, u32 p1, u32 p2);
extern s32 fightOutPokemonCheckCanOutOkWazaBanme(void* fightOutPokemon, u32 banme, u32 p1, u32 p2);
extern s32 fightOutPokemonIsJoutaiDataId(void* fightOutPokemon, u32 joutaiId);
extern s32 fightGetFightResultId(void);
extern s32 fightFloorIsUseFightTimerCommand(s32 p0);
extern s32 fightTimerCommandIsOver(void);
extern void* fightFloorBiosGetFightFloorPtr(s32 p0);
extern s32 fightFloorCheckFightActionFightOutPokemonIrekaeSelect(void* floor, void* trainer, void* p2);
extern void fightSeqSelectDefensePokemonPtr(void* p0, u16 p1, u32 p2, void* p3, u32 p4, u32 p5, s32 p6, void* p7);

// Pokemon BIOS functions
extern u16 pokemonBiosGetPokemonDataId(void* pkmn);
extern u32 pokemonBiosGetTokuseiFlag(void* pkmn);
extern void pokemonBiosSetTokuseiFlag(void* pkmn, u32 flag);
extern u32 pokemonBiosGetFightTrainerPokemonDataId(void* pkmn);
extern u32 pokemonBiosGetPokerus(void* pkmn);
extern u16 pokemonBiosGetHp(void* pkmn);
extern u16 pokemonBiosGetMaxHp(void* pkmn);
extern u16 pokemonBiosGetMailId(void* pkmn);
extern u16 pokemonBiosGetPokemonWazaDataId(void* pkmn, u32 index);
extern u8 pokemonBiosGetPokemonWazaPp(void* pkmn, u32 index);
extern u32 pokemonBiosGetAttest(void* pkmn);
extern const char* pokemonBiosGetNicknamePtr(void* pkmn);
extern u8 pokemonBiosGetLevel(void* pkmn);
extern u32 pokemonBiosGetRnd(void* pkmn);

// Game data functions
extern u32 gamedataAttestBiosGetLangareaId(u32* attest);
extern u32 pokemonGetSex(void* pkmn);
extern u32 exribbonGetNo(u32 index);
extern u32 GetWazaDocGBA(u32 wazaId, u32 p1);
extern u32 wazaconv(u32* out, u32 p1);
extern u32 GBAMakeFromGSchar(u8* out, const char* in, u32 langareaId);
extern s32 menuCBRule_DEOKISISUCamouflage(void);
extern u32 pokemonGetDeoxysSel(u32 form);
extern u32 menuCB_GetToolBattleModeFlag(void);
extern u32 menuCBBios_CurrentlyWorkingToolBattle(void);
extern void GSthreadSwitch(void);

// Local static variables (from .sbss and .data)
static u8 gba_SIProbe_ErrorCnt[4];  // sda21 offset
static u16 _keyCounter[4];          // sda21 offset
static u16 _keyPressed[4];          // sda21 offset
static u8 _needSelect;              // sda21 offset
static u32 _SIProbe_Result[4];      // .data
static u32 _SIProbe_Counter[4];     // .data
static u32 _keyState[4];            // .bss
static u32 _keyResult[4];           // .bss

// ============================================================================
// gba_SIProbe_ErrorCntClear
// Address: 0x80027E84 | Size: 0x34
// Args: r3 = port/index
// Returns: void
// Clears SI probe error counters for the given port.
// ============================================================================
void gba_SIProbe_ErrorCntClear(s32 port)
{
    if (port == -1)
    {
        gba_SIProbe_ErrorCnt[0] = 0;
        gba_SIProbe_ErrorCnt[1] = 0;
        gba_SIProbe_ErrorCnt[2] = 0;
        gba_SIProbe_ErrorCnt[3] = 0;
    }
    else
    {
        gba_SIProbe_ErrorCnt[port] = 0;
    }
}

// ============================================================================
// gba_SIProbe
// Address: 0x80027EB8 | Size: 0x14
// Args: r3 = port index
// Returns: r3 = SI probe result
// Returns the SI probe result for the given port (indexed by port*4).
// ============================================================================
u32 gba_SIProbe(u32 port)
{
    return _SIProbe_Result[port * 2];  // slwi r0, r3, 2 -> lwzx
}

// ============================================================================
// gbaCommandChangePokemonEnd
// Address: 0x80027ECC | Size: 0x24
// Args: r3 = port + 1
// Returns: void
// Ends the Pokémon exchange on the given port.
// ============================================================================
void gbaCommandChangePokemonEnd(s32 port)
{
    PKJB_ExchangeEnd(port - 1);
}

// ============================================================================
// gbaCommandChangePokemonIsPrepared
// Address: 0x80027EF0 | Size: 0x88
// Args: r3 = port + 1
// Returns: r3 = status (-1 when ready, 0 otherwise)
// Checks if Pokémon exchange is prepared. Increments key counter.
// ============================================================================
s32 gbaCommandChangePokemonIsPrepared(s32 port)
{
    s32 status;
    s32 result = 0;
    
    status = PKJB_ExchangeIsPrepared(port - 1);
    
    if (status >= 0)
    {
        if (status == 1 || status == 2)
        {
            _keyCounter[port]++;
            if (_keyCounter[port] >= 0xA)
            {
                result = -1;
            }
        }
    }
    else
    {
        _keyCounter[port] = 0;
    }
    
    return result;
}

// ============================================================================
// gbaCommandChangePokemon
// Address: 0x80027F78 | Size: 0xF8
// Args: r29=r3=port+1, r31=r4=pkmn, r30=r6=flags
// Returns: void
// Starts Pokémon exchange. Converts GC Pokemon to GBA format and sends.
// ============================================================================
void gbaCommandChangePokemon(s32 port, void* pkmn, u32 flags)
{
    u32 swappedFlags;
    u16 dataId;
    u32 tokuseiFlag;
    u32 i;
    u8 ribbonData[0x74];  // buffer for GBA Pokemon data
    
    // Swap flags to little-endian
    swappedFlags = _swap32__FUl(flags);
    
    // Get and combine data ID with tokusei flag
    dataId = pokemonBiosGetPokemonDataId(pkmn);
    dataId = (dataId & 0xFFFF) | ((flags >> 16) & 0xFFFF);
    // ASM: clrlwi r3, r3, 16 | slwi r0, r30, 16 | or r3, r0, r3
    u32 combinedDataId = _swap32__FUl((u32)dataId);
    
    // Check for special species (Deoxys = 0x181)
    if (pokemonBiosGetPokemonDataId(pkmn) == 0x181)
    {
        tokuseiFlag = pokemonBiosGetTokuseiFlag(pkmn);
        tokuseiFlag &= 0xFFFFFF;  // clear top byte
        // Count leading zeros and shift
        u32 cnt = 0;
        while ((tokuseiFlag & (1 << cnt)) == 0 && cnt < 32) cnt++;
        u32 shifted = cnt >> 5;
        pokemonBiosSetTokuseiFlag(pkmn, shifted);
    }
    
    // Convert GC Pokemon to GBA format
    gbaPokemonFromGC(ribbonData, pkmn);
    
    // Clear upper portion of buffer
    memset(ribbonData + 0x74, 0, 0xC);
    
    // Collect ribbon data
    for (i = 0; i < 0xB; i++)
    {
        ribbonData[i] = exribbonGetNo(i);
    }
    
    // Start exchange
    PKJB_ExchangeStart(port - 1, &swappedFlags);
    
    // Reset key counter
    _keyCounter[port] = 0;
}

// ============================================================================
// gbaCommandGetGBAChangePokemon
// Address: 0x80028070 | Size: 0x8
// Args: r3 = command data
// Returns: r3 = lower 16 bits (data ID)
// Extracts the GBA Pokemon data ID from command.
// ============================================================================
u16 gbaCommandGetGBAChangePokemon(u32 cmd)
{
    return cmd & 0xFFFF;
}

// ============================================================================
// gbaCommandGetWazaTarget
// Address: 0x80028078 | Size: 0x8
// Args: r3 = command data
// Returns: r3 = bits 8-23 (Waza target)
// Extracts Waza target from command.
// ============================================================================
u16 gbaCommandGetWazaTarget(u32 cmd)
{
    return (cmd >> 8) & 0xFFFF;
}

// ============================================================================
// gbaCommandGetWazaDataId
// Address: 0x80028080 | Size: 0x8
// Args: r3 = command data
// Returns: r3 = upper 8 bits (Waza data ID)
// Extracts Waza data ID from command.
// ============================================================================
u8 gbaCommandGetWazaDataId(u32 cmd)
{
    return cmd >> 24;
}

// ============================================================================
// gbaCommandGetAction
// Address: 0x80028088 | Size: 0x8
// Args: r3 = command data
// Returns: r3 = bits 16-31 (action)
// Extracts action from command.
// ============================================================================
u16 gbaCommandGetAction(u32 cmd)
{
    return cmd >> 16;
}

// ============================================================================
// _dummySelect
// Address: 0x80028A90 | Size: 0x10
// Args: r3=FightOutPokemon*, r4=r5=unsigned short
// Returns: r3=0
// Callback that sets _needSelect flag and returns 0.
// ============================================================================
static s32 _dummySelect(void* fightOutPokemon, u16 p1, u16 p2)
{
    _needSelect = 1;
    return 0;
}

// ============================================================================
// gbaCommandKeyPressed
// Address: 0x80028C48 | Size: 0x14
// Args: r3 = port index
// Returns: r3 = key pressed status
// Returns the key pressed status for the given port.
// ============================================================================
u16 gbaCommandKeyPressed(u32 port)
{
    return _keyPressed[port];
}

// ============================================================================
// gbaCommandIsConnected
// Address: 0x80028C5C | Size: 0x40
// Args: r3 = port index
// Returns: r3 = 1 if connected, 0 otherwise
// Checks if GBA is connected on the given port.
// ============================================================================
s32 gbaCommandIsConnected(u32 port)
{
    if (_keyState[port] == 0)
        return 0;
    if (_keyResult[port] != 0)
        return 1;
    return 0;
}

// ============================================================================
// gbaCommandSetKeyState
// Address: 0x80028C9C | Size: 0x50
// Args: r3 = port, r4 = new state
// Returns: void
// Sets the key state and clears related counters/results.
// ============================================================================
void gbaCommandSetKeyState(u32 port, u32 newState)
{
    _keyState[port] = newState;
    _keyResult[port] = 0;
    _keyCounter[port] = 0;
    _keyPressed[port] = 0;
}

// ============================================================================
// gbaCommandEntryPokemon
// Address: 0x80028AA0 | Size: 0x38
// Args: r3 = command data, r4 = output buffer
// Returns: void
// Extracts Pokemon data from command and writes to buffer.
// ============================================================================
void gbaCommandEntryPokemon(u32 cmd, u8* out)
{
    out[0] = cmd >> 28;       // top 4 bits
    out[1] = (cmd >> 24) & 0xF;
    out[2] = (cmd >> 20) & 0xF;
    out[3] = (cmd >> 16) & 0xF;
    out[4] = (cmd >> 12) & 0xF;
    out[5] = (cmd >> 8) & 0xF;
}

// ============================================================================
// gbaCommandEntryResult
// Address: 0x80028AD8 | Size: 0xFC
// Args: r3=port+1, r4=output buffer
// Returns: r3=0
// Gets the result of entry request.
// ============================================================================
s32 gbaCommandEntryResult(s32 port, u32* out)
{
    s32 status;
    
    *out = 0x200;
    status = PKJB_EntryGetStatus(port - 1, out);
    
    if (status == 1)
    {
        // Increment error counter
        gba_SIProbe_ErrorCnt[port - 1]++;
        if (gba_SIProbe_ErrorCnt[port - 1] >= 2)
        {
            status = -1;
        }
    }
    else
    {
        gba_SIProbe_ErrorCntClear(port - 1);
    }
    
    if (status < 0)
    {
        return 0;
    }
    
    if (status == 0)
    {
        if (*out != 0)
        {
            u32 swapped = _swap32__FUl(*out);
            *out = swapped;
            if ((swapped >> 24) != 0)
            {
                return 0;
            }
            gbaCommandSetKeyState(port, 1);
        }
    }
    else
    {
        *out = 0x300;
        gbaCommandSetKeyState(port, 1);
    }
    
    return 0;
}

// ============================================================================
// gbaCommandEntryRequest
// Address: 0x80028BD4 | Size: 0x34
// Args: r3=port+1, r4=r6<<24, r5=r5<<8
// Returns: void
// Sends entry request to GBA.
// ============================================================================
void gbaCommandEntryRequest(s32 port, u32 r4, u32 r5, u32 r6)
{
    u32 combined = r6 << 24 | r5 << 8 | r4;
    PKJB_EntryRequest(port - 1, combined);
}

// ============================================================================
// gbaCommandSendWazaText
// Address: 0x80028C08 | Size: 0x40
// Args: r3=port+1, r4=waza text data
// Returns: void
// Sends Waza text to GBA after conversion.
// ============================================================================
void gbaCommandSendWazaText(s32 port, u32* wazaText)
{
    u32 converted[0x790];  // large buffer for conversion
    
    wazaconv(converted, *wazaText);
    PKJB_SendWazaText(port - 1, converted);
}

// ============================================================================
// gbaCommandKeyRead
// Address: 0x80028CEC | Size: 0x26C
// Args: r3 = port index (1 or 2)
// Returns: r3 = result (0 or 1)
// Reads key state from GBA. Handles SI probe initialization for port 2.
// ============================================================================
s32 gbaCommandKeyRead(u32 port)
{
    u32 keyState;
    s32 result;
    u32 i;
    
    // For port 2, perform SI probe initialization
    if (port == 2)
    {
        u32* resultPtr = _SIProbe_Result;
        u32* counterPtr = _SIProbe_Counter;
        
        for (i = 0; i < 4; i++)
        {
            u32 probeResult;
            
            SIProbe(i);
            probeResult = result;
            
            // Check for tool battle mode
            if (menuCB_GetToolBattleModeFlag() == 1 && menuCBBios_CurrentlyWorkingToolBattle() != 0)
            {
                probeResult = 0x40000;  // lis r28, 0x4
            }
            
            if (probeResult == 0x40000)
            {
                *resultPtr = probeResult;
                *counterPtr = 2;
            }
            else if (*counterPtr == 0)
            {
                *resultPtr = probeResult;
            }
            else
            {
                *counterPtr = *counterPtr - 1;
            }
            
            resultPtr++;
            counterPtr++;
        }
    }
    
    keyState = _keyState[port];
    
    if (keyState == 2)
    {
        // Connected state - reset key pressed
        _keyPressed[port] = 0;
        result = 0;
    }
    else if (keyState >= 4)
    {
        // Error state - call PKJB_IdleSend
        s32 idleResult = PKJB_IdleSend(port - 1);
        
        if (idleResult == 0)
        {
            _keyCounter[port] = 0;
        }
        else if (idleResult <= 2)
        {
            _keyCounter[port]++;
            if (_keyCounter[port] >= 0xA)
            {
                _keyPressed[port] = 0;
                gbaCommandSetKeyState(port, 0);
            }
        }
        else
        {
            _keyPressed[port] = 0;
            gbaCommandSetKeyState(port, 0);
        }
        
        _keyPressed[port] = 0;
    }
    else if (keyState >= 1)
    {
        // Key read in progress
        s32 getKeyResult = PKJB_GetKey(port - 1, &result);
        
        if (getKeyResult != 0)
        {
            if (getKeyResult <= 2)
            {
                _keyCounter[port]++;
                if (_keyCounter[port] >= 0xA)
                {
                    _keyPressed[port] = 0;
                    gbaCommandSetKeyState(port, 0);
                }
                else
                {
                    result = 0;
                }
            }
            else
            {
                _keyPressed[port] = 0;
                gbaCommandSetKeyState(port, 0);
            }
        }
        else
        {
            // Success - store key data
            _keyPressed[port] = result;
            _keyCounter[port] = 0;
            result = 0;
        }
    }
    else
    {
        // Disconnected or unknown state
        _keyPressed[port] = 0;
        result = 1;
    }
    
    _keyResult[port] = result;
    
    return result;
}

// ============================================================================
// _swap32
// Address: 0x80028F58 | Size: 0x28
// Args: r3 = value
// Returns: r3 = byte-swapped value
// Swaps the byte order of a 32-bit value (big-endian <-> little-endian).
// ============================================================================
u32 _swap32__FUl(u32 val)
{
    u32 b0 = (val >> 24) & 0xFF;
    u32 b1 = (val >> 16) & 0xFF;
    u32 b2 = (val >> 8) & 0xFF;
    u32 b3 = val & 0xFF;
    
    return b0 | (b1 << 8) | (b2 << 16) | (b3 << 24);
}

// ============================================================================
// _swap16
// Address: 0x80028F80 | Size: 0x18
// Args: r3 = value
// Returns: r3 = byte-swapped value
// Swaps the byte order of a 16-bit value (big-endian <-> little-endian).
// ============================================================================
u16 _swap16__FUs(u16 val)
{
    return (val << 8) | (val >> 8);
}

// ============================================================================
// gbaCommandRequestAction
// Address: 0x80028090 | Size: 0xA00
// Args: r3=port+1, r4=fightOutPokemon, r5=floorId, r6=flags
// Returns: r3 = result code
// Large function that handles battle requests with GBA.
// Prepares Pokemon data, handles battle loop, and returns result.
// ============================================================================
s32 gbaCommandRequestAction(s32 port, void* fightOutPokemon, u32 floorId, u32 flags)
{
    // NOTE: This is a very large function (0xA00 bytes) with complex logic.
    // The decompilation below captures the main structure and flow.
    // Full implementation requires careful analysis of all sub-sections.
    
    u32 status;
    void* typeData;
    u32 trainerNum;
    void* targetPtr;
    void* trainerPtr;
    u32 i;
    u32 j;
    u32 reqData[0x900];  // large request buffer
    
    // Get fight floor status
    status = fightFloorGetStatus(0, 0, 0x14, 0);
    typeData = fightTypeDataBiosGetPtr(status);
    trainerNum = fightTypeDataBiosGetTrainerNum(typeData);
    
    // Get entry/fightout Pokemon numbers
    u32 entryNum = fightTypeDataBiosGetEntryPokemonNum(typeData);
    u32 fightoutNum = fightTypeDataBiosGetFightoutPokemonNum(typeData);
    
    // Calculate target index
    u32 targetIndex = (trainerNum & 0xFF) * (fightoutNum & 0xFF) * 2;
    targetPtr = fightTargetGetPtr(0xB, status, targetIndex);
    
    // Get valid fightout Pokemon pointer
    trainerPtr = fightTrainerGetValidFightOutPokemonPtr(targetPtr, 0);
    
    // Handle based on trainer number
    if (trainerNum == 2)
    {
        // Two trainer battle setup
        void* trainer7 = fightTargetGetPtr(0x7, status, 0);
        trainerPtr = fightTrainerGetValidFightOutPokemonPtr(trainer7, 0);
        u32 ctrlId = fightTrainerBiosGetControllerId(trainer7);
        
        void* trainer9 = fightTargetGetPtr(0x9, status, 0);
        void* trainer9Ptr = fightTrainerGetValidFightOutPokemonPtr(trainer9, 0);
        u32 ctrlId9 = fightTrainerBiosGetControllerId(trainer9);
        
        void* trainerA = fightTargetGetPtr(0xA, status, 0);
        void* trainerAPtr = fightTrainerGetValidFightOutPokemonPtr(trainerA, 0);
        u32 ctrlIdA = fightTrainerBiosGetControllerId(trainerA);
    }
    // ... more cases for other trainer configurations
    
    // Build request data - iterate through entry Pokemon
    u32 numEntry = entryNum & 0xFF;
    u32 dataOffset = 0x38;
    u32 pokeOffset = 0x8;
    
    for (i = 0; i < numEntry; i++)
    {
        void* fightPkmn = fightTrainerGetValidFightPokemonPtr(fightOutPokemon, i);
        if (fightPkmn == 0)
        {
            // Handle missing Pokemon
            u32 mask = 1 << (i * 4);
            // Set invalid bit
            break;
        }
        
        void* pkmn = fightPokemonGetPokemonPtr(fightPkmn);
        u16 dataId = pokemonBiosGetFightTrainerPokemonDataId(pkmn);
        
        // Check if can replace
        s32 canReplace = fightTrainerCheckCanIrekaeFightPokemon(fightPkmn, pkmn);
        
        // Get Pokerus
        u32 pokerus = pokemonBiosGetPokerus(pkmn);
        
        // Get HP and swap to LE
        u16 hp = _swap16__FUs(pokemonBiosGetHp(pkmn));
        
        // Get condition
        u16 condition = gbaPokemonConditonFromGC(pkmn);
        
        // Get item
        u16 item = fightPokemonGetSoubiItemDataId(fightPkmn);
        item = _swap16__FUs(item);
        
        // Get mail ID and pack into byte
        u16 mailId = pokemonBiosGetMailId(pkmn);
        
        // Get moves and PP
        for (j = 0; j < 4; j++)
        {
            u16 moveId = pokemonBiosGetPokemonWazaDataId(pkmn, j);
            moveId = _swap16__FUs(moveId);
            u8 pp = pokemonBiosGetPokemonWazaPp(pkmn, j);
            u32 doc = GetWazaDocGBA(moveId, dataOffset + 0x38);
        }
        
        dataOffset += 0x154;
        pokeOffset += 1;
    }
    
    // Build request command words
    u32 cmd1 = _swap32__FUl(/* packed data */);
    u32 cmd2 = _swap32__FUl(/* packed data */);
    
    // Get fightout Pokemon data
    void* outPkmn = fightOutPokemonGetPokemonPtr(fightOutPokemon);
    u32 rndStatus1, rndStatus2;
    fightOutPokemonGetRndStatus(fightOutPokemon, &rndStatus1, &rndStatus2);
    
    rndStatus1 = _swap32__FUl(rndStatus1);
    rndStatus2 = _swap32__FUl(rndStatus2);
    
    u16 outDataId = pokemonBiosGetPokemonDataId(outPkmn);
    outDataId = _swap16__FUs(outDataId);
    
    // Handle special species (Deoxys)
    if (outDataId == 0x181)
    {
        u32 zokusei = fightOutPokemonBiosGetZokuseiDataId(fightOutPokemon, 0);
        u16 zokuseiGba = 0;
        if (zokusei == 0xA) zokuseiGba = 1;
        else if (zokusei == 0xB) zokuseiGba = 2;
        else if (zokusei == 0xF) zokuseiGba = 3;
        zokuseiGba = _swap16__FUs(zokuseiGba);
    }
    
    // Check for Waza select action
    s32 wazaAction = fightOutPokemonCheckFightActionWazaSelect(fightOutPokemon, 0, 0);
    
    // Iterate through moves for banme check
    for (i = 0; i < 4; i++)
    {
        u16 moveId = pokemonBiosGetPokemonWazaDataId(outPkmn, i);
        moveId = _swap16__FUs(moveId);
        u8 pp = pokemonBiosGetPokemonWazaPp(outPkmn, i);
        
        // Call fightSeqSelectDefensePokemonPtr
        _needSelect = 0;
        fightSeqSelectDefensePokemonPtr(fightOutPokemon, moveId, floorId, 
                                         _dummySelect, 1, 0, -1, 
                                         /* callback data */);
        
        if (_needSelect)
        {
            // Set select bit
        }
        
        s32 canOut = fightOutPokemonCheckCanOutOkWazaBanme(fightOutPokemon, i, 1, 0x10);
        if (canOut == 5)
        {
            // Handle special case
        }
    }
    
    // Copy Pokemon data blocks
    memmove(/* dest */, /* src */, /* size */);
    
    // Send battle request
    PKJB_BattleRequest(port - 1, reqData, /* size */);
    gba_SIProbe_ErrorCntClear(port - 1);
    
    // Battle result loop
    while (1)
    {
        s32 fightResult = fightGetFightResultId();
        
        if (fightResult == 1)
        {
            PKJB_ReturnTitle(port - 1);
            return 5;
        }
        
        // Check timer
        if (fightFloorIsUseFightTimerCommand(0) == 1 && fightTimerCommandIsOver() == 1)
        {
            PKJB_ReturnTitle(port - 1);
            return 4;
        }
        
        // Get battle status
        u32 battleStatus;
        s32 battleResult = PKJB_BattleGetStatus(port - 1, &battleStatus);
        
        if (battleResult == 1)
        {
            // Increment error counter
            gba_SIProbe_ErrorCnt[port - 1]++;
            if (gba_SIProbe_ErrorCnt[port - 1] >= 2)
            {
                return -1;
            }
        }
        else
        {
            gba_SIProbe_ErrorCntClear(port - 1);
        }
        
        if (battleResult > 0)
        {
            return battleResult | 0x5;
        }
        else if (battleResult == 0)
        {
            return _swap32__FUl(battleStatus);
        }
        
        GSthreadSwitch();
    }
}
