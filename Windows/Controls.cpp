
#include "Controls.h"


/***************************************
*
* F(x): Constructor
* Date: 23 Nov 2016
* Description: Initialize instance
*
***************************************/
Controls::Controls()
{
}


/***************************************
*
* F(x): Destructor
* Date: 23 Nov 2016
* Description: Destroy instance
*
***************************************/
Controls::~Controls()
{
    SDL_FlushEvents(SDL_USEREVENT, SDL_LASTEVENT);
}


/***************************************
*
* F(x): eventStatus
* Date: 23 Nov 2016
* Description: return true when event
*              queue is empty.
*
***************************************/
bool Controls::eventStatus()
{
    return (SDL_PollEvent(&e) != 0);
}


/***************************************
*
* F(x): exitGame
* Date: 23 Nov 2016
* Description: Exit game.
*
***************************************/
bool Controls::exitGame()
{
    return e.type == SDL_QUIT;
}
