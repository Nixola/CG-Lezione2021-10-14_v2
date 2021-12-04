#include "Fan.h"

Spite::Fan::Fan(glm::vec4 colors(int i, int n)) : Drawable::Drawable(4)
{
	float v1 = cos(glm::radians(70.0));
	float v2 = sin(glm::radians(70.0));
	_vertexData.push_back({ glm::vec3(0.0), colors(0, 12)});
	_vertexData.push_back({ glm::vec3(-v1, v2, 0), colors(1, 12)});
	_vertexData.push_back({ glm::vec3(v1, v2, 0), colors(2, 12)});
	
	_vertexData.push_back({ glm::vec3(0.0), colors(3, 12)});
	_vertexData.push_back({ glm::vec3(v2, -v1, 0), colors(4, 12)});
	_vertexData.push_back({ glm::vec3(v2, v1, 0), colors(5, 12)});
	
	_vertexData.push_back({ glm::vec3(0.0), colors(6, 12)});
	_vertexData.push_back({ glm::vec3(-v1, -v2, 0), colors(7, 12)});
	_vertexData.push_back({ glm::vec3(v1, -v2, 0), colors(8, 12)});
	
	_vertexData.push_back({ glm::vec3(0.0), colors(9, 12)});
	_vertexData.push_back({ glm::vec3(-v2, -v1, 0), colors(10, 12)});
	_vertexData.push_back({ glm::vec3(-v2, v1, 0), colors(11, 12)});

	setDrawMode(GL_TRIANGLES);
	initVao(GL_STATIC_DRAW);
}