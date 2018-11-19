#ifndef _LIGHT_
#define _LIGHT_

#include <glm.hpp>
#include <sstream>

#include "Component.h"

class Shader;

class Light :
	public Component
{
public:
	Light();
	~Light();

	bool GetIfUploaded() { return m_dataUploaded; }
	void SwitchIfUplaoded() { m_dataUploaded = !m_dataUploaded; }

	virtual void UploadLightData(std::shared_ptr<Shader> _shader);

	void OnInit(std::shared_ptr<GameObject> _parent,int _typeOfLight);

	void OnInit() override;
	void OnBegin() override;
	void OnUpdate() override;
	void OnDisplay() override;

protected:
	bool m_dataUploaded;

	int m_ID;

	enum E_LIGHT_TYPE {e_DirLight,e_PointLight,e_SpotLight};
	E_LIGHT_TYPE m_lightType;

	static int m_numberOfDirLights;
	static int m_numberOfPointLights;
	static int m_numberOfSpotLights;

	glm::vec3 m_lightColour;
	glm::vec3 m_lightAmbient;
	glm::vec3 m_lightDiffuse;
	glm::vec3 m_lightSpecular;

private:
	glm::vec3 m_direction;
	glm::mat4 m_lightSpaceMatrix;
};

#endif // !_LIGHT_


