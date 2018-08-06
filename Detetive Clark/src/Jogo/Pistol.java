package Jogo;
import java.util.Random;



public class Pistol extends Collectables {
	
	private int attack;
	
	public void use(Player player)
	{
		player.improveAttack(this.attack);
	}
	
	
	Pistol()
	{
		Random gerador = new Random();
		
		this.attack = gerador.nextInt(5);
		
		while (this.attack <= 1)
		{
			this.attack = gerador.nextInt(5);
		}
		
		description = "Arma";
		
		
		
	}
	

	public int getAttack()
	{
		return this.attack;
	}
}
