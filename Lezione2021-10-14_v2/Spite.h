#pragma once
#include <memory>
#include <set>
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "wglext.h"
#include "Scene.h"
namespace Spite {
	class Spite
	{
	private:
		Spite();
		std::unique_ptr<Scene> _scene;
		std::set<int> _keys;
		glm::vec2 _mouse;

		int _width;
		int _height;

		GLuint _emptyTexture;

		glm::mat4 _projection;
		glm::mat4 _transforms;
		std::stack<glm::mat4> _transformStack;
		GLuint _shader;

		void initEmptyTexture();

		static void timer(int a);
		static void draw(void);

		static void mouse(int button, int state, int x, int y);
		static void motion(int x, int y);

		static void keyboard(unsigned char key, int x, int y);
		static void keyboardUp(unsigned char key, int x, int y);
		static void special(int key, int x, int y);
		static void specialUp(int key, int x, int y);

		static void reshape(int width, int height);

		void updateMatrix();

	public:
		Spite(Spite const&) = delete;
		void operator=(Spite const&) = delete;
		static Spite& get();

		void start(int* argcp, char* argv[], const int width, const int height, const char* title, Scene *scene);
		void sendModel(glm::mat4 model);
		void loadScene(Scene *scene);
		bool isKeyDown(const int key);
		glm::vec2 getMousePosition();
		void translate(glm::vec2 t);
		void origin();
		void pushTransforms();
		void popTransforms();
		GLuint getEmptyTexture();
		void setColor(glm::vec4 c);
		void setShader(GLuint shader);
		void setShader();
	};
}