#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <list>
#include <SDL.h>
#include <Classes/App/app.h>


class Dashboard {
public:
	Dashboard();
	~Dashboard();
	SDL_Texture* wallpaper;
	std::list<App> appList;
	Xynergy_TaskbarMode taskbarMode;
	Xynergy_TaskBarOrientation taskbarOrientation;
private:

};

#endif