#pragma once
#include "Drawable.h"

class Circle :
    public Drawable
{
public:
    Circle(int n, glm::vec4 f(int i, int n));
};

