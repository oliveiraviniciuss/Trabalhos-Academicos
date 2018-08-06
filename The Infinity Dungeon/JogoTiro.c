#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <math.h>
//#define M_PI acos(-1.0)

#include "Player.h"
#include "Shot.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "MonoBehaviour.h"
#include "Font.h"

/*#ifndef WINDOW_H__
#define WINDOW_H__
#endif 
#include "Window.h"*/

#define SCREEN_WIDTH 800   
#define SCREEN_HEIGHT  600
#define GAME_TITLE "THE INFINITY DUNGEON"
#define SCREEN_FPS  60
#define SCREEN_TICKS_PER_FRAME 1000 / SCREEN_FPS

//WAVES
#define WAVE1  5
#define WAVE2  10
#define WAVE3  12
#define WAVE4  15
#define WAVE5  20

//Textures
SDL_Texture* backgroundTexture = NULL;
SDL_Texture* backgroundGameTexture = NULL;
SDL_Texture* backgroundCredits = NULL;
SDL_Texture* borderTexture = NULL;
SDL_Texture* nameDeadTexture_stage0 = NULL;
SDL_Texture* nameDeadTexture_stage1 = NULL;
SDL_Texture* nameDeadTexture_stage2 = NULL;
SDL_Texture* startTexture = NULL;
SDL_Texture* startTexture_blink = NULL;
SDL_Texture* spacetoskipTexture = NULL;
SDL_Texture* bloodTexture = NULL;
SDL_Texture* pauseTexture = NULL;
SDL_Texture* ghost = NULL;
SDL_Texture* ghostmirrored = NULL;
SDL_Texture* skeleton = NULL;
SDL_Texture* skeletonmirrored = NULL;
SDL_Texture* boss1 = NULL;
SDL_Texture* boss2 = NULL;
SDL_Texture* boss1mirrored = NULL;
SDL_Texture* boss2mirrored = NULL;
SDL_Texture* halflifeTexture = NULL;
SDL_Texture* lowlifeTexture = NULL;
SDL_Texture* highlifeTexture = NULL;
SDL_Texture* hitfireTexture = NULL;
SDL_Texture* hitcoldTexture = NULL;
SDL_Texture* keyTexture = NULL;
SDL_Texture* fire_arrowTexture = NULL;
SDL_Texture* fire_arrow_usedTexture = NULL;
SDL_Texture* cold_arrowTexture = NULL;
SDL_Texture* cold_arrow_usedTexture = NULL;
SDL_Texture* potionTexture = NULL;
SDL_Texture* logoTexture = NULL;
SDL_Texture *highScoreTexture = NULL;
SDL_Texture *recordesTexture = NULL;


//Rects
SDL_Rect munitionRect;
SDL_Rect spacetoskipRect;
SDL_Rect bloodRect;
SDL_Rect keyRect;
SDL_Rect potionRect;
SDL_Rect fire_arrowRect;
SDL_Rect fire_arrow_usedRect;
SDL_Rect cold_arrowRect;
SDL_Rect nameDeadRect;
SDL_Rect pauseTextureRect;
SDL_Rect hitcoldRect;


//Intro
SDL_Texture* introTexture = NULL;  
SDL_Rect introRect;

//Doors
SDL_Texture* doorLeftTexture = NULL;  
SDL_Texture* doorLeftGameTexture = NULL;  
SDL_Rect doorLeftRect;
SDL_Rect blackLeftRect;

SDL_Texture* doorRightTexture = NULL;  
SDL_Texture* doorRightGameTexture = NULL;  
SDL_Rect doorRightRect;
SDL_Rect blackRightRect;

SDL_Texture* doorUpTexture = NULL;  
SDL_Texture* doorUpGameTexture = NULL;  
SDL_Rect doorUpRect;
SDL_Rect blackUpRect;

SDL_Texture* doorDownTexture = NULL;  
SDL_Texture* doorDownGameTexture = NULL;  
SDL_Rect doorDownRect;
SDL_Rect blackDownRect;
//


//Fade
SDL_Texture* fadeTexture = NULL;
Uint8 alpha = 255;
int fadeInDone = 0;
int fadeOutDone = 0;

//Musics
Mix_Chunk *gMusic = NULL;
Mix_Chunk *gKey = NULL; 
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gCollision = NULL;
Mix_Chunk *gMusicMenu = NULL;
Mix_Chunk *gStart = NULL;
Mix_Chunk *gHitCollision = NULL;

//Mouse Pos
Sint32 myMouseX = 0;
Sint32 myMouseY = 0;


void CreateComponents();
void CreateFont();
void CreateFont2();
void loadFromRenderedText();
void loadFromRenderedText2( char text[100], SDL_Color textColor, SDL_Texture* texture );
void loadFromRenderedText3( char text[100], SDL_Color textColor, SDL_Texture** texture );
void ReadAllLetters();
SDL_Texture* loadTexture( char* path);

//Prototypes
void Draw();
void Update();
void Collision();
void UpdateKeyBoard();
void UpdateShotPosition();
void UpdatePlayerDeadKeyBoard();
void PlayerVunerability();
void CreateEnemy();
void CreateBoss();
void RemoveAt_Shot(ARRAYSHOT *arrayShot, int pos);
void RemoveAt_Enemy(ARRAYENEMY *arrayEnemy, int pos);
void CreateRound();
void GameOver();
void Shoot(float directionH, float directionV);
void LookAtMouse(PLAYER* player, VECTOR2 mousePos);
VECTOR2 GetMousePos();
void AnimPlayer();
void AnimateEnemy();
void DrawMunition();
void openFileRead();
void openFileWrite();
void openFileWrite2(char name[3]);
void LoadMusics();
void myGetMousePos(SDL_Event e);
void tookDamageSprite();
void PlayerHandleEvent(SDL_Event e);
int rand(void);
time_t t;


//Loops and Variables
int quit = 0;
SDL_Event e;
int gameDelay = 8;
int delayIntro = 0;
int score = 0;
int wavesurvived = 0;
int totalwaves = 0;
int isboss = 0;
int bossdamage = 0;
int infire = 0;
int incold = 0;
int firearrow_enabled = 0;
int coldarrow_enabled = 0;
int just_pressed = 0;
int liga_audio = 1;
int remaining_firearrows = 0;
int remaining_coldarrows = 0;
int tookdamage_delay = 0;
int pause = 0;
int i, j;
int count_orientation = 0;



//Structs
WINDOW window;
PLAYER player;
ARRAYSHOT arrayShot;
ARRAYENEMY arrayEnemy;
HITFIRE hitfire;
FONT font;


//Font
TTF_Font *scoreFont = NULL;
SDL_Texture *scoreTexture = NULL;
SDL_Rect fontRect;





//Enums
enum SCENE{ INTRO, MENU, GAME, MENU_AND_GAME, PRE_MENU, HIGHSCORE, CREDITS, PLAYER_DEAD, START};
enum SCENE scene;

enum DOOROPEN{ NONE, UP, DOWN, RIGHT, LEFT };
enum DOOROPEN doorOpen;

//Frames
Uint32  startTicks;
int countedFrames = 1;

Uint32 currentTicks;


// Variaveis do arquivo//
int vetor[] = {0,0,0,0,0,0,0,0,0,0};
FILE *arquivo;

FILE *arquivoSTR;
char vetorSTR[10][10];



