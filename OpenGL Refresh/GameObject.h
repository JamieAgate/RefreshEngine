#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include "lodepng.h"
#include "Component.h"

#include <iostream>
#include <map>
#include <gtc/matrix_transform.hpp>

class Shader;

class GameObject
{
public:
	GameObject();
	GameObject(std::weak_ptr<Core> _core, glm::vec3 _pos);
	~GameObject();

	void Update();

	void Draw();
	void Draw(std::shared_ptr<Shader> _shader);

	glm::mat4 GetModelMatrix() { return m_modelMatrix; }
	std::shared_ptr<Core> GetCore() { return m_core.lock(); }
	std::shared_ptr<Component> GetComponent(std::string _a);

	void SetCore(std::shared_ptr<Core> _core) { m_core = _core; }

	void SetScale(float _x, float _y, float _z) { m_scale = glm::vec3(_x, _y, _z); }
	void SetRotation(glm::vec3 _v) { m_rotation = _v; }

	glm::vec3 GetPosition() { return m_position; }
	glm::vec3 GetRotation() { return m_rotation; }

	template<typename T>
	std::shared_ptr<T> GetComponent();

	template <typename T>
	std::shared_ptr<T> AddComponenet(std::string _name);

	template <typename T, typename A>
	std::shared_ptr<T> AddComponenet(std::string _name, A a);

	template <typename T, typename A, typename B>
	std::shared_ptr<T> AddComponenet(std::string _name, A a, B b);

	template <typename T, typename A, typename B, typename C>
	std::shared_ptr<T> AddComponenet(std::string _name, A a, B b, C c);

	template <typename T, typename A, typename B, typename C, typename D>
	std::shared_ptr<T> AddComponenet(std::string _name, A a, B b, C c, D d);

	template <typename T, typename A, typename B, typename C, typename D, typename E>
	std::shared_ptr<T> AddComponenet(std::string _name, A a, B b, C c, D d, E e);


private:
	std::weak_ptr<Core> m_core;

	std::map<std::string, std::shared_ptr<Component>> m_components;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_modelMatrix;
};



template<typename T>
inline std::shared_ptr<T> GameObject::GetComponent()
{
	typedef std::map<std::string, std::shared_ptr<Component>>::iterator iterator;

	for (iterator it = m_components.begin(); it != m_components.end(); it++)
	{
		std::shared_ptr<T> test = std::dynamic_pointer_cast<T>(it->second);
		if (test)
		{
			return test;
		}
	}

	return false;
}

#define CREATE \
	std::shared_ptr<T> rtn = std::make_shared<T>(); \

template<typename T>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name)
{
	CREATE;
	rtn->OnInit();
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

template<typename T, typename A>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name, A a)
{
	CREATE;
	rtn->OnInit(a);
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

template<typename T, typename A, typename B>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name, A a, B b)
{
	CREATE;
	rtn->OnInit(a, b);
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

template<typename T, typename A, typename B, typename C>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name, A a, B b, C c)
{
	CREATE;
	rtn->OnInit(a,b,c);
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

template<typename T, typename A, typename B, typename C, typename D>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name, A a, B b, C c, D d)
{
	CREATE;
	rtn->OnInit(a,b,c,d);
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

template<typename T, typename A, typename B, typename C, typename D, typename E>
inline std::shared_ptr<T> GameObject::AddComponenet(std::string _name, A a, B b, C c, D d, E e)
{
	CREATE;
	rtn->OnInit(a, b, c, d, e);
	m_components.insert(std::pair<std::string, std::shared_ptr<Component>>(_name, rtn));
	return rtn;
}

#endif // !_GAME_OBJECT_
