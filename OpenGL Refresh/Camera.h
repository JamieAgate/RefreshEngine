#ifndef _CAMERA_
#define _CAMERA_

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL.h>
#include <memory>

#include "InputManager.h"

class Camera
{
public:
	Camera(std::weak_ptr<InputManager> _input);
	~Camera();

	glm::mat4 GetViewMatrix() { return m_viewMatrix; };
	glm::mat4 GetPerspecMat() { return m_perspecticeMat; }
	glm::vec3 GetCamPos() { return m_camPos; }

	void Update(float _deltaT);

	void Movement(float _deltaT);

private:
	std::weak_ptr<InputManager> m_input;

	glm::vec3 m_camPos;
	glm::mat4 m_perspecticeMat;
	glm::mat4 m_viewMatrix;

	glm::vec3 m_camFront;
	glm::vec3 m_camUp;

	float m_cameraAngleX;
	float m_cameraAngleY;
	int m_mouseX = 0;
	int m_mouseY = 0;
	

};

#endif // !_CAMERA_


