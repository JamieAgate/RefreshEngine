#include "Camera.h"

Camera::Camera(std::weak_ptr<InputManager> _input)
{
	m_perspecticeMat = glm::perspective(45.0f, 1600.0f/900.0f, 0.1f, 100.0f);

	m_input = _input;//sets input
	m_cameraAngleX = 0.0f;//sets x angle
	m_cameraAngleY = 0.0f;//sets y angle
	m_mouseX = 0;//initialises mousex
	m_mouseY = 0;//initialises mousey
	m_camPos = glm::vec3(-3.0f,0.0f,0.0f);//sets camera position

	m_viewMatrix = glm::translate(glm::mat4(1), m_camPos);//creats the veiw matrix
	m_camFront = { 0.0f,0.0f,-1.0f };//sets the camera front
	m_camUp = { 0.0f, 1.0f, 0.0f };//sets the camera up
}


Camera::~Camera()
{

}

void Camera::Update(float _deltaT)
{

	m_input.lock()->UpdateMouse(&m_mouseX, &m_mouseY);//updates mouse
	m_cameraAngleX += m_mouseX * 0.05f;//changes x camera angle
	m_cameraAngleY -= m_mouseY * 0.05f;//changes y camera angle

	if (m_cameraAngleY > 89.0f)
	{
		m_cameraAngleY = 89.0f;//stops from looing too far up
	}
	if (m_cameraAngleY < -89.0f)
	{
		m_cameraAngleY = -89.0f;//stops from looking too far down
	}

	//calculates the front facing direction
	glm::vec3 front;
	front.x = cos(glm::radians(m_cameraAngleY)) * cos(glm::radians(m_cameraAngleX));
	front.y = sin(glm::radians(m_cameraAngleY));
	front.z = cos(glm::radians(m_cameraAngleY)) * sin(glm::radians(m_cameraAngleX));
	m_camFront = glm::normalize(front);

	Movement(_deltaT);//moves camera

	m_viewMatrix = glm::lookAt(m_camPos, m_camPos + m_camFront, m_camUp);//creates view matrix
}

void Camera::Movement(float _deltaT)
{
	float camSpeed = 2.0f * _deltaT;//sets cam speed
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_W))
	{
		m_camPos += camSpeed * m_camFront;//move forward
	}
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_S))
	{
		m_camPos -= camSpeed * m_camFront;//move backwards
	}
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_A))
	{
		m_camPos -= glm::normalize(glm::cross(m_camFront, m_camUp)) * camSpeed;//moves left
	}
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_D))
	{
		m_camPos += glm::normalize(glm::cross(m_camFront, m_camUp)) * camSpeed;//moves right
	}
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_Q))
	{
		m_camPos += camSpeed * m_camUp;//moves up
	}
	if (m_input.lock()->IsKeyDown(SDL_SCANCODE_E))
	{
		m_camPos -= camSpeed * m_camUp;//moves down
	}
}
