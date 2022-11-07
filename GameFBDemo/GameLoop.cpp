#include "GameLoop.h"
#include "TextureManager.h"
GameLoop::GameLoop() {
	window = NULL;
	renderer = NULL;
	sound_birdflap = NULL;
	sound_hit = NULL;
	sound_score = NULL;
	gameState = false;
	start = false;
	running = false;
	font = NULL;
	text_score_Suf = NULL;
	text_score_Tex = NULL;
	text_highScore_Suf = NULL;
	text_highScore_Tex = NULL;
	// BIRD
	bird.setScr(0, 0, bird.getWidth(), bird.getHeight());
	bird.setDes((WIDTH_SCREEEN/2) - (bird.getWidth()/2), (HEIGHT_SCREEN/2) - (bird.getHeight()/2), bird.getWidth(), bird.getHeight());
	// FLOOR
	floor1.setScr(0, 0, floor1.getWidth(), floor1.getHeight());
	floor2.setScr(0, 0, floor2.getWidth(), floor2.getHeight());
	// PIPE
	pipeTop1.setScr(0, 0, pipeTop1.getOriginalWidth(), pipeTop1.getOriginalHeight());
	pipeTop2.setScr(0, 0, pipeTop2.getOriginalWidth(), pipeTop2.getOriginalHeight());
	pipeUnder1.setScr(0, 0, pipeUnder1.getOriginalWidth(), pipeUnder1.getOriginalHeight());
	pipeUnder2.setScr(0, 0, pipeUnder2.getOriginalWidth(), pipeUnder2.getOriginalHeight());
	// TRANSCRIPT
	transcript.setScr(0, 0, 1117, 1082);
	transcript.setDes(WIDTH_SCREEEN / 2 - WIDTH_SCREEEN / 4, 200, 200, 193);
	// GAMEOVER
	gameOver.setScr(0, 0, 192, 42);
	gameOver.setDes(WIDTH_SCREEEN / 2 - 192 / 2, 100, 192, 42);
	// start screen
	start_screen.setScr(0, 0, 2309, 3464);
	start_screen.setDes(0, 25, 400, 600);
	// button
}

bool::GameLoop::getGameState() {
	return gameState;
}

void GameLoop::Initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//text
	TTF_Init();
	window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH_SCREEEN, HEIGHT_SCREEN, SDL_WINDOW_RESIZABLE);
	if (window) {
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			cout << "Khoi tao thanh cong" << endl;
			gameState = true;

			//TEXT
			//Text_Score.InitText();
			font = TTF_OpenFont("LuckiestGuy-Regular.ttf", FontSize);
			
			background.CreateTexture("image/background_plus.png", renderer);
			backgroundAgain.CreateTexture("image/background_plus.png", renderer);
			bird.CreateTexture("image/yellowbird-upflap.png", renderer);
			bird.CreateTexture1("image/yellowbird-midflap.png", renderer);
			bird.CreateTexture2("image/yellowbird-downflap.png", renderer);
			floor1.CreateTexture("image/floor_plus.png", renderer);
			floor2.CreateTexture("image/floor_plus.png", renderer);
			
			//PIPE

			pipeTop1.CreateTexture("image/upper_pipe.png", renderer);
			pipeTop2.CreateTexture("image/upper_pipe.png", renderer);
			pipeUnder1.CreateTexture("image/bottom_pipe.png", renderer);
			pipeUnder2.CreateTexture("image/bottom_pipe.png", renderer);

			// transcript
			transcript.CreateTexture("image/transcript.png", renderer);
			// game over
			gameOver.CreateTexture("image/gameover.png", renderer);
			// start screen
			start_screen.CreateTexture("image/gamestart.png", renderer);
			// button
			playAgain.CreateTexture("image/play_again_button.png", renderer);
			Exit.CreateTexture("image/button_exit.png", renderer);

		}
		else {
			cout << "Khoi tao khong thanh cong" << endl;
		}
		if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1) {
			cout << "Khoi tao am thanh that bai !" << endl;
		}
		else {
			sound_birdflap = Mix_LoadWAV("sound/sfx_wing.wav");
			sound_score = Mix_LoadWAV("sound/sfx_point.wav");
			sound_hit = Mix_LoadWAV("sound/sfx_hit.wav");
			sound_die = Mix_LoadWAV("sound/sfx_die.wav");
		}
	}
	else {
		cout << "Khoi tao window that bai" << endl;
	}
}

