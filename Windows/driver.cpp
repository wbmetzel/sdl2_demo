/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include "Texture.h"
#include "Character.h"
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 480;

char* BACKGROUNDS[] = {"Resources/mario_background2.png"};

// // // // // // // // // // // // // // // // // // // //

const int FRAMES = 6;
const int WALKING_ANIMATION_FRAMES = FRAMES;

bool init(SDL_Window *&window, SDL_Renderer *&renderer);
bool loadLevel(Texture &background,Character &character, SDL_Renderer *&renderer);
void close(SDL_Window *&window, SDL_Renderer *&renderer);


//Walking animation

SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
SDL_Rect spriteIdle[4];
//Texture gSpriteSheetTexture;


int main( int argc, char* args[] )
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    Texture backgroundTexture;
    Character stimpy;

	//Start up SDL and create window
	if( !init(window,renderer) )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadLevel(backgroundTexture, stimpy, renderer) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;
            int idleCounter = 0;
            int walk_frame = 0;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//gSpriteSheetTexture.handleEvent(e);
				}

				//gSpriteSheetTexture.movement();

                  // Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );

				backgroundTexture.render(0,0,renderer,NULL);

                SDL_Rect *currentClip = &spriteIdle[frame / 4];

				stimpy.render( currentClip->w - 30, SCREEN_HEIGHT - (currentClip->h * 2) - 10, renderer, currentClip );

                  // Render to screen
                SDL_RenderPresent( renderer );
				idleCounter++;

				if(idleCounter > 20)
                {
                    ++frame;
                    idleCounter = 19;
                }

				if(frame / 4 >= 4)
                {
                    frame = 0;
                    idleCounter = 0;
                }


/*
                SDL_Rect* currentClip = &gSpriteClips[ frame / FRAMES ];

                gSpriteSheetTexture.render(currentClip );

				//Update screen
                SDL_RenderPresent( renderer );

				//Go to next frame
				++frame;

				//Cycle animation
				if( frame / FRAMES >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}

*/




			}
		}
	}

	//Free resources and close SDL
	close(window,renderer);

	return 0;
}


bool init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if(SDL_Init( SDL_INIT_VIDEO ) >= 0)
	{
		  // Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_Log( "Warning: Linear texture filtering not enabled!" );
		}

		window = SDL_CreateWindow( "Stimpy's Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window != NULL)
		{
			  // Create v-synced renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer != NULL )
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				//int imgFlags = IMG_INIT_PNG;
				if(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
				{
					return true;
				}
			}
		}
	}

	return false;
}


bool loadLevel(Texture &background, Character &character, SDL_Renderer *&renderer)
{
    if(!background.loadPNG(BACKGROUNDS[0], renderer))
    {
        return false;
    }

    if(character.loadPNG("Resources/stimpy.png", renderer, 0x65, 0x8D, 0xD1))
    {
          // Sprite idle clips
	    spriteIdle[ 0 ].x =   2;
		spriteIdle[ 0 ].y =  28;
		spriteIdle[ 0 ].w =  39;
		spriteIdle[ 0 ].h =  52;

		spriteIdle[ 1 ].x =  41;
		spriteIdle[ 1 ].y =  28;
		spriteIdle[ 1 ].w =  39;
		spriteIdle[ 1 ].h =  52;

		spriteIdle[ 2 ].x =  80;
		spriteIdle[ 2 ].y =  28;
		spriteIdle[ 2 ].w =  39;
		spriteIdle[ 2 ].h =  52;

		spriteIdle[ 3 ].x =  41;
		spriteIdle[ 3 ].y =  28;
		spriteIdle[ 3 ].w =  39;
		spriteIdle[ 3 ].h =  52;
    }
    else
    {
        return false;
    }
    return true;
}
    /*
	if(!gBackgroundTexture.loadFromFile("Resources/mario_background2.png"))
	{
		printf( "Failed to load Background texture!\n" );
		return false;
	}

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "Resources/stimpy.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}
	else
	{
	    // Sprite idle clips
	    spriteIdle[ 0 ].x =   2;
		spriteIdle[ 0 ].y =  28;
		spriteIdle[ 0 ].w =  39;
		spriteIdle[ 0 ].h =  52;

		spriteIdle[ 1 ].x =  41;
		spriteIdle[ 1 ].y =  28;
		spriteIdle[ 1 ].w =  39;
		spriteIdle[ 1 ].h =  52;

		spriteIdle[ 2 ].x =  80;
		spriteIdle[ 2 ].y =  28;
		spriteIdle[ 2 ].w =  39;
		spriteIdle[ 2 ].h =  52;

		spriteIdle[ 3 ].x =  41;
		spriteIdle[ 3 ].y =  28;
		spriteIdle[ 3 ].w =  39;
		spriteIdle[ 3 ].h =  52;


		//Set sprite clips for walking
		gSpriteClips[ 0 ].x =   2;
		gSpriteClips[ 0 ].y = 104;
		gSpriteClips[ 0 ].w =  39;
		gSpriteClips[ 0 ].h =  52;

		gSpriteClips[ 1 ].x =  41;
		gSpriteClips[ 1 ].y = 104;
		gSpriteClips[ 1 ].w =  39;
		gSpriteClips[ 1 ].h =  52;

		gSpriteClips[ 2 ].x =  80;
		gSpriteClips[ 2 ].y = 104;
		gSpriteClips[ 2 ].w =  39;
		gSpriteClips[ 2 ].h =  52;

		gSpriteClips[ 3 ].x = 118;
		gSpriteClips[ 3 ].y = 104;
		gSpriteClips[ 3 ].w =  39;
		gSpriteClips[ 3 ].h =  52;

		gSpriteClips[ 4 ].x = 157;
		gSpriteClips[ 4 ].y = 104;
		gSpriteClips[ 4 ].w =  39;
		gSpriteClips[ 4 ].h =  52;

        gSpriteClips[ 5 ].x = 196;
		gSpriteClips[ 5 ].y = 104;
		gSpriteClips[ 5 ].w =  39;
		gSpriteClips[ 5 ].h =  52;
	}

	return false;
}
*/


void close(SDL_Window *&window, SDL_Renderer *&renderer)
{
	//Free loaded images
	//gSpriteSheetTexture.free();

	SDL_DestroyRenderer( renderer );
	renderer = NULL;

	SDL_DestroyWindow( window );
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
