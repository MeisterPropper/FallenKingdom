#pragma once

#include <string>
#include <vector>

enum EULETYPES_1 {
	E_ULE_NODE,
	E_ULE_TYPE,
	E_ULE_DATATYPE,
	E_ULE_LANG,
	E_ULE_COUNT,
	E_ULE_DATA,
	E_ULE_LENGTH
};

enum EULETYPES_2 {
	E_ULE_STARTNODE = 1,
	E_ULE_CLOSENODE = 2,
	E_ULE_CONTAINER = 3
};

enum EULEDATATYPES {
	E_ULE_STRING = 256,
	E_ULE_INT = 257,
	E_ULE_FLOAT = 258,
	E_ULE_BOOL = 259
};

struct ULEAttribute {
	long type1;
	long type2;
	char* value;

	///////////////////////
	// Konstruktor
	ULEAttribute(long t1, long  t2, std::string v) : type1(t1), type2(t2){
		value = (char*)malloc(v.size() + 1);
		memcpy_s(value, v.size() + 1, v.c_str(), v.size() + 1);
	}

	void freeData() {
		free(value);
		value = nullptr;
	}
};

struct ULENode {
	std::string					nodeName;
	std::vector<ULEAttribute>	AttrList;
	ULENode					*   pParent = nullptr;
	std::vector<ULENode*>		pChild;
	long						lChildNum = 0;
	void					*   pData = nullptr;
	long						lDataLength = 0;
	~ULENode() {
		for (int i = 0; i != pChild.size(); ++i) {
			pChild[i]->~ULENode();
			free(pChild[i]);
		}
		for (int i = 0; i != AttrList.size(); ++i) {
			AttrList[i].freeData();
		}
		nodeName.clear();
		pChild.clear();
		AttrList.clear();
		free(pData);
		pData = nullptr;
	}
};


class ULEParser {
public:
	ULEParser();
	ULEParser(char* path);
	ULEParser(ULEParser & copy);
	~ULEParser();


	long loadFile();
	long loadFile(const char* path);

	std::string getString(std::string value);
	int			getInteger(std::string value);
	float		getFloat(std::string value);
	bool		getBool(std::string value);

private:
	char*		m_pcPath;
	ULENode*	m_pNodeTree;
};
