
#include "Environment.h"

/***************************************
*
* F(x): Constructor
* Date: 23 Nov 2016
* Description: Initialize instance
*
***************************************/
Environment::Environment()
{
}


/***************************************
*
* F(x): Destructor
* Date: 23 Nov 2016
* Description: Destroy instance
*
***************************************/
Environment::~Environment()
{
}


/***************************************
*
* F(x): loadBackground
* Date: 22 Nov 2016
* Description: Loads background to surface
*
***************************************/
bool Environment::loadBackground()
{
    if(!Texture::loadPNG("Resources/mario_background2.png"))
    {
        return false;
    }

    this->render(0,0,NULL);
    return true;
}

