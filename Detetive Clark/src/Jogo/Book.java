package Jogo;

import java.util.ArrayList;
import java.util.Collection;


/**
 * Created by filipebraida on 31/05/16.
 */
public class Book {

    public Book(String description, Event eventInitial, Player player) {
        this.eventInitial = eventInitial;
        this.description = description;
        this.player = player;

        this.resetHistory();
    }

    public void resetHistory() {
        this.eventActually = this.eventInitial;
    }

    public String showHistory() {
        return this.eventActually.history();
    }

    public boolean isTheEnd() {
        return this.eventActually.isEndEvent();
    }

    public String showHistoryBook(){
        return this.description;
    }

    @SuppressWarnings({ "unchecked", "rawtypes" })
	public boolean nextEvent(int number) {
        Choice choice = this.selectChoice(number);
        int item = 0;

        if(choice != null) {
            choice.executeChoice(player);
            this.executedchoice = choice;
            
            
           if(choice instanceof BattleChoice && player.isAlive())
            {
          
            		BattleChoice battlechoice = (BattleChoice) choice;
            		
            		Collection proceed = new ArrayList<Choice>();
            		
            		Choice next = new BlankChoice("Continuar", choice.getEvent());
            		
            		proceed.add(next);
            		
            		Event stillFighting = new BlankEvent("Você :" + this.player.showState() + "\nInimigo :" + battlechoice.getEnemy().showState(), this.eventActually.nextEvents());
            		Event won = new BlankEvent("Você ganhou!!", proceed);
            	

            		
            		
            		if (((BattleChoice)choice).getEnemy().isAlive())
            		this.eventActually =  stillFighting;
            		
            		else
            			this.eventActually = won;
            		
            		
            		
            		this.eventActually.applyHistory(player);
            		
            		this.pastEvent = this.eventActually;
            		
           
            }
            
            else if(choice instanceof TryToArrestChoice)
            {
            	TryToArrestChoice runChoice = (TryToArrestChoice) choice;
            	
            	Collection proceed = new ArrayList<Choice>();
        		
            	Choice next = new BlankChoice("Continuar", choice.getEvent());
        		
            	proceed.add(next);
        		
        		Event stillFighting = new BlankEvent("Você :" + this.player.showState() + "\nInimigo :" + runChoice.getEnemy().showState() + runChoice.getFeedback(), this.eventActually.nextEvents());
        		Event won = new BlankEvent("Você o prendeu!!", proceed);
        		
        		
        		if (!((TryToArrestChoice)choice).getEnemy().isArrested())
        			this.eventActually = stillFighting;        		
        		else
        			this.eventActually = won;
        		
        		if(player.getLife() <= 0) {
        			 Event gameOver = new BlankEvent("Game Over", new ArrayList<Choice>());
                     this.eventActually = gameOver;
        		}
        		
     
        		this.eventActually.applyHistory(player);
            	
            	
            }
            
            else if (choice instanceof UseCollectableChoice)
            {
            	UseCollectableChoice chooseChoice = (UseCollectableChoice) choice;
            	
            	Event stillFighting = new BlankEvent("Você :" + this.player.showState() + "\nInimigo :" + chooseChoice.getEnemy().showState() + "\n" + chooseChoice.getFeedback(), this.pastEvent.nextEvents());
        		
        		this.eventActually = stillFighting;
        		this.eventActually.applyHistory(player);
            }
            
            else if(choice instanceof UseOrNotCollectableChoice)
            {
            	UseOrNotCollectableChoice useChoice = (UseOrNotCollectableChoice) choice;
     
        		item = 0;
        		
        		boolean isPistol = false;
        		
        		Pistol temporaryPistol = null;
        		
        		for (int i = 0; i < player.getBackpack().length; i ++)
        		{
        			if (player.getBackpack()[i] != null)
        			{
        				if (player.getBackpack()[i].description.equalsIgnoreCase(useChoice.getItem().description))
        				{
        					item ++;
        			
        			
        					if(player.getBackpack()[i].description.equalsIgnoreCase(new Pistol().description))
        					{
        						temporaryPistol = (Pistol) player.getBackpack()[i];
        						isPistol = true;
        					}
        				
        				}
        			}
        		}
        		
        		
        		Collection confirm = new ArrayList<Choice>();
        		
        		Collection choose = new ArrayList<Choice>();
        		
        		Event okEvent;
        		
        		Event stillFighting = new BlankEvent("Você :" + this.player.showState() + "\nInimigo :" + useChoice.getEnemy().showState(), this.eventActually.nextEvents());

        		UseCollectableChoice use ;
        		
        		if(isPistol == true)
        		{
        			use = new UseCollectableChoice("Usar " + temporaryPistol.description, stillFighting, temporaryPistol, useChoice.getEnemy(), player);
                    
        		}
        		else
        		{
        			use = new UseCollectableChoice("Usar " + useChoice.getItem().description, stillFighting, useChoice.getItem() , useChoice.getEnemy(), player);
                
        		}
        		
        		isPistol = false;
        		
        		Choice notUse = new BlankChoice("Não Usar", stillFighting);
        		
        		Choice ok = new BlankChoice("Voltar pra luta", stillFighting);
        		
        		confirm.add(ok);
        		
        		choose.add(use);
        		choose.add(notUse);
        		
        		Event usar;
        		okEvent = new BlankEvent("Você não possui " + useChoice.getItem().description, confirm);
    			
        		
        		if (temporaryPistol != null)
        		{

        			usar = new BlankEvent("Você tem " + item + " restantes" + "\n\nPoder de ataque: " + temporaryPistol.getAttack()   + "\n\nUsar?", choose);
            		
        		}
        		
        		else
        		{
        		    usar = new BlankEvent("Você tem " + item + " restantes" + "\n\nUsar?", choose);
            		
        		}
        		
        		
        		if (item == 0)
        		{

        			this.eventActually = okEvent;
        			
        		}
        		else
        		{
        			this.eventActually = usar;
        		}
        		
        		
        		this.eventActually.applyHistory(player);
            	
            	
            }

            else if(player.isAlive()) {
                this.eventActually = choice.getEvent();
                this.eventActually.applyHistory(player);
                this.pastEvent = this.eventActually;
                
            }
            else {
                Event gameOver = new BlankEvent("Game Over", new ArrayList<Choice>());
                this.eventActually = gameOver;
            }
            

            return true;
        }

        return false;
    }

    public Choice getExecutedchoice() {
		return executedchoice;
	}

	public void setExecutedchoice(Choice executedchoice) {
		this.executedchoice = executedchoice;
	}

	public Choice selectChoice(int number) {
        return this.eventActually.findChoice(number);
    }

    public Collection<Choice> nextEvents() {
        return this.eventActually.nextEvents();
    }
    public boolean isBattling() {
		return isBattling;
	}

	public void setBattling(boolean isBattling) {
		this.isBattling = isBattling;
	}

    private Event eventActually;
    private Event pastEvent;
    private Event eventInitial;
    private String description;
    private Player player;
    private Choice executedchoice;
    private boolean isBattling;
	
}
