#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>


class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath = NULL, const char* fragmentPath = NULL);

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;
	void setMat4(const std::string& name, const float* value) const;
};

#endif