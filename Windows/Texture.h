
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Texture
{
	public:
        // // static const int VELOCITY = 10;

		Texture();
		Texture(char* path);
		~Texture();
		void clearMemory();
        bool loadPNG(char* path, SDL_Renderer *&renderer, Uint8 red = 0xFF, Uint8 green = 0xFF, Uint8 blue = 0xFF);
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render(const int &x,const int &y, SDL_Renderer *&renderer, SDL_Rect* clip);//Renders texture at given point
		// // void render(SDL_Rect* clip = NULL);//Renders texture at given point

		// // void movement();
		// // void handleEvent(SDL_Event &e);

		//Gets image dimensions
		int getWidth();
		int getHeight();
		// // int getPosX();
		// // int getPosY();

	private:
		SDL_Texture *resource;
        // // int mPosX, mPosY;
        // // int mVelX, mVelY;
		//Image dimensions
    protected:
        char* filepath;
		int width;
		int height;
};

#endif // __TEXTURE_H__
