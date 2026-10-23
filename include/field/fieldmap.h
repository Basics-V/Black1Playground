// Sourced from ds-pokemon-hacking/swan

#include "wbtypes.h"

#include "field_encount.h"

STRUCT_DECLARE(Field)

C_DECL_BEGIN

extern EncountSystem* Field_GetEncountSystem(Field*);
extern u32 Field_GetResolvedControllerTypeID(Field*);
extern u16 Field_GetPlayerStateZoneID(Field*);

C_DECL_END
