package Audio;

import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

import Screens.Tela;

public abstract class PlayMusic {
	
	 private static Clip clip;
    private static boolean isPlaying;
	public static boolean isSetted;
	public static boolean isEnded;
    
	

	public static void play(String name, Tela tela)
	{
		if (clip != null)
		{
			clip.close();
		}
	
	    
		isEnded = false;

	    /**
	     * @param filename the name of the file that is going to be played
	     */
	    
	        String strFilename = name;
	        
	     
	        switch(name)
	        {
	        case "Menu":
	        	strFilename = "src/Resources/Audio/Menu.wav";
	        	break;
	        case "Battle":
	        	strFilename = "src/Resources/Audio/Battle.wav";
	        	break;
	        	
	        default:
	        		strFilename = null;
	        		break;
	        }

	        try {
	            File file = new File(strFilename);
	            if (file.exists()) {
	                AudioInputStream sound = AudioSystem.getAudioInputStream(file);
	             // load the sound into memory (a Clip)
	                clip = AudioSystem.getClip();
	                clip.open(sound);
	               
	            }
	            else {
	                throw new RuntimeException("Sound: file not found: " + strFilename);
	            }
	        }
	        catch (MalformedURLException e) {
	            e.printStackTrace();
	            throw new RuntimeException("Sound: Malformed URL: " + e);
	        }
	        catch (UnsupportedAudioFileException e) {
	            e.printStackTrace();
	            throw new RuntimeException("Sound: Unsupported Audio File: " + e);
	        }
	        catch (IOException e) {
	            e.printStackTrace();
	            throw new RuntimeException("Sound: Input/Output Error: " + e);
	        }
	        catch (LineUnavailableException e) {
	            e.printStackTrace();
	            throw new RuntimeException("Sound: Line Unavailable Exception Error: " + e);
	        }

	       
	        loop();
	        if(isPlaying == false)
	        {
	        		clip.stop();
	        		return;
	  
	        }
	        
	       
	        	
	     
	    }
	
	public static boolean isPlaying() {
		return isPlaying;
	}
	
	public static void setIsPlaying(boolean b) {
		isPlaying = b;
	}
	
	
	
	public static void play(){
        //clip.setFramePosition(0);  // Must always rewind!
		isPlaying = true;
        clip.start();
    }
    public static void loop(){
        clip.loop(Clip.LOOP_CONTINUOUSLY);
    }
    public static void stop(){
    	isPlaying = false;
            clip.stop();
    }
    
    public static void stopOrResume()
    {
    	if(isPlaying == true)
    	{
    		stop();
    	}
    	else
    	{
    		play();
    	}
    }
}
