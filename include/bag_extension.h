#include "wbtypes.h"

#include "bag/itemmenu.h"

#define BAG_CUSTOM_ACTION 0x15

// Functions start
C_DECL_BEGIN

extern void ItemUse_FinishMessage(Bag*);
extern void ItemUse_FinishSilent(Bag*);
extern void ItemUse_FinishActionExec(Bag*, BagActionID);

C_DECL_END
