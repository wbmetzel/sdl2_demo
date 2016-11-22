
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

class Texture
{
	public:
		Texture();
		Texture(char* path);
		~Texture();
		void clearMemory();
        bool loadPNG(char* path, SDL_Renderer *&renderer, Uint8 red = 0xFF, Uint8 green = 0xFF, Uint8 blue = 0xFF);
		void setColor(const Uint8 &red, const Uint8 &green, const Uint8 &blue);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(const Uint8 &alpha);
		void render(const int &x,const int &y, SDL_Renderer *&renderer, SDL_Rect* clip);
		int getWidth();
		int getHeight();
    protected:
		SDL_Texture *resource;
        char* filepath;
		int width;
		int height;
};

#endif // __TEXTURE_H__
