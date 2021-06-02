#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <vector>
#include <SDL.h>
#include <Classes/Settings/usersettings.h>
#include <Classes/GameState/Dashboard/taskbar.h>
#include <Classes/App/app.h>
#include <Classes/GameState/Dashboard/dashboardicon.h>
#include <Classes/Texture/texture.h>

/// <summary>
/// The biggest and most complex game state.
/// <para>The main game takes place here.</para>
/// </summary>
class Dashboard {
public:
	Dashboard();
	~Dashboard();

	// Called by Xynergy::render() when the game state changes into Dashboard.
	void setupDashboard(SDL_Renderer* ren, UserSettings currentUser);

	// Renders the entire dashboard.
	void renderDashboard(SDL_Renderer* ren, int width, int height);

	void handleEvents(SDL_Event e);
private:
	Texture wallpaper;
	Taskbar taskbar;
	std::vector<DashboardIcon> icons;

	//Set up all the apps you wish to render to the Dashboard here.
	void appListSetup(SDL_Renderer* ren);
};

#endif