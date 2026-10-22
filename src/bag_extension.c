// bag_extension.c
// Authors: MCMi460

#include "wbtypes.h"

#include "gfl/str/string.h"
#include "gfl/g2d/gfl_bg_sys.h"

#include "bag/itemmenu.h"
#include "bag/items.h"

#include "custom_item.h"

/*
    Hook inserts
*/

// Redirect use function to the repel function
u8 BagExt_CanUse(int itemID) {
    // Vanilla
    if (Bag_IsItemRepel(itemID)) return 1;
    if (itemID == 616 || itemID == 617) return 2; // 616 & 617, Light/Dark Stones

    // Check for custom item use
    for (CustomItem* item = customItemList; item->func != NULL; item++)
        if (item->ID == itemID)
            return 1;

    // If none applicable
    return 0;
}

// Execute custom code if the "repel" is our custom item
b32 BagExt_IsItemRepel(int itemID, Bag* bag) {
    itemID &= 0xFFFF; // Replaced code... itemID is a u16

    // Check if we're executing a custom use item
    for (CustomItem* item = customItemList; item->func != NULL; item++) {
        if (item->ID == itemID) {
            // Execute the CustomItemUseFunc
            item->func(bag);

            // Finish and don't run the rest of the repel function
            return false;
        }
    }
    return Bag_IsItemRepel(itemID);
}

// Show the "use" button
int BagExt_GetUseButtonTypeFromParam(void* itemWork, u32 itemField, BagItem* bagItem) {
    // Check if it's a custom item use
    for (CustomItem* item = customItemList; item->func != NULL; item++)
        if (item->ID == bagItem->ItemID)
            return 1; // != 0

    // Otherwise, treat as normal
    return PML_ItemGetParam(itemWork, itemField);
}

/*
    (ported from White2Playground)
    General use methods for your items:
*/

// General use message for using an item
void ItemUse_FinishMessage(Bag* bag) { // References Bag_RepelEffect
    // Display messagebox
    GFL_MsgDataLoadStrbuf(bag->msgData, 0x3f, bag->strBuf1);
    copyVarForText(bag->wordSetSystem, 0, bag->trainerCardWork);
    Bag_LoadItemName(bag, 1, bag->itemID);
    GFL_WordSetFormatStrbuf(bag->wordSetSystem, bag->strBuf2, bag->strBuf1);
    Bag_CreateTextBox(bag, 1);

    // Wait for the player to close the messagebox
    Bag_UpdateStateMachine(bag, Bag_WaitDialogue);
}

// To skip the dialogue box that says you've used the item
void ItemUse_FinishSilent(Bag* bag) { // References Bag_WaitDialogue
    // Clear and redraw
    GFL_BGSysClearScr(G2D_BG3A);
    Bag_DrawWindow(bag);

    // Update view and control for player
    Bag_SetMenuBrightness(bag, true);
    Bag_SetItemWindowState(bag);
}

// Execute an action
void ItemUse_FinishActionExec(Bag* bag, BagActionID action) {
    bag->nextActionID = action;
    Bag_UpdateStateMachine(bag, NULL);
}
