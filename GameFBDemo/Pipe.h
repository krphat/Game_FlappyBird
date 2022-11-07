#pragma once
#include "Entity.h"
#include <ctime>
class Pipe : public Entity {
public:
	void Render(SDL_Renderer* ren);
	int getWidth();
	int getHeight();
	int getOriginalWidth();
	int getOriginalHeight();
	int getDistance2Pipe();
	int getDistance2Occurrences();

	void MovePipe1();
	void MovePipe2();
	void setMovePipe1(int move1);
	int getMove1();
	int getMove2();
	int getDelta_y1();
	int getDelta_y2();
	void setMovePipe2(int move2);
private:
	const int original_width = 41;
	const int original_height = 253;
	const int WIDTH_PIPE = 60;
	const int HEIGHT_PIPE = 310;
	const int DISTANCE_BETWEEN_2_PIPES = 110;
	const int DISTANCE_BETWEEN_2_OCCURRENCES = 200;
	int move1 = 400;
	int move2 = move1 + WIDTH_PIPE + DISTANCE_BETWEEN_2_OCCURRENCES;
	int delta_y1;
	int delta_y2;
};
