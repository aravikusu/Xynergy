#ifndef APP_H
#define APP_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <Utils/enums.h>
#include <Classes/Texture/texture.h>

class App {
public:
	// The icon. Use the Texture::loadImage() function.
	Texture icon;

	// The name. Use the Texture::loadText() function.
	Texture name;

	// Determines the expected logic when you click on it.
	Xynergy_AppType appType;

	// If false it won't appear on the dashboard.
	// Coordinates will also be ignored.
	bool showOnDashboard;
	SDL_Rect coordinates;
};

#endif