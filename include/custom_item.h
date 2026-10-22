// custom_item.h
// Authors: MCMi460

#include "wbtypes.h"

#include "system/game_event.h"

#include "bag/itemmenu.h"

#include "field/fieldmap.h"

STRUCT_DECLARE(CustomItem)

// Functions
typedef Bag_StateFunc CustomItemUse;
typedef GameEvent* (CustomItemActive)(Field*, GameSystem*);

// Data types
struct CustomItem {
    u32 ID;
    CustomItemUse* func;
    CustomItemActive* activate;
};

// Global list of custom items
extern CustomItem customItemList[];
