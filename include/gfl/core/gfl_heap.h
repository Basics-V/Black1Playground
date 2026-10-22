// Sourced from ds-pokemon-hacking/swan
#include "wbtypes.h"

typedef u16 HeapID;

C_DECL_BEGIN

extern void* GFL_HeapAllocate(HeapID heapId, u32 size, b32 calloc, const char* sourceFile, u16 lineNo);
extern void GFL_HeapFree(void* heap);

C_DECL_END
