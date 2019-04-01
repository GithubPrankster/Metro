#ifndef TEXHANDLER_H
#define TEXHANDLER_H

#include <glad/glad.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Texture {
public:
	unsigned int textureId;
	Texture(const char* name, GLenum rgbType, GLenum filterSpace) {
		stbi_set_flip_vertically_on_load(true);

		int width, height, nrChannels;
		unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 4);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Near Filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterSpace);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterSpace);

		glGenerateMipmap(GL_TEXTURE_2D);
		glGenerateTextureMipmap(textureId);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, rgbType, width, height, 0, rgbType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "The textureHandler did not appreciate this data screw-ery." << std::endl;
		}
		stbi_image_free(data);
	}
	Texture(std::vector<const char*> names, GLenum rgbType, GLenum filterSpace) {
		stbi_set_flip_vertically_on_load(false);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

		int width, height, nrChannels;
		for (int i = 0; i < names.size(); i++) {
			unsigned char *data = stbi_load(names[i], &width, &height, &nrChannels, 4);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, rgbType, width, height, 0, rgbType, GL_UNSIGNED_BYTE, data);
			}
			else
			{
				std::cout << "The textureHandler did not appreciate this data screw-ery with "<< names[i] << std::endl;
			}
			stbi_image_free(data);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filterSpace);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filterSpace);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		stbi_set_flip_vertically_on_load(true);
	}
	Texture() = default;
	void terminator() {
		glDeleteTextures(1, &textureId);
	}
};

#endif
//Leave as 0 if no texture.
void textureBind(unsigned int diffuse, int currentTexture, bool cubemap = false) {
	glActiveTexture(GL_TEXTURE0 + currentTexture);
	if (!cubemap) {
		glBindTexture(GL_TEXTURE_2D, diffuse);
	}
	else {
		glBindTexture(GL_TEXTURE_CUBE_MAP, diffuse);
	}	
}
//Create a cool icon and assign it.
void iconAssign(const char* path, GLFWwindow* window) {
	if (stbi_set_flip_vertically_on_load != 0) {
		stbi_set_flip_vertically_on_load(true);
	}
	int width, height, nrChannels;
	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	GLFWimage img;
	img.width = width, img.height = height, img.pixels = data;
	stbi_image_free(data);
	glfwSetWindowIcon(window, 1, &img);
}
