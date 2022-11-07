#include <iostream>
#include "GameLoop.h"
using namespace std;
int main(int argc, char* argv[]) {
	GameLoop* game = new GameLoop;
	SDL_Event event_exit;
	game->Initialize();
	do {
		game->Running();
		cout << "out running" << endl;
		game->PlayAgain();
		cout << "out playagain" << endl;
	} while (game->getGameState());
	game->Clean();
	return 0;
}