int main(void)
{
    CreateWindow(&window, GAME_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
    CreateComponents();
    CreateFont();
    CreateFont2();
    ReadAllLetters();
    openFileRead();
    
   
    scene = INTRO;
        
       
        

    potionRect.x = SCREEN_WIDTH/2;
    potionRect.y = SCREEN_HEIGHT/2;
    potionRect.w = 20;
    potionRect.h = 28;

    spacetoskipRect.x = 650;
    spacetoskipRect.y = 540;
    spacetoskipRect.w = 110;
    spacetoskipRect.h = 60;

    bloodRect.x = 650;
    bloodRect.y = 540;
    bloodRect.w = 52;
    bloodRect.h = 52;

    fire_arrowRect.x = SCREEN_WIDTH/2;
    fire_arrowRect.y = SCREEN_HEIGHT/2;
    fire_arrowRect.w = 48;
    fire_arrowRect.h = 31;

    cold_arrowRect.x = SCREEN_WIDTH/2;
    cold_arrowRect.y = SCREEN_HEIGHT/2;
    cold_arrowRect.w = 48;
    cold_arrowRect.h = 31;

    hitcoldRect.x = SCREEN_WIDTH/2;
    hitcoldRect.y = SCREEN_HEIGHT/2;
    hitcoldRect.w = 28;
    hitcoldRect.h = 28;

    hitfire.rect.x = 0;
    hitfire.rect.y = 0;
    hitfire.rect.w = 28;
    hitfire.rect.h = 28;
	hitfire.image.x = 0;
    hitfire.image.y = 0;
    hitfire.image.w = 48;
    hitfire.image.h = 48;
    hitfire.spritePos = rand () % 3;
    hitfire.spriteMax = 2;
    hitfire.delaySprite = 0;

    keyRect.x = 650;
    keyRect.y = 100;
    keyRect.w = 34;
    keyRect.h = 18; 

    nameDeadRect.x = (SCREEN_WIDTH/2)- 250;
    nameDeadRect.y = (SCREEN_HEIGHT/2) - 150;
	nameDeadRect.w = 500;
    nameDeadRect.h = 300;

    pauseTextureRect.x = (SCREEN_WIDTH/2) - 200;
    pauseTextureRect.y = (SCREEN_HEIGHT/2) - 100;
    pauseTextureRect.w = 400;
    pauseTextureRect.h = 200;

    introRect.x = 100;
    introRect.y = 300;
    introRect.w = 600;
    introRect.h = 1000; 


    doorLeftRect.w = 75;
    doorLeftRect.h = 150;
    doorLeftRect.x = 40;
    doorLeftRect.y = SCREEN_HEIGHT/2 - 100 ;

    blackLeftRect.w = 75;
    blackLeftRect.h = 150;
    blackLeftRect.x = 35;
    blackLeftRect.y = SCREEN_HEIGHT/2 - 100 ;

    doorRightRect.w = 75;
    doorRightRect.h = 150;
    doorRightRect.x = SCREEN_WIDTH - 40 - 75;
    doorRightRect.y = SCREEN_HEIGHT/2 - 100 ;

    blackRightRect.w = 75;
    blackRightRect.h = 150;
    blackRightRect.x = SCREEN_WIDTH - 35 - 75;
    blackRightRect.y = SCREEN_HEIGHT/2 - 100 ;

    doorUpRect.w = 140;
    doorUpRect.h = 55;
    doorUpRect.x = SCREEN_WIDTH/2 - 70;
    doorUpRect.y = 32;

    blackUpRect.w = 140;
    blackUpRect.h = 55;
    blackUpRect.x = SCREEN_WIDTH/2  - 70;
    blackUpRect.y = 27;

    doorDownRect.w = 140;
    doorDownRect.h = 55;
    doorDownRect.x = SCREEN_WIDTH/2 - 70;
    doorDownRect.y = SCREEN_HEIGHT - 83;

    blackDownRect.w = 140;
    blackDownRect.h = 55;
    blackDownRect.x = SCREEN_WIDTH/2  - 70;
    blackDownRect.y = SCREEN_HEIGHT - 78;


    //Loading Textures Screens
    introTexture = loadTexture("Sprites/intronew.png");
    logoTexture = loadTexture("Sprites/Logo.png");
    nameDeadTexture_stage0 = loadTexture("Sprites/nameDead0.png");
    nameDeadTexture_stage1 = loadTexture("Sprites/nameDead1.png");
    nameDeadTexture_stage2 = loadTexture("Sprites/nameDead2.png");
    pauseTexture = loadTexture("Sprites/pause.png");
    startTexture = loadTexture("Sprites/titulo.png");
    startTexture_blink = loadTexture("Sprites/tituloblink.png");
    spacetoskipTexture = loadTexture("Sprites/spacetoskip.png");


    //Loading Textures Word
    backgroundTexture = loadTexture("Sprites/MENU2.png");
    backgroundGameTexture = loadTexture("Sprites/Background0.png");
    backgroundCredits = loadTexture("Sprites/creditos.png");
    borderTexture = loadTexture("Sprites/Border_Purple.png");
    fadeTexture = loadTexture("Sprites/Fade.png");
    doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
    doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
    doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
    doorDownTexture = loadTexture("Sprites/Doors/DoorDown_0.png");
    doorLeftGameTexture = loadTexture("Sprites/Doors/DoorLeft_1.png");
    doorRightGameTexture = loadTexture("Sprites/Doors/DoorRight_1.png");
    doorUpGameTexture = loadTexture("Sprites/Doors/DoorUp_1.png");
    doorDownGameTexture = loadTexture("Sprites/Doors/DoorDown_1.png");

    
    //Weapons and Effects
    keyTexture = loadTexture("Sprites/Key.png");
    fire_arrowTexture = loadTexture("Sprites/fire.png");
    cold_arrowTexture = loadTexture("Sprites/cold.png");
    fire_arrow_usedTexture = loadTexture("Sprites/fire.png");
    cold_arrow_usedTexture = loadTexture("Sprites/cold.png");
    hitfireTexture = loadTexture("Sprites/hitfire.png");
    hitcoldTexture = loadTexture("Sprites/incold.png");
    potionTexture = loadTexture("Sprites/potion.png");
    halflifeTexture = loadTexture("Sprites/Life2.png");
    lowlifeTexture = loadTexture("Sprites/Life3.png");
    highlifeTexture = loadTexture("Sprites/Life.png");
    bloodTexture = loadTexture("Sprites/blood.png");

    
    //enemies 
    ghost = loadTexture("Sprites/ghost.png");
    ghostmirrored = loadTexture("Sprites/ghostmirrored.png");
    skeleton = loadTexture("Sprites/skeleton.png");
    skeletonmirrored = loadTexture("Sprites/skeletonmirrored.png");
    boss1 = loadTexture("Sprites/bat2.png");
    boss2 = loadTexture("Sprites/ghostboss2.png");
    boss1mirrored = loadTexture("Sprites/bat2mirrored.png");
    boss2mirrored = loadTexture("Sprites/ghostboss2mirrored.png");
 
    


    startTicks = SDL_GetTicks();

	while(quit == 0)
    {
        
        SDL_Delay(gameDelay);
     
        while(pause == 1)
        {
            SDL_Delay(gameDelay);
            if(just_pressed > 0)
                just_pressed--;


            SDL_Event event;
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_KEYDOWN)
                {
                    switch(event.key.keysym.sym){
                        case SDLK_p:
                        pause = 0;
                        just_pressed = 20;
                        break;
                        case SDLK_ESCAPE:
                        pause = 0;
                        quit = 1;
                        break;
                        case SDLK_SPACE:
                        if (scene == GAME)
                        {
                        	pause = 0;
                        	scene = MENU;
   							doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
   							Mix_FreeChunk(gMusic);
   							CreateComponents();
   						}
                        break;
                    }
                }
                  if( event.type == SDL_QUIT )
                {
                    pause = 0;
                    quit = 1;
                }

            }

            
        }

        currentTicks = SDL_GetTicks();


        //If frame finished early
        int frameTicks = ((currentTicks - startTicks) / 1000);
        if( frameTicks > SCREEN_TICKS_PER_FRAME )
        {
            //Wait remaining time
            SDL_Delay( frameTicks - SCREEN_TICKS_PER_FRAME );
            startTicks = SDL_GetTicks();
        }


		while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }

            WindowHandleEvent(e, &window);

            if(scene == GAME || scene == MENU)
            PlayerHandleEvent(e);

        	myGetMousePos(e);
           
        }

        SDL_Delay(gameDelay);
      
        player.lifeRect.x = player.rect.x + 2;
        player.lifeRect.y = player.rect.y - 10;
        player.lifeRectBG.x = player.rect.x + 2;
        player.lifeRectBG.y = player.rect.y - 10;
        player.lifeRect.w = player.hp;

        if (player.hp < 15 && player.hp > 6)
        {
        	player.lifeTexture = halflifeTexture;
        }

        else if (player.hp < 7)
        {
        	player.lifeTexture = lowlifeTexture;
        }

        else if (player.hp > 14)
        {
        	player.lifeTexture = highlifeTexture;
        }

        Update();
        Draw();  
        countedFrames++;     
    
	}

    Mix_FreeChunk(gScratch);
    Mix_FreeChunk(gKey);
    Mix_FreeChunk(gCollision);
    Mix_FreeChunk(gHitCollision);
    gHitCollision =
    gScratch = NULL;         
    gKey = NULL;         
    gCollision = NULL;         
}


void PlayerHandleEvent(SDL_Event e)
{
    VECTOR2 mousePos = GetMousePos();
    LookAtMouse(&player, mousePos);

    if(e.type == SDL_MOUSEBUTTONDOWN){

        VECTOR2 playerPos;
        playerPos.x = player.rect.x;
        playerPos.y = player.rect.y;


        player.canShoot = 0;
        VECTOR2 dir = GetVector(playerPos, mousePos);
        dir = Normalize(dir);
        Shoot(dir.x, dir.y);
    }
    if(e.type == SDL_MOUSEBUTTONUP && player.canShoot == 1 ){
        player.canShoot = 1;
    }
}

void DrawIntro()
{
    SDL_RenderCopy( window.renderer, logoTexture, NULL, NULL );

    SDL_SetTextureBlendMode(fadeTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( fadeTexture, alpha );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, NULL );
    
    if(fadeInDone == 0)
        fadeInDone = FadeIn(&alpha);
    else
    {
         fadeOutDone = FadeOut(&alpha);
        
    }

    if(fadeOutDone == 1){
    	
        scene = START;
        Mix_PlayChannel(-1, gStart, -1);
		Mix_VolumeChunk(gStart, 60);
        fadeInDone = 0;
        fadeOutDone = 0;
    }
}

SDL_Texture* highScoreNumbersTexture[10];
SDL_Texture* highScoreNamesTexture[10];
SDL_Texture* highScoreIndexTexture[10];

