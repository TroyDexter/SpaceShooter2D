#pragma once
#include "AnimatedSprite.h"
#include "Bullet.h"
#include <vector>

using namespace std;

class Player : public AnimatedSprite
{
private:
	const double DELTA_ANGLE = 1.5f;
	const double DRAG = 0.975f;

	
	vector<Bullet*> bullets;
	
	double velX = 0, velY = 0, velMax = 10;
	
	void MoveFoward();
	void MoveBackward();
	void UpdatePlayer();

	void UpdateBullets();
	void SpawnBullet();
	
	
public:
	int nextShootTime = 0;

	int lives = 3;
	
	Player(SDL_Texture* tex, double x, double y);
	~Player();

	void Update();
	void Render();
	void SetIdle();
	void DeleteBullets(int i);

	vector<Bullet*>& GetBullets()
	{
		return bullets;
	}
	
};