void GameLoop::Render() {
	SDL_RenderClear(renderer);
	background.Render(renderer);
	pipeTop1.Render(renderer);
	pipeUnder1.Render(renderer);
	pipeTop2.Render(renderer);
	pipeUnder2.Render(renderer);
	bird.Render(renderer);
	floor1.Render(renderer);
	floor2.Render(renderer);
	if (!start) {
		start_screen.RenderItem(renderer);
	}
	// text
	if (start) {
		SDL_RenderCopy(renderer, text_score_Tex, NULL, &text_score_Rect);
	}
	SDL_RenderPresent(renderer);
}

void GameLoop::Event() {
	bird.getJumpTime();
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT) {
		gameState = false;
		running = false;
	}
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP && start) {
			if (!bird.getJumpState()) {
				bird.Jump();
				Mix_PlayChannel(-1, sound_birdflap, 0); // am thanh nhay
			}
			else {
				bird.Gravity();
			}
		}
	}
	else {
		if (start) {
			bird.Gravity();
		}
	}
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_SPACE) {
			start = true;
			bird.setDes(bird.getX(), bird.getY(), bird.getWidth(), bird.getHeight());
		}
	}
	Collide();
}

void GameLoop::Update() {
	if (start) {
		pipeTop1.MovePipe1();
		pipeUnder1.setDes(pipeTop1.getDes().x, pipeTop1.getDes().y + pipeTop1.getHeight() + pipeTop1.getDistance2Pipe(), pipeUnder1.getWidth(), pipeUnder1.getHeight());
		pipeTop2.MovePipe2();
		pipeUnder2.setDes(pipeTop2.getDes().x, pipeTop2.getDes().y + pipeTop2.getHeight() + pipeTop2.getDistance2Pipe(), pipeUnder2.getWidth(), pipeUnder2.getHeight());
	}
	floor1.MoveFloor1();
	floor2.MoveFloor2();
	DisplayScore();
	//text
	//time = SDL_GetTicks() / 1000;
	text_score = to_string(score);
	text_score_Suf = TTF_RenderText_Solid(font, text_score.c_str(), { 255,255,255 });
	text_score_Tex = SDL_CreateTextureFromSurface(renderer, text_score_Suf);
	text_score_Rect = { WIDTH_SCREEEN/2 - FontSize/2,50,text_score_Suf->w, text_score_Suf->h };
}

void GameLoop::Clean() {
	//text
	SDL_FreeSurface(text_score_Suf);
	SDL_FreeSurface(text_highScore_Suf);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_RenderClear(renderer);
}

void GameLoop::Collide() {
	if (Collide_Border() || Collide_Pipe()) {
		Mix_PlayChannel(-1, sound_hit, 0);
		//SDL_Delay(1000);
		gameState = false;
		running = true;
	}
}

bool GameLoop::Collide_Border() {
	if ((bird.getDes().y <= 0) || (bird.getDes().y + bird.getHeight() >= (HEIGHT_SCREEN - floor1.getHeight()))) {
		return true;
	}
	return false;
}

