// Sourced from ds-pokemon-hacking/swan
#pragma once
#include "wbtypes.h"

STRUCT_DECLARE(WildEncSlot)
STRUCT_DECLARE(EncData)

ENUM_DECLARE_EX(EncountType, u32)
enum EncountType: u32 {
    ENCTYPE_GRASS,
    ENCTYPE_GRASS_RARE,
    ENCTYPE_GRASS_SHAKING,
    ENCTYPE_SURF,
    ENCTYPE_SURF_RARE,
    ENCTYPE_FISHING,
    ENCTYPE_FISHING_RARE,
    ENCTYPE_MAX
};

C_DECL_BEGIN

C_DECL_END

struct WildEncSlot {
    u16 species:11;
    u8 forme:5;
    char LvMin;
    char LvMax;
};

struct EncData {
    u8 UserData[ENCTYPE_MAX];
    u8 Flags:7;
    b32 FishingEnable:1;
    WildEncSlot Slots[56];
};
