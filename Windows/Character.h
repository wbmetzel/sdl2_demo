
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Texture.h"

class Character : public Texture
{
	public:
        static const int VELOCITY = 10;

		Character();
		~Character();

		// // void render(SDL_Rect* clip = NULL);//Renders texture at given point
		// // void movement();
		// // void handleEvent(SDL_Event &e);

		// // int getPosX();
		// // int getPosY();

	private:
        int posX, posY;
        int velX, velY;

};

#endif // __CHARACTER_H__
