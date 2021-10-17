#include "Model.h"

void Model::update(void)
{
    this->_matrix = glm::translate(glm::mat4(1.0), glm::vec3(this->_pos, 0.0));
    this->_matrix = glm::rotate(this->_matrix, this->_angle, glm::vec3(0.0,0.0,1.0));
    this->_matrix = glm::translate(this->_matrix, glm::vec3(-this->_offset, 1.0));
    this->_matrix = glm::scale(this->_matrix, glm::vec3(this->_scale, 1.0));
}

glm::mat4 Model::getMatrix()
{
    this->update();
    return this->_matrix;
}

void Model::translate(glm::vec2 pos)
{
    this->_pos += pos;
}

void Model::scale(glm::vec2 scale)
{
    this->_scale *= scale;
}

void Model::rotate(float angle)
{
    this->_angle += angle;
}

void Model::offset(glm::vec2 offset)
{
    this->_offset += offset;
}

void Model::transform(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
    this->translate(pos);
    this->scale(scale);
    this->rotate(angle);
    this->offset(offset);
}

void Model::setPos(glm::vec2 pos)
{
    this->_pos = pos;
}

void Model::setScale(glm::vec2 scale)
{
    this->_scale = scale;
}

void Model::setAngle(float angle)
{
    this->_angle = angle;
}

void Model::setOffset(glm::vec2 offset)
{
    this->_offset = offset;
}

void Model::set(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
    this->setPos(pos);
    this->setScale(scale);
    this->setAngle(angle);
    this->setOffset(offset);
}

Model::Model(void)
{
    this->_pos = glm::vec2(0.0);
    this->_scale = glm::vec2(0.0);
    this->_angle = 0.0;
    this->_offset = glm::vec2(0.0);
    this->_matrix = glm::mat4(1.0);
}

Model::Model(glm::vec2 pos) : Model()
{
    this->setPos(pos);
}

Model::Model(glm::vec2 pos, glm::vec2 scale) : Model(pos)
{
    this->setScale(scale);
}

Model::Model(glm::vec2 pos, glm::vec2 scale, float angle) : Model(pos, scale)
{
    this->setAngle(angle);
}

Model::Model(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset) : Model(pos, scale, angle)
{
    this->setOffset(offset);
}
