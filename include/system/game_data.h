// Sourced from ds-pokemon-hacking/swan
#include "wbtypes.h"

#include "save/savedata_trainercard.h"
#include "save/savedata_eventwork.h"

#include "field/field_sound_system.h"
#include "field/field_encount.h"

STRUCT_DECLARE(GameData)

C_DECL_BEGIN

extern FieldSoundSystem* GameData_GetFieldSoundSystem(GameData*);
extern TrainerCardData* getTrainerCardDataBlkAddress(GameData*);
extern EncountState* GameData_GetEncountState(GameData*);
extern EventWorkSave* GameData_GetEventData(GameData*);

extern u8 GameData_GetSeason(GameData*);

extern u16 GetMapBGMIDByPlayerState(GameData*, u16, u8);

C_DECL_END
