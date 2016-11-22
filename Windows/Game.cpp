
#include "Game.h"


/***************************************
*
* F(x): Constructor
* Date: 22 Nov 2016
* Description: Initialize instance
*
***************************************/
Game::Game()
{
    this->window = NULL;
    this->renderer = NULL;
}


/***************************************
*
* F(x): Destructor
* Date: 22 Nov 2016
* Description: Destroy Object
*
***************************************/
Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}


/***************************************
*
* F(x): initialize
* Date: 22 Nov 2016
* Description: Initialize game.
*
***************************************/
bool Game::initialize()
{
    if(SDL_Init( SDL_INIT_VIDEO ) >= 0)
	{
		  // Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			SDL_Log( "Warning: Linear texture filtering not enabled!" );
		}

		this->window = SDL_CreateWindow("Stimpy's Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(this->window != NULL)
		{
			  // Create v-synced renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( renderer != NULL )
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				if(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
				{
					return true;
				}
			}
		}
	}

	return false;
}


/***************************************
*
* F(x): run
* Date: 22 Nov 2016
* Description: Run main game loop.
*
***************************************/
void Game::run()
{
    bool quit = false;

    while( !quit )
    {
        while( SDL_PollEvent(&e) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
            //gSpriteSheetTexture.handleEvent(e);
        }
    }
}


