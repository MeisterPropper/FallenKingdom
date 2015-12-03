#pragma once

#include <SFML\Graphics.hpp>
#include "CRenderManager.h"
#include "CWorld.h"
#include "CObjectManager.h"

class CFallenKingdom {
public:
	// Konstruktor
	//
	CFallenKingdom();

	// Destruktor
	//
	~CFallenKingdom();

	// init
	// xxxxxxxxxxxxxx
	// Initialisiert das Spiel
	// xxxxxxxxxxxxxx
	// return Status: 0 wenn alles geklappt hat
	int init();

	// doGameLoop
	// xxxxxxxxxxxxxx
	// Lässt das Spiel laufen
	// xxxxxxxxxxxxxx
	// return - Status: 0 wenn alles geklappt hat
	int doGameLoop();	

private:
	bool						m_bRunning;			// Läuft das Spiel noch?
	bool						m_bInitialized;		// Wurde das Spiel bereits initialisiert?
	sf::RenderWindow *			m_sfWindow;			// Hauptfenster des Spiels
	sf::Event *					m_sfEvent;			// Eventstruktur
	CRenderManager *			m_pRenderer;		// Renderer
	CWorld *					m_pWorld;			// Spielwelt
	CObjectManager				m_ObjectManager;	// Verwaltung aller Spielobjekte
};