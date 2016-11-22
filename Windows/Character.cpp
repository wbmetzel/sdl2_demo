
#include "Character.h"


Character::Character()
{
    this->posX = 0;
    this->posY = 0;
    this->velX = 0;
    this->velY = 0;
}

Character::~Character()
{
}

/*
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
*/
