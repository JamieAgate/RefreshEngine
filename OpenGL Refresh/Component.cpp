#include "Component.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Core.h"

Component::Component()
{
	m_parentGameObject.lock() = std::make_shared<GameObject>();
}


Component::~Component()
{

}

std::shared_ptr<GameObject> Component::GetParent()
{
	return m_parentGameObject.lock();
}

std::shared_ptr<InputManager> Component::GetInput()
{
	return GetParent()->GetCore()->GetInput();
}

std::shared_ptr<Core> Component::GetCore()
{
	return GetParent()->GetCore();
}

void Component::SetParent(std::shared_ptr<GameObject> _parent)
{
	m_parentGameObject = _parent;
}

glm::vec3 Component::GetPosition()
{
	return GetParent()->GetPosition();
}

glm::vec3 Component::GetRotation()
{
	return GetParent()->GetRotation();
}
