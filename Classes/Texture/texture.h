#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/// <summary>
/// The class name is pretty self-explanatory.
/// <para>Lets you create a texture and give you plenty of helper functions to modify it.</para>
/// <para>It can load both images and text so be sure to use the right functions.</para>
/// </summary>
class Texture {
public:
	Texture();
	~Texture();
	bool loadFile(std::string path, SDL_Renderer* ren);
	bool loadText(std::string text, SDL_Color textColor, TTF_Font* font, int fontSize, SDL_Renderer* ren);
	void kill();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blend);
	void setAlpha(Uint8 alpha);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif