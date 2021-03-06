
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 480;
const int FRAMES = 6;

class LTexture
{
	public:
        static const int VELOCITY = 10;

		LTexture();
		~LTexture();
		bool loadFromFile( std::string path );
		void free();//Deallocates texture
		void setColor( Uint8 red, Uint8 green, Uint8 blue );//Set color modulation
		void setBlendMode( SDL_BlendMode blending );//Set blending
		void setAlpha( Uint8 alpha );//Set alpha modulation
		void render( int x, int y, SDL_Rect* clip = NULL );//Renders texture at given point
		void render(SDL_Rect* clip = NULL);//Renders texture at given point

		void movement();
		void handleEvent(SDL_Event &e);

		//Gets image dimensions
		int getWidth();
		int getHeight();
		int getPosX();
		int getPosY();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;
        int mPosX, mPosY;
        int mVelX, mVelY;
		//Image dimensions
		int mWidth;
		int mHeight;
};


bool init();
bool loadMedia();
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Event e;

//Walking animation
const int WALKING_ANIMATION_FRAMES = FRAMES;
SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
SDL_Rect spriteIdle[4];
LTexture gSpriteSheetTexture;
LTexture gBackgroundTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mPosX = 0;
	mPosY = 0;
	mVelX = 0;
	mVelY = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0x65, 0x8D, 0xD1 ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= VELOCITY;
            break;
        case SDLK_DOWN:
            mVelY += VELOCITY;
            break;
        case SDLK_LEFT:
            mVelX -= VELOCITY;
            break;
        case SDLK_RIGHT:
            mVelX += VELOCITY;
            break;

        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += VELOCITY;
            break;
        case SDLK_DOWN:
            mVelY -= VELOCITY;
            break;
        case SDLK_LEFT:
            mVelX += VELOCITY;
            break;
        case SDLK_RIGHT:
            mVelX -= VELOCITY;
            break;
        }
    }
}

void LTexture::movement()
{
    mPosX += mVelX;

    if((mPosX < 0) || (mPosX + mWidth > SCREEN_WIDTH))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if((mPosY < 0) || (mPosY + mHeight > SCREEN_HEIGHT))
    {
        mPosY -= mVelY;
    }
}

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

void LTexture::render(SDL_Rect* clip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { mPosX, mPosY, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
	    renderQuad.x = clip->x;
	    renderQuad.y = clip->y;
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

int LTexture::getPosX()
{
    return mPosX;
}

int LTexture::getPosY()
{
    return mPosY;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if(!gBackgroundTexture.loadFromFile("mario_background2.png"))
	{
		printf( "Failed to load Background texture!\n" );
		success = false;
	}

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "stimpy.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
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

	return success;
}

void close()
{
	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
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
					gSpriteSheetTexture.handleEvent(e);
				}

				gSpriteSheetTexture.movement();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				gBackgroundTexture.render(0,0);

/*
                SDL_Rect* currentClip = &gSpriteClips[ frame / FRAMES ];

                gSpriteSheetTexture.render(currentClip );

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Go to next frame
				++frame;

				//Cycle animation
				if( frame / FRAMES >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}

*/
				SDL_Rect *currentClip = &spriteIdle[frame / 4];

				gSpriteSheetTexture.render( currentClip->w - 30, SCREEN_HEIGHT - (currentClip->h * 2) - 10, currentClip );

				//Update screen
				SDL_RenderPresent( gRenderer );

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


			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
