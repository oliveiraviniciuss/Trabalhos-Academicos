package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class Character {

    public Character(int life, int attack) {
        this.life = life;
        this.attack = attack;
    }

    public int getLife() {
		return life;
	}

	public void battle(Character enemy) {
        this.takeDamage(enemy.getAttack());
        enemy.takeDamage(this.getAttack());
        
        
    }

    public boolean isAlive() {
        if(this.life > 0)
            return true;

        return false;
    }

    public void takeDamage(int attack) {
        this.life -= attack;
    }

    public int getAttack() {
        return this.attack;
    }
    
    public void improveAttack(int x)
    {
    	this.attack += x;
    	
    }
    
    public void recoverLife(int x)
    {
    	this.life += x;
    	
    	if (this.life > 20)
    	{
    		this.life = 20;
    	}
    }
    
    public String showState()
    {
    	return "Vida ".concat(this.life + " Ataque ") + this.attack;

    }

    private int life;
    private int attack;
}
