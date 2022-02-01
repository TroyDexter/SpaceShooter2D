#include "AnimatedSprite.h"

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::Animate()
{
	frameNum++;

	if(frameNum == frameMax)
	{
		frameNum = 0;
		spriteNum++;
		if(spriteNum == spriteMax)
			spriteNum = 0;
	}
}
