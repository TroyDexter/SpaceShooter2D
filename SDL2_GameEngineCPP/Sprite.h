#pragma once
#include <SDL.h>
#include <SDL_image.h>

//Base class that just static sprites
class Sprite
{
private:
	

	

protected:
	//defines part of the spritesheet would like to render
	SDL_Rect spriteSrcRect;
	//position on the screen we would like to render this sprite
	SDL_Rect spriteDestRect;

	//SDL_Surface* sprite; //the handle to the image
	
	SDL_Texture* texture; //texture holds the sprite texture after loading it from the sprite
	
	double angle; //the angle (in degrees) to rotate the sprite

	double X,
		Y,
		dX, //Delta X -change in x coord
		dY,
		radius,
		speed; //speed in pixels to move per change


public:
	Sprite() {}
	Sprite(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect);
	~Sprite();
	void Render(SDL_Renderer* renderer);

	static SDL_Texture* LoadTexture(const char* path);

	void UpdateDestRect();
	
	double GetX() {return X;}
	double GetY() {return Y;}
	double GetRadius() {return radius;}
	
};