void ReadScoreTextures()
{
    int i = 0;
    SDL_Color textColor = { 0xBD, 0x39, 0x20 };

    for (i = 0; i < 10; i++){
        //Load Numbers
        char scoreString[10] = {};
        sprintf(scoreString,"%i", vetor[i]);
        loadFromRenderedText3(scoreString, textColor, &highScoreNumbersTexture[i]); 
        //Load Names
        loadFromRenderedText3(vetorSTR[i], textColor, &highScoreNamesTexture[i]);
        //Load Index
        char index[10];
        sprintf(index, "%i", i);
        index[1] = '.';      
        loadFromRenderedText3(index, textColor, &highScoreIndexTexture[i]);
    }

    //ScoreText
    char recordes[50];
    //recordes[0] = 'F';
    strcpy(recordes, "Recordes");
    loadFromRenderedText3(recordes, textColor, &recordesTexture);
}

void DrawHighScore()
{
    //DrawBackground
    SDL_RenderCopy( window.renderer, backgroundGameTexture, NULL, NULL );
    //Draw BlackSquares
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackLeftRect );
    //Draw Door
    SDL_RenderCopy( window.renderer, doorLeftTexture, NULL, &doorLeftRect );
    //Draw Border
    SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );
    //Draw Font
    SDL_Color textColor = { 0xBD, 0x39, 0x20 };
    SDL_Rect highScoreRect;
    SDL_Rect indexRect;
    SDL_Rect highScoreNumbersRect;
    SDL_Rect highScoreTextRect;

    highScoreTextRect.x = 280;
    highScoreTextRect.y = 50;
    highScoreTextRect.w = 120;
    highScoreTextRect.h = 40;

    for(i = 0; i < 10 ; i ++){
        highScoreRect.x = 280;
        highScoreRect.y = 115 + (40 * i);
        highScoreRect.w = 50;
        highScoreRect.h = 20;

        indexRect.x = 250;
        indexRect.y = 115 + (40 * i);
        indexRect.w = 40;
        indexRect.h = 20;

        
        highScoreNumbersRect.x = 400;
        highScoreNumbersRect.y = 115 + (40 * i);
        highScoreNumbersRect.w = 15;
        highScoreNumbersRect.h = 20;


        if (vetor[i] > 9)
        	highScoreNumbersRect.w = 30;

        if (vetor[i] > 99)
        	highScoreNumbersRect.w = 55;

        if (vetor[i] > 999)
        {
        	highScoreNumbersRect.w = 75;

        }

        

        SDL_RenderCopy( window.renderer, highScoreNumbersTexture[i], NULL,&highScoreNumbersRect );
        SDL_RenderCopy( window.renderer, highScoreNamesTexture[i], NULL,&highScoreRect );
        SDL_RenderCopy( window.renderer, highScoreIndexTexture[i], NULL,&indexRect );
    }

    SDL_RenderCopy( window.renderer, recordesTexture, NULL,&highScoreTextRect );

    //Draw Player 
    if(scene != MENU_AND_GAME)
        DrawPlayer(player, &window);
}

void DrawCredits()
{
    //DrawBackground
    SDL_RenderCopy( window.renderer, backgroundCredits, NULL, NULL );
    //Draw Player 
    if(scene != MENU_AND_GAME)
        DrawPlayer(player, &window);
    //Draw BlackSquares
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackRightRect );
    //Draw Door
    SDL_RenderCopy( window.renderer, doorRightTexture, NULL, &doorRightRect );
    //Draw Border
    SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );
}

void DrawPreMenu()
{

    SDL_RenderCopy( window.renderer, introTexture, NULL, &introRect );
     SDL_RenderCopy( window.renderer, spacetoskipTexture, NULL, &spacetoskipRect );
   
    SDL_SetTextureBlendMode(fadeTexture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod( fadeTexture, alpha );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, NULL );
    
    if(fadeInDone == 0){
        fadeInDone = FadeIn(&alpha);
    }
    else if (introRect.y < -800){
        fadeOutDone = FadeOut(&alpha);
    }
        
    if(fadeOutDone == 1){
        scene = MENU;
        fadeInDone = 0;
        fadeOutDone = 0;
    }

   
        introRect.y --;

        

    

   
}

SDL_Texture* allLettersTexture[26];
SDL_Texture* playerDeadHighScore;

void ReadAllLetters()
{
    int i = 0;
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    for (i = 0; i < 26; i++){
        //Load Index
        char letter[2];
        char c = 'A' + i;
        letter[0] = c;
        letter[1] = '\0';    
        loadFromRenderedText3(letter, textColor, &allLettersTexture[i]);
    }
}

int currentLetter = 0;
int currentIndexLetter[3] = {0, 0, 0};
void DrawPlayerDead()
{
    //Desenha o score para colocar o nome
    
    //Draw Player 
    
    DrawPlayer(player, &window);
    
    SDL_RenderCopy( window.renderer, backgroundGameTexture, NULL, NULL );
    //Draw BlackSquares
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackLeftRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackRightRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackUpRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackDownRect );
    //Draw Door
    SDL_RenderCopy( window.renderer, doorLeftTexture, NULL, &doorLeftRect );
    SDL_RenderCopy( window.renderer, doorRightTexture, NULL, &doorRightRect );
    SDL_RenderCopy( window.renderer, doorUpTexture, NULL, &doorUpRect );
    SDL_RenderCopy( window.renderer, doorDownTexture, NULL, &doorDownRect );
    //Draw Border
    SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );
    //Draw Border
    SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );

    if (currentLetter == 0)
    {
    	SDL_RenderCopy( window.renderer, nameDeadTexture_stage0, NULL, &nameDeadRect);
    }

    else if (currentLetter == 1)
    {
    	SDL_RenderCopy( window.renderer, nameDeadTexture_stage1, NULL, &nameDeadRect);
    }

    else if (currentLetter == 2)
    {
    	SDL_RenderCopy( window.renderer, nameDeadTexture_stage2, NULL, &nameDeadRect);
    }

    int i = 0;
    for(i = 0; i < 3; i++){
        SDL_Rect lettersRect;
        lettersRect.x = 195 + (72 * i);
        lettersRect.y = 270;
        lettersRect.w = 60;
        lettersRect.h = 90;
        
        SDL_RenderCopy( window.renderer, allLettersTexture[currentIndexLetter[i]], NULL,&lettersRect );
    }

    SDL_Rect scorePlayerDeadRect;
        scorePlayerDeadRect.y = 270;
        scorePlayerDeadRect.h = 90;

        if(score < 10){
        scorePlayerDeadRect.x = 480;
        scorePlayerDeadRect.w = 60;
        }
        else
        { 
        scorePlayerDeadRect.x = 450;
        scorePlayerDeadRect.w = 120;
       

        }
    SDL_RenderCopy( window.renderer, playerDeadHighScore, NULL,&scorePlayerDeadRect );
    
}

void DrawMenu()
{
    

    //Draw Background
    SDL_RenderCopy( window.renderer, backgroundTexture, NULL, NULL );
    //Draw BlackSquares
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackLeftRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackRightRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackUpRect );
    SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackDownRect );
    //Draw Door
    SDL_RenderCopy( window.renderer, doorLeftTexture, NULL, &doorLeftRect );
    SDL_RenderCopy( window.renderer, doorRightTexture, NULL, &doorRightRect );
    SDL_RenderCopy( window.renderer, doorUpTexture, NULL, &doorUpRect );
    SDL_RenderCopy( window.renderer, doorDownTexture, NULL, &doorDownRect );
    //Draw Border
    SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );
    //DrawKey
    SDL_RenderCopy( window.renderer, keyTexture, NULL, &keyRect );

    //Draw Player 
    DrawPlayer(player, &window);

    
    if(fadeInDone == 0)
        fadeInDone = FadeIn(&alpha);

}

void tookDamageSprite()
{
	
		bloodRect.x = player.rect.x;
		bloodRect.y = player.rect.y;
		bloodRect.w = player.rect.w + 5;
		bloodRect.h = player.rect.h + 5;

		 SDL_RenderCopy( window.renderer, bloodTexture, NULL, &bloodRect );

		if (tookdamage_delay > 20)
		{
			tookdamage_delay = 0;
		}
}


