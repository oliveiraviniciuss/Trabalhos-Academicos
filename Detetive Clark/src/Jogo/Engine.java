package Jogo;

import java.awt.Window;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import Screens.Tela;

import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

import Audio.PlayMusic;

import javax.swing.UnsupportedLookAndFeelException;




/**
 * Created by filipebraida on 31/05/16.
 */
public class Engine {
    public static void main(String[] args) throws IOException {
    
    	
    	Book book = Engine.createBook();
    	
        String className = getLookAndFeelClassName("Nimbus");
        try {
			UIManager.setLookAndFeel(className);
			for(Window window : JFrame.getWindows()) {
		        SwingUtilities.updateComponentTreeUI(window);
		    }
			
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (UnsupportedLookAndFeelException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
        
        
        Tela tela = new Tela(book, "Detetive Clark");
        
        PlayMusic.setIsPlaying(true);
        PlayMusic.isSetted = false;
        PlayMusic.play("Menu", tela);	
           
        
    }
    
    public static String getLookAndFeelClassName(String nameSnippet) {
        LookAndFeelInfo[] plafs = UIManager.getInstalledLookAndFeels();
        for (LookAndFeelInfo info : plafs) {
            if (info.getName().contains(nameSnippet)) {
                return info.getClassName();
            }
        }
        return null;
    }

    @SuppressWarnings({ "rawtypes", "unchecked" })
	public static Book createBook() {
    	
    	//Event finalEvent = new BlankEvent("O jogo acabou", new ArrayList<Choice>());
    	Player clark = new Player(20, 5);
    	Enemy inimigo = new Enemy(20 ,5);
    			
    	Collection attackOrDefend = new ArrayList<Choice>();
    	
		
		
    	BlankEvent kill = new BlankEvent("A fúria dos seus sentimentos foi capaz de matar Johnny... será que agora o criminoso é você?\n\n"
				+ "A continuar o capítulo 2...", new ArrayList<Choice>());
    	
    	BlankEvent eventoBranco = new BlankEvent("Com certeza vai ser o orgulho da equipe\n\n"
				+ "A continuar o capítulo 2...", new ArrayList<Choice>());
    			
    	BattleChoice attack = new BattleChoice("Atacar.", kill, inimigo);
    			
    			TryToArrestChoice getAway = new TryToArrestChoice("Tentar prender.",  eventoBranco, inimigo);
    			
    			UseOrNotCollectableChoice health = new UseOrNotCollectableChoice("Usar MedKit.", kill, new Health(),inimigo, clark);
    			UseOrNotCollectableChoice gun = new UseOrNotCollectableChoice("Usar arma.", kill, new Pistol() ,inimigo, clark);
    			
    			attackOrDefend.add(attack);
    			attackOrDefend.add(getAway);
    			attackOrDefend.add(health);
    			attackOrDefend.add(gun);
        		
       		   BlankEvent BattleStatus = new BlankEvent("Você :" + clark.showState() + "\nInimigo :" + inimigo.showState(), attackOrDefend);


        	
        		Collection faceToFace = new ArrayList<Choice>();
        		
        		Choice fight = new BlankChoice("Lutar.", BattleStatus );
        		
        		
        		faceToFace.add(fight);
        	
    	
    			BlankEvent johnny = new BlankEvent("Clark: Você vai pagar pelo que fez, eu nunca fui com a sua cara mesmo.\n" 
    												+ "\nJohnny: Você é um fraco mesmo.. não percebeu que eu estava apenas te analizando"
    												+ " para estar sempre um passo a frente? Você vai ser só mais uma vítmia agora..", faceToFace);
    		
               
                
                
                
           
               Collection reachJohnnyChoices = new ArrayList<Choice>();
               
               Choice silent = new BlankChoice("Ir sorrateiramente.", johnny);
               Choice rage = new BlankChoice("Partir pra cima.", johnny);
               
               reachJohnnyChoices.add(rage);
               reachJohnnyChoices.add(silent);
                
               
               Event enemyAtAmbush = new BlankEvent("Clark: Como??!!! Não pode ser... eu não acredito. "
	   					+ "É Johnny Fieldsman!!!! Meu antigo colega de trabalho.\n"
	   					+ "Todos esses anos querendo ser quem eu era no Departamento, e"
	   					+ " agora comentendo esses crimes bizarros. Você vai pagar pelo que fez, eu nunca fui com a sua cara mesmo." 
	   					+ "\n\nJohnny: Você é um fraco mesmo.. não percebeu que eu estava apenas te analizando"
	   					+ " para estar sempre um passo a frente? Você vai ser só mais uma vítmia agora..", faceToFace);

               
               Collection getUpChoice = new ArrayList<Choice>();
               
               Choice getUp = new BlankChoice("Levantar.", enemyAtAmbush);
               
               getUpChoice.add(getUp);
           
               Event caught = new BlankEvent("Era uma cilada!! Você foi jogado ao chão por tras... ", getUpChoice);
               
                
               Collection analize = new ArrayList<Choice>();
               
               Choice trunk = new BlankChoice("Olhar porta malas.", caught);
               Choice backToCar = new BlankChoice ("Voltar para o carro.", caught);
               
               analize.add(trunk);
               analize.add(backToCar);
                
               
               Event ambush = new BlankEvent("Clark: Isto está meio estranho...", analize);
               
               Event enemyAtCassino = new BlankEvent("Clark: Ali está ele!!! Não pode ser... eu não acredito. "
            		   					+ "É Johnny Fieldsman!!!! Meu antigo colega de trabalho. "
            		   					+ "Todos esses anos querendo ser quem eu era no Departamento, e"
            		   					+ " agora comentendo esses crimes bizarros. Ainda bem que não me viu, mas que a justiça seja feita!", reachJohnnyChoices);
               
               
               Collection enterCassinoChoices = new ArrayList<Choice>();
               
               Choice frontward = new BlankChoice("Entrar na Porta Principal.", enemyAtCassino);
               Choice backward = new BlankChoice("Entrar pelos fundos.", enemyAtCassino);
               
               enterCassinoChoices.add(frontward);
               enterCassinoChoices.add(backward);
               
               
               
               Event cassino = new BlankEvent("Finalmente, o temido cassino Laus Parks!", enterCassinoChoices);
                
               Collection strangeThing = new ArrayList<Choice>();
               
               Choice stop = new BlankChoice("Parar para averiguar.", ambush);
               Choice alternativeWay = new BlankChoice("Contonar por outro caminho.", cassino);
               
               strangeThing.add(alternativeWay);
               strangeThing.add(stop);
                
                
                Event eventW = new BlankEvent("Clark: Mas ..... o que???     Tem um carro atravessado no meio da Pista "
        				+ "com o alerta ligado.... mas aprentemente ninguém.", strangeThing);
                
                Collection cassinoPath = new ArrayList<Choice>();
                
                Choice keepdriving = new BlankChoice("Continuar dirigindo.", eventW);
                
                cassinoPath.add(keepdriving);
                
                
                
         
                
                Event eventN = new BlankEvent("Seguindo pra cassino... Estranhamente está tudo muito deserto.",cassinoPath);
                
                Collection goToCassinoChoice = new ArrayList<Choice>();
                
                Choice go = new BlankChoice("Ir para o Laus Parks.", eventN);
                
                goToCassinoChoice.add(go);
                
                
                
               Event forceToCassino = new BlankEvent("Você precisa ir!! Antes que o suspeito vá embora de lá.", goToCassinoChoice);
                
                
                
                Collection pegarOuNaoMedkit2 = new ArrayList<Choice>();
                Choice choiceNao2 = new BlankChoice("Nao pegar.",forceToCassino);
                Choice choiceSim2 = new PickUpItemChoice("Pegar.", forceToCassino, new Health());
                
                pegarOuNaoMedkit2.add(choiceSim2);
                pegarOuNaoMedkit2.add(choiceNao2);
                
                
                Event eventP2 = new BlankEvent("Clark: Um medkit... isso pode ser util?!",pegarOuNaoMedkit2);
                
                
                
                
                
                Collection choiceSala = new ArrayList<Choice>();
                
                Choice verificarSala = new BlankChoice("Verificar.",eventP2);
                Choice naoVerificarSala = new BlankChoice("Não verificar.",forceToCassino);
                choiceSala.add(verificarSala);
                choiceSala.add(naoVerificarSala);
                
                Event eventR = new BlankEvent("Como você não pegou a pistola, gostaria de verificar o armário forense?",choiceSala);
                
                
                Collection pegarOuNaoPistola = new ArrayList<Choice>();
                Choice choiceNao = new BlankChoice("Nao pegar.",eventR);
                Choice choiceSim = new PickUpItemChoice("Pegar pistola.", forceToCassino, new Pistol());
                
                pegarOuNaoPistola.add(choiceSim);
                pegarOuNaoPistola.add(choiceNao);
                
                
                Event eventP = new BlankEvent("Clark: Ainda bem que vim aqui, tinha esquecido minha pistola!",pegarOuNaoPistola);
                
                Collection choicesArmario2 = new ArrayList<Choice>();
                
                Choice verificaArmario = new BlankChoice("Verificar o armário forense.",eventP);
                Choice naoVerificarArmario = new BlankChoice("Não verificar armário forense.",forceToCassino);
                choicesArmario2.add(verificaArmario);
                choicesArmario2.add(naoVerificarArmario);
                
                
                Event eventT = new BlankEvent("Como você não pegou o Kit médico, gostaria de verificar o armário forense da delegacia?",choicesArmario2);
                
                
                
                Collection choicesArmario = new ArrayList<Choice>();
                Choice pegarKit = new PickUpItemChoice("Pegar MedKit." ,forceToCassino, new Health());
                Choice naoPegarKit = new BlankChoice("Não pegar item.",eventT);
                choicesArmario.add(pegarKit);
                choicesArmario.add(naoPegarKit);
                
                Event eventQ = new BlankEvent("Clark: Que sorte!! Encontrei um um kit médico aqui.. Acho melhor levar isso comigo.",choicesArmario);
                
                
                Collection delegaciaChoices = new ArrayList<Choice>();
                
                Choice checarArmario = new BlankChoice("Checar dispensa forense antes de ir no cassino.",eventQ);
                Choice checarSuaSala = new BlankChoice("Checar sua sala antes de ir no cassino.",eventP);
                Choice leave = new BlankChoice("Ir direto ao Cassino", eventN);
                delegaciaChoices.add(checarArmario);
                delegaciaChoices.add(checarSuaSala);
                delegaciaChoices.add(leave);
                
                
                Event eventM = new BlankEvent("Não há mais evidências na delegacia. Você deve ir ao cassino Laus Park para obter mais informações.",delegaciaChoices);
                
                
                Collection clarkChoices = new ArrayList<Choice>();
                
                Choice irAoCassino = new BlankChoice("Ir ao cassino Laus Parks.",eventN);
                Choice ficarNaDelegacia = new BlankChoice("Ficar na delegacia.",eventM);
                clarkChoices.add(irAoCassino);
                clarkChoices.add(ficarNaDelegacia);
                
                Event eventL = new BlankEvent("Clark: Billy, eu tenho um palmite. Eu acho que esse assassino é o mesmo que contrabandeia armas "
                		+ "por toda a cidade de Nova York, e pelas ultimas informações que eu tive, ele sempre frequenta o cassino Laus Parks, porém "
                		+ " isso nunca passou de boatos.",clarkChoices);
                
                
                Collection choiceBilly = new ArrayList<Choice>();
                Choice pegarRelatorio = new BlankChoice("Pegar relatórios dos depoimentos com a sua equipe.",eventL);
                Choice perguntarEquipe = new BlankChoice("Pedir a possível caricatura do criminoso.",eventL);
                choiceBilly.add(pegarRelatorio);
                choiceBilly.add(perguntarEquipe);
                
                
                Event eventK = new BlankEvent("Billy: Nossa Clark, esse cara parece com a descrição das 3 testesmunhas que eu interroguei. "
                		+"Ele tinha um capuz preto, era alto e tinham ombros largos. ",choiceBilly);
                
               
                Collection conversaEquipe = new ArrayList<Choice>();
                
                Choice choiceMostrarImagem = new BlankChoice("Mostrar imagens para a equipe.",eventK);
                Choice choiceNaoMostrar = new BlankChoice("Não mostrar imagens para a equipe.",eventL);
                
                conversaEquipe.add(choiceMostrarImagem);
                conversaEquipe.add(choiceNaoMostrar);
                
              
                
                Event eventJ = new BlankEvent("Clark: Olá pessoal, trouxe comigo algumas informações da cena do crime. Apesar de não obter "
                +"boas informações com o luminol, consegui ótimas imagens em uma câmera localizada proxima ao local.",conversaEquipe);
                
                Collection delegaciaChoices2 = new ArrayList<Choice>();
                
                Choice conversarComEquipe = new BlankChoice("Conversar com a equipe.",eventJ);
                
                delegaciaChoices2.add(conversarComEquipe);
             
                
                
                Event eventE = new BlankEvent("Depois de analisar a cena do crime, o detetive resolve voltar para a delegacia"
                		+" para conversar com a sua equipe sobre a sua visita ao local. Ao chegar, ele se depara com uma parte da sua equipe"
                		+ " recolhendo depoimentos de uma série de pessoas.",delegaciaChoices2);
                
                
                
                Collection cameraChoice = new ArrayList<Choice>();
                Choice choiceCamera = new BlankChoice("Ok.",eventE);
                cameraChoice.add(choiceCamera);
                
                Event eventC = new BlankEvent("Ao verificar a câmera de segurança de um posto de gasolina, o detetive se depara com uma pessoa de capuz saindo do local do crime horas antes",cameraChoice);
               
               
                Collection cameraChoices = new ArrayList<Choice>();
                Choice analisarCamera = new BlankChoice("Analisar as câmeras",eventC);
                cameraChoices.add(analisarCamera);
                
                Event eventF = new BlankEvent("Agora que você analisou a cena do crime com luminol, como um bom detetive, não deixe passar informações "
                		 +"e analise também as informações das câmeras de segurança.",cameraChoices);
              
                
                Collection sceneLuminolChoices = new ArrayList<Choice>();
                
                Choice luminolChoice = new BlankChoice("Ok.",eventF);
                sceneLuminolChoices.add(luminolChoice);
                
                Event eventD = new BlankEvent("Detetive Clark: Que assissino profissional! Até agora não encontrei nenhuma marca.",sceneLuminolChoices);
                
                Collection luminolChoiceAgain = new ArrayList<Choice>();
                
                Choice luminolChoice2 = new BlankChoice("Ok.",eventE);
                luminolChoiceAgain.add(luminolChoice2);
                
                Event eventI = new BlankEvent("Detetive Clark: Que assissino profissional! Até agora não encontrei nenhuma marca.",luminolChoiceAgain);
                
                Collection sceneLuminolChoice = new ArrayList<Choice>();
                Choice analisarLuminol = new BlankChoice("Analisar a cena do crime com luminol.",eventI);
                sceneLuminolChoice.add(analisarLuminol);
                
                Event eventG = new BlankEvent("Agora que você analisou as câmeras de segurança, como um bom detetive, não deixe passar nenhuma informação."
                		+ " e analise também a cena do crime com luminol.",sceneLuminolChoice);
                
                
               
                Collection cameraChoice2 = new ArrayList<Choice>();
                Choice choiceCamera2 = new BlankChoice("Ok.",eventG);
                cameraChoice2.add(choiceCamera2);
                
                Event eventH = new BlankEvent("Ao verificar a câmera de segurança de um posto de gasolina, o detetive se depara com uma pessoa de capuz saindo do local do crime horas antes.",cameraChoice2);
                
                
                
                Collection sceneCrimeChoices = new ArrayList<Choice>();
                Choice choiceAnalisar1 = new BlankChoice("Analisar melhor a cena usando luminol.",eventD);
                Choice choiceAnalisar2 = new BlankChoice("Verificar as câmeras de segurança da redondeza.",eventH);
                sceneCrimeChoices.add(choiceAnalisar1);
                sceneCrimeChoices.add(choiceAnalisar2);
                
                Event eventA = new BlankEvent("Chegando na cena do crime, o detetive Clark encontra o local isolado "
                		+ "por faixas, porém sem nenhum vestígio de algum autor.", sceneCrimeChoices);
                

                Collection clarkChoices2 = new ArrayList<Choice>();
                
                Choice irParaCena = new BlankChoice("Ir para cena do crime.",eventA);
                clarkChoices2.add(irParaCena);
                
                Event eventO = new BlankEvent("Não será necessário que você fique pois sua equipe já estará aqui ouvindo os depoimentos.",clarkChoices2);
                
                Collection initialChoices = new ArrayList<Choice>();
                Choice choiceCrimeScene = new BlankChoice("Ir até a cena do crime.", eventA);
                Choice choiceDelegacia = new BlankChoice("Ficar na delegacia para ouvir depoimentos.",eventO );
               
                initialChoices.add(choiceCrimeScene);
                initialChoices.add(choiceDelegacia);
               
                
                
                Event clarkHistory = new BlankEvent("Você é o Detetive Clark, 38 anos, e este assassinato, embora não tenha nada demais, está "
                		+ "lhe causando uma sensação diferente...\t Então, o que você vai fazer?", initialChoices);
                
                Collection prologueChoices = new ArrayList<Choice>();
                
                Choice whoAmI = new BlankChoice("Ok, e eu sou...?", clarkHistory);
                
                prologueChoices.add(whoAmI);
                
                
                Event initialEvent = new BlankEvent("Ano de 2017, dia 1 de Janeiro aconteceu um crime bárbaro na cidade"
                		+ " de Nova York. Um assassino, cujo a identidade é desconhecida, matou o Governador de Nova York."
                		+ " Como você é um detetive forense da delegacia de homicídios, sua equipe foi a escolhida para "
                		+ "investigar o caso que está aterrorizando a cidade.", prologueChoices );
                
                
    		Book livro = new Book("Detetive Clark", initialEvent, clark);
    		
    	
        return livro;

    }
}