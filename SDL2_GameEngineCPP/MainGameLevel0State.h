#pragma once
#include <SDL_ttf.h>
#include <vector>
#include "Asteroid.h"
#include "ScreenState.h"
#include "Sprite.h"
#include "UIText.h"
#include <iostream>

#include "Player.h"

using namespace std;

class MainGameLevel0State: public ScreenState
{
private:
	Sprite* bgSprite;//SDL_Rect background;
	SDL_Texture* mainSpriteTex; //load and store the main sprite texture
	vector<Asteroid*> asteroids; //a vector of astroides we will have in the game
	
	Player* player;

	TTF_Font* font; //reference to the loaded font TTF file
	UIText* scoreText;
	UIText* livesText;

	int score = 0;
	int lives = 3;
	
	void CheckCollision();
	void EndGame();

public:
	MainGameLevel0State() { }
	~MainGameLevel0State() { }

	void DestroyAsteroids(int i);
	
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() { }
	
};