void DrawGame()
{
        //DrawBackground
        SDL_RenderCopy( window.renderer, backgroundGameTexture, NULL, NULL );

        //SDL_RenderCopy( window.renderer, backgroundTexture, NULL, NULL );

        //Draw BlackSquares
        SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackLeftRect );
        SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackRightRect );
        SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackUpRect );
        SDL_RenderCopy( window.renderer, fadeTexture, NULL, &blackDownRect );

         if (wavesurvived == 4 && totalwaves % 2 == 0)
    	{
    	SDL_RenderCopy( window.renderer, potionTexture, NULL, &potionRect );
    	SDL_RenderCopy( window.renderer, fire_arrowTexture, NULL, &fire_arrowRect );
   		}

   		
   		else if (wavesurvived == 4 && totalwaves % 2 != 0)
    	{
    	SDL_RenderCopy( window.renderer, cold_arrowTexture, NULL, &cold_arrowRect );
    	SDL_RenderCopy( window.renderer, potionTexture, NULL, &potionRect );
   		}

   		if (remaining_firearrows == 0 && player.currArrow == FIRE_ARROW)
   		 {
    	
    		firearrow_enabled = 0;
    		player.currArrow == DEFAULT;

  
    	}


   		 if (remaining_coldarrows == 0 && player.currArrow == COLD_ARROW)
    	{

    		coldarrow_enabled = 0;
    		player.currArrow == DEFAULT;
   
    	}



   		if (incold > 30 && isboss == 1)
        {
                  incold = 0;
                  arrayEnemy.vetor[0].speedH = 2 + wavesurvived/2;
                  arrayEnemy.vetor[0].speedV = 2 + wavesurvived/2;
        }

        if (incold > 0)
        {
        	incold ++;
        }

        if (tookdamage_delay > 0)
        {
        	tookdamage_delay ++;
        	tookDamageSprite();
        }

        if (firearrow_enabled == 0 && coldarrow_enabled == 0)
        {
        	player.currArrow = DEFAULT;
        }
   		


        

        //Draw Enemies
        for( j=0; j<arrayEnemy.length; j++)
        {	
        	 if (arrayEnemy.vetor[j].colliding == 0)
        	 {
        	  SDL_RenderCopyEx( window.renderer, arrayEnemy.vetor[j].texture, &arrayEnemy.vetor[j].imageRect, &arrayEnemy.vetor[j].rect, 0, NULL, SDL_FLIP_NONE);
        	 }


        	 if (arrayEnemy.vetor[j].colliding == 1)
        	 {
        	 		if (arrayEnemy.vetor[j].delay_colliding < 15)
        	 		{

        	 			arrayEnemy.vetor[j].rotation += 2;


        	  			SDL_RenderCopyEx( window.renderer, arrayEnemy.vetor[j].texture, &arrayEnemy.vetor[j].imageRect, &arrayEnemy.vetor[j].rect, arrayEnemy.vetor[j].rotation, NULL, SDL_FLIP_NONE);
        	  			arrayEnemy.vetor[j].delay_colliding ++;
        	  		}

        	  		else if (arrayEnemy.vetor[j].delay_colliding < 30)
        	 		{

        	 			arrayEnemy.vetor[j].rotation -= 2;

        	  			SDL_RenderCopyEx( window.renderer, arrayEnemy.vetor[j].texture, &arrayEnemy.vetor[j].imageRect, &arrayEnemy.vetor[j].rect, arrayEnemy.vetor[j].rotation, NULL, SDL_FLIP_NONE);
        	  			arrayEnemy.vetor[j].delay_colliding ++;
        	  		}

        	  		 
        	  	
        	 }

        	 if (arrayEnemy.vetor[j].delay_colliding >= 30)
        	 		 
        	 		 {
        	 			arrayEnemy.vetor[j].delay_colliding = 0;
        	 			arrayEnemy.vetor[j].colliding = 0;
        	 		 }

        }
        

         if (infire > 0 && infire < 70){
    	   //SDL_RenderCopy( window.renderer, hitfireTexture, NULL, &(hitfire.rect) );
           SDL_RenderCopyEx( window.renderer, hitfireTexture, &(hitfire.image), &(hitfire.rect), 0, NULL, SDL_FLIP_NONE);

           hitfire.delaySprite ++;
        	if(hitfire.delaySprite > 15){
            hitfire.delaySprite = 0;
            hitfire.spritePos++;

           if(hitfire.spritePos >= hitfire.spriteMax)
            hitfire.spritePos = 0;

            hitfire.image.x = 48 + (hitfire.spritePos * 48);
        	}
    	   
   		}

   		if (infire > 0)
   		{
   			infire ++;
   		}

   		if (infire > 70)
   		{
   			infire = 0;
   		}

   		if (incold > 0 && incold < 70){
   			if (wavesurvived != 3)
   			{
   				hitcoldRect.w = 36;
   				hitcoldRect.w = 36;

   				SDL_RenderCopyEx( window.renderer, NULL, &arrayEnemy.vetor[j].imageRect, &hitcoldRect, arrayEnemy.vetor[j].rotation, NULL, SDL_FLIP_NONE);

   			}

   			

   			if (wavesurvived == 3)
   			{
   				hitcoldRect.h = 48;
   				hitcoldRect.w = 48;
   				SDL_RenderCopy( window.renderer, hitcoldTexture, NULL, &hitcoldRect);
   			}
   			else
   			{
   			hitcoldRect.w = 28;
   			hitcoldRect.w = 28;
   			SDL_RenderCopy( window.renderer, hitcoldTexture, NULL, &hitcoldRect);
	
   			}

    	    
        	
        	}

        	if (incold > 0)
   		{
   			incold ++;
   		}

   		if (incold > 70)
   		{
   			incold = 0;
   		}
    	   
   		

        //Draw Door
        SDL_RenderCopy( window.renderer, doorLeftGameTexture, NULL, &doorLeftRect );
        SDL_RenderCopy( window.renderer, doorRightGameTexture, NULL, &doorRightRect );
        SDL_RenderCopy( window.renderer, doorUpGameTexture, NULL, &doorUpRect );
        SDL_RenderCopy( window.renderer, doorDownGameTexture, NULL, &doorDownRect );
        
        
       
        //Draw Player 
        if(scene != MENU_AND_GAME)
        DrawPlayer(player, &window);

         //Draw Shot
        for( i=0; i<arrayShot.length; i++){

            SDL_Point a;
            a.x = 0 + arrayShot.vetor[i].rect.w/2;
            a.y = 0 + arrayShot.vetor[i].rect.h/2;             
             SDL_RenderCopyEx( window.renderer, arrayShot.defaultShotTexture, NULL, &arrayShot.vetor[i].rect, arrayShot.vetor[i].rotation, &a, SDL_FLIP_NONE );
       }

       

       

       //Draw Border

       SDL_RenderCopy( window.renderer, borderTexture, NULL, NULL );
       
        //Draw Font
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        char scoreText[100];
        sprintf(scoreText, "%i", score);
        loadFromRenderedText(scoreText, textColor);

        if(score > 9)
        	fontRect.w = 30;
        if(score > 99)
        	fontRect.w = 55;
        if(score > 999)
        		fontRect.w = 75;


        SDL_RenderCopy( window.renderer, scoreTexture, NULL, &fontRect);
}

void DrawPause()
{
    SDL_RenderCopy( window.renderer, pauseTexture, NULL, &pauseTextureRect);
}

int startscreen_blink = 60;
void DrawPresstoStart()
{

	

	if (startscreen_blink > 29)
	{
	SDL_RenderCopy( window.renderer, startTexture, NULL, NULL);
	}

	else if (startscreen_blink < 30)
	{
	SDL_RenderCopy( window.renderer, startTexture_blink, NULL, NULL);
	}
    
    

    startscreen_blink --;

    if (startscreen_blink == 0)
    {
    	startscreen_blink = 60;
    }


}

void Draw()
{
    if(window.minimized == 1)
        return;

    //Screen
    SDL_SetRenderDrawColor( window.renderer, 0000, 0000, 0000, 0000 );
    SDL_RenderClear(window.renderer);
    
    if(scene == INTRO){
        DrawIntro();
    }
    if(scene == PRE_MENU){
        DrawPreMenu();
    }
    if(scene == GAME) {
        DrawGame();
   		DrawMunition();
    }
    if (scene == MENU){   
        DrawMenu();
        DrawMunition();
    }

    if(scene == HIGHSCORE){
        DrawHighScore();
    }

    if(scene == CREDITS){
        DrawCredits();
    }
    if (scene == PLAYER_DEAD){
    	DrawPlayerDead();
    }

    if (scene == START){
    	DrawPresstoStart();
    }

    if(pause == 1){
        DrawPause();
    }

    if(scene == GAME || scene == MENU){
       //Draw Shot
        for( i=0; i<arrayShot.length; i++){
            SDL_Point a;
            a.x = 0 + arrayShot.vetor[i].rect.w/2;
            a.y = 0 + arrayShot.vetor[i].rect.h/2;             
               


             SDL_RenderCopyEx( window.renderer, arrayShot.vetor[i].texture, NULL, &arrayShot.vetor[i].rect, arrayShot.vetor[i].rotation, &a, SDL_FLIP_NONE );
            
          
        }
   }

    SDL_RenderPresent(window.renderer); 
}

void DrawMunition(){
    if(player.currArrow == KEY)
    {
         SDL_RenderCopy( window.renderer, keyTexture, NULL, &munitionRect );
    }

     if(player.currArrow == DEFAULT)
     {
         SDL_RenderCopy( window.renderer, arrayShot.defaultShotTexture, NULL, &munitionRect );
     }

     if(player.currArrow == FIRE_ARROW )
    {
         SDL_RenderCopy( window.renderer, fire_arrowTexture, NULL, &munitionRect );
    }
    if(player.currArrow == COLD_ARROW )
    {
         SDL_RenderCopy( window.renderer, cold_arrowTexture, NULL, &munitionRect );
    }


    
    	
}




void TakeKey(){
    if(Collision_Rect_Rect(player.rect, keyRect) == 1){
        Mix_PlayChannel(-1,gKey,0);
        keyRect.x = 999;
        player.currArrow = KEY;
    }
}

