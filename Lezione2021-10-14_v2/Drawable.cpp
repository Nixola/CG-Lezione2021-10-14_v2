#include "Drawable.h"

Spite::Drawable::Drawable(int n)
{
	this->_nTriangles = n;
	this->initVao();
}

void Spite::Drawable::setDrawMode(GLenum mode)
{
	this->_drawMode = mode;
}

void Spite::Drawable::initVao(void)
{
	glGenVertexArrays(1, &this->_VAO);
	glBindVertexArray(this->_VAO);
	//Initialize geometry VBO
	glGenBuffers(1, &this->_geometryVBO);
	//Bind the VBO for sending/setting data
	glBindBuffer(GL_ARRAY_BUFFER, this->_geometryVBO);
	//Send data to VBO
	glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(glm::vec3), this->_vertices.data(), GL_STATIC_DRAW);

	//Geometry VBO is layer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &this->_colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->_colorVBO);
	glBufferData(GL_ARRAY_BUFFER, this->_colors.size() * sizeof(glm::vec4), this->_colors.data(), GL_STATIC_DRAW);
	//Color VBO is layer 1
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void Spite::Drawable::draw(void)
{
	glBindVertexArray(this->_VAO);
	//glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(this->_model.getMatrix()));
	glDrawArrays(this->_drawMode, 0, this->_vertices.size());
}

void Spite::Drawable::draw(glm::vec2 pos)
{
	this->draw(pos, glm::vec2(0.0), 0.0, glm::vec2(0.0));
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