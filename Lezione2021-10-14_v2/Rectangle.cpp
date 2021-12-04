#include "Rectangle.h"

Spite::Rectangle::Rectangle(int n, glm::vec4 colors(int i, int n)) : Spite::Drawable::Drawable(n)
{
	for (int i = 0; i < _nTriangles; i++)
	{
		int p = i / 2;
		float x = (float)p * 4.0 / _nTriangles;
		float y = (i % 2);
		_vertexData.push_back({ glm::vec3(x, y, 0.0), colors(i, _nTriangles) });
	}
	setDrawMode(GL_TRIANGLE_STRIP);
	initVao(GL_STATIC_DRAW);
}
