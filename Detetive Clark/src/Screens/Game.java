package Screens;


import javax.swing.JPanel;
import Jogo.Book;
import Jogo.Choice;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTextPane;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;

import Audio.PlayMusic;

@SuppressWarnings("serial")
public class Game extends JPanel {
		
		private JButton[] arrayBotao;
		private JTextPane texto;
        private JLabel background;
        private JButton muteButton;
	
	private JButton getMuteButton() {
			return muteButton;
		}

		private void setMuteButton(JButton muteButton) {
			this.muteButton = muteButton;
		}

	public Game(Book book, Tela tela) {
		
		drawBackGround();
                
		this.arrayBotao = new JButton[4];
		
		drawText(book);
		drawMuteButton(tela);
		createButtons();
        makeColumnOfButtons(book);
        addListeners(book, tela);
	}
	
	private void drawBackGround() 
	{
		
		setBackGround(new JLabel(new ImageIcon("src/Resources/Images/Game.png")));
		
		getBackGround().setBounds(0, 0, 700, 500);
		getBackGround().setVisible(true);
		this.add(getBackGround());
		
	}
	
	private void drawText(Book book)
	{
		texto = new JTextPane();
        texto.setText(book.showHistory());
        SimpleAttributeSet align = new SimpleAttributeSet();  
        StyleConstants.setAlignment(align , StyleConstants.ALIGN_CENTER);  
        texto.setParagraphAttributes(align,true);
		texto.setBounds(45 , 50 ,600, 200);
		texto.setEditable(false);
		setTexto(texto);
		getBackGround().add(texto);
		
	}
	
	private void drawMuteButton(Tela tela)
	{
		JButton botao = new JButton();
		if(PlayMusic.isPlaying() == false){
			botao.setIcon(new ImageIcon("src/Resources/Images/Unmute.png"));
		
		}
		else
		{
			botao.setIcon(new ImageIcon("src/Resources/Images/Mute.png"));
		}
		botao.setForeground(new Color(255, 255, 255));
		botao.setBackground(new Color(40, 40,40));
		
		//botao.setOpaque(false);
		//botao.setContentAreaFilled(false);
		//botao.setBorderPainted(false);
		
		setMuteButton(botao);
		getMuteButton().setBounds(650, 450 ,30, 30);
		
		
		getMuteButton().addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
				
				if(PlayMusic.isPlaying() == false){
					botao.setIcon(new ImageIcon("src/Resources/Images/Unmute.png"));
				
				}
				else
				{
					botao.setIcon(new ImageIcon("src/Resources/Images/Mute.png"));
				}
				
				PlayMusic.stopOrResume();
				
				tela.mudarParaTela("Game");
				
				
			}
		});
		
		getBackGround().add(botao);
			
	}

	
	private JButton[] getArrayBotao() {
			return arrayBotao;
		}
		
	private JTextPane getTexto() {
			return texto;
		}
	private void setTexto(JTextPane texto) {
			this.texto = texto;
		}
	private JLabel getBackGround() {
			return background;
	}
	private void setBackGround(JLabel background) {
			this.background = background;
		}
    private void createButtons(){
                
    	for(int i = 0; i< getArrayBotao().length;i++){
                    
    			getArrayBotao()[i] = new JButton(""+ i);
                
    			getArrayBotao()[i].setForeground(new Color(255, 255, 255));
    			getArrayBotao()[i].setBackground(new Color(40, 40, 40));
                
                getBackGround().add(getArrayBotao()[i]);
                    
        	}
    }
        
    public void makeColumnOfButtons(Book book){
            int i = 0;
            int j = 0;
                
            for (int w = 0; w < 4; w ++)
            {
            	 getArrayBotao()[w].setBounds(150, 270+j,400 , 40);
            	 i++;
                 j += 50;
                 getArrayBotao()[w].setVisible(false);
            	
            }
            
            i = 0;
            
            for(Choice choice:book.nextEvents())
            {
                   
            	getArrayBotao()[i].setVisible(true);
            	getArrayBotao()[i].setText(choice.getDescription());
                i++;
                   
            }
               
        }
     private void repaint(Book book){
    	 
           getTexto().setText(book.showHistory());
            int i = 0;
            
            for(Choice choice:book.nextEvents()){
                
            	getArrayBotao()[i].setVisible(true);
            	getArrayBotao()[i].setText(choice.getDescription());
                i++;
            }
            for(;i<getArrayBotao().length;i++){
            	getArrayBotao()[i].setVisible(false);
        }

}
       
     private void addListeners(Book book,Tela tela){
        
    	 getArrayBotao()[0].addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0){
                book.nextEvent(0);
                if(arrayBotao[0].getText().equalsIgnoreCase("0: lutar.") && PlayMusic.isSetted == false)
                {
                	book.setBattling(true);
                	PlayMusic.isSetted = true;
                	PlayMusic.play("Battle", tela );
                }
                else if(arrayBotao[0].getText().equalsIgnoreCase("0: continuar."))
                {
                	
                	
                	book.setBattling(false);
                	PlayMusic.isSetted = false;
                	PlayMusic.play("Menu", tela);
                }
                repaint(book);
            }

});
                
    	 getArrayBotao()[1].addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0){
                book.nextEvent(1);
                repaint(book);
            }

});
                
    	 getArrayBotao()[2].addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0){
                book.nextEvent(2);
                repaint(book);
            }

});
                
    	 getArrayBotao()[3].addActionListener(new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent arg0){
                book.nextEvent(3);
                repaint(book);
            }

});
}
}

