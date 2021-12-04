#include "Spring.h"

#include <iostream>

Spite::Spring::Spring(Spite::Point* p1, Spite::Point* p2, float forceCoefficient, float dampingCoefficient) :
	//_p1(p1), _p2(p2), 
	_base({0,0})
{
	_p1 = p1;
	_p2 = p2;
	_fixed = false;
	_restingLength = glm::length(p1->getPosition() - p2->getPosition());
	_forceCoefficient = forceCoefficient;
	_dampingCoefficient = dampingCoefficient;
}

Spite::Spring::Spring(Spite::Point* p1, float forceCoefficient, float dampingCoefficient) :
	_p1(p1), _p2(&_base), _base(p1->getPosition())
{
	_fixed = true;
	_restingLength = 0;
	_forceCoefficient = forceCoefficient;
	_dampingCoefficient = dampingCoefficient;
}

void Spite::Spring::update()
{
	glm::vec2 distance = _p2->getPosition() - _p1->getPosition();
	float length = glm::length(distance);
	if (length < 0.001f) {
		return;
	}
	float deltaLength = glm::length(distance) - _restingLength;
	float forceStrength = deltaLength * _forceCoefficient;

	glm::vec2 direction = glm::normalize(distance);
	if (direction.x != direction.x || direction.y != direction.y) {
		return;
	}
	glm::vec2 deltaV = _p2->getVelocity() - _p1->getVelocity();
	float damping = glm::dot(deltaV, direction) * _dampingCoefficient;

	_p1->applyForce(distance * (forceStrength + damping));
	if (!_fixed) {
		_p2->applyForce(distance * (forceStrength + damping) * -1.0f);
	}
}
