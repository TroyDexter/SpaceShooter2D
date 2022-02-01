#include "Button.h"
#include "GameEngine.h"
#include "Sprite.h"

Button::Button(const char* texturePath, SDL_Rect srcRect, SDL_Rect destRect)
{
	src = srcRect;
	dst = destRect;
	tex = Sprite::LoadTexture(texturePath);
	released = true;
}

Button::~Button()
{
	SDL_DestroyTexture(tex);
}

void Button::Render()
{
	src.x = src.w*buttonState;
	SDL_RenderCopy(GameEngine::GetInstance()->GetRenderer(), tex, &src, &dst);
}

void Button::Update()
{
	int mx = GameEngine::GetInstance()->GetMouseX();
	int my = GameEngine::GetInstance()->GetMouseY();
	
	if(mx < (dst.x + dst.w) && mx > dst.x && my < (dst.y + dst.h) && my > dst.y)
	{
		if(GameEngine::GetInstance()->GetLeftMouse() && released)
		{
			buttonState = BTN_STATE::MOUSE_DOWN;
			released = false;
		}
		else if (!GameEngine::GetInstance()->GetLeftMouse())
		{
			released = true;
			buttonState = BTN_STATE::MOUSE_OVER;
		}
	}
	else
		buttonState = BTN_STATE::MOUSE_UP;
}