void TakeFire_Arrow(){
    if(Collision_Rect_Rect(player.rect, fire_arrowRect) == 1 && wavesurvived == 4 && totalwaves % 2 == 0){
        fire_arrowRect.x = 999;
        player.currArrow = FIRE_ARROW;
        
        remaining_firearrows = 15;
        firearrow_enabled = 1;
    }
}

void TakeCold_Arrow(){
    if(Collision_Rect_Rect(player.rect, cold_arrowRect) == 1 && wavesurvived == 4 && totalwaves % 2 != 0){
        cold_arrowRect.x = 999;
        player.currArrow = COLD_ARROW;
        
        remaining_coldarrows = 15;
        coldarrow_enabled = 1;

    }
}

void TakePotion(){

 	if(Collision_Rect_Rect(player.rect, potionRect) == 1 && wavesurvived == 4){
        	

        	potionRect.x = 999;
        	if (player.hp + 8 > 34)
        	{
        		player.hp = 34;
        	}

        	else
        	{
        		player.hp += 8;
        	}

      }  	

}

void Update()
{
    if(scene == GAME || scene == MENU){
        UpdateShotPosition();
        UpdateKeyBoard();
        Collision();
    }
    if(scene == GAME){
    	TakePotion();
    	TakeFire_Arrow();
    	TakeCold_Arrow();
        PlayerVunerability();
        GameOver();
        CreateRound();
        AnimateEnemy();
    }
    if(scene == MENU){
        TakeKey();
        Collision();
    }
    if(scene == PRE_MENU){
       UpdateKeyBoard();
    }

    if(scene == HIGHSCORE){
       UpdateKeyBoard();
       Collision();
    }
    if(scene == CREDITS){
       UpdateKeyBoard();
       Collision();
    }
    if (scene == PLAYER_DEAD){
        DrawPlayerDead();
        UpdatePlayerDeadKeyBoard();
    }
    if (scene == START)
    {
    	const Uint8 *keystates = SDL_GetKeyboardState( NULL );
			
		if(keystates[ SDL_SCANCODE_RETURN] )
		{

            scene = PRE_MENU;
            Mix_FreeChunk(gStart);

        }
              
    }

}

void Reajust(int* vetor, int pos, int number){
    if(pos == 10)
        return;

    int newNumber = vetor[pos];
    
    vetor[pos] = number;

    Reajust(vetor, pos + 1, newNumber);
}

void ReajustSTR(char vetor[][10], int pos, char* name){
    if(pos == 10)
        return;

    char newName[10];
    strcpy(newName,vetor[pos]);
    //printf("%s\n",name );
    
    strcpy(vetor[pos],name);

    ReajustSTR(vetor, pos + 1, newName);
}

void openFileWrite2(char name[3])
{
    int numero;
    int j;

    arquivo = fopen("arquivo.txt","w");
    arquivoSTR = fopen("arquivoSTR.txt", "w");

    
    for(i = 0; i < 10; i++){
        if(score > vetor[i])
        {
            
            Reajust(vetor, i, score);
            
            //scanf("Digite seu nome: %s", name);
            ReajustSTR(vetorSTR, i, name);
            break;
        }
    }


    

    for(i = 0; i < 10; i++){    

            //printf("%i\n",vetor[i] );
            fprintf(arquivo,"%d ",vetor[i]);
            fprintf(arquivoSTR,"%s ",vetorSTR[i]);
            
    }

    printf("Arquivo criado com sucesso");
    fclose(arquivo);
    fclose(arquivoSTR);

}

void openFileWrite()
{
    int numero;
    int j;

    arquivo = fopen("arquivo.txt","w");
    arquivoSTR = fopen("arquivoSTR.txt", "w");

    
    for(i = 0; i < 10; i++){
        if(score > vetor[i])
        {
            
            Reajust(vetor, i, score);
            char name[10];
            
            //scanf("Digite seu nome: %s", name);
            ReajustSTR(vetorSTR, i, "Felcks");
            break;
        }
    }


    

    for(i = 0; i < 10; i++){    

            //printf("%i\n",vetor[i] );
            fprintf(arquivo,"%d ",vetor[i]);
            fprintf(arquivoSTR,"%s ",vetorSTR[i]);
            
    }

    printf("Arquivo criado com sucesso");
    fclose(arquivo);
    fclose(arquivoSTR);

}


