#include "MainScene.h"
#include "Rectangle.h"


void MainScene::load()
{
	Spite::Drawable *d;
	Spite::Rectangle *r = new Spite::Rectangle(4, [](int i, int n) { return glm::vec4(0.0); });
	//= new Rectangle(4, [](int i, int n) { return glm::vec4(0.0); });
}