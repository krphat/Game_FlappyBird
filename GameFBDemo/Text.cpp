#include "Text.h"

Text::Text() {
	fontText = NULL;
	textSuf = NULL;
	textTT = NULL;
}

Text::~Text() {

}

void Text::CreateTextTexture(int number, string text, SDL_Renderer* ren) {
	text = to_string(number);
	textSuf = TTF_RenderText_Solid(fontText, text.c_str(), colorText);
	textTT = SDL_CreateTextureFromSurface(ren, textSuf);
}

void Text::InitText() {
	colorText = { 255,255,255 };
	fontText = TTF_OpenFont("LuckiestGuy - Regular.ttf", fontSize);
}

SDL_Surface *Text::getTextSuf() {
	return textSuf;
}
void Text::setTextRect(int x, int y, int w, int h) {
	textRect.x = x;
	textRect.y = y;
	textRect.w = w;
	textRect.h = h;
}

SDL_Rect& Text::getTextRect() {
	return textRect;
}

void Text::RenderText(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, textTT, NULL, &getTextRect());
}

void Text::ClearText() {
	TTF_CloseFont(fontText);
	SDL_FreeSurface(textSuf);
	fontText = NULL;
	textSuf = NULL;
	textTT = NULL;
	TTF_Quit();
}