#include "MainScene.h"
#include "Rectangle.h"


void MainScene::load()
{
	Drawable *d;
	Rectangle r = new Rectangle(4, [](int i, int n) { return glm::vec4(0.0); });
	//= new Rectangle(4, [](int i, int n) { return glm::vec4(0.0); });
}