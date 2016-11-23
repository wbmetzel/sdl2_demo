
#include "Texture.h"


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
bool Texture::loadPNG(char* path, Uint8 red, Uint8 green, Uint8 blue)
{
	this->clearMemory();

    SDL_Surface *current = IMG_Load(path);

    if(current != NULL)
    {
        SDL_SetColorKey(current, SDL_TRUE, SDL_MapRGB(current->format, red, green, blue));
        SDL_Texture *newTexture = SDL_CreateTextureFromSurface(this->renderer,current);
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
void Texture::render(const int &x, const int &y, SDL_Rect* clip)
{
    if(clip != NULL)
    {
       this->width = clip->w;
       this->height = clip->h;
    }

      // Render params
	SDL_Rect renderQuad = {x, y, this->width, this->height};
	SDL_RenderCopy( this->renderer, this->resource, clip, &renderQuad );
}


/***************************************
*
* F(x): setColor
* Date: 22 Nov 2016
* Description: Texture colour modulation
*
***************************************/
void Texture::setColor(const Uint8 &red, const Uint8 &green, const Uint8 &blue)
{
	SDL_SetTextureColorMod(this->resource, red, green, blue);
}


/***************************************
*
* F(x): setBlendMode
* Date: 22 Nov 2016
* Description: Texture Blending
*
***************************************/
void Texture::setBlendMode(SDL_BlendMode blending)
{
	  // Set blending function
	SDL_SetTextureBlendMode(this->resource, blending );
}


/***************************************
*
* F(x): setAlpha
* Date: 22 Nov 2016
* Description:Texture alpha modulation
*
***************************************/
void Texture::setAlpha(const Uint8 &alpha)
{
	SDL_SetTextureAlphaMod(this->resource, alpha);
}


/***************************************
*
* F(x): getWidth
* Date: 22 Nov 2016
* Description: width accessor
*
***************************************/
int Texture::getWidth()
{
	return this->width;
}


/***************************************
*
* F(x): getHeight
* Date: 22 Nov 2016
* Description: height accessor
*
***************************************/
int Texture::getHeight()
{
	return this->height;
}
