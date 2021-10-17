#include "Mountain.h"

Mountain::Mountain(int n, glm::vec4 colors(int i, int n)) : Drawable::Drawable(n)
{
	float stepA = (2 * PI) / this->nTriangles;

	for (int i = 0; i <= this->nTriangles; i++)
	{
		int p = i / 2;
		float t = i * stepA;
		float x = (float)p * 2.0 / this->nTriangles;
		float y = sin(t / 2.0) * ((i + 1) % 2);
		this->vertices.push_back(glm::vec3(x, y, 1.0));
		this->colors.push_back(colors(i, this->nTriangles));
	}
	this->setDrawMode(GL_TRIANGLE_STRIP);
}
