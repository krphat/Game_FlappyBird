#pragma once
#include "Entity.h"
#include "SDL_ttf.h"
#include <string>
using namespace std;
class Text {
public:
	Text();
	~Text();
	void InitText();
	void CreateTextTexture(int number, string text, SDL_Renderer* ren);
	void setTextRect(int x, int y, int w, int h);
	SDL_Rect& getTextRect();
	void RenderText(SDL_Renderer* ren);
	SDL_Surface* getTextSuf();
	void ClearText();
	int getWSuf();
	int getHSuf();
private:
	const int fontSize = 45;
	SDL_Color colorText;
	TTF_Font* fontText;
	SDL_Surface* textSuf;
	SDL_Texture* textTT;
	SDL_Rect textRect;
};
