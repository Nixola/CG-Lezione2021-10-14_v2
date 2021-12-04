#include <memory>
#include <iostream>
#include <set>
#include <limits>
#include <cstdlib>

#include <glm/gtx/transform.hpp>

#include "MainScene.h"
#include "Rectangle.h"
#include "Spite.h"
#include "Sprite.h"

#include "Texture.h"
#include "dirt4.h"

#define SEGMENTS 10
#define SPRINGFORCE 30
#define STEPS 3.f


MainScene::~MainScene()
{
	delete _player;
	delete _background;

	for (auto dis = _enemies.begin(); dis != _enemies.end(); dis++) {
		delete* dis;
	}
	for (auto dis = _lines.begin(); dis != _lines.end(); dis++) {
		delete* dis;
	}
}

void MainScene::load(const int screenWidth, const int screenHeight)
{
	_player = new Spite::SoftBody(SEGMENTS, 32, glm::vec2(0), SPRINGFORCE);
	_health.insert({ _player, 4 });
	_player->setColor({ 0.8,0.8,0.8,1.0 });
	_screenSize.x = screenWidth;
	_screenSize.y = screenHeight;
	_background = new Spite::Sprite(Texture::load<Texture::Dirt>());
	_background->setScale(_screenSize * 2.f);
	_background->setTextureCoordinates(glm::vec2(0.0), _screenSize / 256.f);

	_time = 0;

	Spite::Spite::get().setColor({ 1.0, 1.0, 1.0, 1.0 });
}

void MainScene::update(float dt)
{
	if (_dead || _pause) return;
	dt = std::min(dt, 1.f / 30.f);
	if ((float)rand() / (float)RAND_MAX > std::pow(0.1, dt)) {
		float a = (float)rand() / (float)RAND_MAX * 2 * PI;
		Spite::SoftBody* enemy = new Spite::SoftBody(SEGMENTS, 32, glm::vec2(std::cos(a), std::sin(a)) * glm::length(_screenSize) + _player->getPos(), SPRINGFORCE);
		_health.insert({ enemy, 3 });
		enemy->setColor({ 0.0, 0.8, 0.0, 1.0 });
		_enemies.push_back(enemy);
	}

	dt = dt / STEPS;
	for (int i = 0; i < STEPS; i++) {
		_time += dt;
		Spite::Spite& s = Spite::Spite::get();
		glm::vec2 force = glm::vec2(0, 0);
		if (s.isKeyDown('a')) {
			force.x -= 1;
		}
		if (s.isKeyDown('d')) {
			force.x += 1;
		}
		if (s.isKeyDown('s')) {
			force.y -= 1;
		}
		if (s.isKeyDown('w')) {
			force.y += 1;
		}
		force = glm::normalize(force) * 2000.f;
		if (force.x == force.x && force.y == force.y) {
			_player->applyForce(force);
		}
		std::set<Spite::SoftBody*> bodies(_enemies.begin(), _enemies.end());
		bodies.insert(_player);
		std::set<Spite::SoftBody*> updated;
		bool hit = false;
		for (auto e1 = bodies.begin(); e1 != bodies.end(); e1++) {
			updated.insert(*e1);
			if ((*e1) != _player) {
				glm::vec2 dir = glm::normalize(_player->getPos() - (*e1)->getPos());
				(*e1)->applyForce(dir * 1000.f);
			}
			for (auto e2 = bodies.begin(); e2 != bodies.end(); e2++) {
				if (updated.count(*e2) > 0) {
					continue;
				}
				glm::vec2 delta = (*e2)->getPos() - (*e1)->getPos();
				glm::vec2 dir = glm::normalize(delta);
				float radii = (*e2)->getRadius() + (*e1)->getRadius();
				float dist = glm::length(delta);
				if (dist * dist < radii * radii) {
					if (*e1 == _player || *e2 == _player) {
						hit = true;
					}
					glm::vec2 pointOfContact = (*e1)->getPos() + delta * (*e1)->getRadius() / radii;
					glm::vec2 deltaV = (*e1)->getCenter().getVelocity() - (*e2)->getCenter().getVelocity();
					float radius = std::cos((dist - std::max((*e1)->getRadius(), (*e2)->getRadius())) / std::min((*e1)->getRadius(), (*e2)->getRadius()) * PI / 2.f) * std::min((*e1)->getRadius(), (*e2)->getRadius()) + 5.f;
					glm::vec2 force = dir * (radii / dist + 0.1f) * 4500.f;
					(*e1)->knockback(pointOfContact, radius, -force);
					(*e2)->knockback(pointOfContact, radius, force);
				}
			}
		}
		if (hit) {
			float hp = (_health.find(_player)->second -= dt);
			if (hp <= 0) {
				hp = 0;
				_dead = true;
			}
			_player->setColor({ 0.8, hp / 5.f, hp / 5.f, 1.0 });
		}
		_player->update(dt);
		_cameraTarget = _player->getPos() - _screenSize / 2.f;

		glm::vec2 cameraDelta = _camera - _cameraTarget;
		_camera -= cameraDelta * (float)std::pow(0.001, dt);


		for (auto e1 = _enemies.begin(); e1 != _enemies.end(); e1++) {
			(*e1)->update(dt);
			glm::vec2 pos = (*e1)->getPos();
		}
		float invert = s.isKeyDown(32) ? -1 : 1;
		if (s.isKeyDown(256 + GLUT_KEY_LEFT)) {
			_player->knockback(_player->getPos() + glm::vec2(-32, 0), 10, glm::vec2(-3000, 0) * invert);
		}
		_background->setPos(-glm::mod(_camera, glm::vec2(512.f)));
		auto line = _lines.begin();
		while (line != _lines.end()) {
			(*line)->setColor((*line)->getColor() - glm::vec4(0, 0, 0, dt));
			if ((*line)->getColor().a < 0.0) {
				delete* line;
				line = _lines.erase(line);
			}
			else {
				line++;
			}
		}
	}
}

