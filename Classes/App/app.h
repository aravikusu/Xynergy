#ifndef APP_H
#define APP_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <Utils/enums.h>

class App {
public:
	App();
	~App();
	SDL_Texture* icon;
	std::string name;
	Xynergy_AppType appType;
	std::pair<int, int> coordinates;
private:

};

#endif