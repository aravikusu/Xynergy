#include "usericon.h"

void UserIcon::setCoordinates(int x, int y) {
	coordinates.x = x;
	coordinates.y = y;
}

void UserIcon::setIconName(std::string name) {
	iconName = name;
}

void UserIcon::setNames(std::string usrName, std::string dsplName) {
	username = usrName;
	displayName = dsplName;
}

void UserIcon::setupTextures(SDL_Renderer* ren, TTF_Font* font, SDL_Color fontColor) {
	if (iconTexture.getWidth() == 0) {
		iconTexture.loadFile("Materials/textures/usericons/" + iconName, ren);
		iconTexture.setBlendMode(SDL_BLENDMODE_BLEND);
		iconTexture.setAlpha(175);
		nameTexture.loadText(displayName, fontColor, font, 18, ren);
	}
}

std::string UserIcon::getDisplayName() {
	return displayName;
}
std::string UserIcon::getUsername() {
	return username;
}

void UserIcon::render(SDL_Renderer* ren) {
	iconTexture.render(coordinates.x, coordinates.y, ren);
	nameTexture.render(((iconTexture.getWidth() - nameTexture.getWidth()) / 2) + coordinates.x, (coordinates.y + 115), ren);
}

void UserIcon::handleMotionEvent(SDL_MouseMotionEvent& e) {
	if (e.type == SDL_MOUSEMOTION) {
		bool inside = XynergyHelper::event_helper::checkInside(e.x, e.y, iconTexture.getWidth(), iconTexture.getHeight(), coordinates);

		if (inside) {
			iconTexture.setAlpha(255);
		}
		else {
			if (!selected) {
				iconTexture.setAlpha(175);
			}
		}
	}
}

void UserIcon::handleClickEvent(SDL_MouseButtonEvent& e) {
	if (e.button == SDL_BUTTON_LEFT) {
		bool inside = XynergyHelper::event_helper::checkInside(e.x, e.y, iconTexture.getWidth(), iconTexture.getHeight(), coordinates);

		if (inside) {
			selected = true;
		}
		else {
			selected = false;
		}
	}
}

UserIcon::UserIcon() {
	coordinates.x = 0;
	coordinates.y = 0;
	selected = false;
}