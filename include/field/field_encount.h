// Sourced from ds-pokemon-hacking/swan
#pragma once
#include "wbtypes.h"

STRUCT_DECLARE(EncountState)
STRUCT_DECLARE(EncountSystem)

#include "system/gamesystem.h"
#include "system/game_data.h"

#include "field/fieldmap.h"
#include "field/field_encount_data.h"
#include "field/field_effect_encount_state.h"

C_DECL_BEGIN

extern void SpawnPhenomenon(EncountSystem*, EffectEncountState*);
extern void positionShakingSpot(EncountSystem*, EffectEncountState*);
extern void EncountSystem_CancelPhenomenonCore(EncountSystem*, EffectEncountState*);

C_DECL_END

struct EncountState {
    u8 unk1[0x1d];
    u8 field_1d;
};

struct EncountSystem {
    Field* m_Field;
    GameSystem* m_GameSystem;
    GameData* m_GameData;
    EncData* m_EncData;
    EffectEncountState* m_EffectEncountState;
};
