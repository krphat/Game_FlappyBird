#include "Pipe.h"

int Pipe::getWidth() {
	return WIDTH_PIPE;
}

int Pipe::getHeight() {
	return HEIGHT_PIPE;
}

int Pipe::getOriginalWidth() {
	return original_width;
}

int Pipe::getOriginalHeight() {
	return original_height;
}

int Pipe::getDistance2Pipe() {
	return DISTANCE_BETWEEN_2_PIPES;
}

int Pipe::getDistance2Occurrences() {
	return DISTANCE_BETWEEN_2_OCCURRENCES;
}

void Pipe::Render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, getTex(), &getScr(), &getDes());
 }

void Pipe::MovePipe1() {
	move1 = move1 - 1;
	srand(time(0));
	setDes(move1, 0-delta_y1, getWidth(), getHeight());
	if (move1 == -WIDTH_PIPE) {
		move1 = 400 + WIDTH_PIPE;
		delta_y1 = (rand() % 16 + 1) * 10;
	}
}

void Pipe::MovePipe2() {
	move2 = move2 - 1;
	srand(time(0));
	setDes(move2, 0 - delta_y2, getWidth(), getHeight());
	if (move2 == -WIDTH_PIPE) {
		move2 = 400 + WIDTH_PIPE;
		delta_y2 = (rand() % 16 + 1) * 10;
	}
}

void Pipe::setMovePipe1(int move1) {
	this->move1 = move1;
}

void Pipe::setMovePipe2(int move2) {
	this->move2 = move2;
}

int Pipe::getMove1() {
	return move1;
}

int Pipe::getMove2() {
	return move2;
}

int Pipe::getDelta_y1() {
	return delta_y1;
}

int Pipe::getDelta_y2() {
	return delta_y2;
}