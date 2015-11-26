#pragma once

#include <SFML\Graphics.hpp>

class RenderManager{
public:
	RenderManager();
	~RenderManager();

	int  init(sf::RenderWindow * ptr);
	void render();

private:
	sf::RenderWindow * m_pWindow;
	sf::Color		   m_sfFillColor;
};

