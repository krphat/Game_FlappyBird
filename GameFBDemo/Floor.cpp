#include "Floor.h"
#include "Entity.h"

//int Floor::getMove() {
//	return move;
//}

void Floor::Render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, getTex(), &getScr(), &getDes());
}

void Floor::MoveFloor1() {
	moveFloor1 = moveFloor1 - 1;
	setDes(moveFloor1, orginal_coordinates_y_floor1, width, height);
	if (moveFloor1 <= -width) {
		moveFloor1 = width;
	}
}

void Floor::MoveFloor2() {
	moveFloor2 = moveFloor2 - 1;
	setDes(moveFloor2, orginal_coordinates_y_floor2, width, height);
	if (moveFloor2 <= -width) {
		moveFloor2 = width;
	}
}

int Floor::getWidth() {
	return width;
}

int Floor::getHeight() {
	return height;
}

void Floor::setMoveFloor1(int moveFloor1) {
	this->moveFloor1 = moveFloor1;
}
void Floor::setMoveFloor2(int moveFloor2) {
	this->moveFloor2 = moveFloor2;
}
int Floor::getOC_X_Floor1() {
	return original_coordinates_x_floor1;
}
int Floor::getOC_X_Floor2() {
	return original_coordinates_x_floor2;
}
int Floor::getOC_Y_Floor1() {
	return orginal_coordinates_y_floor1;
}
int Floor::getOC_Y_Floor2() {
	return orginal_coordinates_y_floor2;
}

