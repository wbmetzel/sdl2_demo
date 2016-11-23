
#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Controls
{
	public:
        Controls();
        ~Controls();
        bool eventStatus();
        bool exitGame();
    protected:
        SDL_Event e;
};

#endif
