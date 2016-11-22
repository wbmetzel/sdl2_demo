
#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Texture.h"

class Character : public Texture
{
	public:
        static const int VELOCITY = 10;

		Character();
		~Character();

		// // void render(SDL_Rect* clip = NULL);
		// // void movement();
		void handleEvent(SDL_Event &e);

		  // Accessors
		int getPosX();
		int getPosY();
        int getVelX();
        int getVelY();
	protected:
        int posX, posY;
        int velX, velY;

};

#endif // __CHARACTER_H__
