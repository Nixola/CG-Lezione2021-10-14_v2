#pragma once
#include "Drawable.h"
namespace Spite {
    class Circle :
        public Drawable
    {
    public:
        Circle(int n, glm::vec4 f(int i, int n));
    };
}