#pragma once
#include "Point.h"
namespace Spite {
	class Spring
	{
	private:
		Point* _p1;
		Point* _p2;
		Point _base;
		bool _fixed;
		float _restingLength;
		float _forceCoefficient;
		float _dampingCoefficient;
	public:
		Spring(Point* p1, Point* p2, float forceCoefficient, float dampingCoefficient);
		Spring(Point* p1, float forceCoefficient, float dampingCoefficient);
		void update();
	};
}
