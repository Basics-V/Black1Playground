// script_commands.h
// Authors: MCMi460

#pragma once

#include "field/field_script.h"

// Declare funcs
C_DECL_BEGIN

ScriptFunc PokePersonalGetAbility;
ScriptFunc WordSetLoadAbility;

C_DECL_END

// Command set list
static ScriptCall ExtendedCommandSet[] = {
    PokePersonalGetAbility, // 0x261
    WordSetLoadAbility,     // 0x262
};

