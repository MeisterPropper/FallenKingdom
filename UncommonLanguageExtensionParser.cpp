#include "UncommonLanguageExtensionParser.h"
#include <fstream>

const char* ULE_STARTNODE = "StartNode";
const char* ULE_ENDNODE = "EndNode";

long processULEFile(char * data, std::streamsize length, ULENode** parent);
long processStartTag(char * data, std::streamsize length, long & position, ULENode** parent);
long processTagData(const char * data, std::streamsize length, ULENode** parent);
long processTagContainer(const char* data, std::streamsize length, long & position, ULENode** parent);

ULEParser::ULEParser(){
	m_pcPath = " ";
}

ULEParser::ULEParser(char * path){
	m_pcPath = path;
}

ULEParser::ULEParser(ULEParser & copy){
}

ULEParser::~ULEParser(){
	delete m_pNodeTree;
	m_pNodeTree = nullptr;
	free(m_pcPath);
}

long ULEParser::loadFile(){
	// Dateihandle
	std::fstream fileStream;

	// Datei öffnen
	fileStream.open(m_pcPath, std::ios::in);

	// Puffer für den Dateiinhalt
	char* pcDataBuffer = (char*)malloc(fileStream.width());

	// Datei auslesen und schließen
	fileStream.read(pcDataBuffer, fileStream.width());
	fileStream.close();

	return 0;
}

long ULEParser::loadFile(const char * path)
{
	// Dateihandle
	std::fstream fileStream;

	m_pcPath = (char*)malloc(strlen(path));
	memcpy_s(m_pcPath, strlen(path), path, strlen(path));

	// Datei öffnen
	fileStream.open(path, std::ios::in);

	// Länge der Datei ermitteln
	fileStream.seekg(0, std::ios::end);
	std::streamsize fileSize = fileStream.tellg();

	// Puffer für den Dateiinhalt
	char* pcDataBuffer = (char*)malloc(fileSize);

	// Lesezeiger zurück auf den Anfang der Datei setzen
	fileStream.seekg(std::ios::cur - 1, 0);

	// Datei auslesen und schließen
	fileStream.read(pcDataBuffer, fileSize);
	fileStream.close();

	// Die Daten verarbeiten
	processULEFile(pcDataBuffer, fileSize, &m_pNodeTree);

	free(pcDataBuffer);

	return 0;
}

std::string ULEParser::getString(std::string value){

	std::vector<std::string> path_intersecs;

	char curCharacter = value[0];
	int iterator = 0;
	while (iterator < value.size()) {
		std::string path;
		curCharacter = value[iterator];
		while (curCharacter != '.' && iterator < value.size()) {
			path.push_back(curCharacter);
			++iterator;
			curCharacter = value[iterator];
		}
		++iterator;
		path_intersecs.push_back(path);
	}

	ULENode * curNode = m_pNodeTree;

	for (int iterator = 1; iterator != path_intersecs.size(); ++iterator) {
		for (int i = 0; i != curNode->lChildNum; ++i) {
			if (curNode->pChild[i]->nodeName == path_intersecs[iterator]) {
				// Überprüfen, ob es sich um einen Container handelt
				curNode = curNode->pChild[i];
				for (int it = 0; it != curNode->AttrList.size(); ++it) {
					if (curNode->AttrList[it].value == std::string("container")) {
						// Nach dem entsprechenden Eintrag suchen
						++iterator;
						for (int it = 0; it != curNode->lChildNum; ++it) {
							if (curNode->pChild[it]->nodeName == path_intersecs[iterator]) {
								curNode = curNode->pChild[i];
								break;
							}
						}
						// Über die Attribute den entsprechenden Wert finden
						for (int it = 0; it != curNode->AttrList.size(); ++it) {
							static int pos = 0;
							if (curNode->AttrList[it].type1 == E_ULE_DATA) {
								if (curNode->AttrList[it].value == path_intersecs[path_intersecs.size() - 1]) {
									if (pos == 0) {
										return std::string((char*)curNode->pData, curNode->AttrList[it + 1].type2);
									}
									else {
										return std::string((char*)curNode->pData + curNode->AttrList[it - 1].type2, curNode->AttrList[it + 1].type2);
									}
								}
								++pos;
							}
						}

						//return atoi((char*))
					}
				}
				break;
			}
		}
	}
	return std::string((char*)curNode->pData, curNode->lDataLength);
}

