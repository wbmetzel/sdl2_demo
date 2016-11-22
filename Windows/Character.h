
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

class Character : public Texture
{
	public:
        // // static const int VELOCITY = 10;

		Character();
		//Character(char* path);
		~Character();

		// // void render(SDL_Rect* clip = NULL);//Renders texture at given point
		// // void movement();
		// // void handleEvent(SDL_Event &e);

		// // int getPosX();
		// // int getPosY();

	private:
        // // int mPosX, mPosY;
        // // int mVelX, mVelY;
		//Image dimensions
};

#endif // __CHARACTER_H__
