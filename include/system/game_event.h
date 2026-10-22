// Sourced from ds-pokemon-hacking/swan

#include "wbtypes.h"

#include "system/gamesystem.h"

STRUCT_DECLARE(GameEvent)

ENUM_DECLARE_EX(GameEventReturnCode, u32)
enum GameEventReturnCode: u32 {
    GAMEEVENT_CONTINUE = 0x0,
    GAMEEVENT_DONE     = 0x1
};

// Functions
typedef GameEventReturnCode (*GameEventCallback)(GameEvent*, u32*, void*);

C_DECL_BEGIN

extern GameEvent* GameEvent_Create(GameSystem* gsys, GameEvent* parentEvent, GameEventCallback callback, u32 evtDataSize);
extern void* GameEvent_GetData(GameEvent* event);
extern u32* GameEvent_GetStatePtr(GameEvent* event);
extern GameEvent* GameEvent_GetReturnEvent(GameEvent* event);
extern GameSystem* GameEvent_GetGameSystem(GameEvent* event);
extern GameEventReturnCode GameEvent_RunCallback(GameEvent* event);
extern void GameEvent_Transplant(GameEvent* event, GameEventCallback callback, u32 size);
extern void GameEvent_Replace(GameEvent* nowEvent, GameEvent* event);
extern void GameEvent_ChainNext(GameEvent* currentEvent, GameEvent* event);
extern void GameEvent_Free(GameEvent* event);

C_DECL_END

// Structures
struct GameEvent {
    GameEvent* ReturnEvent;
    GameEventCallback Callback;
    u32 EventState;
    void* EventData;
    GameSystem* m_GameSystem;
};
