#include "app.h"

std::string App::getName() {
	return name;
}
std::string App::getDescription() {
	return description;
}
Xynergy_AppType App::getAppType() {
	return appType;
}


void App::setupApp(std::string appName, Xynergy_AppType type, std::string appDescription) {
	name = appName;
	appType = type;
	description = appDescription;
}

App::App() {
	appType = Xynergy_AppType::XYNERGY_APP_EMPTY;
}