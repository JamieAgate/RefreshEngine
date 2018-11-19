#include "Light.h"
#include "GameObject.h"
#include "Core.h"
#include "Shader.h"

int Light::m_numberOfDirLights = 0;
int Light::m_numberOfPointLights = 0;
int Light::m_numberOfSpotLights = 0;

Light::Light() :
	Component()
{

}


Light::~Light()
{

}


void Light::OnInit(std::shared_ptr<GameObject> _parent, int _typeOfLight)
{
	SetParent(_parent);

	glm::mat4 lightProjMat = glm::mat4(1.0f), lightViewMat = glm::mat4(1.0f);
	float near =  1.0f, far = 7.5f;
	m_direction.x = glm::cos(glm::radians(GetRotation().y)) * glm::cos(glm::radians(GetRotation().x));
	m_direction.y = glm::sin(glm::radians(GetRotation().y));
	m_direction.z = glm::cos(glm::radians(GetRotation().y)) * glm::sin(glm::radians(GetRotation().z));
	m_direction = glm::normalize(m_direction);
	//m_direction = glm::radians(GetRotation());
	lightProjMat = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
	lightViewMat = glm::lookAt(m_direction * glm::vec3(5.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//lightViewMat = glm::translate(lightViewMat, GetPosition());
	//lightViewMat = glm::rotate(lightViewMat, m_direction.x , glm::vec3(1.0f, 0.0f, 0.0f)); 
	//lightViewMat = glm::rotate(lightViewMat, m_direction.y, glm::vec3(0.0f, 1.0f, 0.0f));
	//lightViewMat = glm::rotate(lightViewMat, m_direction.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_lightSpaceMatrix = lightProjMat * lightViewMat;

	switch (_typeOfLight)
	{
	case 0:
		m_ID = m_numberOfDirLights;
		m_numberOfDirLights++;
		m_lightType = e_DirLight;

		m_lightColour = glm::vec3(1.0f);
		m_lightAmbient = glm::vec3(0.05f, 0.05f, 0.05f);
		m_lightDiffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		m_lightSpecular = glm::vec3(0.5f, 0.5f, 0.5f);
		break;
	case 1:
		m_ID = m_numberOfPointLights;
		m_numberOfPointLights++;
		m_lightType = e_PointLight;

		m_lightColour = glm::vec3(1.0f);
		m_lightAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		m_lightDiffuse = glm::vec3(0.3f, 0.3f, 0.3f);
		m_lightSpecular = glm::vec3(0.7f, 0.7f, 0.7f);

		break;
	case 2:
		m_ID = m_numberOfSpotLights;
		m_numberOfSpotLights++;
		m_lightType = e_SpotLight;

		m_lightColour = glm::vec3(1.0f);
		m_lightAmbient = glm::vec3(0.5f, 0.5f, 0.5f);
		m_lightDiffuse = glm::vec3(0.3f, 0.3f, 0.3f);
		m_lightSpecular = glm::vec3(0.7f, 0.7f, 0.7f);

		m_direction = glm::vec3(-0.2f, -1.0f, -0.3f);
		break;
	}

	m_dataUploaded = false;
	GetParent()->GetCore()->SetIfLightingDataUploaded(false);
}

void Light::OnInit()
{
}

void Light::OnBegin()
{
}

void Light::OnUpdate()
{
	
}

void Light::OnDisplay()
{
}

void Light::UploadLightData(std::shared_ptr<Shader> _shader)
{
	_shader->SetInt("numberOfDirLights", m_numberOfDirLights);
	_shader->SetInt("numberOfPointLights", m_numberOfPointLights);
	_shader->SetMat4("lightSpaceMatrix", m_lightSpaceMatrix);
	std::ostringstream os;
	std::string lightType = "";
	glm::vec3 pos;

	os.str("");
	os.clear();

	switch (m_lightType)
	{
	case e_DirLight:
		lightType = "dirLights[";
		os << lightType << m_ID << "].direction";
		_shader->SetVec3(os.str(), m_direction.x, m_direction.y, m_direction.z);

		os.str("");
		os.clear();
		
		pos = m_direction * glm::vec3(10.0f);
		os << lightType << m_ID << "].position";
		_shader->SetVec3(os.str(), pos.x, pos.y,pos.z);

		break;
	case e_PointLight:
		lightType = "pointLights[";
		break;
	case e_SpotLight:
		lightType = "spotLights[";
		os << lightType << m_ID << "].direction";
		_shader->SetVec3(os.str(), m_direction.x, m_direction.y, m_direction.z);
		break;
	}

	os.str("");
	os.clear();

	os << lightType << m_ID << "].lightColour";
	_shader->SetVec3(os.str(), m_lightColour.x, m_lightColour.y, m_lightColour.z);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].ambient";
	_shader->SetVec3(os.str(), m_lightAmbient.x, m_lightAmbient.y, m_lightAmbient.z);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].diffuse";
	_shader->SetVec3(os.str(), m_lightDiffuse.x, m_lightDiffuse.y, m_lightDiffuse.z);

	os.str("");
	os.clear();
	os << lightType << m_ID << "].specular";
	_shader->SetVec3(os.str(), m_lightSpecular.x, m_lightSpecular.y, m_lightSpecular.z);

	m_dataUploaded = true;
}
