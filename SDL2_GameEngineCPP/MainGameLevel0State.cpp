#include "MainGameLevel0State.h"
#include "GameEngine.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>

#include "Color.h"
#include "LoseState.h"
#include "WinState.h"

void MainGameLevel0State::Enter()
{
	cout << "Entering main Game... \n";
	SDL_Texture* tex = Sprite::LoadTexture("Assets/Sprites/background.png");

	SDL_Texture* mainSpriteTex = Sprite::LoadTexture("Assets/Sprites/Sprite2.png");
	
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0; //srcRect.w = srcRect.h = 256;
	SDL_QueryTexture(tex, NULL,NULL, &srcRect.w, &srcRect.h ); //set the w/h of the srcRect by querying it from texture
	
	SDL_Rect destRect;
	destRect.x = 0; destRect.y = 0; 
	destRect.w = GameEngine::GetInstance()->windowWidth; //the width of the sprite on the window. 
	destRect.h = GameEngine::GetInstance()->windowHeight;
	
	bgSprite = new Sprite(tex, srcRect, destRect);

	SDL_Rect asteroidSrcRect;
	asteroidSrcRect.x = 124;
	asteroidSrcRect.y = 0;
	asteroidSrcRect.w = asteroidSrcRect.h = 66;
	SDL_Rect asteroidDestRect;
	asteroidDestRect.w = asteroidDestRect.h = 66;

	srand(time(0));
	
	for (int i=0; i<5; i++)
	{
		float rotSpeed = (1 - rand() % 2 *2) * (rand() % 6 + 1);

		asteroidDestRect.x = (rand() % 700) + 1; //Generate between 1 and 700
		asteroidDestRect.y = (rand() % 600) + 1; //Generate between 1 and 600

		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, rotSpeed);
		asteroids.push_back(ast);
	}

	//Init PLayer
	player = new Player(mainSpriteTex,GameEngine::GetInstance()->windowWidth * 0.5, GameEngine::GetInstance()->windowHeight - 100);

	/****Load font*****/
	font = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 15);//initial font size 12
	//if font was not loaded
	if (!font)
	{
		cout << "Failed to load font: " << TTF_GetError() << endl;
	}

	scoreText = new UIText(10, 10, font, Color::White);
	scoreText->text = "Score: ";

	livesText = new UIText(10, 25, font, Color::White);
	livesText->text = "Lives: ";

	//Init Sound
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/Fire.wav"); //id =0
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/explode.wav"); //id=1
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/Engines.wav"); //id=2
	GameEngine::GetInstance()->GetAM()->LoadSound("Assets/Aud/button.wav"); //id=3
}

void MainGameLevel0State::Render()
{
	SDL_RenderClear(GameEngine::GetInstance()->GetRenderer());
	//Must be first
	bgSprite->Render(GameEngine::GetInstance()->GetRenderer());

	for (int i =0; i < asteroids.size();i++)
	{
		asteroids[i]->Render(GameEngine::GetInstance()->GetRenderer());
	}

	if(player)
	{
		player->Render();
	}

	scoreText->RenderText();
	livesText->RenderText();
	
	//Must be LAST render
	ScreenState::Render();
}

void MainGameLevel0State::Update()
{
	if(player)
		player->Update();

	if(player)
		CheckCollision();		
	
	if(!asteroids.empty())
	{
		for(int i=0; i<asteroids.size();i++)
		{
			asteroids[i]->Update();
		}
		//draw score
		scoreText->text = "Score: " + to_string(score);		
		livesText->text = "Lives: " + to_string(lives);
	}
}

void MainGameLevel0State::Exit()
{
	cout << "Exiting Main level...\n";
	delete bgSprite;
	delete player;
	delete scoreText;
	delete livesText;
	
	for(int i = 0; i < asteroids.size(); i++)
	{
		delete asteroids[i];
		asteroids[i] = nullptr;
	}

	asteroids.clear();
	asteroids.shrink_to_fit();
}

void MainGameLevel0State::CheckCollision()
{
	//check for the player and asteroid collisions
	for(int i = 0; i < asteroids.size(); i++)
	{
		if(GameEngine::GetInstance()->CircleCollisionTest(player->GetX(), player->GetY(),asteroids[i]->GetX(), asteroids[i]->GetY(), player->GetRadius(),asteroids[i]->GetRadius() ))
		{
		cout << "Player collided with asteroid and got killed...\n";
			//Game logic goes here
			lives--;
			
			DestroyAsteroids(i);

			//Game-end condition
			if(lives < 0)
			{
				cout << "You have lost the game\n";
				GameEngine::GetInstance()->GetFSM()->ChangeState(new LoseState());
			}
			return;
		}
	}

	//next Block:: check for bullet and asteroid collision
	for (int b = 0; b < player->GetBullets().size();b++)
	{
		Bullet* bullet = player->GetBullets()[b];
		
		for(int i = 0; i < asteroids.size(); i++)
		{
			if(GameEngine::GetInstance()->CircleCollisionTest(bullet->GetX(),bullet->GetY(),asteroids[i]->GetX(), asteroids[i]->GetY(),bullet->GetRadius(),asteroids[i]->GetRadius()))
			{
				cout << "Bullet collided with an asteroid...\n";
				//Your scoring data here
				score += 100;
				
				//destroy the bullet
				player->DeleteBullets(b);
				
				//destroy the asteroid
				DestroyAsteroids(i);
				break;
			}
		}

		//Game-end condition
		if(asteroids.empty())
		{
 			cout << "You have Won the game\n";
			GameEngine::GetInstance()->GetFSM()->ChangeState(new WinState());
			break;
		}
	}
}

void MainGameLevel0State::DestroyAsteroids(int i)
{
	delete asteroids[i];
	asteroids[i] = nullptr;
	asteroids.erase(asteroids.begin()+i);
	asteroids.shrink_to_fit();
}

