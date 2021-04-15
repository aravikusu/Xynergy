#include "app.h"

void App::render(SDL_Renderer* ren) {
	if (showOnDashboard) {
		icon.render(appX, appY, ren);
		name.render((appX - 10), (appY + 50), ren);
	}
}

void App::toggleShow() {
	showOnDashboard = !showOnDashboard;
}

void App::setCoordinates(int x, int y) {
	appX = x;
	appY = y;
}

void App::setAppType(Xynergy_AppType type) {
	appType = type;
}


void App::setupApp(std::string iconName, std::string appName, SDL_Color textColor, TTF_Font* font, SDL_Renderer* ren) {
	std::string iconPath = "Materials/textures/icons/";
	icon.loadFile(iconPath + iconName, ren);
	// Check if the icon was sucessfully made or not, and if it wasn't use the error icon
	if (icon.getHeight() == 0) {
		icon.loadFile(iconPath + "iconerror.png", ren);
	}

	// Again, if font is NULL we'll open Roboto.
	// It's not performance efficient to constantly open and close fonts.
	// This is more of a failsafe. Do not rely on this.
	if (font == NULL) {
		font = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 18);
		name.loadText(appName, textColor, font, 16, ren);
		TTF_CloseFont(font);
	}
	else {
		name.loadText(appName, textColor, font, 16, ren);
	}
}

App::App() {
	appX = 0;
	appY = 0;
	appType = Xynergy_AppType::XYNERGY_APP_EMPTY;
}

App::~App() {
	icon.kill();
	name.kill();

}