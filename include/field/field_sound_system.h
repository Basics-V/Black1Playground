// Sourced from ds-pokemon-hacking/swan

#include "wbtypes.h"

STRUCT_DECLARE(FieldSoundSystemRequest)
STRUCT_DECLARE(FieldSoundSystem)

C_DECL_BEGIN

extern void FieldSnd_SendRequest(FieldSoundSystem*, u32, u32, u16, u16);
extern void FieldSnd_ResumeAmbience(FieldSoundSystem*, int);

C_DECL_END
