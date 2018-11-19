#ifndef _MESH_
#define _MESH_

#include <glm.hpp>
#include <string>
#include "glew.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Resource.h"
#include "RefreshException.h"

class Mesh : public Resource
{
public:
	Mesh();
	~Mesh();

	void Load(std::string _file) override;

	void Draw();

private:
	GLuint m_VAO;

	unsigned int m_numVertices;
};

#endif // !_MESH_


