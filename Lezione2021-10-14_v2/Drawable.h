#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <stack>
#include <string>

#include "Model.h"
#include "Vertex.h"

#define  PI   3.141592653589793238465
namespace Spite {
	class Drawable
	{
	private:
		//OpenGL stuff
		GLuint _VAO;
		GLuint _VBO;
		GLuint _texture;
		GLenum _drawMode;

		//model matrix
		Model _model;
		std::stack<Model> _modelStack;

	protected:
		int _nTriangles;
		std::vector<Vertex> _vertexData;

		void setDrawMode(GLenum mode);
		void initVao(GLenum hint);
		void initVao(GLenum hint, GLuint size);
		void updateVao();
		Drawable(int n);
		Drawable(int n, GLenum hint);
		~Drawable();

	public:
		std::string _name;

		glm::vec2 getPos();
		glm::vec2 getScale();
		float getAngle();
		glm::vec2 getOffset();

		void setTexture(GLuint texture);

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


		void draw(void);
		void draw(glm::vec2 pos);
		void draw(glm::vec2 pos, glm::vec2 scale);
		void draw(glm::vec2 pos, glm::vec2 scale, float angle);
		void draw(glm::vec2 pos, glm::vec2 scale, float angle, glm::vec2 offset);
	};
}