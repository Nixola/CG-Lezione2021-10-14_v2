#include "Circle.h"

Spite::Circle::Circle(int n, glm::vec4 colors(int i, int n)) : Drawable::Drawable(n)
{
	float stepA = (2 * PI) / _nTriangles;
	_vertexData.push_back({ glm::vec3(0.0), colors(-1, _nTriangles) });
	for (int i = 0; i <= _nTriangles; i++)
	{
		float t = i * stepA;
		_vertexData.push_back({ glm::vec3(cos(t), sin(t), 0.0), colors(i, _nTriangles)});
	}
	setDrawMode(GL_TRIANGLE_FAN);
	initVao(GL_STATIC_DRAW);
}
