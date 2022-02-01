
#include "GameEngine.h"
#include "MainMenuState.h"

int main(int argc, char* argv[])
{
	GameEngine* gameEngine = GameEngine::GetInstance();  /// new GameEngine();

	if (!gameEngine->InitGameEngine("SpaceShooter2D",800,600))
		return -1;

	gameEngine->GetFSM()->ChangeState(new MainMenuState());
	
	while (GameEngine::GetInstance()->IsRunning())
	{
		GameEngine::GetInstance()->HandleEvents();

		gameEngine->GetFSM()->Update();
		gameEngine->GetFSM()->Render();
		
		SDL_Delay(10);//Delay of 10ms after every loop iteration
	}
	
	GameEngine::GetInstance()->Quit();

	return 0;
}
