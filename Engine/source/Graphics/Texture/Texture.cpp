#include "precompiled.hpp"
#include "Texture.hpp"

#include <iostream>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "Deps/stb_image.h"

Texture2D::Texture2D(const char* path)
{
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	mLocalPath = path;
}
Texture2D::~Texture2D() { glBindTexture(GL_TEXTURE_2D, 0); }

void Texture2D::Activate(int id) const { 
	glActiveTexture(GL_TEXTURE0 + id);
}
void Texture2D::Load(unsigned int internalFormat, unsigned int imgFormat) const {
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	int tWidth, tHeight, nrChannels;
	unsigned char* tData = stbi_load(mLocalPath.c_str(), &tWidth, &tHeight, &nrChannels, 0);

	if (tData) {
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tWidth, tHeight, 0, imgFormat, GL_UNSIGNED_BYTE, tData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to Load Texture" << std::endl;
	}
	stbi_image_free(tData);
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, mTextureID); }
void Texture2D::SetParams(unsigned int* params, int size) const {
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	for (int i = 0; i < size; i++) {
		glTexParameteri(GL_TEXTURE_2D, params[i + i], params[i + i + 1]);
	}
}
