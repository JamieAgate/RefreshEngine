#pragma once
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

class Resource
{
public:
	Resource();
	~Resource();

	virtual void Load(std::string _path);
	void SetName(std::string _name) { m_name = _name; }

	std::string GetPath() { return m_path; }
	std::string GetName() { return m_name; }
protected:
	std::string m_name;
	std::string m_path;
};

#endif // !_RESOURCE_H_


