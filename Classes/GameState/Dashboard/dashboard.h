#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include <SDL.h>
#include <Classes/GameState/Dashboard/taskbar.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>


class Dashboard {
public:
	Dashboard();
	~Dashboard();

	// Called by Xynergy::render() when the game state changes into Dashboard.
	void setupDashboard(SDL_Renderer* ren);

	// Renders the entire dashboard.
	void renderDashboard(SDL_Renderer* ren, int width, int height);
private:
	Texture wallpaper;
	Taskbar taskbar;
	std::vector<App> apps;

	//Set up all the apps you wish to render to the Dashboard here.
	void appListSetup(SDL_Renderer* ren);
};

#endif