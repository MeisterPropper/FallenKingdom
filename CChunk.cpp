#include "CChunk.h"
#include <fstream>
#include <Windows.h>


CChunk::CChunk()
{
}


CChunk::~CChunk()
{
}

CChunk::CChunk(CChunk & rhs){
	m_Data = rhs.m_Data;
	m_bRendering = rhs.m_bRendering;
	m_pTarget = rhs.m_pTarget;
}

long CChunk::load(sf::RenderWindow* pwin, CObjectManager* mng, sf::Vector2i& pos, sf::Vector2i& winPos) {
	m_pTarget = pwin;
	m_Data.position = pos;

	char* file_to_load = (char*)malloc(128);

	sprintf_s(file_to_load, 128, "Data/World/Chunk_%d_%d.chunk", pos.x, pos.y);

	if (!loadChunkData(boost::filesystem::path(file_to_load), m_Data, mng)) {
		m_bRendering = true;
		setupChunkData(m_Data, winPos);
	}
	else {
		m_bRendering = false;
	}

	free(file_to_load);

	return 0;
}

long CChunk::load(CChunk & inherit, sf::Vector2i& winPos){
	for (int first = 0; first != 16; ++first) {
		for (int second = 0; second != 16; ++second) {
			m_Data.pmat[first][second] = inherit.m_Data.pmat[first][second];
		}
	}
	m_bRendering = inherit.m_bRendering;
	m_pTarget = inherit.m_pTarget;
	m_Data.frotation = inherit.m_Data.frotation;

	if (m_bRendering) {
		setupChunkData(m_Data, winPos);
	}
	return 0;
}

long CChunk::unload() {
	m_bRendering = false;
	deleteChunkData(m_Data);
	return 0;
}

void CChunk::render(){
	if (m_bRendering) {
		for (int first = 0; first != 16; ++first) {
			for (int second = 0; second != 16; ++second) {
				m_pTarget->draw(*m_Data.psprite[first][second]);
			}
		}
	}
}

void CChunk::update(){
	
}

void CChunk::setFocus(bool activate){
	if (m_bRendering) {
		for (int first = 0; first != 16; ++first) {
			for (int second = 0; second != 16; ++second) {
				activate ?
					m_Data.psprite[first][second]->setColor(sf::Color(128, 128, 128)) :
					m_Data.psprite[first][second]->setColor(sf::Color(256, 256, 256));
			}
		}
	}
}

void CChunk::processUser(sf::Event & ev){
	if (m_bRendering) {
		for (int first = 0; first != 16; ++first) {
			for (int second = 0; second != 16; ++second) {
				m_Data.psprite[first][second]->setRotation(m_Data.frotation);
			}

		}
	}
	m_Data.frotation += 0.01f;
}

long loadChunkData(boost::filesystem::path& file, SChunkData & data, CObjectManager* mng)
{
	if (!boost::filesystem::exists(file)){
		return 1;
	}

	std::fstream File;

	File.open(file.c_str(), std::ios::in);

	std::string Ground_identifier[2] = { "START_OF_GROUNDLAYER", "END_OF_GROUNDLAYER" };

	while (!File.eof()) {
		char* pcIdentifier = (char*)malloc(128);
		File.getline(pcIdentifier, 128);
		if (!strcmp(pcIdentifier, Ground_identifier[0].c_str())) {
			char* rawlinedata = (char*)malloc(256);

			File.getline(rawlinedata, 256);

			while (strcmp(rawlinedata, Ground_identifier[1].c_str())) {
				int curline = 0;
				char Layer_ident[6];
				char Layer_number[2];
				for (int it = 0; it != 5; ++it) {
					Layer_ident[it] = rawlinedata[it];
				}
				Layer_ident[5] = '\0';

				if (!strcmp(Layer_ident, "Layer")) {
					for (int it = 0; it != 2; ++it) {
						Layer_number[it] = rawlinedata[it + 5];
					}
					File.getline(rawlinedata, 256);
				}
				int iLayer = atoi(Layer_number) - 1;

				while (strcmp(rawlinedata, "}end")) {
					char* firstdata = (char*)malloc(64);
					int i = 0;
					while (rawlinedata[i] != ';') {
						firstdata[i] = rawlinedata[i + 1];
						++i;
					}
					firstdata[i - 1] = '\0';
					data.pmat[iLayer][curline] = mng->getObject<CMaterial*>(std::string(firstdata));
					++curline;
					free(firstdata);
					ZeroMemory(rawlinedata, 256);
					File.getline(rawlinedata, 256);
				}
				ZeroMemory(rawlinedata, 256);
				File.getline(rawlinedata, 256);
			}
				free(rawlinedata);
		}
	}

	File.close();
	return 0;
}

long setupChunkData(SChunkData & rhs, sf::Vector2i& winPos)
{
	for (int first = 0; first != 16; ++first) {
		for (int second = 0; second != 16; ++second) {
			rhs.psprite[first][second] = new sf::Sprite();
			rhs.psprite[first][second]->setRotation(rhs.frotation);
			rhs.psprite[first][second]->setTexture(*rhs.pmat[first][second]->getTexture());
			rhs.psprite[first][second]->setPosition(sf::Vector2f((64.0f * first) + (winPos.x * 1024.0f),
				(64.0f * second) + (winPos.y * 1024.0f)));

			rhs.collmap[first] = 0;
			rhs.collmap[first] = rhs.collmap[first] ^ rhs.pmat[first][second]->getCollision();
		}
	}
	return 0;
}

long deleteChunkData(SChunkData & rhs)
{
	rhs.frotation = 0.0f;
	for (int first = 0; first != 16; ++first) {
		for (int second = 0; second != 16; ++second) {
			delete rhs.psprite[first][second];
			rhs.psprite[first][second] = nullptr;
		}
	}
	return 0;
}
