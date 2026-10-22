// poke_radar.c
// Authors: MCMi460

#include "wbtypes.h"

#include "poke_radar.h"

#include "util.h"

//TODO: Poké Radar
GameEventReturnCode PokeRadarCallback(GameEvent* event, u32* state, void* eventData) {
    PokeRadarEvent* radarEvent = (PokeRadarEvent*)eventData;

    Mi4_Printf("HOLLOW IMPLEMENTATION.\n");

    return GAMEEVENT_DONE;
}
