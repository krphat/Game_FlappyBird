#include "Button.h"

void Button::Render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, getTex(), &getScr(), &getDes());
}