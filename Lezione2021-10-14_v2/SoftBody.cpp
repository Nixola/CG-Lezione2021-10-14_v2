#define _USE_MATH_DEFINES
#include <cmath>
#include "SoftBody.h"
#include "Spite.h"

#include "dirt4.h"
#include "Texture.h"

#include <iostream>

#define IfromPolar(ring,pos,segments) ((ring-1) * (segments) + (pos) + 1)

float dampingForceCoefficient = 0.5;


Spite::SoftBody::SoftBody(int segments, double radius, glm::vec2 pos, float springForce) : 
	HermiteCurve(segments * 3 + 1, GL_DYNAMIC_DRAW),
	_segments(segments), 
	_radius(radius)
{
	_force = glm::vec2(0.0, 0.0);
	_vel = glm::vec2(0.0, 0.0);
	_color = glm::vec4(1.0);
	_points.push_back(new Point({ 0, 0 }));
	setPos(pos);
	for (int ring = 1; ring <= _rings; ring++) {
		for (int i = 0; i < segments; i++) {
			float angle = M_PI * 2 / (float)segments * (float) i;
			float x = std::cos(angle) * radius * (float)ring / (float) _rings;
			float y = std::sin(angle) * radius * (float)ring / (float) _rings;
			_points.push_back(new Point({ x, y }));
			_springs.push_back(new Spring(_points[_points.size() - 1], springForce, dampingForceCoefficient));
		}
	}

	for (int i = 1; i <= segments; i++) {
		int cw = i % segments + 1;
		_springs.push_back(new Spring(_points[i], _points[0], springForce, dampingForceCoefficient));
		_springs.push_back(new Spring(_points[i], _points[cw], springForce, dampingForceCoefficient));
	}

	for (int i = segments + 1; i <= segments * _rings; i++) {
		int ring = std::ceil((float)i / (float)segments);
		int pos = (i - 1) % segments;

		int belowc = IfromPolar(ring - 1, pos, segments);
		int belowccw = IfromPolar(ring - 1, glm::mod((float) pos - 1.0f, (float) segments), segments);
		int belowcw = IfromPolar(ring - 1, glm::mod((float) pos + 1.0f, (float) segments), segments);
		int prev = IfromPolar(ring, glm::mod((float) pos - 1.0f, (float) segments), segments);

		_springs.push_back(new Spring(_points[i], _points[belowc], springForce, dampingForceCoefficient));
		_springs.push_back(new Spring(_points[i], _points[belowcw], springForce, dampingForceCoefficient));
		_springs.push_back(new Spring(_points[i], _points[belowccw], springForce, dampingForceCoefficient));
		_springs.push_back(new Spring(_points[i], _points[prev], springForce, dampingForceCoefficient));
	}
	setDrawMode(GL_TRIANGLE_FAN);
	initVao(GL_DYNAMIC_DRAW, segments * 3 + 1);
}

Spite::SoftBody::~SoftBody()
{
	for (auto dis = _points.begin(); dis != _points.end(); dis++) {
		delete* dis;
	}
	for (auto dis = _springs.begin(); dis != _springs.end(); dis++) {
		delete* dis;
	}
}

float Spite::SoftBody::getRadius()
{
	return _radius;
}

Spite::Point Spite::SoftBody::getCenter()
{
	return *_points[0];
}

void Spite::SoftBody::setColor(glm::vec4 c)
{
	_color = c;
}

void Spite::SoftBody::applyForce(glm::vec2 force) {
	_force += force;
}

void Spite::SoftBody::updateVao() {
	/*
	_vertexData.clear();
	//std::cout << '{';
	//_vertices.push_back(glm::vec3(0.0));
	for (int i = _points.size() - _segments; i < _points.size(); i++) {
		_vertexData.push_back({ glm::vec3(_points[i].getPosition(), 0.0), glm::vec4(1.0) });
		//std::cout << '(' << _points[i].getPosition().x << ',' << _points[i].getPosition().y << "), ";
	}
	//std::cout << std::endl;
	//*/
	interpolate(_color);
	Drawable::updateVao();
}

void Spite::SoftBody::update(float dt)
{
	for (auto it = _springs.begin(); it != _springs.end(); it++) {
		(*it)->update();
	}

	_points[0]->applyForce(_force);
	_points[0]->update(dt);
	glm::vec2 center = _points[0]->getPosition();
	translate(center);
	_points[0]->setPosition(glm::vec2(0, 0));
	_controlPoints.clear();
	for (auto it = ++_points.begin(); it != _points.end(); it++) {
		(*it)->applyForce(_force);
		(*it)->setVelocity((*it)->getVelocity() + _vel);
		(*it)->update(dt);
		(*it)->setPosition((*it)->getPosition() - center);
	}
	for (int i = _points.size() - _segments; i < _points.size(); i++) {
		_controlPoints.push_back(_points[i]->getPosition());
	}
	_controlPoints.push_back(_points[_points.size() - _segments]->getPosition());
	_force = glm::vec2(0, 0);
	_vel = glm::vec2(0.0);
	updateVao();
}

void Spite::SoftBody::draw()
{
	// prepare stencil buffer
	glEnable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);

	// set stencil buffer to invert value on draw, 0 to 1 and 1 to 0
	glStencilFunc(GL_ALWAYS, 0, 1);
	glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);

	// disable writing to color buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// draw polygon into stencil buffer
	Drawable::draw();

	// set stencil buffer to only keep pixels when value in buffer is 1
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	// enable color again
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	// redraw polygon again, this time into color buffer.
	// alternatively, only draw bounding box of polygon
	Drawable::draw();

	glDisable(GL_STENCIL_TEST);
}

void Spite::SoftBody::knockback(glm::vec2 position, float radius, glm::vec2 strength)
{
	if (radius < 1) {
		std::cout << "ohno " << radius << std::endl;
	}
	for (auto it = _points.begin(); it != _points.end(); it++) {
		float portion = 1 - glm::length(position - getPos() - (*it)->getPosition()) / radius;
		if (portion > 0) {
			(*it)->applyForce(strength * (float) std::pow(portion, 2.0));
		}
		if (portion > 1) {
			std::cout << "OH NO " << portion << std::endl;
		}
	}
}

void Spite::SoftBody::impulse(glm::vec2 vel)
{
	_vel += vel;
}
