#pragma once
#include <glm/glm.hpp>

namespace Spite {
	struct Vertex {
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 uv;
	};
}