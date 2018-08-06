package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class Player extends Character {
	
	private Collectables[] backpack; 

    public Player(int life, int attack) {
        super(life, attack);
        
        this.backpack = new Collectables [10]; 
        
        //this.backpack[3] = new Health();
        //this.backpack[4] = new Health();
        //this.backpack[5] = new Pistol();
        
    }
    
    public Collectables [] getBackpack()
    {
    	return this.backpack;
    }
    
  
}
