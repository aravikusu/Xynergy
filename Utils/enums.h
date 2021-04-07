#ifndef ENUMS_H
#define ENUMS_H

/// <summary>
/// Windowed, borderless, fullscreen.
/// </summary>
enum class Xynergy_WindowMode {
	XYNERGY_WINDOW = 0,
	XYNERGY_BORDERLESS = 1,
	XYNERGY_FULLSCREEN = 2
};

/// <summary>
/// All of the XynergySettings. Used in XynergySettings::fetchSettings().
/// </summary>
/// <param name="too many to list"></param>
enum class Xynergy_SettingsType {
	XYNERGY_HEIGHT = 0,
	XYNERGY_WIDTH = 1,
	XYNERGY_WINDOWMODE = 2
};

/// <summary>
/// Xynergy_GameState determines which screen we're currently rendering.
///</summary>
/// <param name="XYNERGY_BOOT">The initial boot-up sequence. Game always starts here.</param>
/// <param name="XYNERGY_LOGIN">The login screen. Can be toggled to always show or not in XynergySettings.</param>
/// <param name="XYNERGY_DASHBOARD">The dashboard, or desktop, if you will. The main game takes place here.</param>
/// <param name="XYNERGY_INITSETUP">The first-time installation. Only runs once.</param>
enum class Xynergy_GameState {
	XYNERGY_BOOT = 0,
	XYNERGY_LOGIN = 1,
	XYNERGY_DASHBOARD = 2,
	XYNERGY_INITSETUP = 99
};

/// <summary>
/// Used in the App class to determine which type of app it is. This will determine what behavior is expected from your app.
/// </summary>
/// <param name="far too many. Check the list."></param>
enum class Xynergy_AppType {
	XYNERGY_IMAGE = 0,
	XYNERGY_TEXT = 1
};

/// <summary>
/// Changes the mode of the wallpaper. XYNERGY_WALLPAPER_STRETCH is default.
/// </summary>
enum class Xynergy_WallpaperMode {
	XYNERGY_WALLPAPER_STRETCH = 0,
	XYNERGY_WALLPAPER_TILE = 1
};

/// <summary>
/// The mode of the taskbar in the Dashboard state.
/// </summary>
/// <param name="XYNERGY_TASKBARWIN">Makes the taskbar look and act like the one on Windows.</param>
/// <param name="XYNERGY_TASKBARX">Makes the taskbar look and act like the menu bar on MacOS/OSX.</param>
/// <param name="XYNERGY_TASKBARCUSTOM">This can be used in case you want to make your own unique taskbar. Note that it requires you to write all the code yourself.</param>
enum class Xynergy_TaskbarMode {
	XYNERGY_TASKBAR_WIN = 0,
	XYNERGY_TASKBAR_X = 1,
	XYNERGY_TASKBAR_CUSTOM = 2
};

/// <summary>
/// Determines on what side of the screen your taskbar will appear.
/// <para>Note that this setting is ignored if your taskbar uses XYNERGY_TASKBAR_X.</para>
/// </summary>
enum class Xynergy_TaskBarOrientation {
	XYNERGY_TASKBAR_TOP = 0,
	XYNERGY_TASKBAR_RIGHT = 1,
	XYNERGY_TASKBAR_BOTTOM = 2,
	XYNERGY_TASKBAR_LEFT = 3
};

#endif