#pragma once

#include <SDL.h>
#include <iostream>
#include "AudioManager.h"
#include "StateMachine.h"

using namespace std;

class GameEngine
{
private:
	bool isRunning = true;
	SDL_Window* window; //reference to our window
	SDL_Renderer* renderer; //reference to our renderer

	AudioManager* am; //pointer to the audio manager object

	bool leftMouse = false; //keeps track of left mouse button state
	int mouseX, mouseY; //Variables to hold mouse position

	const Uint8* keyStates; //manages the keyStates

	StateMachine* fsm;

public:

	//If you have no plans to have any code in the constructor/destructor, 
	//you do not need to explicitly declare them.
	
	// GameEngine();
	// ~GameEngine();
	
	//returns a singleton instance of this GameEngine's object
	static GameEngine* GetInstance();

	//getter/accessor to our audio manager pointer
	AudioManager* GetAM() {return am;}

	bool IsRunning() { return isRunning;  }

	//Next task:: declare a getter function 'GetRenderer()' for returning the 'renderer'. and use this function in Game.cpp to clear out the errors
 
	SDL_Renderer* GetRenderer() { return renderer; }


	void ShutDown() { isRunning = false;  } 
	//Next Task:: Call this Shutdown() function in the Game.cpp to replace the lines where we set isRunning to false in that class.


	//Task 7:Declare static fields for window Width & window height so that we may access
	//these outside of the GameEngine class (as we need to access these from Game class)
	 int windowWidth;
	 int windowHeight;


	bool InitGameEngine(const char* windowName, int width, int height); //initialize the game engine
	
	void Quit();

	void HandleEvents();

	bool KeyDown(SDL_Scancode c);
	bool KeyUp(SDL_Scancode c);
	bool GetKeyState(SDL_Scancode c, int keyPosition);
	
	
	int GetMouseX() { return mouseX;}
	int GetMouseY() { return mouseY;}
	int GetLeftMouse() { return leftMouse;}

	//to reset mouse click state manually
	void SetLeftMouse(bool b) { leftMouse = b;}

	StateMachine* GetFSM() { return fsm;}

	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));
	}

	
};


