#include "GameObject.h"
#include "Core.h"
#include "Shader.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::weak_ptr<Core> _core, glm::vec3 _pos)
{
	m_core = _core;
	m_position = _pos;
	m_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_modelMatrix = glm::mat4(1.0f);
}


GameObject::~GameObject()
{

}

void GameObject::Update()
{
	typedef std::map<std::string, std::shared_ptr<Component>>::iterator iterator;

	for (iterator it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->OnUpdate();
	}
}

std::shared_ptr<Component> GameObject::GetComponent(std::string _a)
{
	return m_components.find(_a)->second;
}

void GameObject::Draw()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f),m_scale);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	typedef std::map<std::string, std::shared_ptr<Component>>::iterator iterator;

	for (iterator it = m_components.begin(); it != m_components.end(); it++)
	{
		it->second->OnDisplay();
	}
}

void GameObject::Draw(std::shared_ptr<Shader> _shader)
{
	m_modelMatrix = glm::translate(glm::mat4(1.0f), m_position) * glm::scale(glm::mat4(1.0f), m_scale);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	if (GetComponent<MeshRenderer>())
	{
		GetComponent<MeshRenderer>()->OnDisplay(_shader);
	}
}