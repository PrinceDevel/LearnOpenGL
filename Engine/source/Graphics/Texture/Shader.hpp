#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include "Maths.hpp"  

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader 
{
public:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    // use/activate the shader
    void Use() const;
    unsigned int ID() { return mShaderID; }

    // utility uniform functions
    void setBool(const char* name, bool value) const;  
    void setInt(const char* name, int value) const;   
    void setFloat(const char* name, float value) const;

    void setVec3(const char* name, float x = 0, float y = 0, float z = 0) const;
    void setVec4(const char* name, float x = 0, float y = 0, float z = 0, float w = 0) const;
    void setMat4(const char* name, float* matStart) const;

    void setVec3(const char* name, const Vec3F& vector) const;
    void setVec4(const char* name, const Vec4F& vector) const;
    void setMat4(const char* name, const Mat4F& matrix) const;

private:
    unsigned int mShaderID;
    
};