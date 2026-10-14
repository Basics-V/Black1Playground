#pragma once

#include "wbtypes.h"

#include "system/vm.h"
#include "system/gamesystem.h"

#include "gfl/str/wordset.h"

// Defs
#define FLDSCRCMD_SIZE 0x261

// Field script data structures
STRUCT_DECLARE(ScriptWork)
STRUCT_DECLARE(FieldScriptEnv)
STRUCT_DECLARE(ScriptGlobalTableEntry)
STRUCT_DECLARE(OpcodeGuardEntry)

// Function types
typedef int (ScriptFunc)(ScriptVM*, FieldScriptEnv*);
typedef ScriptFunc* ScriptCall;

// Struct definitions
struct ScriptGlobalTableEntry {
    u16 startID;
    u16 endID;
    u16 scrDatID;
    u16 textArcID;
    u16 textDatID;
};

struct OpcodeGuardEntry {
    u8 guard1: 1;
    u8 guard2: 1;
    u8 guard3: 1;
};

// Script table constants
extern ScriptGlobalTableEntry GLOBAL_SCRIPT_TABLE[0x2E];
extern ScriptCall EVCMD_TABLE;

// Script functions
C_DECL_BEGIN

u16 FieldScript_ResolveSCRID(u16, u16, u16*, u16*, u16*);
b32 FieldScript_OpcodeGuard(ScriptVM*, FieldScriptEnv*, GameSystem*, u16);

GameSystem* ScriptWork_GetGameSystem(ScriptWork*);
ScriptWork* FieldScriptEnv_GetScriptWork(FieldScriptEnv*);
u16* ScriptReadVar(ScriptVM*, FieldScriptEnv*);
u16 ScriptReadAny(ScriptVM*, FieldScriptEnv*);

WordSet* ScriptWork_GetWordSet(ScriptWork*);

C_DECL_END
