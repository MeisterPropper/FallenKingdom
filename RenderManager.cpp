#include "RenderManager.h"
#include "DebugUtilities.h"

RenderManager::RenderManager(){
	m_pWindow = nullptr;
	m_sfFillColor = sf::Color(0, 0, 0);
}


RenderManager::~RenderManager(){
}

int RenderManager::init(sf::RenderWindow * ptr){
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

void RenderManager::render(){
	// Fensterinhalt löschen
	m_pWindow->clear(m_sfFillColor);

	// Fensterinhalt anzeigen
	m_pWindow->display();
}
