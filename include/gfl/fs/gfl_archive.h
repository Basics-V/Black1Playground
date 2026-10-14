// Sourced from ds-pokemon-hacking/swan/swantypes.h
#include "wbtypes.h"

#include "nds/fs.h"
#include "gfl/core/gfl_heap.h"

C_DECL_BEGIN

extern void* GFL_ArcSysReadHeapNewLZ(int arcId, u16 datId, b32 compressed, HeapID heapId);

C_DECL_END
