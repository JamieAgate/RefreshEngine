#ifndef _COMPONENT_
#define _COMPONENT_

#include <memory>
#include <glm.hpp>

class GameObject;

class InputManager;

class Core;

class Component
{
public:
	Component();
	virtual ~Component();

	std::shared_ptr<GameObject> GetParent();
	std::shared_ptr<InputManager> GetInput();
	std::shared_ptr<Core> GetCore();

	void SetParent(std::shared_ptr<GameObject> _parent);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();

	virtual void OnInit() {};
	virtual void OnBegin() {};
	virtual void OnUpdate() {};
	virtual void OnDisplay() {};

private:
	std::weak_ptr<GameObject> m_parentGameObject;
};

#endif // !_COMPONENT_


