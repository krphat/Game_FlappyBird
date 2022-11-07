#include "Entity.h"

Entity::Entity() {
	tex = NULL;
}

SDL_Rect& Entity::getScr() {
	return scrDimension;
}

void Entity::setScr(int x, int y, int w, int h) {
	scrDimension.x = x;
	scrDimension.y = y;
	scrDimension.w= w;
	scrDimension.h = h;
}

SDL_Rect& Entity::getDes() {
	return desDimension;
}

void Entity::setDes(int x, int y, int w, int h) {
	desDimension.x = x;
	desDimension.y = y;
	desDimension.w = w;
	desDimension.h = h;
}

SDL_Texture* Entity::getTex() {
	return tex;
}

void Entity::CreateTexture(const char* filelocation, SDL_Renderer* ren) {
	tex = TextureManager::Texture(filelocation, ren);
}

