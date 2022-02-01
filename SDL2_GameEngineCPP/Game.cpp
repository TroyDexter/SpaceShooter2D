#include "Game.h"
#include "Color.h"
#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

void Game::InitGameWorld()
{
	SDL_Texture* tex = Sprite::LoadTexture("Assets/Sprites/background.png");

	SDL_Texture* mainSpriteTex = Sprite::LoadTexture("Assets/Sprites/Sprite.png");
	
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0; //srcRect.w = srcRect.h = 256;
	SDL_QueryTexture(tex, NULL,NULL, &srcRect.w, &srcRect.h ); //set the w/h of the srcRect by querying it from texture
	
	SDL_Rect destRect;
	destRect.x = 0; destRect.y = 0; 
	destRect.w = GameEngine::GetInstance()->windowWidth; //the width of the sprite on the window. 
	destRect.h = GameEngine::GetInstance()->windowHeight;
	//SDL_GetWindowSize(GameEngine::GetInstance()->)
	
	bgSprite = new Sprite(tex, srcRect, destRect);

	SDL_Rect asteroidSrcRect;
	asteroidSrcRect.x = 0;
	asteroidSrcRect.y = 128;
	asteroidSrcRect.w = 64;
	asteroidSrcRect.h = 64;

	SDL_Rect asteroidDestRect;
	asteroidDestRect.w = 64;
	asteroidDestRect.h = 64;

	srand(time(0));
	
	for (int i=0; i<5; i++)
	{
		float rotSpeed = (1 - rand() % 2 *2) * (rand() % 6 + 1);

		asteroidDestRect.x = (rand() % 700) + 1; //Generate between 1 and 700
		asteroidDestRect.y = (rand() % 600) + 1; //Generate between 1 and 600

		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, rotSpeed);
		asteroids.push_back(ast);
	}

	/****Load font*****/
	font = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 12);//initial font size 12
	//if font was not loaded
	if (!font)
	{
		cout << "Failed to load font: " << TTF_GetError() << endl;
	}

	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/Fire.wav"); //id =0
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/explode.wav"); //id=1
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/Engines.wav"); //id=2
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/button.wav"); //id=3

	scoreText = new UIText(10, 10, font, Color::White);
}
 

void Game::Input()
{
	
	while (SDL_PollEvent(&event))

	{
		if (event.type == SDL_MOUSEMOTION) //if mouse movement is detected
		{
			SDL_GetMouseState(&mouseX, &mouseY);
		}

		//if we click 'X' button to close the app window then SDL_QUIT event type is triggered 
		if (event.type == SDL_QUIT)
		{
		//GameEngine::GetInstance()->isRunning = false;
			GameEngine::GetInstance()->ShutDown();
		}
		//check if key was pressed

		if (event.type == SDL_KEYDOWN)

		{
			switch (event.key.keysym.sym)

			{

			case SDLK_ESCAPE:
				//GameEngine::GetInstance()->isRunning = false;
				GameEngine::GetInstance()->ShutDown();
				break;

			case SDLK_r:
				scoreText->SetColor(Color::Red);
				break;
			case SDLK_g:
				scoreText->SetColor(Color::Green);
				break;
			case SDLK_b:
				scoreText->SetColor(Color::Black);
				break;
			case SDLK_l:
				scoreText->SetColor(Color::Blue);
				break;
			case SDLK_w:
				scoreText->SetColor(Color::White);
				break;
			case SDLK_y:
				scoreText->SetColor(Color::Yellow);
				break;
			case SDLK_o:
				scoreText->SetColor(Color::Orange);
				break;
			case SDLK_SPACE:
				//Play fire sound
				GameEngine::GetInstance()->GetAM()->PlaySound(0);
				break;
			case SDLK_e:
				//play explosion sound
				GameEngine::GetInstance()->GetAM()->PlaySound(1);
				break;
			}
		}
	}
}

void Game::Render()
{
	SDL_RenderClear(GameEngine::GetInstance()->GetRenderer()); //clear previously drawn frame
 //Start drawing the current frame //Render the Background //5,30,67 represents a dark blue color. Check MS Paint's edit color to get your own rgb value. //the fifth argument below, 255 stands for the 'alpha' i.e. transparency of the color. 255=opaque, 0=transparent 
 // SDL_SetRenderDrawColor(GameEngine::GetInstance()->GetRenderer(), 5, 30, 67, 255);
 //	SDL_RenderFillRect(GameEngine::GetInstance()->GetRenderer(), &background); //fill the background rect with the above color

	//Must be FIRST render
	bgSprite->Render(GameEngine::GetInstance()->GetRenderer());

	for (int i =0; i < asteroids.size();i++)
	{
		asteroids[i]->Render(GameEngine::GetInstance()->GetRenderer());
	}

	//Must be LAST render
	scoreText->RenderText();
	SDL_RenderPresent(GameEngine::GetInstance()->GetRenderer()); //must call this to render the above defined
}

void Game::Update()
{	
	static int score = 0;
	score++;
	//draw score on UI HUD... updates score by 1 every 10 ms
	scoreText->text = "Score: " +to_string(score);
	for(int i=0; i<asteroids.size();i++)
	{
		asteroids[i]->Update();
	}

	SDL_Delay(100); //pause the game loop for 10 milliseconds to slow down the game to a decent speed
}