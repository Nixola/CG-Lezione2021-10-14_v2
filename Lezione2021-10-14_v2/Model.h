#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Model
{
private:
	glm::mat4 _matrix;

	glm::vec2 _pos;
	glm::vec2 _scale;
	float _angle;
	glm::vec2 _offset;
	void update(void);

public:
	glm::mat4 getMatrix();
	void translate(glm::vec2 pos);
	void scale(glm::vec2 scale);
	void rotate(float angle);
	void offset(glm::vec2 offset);
	void transform(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset);

	void setPos(glm::vec2 pos);
	void setScale(glm::vec2 scale);
	void setAngle(float angle);
	void setOffset(glm::vec2 offset);
	void set(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset);

	Model(void);
	Model(glm::vec2 pos);
	Model(glm::vec2 pos, glm::vec2 scale);
	Model(glm::vec2 pos, glm::vec2 scale, float angle);
	Model(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset);
};

