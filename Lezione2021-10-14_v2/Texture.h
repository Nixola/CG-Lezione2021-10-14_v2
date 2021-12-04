#pragma once
#include <GL/glew.h>

namespace Texture {
	template<class T>
	GLuint load() {
		unsigned char buffer[T::width * T::height * 3];
		unsigned char* head = buffer;
		for (unsigned char* i = (unsigned char *) T::header_data; i < T::header_data + sizeof(T::header_data); i++) {
			head++[0] = T::header_data_cmap[i[0]][0];
			head++[0] = T::header_data_cmap[i[0]][1];
			head++[0] = T::header_data_cmap[i[0]][2];
		}
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, T::width, T::height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		return texture;
	}
}