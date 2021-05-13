#ifndef USERICON_H
#define USERICON_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Classes/Texture/texture.h>

/// <summary>
/// Works as a button. Used on the Login screen and in a few places across the Dashboard.
/// </summary>
class UserIcon {
public:
	UserIcon();

	void handleMotionEvent(SDL_MouseMotionEvent& e);
	void handleClickEvent(SDL_MouseButtonEvent& e);
	void setCoordinates(int x, int y);
	void setIconName(std::string name);
	void setNames(std::string usrName, std::string dsplName);
	void setupTextures(SDL_Renderer* ren, TTF_Font* font, SDL_Color fontColor);
	void render(SDL_Renderer* ren);

	std::string getDisplayName();
	std::string getUsername();

	bool selected;
private:
	bool checkInside(int eventX, int eventY);

	// This is mostly here for compatability during login.
	std::string username;

	// If icon is NULL a default image will be used.
	std::string iconName;
	Texture iconTexture;

	// If displayName is NULL it simply won't display.
	std::string displayName;
	Texture nameTexture;
	
	// Simply where it should appear.
	SDL_Point coordinates;
};
#endif