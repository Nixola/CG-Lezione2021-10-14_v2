#pragma once
namespace Spite {
	class Scene
	{
	public:
		virtual void load(const int screenWidth, const int screenHeight) = 0;
		virtual void update(const float dt) = 0;
		virtual void draw() = 0;
		virtual void mousePressed(const int button, const int x, const int y) = 0;
		virtual void mouseReleased(const int button, const int x, const int y) = 0;
		virtual void mouseMoved(const int x, const int y, const int dx, const int dy) = 0;
		virtual void keyPressed(const int key) = 0;
		virtual void keyReleased(const int key) = 0;
		virtual void resize(const int width, const int height) = 0;
	};
}