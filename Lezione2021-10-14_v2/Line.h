#pragma once
#include "Drawable.h"
namespace Spite {
    class Line :
        public Drawable
    {
    private:
        glm::vec4 _color;
    public:
        Line(Vertex p1, Vertex p2);
        glm::vec4 getColor();
        void setColor(glm::vec4 c);
    };
}
