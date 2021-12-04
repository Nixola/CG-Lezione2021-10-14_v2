#pragma once
#include <glm/glm.hpp>
namespace Spite {
	class Point
	{
	private:
		glm::vec2 _position;
		glm::vec2 _velocity;
		glm::vec2 _force;
	public:
		Point(glm::vec2 pos);
		void applyForce(glm::vec2 force);
		void applyImpulse(glm::vec2 impulse);
		glm::vec2 getPosition();
		void setPosition(glm::vec2 pos);
		glm::vec2 getVelocity();
		void setVelocity(glm::vec2 vel);
		void update(float dt);
	};
}
