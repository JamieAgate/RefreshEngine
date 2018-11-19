#include "Material.h"



Material::Material()
{

}


Material::~Material()
{

}


void Material::Load(std::string _path)
{
	m_path = _path;

	std::vector<unsigned char>image;
	unsigned width, hieght;
	unsigned error = lodepng::decode(image, width, hieght, _path.c_str());
	if (error != 0)
	{
		std::cout << "Error: " << error << ": " << lodepng_error_text(error) << std::endl;
		throw RefreshException("Loading Default \n", "Textures / Default.png");
	}

	glGenTextures(1, &m_diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, hieght, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Material::UploadMaterialData(std::shared_ptr<Shader> _shader)
{
	_shader->Use();

	_shader->SetVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	_shader->SetVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	_shader->SetVec3("material.specular", 0.5f, 0.5f, 0.5f);
	_shader->SetFloat("material.shininess", 16.0f);
	_shader->SetInt("material.diffuse", 0);
	_shader->SetInt("material.specular", 1);
	_shader->SetInt("shadowMap", 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
}


void Material::Draw(std::shared_ptr<Shader> _shader, glm::mat4 _modelMat, glm::mat4 _viewMat, glm::mat4 _projMat, glm::vec3 _camPos)
{
	_shader->Use();

	_shader->SetMat4("model", _modelMat);
	_shader->SetMat4("view", _viewMat);
	_shader->SetMat4("projection", _projMat);
	_shader->SetVec3("viewPos", _camPos.x, _camPos.y, _camPos.z);
}

void Material::Draw(glm::mat4 _modelMat, std::shared_ptr<Shader> _shader)
{
	_shader->Use();
	_shader->SetMat4("model", _modelMat);
}
