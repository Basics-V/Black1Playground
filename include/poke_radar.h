// poke_radar.h
// Authors: MCMi460

#include "wbtypes.h"

#include "system/game_event.h"

#include "field/fieldmap.h"

// Data structure decls
STRUCT_DECLARE(PokeRadarEvent)

// Data structure defs
struct PokeRadarEvent {
    Field* field;
    u8 flags;
};

// Prototypes
C_DECL_BEGIN

extern GameEventReturnCode PokeRadarCallback(GameEvent*, u32*, void*);

C_DECL_END
