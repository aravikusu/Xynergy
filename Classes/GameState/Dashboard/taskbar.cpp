#include "taskbar.h"

void Taskbar::renderTaskbar(SDL_Renderer* ren, int windowWidth, int windowHeight) {
	SDL_Rect viewport;
	if (mode == Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN && 
	   (orientation == Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP || orientation == Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM)) {
		viewport.w = windowWidth;
		viewport.h = height;
	}
	else {
		viewport.w = width;
		viewport.h = windowHeight;
	}
	double angle = 0.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	// The taskbar itself
	switch (mode)
	{
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN:
		switch (orientation)
		{
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP:
			viewport.x = 0;
			viewport.y = 0;
			flip = SDL_FLIP_VERTICAL;
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT:
			viewport.x = windowWidth - width;
			viewport.y = 0;
			flip = SDL_FLIP_HORIZONTAL;
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM:
			viewport.x = 0;
			viewport.y = windowHeight - height;
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT:
			viewport.x = 0;
			viewport.y = 0;
			flip = SDL_FLIP_HORIZONTAL;
			break;
		}
		break;
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_X:
		break;
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_CUSTOM:
		break;
	}
	taskbarTexture.render(0, 0, ren, NULL, &viewport, angle, NULL, flip);

	// The button
	if (mode == Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN) {
		int buttonHeight = button.getHeight();
		SDL_RenderSetViewport(ren, NULL);
		switch (orientation)
		{
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_TOP:
			button.render(0, -7, ren);
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_RIGHT:
			button.render((windowWidth - (buttonHeight - 7)), 0, ren);
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM:
			button.render(0, (windowHeight - (buttonHeight - 5)), ren);
			break;
		case Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_LEFT:
			button.render(-5, 1, ren);
			break;
		default:
			break;
		}
	}

}

void Taskbar::setupTaskbar(SDL_Renderer* ren, UserSettings currentUser) {
	orientation = currentUser.curentOrientation;
	taskbarTexture.loadFile("Materials/textures/themes/" + currentUser.currentTheme + "/taskbar.png", ren);
	button.loadFile("Materials/textures/themes/" + currentUser.currentTheme + "/taskbar-button.png", ren);
	height = taskbarTexture.getHeight();
	width = taskbarTexture.getWidth();
}

Taskbar::Taskbar() {
	orientation = Xynergy_TaskbarOrientation::XYNERGY_TASKBAR_BOTTOM;
	height = 0;
	width = 0;
}

Taskbar::~Taskbar() {
	taskbarTexture.kill();
	button.kill();
	height = 0;
}