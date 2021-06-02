#ifndef DASHBOARDICON_H
#define DASHBOARDICON_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>
#include <Utils/xynergyhelper.h>

/// <summary>
/// As the name implies it's an icon that links to an App.
/// <para>Used on the Dashboard as a button to open an App.</para>
/// </summary>
class DashboardIcon {
public :
	DashboardIcon();
	void setupDashboardIcon(App app, std::string iconName, SDL_Color textColor, TTF_Font* font, SDL_Renderer* ren);
	void setCoordinates(int x, int y);
	void render(SDL_Renderer* ren);
	void toggleShow();
	void handleMotionEvent(SDL_MouseMotionEvent& e);
	void handleClickEvent(SDL_MouseButtonEvent& e);
private:
	Texture icon;
	Texture name;
	App app;
	bool show;
	SDL_Point coordinates;
};

#endif