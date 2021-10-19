#pragma once
#include "Drawable.h"
namespace Spite {
    class Fan :
        public Drawable
    {
        Fan(glm::vec4 colors(int i, int n));
    };
}