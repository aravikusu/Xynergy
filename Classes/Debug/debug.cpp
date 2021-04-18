#include "debug.h"

void Debug::setupDebug(std::string fontName, std::string name, std::string fluff, SDL_Renderer* ren) {
	debugFont = TTF_OpenFont(("Materials/fonts/" + fontName).c_str(), 20);

	SDL_Color color = { 255, 255, 255 };
	nameTexture.loadText(name, color, debugFont, 26, ren);

	TTF_CloseFont(debugFont);
	debugFont = TTF_OpenFont(("Materials/fonts/" + fontName).c_str(), 14);
	versionFluffTexture.loadText(fluff, color, debugFont, 14, ren);
}

void Debug::render(int fps, int windowWidth, int windowHeight, SDL_Renderer* ren) {

	SDL_Color color = { 255, 255, 255 };
	fpsTexture.loadText(("FPS: " + std::to_string(fps)), color, debugFont, 14, ren);

	//int x = (windowWidth - versionFluffTexture.getWidth()) - 10;
	//int totalY = (windowHeight - (nameTexture.getHeight() + versionFluffTexture.getHeight() + fpsTexture.getHeight()));

	nameTexture.render((windowWidth - 275), (windowHeight - 125), ren);
	versionFluffTexture.render((windowWidth - 275), (windowHeight - 100), ren);
	fpsTexture.render((windowWidth - 78), (windowHeight - fpsTexture.getHeight()) - 40, ren);
}

bool Debug::getSetup() {
	return isSetup;
}

Debug::Debug() {
	isSetup = false;
	debugFont = NULL;
}

Debug::~Debug() {
	nameTexture.kill();
	versionFluffTexture.kill();
	fpsTexture.kill();
	TTF_CloseFont(debugFont);
}