#include "Player.h"
#include <algorithm>
#include "GameEngine.h"

Player::Player(SDL_Texture* tex, double x, double y)
	:AnimatedSprite(tex, x-50, y-50, 0, 1,4,0.1f)
{
	radius = 50;
	spriteSrcRect={0,0,100,100};
	spriteDestRect={ (int)X-50,(int)Y-50,100,100};
}

Player::~Player()
{
	
}

void Player::Render()
{
	for(int i=0;i<bullets.size();i++)
		bullets[i]->Render(GameEngine::GetInstance()->GetRenderer());

	
	this->AnimatedSprite::Render(GameEngine::GetInstance()->GetRenderer()); //invoke the base class renderer
}

void Player::SetIdle()
{
	spriteSrcRect.y = 0;
	frameNum = 0;
	spriteNum = 0;
}

void Player::Update()
{
	if(GameEngine::GetInstance()->KeyDown(SDL_SCANCODE_A))
		angle -= DELTA_ANGLE;
	else if(GameEngine::GetInstance()->KeyDown(SDL_SCANCODE_D))
		angle += DELTA_ANGLE;
	else if(GameEngine::GetInstance()->KeyDown(SDL_SCANCODE_SPACE))
		SpawnBullet();

	this->UpdatePlayer();
	//when bullet code is added, then we will also need to update bullets' position
	UpdateBullets();
	
	
}

void Player::MoveFoward()
{
	//convert player spaceship angle to deltaX and deltaY
	dX = cos((angle-90)*M_PI/180);
	dY = sin((angle-90)*M_PI/180);

	//Update the velocity
	velX += dX*speed;
	velY += dY*speed;

	// clamp the velocity and that is becasue we need to maintain the previous vector dX and dY
	velX=min(max(velX, -velMax*fabs(dX)), velMax*fabs(dX));
	velY=min(max(velY, -velMax*fabs(dY)), velMax*fabs(dY));
}

void Player::MoveBackward()
{
	//convert player spaceship angle to deltaX and deltaY
	dX = cos((angle-90)*M_PI/180);
	dY = sin((angle-90)*M_PI/180);

	//Update the velocity
	velX -= dX*speed;
	velY -= dY*speed;

	// clamp the velocity and that is becasue we need to maintain the previous vector dX and dY
	velX=min(max(velX, -velMax*fabs(dX)), velMax*fabs(dX));
	velY=min(max(velY, -velMax*fabs(dY)), velMax*fabs(dY));
}


void Player::UpdatePlayer()
{
	if(GameEngine::GetInstance()->KeyDown(SDL_SCANCODE_W))
	{
		spriteSrcRect.y = 100; //set y to 100 so we can start playing 2 row
		this->Animate();
		MoveFoward();
		GameEngine::GetInstance()->GetAM()->PlaySound(2,15);
	}
	else if(GameEngine::GetInstance()->KeyDown(SDL_SCANCODE_S))
	{
		spriteSrcRect.y = 100;
		this->Animate();
		MoveBackward();
		GameEngine::GetInstance()->GetAM()->PlaySound(2,15);
	}
	else if(GameEngine::GetInstance()->KeyUp(SDL_SCANCODE_W))
	{
		SetIdle();
		Mix_FadeOutChannel(15,250);
		//add some drag to slow down
		velX *= DRAG;
		velY *= DRAG;
	}
	

	X += velX; //Update x coord
	Y += velY;
	this->UpdateDestRect();

	spriteSrcRect.x = spriteSrcRect.w * spriteNum; //update the animation
}

void Player::SpawnBullet()
{
	//convert player spaceship angle to deltaX and deltaY
	dX = cos((angle-90)*M_PI/180);
	dY = sin((angle-90)*M_PI/180);
	
	if(nextShootTime >= 8)
	{
		bullets.push_back(new Bullet(texture,X,Y,angle,dX,dY));
		nextShootTime = 0;
	}
	else
	{
		nextShootTime += 1;
	}
}

void Player::UpdateBullets()
{
	for(int i=0;i<bullets.size();i++)
	{
		bullets[i]->Update();
		
		if((bullets[i]->GetX() - 24) > GameEngine::GetInstance()->windowWidth||(bullets[i]->GetX() +24) < 0 
			|| (bullets[i]->GetY() -24 )>GameEngine::GetInstance()->windowHeight||(bullets[i]->GetY() +24)<0)
		{
			DeleteBullets(i);
		}
	}
	bullets.shrink_to_fit();
}

void Player::DeleteBullets(int i)
{
	delete bullets[i];
	bullets[i] = nullptr;
	bullets.erase(bullets.begin()+i);
}

