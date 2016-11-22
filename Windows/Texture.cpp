
#include "Texture.h"

/*
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
*/

/***************************************
*
* F(x): Constructor
* Date: 22 Nov 2016
* Description: Initialize object
*
***************************************/
Texture::Texture()
{
	this->resource = NULL;
	this->filepath = NULL;
	this->width = 0;
	this->height = 0;
}


/***************************************
*
* F(x): Copy Constructor
* Date: 22 Nov 2016
* Description: Initialize object
*
***************************************/
Texture::Texture(char* path)
{
	this->resource = NULL;
	this->filepath = path;
	this->width = 0;
	this->height = 0;
}


/***************************************
*
* F(x): Destructor
* Date: 22 Nov 2016
* Description: Destroy Object
*
***************************************/
Texture::~Texture()
{
	clearMemory();
}


/***************************************
*
* F(x): clearMemory
* Date: 22 Nov 2016
* Description: Deallocate object memory
*
***************************************/
void Texture::clearMemory()
{
	if(this->resource != NULL)
	{
		SDL_DestroyTexture(this->resource);
		this->resource = NULL;
		this->width = 0;
		this->height = 0;
	}
}


/***************************************
*
* F(x): loadPNG
* Date: 22 Nov 2016
* Description: Load resource
*
***************************************/
bool Texture::loadPNG(char* path, SDL_Renderer *&renderer, Uint8 red, Uint8 green, Uint8 blue)
{
	this->clearMemory();

    SDL_Surface *current = IMG_Load(path);

    if(current != NULL)
    {
        SDL_SetColorKey(current, SDL_TRUE, SDL_MapRGB(current->format, red, green, blue));
        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer,current);
        if(newTexture != NULL)
        {
            this->resource = newTexture;
            this->width = current->w;
            this->height = current->h;
        }
    }

    SDL_FreeSurface(current);
    return this->resource != NULL;
}


/***************************************
*
* F(x): render
* Date: 22 Nov 2016
* Description: render resource
*
***************************************/
void Texture::render(const int &x, const int &y, SDL_Renderer *&renderer, SDL_Rect* clip)
{
    if(clip != NULL)
    {
       this->width = clip->w;
       this->height = clip->h;
    }

      // Render params
	SDL_Rect renderQuad = {x, y, this->width, this->height};
	SDL_RenderCopy( renderer, this->resource, clip, &renderQuad );
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	  // Modulate texture rgb
	SDL_SetTextureColorMod(this->resource, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
	  // Set blending function
	SDL_SetTextureBlendMode(this->resource, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
	  // Modulate texture alpha
	SDL_SetTextureAlphaMod( this->resource, alpha );
}


/*
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
*/


int Texture::getWidth()
{
	return this->width;
}

int Texture::getHeight()
{
	return this->height;
}


