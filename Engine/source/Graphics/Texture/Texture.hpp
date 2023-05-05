#pragma once

#include <string>

class Texture2D
{
public:
	Texture2D(const char* path);
	~Texture2D();

	void Activate(int id) const;
	void Load(unsigned int internalFormat, unsigned int imgFormat) const;
	void Bind() const;
	void SetParams(unsigned int* params, int size) const;

	unsigned int ID() const { return mTextureID; }

private:
	unsigned int mTextureID;
	std::string mLocalPath;
};


