#include "dashboardicon.h"

void DashboardIcon::render(SDL_Renderer* ren) {
	if (show) {
		icon.render(coordinates.x, coordinates.y, ren);
		name.render((coordinates.x - 10), (coordinates.y + 50), ren);
	}
}

void DashboardIcon::setupDashboardIcon(App app, std::string iconName, SDL_Color textColor, TTF_Font* font, SDL_Renderer* ren) {
	std::string iconPath = "Materials/textures/icons/";
	icon.loadFile(iconPath + iconName, ren);
	// Check if the icon was sucessfully made or not, and if it wasn't use the error icon
	if (icon.getHeight() == 0) {
		icon.loadFile(iconPath + "iconerror.png", ren);
	}

	std::string appName = app.getName();

	// If font is NULL we'll use Roboto.
	if (font == NULL) {
		font = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 18);
		name.loadText(appName, textColor, font, 16, ren, false, 30);
		TTF_CloseFont(font);
	}
	else {
		name.loadText(appName, textColor, font, 16, ren, false, 30);
	}
}

void DashboardIcon::toggleShow() {
	show = !show;
}

void DashboardIcon::setCoordinates(int x, int y) {
	show = true;
	coordinates.x = x;
	coordinates.y = y;
}

void DashboardIcon::handleMotionEvent(SDL_MouseMotionEvent& e) {
	if (e.type == SDL_MOUSEMOTION) {
		int fullHeight = icon.getHeight() + name.getHeight();
		bool inside = XynergyHelper::event_helper::checkInside(e.x, e.y, icon.getWidth(), fullHeight, coordinates);

		if (inside) {

		}
	}
}

void DashboardIcon::handleClickEvent(SDL_MouseButtonEvent& e) {

}

DashboardIcon::DashboardIcon() {
	show = false;
	coordinates.x, coordinates.y = 0;
}