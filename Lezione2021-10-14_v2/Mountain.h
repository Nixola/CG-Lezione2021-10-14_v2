#pragma once
#include "Drawable.h"

namespace Spite {
    class Mountain :
        public Drawable
    {
    public:
        Mountain(int n, glm::vec4 colors(int i, int n));
    };

}