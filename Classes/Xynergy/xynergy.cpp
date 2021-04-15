#include "xynergy.h"

bool Xynergy::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Xynergy::init: SDL_Init failure: %s\n", SDL_GetError());
		success = false;
	}
	else {

		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Xynergy::init: Warning! Linear texture filtering could not be enabled!");
		}

		int width = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_WIDTH));
		int height = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_HEIGHT));
		if (SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED, &window, &renderer) < 0) {
			printf("Xynergy::init: SDL_CreateWindowAndRenderer failure: %s\n", SDL_GetError());
			success = false;
		}
		else {
			SDL_SetWindowTitle(window, windowName);

			int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags)) {
				printf("Xynergy::init: IMG_init failure: %s\n", IMG_GetError());
				success = false;
			}

			if (TTF_Init() == -1) {
				printf("Xynergy::init: TTF_Init failure: %s\n", TTF_GetError());
				success = false;
			}

		}
	}

	return success;
}

void Xynergy::changeGameState(Xynergy_GameState state) {
	currentState = state;

	switch (state)
	{
	case Xynergy_GameState::XYNERGY_BOOT:
		break;
	case Xynergy_GameState::XYNERGY_LOGIN:
		break;
	case Xynergy_GameState::XYNERGY_DASHBOARD:
		dashboard.setupDashboard(renderer);
		break;
	case Xynergy_GameState::XYNERGY_INITSETUP:
		break;
	}
}

void Xynergy::loop() {
	while (running) {
		lastFrame = SDL_GetTicks();
		static int lastTime;
		if (lastFrame >= (lastTime + 1000)) {
			lastTime = lastFrame;
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

	switch (currentState) {
	case Xynergy_GameState::XYNERGY_BOOT:
		break;
	case Xynergy_GameState::XYNERGY_LOGIN:
		break;
	case Xynergy_GameState::XYNERGY_DASHBOARD:
		drawDashboard();
		break;
	case Xynergy_GameState::XYNERGY_INITSETUP:
		break;
	}

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}

	SDL_RenderPresent(renderer);
}

void Xynergy::drawDashboard() {
	int width = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_WIDTH));
	int height = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_HEIGHT));

	dashboard.renderDashboard(renderer, width, height);
}

void Xynergy::input() {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) running = false;
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
		printf("Initialization failure! \n\nCheck the console for further errors that lead here.\n");
	}
	else {
		running = true;
		changeGameState(Xynergy_GameState::XYNERGY_DASHBOARD);
		loop();
	}
}

Xynergy::~Xynergy() {
	printf("Xynergy is shutting down.\nIt's now save to turn off your computer.\n");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}