#include "Rectangle.h"

Rectangle::Rectangle(int n, glm::vec4 colors(int i, int n)) : Drawable::Drawable(n)
{
	for (int i = 0; i < this->nTriangles; i++)
	{
		int p = i / 2;
		float x = (float)p * 4.0 / this->nTriangles;
		float y = (i % 2);
		this->vertices.push_back(glm::vec3(x, y, 1.0));
		this->colors.push_back(colors(i, this->nTriangles));
	}
	this->setDrawMode(GL_TRIANGLE_STRIP);
}
