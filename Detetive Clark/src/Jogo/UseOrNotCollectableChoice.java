package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class UseOrNotCollectableChoice extends Choice {
	
	private Collectables item;
    
    private Enemy enemy;
    
   
    
    public UseOrNotCollectableChoice(String description, Event event, Collectables collectable,Enemy enemy, Player player) {
        super(description, event);
        
        this.item = collectable;
        this.enemy = enemy;
        

        
      
        
        
    }

    @Override
    public void executeChoice(Character character) {
    	
    

    }
    
    public Collectables getItem()
    {
    	return this.item;
    }
    
    public Enemy getEnemy()
    {
    	return this.enemy;
    }
    
    
}
