#pragma once
#include "AnimatedSprite.h"

class Bullet : public AnimatedSprite
{
private:
	//const double BULLET_SPEED = 20.0f;

	
public:
	Bullet(SDL_Texture* tex, int x, int y,double a, double dx, double dy)
		:AnimatedSprite(tex, x, y, a, 0, 0, 20)
	{
		radius = 8;
		dX = dx;
		dY = dy;
		spriteSrcRect = {100,0,24,24};
		spriteDestRect = {(int)(x-12), (int)(y-12),24,24};
	}
	
	void Update()
	{
		X += dX * speed;
		Y += dY * speed;
		this->UpdateDestRect();
	}
};

