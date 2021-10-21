#include <memory>
#include <iostream>
#include "MainScene.h"
#include "Rectangle.h"
#include "Drawable.h"
#include "Circle.h"
#include "Mountain.h"

void MainScene::load(const int screenWidth, const int screenHeight)
{
	Spite::Rectangle *sky = new Spite::Rectangle(4, [](int i, int n) { return (i%2==0) ? glm::vec4(0.3, 0.7, 1.0, 1.0) : glm::vec4(0.5, 0.0, 1.0, 1.0); });
	sky->set(glm::vec2(0.0, screenHeight / 2.0), glm::vec2(screenWidth, screenHeight / 2.0), 0, glm::vec2(0.0));
	_drawables.push_back(std::unique_ptr<Spite::Drawable>(sky));

	Spite::Rectangle* grass = new Spite::Rectangle(4, [](int i, int n) { return (i + 1 == n) ? glm::vec4(0.7, 1.0, 0.0, 1.0) : glm::vec4(0.0, 0.5, 0.0, 1.0); });
	grass->set(glm::vec2(0.0, 0.0), glm::vec2(screenWidth, screenHeight / 2.0), 0, glm::vec2(0.0));
	_drawables.push_back(std::unique_ptr<Spite::Drawable>(grass));

	for (int i = 0; i < 6; i++) {
		float x = screenWidth / 6.0 * i;
		Spite::Drawable* mountain = new Spite::Mountain(30, [](int i, int n) {return (i % 2 == 0) ? glm::vec4(0.7, 0.5, 0.1, 1.0) : glm::vec4(0.35, 0.1, 0.0, 1.0); });
		mountain->set(glm::vec2(x, screenHeight / 2.0), glm::vec2(screenWidth / 6.0, 80.0), 0, glm::vec2(0.0));
		std::cout << x << std::endl;
		_drawables.push_back(std::unique_ptr<Spite::Drawable>(mountain));
	}
}

void MainScene::update(const float dt)
{
	
}

void MainScene::draw()
{
	for (const auto &it : _drawables) {
		it->draw();
	}
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