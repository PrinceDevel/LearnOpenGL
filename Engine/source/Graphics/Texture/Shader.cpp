#include "precompiled.hpp"
#include "Shader.hpp"

#include <glad/glad.h>
#include <string>
#include <fstream>

Shader::Shader(const char* VertPath, const char* FragPath) {
	
	std::string vertSrc, fragSrc;
	std::ifstream vertShaderFile, fragShaderFile;


	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vertShaderFile.open(VertPath);
        fragShaderFile.open(FragPath);
        std::stringstream vertStream, fragStream;
        // read file's buffer contents into streams
        vertStream << vertShaderFile.rdbuf();
        fragStream << fragShaderFile.rdbuf();
        // close file handlers
        vertShaderFile.close();
        fragShaderFile.close();
        // convert stream into string
        vertSrc = vertStream.str();
        fragSrc = fragStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE NOT SUCCESFULLY READ" << std::endl;
    }

	unsigned int VS, FS;
	int success;
	char infoLog[512];
	const char* vertCode = vertSrc.c_str();
	const char* fragCode = fragSrc.c_str();

	// Creating Vertex Shader
	VS = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VS, 1, &vertCode, NULL);
	glCompileShader(VS); // Compiling VS
	glGetShaderiv(VS, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(VS, 512, NULL, infoLog);
		std::cout << "Error: Unable to load Vertex Shader" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Creating Vertex Shader
	FS = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FS, 1, &fragCode, NULL);
	glCompileShader(FS); // Compiling VS
	glGetShaderiv(FS, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(FS, 512, NULL, infoLog);
		std::cout << "Error: Unable to load Fragment Shader" << std::endl;
		std::cout << infoLog << std::endl;
	}



	// Create Shader Program, Attach and Link Shader
	mShaderID = glCreateProgram();
	glAttachShader(mShaderID, VS);
	glAttachShader(mShaderID, FS);

	glLinkProgram(mShaderID);
	glGetProgramiv(mShaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(mShaderID, 512, NULL, infoLog);
		std::cout << "Error: Unable to link Shader Program" << std::endl;
		std::cout << infoLog << std::endl;
	}

	// Cleaning Up
	glDeleteShader(VS);
	glDeleteShader(FS);
}
Shader::~Shader() {
	glUseProgram(mShaderID);
}

void Shader::Use() const {
	glUseProgram(mShaderID);
}

void Shader::setBool(const char* name, bool value) const {
	glUniform1i (
		glGetUniformLocation(mShaderID, name),
		(int) value
	);
}
void Shader::setInt(const char* name, int value) const {
	glUniform1i(
		glGetUniformLocation(mShaderID, name),
		value
	);
}
void Shader::setFloat(const char* name, float value) const {
	glUniform1f(
		glGetUniformLocation(mShaderID, name),
		value
	);
}

void Shader::setVec3(const char* name, float x, float y, float z) const {
	glUniform3f(
		glGetUniformLocation(mShaderID, name),
		x, y, z
	);
}
void Shader::setVec4(const char* name, float x, float y, float z, float w) const {
	glUniform4f(
		glGetUniformLocation(mShaderID, name),
		x, y, z, w
	);
}
void Shader::setMat4(const char* name, float* matStart) const {
	glad_glUniformMatrix4fv(
		glGetUniformLocation(mShaderID, name),
		1, GL_FALSE,
		matStart
	);
}

void Shader::setVec3(const char* name, const Vec3F& vector) const {
	glUniform3f(
		glGetUniformLocation(mShaderID, name),
		vector.x, vector.y, vector.z
	);
}
void Shader::setVec4(const char* name, const Vec4F& vector) const {
	glUniform4f(
		glGetUniformLocation(mShaderID, name),
		vector.x, vector.y, vector.z, vector.w
	);
}
void Shader::setMat4(const char* name, const Mat4F& matrix) const {
	glad_glUniformMatrix4fv(
		glGetUniformLocation(mShaderID, name),
		1, GL_FALSE,
		glmValue(matrix)
	);
}