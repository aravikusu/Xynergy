#include "xynergy.h"

bool Xynergy::init() {
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL_Init failure: %s\n", SDL_GetError());
		success = false;
	}

	int width = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_WIDTH));
	int height = std::stoi(settings.fetchSetting(Xynergy_SettingsType::XYNERGY_HEIGHT));
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
		printf("SDL_CreateWindowAndRenderer failure: %s\n", SDL_GetError());
		success = false;
	}

	return success;
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
	switch (currentState) {
	case Xynergy_GameState::XYNERGY_BOOT:
		break;
	case Xynergy_GameState::XYNERGY_LOGIN:
		break;
	case Xynergy_GameState::XYNERGY_DASHBOARD:
		break;
	case Xynergy_GameState::XYNERGY_INITSETUP:
		break;
	}
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_Rect rect{};
	rect.x = rect.y = 0;
	rect.w = 1280;
	rect.h = 720;
	SDL_RenderFillRect(renderer, &rect);

	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < (1000 / 60)) {
		SDL_Delay((1000 / 60) - timerFPS);
	}

	SDL_RenderPresent(renderer);
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
		printf("Initialization failure! Game over!\n\nCheck the console for further errors that lead here.");
	}
	else {
		SDL_SetWindowTitle(window, "Xynergy");
		running = true;
		currentState = Xynergy_GameState::XYNERGY_BOOT;
		loop();
	}
}

Xynergy::~Xynergy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}