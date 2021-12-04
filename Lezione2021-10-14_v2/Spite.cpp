#include <chrono>
#include <ctype.h>

#include "Spite.h"
#include "EmptyScene.h"
#include "ShaderMaker.h"

#include <iostream>

Spite::Spite::Spite()
{
	_scene = std::make_unique<EmptyScene>();
}

void Spite::Spite::start(int* argcp, char* argv[], int width, int height, const char* title, Scene *scene)
{
	glutInit(argcp, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);


	glutInitWindowSize(width, height);
	_width = width;
	_height = height;
	glutCreateWindow(title);
	std::cout << "HEY" << std::endl;
	glutDisplayFunc(Spite::Spite::draw);
	glutTimerFunc(16, Spite::Spite::timer, 0);
	
	glutMouseFunc(Spite::Spite::mouse);
	glutMotionFunc(Spite::Spite::motion);
	glutPassiveMotionFunc(Spite::Spite::motion);

	glutKeyboardFunc(Spite::Spite::keyboard);
	glutKeyboardUpFunc(Spite::Spite::keyboardUp);
	glutSpecialFunc(Spite::Spite::special);
	glutSpecialUpFunc(Spite::Spite::specialUp);

	glutReshapeFunc(Spite::Spite::reshape);

	glewExperimental = GL_TRUE;
	glewInit();
	//TODO: setShader
	GLenum ErrorCheckValue = glGetError();
	_shader = ShaderMaker::createProgram("vertexShader_M.glsl", "fragmentShader_M.glsl");
	glUseProgram(_shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	_projection = glm::ortho(0.0f, float(width), 0.0f, float(height));
	_transforms = glm::mat4(1.0);
	
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalExt = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalExt(1);

	initEmptyTexture();
	loadScene(scene);
	glActiveTexture(GL_TEXTURE0);
	glutTimerFunc(0, Spite::Spite::timer, 0);
	setColor({ 1.0, 1.0, 1.0, 1.0 });
	glutMainLoop();
}

void Spite::Spite::loadScene(Scene *scene)
{
	_scene.reset(scene);
	_scene->load(_width, _height);
}

bool Spite::Spite::isKeyDown(const int key)
{
	return _keys.count(key) > 0;
}

glm::vec2 Spite::Spite::getMousePosition()
{
	return _mouse;
}


void Spite::Spite::sendModel(glm::mat4 model)
{
	glUniformMatrix4fv(glGetUniformLocation(_shader, "Model"), 1, GL_FALSE, value_ptr(model));
}

void Spite::Spite::setColor(glm::vec4 c)
{
	glUniform4fv(glGetUniformLocation(_shader, "color"), 1, value_ptr(c));
	std::cout << "COLOR" << std::endl;
}

Spite::Spite &Spite::Spite::get()
{
	static Spite spite;
	return spite;
}

void Spite::Spite::initEmptyTexture()
{
	glGenTextures(1, &_emptyTexture);
	glBindTexture(GL_TEXTURE_2D, _emptyTexture);
	unsigned char white[] = { 255, 255, 255 };
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, white);
}

void Spite::Spite::timer(int a)
{
	static std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now(), oldTime = time;
	time = std::chrono::steady_clock::now();
	
	Spite::get()._scene->update(std::chrono::duration_cast<std::chrono::duration<float>>(time - oldTime).count());

	std::chrono::steady_clock::time_point time2 = std::chrono::steady_clock::now();
	//std::cout << "Update:\t" << std::chrono::duration_cast<std::chrono::duration<float>>(time2 - time).count() << std::endl;

	glutPostRedisplay();
	//glutTimerFunc(16, Spite::Spite::timer, 0);
	oldTime = time;
}

void Spite::Spite::mouse(int button, int state, int x, int y)
{
	y = get()._height - y;
	switch (state) {
	case GLUT_DOWN:
		Spite::get()._scene->mousePressed(button, x, y);
		break;
	case GLUT_UP:
		Spite::get()._scene->mouseReleased(button, x, y);
		break;
	}
}

void Spite::Spite::motion(int x, int y)
{
	y = get()._height - y;
	static int first = 1;
	if (!first)
		Spite::get()._scene->mouseMoved(x, y, x - Spite::get()._mouse.x, y - Spite::get()._mouse.y);
	first = 0;
	Spite::get()._mouse.x = x;
	Spite::get()._mouse.y = y;
}

void Spite::Spite::draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Spite::get().updateMatrix();
	std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
	Spite::get()._scene->draw();
	std::chrono::steady_clock::time_point time2 = std::chrono::steady_clock::now();
	//std::cout << "Draw:\t" << std::chrono::duration_cast<std::chrono::duration<float>>(time2 - time).count() << std::endl;
	glutSwapBuffers();

	GLenum err;
	while (1) {
		err = glGetError();
		if (err != GL_NO_ERROR) {
			std::cout << gluErrorStringWIN(err) << std::endl;
		}
		else {
			break;
		}
	}
	//glutTimerFunc(1, Spite::Spite::timer, 0);
	Spite::Spite::timer(0);
}

void Spite::Spite::keyboard(unsigned char key, int x, int y)
{
	key = tolower(key);
	Spite::get()._keys.insert(key);
	Spite::get()._scene->keyPressed(key);
}

void Spite::Spite::keyboardUp(unsigned char key, int x, int y)
{
	key = tolower(key);
	Spite::get()._keys.erase(key);
	Spite::get()._scene->keyReleased(key);
}

void Spite::Spite::special(int key, int x, int y)
{
	key = key + 256;
	Spite::get()._keys.insert(key);
	Spite::get()._scene->keyPressed(key);
}

void Spite::Spite::specialUp(int key, int x, int y)
{
	key = key + 256;
	Spite::get()._keys.erase(key);
	Spite::get()._scene->keyReleased(key + 256);
}

void Spite::Spite::reshape(int width, int height)
{
	Spite &s = Spite::get();
	s._scene->resize(width, height);
	s._width = width;
	s._height = height;
	s._projection = glm::ortho(0.0f, float(width), 0.0f, float(height));
	glViewport(0, 0, width, height);
	s.updateMatrix();
}

void Spite::Spite::updateMatrix()
{
	glm::mat4 matrix = _projection * _transforms;
	glUniformMatrix4fv(glGetUniformLocation(_shader, "Projection"), 1, GL_FALSE, value_ptr(matrix));
}

void Spite::Spite::translate(glm::vec2 t)
{
	_transforms = glm::translate(_transforms, glm::vec3(t, 0.0));
	updateMatrix();
}

void Spite::Spite::origin()
{
	_transforms = glm::mat4(1.0);
}

void Spite::Spite::pushTransforms()
{
	_transformStack.push(_transforms);
}

void Spite::Spite::popTransforms()
{
	_transforms = _transformStack.top();
	_transformStack.pop();
	updateMatrix();
}

GLuint Spite::Spite::getEmptyTexture()
{
	return _emptyTexture;
}
