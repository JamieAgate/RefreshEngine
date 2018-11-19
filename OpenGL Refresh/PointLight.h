#pragma once
#include "Light.h"

class PointLight :
	public Light
{
public:
	PointLight();
	~PointLight();

	void UploadLightData(std::shared_ptr<Shader> _shader) override;

	void OnInit(std::shared_ptr<GameObject> _parent);
	void OnInit() override;
	void OnBegin() override;
	void OnUpdate() override;
	void OnDisplay() override;

protected:
	float m_lightConstant;
	float m_lightLinear;
	float m_lightQuadratic;
};

