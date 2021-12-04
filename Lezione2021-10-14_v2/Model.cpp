#include "Model.h"

void Spite::Model::update(void)
{
    this->_matrix = glm::translate(_base, glm::vec3(this->_pos, 0.0));
    this->_matrix = glm::rotate(this->_matrix, this->_angle, glm::vec3(0.0,0.0,1.0));
    this->_matrix = glm::translate(this->_matrix, glm::vec3(-this->_offset, 0.0));
    this->_matrix = glm::scale(this->_matrix, glm::vec3(this->_scale, 1.0));
}

glm::mat4 Spite::Model::getMatrix()
{
    this->update();
    return this->_matrix;
}

glm::vec2 Spite::Model::getPos() {
    return _pos;
}

glm::vec2 Spite::Model::getScale() {
    return _scale;
}

float Spite::Model::getAngle() {
    return _angle;
}

glm::vec2 Spite::Model::getOffset() {
    return _offset;
}

void Spite::Model::translate(glm::vec2 pos)
{
    this->_pos += pos;
}

void Spite::Model::scale(glm::vec2 scale)
{
    this->_scale *= scale;
}

void Spite::Model::rotate(float angle)
{
    this->_angle += angle;
}

void Spite::Model::offset(glm::vec2 offset)
{
    this->_offset += offset;
}

void Spite::Model::transform(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
    this->translate(pos);
    this->scale(scale);
    this->rotate(angle);
    this->offset(offset);
}

void Spite::Model::setPos(glm::vec2 pos)
{
    this->_pos = pos;
}

void Spite::Model::setScale(glm::vec2 scale)
{
    this->_scale = scale;
}

void Spite::Model::setAngle(float angle)
{
    this->_angle = angle;
}

void Spite::Model::setOffset(glm::vec2 offset)
{
    this->_offset = offset;
}

void Spite::Model::set(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset)
{
    this->setPos(pos);
    this->setScale(scale);
    this->setAngle(angle);
    this->setOffset(offset);
}

Spite::Model::Model(void)
{
    _base = glm::mat4(1.0);
    this->_pos = glm::vec2(0.0);
    this->_scale = glm::vec2(1.0);
    this->_angle = 0.0;
    this->_offset = glm::vec2(0.0);
    this->_matrix = glm::mat4(1.0);
}

Spite::Model::Model(glm::mat4 base) : Model()
{
    _base = base;
}

Spite::Model::Model(glm::vec2 pos) : Spite::Model()
{
    this->setPos(pos);
}

Spite::Model::Model(glm::vec2 pos, glm::vec2 scale) : Spite::Model(pos)
{
    this->setScale(scale);
}

Spite::Model::Model(glm::vec2 pos, glm::vec2 scale, float angle) : Spite::Model(pos, scale)
{
    this->setAngle(angle);
}

Spite::Model::Model(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset) : Spite::Model(pos, scale, angle)
{
    this->setOffset(offset);
}
