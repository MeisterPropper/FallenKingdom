#pragma once

#include "CMaterial.h"
#include "CObjectManager.h"

struct SChunkData {
	CMaterial*	pmat[16][16];
	sf::Sprite* psprite[16][16];
	__int16		collmap[16];
};

long setupChunkData(SChunkData&);

class CChunk
{
public:
	CChunk();
	~CChunk();

	long load(sf::RenderWindow* pwin, CObjectManager* mng);
	long unload();

	void render();

private:
	SChunkData			m_Data;
	sf::RenderWindow *	m_pTarget;
};

