#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Utils/libs/ini.h>
#include <Classes/Texture/texture.h>
#include <Classes/UserIcon/usericon.h>
#include <Classes/Timer/timer.h>
//#include <Classes/Button/Button>

//#if defined(_WIN32)
//#include <Windows.h>
//#endif

/// <summary>
/// The 2nd GameState - the Login screen.
/// </summary>
class Login {
public:
	Login();

	void setupLogin(SDL_Renderer* ren, std::string lastTheme);

	void clear();

	void renderLogin(SDL_Renderer* ren, int windowHeight, int windowWidth, std::string lastTheme);

	void handleEvents(SDL_Event e);

	// This is the user that we're logging in.
	std::string authedUser;
	bool loginComplete;
private:
	TTF_Font* loginFont;
	Texture border;
	Texture headerText;

	std::vector<UserIcon> userList;
	std::string selectedUser;
	Timer timeOut;
};
#endif