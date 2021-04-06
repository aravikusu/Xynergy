#include "texture.h"

/// <summary>
/// Takes an image and creates a texture from it.
/// </summary>
/// <param name="path">Path to the file.</param>
/// <param name="ren">The Xynergy renderer.</param>
/// <returns>True or false if the texture was successfully created or not.</returns>
bool Texture::loadFile(std::string path, SDL_Renderer* ren) {
	kill();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		printf("Texture::loadFile: Unable to load %s! SDL_Image error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(ren, surface);

		if (newTexture == NULL) {
			printf("Texture::loadFile: Unable to create texture from %s! SDL error: %s\n", path.c_str(), SDL_GetError());
		}
		else {
			width = surface->w;
			height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	texture = newTexture;
	return texture != NULL;
}

/// <summary>
/// Creates a texture based on the font and text sent in.
/// </summary>
/// <param name="text">The text you want to display.</param>
/// <param name="textColor">An SDL_Color. Make your text beautiful.</param>
/// <param name="font">The font you wish to use.</param>
/// <param name="fontSize">Do you prefer it bigger or smaller?</param>
/// <param name="ren">The Xynergy renderer.</param>
/// <returns>True or false if the texture was successfully created or not.</returns>
bool Texture::loadText(std::string text, SDL_Color textColor, TTF_Font* font, int fontSize, SDL_Renderer* ren) {
	kill();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font,text.c_str(), textColor);

	return texture != NULL;
}

/// <summary>
/// Give your image a nice tint of color.
/// </summary>
void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, blue, green);
}

/// <summary>
/// Sets the SDL_BlendMode used when rendering the texture.
/// </summary>
/// <param name="blend"></param>
void Texture::setBlendMode(SDL_BlendMode blend) {
	SDL_SetTextureBlendMode(texture, blend);
}

/// <summary>
/// Do you want it to be transparent? 
/// </summary>
/// <param name="alpha"></param>
void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

/// <summary>
/// Kill it with fire!
/// <para>Might also just flush the texture, freeing it from memory.</para>
/// </summary>
void Texture::kill() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		width = 0;
		height = 0;
	}
}

Texture::Texture() {
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture() {
	kill();
}