#pragma once
#include "Entity.h"

class Bird : public Entity {
public:
	int getWidth();
	int getHeight();
	int getX();
	void setX(int bird_coordinates_x);
	void setY(int bird_coordinates_y);
	int getY();
	int getDistanceX();
	int getDistanceY();
	void Render(SDL_Renderer* ren);
	void Gravity();
	void getJumpTime();
	void Jump();
	bool getJumpState();
	void CreateTexture1(const char* filelocation, SDL_Renderer* ren);
	void CreateTexture2(const char* filelocation, SDL_Renderer* ren);
private:
	const int width = 34;
	const int height = 24;
	const int distance_x = 100;
	const int distance_y = 313;  // (screen_height / 2) - (bird_height / 2)
	int timeAnimation = 0;
	double gravity = 0.2;
	int bird_coordinates_x = distance_x;
	int bird_coordinates_y = distance_y;
	double jumpHeight = -5.5;
	double accelerator1 = 0;
	double accelerator2 = 0;
	bool inJump = false;
	double jumptimer;
	double lastJump = 0;
	SDL_Event jump;
	SDL_Texture* tex1;
	SDL_Texture* tex2;
};