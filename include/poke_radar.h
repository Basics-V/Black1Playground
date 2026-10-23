// poke_radar.h
// Authors: MCMi460

#include "wbtypes.h"

#include "system/game_event.h"

#include "field/fieldmap.h"

// Script IDs
#define POKERADAR_useFailed  10526
#define POKERADAR_spawnFail  10527
#define POKERADAR_useSuccess 10528

// Eventworks
#define POKERADAR_event 0x4010

// Data structure decls
STRUCT_DECLARE(PokeRadarEvent)

// Data structure defs
struct PokeRadarEvent {
    Field* field;
};

// Prototypes
C_DECL_BEGIN

extern GameEventReturnCode PokeRadar_Callback(GameEvent*, u32*, void*);

C_DECL_END
