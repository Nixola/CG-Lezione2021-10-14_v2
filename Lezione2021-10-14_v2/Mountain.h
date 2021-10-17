#pragma once
#include "Drawable.h"

#define  PI   3.141592653589793238465

class Mountain :
    public Drawable
{
protected:
    void build(glm::vec4 colors(int i, int n)) override;
};

