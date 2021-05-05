#ifndef XYNERGY_H
#define XYNERGY_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Classes/Settings/xynergysettings.h>
#include <Classes/Settings/usersettings.h>
#include <Classes/GameState/Dashboard/dashboard.h>
#include <Classes/GameState/Boot/boot.h>
#include <Classes/Debug/debug.h>
#include <Utils/enums.h>

/// <summary> 
/// The main Xynergy class. It handles everything related to the game loop and window.
/// <para>While I've tried hard to ensure that it's easy to edit things... unless you know what you're doing you're better off
/// not touching this file in particular.</para> 
/// </summary> 
class Xynergy {
public:
	Xynergy();
	~Xynergy();
	XynergySettings settings;

	// Initializes SDL and all of its components.
	bool init();
	void setSDLHints();

	void changeGameState(Xynergy_GameState state);
	void clearGameState();

	// The main render function for the game loop.
	// GameState determines where we go.

	void loop();
	void update();
	void render();
	void input();
	void drawBoot();
	void drawLogin();
	void drawDashboard();
	void drawSetup();

	void toggleDebug();

	/// <summary>
	/// Renders debug-specific info to the screen.
	/// </summary>
	void drawDebug();
private:
	const char* windowName = "Xynergy";
	SDL_Renderer* renderer;
	SDL_Window* window;
	bool running;
	Uint32 lastFrame;
	int frameCount, timerFPS, fps;

	Xynergy_GameState currentState;
	Dashboard dashboard;
	Boot boot;
	UserSettings currentUser;
	Debug debug;
};

#endif 