package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class PickUpItemChoice extends Choice {
    public PickUpItemChoice(String description, Event event, Collectables item ) {
        super(description, event);
        
        this.item = item;
        
    }

    @Override
    public void executeChoice(Character character) {
    	
    	
    	
    	for (int i = 0; i < ((Player) character).getBackpack().length; i ++)
    	{
    			if (((Player) character).getBackpack()[i] == null)
    			{
    				((Player) character).getBackpack()[i] = this.item;
    				return;
    			}
    		
    	}
    

    }
    
    private Collectables item;
}
