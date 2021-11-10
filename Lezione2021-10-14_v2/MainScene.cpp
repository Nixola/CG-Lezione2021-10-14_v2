#include <memory>
#include <iostream>
#include "MainScene.h"
#include "Rectangle.h"
#include "Drawable.h"
#include "Circle.h"
#include "Mountain.h"
#include "Fan.h"
#include "Spite.h"

void MainScene::load(const int screenWidth, const int screenHeight)
{
	_screenSize = glm::vec2(screenWidth, screenHeight);
	_sky.reset(new Spite::Rectangle(4, [](int i, int n) { return (i%2==0) ? glm::vec4(0.3, 0.7, 1.0, 1.0) : glm::vec4(0.5, 0.0, 1.0, 1.0); }));
	_sky->set(glm::vec2(0.0, screenHeight / 2.0), glm::vec2(screenWidth, screenHeight / 2.0), 0, glm::vec2(0.0));

	_grass.reset(new Spite::Rectangle(4, [](int i, int n) {return (i + 1 == n) ? glm::vec4(0.7, 1.0, 0.0, 1.0) : glm::vec4(0.0, 0.5, 0.0, 1.0); }));
	_grass->set(glm::vec2(0.0, 0.0), glm::vec2(screenWidth, screenHeight / 2.0), 0, glm::vec2(0.0));

	for (int i = 0; i < 6; i++) {
		Spite::Drawable *mountain = new Spite::Mountain(30, [](int i, int n) {return (i % 2 == 0) ? glm::vec4(0.7, 0.5, 0.1, 1.0) : glm::vec4(0.35, 0.1, 0.0, 1.0); });
		mountain->set(glm::vec2(screenWidth / 6.0 * i, screenHeight / 2.0), glm::vec2(screenWidth / 6.0, 80.0), 0, glm::vec2(0.0));
		_mountains.push_back(std::unique_ptr<Spite::Drawable>(mountain));

		Spite::Drawable *pole = new Spite::Rectangle(4, [](int i, int n) {return (i % 2 == 0) ? glm::vec4(0.0, 0.6, 0.0, 1.0) : glm::vec4(0.0, 1.0, 0.0, 1.0); });
		pole->set(glm::vec2(screenWidth / 7.0 * (i + 1), screenHeight / 2.0 + 20), glm::vec2(3.0, 80.0), 0, glm::vec2(1.5, 0.0));
		_poles.push_back(std::unique_ptr<Spite::Drawable>(pole));

		Spite::Drawable* fan = new Spite::Fan([](int i, int n) {return (i % 3 == 0) ? glm::vec4(0.0, 1.0, 0.0, 1.0) : glm::vec4(1.0, 0.8, 0.0, 1.0); });
		fan->set(pole->getPos() + glm::vec2(0.0, 80.0), glm::vec2(40.0), rand(), glm::vec2(0.0));
		_fans.push_back(std::unique_ptr<Spite::Drawable>(fan));
	}

	_ball.reset(new Spite::Circle(50, [](int i, int n) { return i == -1 ? glm::vec4(1.0, 0.9, 0.0, 1.0) : glm::vec4(1.0, 0.0, 0.0, 1.0); }));
	_ball->set(glm::vec2(screenWidth / 2.0 - 40.0, screenHeight / 5.0), glm::vec2(50.0), 0, glm::vec2(0.0));

	_shadow.reset(new Spite::Circle(50, [](int i, int n) { return i == -1 ? glm::vec4(0.0, 0.0, 0.0, 0.6) : glm::vec4(0.0); }));
	_shadow->set(_ball->getPos() - glm::vec2(0, 40), glm::vec2(50.0, 35.0), 0, glm::vec2(0.0));

	_sun.reset(new Spite::Circle(50, [](int i, int n) { return i == -1 ? glm::vec4(1.0, 1.0, 0.0, 1.0) : glm::vec4(1.0); }));
	_sun->set(glm::vec2(screenWidth / 2.0, screenHeight / 5.0 * 4.0), glm::vec2(40.0), 0, glm::vec2(0.0));

	_flare.reset(new Spite::Circle(50, [](int i, int n) { return i == -1 ? glm::vec4(1.0, 1.0, 0.0, 1.0) : glm::vec4(1.0, 1.0, 1.0, 0.0); }));
	_flare->set(_sun->getPos(), glm::vec2(80.0), 0, glm::vec2(0.0));
}

void MainScene::update(const float dt)
{
	Spite::Spite &s = Spite::Spite::get();
	static float timer = 0;
	timer += dt;

	for (const auto& it : _fans) {
		it->rotate(1.0 * dt);
	}
	glm::vec2 ballPos = _ball->getPos();
	float t = (((int)(timer * 1000.0)) % 2000) / 1000.0;
	float baseHeight = _screenSize.y / 5.0;
	float ballHeight = baseHeight + 500 * t - 250 * t * t;
	ballPos.y = ballHeight;
	if (s.isDown('a') || s.isDown(GLUT_KEY_LEFT + 256)) {
		ballPos.x -= 200.0 * dt;
	}
	if (s.isDown('d') || s.isDown(GLUT_KEY_RIGHT + 256)) {
		ballPos.x += 200.0 * dt;
	}
	ballPos.x = std::max(std::min(ballPos.x, _screenSize.x - 50.0f), 50.0f);
	_ball->setPos(ballPos);
	
	float ballScale = std::min(ballHeight / 200.0, 1.0);
	_ball->setScale(glm::vec2(50.0 / ballScale, 50.0 * ballScale));
	float shadowScale = ballHeight / baseHeight / 1.8;
	_shadow->setPos(glm::vec2(ballPos.x, baseHeight - ballHeight / 10.0));
	_shadow->setScale(glm::vec2(50.0 * shadowScale, 35.0 * shadowScale));
}

void MainScene::draw()
{
	_sky->draw();
	_grass->draw();
	for (const auto &it : _mountains) {
		it->draw();
	}
	for (const auto& it : _poles) {
		it->draw();
	}
	for (const auto& it : _fans) {
		it->draw();
	}
	_shadow->draw();
	_ball->draw();
	_flare->draw();
	_sun->draw();
}

void MainScene::mousePressed(const int b, const int x, const int y)
{
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
}

void MainScene::resize(const int width, const int height)
{
}