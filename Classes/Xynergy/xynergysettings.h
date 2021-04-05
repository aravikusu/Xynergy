#ifndef XYNERGYSETTINGS_H
#define XYNERGYSETTINGS_H

#include <string>
#include <Utils/enums.h>

/// <summary>
/// XynergySettings is here to make it easy to save and fetch settings.
/// </summary>
class XynergySettings {
public:
	XynergySettings();
	~XynergySettings();
	bool saveSetting(std::string);
	std::string fetchSetting(Xynergy_SettingsType);
private:
	void setDefault();
	bool debug;
	int width, height;
	Xynergy_WindowMode windowMode;
};

#endif