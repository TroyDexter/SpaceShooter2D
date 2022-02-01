#pragma once

#include "Sprite.h"

class Asteroid: public Sprite
{
private:
	float rotationSpeed;

public:
	Asteroid(SDL_Texture* text, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed)
		:Sprite(text, srcRect, destRect), rotationSpeed(rotSpeed)
	{
		radius = 33;
	}

	void Update()
	{
		angle += rotationSpeed;
	}

	
	
	
};

