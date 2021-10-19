#include "Fan.h"

Spite::Fan::Fan(glm::vec4 colors(int i, int n)) : Drawable::Drawable(4)
{
	float v1 = cos(glm::radians(70.0));
	float v2 = sin(glm::radians(70.0));
	_vertices.push_back(glm::vec3(0.0));
	_colors.push_back(colors(0, 12));
	_vertices.push_back(glm::vec3(-v1, v2, 0.0));
	_colors.push_back(colors(1, 12));
	_vertices.push_back(glm::vec3(v1, v2, 0.0));
	_colors.push_back(colors(2, 12));

	_vertices.push_back(glm::vec3(0.0));
	_colors.push_back(colors(3, 12));
	_vertices.push_back(glm::vec3(v2, -v1, 0.0));
	_colors.push_back(colors(4, 12));
	_vertices.push_back(glm::vec3(v2, v1, 0.0));
	_colors.push_back(colors(5, 12));

	_vertices.push_back(glm::vec3(0.0));
	_colors.push_back(colors(6, 12));
	_vertices.push_back(glm::vec3(-v1, -v2, 0.0));
	_colors.push_back(colors(7, 12));
	_vertices.push_back(glm::vec3(v1, -v2, 0.0));
	_colors.push_back(colors(8, 12));

	_vertices.push_back(glm::vec3(0.0));
	_colors.push_back(colors(9, 12));
	_vertices.push_back(glm::vec3(-v2, -v1, 0.0));
	_colors.push_back(colors(10, 12));
	_vertices.push_back(glm::vec3(-v2, v1, 0.0));
	_colors.push_back(colors(11, 12));

	setDrawMode(GL_TRIANGLES);
}