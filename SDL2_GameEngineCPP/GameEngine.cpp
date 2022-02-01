
#include "GameEngine.h"
#include <SDL_ttf.h>


//implement 'GetInstance()' function
GameEngine* GameEngine::GetInstance()
{
	//"Singleton" instance of the GameEngine
	static GameEngine* instance;

	if (instance == nullptr)
	{
		instance = new GameEngine();
	}

	return instance;
}


bool GameEngine::InitGameEngine(const char* windowName, int width, int height)
{
	windowWidth =   width;
	windowHeight = height;

	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, 0);
	if (!window)
	{
		cout << "Window initialization failed.\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		cout << "Renderer intialization failed\n";
		return false;
	}
	//check if ttf engine can be used
	if (TTF_Init() != 0)
	{
		cout << "TTF Engine init failed.\n";
		return false;
	}

	am = new AudioManager();
	//if audio manager not init return false
	if(!am->InitAudioManager())
		return false;

	keyStates = SDL_GetKeyboardState(nullptr);

	fsm = new StateMachine();
	
	return true;
}


void GameEngine::Quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete am;
	
	TTF_Quit();
	SDL_Quit();

	isRunning = false;

}

void GameEngine::HandleEvents()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			break;
			
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				leftMouse = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if(event.button.button == SDL_BUTTON_LEFT)
				leftMouse = false;
			break;

		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
}

bool GameEngine::KeyDown(SDL_Scancode c)
{
	return GetKeyState(c, 1);
}

bool GameEngine::KeyUp(SDL_Scancode c)
{
	return GetKeyState(c, 0);
}

bool GameEngine::GetKeyState(SDL_Scancode c, int keyPosition)
{
	if(keyStates == nullptr)
	{
		cout << "KeyStates is null\n";
		return false;
	}

	if(keyStates[c] == keyPosition) //if the given key's state is pressed, return true
		return true;
	else return false;
}