bool GameLoop::Collide_Pipe() {
	// va cham truc dien ong tren
	bool CL_X_pipeTop1 = bird.getDes().x + bird.getWidth() == pipeTop1.getDes().x;
	bool CL_Y_pipeTop1 = (bird.getDes().y > 0) && (bird.getDes().y <= (pipeTop1.getDes().y + pipeTop1.getHeight()));

	bool CL_X_pipeTop2 = bird.getDes().x + bird.getWidth() == pipeTop2.getDes().x;
	bool CL_Y_pipeTop2 = (bird.getDes().y > 0) && (bird.getDes().y <= (pipeTop2.getDes().y + pipeTop2.getHeight()));

	// va cham truc dien ong duoi
	bool CL_X_pipeUnder1 = bird.getDes().x + bird.getWidth() == pipeUnder1.getDes().x;
	bool CL_Y_pipeUnder1 = ((bird.getDes().y + bird.getHeight()) >= pipeUnder1.getDes().y) && ((bird.getDes().y + bird.getHeight()) <= 555);

	bool CL_X_pipeUnder2 = bird.getDes().x + bird.getWidth() == pipeUnder2.getDes().x;
	bool CL_Y_pipeUnder2 = ((bird.getDes().y + bird.getHeight()) >= pipeUnder2.getDes().y) && ((bird.getDes().y + bird.getHeight()) <= 555);
	
	//va cham vao cap ong 1
	bool CL_X_In_pipes1 = ((bird.getDes().x + bird.getWidth()) >= pipeTop1.getDes().x) && ((bird.getDes().x + bird.getWidth()) <= (pipeTop1.getDes().x + pipeTop1.getWidth()));
	bool CL_Y_In_pipeTop1 = bird.getDes().y <= (pipeTop1.getDes().y + pipeTop1.getHeight());
	bool CL_Y_In_pipeUnder1 = (bird.getDes().y + bird.getHeight()) >= pipeUnder1.getDes().y;

	// va cham vao ong 2
	bool CL_X_In_pipes2 = ((bird.getDes().x + bird.getWidth()) >= pipeTop2.getDes().x) && ((bird.getDes().x + bird.getWidth()) <= (pipeTop2.getDes().x + pipeTop2.getWidth()));
	bool CL_Y_In_pipeTop2 = bird.getDes().y <= (pipeTop2.getDes().y + pipeTop2.getHeight());
	bool CL_Y_In_pipeUnder2 = (bird.getDes().y + bird.getHeight()) >= pipeUnder2.getDes().y;

	//va cham ra ong 1
	bool CL_X_Out_pipes1 = (bird.getDes().x >= pipeTop1.getDes().x) && (bird.getDes().x <= (pipeTop1.getDes().x + pipeTop1.getWidth()));
	bool CL_Y_Out_pipeTop1 = bird.getDes().y <= (pipeTop1.getDes().y + pipeTop1.getHeight());
	bool CL_Y_Out_Pipender1 = (bird.getDes().y + bird.getHeight()) >= pipeUnder1.getDes().y;

	//va cham ra ong 2
	bool CL_X_Out_pipes2 = (bird.getDes().x >= pipeTop2.getDes().x) && (bird.getDes().x <= (pipeTop2.getDes().x + pipeTop2.getWidth()));
	bool CL_Y_Out_pipeTop2 = bird.getDes().y <= (pipeTop2.getDes().y + pipeTop2.getHeight());
	bool CL_Y_Out_Pipender2 = (bird.getDes().y + bird.getHeight()) >= pipeUnder2.getDes().y;

	if (CL_X_pipeTop1 && CL_Y_pipeTop1) {
		cout << "cham tren 1" << endl;
		//Collide();
		return true;
	}
	if (CL_X_pipeTop2 && CL_Y_pipeTop2) {
		cout << "cham tren 2" << endl;
		return true;
	}
	if (CL_X_pipeUnder1 && CL_Y_pipeUnder1) {
		cout << "cham duoi 1" << endl;
		return true;
	}
	if (CL_X_pipeUnder2 && CL_Y_pipeUnder2) {
		cout << "cham duoi 2" << endl;
		return true;
	}
	if (CL_X_In_pipes1 && (CL_Y_In_pipeTop1 || CL_Y_In_pipeUnder1)) {
		cout << "cham vao 1" << endl;
		return true;
	}
	if (CL_X_In_pipes2 && (CL_Y_In_pipeTop2 || CL_Y_In_pipeUnder2)) {
		cout << "cham vao 2" << endl;
		return true;
	}
	if (CL_X_Out_pipes1 && (CL_Y_Out_pipeTop1 || CL_Y_Out_Pipender1)) {
		cout << "cham ra 1" << endl;
		return true;
	}
	if (CL_X_Out_pipes2 && (CL_Y_Out_pipeTop2 || CL_Y_Out_Pipender2)) {
		cout << "cham ra 2" << endl;
		return true;
	}
	return false;
}

bool GameLoop::Score() {
	if (bird.getDes().x == (pipeTop1.getDes().x + pipeTop1.getWidth())) {
		return true;
	}
	if (bird.getDes().x == (pipeTop2.getDes().x + pipeTop2.getWidth())) {
		return true;
	}
	return false;
}

void GameLoop::DisplayScore() {
	if (Score()) {
		Mix_PlayChannel(-1, sound_score, 0);
		score++;
		cout << "+1" << endl;
	}
}


void GameLoop::RenderAgain() {
	SDL_RenderClear(renderer);
	text_score_Rect = { WIDTH_SCREEEN/2 - FontSize/2 + 7,255,text_score_Suf->w, text_score_Suf->h };
	backgroundAgain.Render(renderer);
	transcript.RenderItem(renderer);
	gameOver.RenderItem(renderer);
	// score
	SDL_RenderCopy(renderer, text_score_Tex, NULL, &text_score_Rect);
	//high score
	CheckScore();
	text_hightScore = to_string(hightScore);
	text_highScore_Suf = TTF_RenderText_Solid(font, text_hightScore.c_str(), { 255,255,255 });
	text_highScore_Tex = SDL_CreateTextureFromSurface(renderer, text_highScore_Suf);
	text_highScore_Rect = { WIDTH_SCREEEN/2 - FontSize/2 + 7,350,text_highScore_Suf->w, text_highScore_Suf->h };
	SDL_RenderCopy(renderer, text_highScore_Tex, NULL, &text_highScore_Rect);

	playAgain.setScr(0, positionPlayAgain, 1099, 549.5);
	playAgain.setDes(25, 400, 150, 75);
	playAgain.Render(renderer);

	Exit.setScr(0, positionExit, 1099, 549.5);
	Exit.setDes(225, 400, 150, 75);
	Exit.Render(renderer);
	SDL_RenderPresent(renderer);
}

