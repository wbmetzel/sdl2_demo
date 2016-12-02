
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "Texture.h"

class Environment : Texture
{
public:
    Environment();
    ~Environment();
    bool loadBackground();

};

#endif
