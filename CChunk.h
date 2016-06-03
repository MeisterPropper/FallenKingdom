#pragma once

#include "CMaterial.h"
#include "CObjectManager.h"
#include <boost\filesystem.hpp>

struct SChunkData {
	CMaterial*					pmat[16][16];
	sf::Sprite*					psprite[16][16];
	__int16						collmap[16];
	sf::Vector2i				position;
	float						frotation;
};

long loadChunkData(boost::filesystem::path&, SChunkData&, CObjectManager* mng);
long setupChunkData(SChunkData&, sf::Vector2i&);
long deleteChunkData(SChunkData&);

class CChunk
{
public:
	CChunk();
	~CChunk();
	CChunk(CChunk&);

	long load(sf::RenderWindow* pwin, CObjectManager* mng, sf::Vector2i& pos, sf::Vector2i& winPos);
	long load(CChunk & inherit, sf::Vector2i&);
	long unload();

	const SChunkData & getChunkData() const { return m_Data; } 
	void render();
	void update();
	void setFocus(bool);
	void processUser(sf::Event& ev);
	void setRendering(bool val) { m_bRendering = val; }
	bool getRendering() { return m_bRendering; }

private:
	SChunkData			m_Data;
	sf::RenderWindow *	m_pTarget;
	bool				m_bRendering;
};



