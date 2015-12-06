#pragma once

#include <map>
#include "CObject.h"

class CObjectManager
{
public:
	CObjectManager();
	~CObjectManager();

	long loadObjectTable();
	long addObject(CObject* obj);
	long delObject(std::string name);

	template<typename type>
	type getObject(std::string & name);

private:
	std::map<std::string, CObject*>	m_ObjectMap;
};


template<typename type>
inline type CObjectManager::getObject(std::string & name) {
	// Gesuchtes Object finden
	auto tmp = m_ObjectMap.find(name);
	if(tmp == m_ObjectMap.end()) {
		return nullptr;
	}

	switch (tmp->second->getType()) {
	case EMaterial: {
		dynamic_cast<CMaterial*>(tmp->second);
	}break;
	}

	return dynamic_cast<type>(tmp->second);
}