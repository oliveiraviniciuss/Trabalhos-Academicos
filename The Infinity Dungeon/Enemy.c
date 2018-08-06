#include "Enemy.h"

SDL_Rect ChasePlayer(SDL_Rect enemyRect, SDL_Rect playerRect, ENEMY* enemy)
{



	(*enemy).countIA++;
	if((*enemy).countIA <= 2)
		return enemyRect;

	(*enemy).countIA = 0;

	
	if (enemyRect.x + (*enemy).rect.w > 110 && enemyRect.x + (*enemy).rect.w < 690 && enemyRect.y + (*enemy).rect.h > 100 && enemyRect.y + (*enemy).rect.h < 510 ){

		if(enemyRect.x + (*enemy).speedH < playerRect.x)
		{
			enemyRect.x += (*enemy).speedH;
			(*enemy).orientation = 1;
		
		}

		else if (enemyRect.x - (*enemy).speedH > playerRect.x)
		{
			enemyRect.x -= (*enemy).speedH;
			(*enemy).orientation = 0;
			
		}

		if(enemyRect.y + (*enemy).speedV < playerRect.y)
			enemyRect.y += (*enemy).speedV;
		else if (enemyRect.y - (*enemy).speedV > playerRect.y)
			enemyRect.y -= (*enemy).speedV;

		return enemyRect;

	}
	else
	{
		if (enemyRect.x + (*enemy).rect.w <= 110)
		{
				enemyRect.x += (*enemy).speedH;
				(*enemy).orientation = 1;
		}

		if (enemyRect.x + (*enemy).rect.w >= 690)
		{
				enemyRect.x -= (*enemy).speedH;
				(*enemy).orientation = 0;
		}

		if (enemyRect.y + (*enemy).rect.h <= 100 )
		{
				enemyRect.y += (*enemy).speedV;
		}

		if (enemyRect.y + (*enemy).rect.h >= 510 )
		{
				enemyRect.y -= (*enemy).speedV;
		}

		
		return enemyRect;
	}
	
}