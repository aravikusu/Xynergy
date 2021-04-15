#include "taskbar.h"

void Taskbar::renderTaskbar(SDL_Renderer* ren, int windowWidth, int windowHeight) {
	SDL_Rect viewport;
	viewport.w = windowWidth;
	viewport.h = height;

	// The taskbar itself
	switch (mode)
	{
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN:
		switch (orientation)
		{
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_TOP:
			taskbarTexture.render(0, (0 + height), ren);
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_RIGHT:
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_BOTTOM:
			viewport.x = 0;
			viewport.y = windowHeight - height;
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_LEFT:
			break;
		}
		break;
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_X:
		break;
	case Xynergy_TaskbarMode::XYNERGY_TASKBAR_CUSTOM:
		break;
	}
	taskbarTexture.renderViewport(ren, &viewport);

	// The button
	if (mode == Xynergy_TaskbarMode::XYNERGY_TASKBAR_WIN) {
		viewport.h = windowHeight;
		viewport.x, viewport.y = 0;
		int buttonHeight = button.getHeight();
		SDL_RenderSetViewport(ren, &viewport);
		switch (orientation)
		{
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_TOP:
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_RIGHT:
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_BOTTOM:
			button.render(0, (windowHeight - (buttonHeight - 5)), ren);
			break;
		case Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_LEFT:
			break;
		default:
			break;
		}
	}

}

void Taskbar::setupTaskbar(SDL_Renderer* ren) {
	// TODO: check UserSettings or default things
	taskbarTexture.loadFile("Materials/textures/taskbar/xyn-taskbar-plum.png", ren);
	button.loadFile("Materials/textures/taskbar/xynergy-taskbar-button.png", ren);
	height = taskbarTexture.getHeight();
}

Taskbar::Taskbar() {
	// TODO: check UserSettings
	orientation = Xynergy_TaskBarOrientation::XYNERGY_TASKBAR_BOTTOM;
	height = 0;
}

Taskbar::~Taskbar() {
	taskbarTexture.kill();
	button.kill();
	height = 0;
}