#ifndef APP_H
#define APP_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Utils/enums.h>
#include <Classes/Texture/texture.h>

/// <summary>
/// App serves a double-purpose.
/// <para>The main one being a more advanced Button class that shows up as an icon on the Dashboard,</para>
/// <para>the other being a list in the Taskbar.</para>
/// </summary>
class App {
public:
	App();
	~App();

	/// <summary>
	/// Create your app. Show it some love.
	/// </summary>
	/// <param name="iconName">The name of your icon in the icon folder. Example: "icon.png"</param>
	/// <param name="font">If the font is NULL it will default to Roboto. But try to send in a font as it's less efficient for the code to constantly create new ones.</param>
	void setupApp(std::string iconName, std::string appName, SDL_Color textColor,
		TTF_Font* font, SDL_Renderer* ren);

	void render(SDL_Renderer* ren);

	/// <summary>
	/// Determines the expected logic when you click on it.
	/// </summary>
	void setAppType(Xynergy_AppType type);

	/// <summary>
	/// The app defaults to show. Use this if you want to hide/show an app.
	/// </summary>
	void toggleShow();

	void setCoordinates(int x, int y);
private:
	// The icon. Use the Texture::loadImage() function.
	Texture icon;

	// The name. Use the Texture::loadText() function.
	Texture name;

	// Determines the expected logic when you click on it.
	Xynergy_AppType appType;

	// If false it won't appear on the dashboard.
	// Coordinates will also be ignored.
	bool showOnDashboard = true;
	int appX, appY;
};

#endif