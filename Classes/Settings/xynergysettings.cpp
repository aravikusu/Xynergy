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

std::string XynergySettings::getLastTheme() {
	return lastTheme;
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
	lastTheme = (ini.get("looks").get("lasttheme"));

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
		{"windowmode", "0"},
	});
	ini["looks"].set({
		{"lasttheme", "plum"}
	});

	debug = false;
	width = 1280;
	height = 720;
	windowMode = Xynergy_WindowMode::XYNERGY_WINDOW;

	if (file.write(ini)) {
		std::cout << "XynergySettings::setDefault:" << XynergyHelper::console::success() << "settings.ini was successfully created!\n";
	}
	else {
		std::cout << "XynergySettings::setDefault:" << XynergyHelper::console::error() << "settings.ini could not be created!\n";
	}
}

XynergySettings::XynergySettings() {
	mINI::INIFile file("settings.ini");
	mINI::INIStructure ini;

	if (file.read(ini)) {
		std::cout << "XynergySettings:" << XynergyHelper::console::success() << "settings.ini was found!\n";
		setExisting(file, ini);
	}
	else {
		std::cout << "XynergySettings::setDefault:" << XynergyHelper::console::warning() << "settings.ini was not found! Creating and default settings.\n";
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
		std::cout << "XynergySettings:" << XynergyHelper::console::question() << "Did you remove settings.ini? Why?\n";

		dumbdumb = true;
	}

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
	ini["looks"].set({
		{"lasttheme", lastTheme}
		});
	
	if (file.write(ini)) {
		if (dumbdumb) {
			std::cout << "XynergySettings:" << XynergyHelper::console::success() << "settings.ini has been recreated. Can we just... not remove it in the future?\n";
		}
		else {
			std::cout << "XynergySettings:" << XynergyHelper::console::success() << "Settings have been stored in settings.ini!\n";
		}
	}
	else {
		std::cout << "XynergySettings:" << XynergyHelper::console::error() << "Couldn't write to settings.ini! Settings were not saved.\n";
	}

	file.~INIFile();
}