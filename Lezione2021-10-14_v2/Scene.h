#pragma once
namespace Spite {
	class Scene
	{
		virtual void load() = 0;
		virtual void update(float dt) = 0;
		virtual void draw() = 0;
		virtual void mousePressed(int button, int x, int y) = 0;
		virtual void mouseReleased(int button, int x, int y) = 0;
		virtual void mouseMoved(int x, int y, int dx, int dy) = 0;
		virtual void keyPressed(int key) = 0;
		virtual void keyReleased(int key) = 0;
	};
}