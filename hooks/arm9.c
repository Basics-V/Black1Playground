// Target new plugin command set
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_VM_Run_0x44(void) {
    __asm__ volatile (
        "BL ScriptPlugin_ReadCommandID\n\t"
    );
}
