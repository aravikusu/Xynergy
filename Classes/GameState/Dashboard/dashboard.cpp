#include "dashboard.h";

void Dashboard::appListSetup(SDL_Renderer* ren) {
	SDL_Color color = { 0, 0, 0 };
	TTF_Font* font = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 18);
	App testApp;
	testApp.setupApp("Test App", Xynergy_AppType::XYNERGY_APP_IMAGE, "");
	DashboardIcon testIcon;
	icons.push_back(testIcon);
	icons[0].setupDashboardIcon(testApp, "iconerror.png", color, font, ren);
	icons[0].setCoordinates(15, 10);

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
	for (int i = 0; i < icons.size(); i++) {
		icons[i].render(ren);
	}

	//Lastly we render the taskbar because we want it to have priority.
	taskbar.renderTaskbar(ren, width, height);
}

void Dashboard::setupDashboard(SDL_Renderer* ren, UserSettings currentUser) {
	wallpaper.loadFile("Materials/textures/wallpapers/" + currentUser.currentWallpaper, ren);
	taskbar.setupTaskbar(ren, currentUser);
	appListSetup(ren);
}

void Dashboard::handleEvents(SDL_Event e) {
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		for (auto& icon : icons) {
			icon.handleMotionEvent(e.motion);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (auto& icon : icons) {
			icon.handleClickEvent(e.button);
		}
		break;
	}
}

// Go on user settings eventually...
Dashboard::Dashboard() {

}

Dashboard::~Dashboard() {
	wallpaper.kill();
	icons.clear();
}