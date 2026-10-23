// Wrap EncountSystem_CancelPhenomenonCore and restart BGM
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_EncountSystem_CancelPhenomenon(void) {
    __asm__ volatile (
        "LDR R3, =PokeRadar_CancelPhenomenon\n\t"
        "BX R3\n\t"
    );
}

// Force random events to go through our code
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_CreateRandomPhenomenonEvent_0xb4(void) {
    __asm__ volatile (
        "BL EncountSystem_CancelPhenomenon\n\t"
    );
}
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_CreateRandomPhenomenonEvent_0xc6(void) {
    __asm__ volatile (
        "BL EncountSystem_CancelPhenomenon\n\t"
    );
}

// Force Poké Radar Phenomenons to be encounters
__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_CreateRandomPhenomenonEvent_0x68(void) {
    __asm__ volatile (
        "BL PokeRadar_HookPhenomenonInteract\n\t"
    );
}
