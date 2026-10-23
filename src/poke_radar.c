// poke_radar.c
// Authors: MCMi460

#include "wbtypes.h"

#include "data/heapid_def.h"

#include "gfl/core/gfl_random.h"

#include "field/field_encount.h"
#include "field/field_script.h"
#include "field/event/event_bgm.h"

#include "poke_radar.h"

#include "util.h"

GameEventReturnCode PokeRadar_Callback(GameEvent* event, u32* state, void* eventData) {
    PokeRadarEvent* radarEvent = (PokeRadarEvent*)eventData;

    // Fetch necessary works...
    EncountSystem* encSys = Field_GetEncountSystem(radarEvent->field);
    EncountState* encState = GameData_GetEncountState(encSys->m_GameData);
    EncData* encData = encSys->m_EncData;
    EffectEncountState* effEncState = (EffectEncountState*)encSys->m_EffectEncountState;

    /* Heavily references UpdatePhenomenon/OVL_21:0x21AA80D */
    switch (*state) {
        case 0: {
            if (
                encSys != NULL && encSys->m_EncData != NULL && encSys->m_EncData->FishingEnable != false &&
                isBadgeObtained(getTrainerCardDataBlkAddress(encSys->m_GameData), 0) &&
                Field_GetResolvedControllerTypeID(encSys->m_Field) == 0
            ) {
                // If a phenomenon already exists
                if ((encState->field_1d & 0xF) != 0) {
                    EncountSystem_CancelPhenomenonCore(encSys, encSys->m_EffectEncountState);
                }

                // Spawn the phenomenon
                positionShakingSpot(encSys, effEncState);
                if (effEncState->maxMapEffects != 0) {
                    (*state)++;
                    break;
                } else {
                    // Failed to find a spot!
                    EventScriptCall_Start(event, POKERADAR_spawnFail, NULL, NULL, HEAPID_FIELDMAP);
                    *state = 3;
                    break;
                }
            }
            // Failed to use the item!
            EventScriptCall_Start(event, POKERADAR_useFailed, NULL, NULL, HEAPID_FIELDMAP);
            *state = 3;
            break;
        }
        case 1:
            // Succeeded to use the item!
            EventScriptCall_Start(event, POKERADAR_useSuccess, NULL, NULL, HEAPID_FIELDMAP);
            (*state)++;
            break;
        case 2:
            while ((encState->field_1d & 0xF) == 0) SpawnPhenomenon(encSys, effEncState);
        case 3:
            return GAMEEVENT_DONE;
    }
    return GAMEEVENT_CONTINUE;
}

// Only encounter Pokémon when interacting with the phenomenon
u32 PokeRadar_HookPhenomenonInteract(u32 max) {
    if (*EventWork_GetWkPtr(GameData_GetEventData(GSYS_GetGameData(g_GameSystem)), POKERADAR_event) == 1)
        return 0;
    return GFL_RandomLCAlt(max);
}

// Restores the field's BGM when a Pokémon is encountered, if the BGM has been overridden
void PokeRadar_RestartBGM(GameSystem* gameSys, u16 fadeOut, u16 fadeIn) {
    GameData* gameData = GSYS_GetGameData(gameSys);

    u16* radarWk = EventWork_GetWkPtr(GameData_GetEventData(gameData), POKERADAR_event);
    if (*radarWk == 1) {
        /* References s009E_BGMChangeMap */
        FieldSoundSystem* fldSndSys = GameData_GetFieldSoundSystem(gameData);
        u16 zoneID = Field_GetPlayerStateZoneID(GSYS_GetField(gameSys));
        u8 season = GameData_GetSeason(gameData);
        u32 bgmID = GetMapBGMIDByPlayerState(gameData, zoneID, season);

        GameEvent_RunCallback(EventBGMChange_Create(gameSys, bgmID, fadeOut, fadeIn));
        FieldSnd_ResumeAmbience(fldSndSys, 2);

        *radarWk = 4;
    }
}

// When cancelling a phenomenon normally (NPCs, Poké Radar, etc...)
void PokeRadar_CancelPhenomenon(EncountSystem* encSys) {
    PokeRadar_RestartBGM(encSys->m_GameSystem, 0x5A, 0x3C);
    EncountSystem_CancelPhenomenonCore(encSys, encSys->m_EffectEncountState);
}

// Force random events to go through our code
GameEvent* PokeRadar_HookWildBattle_RestartBGM(GameSystem* gameSys, GameEvent* parentEvent, GameEventCallback callback, u32 evtDataSize) {
    PokeRadar_RestartBGM(gameSys, 0, 0);
    GameEvent_Create(gameSys, parentEvent, callback, evtDataSize);
}
