#include "CObject.h"
#include <string>

CObject::CObject(long type) : m_Type(type){
}

CObject::CObject(CObject& obj) : m_ID(obj.m_ID), m_Type(obj.m_Type) {
}

CObject & CObject::operator=(CObject&) {
	return *this;
}

CObject::~CObject() {
}

const long CObject::getID() const {
	return m_ID;
}

long CObject::_getNextID() {
	return _nextID++;
}

long CObject::_nextID = 0;

long getTypeFromString(const char * str)
{
	if (!strcmp(str, "CMaterial")) {
		return EMaterial;
	}
	else if (!strcmp(str, "CWeapon")) {
		return EWeapon;
	}

	return EUnknown;
}
