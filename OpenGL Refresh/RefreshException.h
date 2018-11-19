#pragma once
#ifndef _REFRESHEXCEPTION_H_
#define _REFRESHEXCEPTION_H_

#include <exception>
#include <string>

class RefreshException : public std::exception
{
public:
	RefreshException(std::string _msg, std::string _defaultPath) : std::exception(_msg.c_str()),
		m_defaultPath(_defaultPath)
	{
	}
	~RefreshException();

	std::string GetPath() { return m_defaultPath; }
private:
	std::string m_defaultPath;
};
#endif // !_REFRESHEXCEPTION_H_


