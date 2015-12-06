#include "CWorld.h"
#include "DebugUtilities.h"



CWorld::CWorld(sf::RenderWindow * pwin, CObjectManager* pobjmng){
	m_pTarget = pwin;
	m_pObjManager = pobjmng;
	m_pView = new sf::View();
	m_pView->setSize(sf::Vector2f(1920, 1080));
	m_pView->setCenter(sf::Vector2f(960, 540));
	m_pView->move(sf::Vector2f(-448, -28));
	m_pTarget->setView(*m_pView);
	m_curCenteredChunk = { 0, 0 };
}


CWorld::~CWorld(){
}

void CWorld::load(){
	for (int first = 0; first != 5; ++first) {
		for (int second = 0; second != 5; ++second) {
			m_aChunks[first][second].load(m_pTarget, m_pObjManager, 
				sf::Vector2i(first - 2 + m_curCenteredChunk.x,
					second - 2 + m_curCenteredChunk.y),
				sf::Vector2i(first - 2, second - 2));
		}
	}
	m_aChunks[2][2].setFocus(true);
}

void CWorld::reloadChunks(short dir){
	switch (dir) {
	case 1: {
	for (int first = 0; first != 5; ++first) {
			m_aChunks[4][first].unload();
			m_aChunks[4][first].load(m_aChunks[3][first], m_curCenteredChunk +
				sf::Vector2i(2, first - 2));
			m_aChunks[3][first].unload();
			m_aChunks[3][first].load(m_aChunks[2][first], m_curCenteredChunk + 
				sf::Vector2i(1, first - 2));
			m_aChunks[2][first].unload();
			m_aChunks[2][first].load(m_aChunks[1][first], m_curCenteredChunk + 
				sf::Vector2i(0, first - 2));
			m_aChunks[1][first].unload();
			m_aChunks[1][first].load(m_aChunks[0][first], m_curCenteredChunk + 
				sf::Vector2i(-1, first - 2));
			m_aChunks[0][first].unload();
			m_aChunks[0][first].load(m_pTarget, m_pObjManager, m_curCenteredChunk +
				sf::Vector2i(-2, first - 2),
				m_curCenteredChunk + sf::Vector2i(-2, first - 2));
		}
		m_aChunks[2][2].setFocus(true);
	}break;
	case 2: {
		for (int first = 0; first != 5; ++first) {
			m_aChunks[0][first].unload();
			m_aChunks[0][first].load(m_aChunks[1][first], m_curCenteredChunk +
				sf::Vector2i(-2, first - 2));
			m_aChunks[1][first].unload();
			m_aChunks[1][first].load(m_aChunks[2][first], m_curCenteredChunk +
				sf::Vector2i(-1, first - 2));
			m_aChunks[2][first].unload();
			m_aChunks[2][first].load(m_aChunks[3][first], m_curCenteredChunk +
				sf::Vector2i(0, first - 2));
			m_aChunks[3][first].unload();
			m_aChunks[3][first].load(m_aChunks[4][first], m_curCenteredChunk +
				sf::Vector2i(1, first - 2));
			m_aChunks[4][first].unload();
			m_aChunks[4][first].load(m_pTarget, m_pObjManager, m_curCenteredChunk +
				sf::Vector2i(2, first - 2),
				m_curCenteredChunk + sf::Vector2i(2, first - 2));
		}
			m_aChunks[2][2].setFocus(true);
	}break;
	}
	char msg[1024];
	sprintf_s(msg, "Chunks neu geladen mit x: %d y: %d als Chunk im Center und x: %d y: %d als Kameraposition",
		m_curCenteredChunk.x, m_curCenteredChunk.y,
		(int)m_curCameraPosition.x / 1024,
		(int)m_curCameraPosition.y / 1024);
	DebugUtilities::printInfo(msg);
}

void CWorld::update()
{
	// Rendern der Chunks
	for (int first = 0; first != 5; ++first) {
		for (int second = 0; second != 5; ++second) {
			m_aChunks[first][second].update();
			m_aChunks[first][second].render();
		}
	}
}

void CWorld::eventHandler(sf::Event * pev){
	switch (pev->type) {
	case sf::Event::MouseButtonPressed: {

	}break;
	case sf::Event::KeyPressed: {
		switch (pev->key.code) {
		case sf::Keyboard::A: {
			m_pView->move(-20.f, 0.f);
			m_pTarget->setView(*m_pView);
			m_curCameraPosition.x -= 20.f;
			short probe = (int)(m_curCameraPosition.x - 512) / 1024;
			if (probe != m_curCenteredChunk.x) {
				m_curCenteredChunk.x -= 1;
				reloadChunks(1);
			}
		}break;
		case sf::Keyboard::D: {
			m_pView->move(20.f, 0.f);
			m_pTarget->setView(*m_pView);
			m_curCameraPosition.x += 20.f;
			short probe = (int)(m_curCameraPosition.x + 512) / 1024;
			if (probe != m_curCenteredChunk.x) {
			m_curCenteredChunk.x += 1;
				reloadChunks(2);
			}
		}break;
		case sf::Keyboard::W: {
			m_pView->move(0, -20.f);
			m_pTarget->setView(*m_pView);
			m_curCameraPosition.y -= 20.f;
			short probe = m_curCenteredChunk.y;
			m_curCenteredChunk.y = (int)m_curCameraPosition.y / 1024;
			if (probe < m_curCenteredChunk.y - 1 ||
				probe > m_curCenteredChunk.y + 1) {
				reloadChunks(4);
			}
		}break;
		case sf::Keyboard::S: {
			m_pView->move(0, 20.f);
			m_pTarget->setView(*m_pView);
			m_curCameraPosition.y += 20.f;
			short probe = m_curCenteredChunk.y;
			m_curCenteredChunk.y = (int)m_curCameraPosition.y / 1024;
			if (probe != m_curCenteredChunk.y) {
				reloadChunks(3);
			}
		}break;
		}
	}break;
	}

	m_aChunks[2][2].processUser(*pev);
}
