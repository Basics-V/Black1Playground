#include "wbtypes.h"

#include "system/game_data.h"

#include "gfl/str/string.h"

#include "save/savedata_bag.h"

// Data structures
STRUCT_DECLARE(Bag)

// Types
typedef u32 BagActionID;
typedef void (Bag_StateFunc)(Bag*);

// Structure defs
struct Bag {
    GameData* gameData;
    u8 unk1[4];
    void* trainerCardWork;
    u8 unk2[0x510];
    void* msgData;
    void* wordSetSystem;
    StrBuf* strBuf1;
    StrBuf* strBuf2;
    u8 unk3[0x318];
    BagActionID nextActionID;
    u32 bagItemActions;
    u32 itemID;
    // ...
};

// Functions
C_DECL_BEGIN

extern b32 Bag_IsItemRepel(int);
extern Bag_StateFunc Bag_WaitDialogue;
extern void Bag_UpdateStateMachine(Bag*, Bag_StateFunc);
extern void Bag_SetItemWindowState(Bag*);
extern void Bag_LoadItemName(Bag*, int, u32);
extern void Bag_CreateTextBox(Bag*, int);
extern void Bag_DrawWindow(Bag*);
extern void Bag_SetMenuBrightness(Bag*, b32);
extern void Bag_SubItem(Bag*, u16);

C_DECL_END
