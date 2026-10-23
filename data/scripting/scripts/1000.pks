import pokemon.PokePersonal;
import pokemon.PokeParty;
import system.text.WordSetExt;
import event.actors.Actor;
import event.dialogs.Message;
import pokescript.vm.VM;
import system.EventFlags;
import system.EventWorks;
import system.Input;
import system.Runtime;
import system.Sound;
import system.text.WordSet;

// Note: All script IDs must be within the bounds set in global_script.h
public class AbilityTester {
    // 10525
    public static void abilityGameGuesser() {
        for (int i = 0; i < 6; i++) {
            int species = PokeParty.GetSpecies(i);
            int forme = PokeParty.GetForme(i);

            for (int n = 0; n < 3; n++) {
                int abilityNum = PokePersonal.GetAbility(species, forme, n);

                WordSet.LoadPokeSpecies(0, species);
                WordSet.LoadNumber(1, n, 3);
                WordSetExt.LoadAbility(2, abilityNum);

                Message.Actor(1024, 0, 0, 0);
                Input.LastKeyWait();
                Message.CloseActor();
            }
        }
    }
}
