#include "ScreenState.h"
#include "GameEngine.h"


void ScreenState::Render()
{
	SDL_RenderPresent(GameEngine::GetInstance()->GetRenderer());
}
