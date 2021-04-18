#include "dashboard.h";

void Dashboard::appListSetup(SDL_Renderer* ren) {
	SDL_Color color = { 0, 0, 0 };
	TTF_Font* font = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 18);
	App testApp;
	apps.push_back(testApp);
	apps[0].setupApp("iconerror.png", "Test App", color, font, ren);
	apps[0].setCoordinates(15, 10);

	/*App testApp2 = { "iconerror.png", "Test App", color, font, ren };
	testApp2.setCoordinates(50, 0);
	apps.push_back(testApp2);*/

	TTF_CloseFont(font);
}

void Dashboard::renderDashboard(SDL_Renderer* ren, int width, int height) {
	// First we render the wallpaper since it goes at the very back.
	wallpaper.render(0, 0, ren);
	// Loop through and render the apps we created in appListSetup().
	/*for (auto it = begin(appList); it != end(appList); ++it) {
		it->render(ren);
	}*/
	for (int i = 0; i < apps.size(); i++) {
		apps[i].render(ren);
	}

	//Lastly we render the taskbar because we want it to have priority.
	taskbar.renderTaskbar(ren, width, height);
}

void Dashboard::setupDashboard(SDL_Renderer* ren) {
	printf("Dashboard is being set up.\n");
	wallpaper.loadFile("Materials/textures/wallpapers/xynergy-b.png", ren);
	taskbar.setupTaskbar(ren);
	appListSetup(ren);
}

// Go on user settings eventually...
Dashboard::Dashboard() {

}

Dashboard::~Dashboard() {
	//printf("Dashboard is being killed!\n");
	wallpaper.kill();
	apps.clear();
}