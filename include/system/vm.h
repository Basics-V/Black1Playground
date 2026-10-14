#include "wbtypes.h"

// Declare VM structure
STRUCT_DECLARE(ScriptVM)
STRUCT_DECLARE(ScriptVMSetup)

// Function types
typedef int (*VMCommand)(ScriptVM*, void*);
typedef b32 (*VMCallbackVerifier)(ScriptVM*, void*, void*, u16);
typedef bool (*VMNativeCallback)(ScriptVM*, void*);

// Data structures
struct ScriptVMSetup {
    u16 StackCapacity;
    u16 VMVarCount;
    VMCommand* CommandSet;
    u32 CommandSetSize;
};
struct ScriptVM {
    ScriptVMSetup VMSetup;
    // ...
};

// VM functions
C_DECL_BEGIN

void VM_SetCallbackVerifier(ScriptVM*, VMCallbackVerifier, void*);
void VM_SetNativeCallback(ScriptVM*, VMNativeCallback);
u16 VM_Read16(ScriptVM*);

C_DECL_END
