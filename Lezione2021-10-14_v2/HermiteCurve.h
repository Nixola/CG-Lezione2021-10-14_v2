#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "Drawable.h"

#define PHI0(t)  (2.0*t*t*t-3.0*t*t+1)
#define PHI1(t)  (t*t*t-2.0*t*t+t)
#define PSI0(t)  (-2.0*t*t*t+3.0*t*t)
#define PSI1(t)  (t*t*t-t*t)
namespace Spite {
    class HermiteCurve :
        public Drawable
    {
    private:
        int _segments;
        glm::vec2 derivative(int i);
        glm::vec2 derivative(int i, float tens, float bias, float cont);

    protected:
        std::vector<glm::vec2> _controlPoints;

    public:
        HermiteCurve(std::vector<glm::vec2>& points, int segments, GLuint hint);
        HermiteCurve(int segments, GLuint hint);
        void setControlPoints(std::vector<glm::vec2>& controlPoints);
        void interpolate(glm::vec4 color);

    };

}