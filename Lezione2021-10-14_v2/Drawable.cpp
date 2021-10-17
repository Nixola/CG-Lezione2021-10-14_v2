#include "Drawable.h"

Drawable::Drawable(int n, glm::vec4 colors(int i, int n))
{
	this->nTriangles = n;
	this->build(colors);
	this->initVao();
}

void Drawable::setDrawMode(GLenum mode)
{
	this->drawMode = mode;
}

void Drawable::initVao(void)
{
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	//Initialize geometry VBO
	glGenBuffers(1, &this->geometryVBO);
	//Bind the VBO for sending/setting data
	glBindBuffer(GL_ARRAY_BUFFER, this->geometryVBO);
	//Send data to VBO
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

	//Geometry VBO is layer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &this->colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorVBO);
	glBufferData(GL_ARRAY_BUFFER, this->colors.size() * sizeof(glm::vec4), this->colors.data(), GL_STATIC_DRAW);
	//Color VBO is layer 1
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);
}

void Drawable::draw(void)
{
	glBindVertexArray(this->VAO);
	//glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(this->model.getMatrix()));
	glDrawArrays(this->drawMode, 0, this->vertices.size());
}

void Drawable::draw(glm::vec2 pos)
{
	this->draw(pos, glm::vec2(0.0), 0.0, glm::vec2(0.0));
}

void Drawable::draw(glm::vec2 pos, glm::vec2 scale)
{
	this->draw(pos, scale, 0.0, glm::vec2(0.0));
}

void Drawable::draw(glm::vec2 pos, glm::vec2 scale, float angle)
{
	this->draw(pos, scale, angle, glm::vec2(0.0));
}

void Drawable::draw(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
	this->modelStack.push(this->model);
	this->model.transform(pos, scale, angle, offset);
	this->draw();
	this->model = this->modelStack.top();
	this->modelStack.pop();
}