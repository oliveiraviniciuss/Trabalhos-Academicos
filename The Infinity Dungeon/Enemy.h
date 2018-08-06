#include <SDL2/SDL.h>

typedef struct {
	SDL_Rect rect;
	SDL_Rect imageRect;
	int spritePos;
	int spriteMax;
	int countSprite;
	int delaySprite;
	SDL_Texture* texture;
	int speedH;
	int speedV;
	int directionH;
	int directionV;
	int countIA;
	int orientation;
	int currentStageDamaged;
	int colliding;
	int rotation;
	int delay_colliding;
} ENEMY;


typedef struct {
	ENEMY vetor[100];
	int length;
} ARRAYENEMY; 

typedef struct {
	SDL_Rect rect;
	SDL_Rect image;
	int spritePos;
	int spriteMax;
	int delaySprite;
	
} HITFIRE; 

SDL_Rect ChasePlayer(SDL_Rect enemyRect, SDL_Rect playerRect, ENEMY* enemy);
