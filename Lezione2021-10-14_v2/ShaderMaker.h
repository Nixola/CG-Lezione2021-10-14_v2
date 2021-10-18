#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>

class ShaderMaker
{
public:
	static GLuint createProgram(char* vertexfilename, char* fragmentfilename);

private:
	ShaderMaker() { }
	static char* readShaderSource(const char* shaderFile);
};