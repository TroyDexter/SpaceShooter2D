#pragma once
#include <SDL.h>

//Abstract base class
class ScreenState
{
public:
	virtual void Update() = 0; //Pure virtual function
	virtual void Render();
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
};

