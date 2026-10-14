// global_script.h
// Authors: MCMi460

#pragma once

#include "wbtypes.h"

// Custom script data type
STRUCT_DECLARE(CustomScriptEntry)

struct CustomScriptEntry {
    ScriptGlobalTableEntry global;
    const char* path;
};

// Custom script table for global script injection
static CustomScriptEntry customScriptTable[] = {
    {
        .global = {
            .startID   = 10525,
            .endID     = 10527,
            .scrDatID  = 899,
            .textArcID = 3,
            .textDatID = 0,
        },
        .path = "Black1Playground/Globals.ev"
    },
    { .path = NULL, } // Sentinel - don't remove!
};
