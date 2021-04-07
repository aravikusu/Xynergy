#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <list>
#include <SDL.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>
#include <filesystem>


class Dashboard {
public:
	Dashboard(SDL_Renderer* ren);
	~Dashboard();
	void renderDashboard(SDL_Renderer* ren);
private:
	Texture wallpaper;
	Texture taskbar;
	std::list<App> appList;
	void appListSetup();
	void taskbarSetup();
	void wallpaperSetup(SDL_Renderer* ren);
};

#endif