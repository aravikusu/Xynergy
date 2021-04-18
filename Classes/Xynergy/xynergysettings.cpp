#include "xynergysettings.h";

bool XynergySettings::getDebug() {
	return debug;
}

int XynergySettings::getWidth() {
	return width;
}

int XynergySettings::getHeight() {
	return height;
}

Xynergy_WindowMode XynergySettings::getWindowMode() {
	return windowMode;
}


template<typename T>
bool XynergySettings::saveSetting(Xynergy_SettingsType type, T value) {
	if constexpr (std::is_same_v<std::decay_t<T>, int>) {

	}
	else if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {

	}
	else if constexpr (std::is_same_v<std::decay_t<T>, Xynergy_WindowMode>) {

	}
	else {
		printf("XynergySettings::saveSetting: %s Setting not saved. saveSetting() can only take int, string, or enum class Xynergy_SettingsType.\n", "\033[0;31mError!\033[0;37m");
		return false;
	}
	return true;
}

void XynergySettings::setExisting(mINI::INIFile file, mINI::INIStructure ini) {
	std::istringstream(ini.get("scary_skeletons").get("debug")) >> debug;
	width = std::stoi(ini.get("main_window").get("width"));
	height = std::stoi(ini.get("main_window").get("height"));

	int window = std::stoi(ini.get("main_window").get("windowmode"));

	windowMode = static_cast<Xynergy_WindowMode>(window);

	file.~INIFile();
}

/// <summary>
/// Runs if settings.ini wasn't found. Simply creates it and defaults settings.
/// </summary>
void XynergySettings::setDefault(mINI::INIFile file, mINI::INIStructure ini) {
	ini["scary_skeletons"].set({
		{"debug", "0"}
	});
	ini["main_window"].set({
		{"width", "1280"},
		{"height", "720"},
		{"windowmode", "0"}
	});

	debug = false;
	width = 1280;
	height = 720;
	windowMode = Xynergy_WindowMode::XYNERGY_WINDOW;

	if (file.write(ini)) {
		printf("XynergySettings::setDefault: %s settings.ini was successfully created!\n", "\033[0;32mSuccess!\033[0;37m");
	}
	else {
		printf("XynergySettings::setDefault: %s settings.ini could not be created! Is the syntax right?\n", "\033[0;31mError!\033[0;37m");
	}
}

XynergySettings::XynergySettings() {
	mINI::INIFile file("settings.ini");
	mINI::INIStructure ini;

	if (file.read(ini)) {
		printf("XynergySettings: %s settings.ini found!\n", "\033[0;32mSuccess!\033[0;37m");
		setExisting(file, ini);
	}
	else {
		printf("XynergySettings: %s settings.ini was not found! Creating and defaulting settings.\n", "\033[0;33mWarning!\033[0;37m");
		setDefault(file, ini);
	}

	file.~INIFile();
}

XynergySettings::~XynergySettings() {
	mINI::INIFile file("settings.ini");
	mINI::INIStructure ini;

	// First check if some genius decided to trash the file while the game was running and call them out.
	bool dumbdumb = false;

	if (!file.read(ini)) {
		printf("XynergySettings: %s Did you remove settings.ini? Why?\n", "\033[0;36mQuestion:\033[0;37m");
		dumbdumb = true;
	}

	// TODO: actually saving the data...
	int window = 0;
	if (windowMode == Xynergy_WindowMode::XYNERGY_BORDERLESS) {
		window = 1;
	}
	else if (windowMode == Xynergy_WindowMode::XYNERGY_FULLSCREEN) {
		window = 2;
	}

	ini["scary_skeletons"].set({
		{"debug", std::to_string(debug)}
		});
	ini["main_window"].set({
		{"width", std::to_string(width)},
		{"height", std::to_string(height)},
		{"windowmode", std::to_string(window)}
		});
	
	if (file.write(ini)) {
		if (dumbdumb) {
			printf("XynergySettings: %s settings.ini has been recreated. Can we just... not remove it in the future?\n", "\033[0;32mSuccess!\033[0;37m");
		}
		else {
			printf("XynergySettings: %s Settings have been stored in settings.ini!\n", "\033[0;32mSuccess!\033[0;37m");
		}
	}
	else {
		printf("XynergySettings::setDefault: %s Couldn't write to settings.ini! Setings were not saved.\n", "\033[0;31mError!\033[0;37m");
	}

	file.~INIFile();
}