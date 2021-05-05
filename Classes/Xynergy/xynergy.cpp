#include "xynergy.h"

bool Xynergy::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Xynergy::init: %s SDL_Init failure: %s\n", "\033[0;31mError!\033[0;37m", SDL_GetError());
		success = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2")) {
			printf("Xynergy::init: %s Linear texture filtering could not be enabled!", "\033[0;33mWarning!\033[0;37m");
		}
		int width = settings.getWidth();
		int height = settings.getHeight();
		if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC, &window, &renderer) < 0) {
			printf("Xynergy::init: %s SDL_CreateWindowAndRenderer failure: %s\n", "\033[0;31mError!\033[0;37m", SDL_GetError());
			success = false;
		}
		else {
			SDL_SetWindowTitle(window, windowName);

			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("Xynergy::init: %s IMG_init failure: %s\n", "\033[0;31mError!\033[0;37m", IMG_GetError());
				success = false;
			}

			if (TTF_Init() == -1) {
				printf("Xynergy::init: %s TTF_Init failure: %s\n", "\033[0;31mError!\033[0;37m", TTF_GetError());
				success = false;
			}

		}
	}

	switch (settings.getWindowMode())
	{
	case Xynergy_WindowMode::XYNERGY_WINDOW:
		SDL_SetWindowFullscreen(window, 0);
		break;
	case Xynergy_WindowMode::XYNERGY_BORDERLESS:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		break;
	case Xynergy_WindowMode::XYNERGY_FULLSCREEN:
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
		break;
	default:
		break;
	}

	return success;
}

void Xynergy::changeGameState(Xynergy_GameState state) {
	if (currentState != state) {
		clearGameState();
		currentState = state;

		switch (state)
		{
		case Xynergy_GameState::XYNERGY_BOOT:
			boot.setupBoot(renderer);
			break;
		case Xynergy_GameState::XYNERGY_LOGIN:
			break;
		case Xynergy_GameState::XYNERGY_DASHBOARD:
			dashboard.setupDashboard(renderer, currentUser);
			break;
		case Xynergy_GameState::XYNERGY_INITSETUP:
			break;
		}
	}
}

void Xynergy::clearGameState() {
	switch (currentState)
	{
	case Xynergy_GameState::XYNERGY_BOOT:
		boot.clear();
		break;
	case Xynergy_GameState::XYNERGY_LOGIN:
		break;
	case Xynergy_GameState::XYNERGY_DASHBOARD:
		break;
	case Xynergy_GameState::XYNERGY_INITSETUP:
		break;
	default:
		break;
	}
}

void Xynergy::loop() {
	while (running) {
		lastFrame = SDL_GetTicks();
		static int lastTime;
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
			fps = frameCount;
			frameCount = 0;
		}

		render();
		input();
		update();
	}
}

/// <summary>
/// The main render function for the game loop.
/// <para>It breaks off depending on which state the game is in. </para>
/// </summary>
void Xynergy::render() {
	SDL_RenderClear(renderer);

	// There's more detailed descriptions of each gamestate in their class.
	switch (currentState) {
	case Xynergy_GameState::XYNERGY_BOOT:
		drawBoot();
		break;
	case Xynergy_GameState::XYNERGY_LOGIN:
		drawLogin();
		break;
	case Xynergy_GameState::XYNERGY_DASHBOARD:
		drawDashboard();
		break;
	case Xynergy_GameState::XYNERGY_INITSETUP:
		break;
	}

	bool debugMode = settings.getDebug();
	if (debugMode) {
		drawDebug();
	}

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;

	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}

	SDL_RenderPresent(renderer);
}

void Xynergy::drawBoot() {
	boot.renderBootAnimation(renderer, settings.getWidth(), settings.getHeight());
}

void Xynergy::drawLogin() {

}

void Xynergy::drawDashboard() {
	int width = settings.getWidth();
	int height = settings.getHeight();

	dashboard.renderDashboard(renderer, width, height);
}

void Xynergy::drawDebug() {
	int width = settings.getWidth();
	int height = settings.getHeight();
	debug.render(fps, width, height, renderer);
}

void Xynergy::toggleDebug() {
	if (!debug.getSetup()) {
		debug.setupDebug("Roboto-Regular.ttf", "Xynergy Engine", "For private use only. Evaluation build: 0001", renderer);
	}
}

void Xynergy::input() {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) running = false;
	}

	if (currentState == Xynergy_GameState::XYNERGY_BOOT) {
		if (keystates[SDL_SCANCODE_ESCAPE] || keystates[SDL_SCANCODE_KP_ENTER] || keystates[SDL_SCANCODE_SPACE]) {
			changeGameState(Xynergy_GameState::XYNERGY_LOGIN);
		}
	}

	if (keystates[SDL_SCANCODE_C] && SDL_GetModState() && KMOD_CTRL) {
		SDL_SetClipboardText("");
	}
	else if (keystates[SDL_SCANCODE_V] && SDL_GetModState() && KMOD_CTRL) {
		SDL_GetClipboardText();
	}
}

void Xynergy::update() {

}

Xynergy::Xynergy() {
	if (!init()) {
		printf("\033[0;31mInitialization failure!\033[0;37m \n\nCheck the console for further errors that lead here.\n");
	}
	else {
		running = true;
		changeGameState(Xynergy_GameState::XYNERGY_BOOT);
		toggleDebug();

		loop();
	}
}

Xynergy::~Xynergy() {
	printf("\033[0;35mXynergy\033[0;37m is shutting down.\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}