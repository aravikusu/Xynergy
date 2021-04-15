#ifndef XYNERGYSETTINGS_H
#define XYNERGYSETTINGS_H

#include <string>
#include <Utils/enums.h>
#include <type_traits>

/// <summary>
/// XynergySettings is meant to handle settings for the game itself, such as window mode and size, not user data.
/// <para>Everything here is stored in a settings.ini file in the same folder as the .exe.</para>
/// </summary>
class XynergySettings {
public:
	XynergySettings();
	~XynergySettings();
	template<typename T>
	bool saveSetting(Xynergy_SettingsType, T);
	std::string fetchSetting(Xynergy_SettingsType);
private:
	void setDefault();
	bool debug;
	int width, height;
	Xynergy_WindowMode windowMode;
};

#endif