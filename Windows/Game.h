
#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Game
{
	public:
        Game();
        ~Game();
        bool initialize();
        bool initReady();
        void refresh();
    private:
        bool ready;
    protected:
        static const int SCREEN_WIDTH = 512;
        static const int SCREEN_HEIGHT = 480;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event e;
        //char* title;
        //Texture backgroundTexture;
        //Character stimpy;
};

#endif // __GAME_H__
//Screen dimension constants
/*

char* BACKGROUNDS[] = {"Resources/mario_background2.png"};

// // // // // // // // // // // // // // // // // // // //
const int WALKING_FRAMES = 6;

//Walking animation
SDL_Rect gSpriteClips[ WALKING_FRAMES ];
SDL_Rect spriteIdle[4];
*/
