#include "UIText.h"
#include <SDL_ttf.h>
#include "GameEngine.h"



void UIText::RenderText()
{
	//step 1: create SDL_Surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(fontReference,text.c_str(), textColor);

	//text.c_str()
	//Step 2: SDL_CreateTextureFromSurface() creates a font texture from the above surface
	fontTexture = SDL_CreateTextureFromSurface(GameEngine::GetInstance()->GetRenderer(), textSurface);

	//Step 3: Define the  textRect 
	textRect = { destX, destY, textSurface->w, textSurface->h };

	//Step 4: draw the text
	SDL_RenderCopy(GameEngine::GetInstance()->GetRenderer() , fontTexture, 0, &textRect);
	
}

void UIText::SetColor(SDL_Color c)
{
	textColor = c;
}

