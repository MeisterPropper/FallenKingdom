#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <fstream>


class CTextureManager
{
public:
	CTextureManager();
	~CTextureManager();

	void			readTextureList(std::string);
	void			delTexture(std::string);
	sf::Texture*	getTexture(const std::string &);

private:
	std::map<std::string, sf::Texture*>	m_TextureMap;
};

long loadTextureFromFile(std::fstream&, sf::Texture*&, std::string&);

