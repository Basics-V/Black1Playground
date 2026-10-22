__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_Bag_CanUse(void) {
    __asm__ volatile (
        "LDR R3, =BagExt_CanUse\n\t"
        "BX R3\n\t"
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_Bag_RepelEffect_0x8(void) {
    __asm__ volatile (
        "MOV R1,R5\n\t"
        "NOP\n\t"
        "BL BagExt_IsItemRepel\n\t"
    );
}

__attribute__((naked, target("thumb"), aligned(2)))
void FULL_COPY_Bag_GetUseButtonType_0xc(void) {
    __asm__ volatile (
        "BL BagExt_GetUseButtonTypeFromParam\n\t"
    );
}
