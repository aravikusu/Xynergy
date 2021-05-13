#include "texture.h"

bool Texture::loadFile(std::string path, SDL_Renderer* ren) {
	kill();

	SDL_Texture* newTexture = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		std::cout << "Texture::loadFile: " << XynergyHelper::console::error() << " unable to load " << path << "! SDL_Image error: " << IMG_GetError() << "\n";
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(ren, surface);

		if (newTexture == NULL) {
			std::cout << "Texture::loadFile: " << XynergyHelper::console::error() << " unable to create texture from " << path << "! SDL error: " << SDL_GetError() << "\n";
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

bool Texture::loadText(std::string text, SDL_Color textColor, TTF_Font* font, int fontSize, SDL_Renderer* ren, bool wrap, Uint32 wrapLength) {
	kill();

	SDL_Surface* surface;
	if (wrap) {
		surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), textColor, wrapLength);
	}
	else {
		surface = TTF_RenderText_Blended(font, text.c_str(), textColor);
	}

	if (surface == NULL) {
		std::cout << "Texture::loadText: " << XynergyHelper::console::error() << " unable to render text! SDL_TTF error: " << TTF_GetError() << "\n";
	}
	else {
		texture = SDL_CreateTextureFromSurface(ren, surface);

		if (texture == NULL) {
			std::cout << "Texture::loadText: " << XynergyHelper::console::error() << " unable to create texture from text! SDL error: " << SDL_GetError() << "\n";
		}
		else {
			width = surface->w;
			height = surface->h;
		}

		SDL_FreeSurface(surface);
	}

	return texture != NULL;
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_SetTextureColorMod(texture, red, blue, green);
}

void Texture::setBlendMode(SDL_BlendMode blend) {
	SDL_SetTextureBlendMode(texture, blend);
}

void Texture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(texture, alpha);
}

int Texture::getWidth() {
	return width;
}

int Texture::getHeight() {
	return height;
}

void Texture::render(int x, int y, SDL_Renderer* ren, SDL_Rect* clip, SDL_Rect* viewport, double angle, SDL_Point* center, SDL_RendererFlip flip) {

	if (viewport != NULL) {
		SDL_RenderSetViewport(ren, viewport);
		SDL_RenderCopyEx(ren, texture, clip, NULL, angle, center, flip);
	}
	else {
		SDL_Rect quad = { x, y, width, height };

		if (clip != NULL) {
			quad.w = clip->w;
			quad.h = clip->h;
		}

		SDL_RenderCopyEx(ren, texture, clip, &quad, angle, center, flip);
	}
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