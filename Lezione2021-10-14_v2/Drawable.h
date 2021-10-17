#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stack>
#include "Model.h"

class Drawable
{
private:
	//OpenGL stuff
	GLuint VAO;
	GLuint geometryVBO;
	GLuint colorVBO;
	GLenum drawMode;

	//model matrix
	Model model;
	std::stack<Model> modelStack;

protected:
	int nTriangles;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colors;

	void setDrawMode(GLenum mode);
	void initVao(void);
	Drawable(int n);

public:
	char* _name;


	void draw(void);
	void draw(glm::vec2 pos);
	void draw(glm::vec2 pos, glm::vec2 scale);
	void draw(glm::vec2 pos, glm::vec2 scale, float angle);
	void draw(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset);
};

