package pokemon;

public class PokePersonal {
	/**
	 *	Gets the ability ID that a specified Pokémon species has in a slot index.
	 */
	@ArgAsReturn(argNum = 0)
	static native int GetAbility(int species, int forme, int idx): 0x261;
}