int ULEParser::getInteger(std::string value)
{
	std::vector<std::string> path_intersecs;

	char curCharacter = value[0];
	int iterator = 0;
	while (iterator < value.size()) {
		std::string path;
		curCharacter = value[iterator];
		while (curCharacter != '.' && iterator < value.size()) {
			path.push_back(curCharacter);
			++iterator;
			curCharacter = value[iterator];
		}
		++iterator;
		path_intersecs.push_back(path);
	}

	ULENode * curNode = m_pNodeTree;

	for (int iterator = 1; iterator != path_intersecs.size(); ++iterator) {
		for (int i = 0; i != curNode->lChildNum; ++i) {
			if (curNode->pChild[i]->nodeName == path_intersecs[iterator]) {
				curNode = curNode->pChild[i];
				// Überprüfen, ob es sich um einen Container handelt
				for (int it = 0; it != curNode->AttrList.size(); ++it) {
					if (!strcmp(curNode->AttrList[it].value, "container")) {
						// Nach dem entsprechenden Eintrag suchen
						++iterator;
						for (int it = 0; it != curNode->lChildNum; ++it) {
							if (curNode->pChild[it]->nodeName == path_intersecs[iterator]) {
								curNode = curNode->pChild[it];
								break;
							}
						}
						// Über die Attribute den entsprechenden Wert finden
						for (int it = 0; it != curNode->AttrList.size(); ++it) {
							if (curNode->AttrList[it].type1 == E_ULE_DATA) {
								static int pos = 0;
								if (curNode->AttrList[it].value == path_intersecs[path_intersecs.size() - 1]) {
									// TODO:
									// Vereinfachen, wenn möglich
									int val = pos;
									pos = 0;
									/////////////////////////////
									return *((int*)curNode->pData + val);
								}
								++pos;
							}
						}
					}
				}
				break;
			}
		}
	}
	return atoi((char*)curNode->pData);
}

float ULEParser::getFloat(std::string value)
{
	std::vector<std::string> path_intersecs;

	char curCharacter = value[0];
	int iterator = 0;
	while (iterator < value.size()) {
		std::string path;
		curCharacter = value[iterator];
		while (curCharacter != '.' && iterator < value.size()) {
			path.push_back(curCharacter);
			++iterator;
			curCharacter = value[iterator];
		}
		++iterator;
		path_intersecs.push_back(path);
	}

	ULENode * curNode = m_pNodeTree;

	for (int iterator = 1; iterator != path_intersecs.size(); ++iterator) {
		for (int i = 0; i != curNode->lChildNum; ++i) {
			if (curNode->pChild[i]->nodeName == path_intersecs[iterator]) {
				curNode = curNode->pChild[i];
				// Überprüfen, ob es sich um einen Container handelt
				for (int it = 0; it != curNode->AttrList.size(); ++it) {
					if (curNode->AttrList[it].type2 == E_ULE_CONTAINER) {
						// Nach dem entsprechenden Eintrag suchen
						++iterator;
						for (int it = 0; it != curNode->lChildNum; ++it) {
							if (curNode->pChild[it]->nodeName == path_intersecs[iterator]) {
								curNode = curNode->pChild[i];
								break;
							}
						}
						// Über die Attribute den entsprechenden Wert finden
						for (int it = 0; it != curNode->AttrList.size(); ++it) {
							static int pos = 0;
							if (curNode->AttrList[it].type1 == E_ULE_DATA) {
								if (curNode->AttrList[it].value == path_intersecs[path_intersecs.size() - 1]) {
									// TODO:
									// Vereinfachen, wenn möglich
									int val = pos;
									pos = 0;
									/////////////////////////////
									return *((float*)curNode->pData + pos);
								}
								++pos;
							}
						}

						//return atoi((char*))
					}
				}
				break;
			}
		}
	}
	return atof((char*)curNode->pData);
}

bool ULEParser::getBool(std::string value)
{
	std::vector<std::string> path_intersecs;

	char curCharacter = value[0];
	int iterator = 0;
	while (iterator < value.size()) {
		std::string path;
		curCharacter = value[iterator];
		while (curCharacter != '.' && iterator < value.size()) {
			path.push_back(curCharacter);
			++iterator;
			curCharacter = value[iterator];
		}
		++iterator;
		path_intersecs.push_back(path);
	}

	ULENode * curNode = m_pNodeTree;

	for (int iterator = 1; iterator != path_intersecs.size(); ++iterator) {
		for (int i = 0; i != curNode->lChildNum; ++i) {
			if (curNode->pChild[i]->nodeName == path_intersecs[iterator]) {
				curNode = curNode->pChild[i];
				// Überprüfen, ob es sich um einen Container handelt
				for (int it = 0; it != curNode->AttrList.size(); ++it) {
					if (curNode->AttrList[it].type2 == E_ULE_CONTAINER) {
						// Nach dem entsprechenden Eintrag suchen
						++iterator;
						for (int it = 0; it != curNode->lChildNum; ++it) {
							if (curNode->pChild[it]->nodeName == path_intersecs[iterator]) {
								curNode = curNode->pChild[i];
								break;
							}
						}
						// Über die Attribute den entsprechenden Wert finden
						for (int it = 0; it != curNode->AttrList.size(); ++it) {
							static int pos = 0;
							if (curNode->AttrList[it].type1 == E_ULE_DATA) {
								if (curNode->AttrList[it].value == path_intersecs[path_intersecs.size() - 1]) {
									// TODO:
									// Vereinfachen, wenn möglich
									int val = pos;
									pos = 0;
									/////////////////////////////
									(*(int*)curNode->pData + pos) != 0 ? true : false;
								}
								++pos;
							}
						}
					}
				}
				break;
			}
		}
	}
	return (*(int*)curNode->pData) != 0 ? true : false;
}




