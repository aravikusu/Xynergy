#include "usersettings.h"

void UserSettings::readUserSettings(std::string username) {
	mINI::INIFile file("./users/" + username + ".ini");
	mINI::INIStructure ini;

	if (file.read(ini)) {
		name = ini.get("user_related").get("name");
		displayName = ini.get("user_related").get("displayName");
		currentTheme = ini.get("personalisation").get("theme");
		curentOrientation = XynergyHelper::enum_converter::stringToTaskbarOrientation(ini.get("personalisation").get("taskbarOrientation"));
		currentWallpaper = ini.get("personalisation").get("wallpaper");

		std::cout << "UserSettings::readUserSettings:" << XynergyHelper::console::success() << username << "'s settings has been loaded!\n";
	}
	else {
		std::cout << "UserSettings::readUserSettings:" << XynergyHelper::console::error() << "user "  << username << " could not be found!\n";
	}
}

void UserSettings::writeUserSettings() {
	mINI::INIFile file(name + ".ini");
	mINI::INIStructure ini;

	// Warning that gets appended to the top of each settings file
	ini["WARNING!"];
	ini["The chance of you breaking your save file if you edit this is > 0%."];
	ini["I'm not held responsible for dumb decisions."];
	ini["You should probably just avoid it."];

	// Now let's actually set all the settings.

	std::string orientation = XynergyHelper::enum_converter::taskbarOrientationToString(curentOrientation);

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
		std::cout << "UserSettings::writeUserSettings:" << XynergyHelper::console::success() << "Settings have been saved for " << displayName << "!\n";
	}

	file.~INIFile();
}

void UserSettings::clearSettings() {

}