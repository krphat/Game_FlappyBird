#pragma once
#include "Entity.h"
class Floor : public Entity {
public:
	void Render(SDL_Renderer* ren);
	void MoveFloor1();
	void setMoveFloor1(int moveFloor1);
	void setMoveFloor2(int moveFloor2);
	int getOC_X_Floor1();
	int getOC_X_Floor2();
	int getOC_Y_Floor1();
	int getOC_Y_Floor2();
	void MoveFloor2();
	int getHeight();
	int getWidth();
private:
	const int width = 400;
	const int height = 95;
	int original_coordinates_x_floor1 = 0; // toa do x ban dau cua floor 1
	int orginal_coordinates_y_floor1 = 555;
	int original_coordinates_x_floor2 = 400; // toa do x ban dau cua floor 2
	int orginal_coordinates_y_floor2 = 555;
	int moveFloor1 = original_coordinates_x_floor1;
	int moveFloor2 = original_coordinates_x_floor2;
};
