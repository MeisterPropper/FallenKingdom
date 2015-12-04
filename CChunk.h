#pragma once

#include "CMaterial.h"
#include "CObjectManager.h"

struct SChunkData {
	CMaterial*		pmat[16][16];
	sf::Sprite*		psprite[16][16];
	__int16			collmap[16];
	sf::Vector2u	position;
};

long loadChunkData(std::string, SChunkData&, CObjectManager* mng);
long setupChunkData(SChunkData&);
long deleteChunkData(SChunkData&);

class CChunk
{
public:
	CChunk();
	~CChunk();

	long load(sf::RenderWindow* pwin, CObjectManager* mng, sf::Vector2u pos);
	long unload();

	void render();

private:
	SChunkData			m_Data;
	sf::RenderWindow *	m_pTarget;
};



