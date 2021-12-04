#pragma once
#include <vector>
#include <list>
#include <memory>
#include <map>
#include "Scene.h"
#include "Drawable.h"
#include "SoftBody.h"
#include "Sprite.h"
#include "Line.h"

class MainScene :
    public Spite::Scene
{
private:
    Spite::SoftBody *_player;
    bool _dead;
    bool _pause;
    Spite::Sprite *_background;
    float _time;
    std::list<Spite::SoftBody*> _enemies;
    glm::vec2 _screenSize;
    glm::vec2 _camera;
    glm::vec2 _cameraTarget;
    std::vector<Spite::Line*> _lines;
    std::map<Spite::SoftBody*, float> _health;

public:
    ~MainScene();
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

