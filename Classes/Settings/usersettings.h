#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#define MINI_CASE_SENSITIVE
#include <string>
#include <iostream>
#include <Utils/libs/ini.h>
#include <SDL.h>
#include <Utils/enums.h>
#include <Utils/xynergyhelper.h>
#include <Utils/libs/ini.h>

/// <summary>
/// Aka the "save file". Also one of the few functions that is completely public.
/// </summary>
class UserSettings {
public:
	/// <summary>
	/// Fetches the settings file for the requested user and reads all the data.
	/// </summary>
	void readUserSettings(std::string username);

	/// <summary>
	/// Save all current settings to the requested user.
	/// </summary>
	/// <param name="username"></param>
	void writeUserSettings();

	/// <summary>
	/// Clears out all current settings in memory.
	/// </summary>
	void clearSettings();

	std::string name;
	std::string displayName;
	std::string currentWallpaper;
	std::string currentTheme;
	Xynergy_TaskbarOrientation curentOrientation;
};

#endif