#include "Sprite.h"

#include "GameEngine.h"


Sprite::Sprite(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect )
{
	//Step 1: Load the sprite
	//sprite = IMG_Load(spritePath);

	spriteSrcRect = srcRect;
	spriteDestRect = destRect;

	X = destRect.x;
	Y=destRect.y;
	
	//create sprite texture from teh sprite 'surface' using the below function
	texture = tex; //SDL_CreateTextureFromSurface(renderer, sprite);
}

Sprite::~Sprite()
{
	//SDL_DestroyTexture(texture);
}

void Sprite::Render(SDL_Renderer* renderer)
{
	//SDL_RenderCopy(renderer, texture, &spriteSrcRect, &spriteDestRect);

	SDL_RenderCopyEx(renderer, texture, &spriteSrcRect, &spriteDestRect, angle, nullptr, SDL_FLIP_NONE);
}

SDL_Texture* Sprite::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if(!surface)
	{
		cout << "Can't load texture at path: " << path << endl;
	}
	SDL_Texture* t= SDL_CreateTextureFromSurface(GameEngine::GetInstance()->GetRenderer(), surface);
	SDL_FreeSurface(surface); //Free the surface as we no longer need it once we created texture

	return t;
}

void Sprite::UpdateDestRect()
{
	spriteDestRect.x = (X-spriteDestRect.w*0.5f);
	spriteDestRect.y = (Y-spriteDestRect.h*0.5f);
}
