// field_action_extension.c
// Authors: MCMi460

#include "wbtypes.h"

#include "field/field_action.h"

#include "bag_extension.h"
#include "custom_item.h"

#include "util.h"

u32 FldActExt_BagReturnAction(FieldActionSys* fieldActionSys, FieldAction* actionData) {
    // Check if it's our custom BagActionID
    if (actionData->bagActionID == BAG_CUSTOM_ACTION) {
        for (CustomItem* item = customItemList; item->func != NULL; item++) {
            if (item->ID == actionData->itemID) {
                fieldActionSys->returnSys->returnActionID = item->ID + NELEMS(FIELD_COMMON_EVENTS);
                return 3; // Use item in field
            }
        }
    }
    return EventFieldBag_HandleReturnAction(fieldActionSys, actionData);
}

GameEvent* FldActExt_CallEventFunc(u32 eventType, GameSystem* gameSys, Field* field) {
    // Check if we are calling a custom field common event
    if (eventType >= NELEMS(FIELD_COMMON_EVENTS)) {
        eventType -= NELEMS(FIELD_COMMON_EVENTS);
        for (CustomItem* item = customItemList; item->func != NULL; item++)
            if (item->activate != NULL && item->ID == eventType) {
                return item->activate(field, gameSys);
            }
        return NULL;
    }
    return FIELD_COMMON_EVENTS[eventType].func(field, gameSys);
}