void MainScene::draw()
{
	Spite::Spite& s = Spite::Spite::get();
	if (_dead) {
		s.setColor({ 0.5, 0.5, 0.5, 1 });
	} else if (_pause) {
		s.setColor({ 0.75, 0.75, 0.75, 1 });
	}
	else {
		s.setColor({ 1,1,1,1 });
	}
	_background->draw();
	s.pushTransforms();
	s.translate(-_camera);
	(_player)->draw();
	for (auto e1 = _enemies.begin(); e1 != _enemies.end(); e1++) {
		(*e1)->draw();
	}
	for (auto l = _lines.begin(); l != _lines.end(); l++) {
		(*l)->draw();
	}
	s.popTransforms();


	GLuint err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << glewGetErrorString(err) << std::endl;
	}
}

void MainScene::mousePressed(const int b, const int x, const int y)
{
	if (_dead || _pause) return;
	static float lastShot = 0;
	switch (b) {
	case GLUT_RIGHT_BUTTON:
	{
		Spite::SoftBody* enemy = new Spite::SoftBody(SEGMENTS, 32, glm::vec2(x,  y) - _screenSize / 2.f + _player->getPos(), SPRINGFORCE);
		_health.insert({ enemy, 3 });
		enemy->setColor({ 0.0, 0.8, 0.0, 1.0 });
		_enemies.push_back(enemy);
		break;
	}
	case GLUT_LEFT_BUTTON:
		glm::vec2 pos = _player->getPos();
		glm::vec2 mouse = glm::vec2(x, y) + _camera;
		std::cout << mouse.x << " " << mouse.y << std::endl;
		if (_time - lastShot < 0.5f) return;
		lastShot = _time;
		if (pos == mouse) return;
		glm::vec2 dir = glm::normalize(mouse - pos);
		Spite::SoftBody *closest = nullptr;
		float closestDistance = std::numeric_limits<float>::infinity();
		float distanceToLine;

		for (auto e1 = _enemies.begin(); e1 != _enemies.end(); e1++) {
			glm::vec2 epos = (*e1)->getPos();
			float dot = glm::dot(epos - pos, dir);
			if (dot < 0) continue;
			float distance = std::abs((mouse.x - pos.x) * (pos.y - epos.y) - (pos.x - epos.x) * (mouse.y - pos.y)) / glm::length(mouse - pos);
			if (dot < closestDistance && distance < (*e1)->getRadius()) {
				closestDistance = dot;
				closest = (*e1);
				distanceToLine = distance;
			}
		}
		if (closest == nullptr) {
			_lines.push_back(new Spite::Line({ {pos, 0.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0 } }, { {pos + dir * glm::length(_screenSize), 0.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0} }));
			return;
		}
		glm::vec2 PoC = pos + dir * closestDistance - dir * std::sin(std::acos(distanceToLine / closest->getRadius())) * closest->getRadius();
		_lines.push_back(new Spite::Line({ {pos, 0.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0 } }, { {PoC, 0.0}, {1.0,1.0,1.0,1.0}, {0.0,0.0} }));
		closest->knockback(PoC, closest->getRadius(), dir * 100000.f);
		closest->applyForce(dir * 50000.f);
		auto hp = _health.find(closest);
		if (hp != _health.end()) {
			hp->second--;
			if (hp->second == 0) {
				_enemies.remove(closest);
			}
			else {
				std::cout << (3 - hp->second) * 0.4f << std::endl;
				closest->setColor({(3 - hp->second) * 0.4f, 0.8, 0.0, 1.0 });
			}
		}
		break;
	}
}

void MainScene::mouseReleased(const int b, const int x, const int y)
{
}

void MainScene::mouseMoved(const int x, const int y, const int dx, const int dy)
{
}

void MainScene::keyPressed(const int key)
{
}

void MainScene::keyReleased(const int key)
{
	switch (key) {
	case 27:
		if (_dead)
			glutLeaveMainLoop();
		_pause = !_pause;
		break;
	case 'r':
		if (_dead)
			Spite::Spite::get().loadScene(new MainScene());
		break;
	default:
		break;
	}
}

void MainScene::resize(const int width, const int height)
{
}