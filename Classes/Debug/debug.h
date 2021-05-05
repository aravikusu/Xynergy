#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <sstream>
#include <Classes/Texture/texture.h>

/// <summary>
/// The class name is pretty self-explanatory.
/// <para>Lets you create a texture and give you plenty of helper functions to modify it.</para>
/// <para>It can load both images and text so be sure to use the right functions.</para>
/// </summary>
class Debug {
public:
	Debug();
	~Debug();

	/// <summary>
	/// Sets up the debug menu. Gets called when debug mode is toggled on.
	/// </summary>
	/// <param name="name">The name that will appear at the top. Font will be bolder, and bigger.</param>
	/// <param name="fluff">Version fluff. Example: "Private use only. Xynergy Evaluation Build 0001"</param>
	void setupDebug(std::string fontName, std::string name, std::string fluff, SDL_Renderer* ren);

	bool getSetup();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="fps">FPS has to be sent in here due to it changing every frame.</param>
	void render(int fps, int windowWidth, int windowHeight, SDL_Renderer* ren);
private:
	bool isSetup;
	int longestWidth;
	TTF_Font* debugFont;
	Texture nameTexture;
	Texture versionFluffTexture;
	Texture fpsTexture;

	std::stringstream fpsText;
};

#endif