#pragma once
#include "Drawable.h"

#define  PI   3.141592653589793238465

class Mountain :
    public Drawable
{
public:
    Mountain(int n, glm::vec4 colors(int i, int n));
};

