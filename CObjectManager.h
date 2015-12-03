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
	long delObject(long id);

	template<typename type>
	type getObject(long id);

private:
	std::map<long, CObject*>	m_ObjectMap;
};


template<typename type>
inline type CObjectManager::getObject(long id) {
	// Gesuchtes Object finden
	CObject* tmp = m_ObjectMap.find(id)->second;

	switch (tmp->getType()) {
	case EMaterial: {
		return dynamic_cast<CMaterial*>(tmp);
	}break;
	}

	return dynamic_cast<type>(tmp);
}