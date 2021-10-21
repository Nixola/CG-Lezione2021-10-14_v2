#pragma once
#include "Scene.h"
namespace Spite {
    class EmptyScene :
        public Scene
    {
	public:
		void load(const int w, const int h);
		void update(const float dt);
		void draw();
		void mousePressed(const int b, const int x, const int y);
		void mouseReleased(const int b, const int x, const int y);
		void mouseMoved(const int x, const int y, const int dx, const int dy);
		void keyPressed(const int k);
		void keyReleased(const int k);
		void resize(const int w, const int h);

		EmptyScene();
    };

}