
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <SDL_image.h>
#include "Controls.h"
//#include "Environment.h"
#include <stdio.h>

class Game
{
	public:
        Game();
        ~Game();
        bool initialize();
        void renderScreen();
        void refresh();
        bool eventHandler();
    protected:
        static const int SCREEN_WIDTH = 512;
        static const int SCREEN_HEIGHT = 480;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Controls *controller;
        //Environment *environment;
};

#endif // __GAME_H__
