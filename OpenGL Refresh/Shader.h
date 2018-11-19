#ifndef _SHADER_
#define _SHADER_

#include "glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>

#include "Resource.h"
#include "RefreshException.h"

class Shader : public Resource
{
public:
	Shader();
	~Shader();

	GLuint ID;

	void Load(std::string _vertexPath, std::string _fragPath);

	void Use();
	void SetBool(const std::string &_name, bool _value);
	void SetInt(const std::string &_name, int _value);
	void SetFloat(const std::string &_name, float _value);
	void SetVec2(const std::string &_name, float _x, float _y);
	void SetVec2(const std::string &_name, glm::vec2 _v);
	void SetVec3(const std::string &_name, float _x, float _y, float _z);
	void SetVec3(const std::string &_name, glm::vec3 _v);
	void SetVec4(const std::string &_name, float _x, float _y, float _z, float _w);
	void SetVec4(const std::string &_name, glm::vec4 _v);
	void SetMat2(const std::string &_name, glm::mat2 &_mat);
	void SetMat3(const std::string &_name, glm::mat3 &_mat);
	void SetMat4(const std::string &_name, glm::mat4 &_mat);
	void SetUniform(const std::string &_name);

private:
	void CheckCompileErrors(GLuint shader, std::string type);
};

#endif // !_SHADER_


