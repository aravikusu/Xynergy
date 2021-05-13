#ifndef BOOT_H
#define BOOT_H

#include <string>
#include <stdio.h>
#include <array>
#include <vector>
#include <sstream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Classes/Texture/texture.h>
#include <Classes/Timer/timer.h>

#if defined(_WIN32)
#include <Windows.h>
#include <SetupAPI.h>
#include <sysinfoapi.h>
#pragma comment(lib, "Setupapi.lib")
#endif

/// <summary>
/// The Boot GameState is the most simple one. It's just a short animation that plays when you start the game.
/// <para>It gets its own class for consistency and cleaner code.</para>
/// </summary>
class Boot {
public:
	Boot();
	~Boot();

	void setupBoot(SDL_Renderer* ren);

	void renderBootAnimation(SDL_Renderer* ren, int windowWidth, int windowHeight);
	void animationPart1(SDL_Renderer* ren, int logoX);
	void animationPart2(SDL_Renderer* ren, int windowWidth, int windowHeight);
	void clear();

	void handleEvents(SDL_Event e);

	bool bootComplete;
private:
	std::string wmiQuery(const char* query);
	Texture logo;
	Texture text;
	Timer duration;
	TTF_Font* font;

	std::string cpuName;
	int cpuCores;
	int ramCount;
	int totalRAM;
	int ramIncrementer;
	bool memoryCheckOK;
	float memoryCheckClearTime;
	float logoAppeared;
	std::string storageInfo;
	int alphaIncrementer;

	int count;
	bool check1;
	bool check2;
};
#endif