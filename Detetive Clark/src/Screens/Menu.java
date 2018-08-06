package Screens;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

import Audio.PlayMusic;
import Jogo.Book;

import java.awt.*;

@SuppressWarnings("serial")
public class Menu extends JPanel {

	private JLabel background;
	private JButton mainButton;
	private JButton muteButton;
	
public Menu(Book book, Tela tela) {
		
		this.setLayout(null);
		
		drawBackGround();
	
		drawButton(book, tela);
		drawMuteButton(book, tela);
		
		
	}

	private JButton getMuteButton() {
	return muteButton;
	}

	private void setMuteButton(JButton muteButton) {
	this.muteButton = muteButton;
	}

	
	private JButton getMainButton() {
		return mainButton;
	}

	private void setMainButton(JButton mainButton) {
		this.mainButton = mainButton;
	}

	private JLabel getBackGround() {
		return background;
	}

	private void setBackGround(JLabel background) {
		this.background = background;
	}
	
	private void drawBackGround()
	{
		setBackGround(new JLabel(new ImageIcon("src/Resources/Images/Menu.png")));
		getBackGround().setBounds(0, 0, 700, 500);
		//getBackGround().setVisible(true);
		//getBackGround().setLayout(null);
		this.add(getBackGround());
		
	}
	
	private void drawButton(Book book, Tela tela)
	{
		JButton botao = new JButton("", new ImageIcon("src/Resources/Images/MenuButton.png"));
		botao.setRolloverIcon(new ImageIcon("src/Resources/Images/MenuButtonOver.png"));
		botao.setForeground(new Color(255, 255, 255));
		botao.setBackground(new Color(40, 40,40));
		botao.setBorder(javax.swing.BorderFactory.createLineBorder(new Color(255,255,255), 2, true));
		botao.setBounds(295, 410 ,110,50);
		
		botao.setOpaque(false);
		botao.setContentAreaFilled(false);
		botao.setBorderPainted(false);
		
		
		setMainButton(botao);
		
		getMainButton().addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				
				
				tela.mudarParaTela("Game");
				
				
			}
		});
		
		getBackGround().add(botao);
			
	}
	
	private void drawMuteButton(Book book,Tela tela)
	{
		JButton botao = new JButton();
		setMuteButton(botao);
		getMuteButton().setForeground(new Color(255, 255, 255));
		getMuteButton().setBackground(new Color(40, 40,40));
		getMuteButton().setBounds(650, 450 ,30, 30);
		if(PlayMusic.isPlaying() == false){
			getMuteButton().setIcon(new ImageIcon("src/Resources/Images/Unmute.png"));
		
		}
		else
		{
			getMuteButton().setIcon(new ImageIcon("src/Resources/Images/Mute.png"));
		}
		
		
		
		//botao.setOpaque(false);
		//botao.setContentAreaFilled(false);
		//botao.setBorderPainted(false);
		
		
		
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
				
				tela.card.remove(tela.getGame());
				tela.setGame(new Game(book, tela));
				tela.card.add(tela.getGame(), "Game");
				PlayMusic.stopOrResume();
				tela.mudarParaTela("Menu");
				
				
			}
		});
		
		getBackGround().add(getMuteButton());
		
			
	}

}
