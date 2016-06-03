#pragma once

#include <string>

class CObject {
protected:
	CObject(long type);
	CObject(CObject&);
	CObject& operator=(CObject&);

public:
	virtual ~CObject();
	const std::string getID() const;
	const long getType() const { return m_Type; }
	void registerObj(std::string id) { m_ID = id; }

private:
	std::string m_ID;
	long m_Type;
};

enum EObjectType {
	EWeapon,
	EArmor,
	ECharacter,
	ETile,
	EMaterial,
	EUnknown
};

long getTypeFromString(const char* str);