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

#define  PI   3.141592653589793238465

class Drawable
{
private:
	//OpenGL stuff
	GLuint _VAO;
	GLuint _geometryVBO;
	GLuint _colorVBO;
	GLenum _drawMode;

	//model matrix
	Model _model;
	std::stack<Model> _modelStack;

protected:
	int _nTriangles;
	std::vector<glm::vec3> _vertices;
	std::vector<glm::vec4> _colors;

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

