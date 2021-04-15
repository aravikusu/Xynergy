#ifndef TASKBAR_H
#define TASKBAR_H

#include <string>
#include <list>
#include <SDL.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>
#include <Utils/enums.h>

/// <summary>
/// The Taskbar class is more of an extension to the Dashboard.
/// <para>All logic exclusive to the Taskbar is here.</para>
/// </summary>
class Taskbar {
public:
	Taskbar();
	~Taskbar();

	// This function is called immediately by the Dashboard.
	// Defaults values if no UserSettings can be found.
	void setupTaskbar(SDL_Renderer* ren);

	// Renders the Taskbar based on the mode/orientation.
	void renderTaskbar(SDL_Renderer* ren, int windowWidth, int windowHeight);
private:
	Texture taskbarTexture;
	Texture button;
	int height;

	// Determines If you want to have a Windows/OSX/Custom-themed taskbar.
	// Has to be manually set.
	Xynergy_TaskbarMode mode = Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN;

	// Where your taskbar will be rendered.
	// NOTE: will be ignored if TaskbarMode XYNERGY_TASKBAR_X is used.
	Xynergy_TaskBarOrientation orientation;
};

#endif