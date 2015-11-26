#pragma once

#include <SFML\Graphics.hpp>
#include "RenderManager.h"

class FallenKingdom {
public:
	// Konstruktor
	//
	FallenKingdom();

	// Destruktor
	//
	~FallenKingdom();

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
	bool			  m_bRunning;		// Läuft das Spiel noch?
	bool			  m_bInitialized;	// Wurde das Spiel bereits initialisiert?
	sf::RenderWindow* m_sfWindow;		// Hauptfenster des Spiels
	sf::Event*		  m_sfEvent;		// Eventstruktur
	RenderManager *   m_pRenderer;		// Renderer

};