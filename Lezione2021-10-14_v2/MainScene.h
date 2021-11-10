#pragma once
#include <vector>
#include <memory>
#include "Scene.h"
#include "Drawable.h"

class MainScene :
    public Spite::Scene
{
private:
    std::vector<std::unique_ptr<Spite::Drawable>> _mountains;
    std::vector<std::unique_ptr<Spite::Drawable>> _fans;
    std::vector<std::unique_ptr<Spite::Drawable>> _poles;
    std::unique_ptr<Spite::Drawable> _sky;
    std::unique_ptr<Spite::Drawable> _grass;
    std::unique_ptr<Spite::Drawable> _ball;
    std::unique_ptr<Spite::Drawable> _shadow;
    std::unique_ptr<Spite::Drawable> _sun;
    std::unique_ptr<Spite::Drawable> _flare;
    glm::vec2 _screenSize;

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

