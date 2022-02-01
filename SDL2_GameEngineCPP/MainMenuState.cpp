#include "MainMenuState.h"

#include "GameEngine.h"
#include "MainGameLevel0State.h"

MainMenuState::MainMenuState()
{
	
}

MainMenuState::~MainMenuState()
{
	
}

void MainMenuState::Enter()
{
	cout << "Entering MainMenu... \n";
	GameEngine::GetInstance()->SetLeftMouse(false);

	buttons.push_back(new Button("Assets/Sprites/Button/play.png", {0, 0, 400, 100}, {GameEngine::GetInstance()->windowWidth/2 - 200,200,400,100}));
	buttons.push_back(new Button("Assets/Sprites/Button/exit.png", {0, 0, 400, 100}, {GameEngine::GetInstance()->windowWidth/2 - 200,400,400,100}));
}

void MainMenuState::Exit()
{
	cout << "Exiting MainMenu...\n";
	for(int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}

	buttons.clear();
	buttons.shrink_to_fit();
}

void MainMenuState::Update()
{
	//Update buttons so that mouseOvers etc can happen
	for(Button* b : buttons)
		b->Update();

	if(buttons[btn::play]->IsClicked())
	{
		//we need to switch to the mainLevelState
		cout << "TO-DO: Switch to MainLevelState\n";
		GameEngine::GetInstance()->GetFSM()->ChangeState(new MainGameLevel0State());
	}
	else if(buttons[btn::exit]->IsClicked())
	{
		SDL_Delay(500);
		GameEngine::GetInstance()->ShutDown();
	}
}

void MainMenuState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::GetInstance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(GameEngine::GetInstance()->GetRenderer());

	for(Button* b : buttons)
		b->Render();

	ScreenState::Render();
}



