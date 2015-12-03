#pragma once

class CObject {
protected:
	CObject(long type);
	CObject(CObject&);
	CObject& operator=(CObject&);

public:
	virtual ~CObject();
	const long getID() const;
	const long getType() const { return m_Type; }
	void registerObj() { m_ID = CObject::_getNextID(); }

private:
	long m_ID;
	long m_Type;
	static long _nextID;
	static long _getNextID();
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