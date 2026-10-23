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
            .endID     = 10525,
            .scrDatID  = 1000,
            .textArcID = 3,
            .textDatID = 1000
        },
        .path = NULL
    },
    {
        .global = {
            .startID   = 10526,
            .endID     = 10528,
            .scrDatID  = 1001,
            .textArcID = 3,
            .textDatID = 1001
        },
        .path = NULL
    }
};
