#include "TextureManager.h"

SDL_Texture* TextureManager::Texture(const char* filelocation, SDL_Renderer* render) {
	SDL_Texture* tex;
	tex = IMG_LoadTexture(render, filelocation);
	return tex;
}