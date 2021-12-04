#include "Point.h"

Spite::Point::Point(glm::vec2 pos)
{
	_position = pos;
	_velocity = glm::vec2(0, 0);
	_force = glm::vec2(0, 0);
}

void Spite::Point::applyForce(glm::vec2 force)
{
	_force += force;
}

void Spite::Point::applyImpulse(glm::vec2 impulse) {
	_velocity += impulse;
}

glm::vec2 Spite::Point::getPosition() {
	return _position;
}

void Spite::Point::setPosition(glm::vec2 pos) {
	_position = pos;
}

glm::vec2 Spite::Point::getVelocity() {
	return _velocity;
}

void Spite::Point::setVelocity(glm::vec2 vel)
{
	_velocity = vel;
}

void Spite::Point::update(float dt)
{
	glm::vec2 damping = _velocity * -0.2f;
	damping *= glm::length(damping) + 3;
	_force += damping;
	_velocity += _force * dt;
	_velocity *= std::pow(0.1, dt);
	_position += _velocity * dt;
	_force = glm::vec2(0, 0);
}
