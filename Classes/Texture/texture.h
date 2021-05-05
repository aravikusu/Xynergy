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
	bool loadText(std::string text, SDL_Color textColor, TTF_Font* font, int fontSize, SDL_Renderer* ren, bool wrap = false, Uint32 wrapLength = 45);

	/// <summary>
	/// The main render function. It's big, so makes sure you know how it works.
	/// </summary>
	/// <param name="x, y">The coordinates where you want to place your texture.</param>
	/// <param name="ren">The renderer.</param>
	/// <param name="clip">If you use a spritesheet you use this Rect to tell the function what to render.</param>
	/// <param name="viewport">If this isn't null your texture will be rendered in its own viewport.</param>
	/// <param name="angle">Rotate your texture a certain amount of degrees.</param>
	/// <param name="center"></param>
	/// <param name="flip">Vertifal, horizontal, or no flip.</param>
	void render(int x, int y, SDL_Renderer* ren, SDL_Rect* clip = NULL, SDL_Rect* viewport = NULL, double angle= 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

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