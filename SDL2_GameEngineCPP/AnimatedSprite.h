#pragma once
#include "Sprite.h"

class AnimatedSprite: public Sprite
{
protected:
	int spriteNum = 0; //Which sprite to display for animation
	int spriteMax; //how many sprites in total for this animation
	int frameNum = 0; //which frame we are at now
	int frameMax; //number of frames for this sprite

public:
	AnimatedSprite(SDL_Texture* tex, int x, int y, double a, int _frameMax, int _spriteMax, double _speed)
		:spriteMax(_spriteMax), frameMax(_frameMax)
	{
		texture = tex;
		X= x;
		Y= y;
		angle= a;
		speed= _speed;
	}
	
	~AnimatedSprite();

	void Animate();
};

