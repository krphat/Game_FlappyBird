#pragma once
#include "TextureManager.h"
class Entity {
public:
	Entity();
	SDL_Rect& getScr();
	void setScr(int x, int y, int w, int h);
	SDL_Rect& getDes();
	void setDes(int x, int y, int w, int h);
	SDL_Texture* getTex();
	void CreateTexture(const char* filelocation, SDL_Renderer* ren);
	virtual void Render(SDL_Renderer* ren) = 0;
private:
	SDL_Rect scrDimension;
	SDL_Rect desDimension;
	SDL_Texture* tex;
};
