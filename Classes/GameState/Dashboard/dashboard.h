#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include <list>
#include <SDL.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>


class Dashboard {
public:
	Dashboard setupDashboard();
	Texture wallpaper;
	std::list<App> appList;
	Xynergy_TaskbarMode taskbarMode;
	Xynergy_TaskBarOrientation taskbarOrientation;
private:
	std::list<App> appListSetup();
	void taskbarSetup();
};

#endif