package Jogo;
/**
 * Created by filipebraida on 31/05/16.
 */
public class Enemy extends Character {
	
	private boolean isArrested = false;
    public boolean isArrested() {
		return isArrested;
	}
	public void setArrested(boolean isArrested) {
		this.isArrested = isArrested;
	}
	public Enemy(int life, int attack) {
        super(life, attack);
    }
}
