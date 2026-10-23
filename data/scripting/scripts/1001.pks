import system.Runtime;
import system.text.WordSet;
import event.dialogs.Message;
import system.Sound;
import system.EventWorks;
import event.Effects;
import event.actors.Player;
import system.Field;
import system.Input;
import system.Runtime;

import system.SoundExt;

#include "poke_radar.h"

// Note: All script IDs must be within the bounds set in global_script.h
public class PokeRadar {
    // 10526
    public static void useFailed() {
        WordSet.LoadPlayerName(0);
        systemMessage(0);
        Runtime.FinishSubEvents();
    }

    // 10527
    public static void spawnFail() {
        if (EventWorks.Get(POKERADAR_event) == 0) {
            useCutscene();
        } else {
            SoundExt.BGMFadeOut(60);
            Sound.SEPlay(1599);
        }
        EventWorks.Set(POKERADAR_event, 4);

        Message.System(2, 0);
        Runtime.Sleep(30);
        Message.CloseAll();
        Sound.SEStop();

        Field.PlayMapBGM();
        systemMessage(4);

        Runtime.FinishSubEvents();
    }

    // 10528
    public static void useSuccess() {
        int radarWk = EventWorks.Get(POKERADAR_event);
        if (radarWk == 2) {
            return useFailed();
        } else if (radarWk == 0) {
            useCutscene();
            EventWorks.Set(POKERADAR_event, 1);
        } else if (radarWk == 4) {
            SoundExt.BGMFadeOut(60);
            EventWorks.Set(POKERADAR_event, 1);
            radarWk = 0;
            Sound.SEPlay(1599);
        }

        if (radarWk != 0) {
            Sound.SEPlay(1599);
        }
        Message.System(2, 0);
        Runtime.Sleep(30);
        Message.CloseAll();
        Sound.SEStop();

        Sound.SEPlay(2060);
        Runtime.Sleep(20);
        Sound.SEStop();

        if (radarWk == 0) {
            Sound.BGMPlay(1068);
        }
        systemMessage(3);

        Runtime.FinishSubEvents();
    }

    static void useCutscene() {
        SoundExt.BGMFadeOut(60);

        Player.SetSpecialSequence(16);
        UseItemAction(255);

        WordSet.LoadPlayerName(0);
        systemMessage(1);

        int radarWk = EventWorks.Get(POKERADAR_event);
        EventWorks.Set(POKERADAR_event, 5); // For special effect

        Sound.SEPlay(1599);
        Effects.Play(50);

        EventWorks.Set(POKERADAR_event, radarWk); // Reset special effect

        Player.SetSpecialSequence(8);
    }

    static void systemMessage(int msgID) {
        Message.System(msgID, 0);
        Input.LastKeyWait();
        Message.CloseAll();
    }

    static meta void UseItemAction(int actorID): VActionSequence {
        DoItemGetHop(1);
    }

    static native void DoItemGetHop(int amount): 0x9a;
}
