// custom_item.c
// Authors: MCMi460

#include "wbtypes.h"

#include "nds/mem.h"

#include "gfl/snd/se.h"

#include "bag_extension.h"
#include "custom_item.h"

#include "util.h"

// Custom item function prototypes
CustomItemUse    BlackFluteUse;
CustomItemUse    PokeRadarUse;
CustomItemActive PokeRadarActivate;

// DEFINE NEW ITEMS HERE
CustomItem customItemList[] = {
    {
        .ID       = 68,
        .func     = &BlackFluteUse,
        .activate = NULL
    },
    {
        .ID       = 431,
        .func     = &PokeRadarUse,
        .activate = &PokeRadarActivate
    },
    { .func = NULL, } // Sentinel - don't remove!
};

/*
    Black Flute:
        Play a whistle sound effect when used from the bag!
    Additional source: N/A
*/
void BlackFluteUse(Bag* bag) {
    Mi4_Printf("Black Flute has been used!\n");

    // Play a whistle sound effect
    GFL_SndSEPlay(1533); // 1757 could also work

    // Finish with a messagebox
    ItemUse_FinishMessage(bag);
}

/*
    Poké Radar:
        Leave bag and start a GameEvent that spawns a
        phenomenon and calls a script to display
        with the player.
    Additional source: poke_radar.c
*/
#include "poke_radar.h"

void PokeRadarUse(Bag* bag) {
    Mi4_Printf("Poké Radar has been used!\n");

    // Close the bag to prepare for our FieldAction
    ItemUse_FinishActionExec(bag, BAG_CUSTOM_ACTION);
}

GameEvent* PokeRadarActivate(Field* field, GameSystem* gameSys) {
    // Setup Phenomenon Poké Radar Event
    GameEvent* event = GameEvent_Create(gameSys, NULL, PokeRadarCallback, sizeof(PokeRadarEvent));
    PokeRadarEvent* eventData = (PokeRadarEvent*)GameEvent_GetData(event);
    sys_memset(eventData, 0, sizeof(PokeRadarEvent));
    eventData->field = field;
    return event;
}
