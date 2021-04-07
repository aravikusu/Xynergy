#ifndef TASKBAR_H
#define TASKBAR_H

#include <string>
#include <list>
#include <SDL.h>
#include <Classes/App/app.h>
#include <Classes/Texture/texture.h>


class Taskbar {
public:
	Taskbar();
	~Taskbar();
private:
	Texture taskbarTexture;
};

#endif