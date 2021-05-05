#include "usersettings.h"

void UserSettings::readUserSettings(std::string username) {
	mINI::INIFile file(username + ".ini");
	mINI::INIStructure ini;

	if (file.read(ini)) {
		name = ini.get("main_window").get("name");
		displayName = ini.get("main_window").get("displayName");
		currentTheme = ini.get("personalisation").get("theme");
		curentOrientation = stringToTaskbarOrientation(ini.get("personalisation").get("taskbarOrientation"));
		currentWallpaper = ini.get("personalisation").get("wallpaper");

		printf("UserSettings::readUserSettings: %s %s's settings has been loaded!\n", "\033[0;32mSuccess!\033[0;37m", username.c_str());
	}
	else {
		printf("UserSettings::readUserSettings: %s user %s could not be found!\n", "\033[0;31mError!\033[0;37m", username.c_str());
	}
}

void UserSettings::writeUserSettings() {
	mINI::INIFile file(name + ".ini");
	mINI::INIStructure ini;

	// Warning that gets appended to the top of each settings file
	ini[";WARNING!\n;The chance of you breaking your save file if you edit this is > 0%.\n"
		";I'm not held responsible for dumb decisions.\n"
		";You should probably just avoid it."];

	// Now let's actually set all the settings.

	std::string orientation = TaskbarOrientationToString(curentOrientation);

	ini["user_related"].set({
		{"name", name},
		{"displayName", displayName}
	});
	ini["personalisation"].set({
		{"theme", currentTheme},
		{"taskbarOrientation", orientation},
		{"wallpaper", currentWallpaper}
	});

	if (file.write(ini)) {
		printf("UserSettings::writeUserSettings: %s Settings have been saved!\n", "\033[0;32mSuccess!\033[0;37m");
	}

	file.~INIFile();
}

std::string UserSettings::TaskbarOrientationToString(Xynergy_TaskbarOrientation orientation) {
	switch (orientation)
	{
	case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP:
		return "top";
	case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT:
		return "right";
	case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM:
		return "bottom";
	case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT:
		return "left";
	}
}

Xynergy_TaskbarOrientation UserSettings::stringToTaskbarOrientation(std::string orientation) {
	if (orientation == "top") {
		return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP;
	}
	else if (orientation == "right") {
		return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT;
	}
	else if (orientation == "bottom") {
		return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM;
	}
	else if (orientation == "left") {
		return Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT;
	}
}

void UserSettings::clearSettings() {

}