void GameLoop::EventPlayAgain() {
	SDL_PollEvent(&eventAgain);
	if (eventAgain.type == SDL_QUIT) {
		gameState = false;
		running = false;
	}
	if (eventAgain.type == SDL_MOUSEMOTION) {
		if ((eventAgain.motion.x >= 25 && eventAgain.motion.x <= 175) && (eventAgain.motion.y >= 400 && eventAgain.motion.y <= 475)) {
			positionPlayAgain = 0;
		}
		else {
			positionPlayAgain = 549.5;
		}
	}
	if (eventAgain.type == SDL_MOUSEMOTION) {
		if ((eventAgain.motion.x >= 225 && eventAgain.motion.x <= 375) && (eventAgain.motion.y >= 400 && eventAgain.motion.y <= 475)) {
			positionExit = 0;
		}
		else {
			positionExit = 549.5;
		}
	}
	if (eventAgain.type == SDL_MOUSEBUTTONDOWN) {
		if ((eventAgain.motion.x >= 25 && eventAgain.motion.x <= 175) && (eventAgain.motion.y >= 400 && eventAgain.motion.y <= 475)) {
			//bird
			bird.setDes((WIDTH_SCREEEN / 2) - (bird.getWidth() / 2), (HEIGHT_SCREEN / 2) - (bird.getHeight() / 2), bird.getWidth(), bird.getHeight());
			bird.setX(bird.getDistanceX());
			bird.setY(bird.getDistanceY());
			//floor
			floor1.setMoveFloor1(floor1.getOC_X_Floor1());
			floor2.setMoveFloor2(floor2.getOC_X_Floor2());
			floor1.setDes(floor1.getOC_X_Floor1(), floor1.getOC_Y_Floor1(), floor1.getWidth(), floor1.getHeight());
			floor2.setDes(floor2.getOC_X_Floor2(), floor2.getOC_Y_Floor2(), floor2.getWidth(), floor1.getHeight());
			//pipe
			pipeTop1.setMovePipe1(WIDTH_SCREEEN);
			pipeTop2.setMovePipe2(pipeTop1.getMove1() + pipeTop1.getWidth() + pipeTop1.getDistance2Occurrences());
			pipeTop1.setDes(pipeTop1.getMove1(), pipeTop1.getDelta_y1(), pipeTop1.getWidth(), pipeTop1.getHeight());
			pipeUnder1.setDes(pipeTop1.getDes().x, pipeTop1.getDes().y + pipeTop1.getHeight() + pipeTop1.getDistance2Pipe(), pipeUnder1.getWidth(), pipeUnder1.getHeight());
			pipeTop2.setDes(pipeTop2.getMove2(), pipeTop2.getDelta_y2(), pipeTop2.getWidth(), pipeTop2.getHeight());
			pipeUnder2.setDes(pipeTop2.getDes().x, pipeTop2.getDes().y + pipeTop2.getHeight() + pipeTop2.getDistance2Pipe(), pipeUnder2.getWidth(), pipeUnder2.getHeight());
			gameState = true;
			running = false;
			start = false;
		}
		else if ((eventAgain.motion.x >= 225 && eventAgain.motion.x <= 375) && (eventAgain.motion.y >= 400 && eventAgain.motion.y <= 475)) {
			gameState = false;
			running = false;
		}
	}
}

void GameLoop::PlayAgain() {
	SDL_Delay(500);
	Mix_PlayChannel(-1, sound_die, 0);
	while (running == true) {
		EventPlayAgain();
		RenderAgain();
		first = SDL_GetTicks();
		if (first - last < 16.7)
		{
			SDL_Delay(16.7 - (first - last));
			//cout << 1000 / ((16.7 - (first - last)) + (first - last)) << endl;
		}
		last = first;
	}
}

void GameLoop::Running() {
	score = 0;
	while (gameState == true) {
		Event();
		Update();
		Render();
		first = SDL_GetTicks();
		if (first - last < 16.7)
		{
			SDL_Delay(16.7 - (first - last));
			//cout << 1000 / ((16.7 - (first - last)) + (first - last)) << endl;
		}
		last = first;
	}
}

void GameLoop::CheckScore() {
	ifstream hightscore_file;
	hightscore_file.open("highscore.txt");
	hightscore_file >> hightScore;
	hightscore_file.close();
	if (score > hightScore) {
		ofstream score_file;
		score_file.open("highscore.txt");
		score_file << score;
		score_file.close();
	}
}