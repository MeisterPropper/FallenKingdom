#include "CRenderManager.h"
#include "DebugUtilities.h"

CRenderManager::CRenderManager(){
	m_pWindow = nullptr;
	m_sfFillColor = sf::Color(0, 0, 0);
}


CRenderManager::~CRenderManager(){
}

void CRenderManager::addDrawable(sf::Drawable * ptr){
	// Nullzeigertest
	if (!ptr) {
		return;
	}

	// Zur Liste hinzufügen
	m_sfDrawList.push_back(ptr);
}

void CRenderManager::delDrawable(sf::Drawable * ptr){
	if (!ptr) {
		return;
	}

	// Nach Zeiger suchen
	for (auto it = m_sfDrawList.begin(); it != m_sfDrawList.end(); ++it) {
		if ((*it) == ptr) {
			// Zeiger aus Liste entfernen
			m_sfDrawList.erase(it);
			break;
		}
	}
}

int CRenderManager::init(sf::RenderWindow * ptr){
	int iResult = 0;
	if (!ptr) {
		// Nullzeiger sind nicht erlaubt
		DebugUtilities::printErr("Nullzeigerübergabe...");
		iResult = -1;
		return iResult;
	}

	// Fenster des Spieles zuweisen
	m_pWindow = ptr;

	DebugUtilities::printInfo("Renderer wurde initialisiert...");

	return iResult;
}

void CRenderManager::render(){
	// Fensterinhalt löschen
	m_pWindow->clear(m_sfFillColor);

	// Alle Daten rendern
	for (auto it = m_sfDrawList.begin(); it != m_sfDrawList.end(); ++it) {
		m_pWindow->draw(*(*it));
	}

	// Fensterinhalt anzeigen
	m_pWindow->display();
}

void CRenderManager::setFillColor(sf::Color color){
	m_sfFillColor = color;
}

sf::Color CRenderManager::getFillColor(){
	return m_sfFillColor;
}

