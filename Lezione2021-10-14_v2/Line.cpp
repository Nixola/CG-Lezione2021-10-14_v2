#include "Line.h"

Spite::Line::Line(Vertex p1, Vertex p2) : Drawable(2)
{
    setDrawMode(GL_LINES);
    _vertexData.push_back(p1);
    _vertexData.push_back(p2);
    _color = p1.color;
    initVao(GL_STATIC_DRAW);
}

glm::vec4 Spite::Line::getColor()
{
    return _color;
}

void Spite::Line::setColor(glm::vec4 c)
{
    _color = c;
    for (auto it = _vertexData.begin(); it != _vertexData.end(); it++) {
        it->color = c;
    }
    updateVao();
}
