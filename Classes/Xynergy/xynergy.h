#ifndef XYNERGY_H
#define XYNERGY_H

#include <string>
#include <SDL.h>
#include <Classes/Xynergy/xynergysettings.h>
#include <Utils/enums.h>

/// <summary> 
/// The main Xynergy class. It handles everything related to the game loop and window.
/// <para>While I've tried hard to ensure that it's easy to edit things... unless you know what you're doing you're better off not touching this.</para> 
/// </summary> 
class Xynergy {
public:
	Xynergy();
	~Xynergy();
	XynergySettings settings;
	bool init();
	void loop();
	void update();
	void render();
	void input();
private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	bool running;
	int frameCount, timerFPS, lastFrame;
	Xynergy_GameState currentState;
};

#endif 