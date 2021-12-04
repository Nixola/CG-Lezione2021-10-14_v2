#include "Drawable.h"
#include "Spite.h"

#include <iostream>

Spite::Drawable::Drawable(int n) : Drawable(n, GL_STATIC_DRAW)
{
}

Spite::Drawable::Drawable(int n, GLenum usageHint)
{
	_nTriangles = n;
	setTexture(Spite::Spite::get().getEmptyTexture());
}

Spite::Drawable::~Drawable()
{
	std::cout << "DESTROY" << std::endl;
	glDeleteBuffers(1, &_VBO);
	glDeleteVertexArrays(1, &_VAO);
}

glm::vec2 Spite::Drawable::getPos() {
	return _model.getPos();
}

glm::vec2 Spite::Drawable::getScale() {
	return _model.getScale();
}

float Spite::Drawable::getAngle() {
	return _model.getAngle();
}

glm::vec2 Spite::Drawable::getOffset() {
	return _model.getOffset();
}

void Spite::Drawable::setTexture(GLuint texture)
{
	_texture = texture;
}

void Spite::Drawable::translate(glm::vec2 pos)
{
	_model.translate(pos);
}
void Spite::Drawable::scale(glm::vec2 scale)
{
	_model.scale(scale);
}
void Spite::Drawable::rotate(float angle)
{
	_model.rotate(angle);
}
void Spite::Drawable::offset(glm::vec2 offset)
{
	_model.offset(offset);
}
void Spite::Drawable::transform(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
	_model.transform(pos, scale, angle, offset);
}

void Spite::Drawable::setPos(glm::vec2 pos)
{
	_model.setPos(pos);
}

void Spite::Drawable::setScale(glm::vec2 scale)
{
	_model.setScale(scale);
}

void Spite::Drawable::setAngle(float angle)
{
	_model.setAngle(angle);
}

void Spite::Drawable::setOffset(glm::vec2 offset)
{
	_model.setOffset(offset);
}

void Spite::Drawable::set(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
	_model.set(pos, scale, angle, offset);
}

void Spite::Drawable::setDrawMode(GLenum mode)
{
	this->_drawMode = mode;
}


void Spite::Drawable::initVao(GLenum usageHint) {
	initVao(usageHint, _vertexData.size());
}
void Spite::Drawable::initVao(GLenum usageHint, GLuint size) 
{
	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);
	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(Vertex), _vertexData.data(), usageHint);
	//Geometry 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);
	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//Texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (7 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void Spite::Drawable::updateVao()
{
	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _vertexData.size() * sizeof(Vertex), _vertexData.data());
}

void Spite::Drawable::draw(void)
{
	GLint currentTexture;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
	if (currentTexture != _texture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texture);
	}
	glBindVertexArray(this->_VAO);
	Spite::get().sendModel(_model.getMatrix());
	glDrawArrays(_drawMode, 0, _vertexData.size());
}

void Spite::Drawable::draw(glm::vec2 pos)
{
	this->draw(pos, glm::vec2(1.0), 0.0, glm::vec2(0.0));
}

void Spite::Drawable::draw(glm::vec2 pos, glm::vec2 scale)
{
	this->draw(pos, scale, 0.0, glm::vec2(0.0));
}

void Spite::Drawable::draw(glm::vec2 pos, glm::vec2 scale, float angle)
{
	this->draw(pos, scale, angle, glm::vec2(0.0));
}

void Spite::Drawable::draw(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
	this->_modelStack.push(this->_model);
	this->_model.transform(pos, scale, angle, offset);
	this->draw();
	this->_model = this->_modelStack.top();
	this->_modelStack.pop();
}