#include "Shader.h"

Shader::Shader()
{

}


Shader::~Shader()
{
}

void Shader::Load(std::string _vertexPath, std::string _fragPath)
{
	std::string s = _vertexPath;
	s += ", ";
	s += _fragPath;
	m_path = s;

	std::string vertexCode;
	std::string fragCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(_vertexPath);
		fShaderFile.open(_fragPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Shader Error: File not succesfully read\n";
		throw RefreshException("Loading Default Shader \n", "Shaders / DefaultVertShader.txt, Shaders / DefaultFragShader.txt");
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragCode.c_str();

	unsigned int vertex, frag;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");

	frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag, 1, &fShaderCode, NULL);
	glCompileShader(frag);
	CheckCompileErrors(frag, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, frag);
	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(frag);
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string & _name, bool _value)
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), (int)_value);
}

void Shader::SetInt(const std::string & _name, int _value)
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), _value);
}

void Shader::SetFloat(const std::string & _name, float _value)
{
	glUniform1f(glGetUniformLocation(ID, _name.c_str()), _value);
}

void Shader::SetVec2(const std::string & _name, float _x, float _y)
{
	glUniform2f(glGetUniformLocation(ID, _name.c_str()), _x, _y);
}

void Shader::SetVec2(const std::string & _name, glm::vec2 _v)
{
	glUniform2f(glGetUniformLocation(ID, _name.c_str()), _v.x, _v.y);
}

void Shader::SetVec3(const std::string & _name, float _x, float _y, float _z)
{
	glUniform3f(glGetUniformLocation(ID, _name.c_str()), _x, _y, _z);
}

void Shader::SetVec3(const std::string & _name, glm::vec3 _v)
{
	glUniform3f(glGetUniformLocation(ID, _name.c_str()), _v.x, _v.y, _v.z);
}

void Shader::SetVec4(const std::string & _name, float _x, float _y, float _z, float _w)
{
	glUniform4f(glGetUniformLocation(ID, _name.c_str()), _x, _y, _z, _w);
}

void Shader::SetVec4(const std::string & _name, glm::vec4 _v)
{
	glUniform4f(glGetUniformLocation(ID, _name.c_str()), _v.x, _v.y, _v.z, _v.w);
}

void Shader::SetMat2(const std::string & _name, glm::mat2 & _mat)
{
	glUniformMatrix2fv(glGetUniformLocation(ID, _name.c_str()), 1, GL_FALSE, &_mat[0][0]);
}

void Shader::SetMat3(const std::string & _name, glm::mat3 & _mat)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, _name.c_str()), 1, GL_FALSE, &_mat[0][0]);
}

void Shader::SetMat4(const std::string & _name, glm::mat4 & _mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, _name.c_str()), 1, GL_FALSE, &_mat[0][0]);
}

void Shader::SetUniform(const std::string & _name)
{
	glUniform1i(glGetUniformLocation(ID, _name.c_str()), 0);
}



void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
