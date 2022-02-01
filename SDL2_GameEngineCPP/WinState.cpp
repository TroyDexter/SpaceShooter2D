#include "WinState.h"
#include "Color.h"
#include "GameEngine.h"
#include "MainGameLevel0State.h"

void WinState::Enter()
{
	cout << "Entering Win State... \n";
	GameEngine::GetInstance()->SetLeftMouse(false);

	buttons.push_back(new Button("Assets/Sprites/Button/play.png", {0, 0, 400, 100}, {GameEngine::GetInstance()->windowWidth/2 - 200,250,400,100}));
	buttons.push_back(new Button("Assets/Sprites/Button/exit.png", {0, 0, 400, 100}, {GameEngine::GetInstance()->windowWidth/2 - 200,400,400,100}));

	/****Load font*****/
	font = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 75);//initial font size 12
	//if font was not loaded
	if (!font)
	{
		cout << "Failed to load font: " << TTF_GetError() << endl;
	}
	winMessage = new UIText(GameEngine::GetInstance()->windowWidth /2 - 200, 100, font, Color::Green);
	winMessage->text = "YOU WIN!";
}

void WinState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::GetInstance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(GameEngine::GetInstance()->GetRenderer());
	
	winMessage->RenderText();
	
	for(Button* b : buttons)
		b->Render();
	
	//Must be LAST render
	ScreenState::Render();
}

void WinState::Update()
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

void WinState::Exit()
{
	cout << "Exiting Lose State...\n";
	
	for(int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}

	buttons.clear();
	buttons.shrink_to_fit();
	delete winMessage;
}