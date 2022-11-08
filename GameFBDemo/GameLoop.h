#pragma once
#include <iostream>
#include <fstream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Bird.h"
#include "Background.h"
#include "Floor.h"
#include "Pipe.h"
#include <string>
#include "Button.h"
#include "SDL_ttf.h"
using namespace std;
class GameLoop {
public:
	GameLoop();
	bool getGameState();
	void Initialize();
	void Render();
	void Event();
	bool Collide_Border();
	bool Collide_Pipe();
	void Collide();
	bool Score();
	void DisplayScore();
	void Update();
	void Clean();
	void CheckScore();

	void RenderAgain();
	void PlayAgain();
	void EventPlayAgain();
	void Running();
private:
	const int WIDTH_SCREEEN = 400;
	const int HEIGHT_SCREEN = 650;
	SDL_Event event;
	bool gameState;
	bool running;
	bool start;
	SDL_Window* window;
	SDL_Renderer* renderer;

	Bird bird;
	// BACKGROUND
	Background background;
	Background SCORE;
	// FLOOR
	Floor floor1;
	Floor floor2;
	//PIPE
	Pipe pipeTop1;
	Pipe pipeTop2;
	Pipe pipeUnder1;
	Pipe pipeUnder2;
	// SOUND
	Mix_Chunk* sound_birdflap;
	Mix_Chunk* sound_score;
	Mix_Chunk* sound_hit;
	Mix_Chunk* sound_die;

	// play again
	Background backgroundAgain;
	SDL_Event eventAgain;
	// transcript
	Background transcript;
	// game over
	Background gameOver;
	// start game
	Background start_screen;
	// BUTTON
	Button playAgain;
	Button Exit;
};
