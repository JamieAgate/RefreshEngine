#pragma once
#include "PointLight.h"
class SpotLight :
	public PointLight
{
public:
	SpotLight();
	~SpotLight();

	void UploadLightData(std::shared_ptr<Shader> _shader) override;



private:
	float m_cutOff;
	float m_outerCuttOff;
};

