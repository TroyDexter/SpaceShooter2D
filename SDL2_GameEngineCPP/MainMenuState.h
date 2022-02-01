#pragma once
#include "ScreenState.h"
#include "Button.h"
#include <vector>
#include <iostream>

using namespace std;

class MainMenuState : public ScreenState
{
private:
	vector<Button*> buttons;
	enum btn{play,exit};


public:
	MainMenuState();
	~MainMenuState();

	void Enter();
	void Exit();
	void Update();
	void Render();
	void Resume() { }
	
};

