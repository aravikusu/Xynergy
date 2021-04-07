#include "dashboard.h";

/// <summary>
///  Here's where you put which apps you want to have.
/// </summary>
void Dashboard::appListSetup() {

}

/// <summary>
/// Sets up all the taskbar textures and components.
/// <para>If no XynergyUserSettings can be found it uses defaults.</para>
/// </summary>
void Dashboard::taskbarSetup() {

}

/// <summary>
/// Sets up all the wallpaper for the Dashboard.
/// <para>If no XynergyUserSettings can be found it uses defaults.</para>
/// </summary>
void Dashboard::wallpaperSetup(SDL_Renderer* ren) {
	// Implement UserSettings...
	wallpaper.loadFile("Materials/textures/wallpapers/xynergy-b.png", ren);
}

/// <summary>
/// The main Dashboard rendering function. It does a lot.
/// </summary>
void Dashboard::renderDashboard(SDL_Renderer* ren) {
	// First we render the wallpaper since it goes at the very back.
	wallpaper.render(0, 0, ren);
}

/// <summary>
/// The entire Dashboard is generated in its Constructor.
/// </summary>
/// <param name="taskbarMode"></param>
/// <param name="taskbarOrientation"></param>
Dashboard::Dashboard(SDL_Renderer* ren) {

	wallpaperSetup(ren);
}

Dashboard::~Dashboard() {
	wallpaper.kill();
	appList.clear();
}