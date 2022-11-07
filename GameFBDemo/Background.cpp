#include "Background.h"
void Background::Render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, getTex(), NULL, NULL);
}

void Background::RenderItem(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, getTex(), &getScr(), &getDes());
}