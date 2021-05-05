#ifndef TIMER_H
#define TIMER_H

#include <string>
#include <SDL.h>

class Timer {
public:
	Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    Uint32 getTicks();

    //Checks the status of the timer
    bool isStarted();
    bool isPaused();

private:
    Uint32 startTicks;

    Uint32 pausedTicks;

    bool paused;
    bool started;
};

#endif