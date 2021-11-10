#pragma once
#include "Drawable.h"
namespace Spite {
    class Fan :
        public Drawable
    {
    public:
        Fan(glm::vec4 colors(int i, int n));
    };
}