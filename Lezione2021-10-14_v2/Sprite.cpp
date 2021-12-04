#include "Sprite.h"

Spite::Sprite::Sprite(GLuint texture) : Rectangle(4, [](int i, int n) -> glm::vec4 { return glm::vec4(1.0); })
{
	_vertexData[0].uv = { 0.0,0.0 };
	_vertexData[1].uv = { 0.0,1.0 };
	_vertexData[3].uv = { 1.0,0.0 };
	_vertexData[2].uv = { 1.0,1.0 };
	setTexture(texture);
	updateVao();
}

void Spite::Sprite::setTextureCoordinates(glm::vec2 origin, glm::vec2 end)
{
	_vertexData[0].uv = origin;
	_vertexData[1].uv.x = origin.x;
	_vertexData[1].uv.y = end.y;
	_vertexData[2].uv.x = end.x;
	_vertexData[2].uv.y = origin.y;
	_vertexData[3].uv = end;
	updateVao();
}
