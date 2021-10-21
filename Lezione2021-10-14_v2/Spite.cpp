#include <chrono>

#include "Spite.h"
#include "EmptyScene.h"
#include "ShaderMaker.h"

Spite::Spite::Spite()
{
	_scene = std::make_unique<EmptyScene>();
}

void Spite::Spite::start(int* argcp, char* argv[], int width, int height, const char* title, Scene *scene)
{
	glutInit(argcp, argv);

	glutInitContextVersion(4, 0);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(width, height);
	_width = width;
	_height = height;
	glutCreateWindow(title);
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
	loadScene(scene);
	glutMainLoop();
}

void Spite::Spite::loadScene(Scene *scene)
{
	_scene.reset(scene);
	_scene->load(_width, _height);
}

void Spite::Spite::sendModel(glm::mat4 model)
{
	glUniformMatrix4fv(glGetUniformLocation(_shader, "Model"), 1, GL_FALSE, value_ptr(model));
}

Spite::Spite &Spite::Spite::get()
{
	static Spite spite;
	return spite;
}

void Spite::Spite::timer(int a)
{
	static std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now(), oldTime = time;
	time = std::chrono::steady_clock::now();
	
	Spite::get()._scene->update(std::chrono::duration_cast<std::chrono::duration<float>>(time - oldTime).count());

	glutPostRedisplay();
	glutTimerFunc(16, Spite::Spite::timer, 0);
	oldTime = time;
}

void Spite::Spite::mouse(int button, int state, int x, int y)
{
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
	static int mx = 0, my = 0, first = 1;
	if (!first)
		Spite::get()._scene->mouseMoved(x, y, x - mx, y - my);
	first = 0;
	mx = x;
	my = y;
}

void Spite::Spite::draw()
{
	glutPostRedisplay();

	glClear(GL_COLOR_BUFFER_BIT);
	glUniformMatrix4fv(glGetUniformLocation(Spite::get()._shader, "Projection"), 1, GL_FALSE, value_ptr(Spite::get()._projection));
	Spite::get()._scene->draw();
	glutSwapBuffers();
}

void Spite::Spite::keyboard(unsigned char key, int x, int y)
{
	Spite::get()._scene->keyPressed(key);
}

void Spite::Spite::keyboardUp(unsigned char key, int x, int y)
{
	Spite::get()._scene->keyReleased(key);
}

void Spite::Spite::special(int key, int x, int y)
{
	Spite::get()._scene->keyPressed(key + 256);
}

void Spite::Spite::specialUp(int key, int x, int y)
{
	Spite::get()._scene->keyReleased(key + 256);
}

void Spite::Spite::reshape(int width, int height)
{
	Spite &s = Spite::get();
	s._scene->resize(width, height);
	s._width = width;
	s._height = height;
	s._projection = glm::ortho(0.0f, float(width), 0.0f, float(height));
}
