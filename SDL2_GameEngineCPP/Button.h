#pragma once
#include <SDL.h>

class Button
{
private:
	enum BTN_STATE { MOUSE_UP, MOUSE_OVER,MOUSE_DOWN};
	bool released;
	BTN_STATE buttonState;
	SDL_Rect src;
	SDL_Rect dst;

	SDL_Texture* tex;

	
public:
	Button(const char* texturePath, SDL_Rect srcRect, SDL_Rect destRect);
	~Button();

	void Update();
	void Render();
	bool IsClicked() { return buttonState == BTN_STATE::MOUSE_DOWN; }
	
};

