#pragma once
#include "Drawable.h"
namespace Spite {
    class Rectangle :
        public Drawable
    {
    public:
        Rectangle(int n, glm::vec4 colors(int i, int n));
    };

}