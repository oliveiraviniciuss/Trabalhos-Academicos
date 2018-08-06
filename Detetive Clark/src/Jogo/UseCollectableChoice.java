package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class UseCollectableChoice extends Choice {
	
	private Collectables item;
    
    private String feedback;
    
    private Enemy enemy;
   
	public UseCollectableChoice(String description, Event event, Collectables collectable, Enemy enemy, Player player) {
        super(description, event);
        
        this.item = collectable;
        
        this.enemy = enemy;
       
    }

    @Override
    public void executeChoice(Character character) {
    	
    	for (int i = 0; i < ((Player) character).getBackpack().length; i ++)
    	{
    		if (((Player) character).getBackpack()[i] != null)
    		{
    			if (this.item.description.equalsIgnoreCase(((Player) character).getBackpack()[i].description))
    			{
    				this.item.use((Player) character);
    				
    				((Player) character).getBackpack()[i] = null;
    
    				this.feedback = "Você usou " + item.description;
    				return;
    				
    			}
    		}
    	}
    	
    	this.feedback = "Não há " + item.description + " disponível";
    	
    

    }
    
    public Collectables getItem()
    {
    	return this.item;
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
