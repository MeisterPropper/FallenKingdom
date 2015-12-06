#include "CTextureManager.h"

CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
}

void CTextureManager::readTextureList(std::string path){
	std::fstream File;

	File.open(path, std::ios::in);

	while (!File.eof()) {
		sf::Texture* pTemp = nullptr;
		std::string name;
		loadTextureFromFile(File, pTemp, name);
		m_TextureMap.insert(std::pair<std::string, sf::Texture*>(name, pTemp));
	}

	File.close();
}

void CTextureManager::delTexture(std::string name){
	auto result = m_TextureMap.find(name);
	if (result != m_TextureMap.end()) {
		delete(result->second);
		m_TextureMap.erase(result);
	}
}

sf::Texture * CTextureManager::getTexture(const std::string & name){
	auto result = m_TextureMap.find(name);
	if (result != m_TextureMap.end()) {
		return result->second;
	}
	return nullptr;
}


long loadTextureFromFile(std::fstream& file, sf::Texture *& ptexture, std::string & name){

	char* pline = (char*)malloc(512);
	file.getline(pline, 512);

	std::string spath = "Data/Textures/";

	if (pline[0] == '{') {
		int i = 1;
		while (pline[i] != ';') {
			spath.push_back(pline[i]);
			++i;
		}
		while (pline[i] == ' ' || pline[i] == ';') {
			++i;
		}
		while (pline[i] != '}') {
			name.push_back(pline[i]);
			++i;
		}

		ptexture = new sf::Texture();
		ptexture->loadFromFile(spath);
		free(pline);
	}

	return 0;
}

CTextureManager* g_pTextureManager = new CTextureManager();
