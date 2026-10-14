// script_plugin.c
// Authors: MCMi460

#include "wbtypes.h"
#include "system/vm.h"
#include "field/field_script.h"

#include "script_commands.h"
#include "file_handler.h"
#include "util.h"

// Extend the opcode guard (i.e. allow new command IDs, otherwise handle normally)
b32 ScriptPlugin_ExtendOpcodeGuard(ScriptVM* vm, FieldScriptEnv* env, GameSystem* gameSys, u16 opcode) {
    if (opcode >= FLDSCRCMD_SIZE)
        return opcode < FLDSCRCMD_SIZE + NELEMS(ExtendedCommandSet);
    return FieldScript_OpcodeGuard(vm, env, gameSys, opcode);
}

// Shift the VM's command table dynamically to load new commands
u16 ScriptPlugin_ReadCommandID(ScriptVM* vm) {
    const ScriptCall* ExtensionSetStart = ExtendedCommandSet - FLDSCRCMD_SIZE;
    u16 cmdOP = VM_Read16(vm);

    // Reset shifted command set if it persists
    if ((ScriptCall*)vm->VMSetup.CommandSet == ExtensionSetStart)
        vm->VMSetup.CommandSet = (VMCommand*)&EVCMD_TABLE;

    // Shove our command's address right in the running VM's path
    if (cmdOP >= FLDSCRCMD_SIZE && (ScriptCall*)vm->VMSetup.CommandSet == &EVCMD_TABLE)
        vm->VMSetup.CommandSet = (VMCommand*)ExtensionSetStart;

    return cmdOP;
}
