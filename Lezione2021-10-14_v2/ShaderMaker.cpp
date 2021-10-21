
#include "ShaderMaker.h"
#include <iostream>
#include <fstream>

#pragma warning(disable:4996)
char* Spite::ShaderMaker::readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");

	if (fp == NULL) { return NULL; }

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

GLuint Spite::ShaderMaker::createProgram(const char* vertexfilename, const char* fragmentfilename)
{
	GLenum ErrorCheckValue = glGetError();
	int success;
	char infoLog[512];


	glClearColor(0.0, 0.0, 0.0, 0.0);

	//Read the vertex shader source
	GLchar* VertexShader = readShaderSource(vertexfilename);
	//Print it
	//std::cout << VertexShader;

	//Generate an ID for our shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	//Bind the shader source code to our ID
	glShaderSource(vertexShaderId, 1, (const char**)&VertexShader, NULL);
	//Compile shader
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}



	//Read the fragment shader source
	const GLchar* FragmentShader = readShaderSource(fragmentfilename);
	//Print it
	//std::cout << FragmentShader;

	//Generate an ID for the shader and bind its code to it
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, (const char**)&FragmentShader, NULL);
	//Compile shader
	glCompileShader(fragmentShaderId);


	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	ErrorCheckValue = glGetError();
	std::cout << ErrorCheckValue;

	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create the shaders: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		exit(-1);
	}
	//Create an ID for the shader program
	GLuint programId = glCreateProgram();

	//Bind the shaders to it and link it
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);

	return programId;
}
