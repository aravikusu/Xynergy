#ifndef APP_H
#define APP_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Utils/enums.h>
#include <Classes/Texture/texture.h>

/// <summary>
/// App is one of the more complex classes.
/// <para>It deals with all logic relating to apps - what to render, expected logic, etc.</para>
/// <para>It's used as a component in DashboardIcon, TaskbarTrayItem, and TaskbarListItem.</para>
/// </summary>
class App {
public:
	App();

	/// <summary>
	/// Create your app. Show it some love.
	/// </summary>
	/// <param name="name">Simply the display name to be used everywhere for the app.</param>
	/// <param name="appType">The wanted behavior when the app is launched.</param>
	/// <param name="description">Optional flavor text for your app. Shown in the AppList in the Finder.</param>
	void setupApp(std::string appName, Xynergy_AppType type, std::string appDescription = "");

	std::string getName();
	std::string getDescription();
	Xynergy_AppType getAppType();
private:
	std::string name;
	std::string description;

	// Determines the expected logic when you click on it.
	Xynergy_AppType appType;
};

#endif