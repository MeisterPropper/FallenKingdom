#pragma once

#include "CObject.h"
#include <SFML\Graphics.hpp>
#include <string>


class CMaterial : public CObject {
public:
	CMaterial();
	CMaterial(std::string name, sf::Texture* texture, bool collision, float walkspeed);
	~CMaterial();

	sf::Texture*	getTexture() {
		return m_pTexture;
	}
	float			getWalkspeed() {
		return m_fWalkspeed;
	}
	bool			getCollision() {
		return m_bCollision;
	}
	std::string	getName() {
		return m_Name;
	}

private:
	std::string		m_Name;
	sf::Texture*	m_pTexture;
	bool			m_bCollision;
	float			m_fWalkspeed;
};

CMaterial loadMatFromFile(char* path);