void openFileRead()
{
    arquivo = fopen("arquivo.txt","r");
    arquivoSTR = fopen("arquivoSTR.txt", "r");

    i = 0;
    while (!feof(arquivo))
    { 
            fscanf(arquivo,"%d",&vetor[i]);
            fscanf(arquivoSTR,"%s",vetorSTR[i]);
            i++;
    }

    ReadScoreTextures();

    fclose(arquivo);
    fclose(arquivoSTR);
}
void Collision()
{
    player.rect = Collision_Rect_Screen(player.rect, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Collision Shot and Enemy
    for(j = 0; j<arrayEnemy.length; j++){
        for( i = 0; i<arrayShot.length; i++){
            if(Collision_Rect_Rect(arrayEnemy.vetor[j].rect, arrayShot.vetor[i].rect) == 1){
                
                Mix_PlayChannel(-1,gCollision,0);
            	

            	if (player.currArrow == FIRE_ARROW)
                {
                	infire = 1;
                	hitfire.rect.x = arrayEnemy.vetor[j].rect.x;
                    hitfire.rect.y = arrayEnemy.vetor[j].rect.y;
                }

                if (player.currArrow == COLD_ARROW)
                {
                	incold = 1;
                	hitcoldRect.x = arrayEnemy.vetor[j].rect.x;
                    hitcoldRect.y = arrayEnemy.vetor[j].rect.y;
                }

               

                if(isboss == 1)
                {
                    if (player.currArrow == DEFAULT)
                    {
                    	 bossdamage ++;

                    }
                    else if (player.currArrow == FIRE_ARROW)
                    {
                    	bossdamage += 2;
                    }
                    else if (player.currArrow == COLD_ARROW)
                    {
                    	
                    		arrayEnemy.vetor[j].speedH = 1;
                    		arrayEnemy.vetor[j].speedV = 1;
                    		incold = 1;
                    		bossdamage ++;
                    }


                        if(bossdamage >= 2 && bossdamage <= 4){
                            arrayEnemy.vetor[j].currentStageDamaged = 3;
                        }

                        else if(bossdamage > 4 && bossdamage < 6){
                            arrayEnemy.vetor[j].currentStageDamaged = 6;
                        }

                        else if(bossdamage >= 6){
                            arrayEnemy.vetor[j].currentStageDamaged = 9;
                        }
                                         


                    if(bossdamage >= 10 && totalwaves % 2 == 0)
                    {                        
                        score += 10;                        

                        potionRect.x = arrayEnemy.vetor[j].rect.x - 20;
                        potionRect.y = arrayEnemy.vetor[j].rect.y - 20;

                        fire_arrowRect.x = arrayEnemy.vetor[j].rect.x ;
                        fire_arrowRect.y = arrayEnemy.vetor[j].rect.y ;

                        

                        
                     
                        RemoveAt_Enemy(&arrayEnemy, j);
                        isboss = 0;
                        bossdamage = 0;

                        

                    }


                    

                    if(bossdamage >= 15 && totalwaves % 2 != 0)
                    {
                        
                        
                        score += 30;
                        

                        potionRect.x = arrayEnemy.vetor[j].rect.x - 20;
                        potionRect.y = arrayEnemy.vetor[j].rect.y - 20;

                        cold_arrowRect.x = arrayEnemy.vetor[j].rect.x + 30;
                        cold_arrowRect.y = arrayEnemy.vetor[j].rect.y;
       

                        RemoveAt_Enemy(&arrayEnemy, j);
                        isboss = 0;
                        bossdamage = 0;

                        

                    }

                    

                }
                else
                {

                RemoveAt_Enemy(&arrayEnemy, j);
                
                score += 1 + wavesurvived + totalwaves + 1;

                }

                RemoveAt_Shot(&arrayShot, i);

                

            }
        }
    }



     //Collison Enemy_border + follow player
    for(j = 0; j< arrayEnemy.length; j++){
       // arrayEnemy.vetor[j].rect = Collision_Rect_Screen(arrayEnemy.vetor[j].rect, SCREEN_WIDTH, SCREEN_HEIGHT);

        arrayEnemy.vetor[j].rect = ChasePlayer(arrayEnemy.vetor[j].rect, player.rect, &arrayEnemy.vetor[j]);
    }

     //Collision Enemy_Player
    for(j = 0; j<arrayEnemy.length; j++){        
       if(Collision_Rect_Rect(player.rect, arrayEnemy.vetor[j].rect) == 1 && player.vulnerable == 1){
            Mix_PlayChannel(-1,gHitCollision,0);
            Mix_VolumeChunk(gHitCollision,128);
            tookdamage_delay = 1;


            if (wavesurvived == 3){
            player.hp -= 10;
            player.vulnerable = 0;

            }

            else
            {
                if (wavesurvived > 3 && isboss == 0)
                {
                player.hp -= (2 + wavesurvived + 1);
                player.vulnerable = 0;
                }
                else if (isboss == 0)
                {
                   player.hp -= (wavesurvived + 1);
                   player.vulnerable = 0; 
                }

            }

            arrayEnemy.vetor[j].colliding = 1;
       }
    }

    //Collision Shot_Border
    for(i=0; i<arrayShot.length; i++){
        if(Collision_Rect_Screen_Bool(arrayShot.vetor[i].rect, SCREEN_WIDTH, SCREEN_HEIGHT) == 1){
            RemoveAt_Shot(&arrayShot, i);
        }
    //Collision Potion


      
   //Collision Key Door
        if(Collision_Rect_Rect(arrayShot.vetor[i].rect, doorUpRect) == 1){
            if(arrayShot.vetor[i].isKey == 1){
                doorUpTexture = loadTexture("Sprites/Doors/DoorUp_1.png");
                doorDownTexture = loadTexture("Sprites/Doors/DoorDown_0.png");
                doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
                doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
                doorOpen = UP;
            }

                    
                RemoveAt_Shot(&arrayShot, i);

        }

        if(Collision_Rect_Rect(arrayShot.vetor[i].rect, doorLeftRect) == 1){
            if(arrayShot.vetor[i].isKey == 1){
                doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
                doorDownTexture = loadTexture("Sprites/Doors/DoorDown_0.png");
                doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
                doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_1.png");
                doorOpen = LEFT;
            }
            
                    
                RemoveAt_Shot(&arrayShot, i);

        }

        if(Collision_Rect_Rect(arrayShot.vetor[i].rect, doorDownRect) == 1){
            if(arrayShot.vetor[i].isKey == 1){
                doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
                doorDownTexture = loadTexture("Sprites/Doors/DoorDown_1.png");
                doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
                doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
                doorOpen = DOWN;
            }
            
                    
                RemoveAt_Shot(&arrayShot, i);

        }

        if(Collision_Rect_Rect(arrayShot.vetor[i].rect, doorRightRect) == 1){
            if(arrayShot.vetor[i].isKey == 1){
                doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
                doorDownTexture = loadTexture("Sprites/Doors/DoorDown_0.png");
                doorRightTexture = loadTexture("Sprites/Doors/DoorRight_1.png");
                doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
                doorOpen = RIGHT;
            }
            
                    
                RemoveAt_Shot(&arrayShot, i);

        }   


    }

    //Collision Payer Door Open

    if (scene == MENU && doorOpen == UP)
    {
        if (Collision_Rect_Rect(player.rect, doorUpRect) == 1)
        {
            scene = GAME;

            Mix_FreeChunk( gMusicMenu );
            Mix_PlayChannel(-1,gMusic,-1);
            Mix_VolumeChunk(gMusic, 120);
            player.rect.x = SCREEN_WIDTH/2;
            player.rect.y = SCREEN_HEIGHT - 80;
        }
    }

    if (scene == MENU && doorOpen == DOWN)
    {
        if (Collision_Rect_Rect(player.rect, doorDownRect) == 1)
        {
            quit = 1;
        }
    }

    if (scene == MENU && doorOpen == RIGHT)
    {
        if (Collision_Rect_Rect(player.rect, doorRightRect) == 1)
        {
            doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_1.png");
            scene = HIGHSCORE;
            player.rect.x = 120;
            player.rect.y = SCREEN_HEIGHT/2;
        }
    }

	if (scene == MENU && doorOpen == LEFT)
    {
        if (Collision_Rect_Rect(player.rect, doorLeftRect) == 1)
        {
            doorRightTexture = loadTexture("Sprites/Doors/DoorRight_1.png");
           
            player.rect.x = SCREEN_WIDTH - 180;
            player.rect.y = SCREEN_HEIGHT/2;

            scene = CREDITS;
        }
    }

    if (scene == HIGHSCORE)
    {
        if (Collision_Rect_Rect(player.rect, doorLeftRect) == 1)
        {
            
            player.rect.x = SCREEN_WIDTH - 160;
            player.rect.y = SCREEN_HEIGHT/2 - 50;

            doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
            doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
            doorOpen= NONE;
            scene = MENU;

        }
    }

     if (scene == CREDITS)
    {
        if (Collision_Rect_Rect(player.rect, doorRightRect) == 1)
        {
            
            player.rect.x = 120;
            player.rect.y = SCREEN_HEIGHT/2 - 50;

            doorLeftTexture = loadTexture("Sprites/Doors/DoorLeft_0.png");
            doorRightTexture = loadTexture("Sprites/Doors/DoorRight_0.png");
            doorOpen= NONE;
            scene = MENU;

        }
    }


}

void LookAtMouse(PLAYER* player, VECTOR2 mousePos)
{
  //  printf("%i\n",mousePos );
    int x = mousePos.x - (*player).rect.x;
    int y = mousePos.y - (*player).rect.y;
    long double angle = atan2(y,x);
    (*player).rotationDegrees = (angle * 180/ M_PI);
}


void myGetMousePos(SDL_Event e)
{
	if(e.type == SDL_MOUSEMOTION){
		myMouseX = e.motion.x;
		myMouseY = e.motion.y;
	}
}

VECTOR2 GetMousePos()
{
   //Change cursor
    SDL_Cursor* cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);


    //MOUSE MOTION -- EVENTO
    int SDL_SetRelativeMouseMode(SDL_bool enabled);

    


    VECTOR2 mousePos;
    mousePos.x = myMouseX;
    mousePos.y = myMouseY;
    //SDL_GetMouseState( &mousePos.x, &mousePos.y);

    return mousePos;
}

//Returns a copy of array with length - 1 (Removes the element on index i);
void RemoveAt_Shot(ARRAYSHOT *arrayShot, int pos)
{
    SHOT copy[(*arrayShot).length-1];

    int oldArrayPos = 0;
    int newArrayPos = 0;
    for(oldArrayPos=0; oldArrayPos<(*arrayShot).length; oldArrayPos++){
        if(oldArrayPos != pos){
             copy[newArrayPos] = (*arrayShot).vetor[oldArrayPos];
             newArrayPos++;
        }
    }

    (*arrayShot).length--;
    for(j=0; j<(*arrayShot).length; j++){
        (*arrayShot).vetor[j] = copy[j];
    }
}

//Returns a copy of array with length - 1 (Removes the element on index i);
void RemoveAt_Enemy(ARRAYENEMY *arrayEnemy, int pos)
{
    ENEMY copy[(*arrayEnemy).length-1];

    int oldArrayPos = 0;
    int newArrayPos = 0;
    for(oldArrayPos=0; oldArrayPos<(*arrayEnemy).length; oldArrayPos++){
        if(oldArrayPos != pos){
             copy[newArrayPos] = (*arrayEnemy).vetor[oldArrayPos];
             newArrayPos++;
        }
    }

    (*arrayEnemy).length--;
    for(j=0; j<(*arrayEnemy).length; j++){
        (*arrayEnemy).vetor[j] = copy[j];
    }
}


int posVector[24];
void CreateRound(){



    for(i = 0; i< 24 ; i++)
        posVector[i] = 0;

    if (wavesurvived >= 5)
    {
    	totalwaves += wavesurvived;
    	wavesurvived -= 5;
    }

    if(arrayEnemy.length == 0){
       
        if (wavesurvived == 0){

        	for(i=0; i<WAVE1; i++){
            CreateEnemy();
           	}
            wavesurvived ++;
        }
        else if (wavesurvived == 1){

        	for(i=0; i<WAVE2; i++){
            CreateEnemy();
            }
            wavesurvived ++;
        }
        else if (wavesurvived == 2){

        	isboss = 1;

        	CreateBoss();

            
            wavesurvived ++;
        
         }
         else if (wavesurvived == 3){


        	for(i=0; i<WAVE4; i++){

            CreateEnemy();
            
            }

            wavesurvived ++;
         }
         else if (wavesurvived == 4){

        	for(i=0; i<WAVE5; i++){
            CreateEnemy();
            }
            wavesurvived ++;
        
         }

    }

    
    
    
}
void GameOver()
{
    if(player.hp <= 0){
        scene = PLAYER_DEAD;

        char a[10];
        sprintf(a, "%i", score);
        SDL_Color color = { 0xFF, 0xFF, 0xFF};

        
        loadFromRenderedText3(a, color, &playerDeadHighScore);
       // openFileWrite();  
        //score = 0;
        
        
        //CreateComponents();
    }
}


