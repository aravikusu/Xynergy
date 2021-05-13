#include "login.h"

void Login::setupLogin(SDL_Renderer* ren, std::string lastTheme) {
	border.loadFile("Materials/textures/themes/" + lastTheme + "/login-border.png", ren);
	SDL_Color color{ 0, 0, 0 };

	TTF_CloseFont(loginFont);
	loginFont = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 18);

	// The "users" folder is where all UserSettings are saved.
	for (const auto& file : std::filesystem::directory_iterator("./users/")) {
		std::string fileString = file.path().string();

		// We have to do a couple of checks to make sure this is in fact a Xynergy UserSettings file.
		if (fileString.std::string::find(".ini") != std::string::npos) {

			mINI::INIFile settingsFile(fileString);
			mINI::INIStructure ini;

			settingsFile.read(ini);
			// Check for the warning at the top.
			if (ini.has("WARNING!")) {
				if (ini.has("user_related")) {
					std::string name = ini.get("user_related").get("name");
					std::string displayName = ini.get("user_related").get("displayName");
					std::string icon = ini.get("user_related").get("icon");

					UserIcon i;
					userList.push_back(i);
					
					userList.back().setIconName(icon);
					userList.back().setNames(name, displayName);
				}
			}
		}
	}
}

void Login::renderLogin(SDL_Renderer* ren, int windowHeight, int windowWidth, std::string lastTheme) {
	SDL_Rect viewport;
	viewport.w = windowWidth;
	viewport.h = border.getHeight();
	viewport.x = 0;
	viewport.y = 0;

	if (lastTheme == "plum") {
		SDL_SetRenderDrawColor(ren, 149, 46, 191, 255);
	}
	else if (lastTheme == "grass") {

	}
	else {

	}
	SDL_RenderFillRect(ren, NULL);

	border.render(0, 0, ren, NULL, &viewport);
	viewport.y = (windowHeight - border.getHeight());
	border.render(0, (windowHeight - border.getHeight()), ren, NULL, &viewport, 0, NULL, SDL_FLIP_VERTICAL);

	SDL_RenderSetViewport(ren, NULL);

	bool anyUserSelected = false;
	auto it = std::find_if(std::begin(userList), std::end(userList), [&](const UserIcon& uIcon) {return uIcon.selected;});

	if (it != userList.end()) {
		anyUserSelected = true;
	}

	// We need to render different things if something is actually selected.
	if (anyUserSelected) {
		if (authedUser != "" && !timeOut.isStarted()) {
			timeOut.start();
		}
		for (auto& icon : userList) {
			if (icon.selected) {
				selectedUser = icon.getUsername();
				if (TTF_FontHeight(loginFont) != 26) {
					TTF_CloseFont(loginFont);
					loginFont = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 26);
					headerText.loadText("Welcome, " + icon.getDisplayName() + "!", { 0, 0, 0 }, loginFont, 26, ren);
				}
				headerText.render((windowWidth - headerText.getWidth()) / 2, (border.getHeight() - 20), ren);

				icon.setCoordinates((windowWidth - (112 + 10)) / 2, border.getHeight() + 50);
				icon.setupTextures(ren, loginFont, { 0, 0, 0 });
				icon.render(ren);

				// TODO: Check if user is password protected, show password prompt if so.
				// For now, just auth the user immediately
				authedUser = selectedUser;
			}
		}

		if (timeOut.isStarted()) {
			float seconds = (timeOut.getTicks() / 1000.f);

			if (seconds > 1.5) {
				loginComplete = true;
				timeOut.stop();
			}
		}
	}
	else {
		selectedUser = "";
		if (TTF_FontHeight(loginFont) != 26) {
			TTF_CloseFont(loginFont);
			loginFont = TTF_OpenFont("Materials/fonts/Roboto-Regular.ttf", 26);
			headerText.loadText("Who is using Xynergy today?", { 0, 0, 0 }, loginFont, 26, ren);
		}
		headerText.render((windowWidth - headerText.getWidth()) / 2, (border.getHeight() - 20), ren);

		// We need to render each user next to each other, so we get the total width of the entire thing before anything.
		int userDimensions = (windowWidth - ((112 + 10) * userList.size())) / 2;
		SDL_Color color{ 0, 0, 0 };
		for (auto& icon : userList) {
			icon.setCoordinates(userDimensions, border.getHeight() + 50);
			icon.setupTextures(ren, loginFont, color);
			icon.render(ren);
			userDimensions += 132;
		}
	}
}

void Login::handleEvents(SDL_Event e) {
	switch (e.type)
	{
	case SDL_MOUSEMOTION:
		for (auto& icon : userList) {
			icon.handleMotionEvent(e.motion);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		for (auto& icon : userList) {
			icon.handleClickEvent(e.button);
		}
		break;
	}
}

void Login::clear() {
	border.kill();
	headerText.kill();
	userList.clear();
	loginComplete = false;
	authedUser = "";

}

Login::Login() {
	loginFont = NULL;
	loginComplete = false;
}