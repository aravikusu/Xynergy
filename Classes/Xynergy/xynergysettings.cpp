#include "xynergysettings.h";

/// <summary>
/// Simply put, it fetches the value of the setting that you requested.
/// </summary>
/// <param name="type">The requested setting. Has to be a Xynergy_SettingsType enum.</param>
/// <returns>Your desired setting.</returns>
std::string XynergySettings::fetchSetting(Xynergy_SettingsType type) {
	std::string val;

	switch (type) {
	case Xynergy_SettingsType::XYNERGY_HEIGHT:
		val = std::to_string(height);
		break;
	case Xynergy_SettingsType::XYNERGY_WIDTH:
		val = std::to_string(width);
		break;
	case Xynergy_SettingsType::XYNERGY_WINDOWMODE:
		break;
	}

	return val;
}

/// <summary>
/// Runs if settings.ini wasn't found. Simply creates it and defaults settings.
/// </summary>
void XynergySettings::setDefault() {
	printf("XynergySettings: Warning! settings.ini was not found! Creating and defaulting settings.");
	debug = false;
	width = 1280;
	height = 720;
	windowMode = Xynergy_WindowMode::XYNERGY_WINDOW;
}

/// <summary>
/// When Xynergy first starts up it tries to find the .ini file that contains the user's current settings.
/// <para>If it fails to do so it sets them to default.</para>
/// </summary>
XynergySettings::XynergySettings() {
	//TODO: if-statement if it finds the settings or not.

	setDefault();
}

/// <summary>
/// The XynergySettings' deconstructor runs when the app closes.
/// <para>It simply takes all current settings and saves them to the settings.ini file.</para>
/// </summary>
XynergySettings::~XynergySettings() {

}