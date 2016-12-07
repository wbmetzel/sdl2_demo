#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();//Starts up SDL and creates window
bool loadMedia();//Loads media
void close();//Frees media and shuts down SDL
SDL_Texture *loadTexture(std::string path);

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;
			SDL_Event e;

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
				}

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                SDL_RenderPresent(renderer);

				//SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, &stretchRect);
				//SDL_UpdateWindowSurface( gWindow );

			}
		}
	}

	close();

	return 0;
}


/************************************************
* Initialize Window
************************************************/
bool init()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	else
	{
	    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			return false;
		}
		else
		{
		    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		    if(renderer == NULL)
            {
                printf("Renderer could not be created. SDL_Error: %s\n", SDL_GetError());
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x80, 0x80, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if( !(IMG_Init(imgFlags) & imgFlags) )
                {
                    return false;
                }
            }
		}
	}

	return true;
}


/************************************************
* Load media to surface
************************************************/
bool loadMedia()
{
    texture = loadTexture("texture.png");
    if( texture == NULL)
    {
        return false;
    }
	return true;
}


/************************************************
* Deallocate memory for window
************************************************/
void close()
{
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	texture = NULL;
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


/************************************************
* Load surface in window
************************************************/
SDL_Texture *loadTexture( std::string path )
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if(loadedSurface != NULL)
    {
        newTexture = SDL_CreateTextureFromSurface(renderer,loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }

	return newTexture;
}
