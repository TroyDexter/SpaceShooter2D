#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
using namespace std;

class UIText
{
private:
	//this defines where on screen the text needs to be drawn
	SDL_Rect textRect;

	//this is the font texture used to draw the text
	SDL_Texture* fontTexture;  //reference to font texture

	int destX;
	int destY;
	SDL_Color textColor;
	TTF_Font* fontReference;
public:
	string text; //the text we want to set and draw as 

	//constructor
	UIText(int x, int y,TTF_Font* fontRef) :destX(x), destY(y), fontReference(fontRef)
	{
		textColor = { 255,255,255,0 }; //white color
	}

	UIText(int x, int y, TTF_Font* fontRef, SDL_Color c) :destX(x), destY(y), fontReference(fontRef), textColor(c)
	{ }
	
	void RenderText();

	void SetColor(SDL_Color c);
	
	
};

