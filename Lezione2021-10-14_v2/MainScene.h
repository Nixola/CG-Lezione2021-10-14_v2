#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Drawable.h"

class MainScene :
    public Spite::Scene
{
private:
    std::vector<std::unique_ptr<Spite::Drawable>> _drawables;
public:
    void load(const int screenWidth, const int screenHeight);
    void update(const float dt);
    void draw();
    void mousePressed(const int b, const int x, const int y);
    void mouseReleased(const int b, const int x, const int y);
    void mouseMoved(const int x, const int y, const int dx, const int dy);
    void keyPressed(const int key);
    void keyReleased(const int key);
    void resize(const int w, const int h);
};