///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

long processULEFile(char * data, std::streamsize length, ULENode ** parent)
{
	// <>-weise alle Flags auslesen

	// Parentnode
	// Da es sich hier um den äußersten der Nodes handelt,
	// gibt es kein Parent, weshalb dieser Node seinen eigenen
	// Parent darstellt
	*parent = new ULENode;
	(*parent)->pParent = nullptr;
	(*parent)->lChildNum = 0;

	long fileIterator = 0;
	while (fileIterator < length) {
		processStartTag(data, length, fileIterator, parent);
	}

	return 0;
}

long processStartTag(char * data, std::streamsize length, long &position, ULENode** parent) {
	static ULENode * curNode;
	if (position == 0) {
		curNode = *parent;
	}

	long fileIterator = 0;
	// Anfangen mit dem ersten Zeichen
	char curCharacter = data[position];
	std::string curLine;
	std::string tag;

	// Lesezeiger auf die Position setzen, an der
	// der letzte Lesevorgang aufgehört hat
	long iterator = position;

	curLine.clear();
	
	int tagCount = 0;

	while (curCharacter != '\n') {
		if(tagCount < 1){
			if(curCharacter == ' '){
				break;
			}
		}
		if (curCharacter == '<'){
			++tagCount;
		}
		if (curCharacter != '\t') {
			curLine.push_back(curCharacter);
		}
		if (curCharacter == '\0') {
			return -1;
		}
		if (iterator >= length) {
			position = length;
			return -1;
		}
		// Zähler erhöhen
		++iterator;
		// Neues Zeichen auslesen
		curCharacter = data[iterator];
	}

	// Ab jetzt darf position nicht mehr verändert werden!!!
	if (curCharacter == '\n') {
		position = iterator + 2;	// Zeilenende mitberechnen
	}

	// Das momentane Zeichen ist das erste der momentanen Zeile
	curCharacter = curLine[0];

	iterator = 0;
	
	// Wenn die Zeile nur aus einem Tag besteht,
	// muss dieser nicht mehr aus der Zeile heraus 
	// kristallisiert werden
	if(tagCount > 1){
		// Überprüfen, ob es sich um den Anfang eines Tags handelt
		if (curCharacter == '<') {
			while (curCharacter != '>' && iterator != length) {
				// Neues Zeichen auslesen
				curCharacter = curLine[iterator];

				// In den String einfügen
				tag.push_back(curCharacter);

				// Zähler erhöhen
				++iterator;
			}
		}
	}
	else {
		tag = curLine;
	}
	fileIterator += iterator;

	// Flag analysieren

	// Bis zum Namen 'vorspulen'
	iterator = 1;
	curCharacter = tag[iterator];

	std::string tagName;
	// Namen des Tags ausfindig machen
	while (curCharacter != ' ' && curCharacter != '>') {
		tagName.push_back(curCharacter);

		// Zähler erhöhen
		++iterator;

		curCharacter = tag[iterator];
	}

	// Wenn es sich nicht um den Headertag handelt, muss ein 
	// neues Kindnode erstellt werden
	if (tagName != std::string("Header") &&
		tagName[0] != '/') {
		ULENode * tmp = new ULENode();
		tmp->nodeName = tagName;
		tmp->pParent = curNode;
		curNode->pChild.push_back(tmp);
		curNode->lChildNum++;
		curNode = tmp;
	}
	else if (tagName[0] == '/') {
		// Wenn es sich in der Zeile nur um ein
		// End-Tag handelt, zurück zum Parent navigieren
		curNode->AttrList.push_back(ULEAttribute(E_ULE_NODE, E_ULE_CLOSENODE, ULE_ENDNODE));
		curNode = curNode->pParent;
		position--;
		return 0;
	}
	else {
		curNode->nodeName = tagName;
	}

	curNode->AttrList.push_back(ULEAttribute(E_ULE_NODE, E_ULE_STARTNODE, ULE_STARTNODE));
			

	if (tag.size() + 2 > tagName.size()) {
		// Auf weitere Flags untersuchen
		long pos = tag.find("type");

		while (pos != std::string::npos) {
			int iterator = pos + 5;
			std::string type;
			while (tag[iterator] != ';' && tag[iterator] != '>') {
				type.push_back(tag[iterator]);
				++iterator;
			}

			// Überprüfen, ob es sich um ein Datentyp-Attribut handelt
			if (type == std::string("integer")) {
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_INT, type));
			} 
			else if (type == std::string("float")) {
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_FLOAT, type));
			}
			else if (type == std::string("bool")) {
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_BOOL, type));
			}
			else if (type == std::string("string")) {
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_STRING, type));
			}
			else {
				// Wenn keine weiteren Typen angegeben werden, 
				// handelt es sich immer um einen String
				curNode->AttrList.push_back(ULEAttribute(E_ULE_TYPE, E_ULE_STRING, type));
			}

			pos = tag.find("type", pos + 5);
		}
		pos = tag.find("lang");

		while (pos != std::string::npos) {
			int iterator = pos + 5;
			std::string type;
			while (tag[iterator] != ';'&& tag[iterator] != '>') {
				type.push_back(tag[iterator]);
				++iterator;
			}
			// Wenn keine weiteren Typen angegeben werden, 
			// handelt es sich immer um einen String
			curNode->AttrList.push_back(ULEAttribute(E_ULE_LANG, E_ULE_STRING, type));

			pos = tag.find("lang", pos + 5);
		}

		bool isContainer = false;

		// Überprüfen, ob es sich um einen Container handelt
		for (int i = 0; i != curNode->AttrList.size(); ++i) {
			if (curNode->AttrList[i].value == std::string("Container") ||
				curNode->AttrList[i].value == std::string("container")) {
				isContainer = true;
				// Nach der Größe des Containers suchen
				pos = tag.find("count");

				while (pos != std::string::npos) {
					int iterator = pos + 6;
					std::string type;
					while (tag[iterator] != ';'&& tag[iterator] != '>') {
						type.push_back(tag[iterator]);
						++iterator;
					}
					// Wenn keine weiteren Typen angegeben werden, 
					// handelt es sich immer um einen String
					curNode->AttrList.push_back(ULEAttribute(E_ULE_COUNT, E_ULE_INT, type));

					pos = tag.find("count", pos + 6);
				}
			}
		}

		if (isContainer) {
			processTagContainer(data, length, position, &curNode);
			return 0;
		}

		// Daten im Tag bearbeiten, sofern in der selben Zeile
		// das End-Tag steht
		if (curLine.find('/', curLine.size() - tagName.size() - 3) != std::string::npos) {
			processTagData(curLine.c_str(), curLine.size(), &curNode);
		}
	}
	tag.clear();
	curLine.clear();

	return 0;
}

