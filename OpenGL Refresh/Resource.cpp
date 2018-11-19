#include "Resource.h"



Resource::Resource()
{
}


Resource::~Resource()
{
}

void Resource::Load(std::string _path)
{
	m_path = _path;
}
