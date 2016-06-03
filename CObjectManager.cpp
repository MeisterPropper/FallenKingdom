#include "CObjectManager.h"
#include "CMaterial.h"
#include <fstream>

CObjectManager::CObjectManager(){
}


CObjectManager::~CObjectManager(){
}

long CObjectManager::loadObjectTable()
{
	char * path = "Data/Objects/ObjectTable.dat";

	std::fstream objectTable;
	objectTable.open(path, std::ios::in);

	struct entry {
		long  type;
		char* path;
	};

	entry curEntry;

	std::string etype;
	std::string epath;

	while (!objectTable.eof()) {
		if (objectTable.get() == '{') {
			char* tmp = (char*)malloc(1024);
			objectTable.getline(tmp, 1024);
			int counter = 0;
			for (int it = 0; tmp[it] != ';' && tmp[it] != '}'; ++it) {
				if (tmp[it] == ' ') {
					continue;
				}
				etype.push_back(tmp[it]);
				counter = it;
			}
			for (int it = counter + 2; tmp[it] != ';' && tmp[it] != '}'; ++it) {
				if (tmp[it] == ' ') {
					continue;
				}
				epath.push_back(tmp[it]);
			}

			curEntry.type = getTypeFromString(etype.c_str());
			curEntry.path = const_cast<char*>(epath.c_str());

			CObject* obj;

			switch (curEntry.type) {
			case EMaterial: {
				CMaterial mat = loadMatFromFile(curEntry.path);
				obj = new CMaterial(mat.getName(), mat.getTexture(),
					mat.getCollision(), mat.getWalkspeed());
				obj->registerObj(mat.getName());
				m_ObjectMap.insert(std::pair<std::string, CObject*>(obj->getID(), obj));
			}break;
			}

			etype.clear();
			epath.clear();
		}
	}

	objectTable.close();
	return 0;
}

long CObjectManager::addObject(CObject * obj){
	// Auf Null testen
	if (!obj) {
		return -1;
	}

	// Object in Liste einfügen
	m_ObjectMap.insert(std::pair<std::string, CObject*>(obj->getID(), obj));

	return 0;
}

long CObjectManager::delObject(std::string name)
{
	// Object suchen

	return 0;
}