long processTagData(const char * data, std::streamsize size, ULENode ** parent){
	
	// Start-Tag überspringen
	char curCharacter = ' ';
	long iterator = 0; 
	curCharacter = data[iterator];

	while (curCharacter != '>' && iterator != size) {
		++iterator;
		curCharacter = data[iterator];
	}

	++iterator;
	curCharacter = data[iterator];
	// Auslesen der Daten
	std::string content;

	while (curCharacter != '<' && iterator != size) {
		content.push_back(curCharacter);
		++iterator;
		curCharacter = data[iterator];
	}

	// Als Datenattribut eintragen
	(*parent)->AttrList.push_back(ULEAttribute(E_ULE_DATA, E_ULE_STRING, content));

	// Die Daten ebenfalls in den Datencontainer eintragen
	(*parent)->pData = (char*)malloc(content.size());
	(*parent)->lDataLength = content.size();
	memcpy_s((*parent)->pData, content.size(), content.c_str(), content.size());

	// Zurück zum Parentnode kehren
	(*parent) = (*parent)->pParent;

	return 0;
}

long processTagContainer(const char * data, std::streamsize size, long & position, ULENode ** parent) {
	ULENode * curNode = (*parent);
	
	long dataType = 0;
	long count = 0;
	long pos = 0;
	// Den Container-Tag nach dem Datentyp-Attribut durchsuchen
	for (int i = 0; i != curNode->AttrList.size(); ++i) {
		if (curNode->AttrList[i].type1 == E_ULE_DATATYPE) {
			dataType = curNode->AttrList[i].type2;
		}
		else if (curNode->AttrList[i].type1 == E_ULE_COUNT) {
			count = atoi(curNode->AttrList[i].value);
		}
	}

	// Durch das Count-Attribut ist die Anzahl der Einträge bekannt

	for (int it = 0; it != count; ++it) {
		char curCharacter = data[position];
		
		// Neues Kindnode erstellen
		// Da jeder Eintrag Entry heißt, werden diese durchnummeriert

		char* tagName = (char*)malloc(16);
		pos = 0;

		sprintf_s(tagName, 16, "Entry[%d]", it);

		ULENode * tmp = new ULENode();
		tmp->nodeName = tagName;
		tmp->pParent = curNode;
		curNode->pChild.push_back(tmp);
		curNode->lChildNum++;
		curNode = tmp;

		int iterator = position;
		long lineStartPos = 0;

		// Bis zum ersten Eintrag vorrücken
		while (curCharacter != '<') {
			++iterator;

			curCharacter = data[iterator];
			lineStartPos = iterator;
		}

		// Zeile auslesen
		std::string curLine;
		long numSemicola = 0;

		while (curCharacter != '\n') {
			curLine.push_back(curCharacter);
			// Anzahl der Semicola speichern, da sie aufschluss über
			// die Anzahl der enthaltenen Daten gibt
			if (curCharacter == ';') ++numSemicola;

			++iterator;
			curCharacter = data[iterator];
		}

		position += iterator - position + 2;

		long numData = numSemicola;

		curNode->lDataLength = numData;

		// Je nach Datentyp Speicher reservieren
		switch (dataType) {
			// String
		case E_ULE_STRING: {
			curNode->pData = (char*)malloc(curLine.size());
			curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_STRING, "true"));
		}break;
			// Integer
		case E_ULE_INT: {
			curNode->pData = (int*)malloc(numData * sizeof(int));
			curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_INT, "true"));
		}break;
			// Float
		case E_ULE_FLOAT: {
			curNode->pData = (float*)malloc(numData * sizeof(float));
			curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_FLOAT, "true"));
		}break;
			// Bool
		case E_ULE_BOOL: {
			curNode->pData = (bool*)malloc(numData * sizeof(bool));
			curNode->AttrList.push_back(ULEAttribute(E_ULE_DATATYPE, E_ULE_BOOL, "true"));
		}break;
		}

		int iterator_2 = lineStartPos + 7;

		// Die einzelnen Daten auslesen
		for (int it = 0; it != numData; ++it) {
			std::string content;
			std::string identifier;
			curCharacter = data[iterator_2];
			while (curCharacter != '=') {
				identifier.push_back(curCharacter);
				++iterator_2;
				curCharacter = data[iterator_2];
			}

			while (curCharacter != ';') {
				if (curCharacter == '=') {
					++iterator_2;
					curCharacter = data[iterator_2];
					while (curCharacter != ';') {
						content.push_back(curCharacter);
						++iterator_2;
						curCharacter = data[iterator_2];
					}
					break;
				}
				++iterator_2;
				curCharacter = data[iterator_2];
			}

			++iterator_2;
			// Nach den verschiedenen Typen unterscheiden
			switch (dataType) {
				// String
			case E_ULE_STRING: {
				memcpy_s((char*)curNode->pData + pos, curLine.size(), content.c_str(), content.size());
				pos += content.size();
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATA, E_ULE_STRING, identifier));
				curNode->AttrList.push_back(ULEAttribute(E_ULE_LENGTH, content.size(), " "));
			}break;
				// Integer
			case E_ULE_INT: {
				int value = atoi(content.c_str());
				memcpy_s((int*)curNode->pData + it, sizeof(int), &value, sizeof(int));
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATA, E_ULE_INT, identifier));
			}break;
				// Float
			case E_ULE_FLOAT: {
				float value = atof(content.c_str());
				memcpy_s((float*)curNode->pData + it, sizeof(float), &value, sizeof(float));
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATA, E_ULE_FLOAT, identifier));
			}break;
				// Bool
			case E_ULE_BOOL: {
				bool expression = (strcmp(content.c_str(), "true") ||
					strcmp(content.c_str(), "True")) ? true : false;
				memcpy_s((bool*)curNode->pData + it, sizeof(bool), &expression, sizeof(bool));
				curNode->AttrList.push_back(ULEAttribute(E_ULE_DATA, E_ULE_FLOAT, identifier));
			}break;
			}
		}

		curNode = curNode->pParent;
		free(tagName);
	}

	return 0;
}
