#include "wbtypes.h"

#include "system/game_event.h"

#include "field/fieldmap.h"

#include "bag/itemmenu.h"

// Func typedef
typedef GameEvent* (*FieldCommonEventFunc)(Field*, GameSystem*);

// Data structures
STRUCT_DECLARE(FieldActionSys)
STRUCT_DECLARE(FieldActionReturn)
STRUCT_DECLARE(FieldAction)
STRUCT_DECLARE(FieldCommonEventEntry)

// Define data structures
struct FieldActionSys {
    u8 unk1[0x18];
    FieldActionReturn* returnSys;
    u8 unk2[0x50];
    // ...
};

struct FieldAction {
    u8 unk1[0x34];
    BagActionID bagActionID;
    u32 itemID;
    // ...
};

struct FieldCommonEventEntry {
    FieldCommonEventFunc func;
    u32 type;
};

struct FieldActionReturn {
    u8 unk1[0x28];
    u32 returnActionID;
    // ...
};

// Globals
extern FieldCommonEventEntry FIELD_COMMON_EVENTS[6];

// Functions
C_DECL_BEGIN

extern u32 EventFieldBag_HandleReturnAction(FieldActionSys*, FieldAction*);

C_DECL_END
