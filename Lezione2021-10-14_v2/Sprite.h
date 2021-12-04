#pragma once
#include "Rectangle.h"
namespace Spite {
    class Sprite :
        public Rectangle
    {
    public:
        Sprite(GLuint texture);
        void setTextureCoordinates(glm::vec2 origin, glm::vec2 end);
    };
}