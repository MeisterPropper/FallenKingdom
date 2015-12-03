#pragma once

#include "CChunk.h"

class CWorld
{
public:
	CWorld(sf::RenderWindow* pwin, CObjectManager* pobjmng);
	~CWorld();

	void load();
	void update();

private:
	CChunk				m_aChunks[4][4];
	CObjectManager	 *  m_pObjManager;
	sf::RenderWindow *	m_pTarget;
};