void CreateEnemy()
{
    int x[4] = {365, -30, 365, SCREEN_WIDTH + 30};
    int y[4] = {-30, 250, SCREEN_HEIGHT + 30, 250};
    int quad;
    int pos;
    int sortedNumber;

     do{
            sortedNumber = rand() % 24;
            pos = sortedNumber % 6;
            quad = sortedNumber / 6;
    }while(posVector[sortedNumber]);

        posVector[sortedNumber] = 1;

        if(quad % 2 == 1){
        x[quad] -= pos%3 * 41;
        y[quad] += pos/3 * 20;
    }
    else {
        y[quad] -= pos%3 * 41;
        x[quad] += pos/3 * 20;
    }
        


    
    
    ENEMY enemy;
    enemy.rect.x = x[quad];
    enemy.rect.y = y[quad];
    enemy.rect.w = 41;

    enemy.rect.h = 32;
 
    enemy.speedH = 2;
    enemy.speedV = 2;
    //enemy.texture = ghost;
    enemy.countIA = 0;
    enemy.imageRect.x = 0;
    enemy.imageRect.y = 0;
    enemy.spritePos = rand() % 3;
    enemy.imageRect.w =  16;
    enemy.imageRect.h = 16;
    enemy.spriteMax = 2;
    enemy.delaySprite = 0;
    enemy.orientation = 0; //0 = left, 1 = right
    enemy.currentStageDamaged = 0;
    enemy.colliding = 0;
    enemy.rotation = 0;
    enemy.delay_colliding = 0;
   
    

    if (totalwaves >= 5)
    {
        enemy.speedH ++;
        enemy.speedV ++;
    }

    if (enemy.texture == skeleton || enemy.texture == skeletonmirrored)
    {
    	enemy.spriteMax = 3;
        enemy.spritePos = rand() % 4;
    }


    
 

  

    arrayEnemy.vetor[arrayEnemy.length] = enemy;
    arrayEnemy.length++;
    
}

void CreateBoss()
{
    int x[4] = {365, -30, 365, SCREEN_WIDTH + 30};
    int y[4] = {-30, 250, SCREEN_HEIGHT + 30, 250};
    int quad;
    int pos;
    int sortedNumber;

     do{
            sortedNumber = rand() % 24;
            pos = sortedNumber % 6;
            quad = sortedNumber / 6;
    }while(posVector[sortedNumber]);

        posVector[sortedNumber] = 1;

        if(quad % 2 == 1){
        x[quad] -= pos%3 * 41;
        y[quad] += pos/3 * 20;
    }
    else {
        y[quad] -= pos%3 * 41;
        x[quad] += pos/3 * 20;
    }
        


    
    
    ENEMY enemy;
    enemy.rect.x = x[quad];
    enemy.rect.y = y[quad];
    enemy.rect.w = 61;
    enemy.rect.h = 52;
    enemy.speedH = 2 + wavesurvived/2;
    enemy.speedV = 2 + wavesurvived/2;
    //enemy.texture = boss1;
    enemy.countIA = 0;
    enemy.imageRect.x = 0;
    enemy.imageRect.y = 0;
    enemy.spritePos = rand() % 3;
    enemy.imageRect.w =  16;
    enemy.imageRect.h = 16;
    enemy.spriteMax = 2;
    enemy.delaySprite = 0;
    enemy.orientation = 0;
    enemy.currentStageDamaged = 0;
    enemy.colliding = 0;
    enemy.rotation = 0;
    enemy.delay_colliding = 0;
    
  

    arrayEnemy.vetor[arrayEnemy.length] = enemy;
    arrayEnemy.length++;

    
}



void AnimateEnemy(){
    for(i = 0; i < arrayEnemy.length; i++){
        ENEMY* enemy = &(arrayEnemy.vetor[i]);

        if (wavesurvived < 3)
   		{
    	
    		if ((*enemy).orientation == 1)
    		{
        		(*enemy).texture = ghost;  
        		
    		}
    		else if ((*enemy).orientation == 0)
    		{
    			(*enemy).texture = ghostmirrored;  
        		

    		}

    	}

    	if (wavesurvived == 3)
   		{
    	
    		if ((*enemy).orientation == 1)
    		{
    			if (totalwaves % 2 != 0)
    			{
    				(*enemy).texture = boss2;  
    			}
    			else
    			{
    				(*enemy).texture = boss1; 
    			}
        		
    		}
    		else if ((*enemy).orientation == 0)
    		{
    			if (totalwaves % 2 != 0)
    			{
    				(*enemy).texture = boss2mirrored;  
    			}
    			else
    			{
    				(*enemy).texture = boss1mirrored; 
    			}
    		}

    	}

    	if (wavesurvived > 3)
   		{
    	
    		if ((*enemy).orientation == 1)
    		{
        		(*enemy).texture = skeleton;  
        		
    		}
    		else if ((*enemy).orientation == 0)
    		{
    			(*enemy).texture = skeletonmirrored;  
    		}
    	}


        (*enemy).delaySprite ++;
        if((*enemy).delaySprite > 20){
            (*enemy).delaySprite = 0;
            (*enemy).spritePos++;

           if((*enemy).spritePos >= (*enemy).spriteMax + (*enemy).currentStageDamaged)
            (*enemy).spritePos = 0 + (*enemy).currentStageDamaged;

            (*enemy).imageRect.x = 16 + ((*enemy).spritePos * 16);
        }
    }
}

void PlayerVunerability(){
    if(player.vulnerable == 0){
        player.countVulnerable++;
        if(player.countVulnerable > player.minToVulnerable){
            player.countVulnerable = 0;
            player.vulnerable = 1;
        }
    }
}

void UpdateShotPosition(){
    for(i=0; i<arrayShot.length; i++){
        arrayShot.vetor[i].rect.x += arrayShot.vetor[i].currentSpeedH;
        arrayShot.vetor[i].rect.y += arrayShot.vetor[i].currentSpeedV;
    }
}

void Shoot(float directionH, float directionV)
{
    Mix_PlayChannel(-1,gScratch,0);
    Mix_VolumeChunk(gScratch,128);

    SHOT shot;
    shot.rect.x = player.rect.x + 10;
    shot.rect.y = player.rect.y;
    shot.rect.w = arrayShot.defaultShotSize;
    shot.rect.h = arrayShot.defaultShotSize;
    shot.isKey = 0;

    shot.currentSpeedH = arrayShot.defaultShotSpeed * directionH;
    shot.currentSpeedV = arrayShot.defaultShotSpeed * directionV;


    if(player.currArrow == DEFAULT)
            shot.texture = arrayShot.defaultShotTexture;  

    else if(player.currArrow == KEY){
        keyRect.x = 650;
        shot.isKey = 1;
        player.currArrow = DEFAULT;
        shot.texture = keyTexture;
    }
    else if(player.currArrow == FIRE_ARROW)
    {
            shot.texture = fire_arrow_usedTexture; 
    }
    else if(player.currArrow == COLD_ARROW)
    {
            shot.texture = cold_arrow_usedTexture; 
    }

    arrayShot.vetor[arrayShot.length] = shot;
    arrayShot.vetor[arrayShot.length].rotation = player.rotationDegrees;
    arrayShot.length++;
    arrayShot.delay = 0;
	
	if (player.currArrow == FIRE_ARROW)
	{
		remaining_firearrows --;
	}   

	else if (player.currArrow == COLD_ARROW)
	{
		remaining_coldarrows --;
	}   
    

}

int delayPlayerDeadKeyBoard = 0;
void UpdatePlayerDeadKeyBoard(){

    delayPlayerDeadKeyBoard++;

    if(delayPlayerDeadKeyBoard < 20)
        return;

        const Uint8 *keystates = SDL_GetKeyboardState( NULL );

        if(keystates[SDL_SCANCODE_RETURN]){
            
            char scoreName[3];
            scoreName[0] = 'A' + currentIndexLetter[0]; 
            scoreName[1] = 'A' + currentIndexLetter[1]; 
            scoreName[2] = 'A' + currentIndexLetter[2]; 

            openFileWrite2(scoreName);


            scene = MENU;

            ReadScoreTextures();
            Mix_FreeChunk(gMusic);
            doorUpTexture = loadTexture("Sprites/Doors/DoorUp_0.png");
            CreateComponents();
            doorOpen = NONE;

        }
        
        if(keystates[ SDL_SCANCODE_RIGHT] )
        {
             currentLetter++;
            delayPlayerDeadKeyBoard = 0;
        }
        else if(keystates[ SDL_SCANCODE_LEFT] ){
            currentLetter--;
            delayPlayerDeadKeyBoard = 0;
        }
        else if(keystates[ SDL_SCANCODE_UP] )
        {
            currentIndexLetter[currentLetter]++;
            delayPlayerDeadKeyBoard = 0;
        }
        else if(keystates[ SDL_SCANCODE_DOWN] ){
            currentIndexLetter[currentLetter]--;
            delayPlayerDeadKeyBoard = 0;
        }

        if(currentIndexLetter[currentLetter] < 0)
            currentIndexLetter[currentLetter] += 26;
        if(currentIndexLetter[currentLetter] > 25) 
            currentIndexLetter[currentLetter] -= 26;

        if(currentLetter > 2)
            currentLetter = 0;
        if (currentLetter < 0)
            currentLetter = 2;
}



