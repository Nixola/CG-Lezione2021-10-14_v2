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
    void load();
    void update(float dt);
    void draw();
    void mousePressed(int b, int x, int y);
    void mouseReleased(int b, int x, int y);
    void mouseMoved(int x, int y, int dx, int dy);
    void keyPressed(int key);
    void keyReleased(int key);
};

