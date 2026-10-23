// Sourced from ds-pokemon-hacking/swan
#include "wbtypes.h"

#include "system/game_data.h"

#include "field/fieldmap.h"

STRUCT_DECLARE(GameSystem)

extern GameSystem* g_GameSystem;

C_DECL_BEGIN

extern GameData* GSYS_GetGameData(GameSystem*);
extern Field* GSYS_GetField(GameSystem*);

C_DECL_END