void UpdateKeyBoard()
{
        const Uint8 *keystates = SDL_GetKeyboardState( NULL );

    if (scene != PRE_MENU)
    {

        if(keystates[ SDL_SCANCODE_ESCAPE ]){
            quit = 1;
        }
       // if (keystates[SDL_SCANCODE_I])
         //   Mix_Pause(-1);
        if (keystates[SDL_SCANCODE_M] && just_pressed == 0 && liga_audio == 0)
        {
        	Mix_Resume(-1);
        	just_pressed = 20;
        	liga_audio = 1;
        }

        if (keystates[SDL_SCANCODE_M] && just_pressed == 0 && liga_audio == 1)
        {
        	Mix_Pause(-1);
        	just_pressed = 20;
        	liga_audio = 0;
        }
            

        if(keystates [ SDL_SCANCODE_P] && pause == 0 && just_pressed == 0){
           pause = 1;
           just_pressed = 20;
        }

       

        if (just_pressed > 0)
        {
        	just_pressed --;
        }

        



        int moved = 0;

        if(keystates[ SDL_SCANCODE_D] ){
            player.rect.x += player.speed;
            player.directionH = 1;
            player.directionV = 0;
            moved = 1;

            AnimPlayer(&player);
        }
        else if(keystates[ SDL_SCANCODE_A] ){
            player.rect.x += -player.speed;
            player.directionH = -1;
            player.directionV = 0;
            moved = 1;

             AnimPlayer(&player);
        }

        if(keystates[ SDL_SCANCODE_W] ){
            player.rect.y += -player.speed;
            player.directionV = -1;
            if(moved == 0)
                player.directionH = 0;


            AnimPlayer(&player);      
        }
        
        else if(keystates[ SDL_SCANCODE_S] ){
            player.rect.y += player.speed;
            player.directionV = 1;
            if(moved == 0)
                player.directionH = 0;

            AnimPlayer(&player);
        }

        else if(keystates[ SDL_SCANCODE_Q ] && just_pressed == 0){
           

           if (player.currArrow == FIRE_ARROW)
           {
           	 player.currArrow = DEFAULT;
           }
           else if ((player.currArrow == DEFAULT || player.currArrow == COLD_ARROW) && firearrow_enabled == 1)
           {
           	player.currArrow = FIRE_ARROW;
           }

           just_pressed = 20;
        }

        else if(keystates[ SDL_SCANCODE_E ] && just_pressed == 0 ){
           

           if (player.currArrow == COLD_ARROW)
           {
           		player.currArrow = DEFAULT;
           }
           else if ((player.currArrow == DEFAULT || player.currArrow == FIRE_ARROW) && coldarrow_enabled == 1)
           {
           	player.currArrow = COLD_ARROW;
           }

           just_pressed = 20;
        }

        

        
       
    arrayShot.delay++;
    if(keystates[ SDL_SCANCODE_UP] && keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(2, -2);    
    }
    else if(keystates[ SDL_SCANCODE_UP] && keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(-2, -2);    
    }
    else if(keystates[ SDL_SCANCODE_DOWN] && keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {        
        Shoot(-2, 2);    
    }
    else if(keystates[ SDL_SCANCODE_DOWN] && keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {   
        Shoot(2, 2);    
    }

    else if(keystates[ SDL_SCANCODE_UP] && arrayShot.delay >= arrayShot.delayMin)
    {       
        Shoot(0, -2);     
    }  
    else if(keystates[ SDL_SCANCODE_DOWN] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(0, 2 );     
    } 
    else if(keystates[ SDL_SCANCODE_RIGHT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(2, 0 );     
    }  
    else if(keystates[ SDL_SCANCODE_LEFT] && arrayShot.delay >= arrayShot.delayMin)
    {
        Shoot(-2, 0 );     
    }  

	}

	if (scene == PRE_MENU)
        {
        	if(keystates[ SDL_SCANCODE_SPACE])
        	{
        		fadeInDone = 1;
        		introRect.y = -850;
        	}
        }

}

void AnimPlayer(PLAYER* player)
{
    (*player).countSprite++;
    if((*player).countSprite < 10)
        return;

    (*player).indexSprite++;
    (*player).countSprite = 0;

    if((*player).indexSprite > 7)
            (*player).indexSprite = 0;
}

void CreateComponents()
{
	coldarrow_enabled = 0;
	firearrow_enabled = 0;
	wavesurvived = 0;
	totalwaves = 0;

	LoadMusics();
        Mix_PlayChannel(-1,gMusicMenu,-1);
        Mix_VolumeChunk(gMusicMenu, MIX_MAX_VOLUME);

    doorOpen = NONE;
    score = 0;
   

    munitionRect.x = 12;
    munitionRect.y = 40;
    munitionRect.w = 34;
    munitionRect.h = 18;

    player.rect.x = SCREEN_WIDTH / 2 - 47/2;
    player.rect.y = SCREEN_HEIGHT / 2 - 22/2;
    player.rect.w = 47;
    player.rect.h = 22;
    player.speed = 3;
    player.texture = loadTexture("Sprites/PlayerSprite1.png");
    player.lifeTexture = highlifeTexture;


    player.lifeTextureBG = loadTexture("Sprites/Life_BG.png");
    player.hp = 34;
    player.lifeRect.x = player.rect.x + 5;
    player.lifeRect.y = player.rect.y - 10;
    player.lifeRect.w = player.hp;
    player.lifeRect.h = 10;
    player.vulnerable = 1;
    player.minToVulnerable = 50;
    player.countVulnerable = 0;
    player.rotationDegrees = 0;
    player.countSprite = 0;
    player.currArrow = DEFAULT;


    //memset(player.spritePosY, 0, sizeof(player.spritePosY));
   
    player.spritePosY[0] = 0;
    player.spritePosY[1] = 33;
    player.spritePosY[2] = 67;
    player.spritePosY[3] = 99;
    player.spritePosY[4] = 132;
    player.spritePosY[5] = 166;
    player.spritePosY[6] = 198;
    player.spritePosY[7] = 231;
    
    player.indexSprite = 0;
    player.imageRecort.x = 4;
    player.imageRecort.y = player.spritePosY[player.indexSprite];
    player.imageRecort.w = 47;
    player.imageRecort.h = 22;

    player.lifeRectBG.x = player.rect.x + 5;
    player.lifeRectBG.y = player.rect.y - 10;
    player.lifeRectBG.w = 35;
    player.lifeRectBG.h = 10;

    arrayShot.defaultShotSize = 20;
    arrayShot.defaultShotSpeed = 4;
    arrayShot.defaultShotTexture = loadTexture("Sprites/arrow2.png");
    arrayShot.length = 0;
    arrayShot.delay = 0;
    arrayShot.delayMin = 50;

    arrayEnemy.length = 0;
}

SDL_Texture* loadTexture( char* path )
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL )
    {
       printf("#Erro ao carregar imagem!\n");
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( window.renderer, loadedSurface );
        if( newTexture == NULL )
        {
           printf("#Erro ao carregar imagem!\n");
       	}

        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}



void CreateFont()
{
    fontRect.x = 5;
    fontRect.y = 5;
    fontRect.w = 15;
    fontRect.h = 25;

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    scoreFont = TTF_OpenFont( "Fonts/Score_Font.TTF", 28 );
    if( scoreFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        
    }
    else
    {
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        char scoreText[100];
        sprintf(scoreText, "%i", score);
        loadFromRenderedText(scoreText, textColor);
        if( scoreTexture == NULL )
        {
            printf( "Failed to render text texture!\n" );
        }
    }
}

void CreateFont2()
{
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    scoreFont = TTF_OpenFont( "Fonts/Score_Font.TTF", 28 );
    if( scoreFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        
    }
    else
    {
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        char scoreText[100];
        scoreText[0] = 'A';
        scoreText[2] = 'A';
        scoreText[1] = 'A';
        loadFromRenderedText2(scoreText, textColor, highScoreTexture);
        if( highScoreTexture == NULL )
        {
            printf( "Failed to render text texture!\n" );
        }
    }
}

void loadFromRenderedText3( char text[100], SDL_Color textColor, SDL_Texture** texture )
{
    //Render text suface
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, text, textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        *texture = SDL_CreateTextureFromSurface( window.renderer, textSurface );
        if( *texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
          //  mWidth = textSurface->w;
          //  mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void loadFromRenderedText2( char text[100], SDL_Color textColor, SDL_Texture* texture )
{
    //Render text suface
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, text, textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        highScoreTexture = SDL_CreateTextureFromSurface( window.renderer, textSurface );
        if( highScoreTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
          //  mWidth = textSurface->w;
          //  mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void loadFromRenderedText( char text[100], SDL_Color textColor )
{
    //Render text suface
    SDL_Surface* textSurface = TTF_RenderText_Solid( scoreFont, text, textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        scoreTexture = SDL_CreateTextureFromSurface( window.renderer, textSurface );
        if( scoreTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
          //  mWidth = textSurface->w;
          //  mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void LoadMusics()
{  
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    gMusic = Mix_LoadWAV("SoundsGame/MusicGame/151780__weaverfishable__8bit-mix.wav");
    //gKey = Mix_LoadWAV("SoundsGame/key.wav");
    gKey = Mix_LoadWAV("SoundsGame/KeyCollision/a.wav");
    gCollision = Mix_LoadWAV("SoundsGame/CollisionArrow/Flecha.wav");
    gMusicMenu = Mix_LoadWAV("SoundsGame/MenuMusics/somjogo.wav");
    gScratch = Mix_LoadWAV("SoundsGame/Shot/205563__everheat__arrow.wav");
    gStart = Mix_LoadWAV("SoundsGame/MenuMusics/startMusic.wav");
    gHitCollision = Mix_LoadWAV("SoundsGame/enemyHit.wav");
}


