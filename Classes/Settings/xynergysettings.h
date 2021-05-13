#ifndef XYNERGYSETTINGS_H
#define XYNERGYSETTINGS_H

#include <string>
#include <iostream>
#include <Utils/enums.h>
#include <type_traits>
#include <Utils/libs/ini.h>
#include <Utils/xynergyhelper.h>

/// <summary>
/// XynergySettings is meant to handle settings for the game itself, such as window mode and size, not user data.
/// <para>Everything here is stored in a settings.ini file in the same folder as the .exe.</para>
/// </summary>
class XynergySettings {
public:
	/// <summary>
	/// When Xynergy first starts up it tries to find the .ini file that contains the user's current settings.
	/// <para>If it fails to do so it sets them to default.</para>
	/// </summary>
	XynergySettings();

	/// <summary>
	/// The XynergySettings' deconstructor runs when the game closes.
	/// <para>It simply takes all current settings and saves them to the settings.ini file.</para>
	/// </summary>
	~XynergySettings();

	/// <summary>
	/// Saves the value you send in to the SettingsType you chose.
	/// </summary>
	/// <param name="type">The setting you wish to save to.</param>
	/// <param name="value">The value you want to save. Can be anything. If unsure, check the function for its use.</param>
	/// <returns>True if the setting successfully saved, false if not.</returns>
	template<typename T>
	bool saveSetting(Xynergy_SettingsType type, T value);

	bool getDebug();
	int getWidth();
	int getHeight();
	Xynergy_WindowMode getWindowMode();
	std::string getLastTheme();
private:
	/// <summary>
	/// Runs if settings.ini wasn't found. Simply creates it and defaults settings.
	/// </summary>
	void setDefault(mINI::INIFile file, mINI::INIStructure ini);

	/// <summary>
	/// Runs if settings.ini was found. Reads it and applies settings.
	/// </summary>
	void setExisting(mINI::INIFile file, mINI::INIStructure ini);

	bool debug;
	int width, height;
	Xynergy_WindowMode windowMode;
	std::string lastTheme;
};

#endif