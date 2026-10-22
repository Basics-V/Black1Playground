#include "wbtypes.h"

STRUCT_DECLARE(StrBuf);

struct StrBuf { // Paideieitor/PW2Code/Headers/defs.h
    u16 charCapacity;
    u16 charCount;
    u32 magic;
    u16 string[];
};

// String functions
C_DECL_BEGIN

extern void GFL_MsgDataLoadStrbuf(void*, int, StrBuf*);
extern void copyVarForText(void*, int, void*);
extern void GFL_WordSetFormatStrbuf(void*, StrBuf*, StrBuf*);

C_DECL_END
