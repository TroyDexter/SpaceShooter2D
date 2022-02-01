#pragma once
#include <SDL_ttf.h>
#include <vector>

#include "Button.h"
#include "ScreenState.h"
#include "UIText.h"

class LoseState :
    public ScreenState
{
private:
	TTF_Font* font; //reference to the loaded font TTF file
	UIText* loseMessage;

	vector<Button*> buttons;
	enum btn{play,exit};

public:
	LoseState() { }
	~LoseState() { }

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() { }
};

