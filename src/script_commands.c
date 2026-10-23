// script_commands.c
// Authors: MCMi460

#include "wbtypes.h"

#include "field/field_script.h"
#include "script_commands.h"

#include "gfl/str/wordset.h"
#include "pml/poke_personal.h"
#include "field/field_sound_system.h"

#include "util.h"

/*
    Gets the ability ID that a specified Pokémon species has in a slot index.

    Headers:
    PKS: pokemon.PokePersonal.GetAbility
    BTR: PokePersonalGetAbility
*/
int PokePersonalGetAbility(ScriptVM* vm, FieldScriptEnv* env) {
    u16* abil      = ScriptReadVar(vm, env);
    u16  species   = ScriptReadAny(vm, env);
    u16  forme     = ScriptReadAny(vm, env);
    u16  idx       = ScriptReadAny(vm, env);

    // Guard max ability slot
    if (idx > 2) *abil = 0;
    // Otherwise, return ability from Personal NARC
    else *abil = PML_PersonalGetParamSingle(species, forme, PERSONAL_ABILITY + idx);

    return 0;
}

/*
    Loads the ability name into the string buffer by ID.

    Headers:
    PKS: system.text.WordSetExt.LoadAbility
    BTR: WordSetAbility
*/
int WordSetAbility(ScriptVM* vm, FieldScriptEnv* env) {
    ScriptWork* work = FieldScriptEnv_GetScriptWork(env);
    WordSet* wordSet = ScriptWork_GetWordSet(work);

    u16 strbufIdx = ScriptReadAny(vm, env);
    u16 abil      = ScriptReadAny(vm, env);

    // Load the ability name to the string buffer
    GFL_WordSetLoadMsg(wordSet, strbufIdx, WORDSET_ABILITIES, abil);

    return 0;
}

/*
    Fades the area's BGM.

    Headers:
    PKS: system.SoundExt.BGMFadeOut
    BTR: WordSetAbility
*/
int BGMFadeOut(ScriptVM* vm, FieldScriptEnv* env) {
    GameSystem* gameSys = FieldScriptEnv_GetGameSystem(env);
    ScriptWork* work = FieldScriptEnv_GetScriptWork(env);
    GameData* gameData = GSYS_GetGameData(gameSys);
    FieldSoundSystem* fldSndSys = GameData_GetFieldSoundSystem(gameData);

    u16 interval = ScriptReadAny(vm, env);

    FieldSnd_SendRequest(fldSndSys, 2, 0, interval, 0);
    FieldSnd_SendRequest(fldSndSys, 7, 0x3E9, 0, 0);

    return 0;
}
