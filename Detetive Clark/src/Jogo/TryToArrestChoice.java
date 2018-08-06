package Jogo;

import java.util.Random;

/**
 * Created by filipebraida on 31/05/16.
 */
public class TryToArrestChoice extends Choice {
	
	private Enemy enemy;
    private String feedback= "";
    
    public TryToArrestChoice(String description, Event event, Enemy enemy) {
        super(description, event);

        this.enemy = enemy;    
        
    }
   
	@Override
    public void executeChoice(Character character) {
    	
    	Random gerador = new Random();
        
        if (gerador.nextInt(2) == 1 && enemy.getLife() < 11)
        {
        	enemy.setArrested(true);
        }
        else
        {
        	character.takeDamage(enemy.getAttack());
        	feedback = "\nJohnny é ágil, não deu pra prendê-lo... Talvez quando estiver vulnerável?";
        }
    
    }
    
    public String getFeedback()
    {
    	return this.feedback;
    }
    
    public Enemy getEnemy()
    {
    	return this.enemy;
    }

}
