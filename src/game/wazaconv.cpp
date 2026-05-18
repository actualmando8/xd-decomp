// Decompiled from wazaconv.cpp (0x8006C320 - 0x8006C504)
// PowerPC 750CL / Gekko CPU - Metrowerks CodeWarrior
// Calling convention: r3-r4 args, r3 return, LR saved on stack
// Total size: 0x1E4 bytes

#include "global.h"

// Forward declarations for external functions
extern void* heroBiosGetPokemonPtr(u32 heroId, u16 index);
extern u16 pokemonBiosGetPokemonWazaDataId(void* pkmn, u16 index);
extern void* wazaDataBiosGetPtr(u16 wazaId);
extern const unsigned short* wazaDataBiosGetDoc(void* wazaData);
extern const unsigned short* GSmsgGetGSchar(const unsigned short* msg);
extern u32 GBAMakeFromGSchar(u8* out, const unsigned short* in, u32 langareaId);
extern u32 gamedataGetStatus(u32 statusId);

// ============================================================================
// convline
// Address: 0x8006C468 | Size: 0x9C
// Args: r3=output buffer, r4=pointer to source string pointer
// Returns: r3 = number of bytes written
// Converts GS char string to GBA format. Local static function.
// ============================================================================
static u32 convline__FPUcPPCUs(u8* out, const unsigned short** in)
{
    u32 count = 0;
    u16 chars[0x60];  // buffer for converted characters
    
    while (1)
    {
        u16 ch = **in;
        if (ch == 0 || ch == 0xFFFF)
            break;
        
        if (count < 0x50)
        {
            chars[count] = ch;
            count++;
        }
        
        *in = *in + 1;
    }
    
    // Null-terminate the char buffer
    chars[count] = 0;
    
    // Get language area ID from status data
    u32 langareaId = gamedataGetStatus(5);
    
    // Convert to GBA format
    GBAMakeFromGSchar(out, chars, langareaId);
    
    // Return number of bytes written
    return count;  // NOTE: Actual return seems to be based on GBAMakeFromGSchar
}

// ============================================================================
// GetWazaDocGBA
// Address: 0x8006C3AC | Size: 0xBC
// Args: r3=output buffer, r4=waza data ID
// Returns: r3 = 0
// Converts move documentation text to GBA format.
// ============================================================================
void GetWazaDocGBA(u8* out, u16 wazaId)
{
    void* wazaData;
    const unsigned short* docPtr;
    
    memset(out, 0, 0x50);
    
    wazaData = wazaDataBiosGetPtr(wazaId);
    if (wazaData == 0)
        return;
    
    docPtr = wazaDataBiosGetDoc(wazaData);
    docPtr = GSmsgGetGSchar(docPtr);
    
    // Convert first line
    convline__FPUcPPCUs(out, &docPtr);
    
    // Check for line break marker (0xFFFF)
    if (**(const unsigned short**)(&docPtr) == 0xFFFF)
    {
        // Insert line break byte (0xFE)
        *out = 0xFE;
        out++;
        docPtr = docPtr + 1;  // skip the 0xFFFF marker
        convline__FPUcPPCUs(out, &docPtr);
    }
    
    // Null-terminate
    *out = 0xFF;
}

// ============================================================================
// wazaconv
// Address: 0x8006C320 | Size: 0x8C
// Args: r3=hero ID, r4=output buffer
// Returns: r3 = 0 (or early return if valid move found)
// Converts move data for all Pokemon in party to GBA format.
// Iterates through 6 party slots, 4 moves each.
// ============================================================================
u32 wazaconv(u32 heroId, u8* out)
{
    u32 i;
    u32 j;
    
    for (i = 0; i < 6; i++)
    {
        void* pkmn = heroBiosGetPokemonPtr(heroId, (u16)i);
        
        for (j = 0; j < 4; j++)
        {
            u16 wazaId = pokemonBiosGetPokemonWazaDataId(pkmn, (u16)j);
            
            if (GetWazaDocGBA(out, wazaId) != 0)
            {
                return 0;
            }
            
            out += 0x50;
        }
    }
    
    return 0;
}
