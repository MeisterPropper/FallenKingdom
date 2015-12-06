#pragma once

#include "CChunk.h"

class CWorld
{
public:
	CWorld(sf::RenderWindow* pwin, CObjectManager* pobjmng);
	~CWorld();

	void load();
	void reloadChunks(short dir);
	void update();
	void eventHandler(sf::Event * pev);

private:
	CChunk			 			m_aChunks[5][5];
	CObjectManager	 *			m_pObjManager;
	sf::RenderWindow *			m_pTarget;
	sf::View *					m_pView;
	sf::Vector2i				m_curCenteredChunk;
	sf::Vector2<float>			m_curCameraPosition;
	sf::Vector2i				m_distanceSinceLastChunkUpdate;
	sf::Vector2i				m_updateCheck;
};

