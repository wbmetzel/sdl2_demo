
#include "Character.h"


/***************************************
*
* F(x): Constructor
* Date: 22 Nov 2016
* Description: Initialize instance
*
***************************************/
Character::Character()
{
    this->posX = 0;
    this->posY = 0;
    this->velX = 0;
    this->velY = 0;
}


/***************************************
*
* F(x): Destructor
* Date: 22 Nov 2016
* Description: Destroy instance
*
***************************************/
Character::~Character()
{
    this->clearMemory();
}


/***************************************
*
* F(x): handleEvent
* Date: 22 Nov 2016
* Description: Handle events to object
*
***************************************/
void Character::handleEvent(SDL_Event &e)
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            velY -= VELOCITY;
            break;
        case SDLK_DOWN:
            velY += VELOCITY;
            break;
        case SDLK_LEFT:
            velX -= VELOCITY;
            break;
        case SDLK_RIGHT:
            velX += VELOCITY;
            break;

        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            velY += VELOCITY;
            break;
        case SDLK_DOWN:
            velY -= VELOCITY;
            break;
        case SDLK_LEFT:
            velX += VELOCITY;
            break;
        case SDLK_RIGHT:
            velX -= VELOCITY;
            break;
        }
    }
}
/*
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
*/


/***************************************
*
* F(x): getPosX
* Date: 22 Nov 2016
* Description: X position accessor
*
***************************************/
int Character::getPosX()
{
    return this->posX;
}


/***************************************
*
* F(x): getPosY
* Date: 22 Nov 2016
* Description: Y position accessor
*
***************************************/
int Character::getPosY()
{
    return this->posY;
}


/***************************************
*
* F(x): getVelX
* Date: 22 Nov 2016
* Description: X Velocity accessor
*
***************************************/
int Character::getVelX()
{
    return this->velX;
}


/***************************************
*
* F(x): getVelY
* Date: 22 Nov 2016
* Description: Y Velocity accessor
*
***************************************/
int Character::getVelY()
{
    return this->velY;
}
