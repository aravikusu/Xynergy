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

	//Takes an image and creates a texture out of it.
	bool loadFile(std::string path, SDL_Renderer* ren);

	//Creates a texture based on the font and text sent in.
	bool loadText(std::string text, SDL_Color textColor, TTF_Font* font, int fontSize, SDL_Renderer* ren);

	// Simply renders your texture at the coordinates you shoot in.
	void render(int x, int y, SDL_Renderer* ren, SDL_Rect* clip = NULL);

	// Render a texture while setting a specific viewport for it.
	void renderViewport(SDL_Renderer* ren, SDL_Rect* viewport);

	// Free texture from memory.
	void kill();

	// Color.
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	// Blend mode.
	void setBlendMode(SDL_BlendMode blend);

	// Transparency.
	void setAlpha(Uint8 alpha);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* texture;
	int width;
	int height;
};

#endif