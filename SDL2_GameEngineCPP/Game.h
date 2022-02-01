#pragma once
#include <SDL.h>
#include "Sprite.h"
#include <SDL_ttf.h>
#include "UIText.h"
#include "Asteroid.h"
#include <iostream>
#include <vector>

using namespace std;

//Game-specific code goes in here.....
class Game
{
private:
	Sprite* bgSprite;

	//SDL_Rect background;
	int mouseX, mouseY; //for mouse coords
	SDL_Event event; //to handle events

	TTF_Font* font; //reference to the loaded font TTF file

	UIText* scoreText;

	vector<Asteroid*> asteroids; //a vector of astroides we will have in the game
	SDL_Texture* mainSpriteTex; //load and store the main sprite texture

public:
	void InitGameWorld();
	void Input();
	void Update();
	void Render();
	 
};

