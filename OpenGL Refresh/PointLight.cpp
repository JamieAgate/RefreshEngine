#include "PointLight.h"
#include "GameObject.h"
#include "Shader.h"

PointLight::PointLight() :
	Light()
{

}


PointLight::~PointLight()
{

}

void PointLight::OnInit(std::shared_ptr<GameObject> _parent)
{
	m_lightConstant = 1.0f;
	m_lightLinear = 0.09f;
	m_lightQuadratic = 0.032f;
	Light::OnInit(_parent, 1);
}

void PointLight::OnInit()
{
}

void PointLight::OnBegin()
{
}

void PointLight::OnUpdate()
{
}

void PointLight::OnDisplay()
{
}

void PointLight::UploadLightData(std::shared_ptr<Shader> _shader)
{
	std::ostringstream os;
	std::string lightType = "";
	switch (m_lightType)
	{
	case e_PointLight:
		lightType = "pointLights[";
		break;
	case e_SpotLight:
		lightType = "spotLights[";
		break;
	}

	os.str("");
	os.clear();
	glm::vec3 pos = GetParent()->GetPosition();
	os << lightType << m_ID << "].position";
	_shader->SetVec3(os.str(), pos.x, pos.y, pos.z);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].constant";
	_shader->SetFloat(os.str(), m_lightConstant);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].linear";
	_shader->SetFloat(os.str(), m_lightLinear);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].quadratic";
	_shader->SetFloat(os.str(), m_lightQuadratic);

	Light::UploadLightData(_shader);
}
