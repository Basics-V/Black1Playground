#include "wbtypes.h"
#include "util.h"

// Hook our script ID checker
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FieldScript_CheckSCRID(void) {
    __asm__ volatile (
        "LDR R3, =GlobalScript_CheckScriptID\n\t"
        "BX R3\n\t"
    );
}

// Hook our script ID resolver function
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FieldScript_CreateVM_0x62(void) {
    __asm__ volatile (
        "BL GlobalScript_ResolveScriptID\n\t"
    );
}

// Hook our script file loader function
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FieldScript_LoadData(void) {
    __asm__ volatile (
        "LDR R3, =GlobalScript_LoadData\n\t"
        "BX R3\n\t"
    );
}

// Extend the command set size to include our command set plugin
#include "script_commands.h"
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_EVCMD_MAX(void) {
    __asm__ volatile (
        // FLDSCRCMD_SIZE: Default command set size
        ".word %c0"
        :: "i" (FLDSCRCMD_SIZE + NELEMS(ExtendedCommandSet))
    );
}

// Load our custom opcode guard
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FieldScript_AttachOpcodeGuard_0x18(void) {
    __asm__ volatile (
        ".word " STR(ScriptPlugin_ExtendOpcodeGuard)
    );
}

// Hook the bag's return function to inject our custom return action
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_FIELD_PROC_LINK_LIST_0x28(void) {
    __asm__ volatile (
        ".word " STR(FldActExt_BagReturnAction)
    );
}

// Wrapper CallFieldCommonEventFunc to substitute our custom items' functions
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_CallFieldCommonEventFunc(void) {
    __asm__ volatile (
        "LDR R3, =FldActExt_CallEventFunc\n\t"
        "BX R3\n\t"
    );
}

// Force random events to go through our code
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_EventWildBattleCall_CreateCore_0x10(void) {
    __asm__ volatile (
        "BL PokeRadar_HookWildBattle_RestartBGM\n\t"
    );
}
