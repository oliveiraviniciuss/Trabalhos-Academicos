package Jogo;

public class Health extends Collectables {

	public void use (Player player)
	{
		player.recoverLife(5);
	}
	
	Health()
	{
		description = "MedKit";
	}
	 
}
