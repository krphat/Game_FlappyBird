#pragma once
#include "Entity.h"

class Background : public Entity {
public:
	void Render(SDL_Renderer* ren);
	void RenderItem(SDL_Renderer* ren);
private:
};
