#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
namespace Spite {
	class ShaderMaker
	{
	public:
		static GLuint createProgram(const char* vertexfilename, const char* fragmentfilename);

	private:
		ShaderMaker() { }
		static char* readShaderSource(const char* shaderFile);
	};
}