package Screens;

import java.awt.BorderLayout;
import Jogo.Book;
import java.awt.CardLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;




@SuppressWarnings("serial")
public class Tela extends JFrame {

	@SuppressWarnings("unused")
	private Painel painel;
	JPanel card;
	private Book book;
	private Menu menu;
	private Game game;
	
	public Tela(Book book, String nome)
	{
		super(nome);
		
		drawFrame();
		
		setMenu(new Menu(book, this));
		setGame(new Game(book, this));
		setBook(book);
		
		drawPainel();
		
		criarCards();
		this.card.add(getGame(), "Game");
		this.card.add(getMenu(), "Menu");
		
        mudarParaTela("Menu");
        
        this.setResizable(false);
       
	}

	
	Game getGame() {
		return game;
	}

	void setGame(Game game) {
		game.setLayout(null);
		this.game = game;
	}


	private void setPainel(Painel painel) {
		this.painel = painel;
	}

	private Menu getMenu() {
		return menu;
	}

	private void setMenu(Menu menu) {
		menu.setLayout(null);
		this.menu = menu;
	}

	public Book getBook() {
		return book;
	}

	private void setBook(Book book) {
		this.book = book;
	}
	
	private void drawPainel()
	{
		Painel painel = new Painel();
		painel.setLayout(null);
		painel.setVisible(true);
		
		setPainel(painel);
		
	}
	
	private void drawFrame()
	{
		this.setBounds(0, 0, 700, 500);
		this.setVisible(true);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		//this.setResizable(false);
		
		
	}
	
	private void criarCards(){
		this.card = new JPanel(new CardLayout());
		this.getContentPane().add(this.card, BorderLayout.CENTER);
	}
	
	public void mudarParaTela(String tela){ 
		
		CardLayout cl = (CardLayout)(this.card.getLayout());
		cl.show(card, tela);
	}
	
	
}
