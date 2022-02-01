#pragma once
#include <SDL_ttf.h>
#include <vector>

#include "Button.h"
#include "ScreenState.h"
#include "UIText.h"

class WinState :
    public ScreenState
{
private:
	TTF_Font* font; //reference to the loaded font TTF file
	UIText* winMessage;

	std::vector<Button*> buttons;
	enum btn{play,exit};

public:
	WinState() { }
	~WinState() { }
	
	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() { }
};

