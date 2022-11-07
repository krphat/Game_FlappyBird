#include "Bird.h"
#include "GameLoop.h"
using namespace std;

int Bird::getWidth() {
	return width;
}

int Bird::getHeight() {
	return height;
}

int Bird::getX() {
	return bird_coordinates_x;
}

int Bird::getY() {
	return bird_coordinates_y;
}

void Bird::Render(SDL_Renderer* ren) {
	timeAnimation++;
	if (timeAnimation < 20) {
		SDL_RenderCopyEx(ren, getTex(), &getScr(), &getDes(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (timeAnimation >= 20 && timeAnimation <= 40) {
		SDL_RenderCopyEx(ren, tex1, &getScr(), &getDes(), 0, NULL, SDL_FLIP_NONE);
	}
	else if (timeAnimation > 40) {
		SDL_RenderCopyEx(ren, tex2, &getScr(), &getDes(), 0, NULL, SDL_FLIP_NONE);
	}
	if (timeAnimation > 60) {
		timeAnimation = 0;
	}
}


void Bird::Gravity() {
	if (getJumpState()) {
		jumpHeight = gravity + jumpHeight;
		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		bird_coordinates_y = bird_coordinates_y + gravity + accelerator1 + accelerator2 + jumpHeight;
		setDes(bird_coordinates_x, bird_coordinates_y, width, height);
		if (jumpHeight > 0) {
			inJump = false;
			jumpHeight = -5.5;
		}
	}
	else {
		accelerator1 = accelerator1 + 0.035;
		accelerator2 = accelerator2 + 0.035;
		bird_coordinates_y = bird_coordinates_y + gravity + accelerator1 + accelerator2;
		setDes(bird_coordinates_x, bird_coordinates_y, width, height);
	}
}

void Bird::getJumpTime() {
	jumptimer = SDL_GetTicks();
}

bool Bird::getJumpState() {
	return inJump;
}

void Bird::Jump() {
	if (jumptimer - lastJump > 100) {
		accelerator1 = 0;
		accelerator2 = 0;
		inJump = true;
		lastJump = jumptimer;
	}
	else
	{
		Gravity();
	}
}

void Bird::CreateTexture1(const char* filelocation, SDL_Renderer* ren) {
	tex1 = TextureManager::Texture(filelocation, ren);
}

void Bird::CreateTexture2(const char* filelocation, SDL_Renderer* ren) {
	tex2 = TextureManager::Texture(filelocation, ren);
}

void Bird::setX(int bird_coordinates_x) {
	this->bird_coordinates_x = bird_coordinates_x;
}

void Bird::setY(int bird_coordinates_y) {
	this->bird_coordinates_y = bird_coordinates_y;
}

int Bird::getDistanceX() {
	return distance_x;
}
int Bird::getDistanceY() {
	return distance_y;
}