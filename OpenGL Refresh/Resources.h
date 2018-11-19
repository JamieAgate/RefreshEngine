#pragma once
#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <list>
#include <memory>
#include <exception>
#include <vector>

#include "Resource.h"
#include "RefreshException.h"

class Resources
{
public:
	Resources();
	~Resources();

	template <typename T>
	std::vector<std::weak_ptr<T>> GetResources();

	template<typename T>
	std::shared_ptr<T> Get(std::string _name);
	template<typename T>
	std::shared_ptr<T> Load(std::string _name, std::string _path);
	template<typename T>
	std::shared_ptr<T> Load(std::string _name, std::string _path1, std::string _path2);

private:
	std::list<std::shared_ptr<Resource>> m_resources;
};

#endif // !_RESOURCES_H_

template<typename T>
inline std::vector<std::weak_ptr<T>> Resources::GetResources()
{
	std::vector<std::weak_ptr<T>>rtn;
	std::list<std::shared_ptr<Resource>>::iterator it;
	for (it = m_resources.begin(); it != m_resources.end(); it++)
	{
		std::shared_ptr<T> test = std::dynamic_pointer_cast<T>(*it);
		if(test)
		{
			rtn.push_back(test);
		}
	}

	return rtn;
}

template<typename T>
inline std::shared_ptr<T> Resources::Get(std::string _name)
{
		for (std::list<std::shared_ptr<Resource>>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if ((*it)->GetName() == _name)
			{
				return std::dynamic_pointer_cast<T>(*it);
			}
		}
}

template<typename T>
inline std::shared_ptr<T> Resources::Load(std::string _name, std::string _path)
{
		for (std::list<std::shared_ptr<Resource>>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if ((*it)->GetPath() == _path)
			{
				return std::dynamic_pointer_cast<T>(*it);
			}
		}

		std::shared_ptr<T> rtn = std::make_shared<T>();
		try
		{
			rtn->Load(_path);
		}
		catch (RefreshException& e)
		{
			for (std::list<std::shared_ptr<Resource>>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
			{
				if ((*it)->GetPath() == e.GetPath())
				{
					return std::dynamic_pointer_cast<T>(*it);
				}
			}
		}
		rtn->SetName(_name);
		m_resources.push_back(rtn);
		return rtn;
}

template<typename T>
inline std::shared_ptr<T> Resources::Load(std::string _name, std::string _path1, std::string _path2)
{
	std::string s = _path1;
	s += ", ";
	s += _path2;
	for (std::list<std::shared_ptr<Resource>>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
	{
		if ((*it)->GetPath() == s)
		{
			return std::dynamic_pointer_cast<T>(*it);
		}
	}

	std::shared_ptr<T> rtn = std::make_shared<T>();
	try
	{ 
		rtn->Load(_path1, _path2);
	}
	catch (RefreshException& e)
	{
		for (std::list<std::shared_ptr<Resource>>::iterator it = m_resources.begin(); it != m_resources.end(); it++)
		{
			if ((*it)->GetPath() == e.GetPath())
			{
				return std::dynamic_pointer_cast<T>(*it);
			}
		}
	}
	rtn->SetName(_name);
	m_resources.push_back(rtn);
	return rtn;
}
