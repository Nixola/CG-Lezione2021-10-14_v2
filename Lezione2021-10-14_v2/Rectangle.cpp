#include "Rectangle.h"

Spite::Rectangle::Rectangle(int n, glm::vec4 colors(int i, int n)) : Spite::Drawable::Drawable(n)
{
	for (int i = 0; i < this->_nTriangles; i++)
	{
		int p = i / 2;
		float x = (float)p * 4.0 / this->_nTriangles;
		float y = (i % 2);
		this->_vertices.push_back(glm::vec3(x, y, 1.0));
		this->_colors.push_back(colors(i, this->_nTriangles));
	}
	this->setDrawMode(GL_TRIANGLE_STRIP);
	this->initVao();
}
