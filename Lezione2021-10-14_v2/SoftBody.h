#pragma once
#include "HermiteCurve.h"
#include "Point.h"
#include "Spring.h"
namespace Spite {
    class SoftBody :
        public HermiteCurve
    {
    private:
        static const int _rings = 2;
        const int _segments;
        const float _radius;
        std::vector<Point*> _points;
        std::vector<Spring*> _springs;
        glm::vec2 _force;
        glm::vec2 _vel;
        glm::vec4 _color;
    protected:
        void updateVao();
    public:
        SoftBody(int segments, double radius, glm::vec2 pos, float springForce);
        ~SoftBody();
        float getRadius();
        Point getCenter();
        void setColor(glm::vec4 c);
        void applyForce(glm::vec2 force);
        void update(float dt);
        void knockback(glm::vec2 position, float radius, glm::vec2 strength);
        void impulse(glm::vec2 vel);
        void draw();
    };
}
