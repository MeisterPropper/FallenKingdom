#include "FallenKingdom.h"
#include "DebugUtilities.h"

FallenKingdom::FallenKingdom(){
	m_bRunning = true;		// Anwendung läuft
	m_bInitialized = false;	// Anwendung wurde noch nicht initialisiert
	m_sfWindow = nullptr;	// Zeiger mit 0 initialisieren
	m_sfEvent = nullptr;		//			-"-
	m_pRenderer = nullptr;	//			-"-

	DebugUtilities::printInfo("Spielinstanz wurde erfolgreich erstellt...");
}

FallenKingdom::~FallenKingdom(){
	if (m_sfWindow) {
		delete m_sfWindow;
		m_sfWindow = nullptr;
	}
	if (m_sfEvent) {
		delete m_sfEvent;
		m_sfEvent = nullptr;
	}
	if (m_pRenderer) {
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	DebugUtilities::printInfo("Spielinstanz wurde erfolgreich zerstört...");
}

int FallenKingdom::init()
{
	int iResult = 0;
	// Wurde init() bereits aufgerufen?
	if (m_bInitialized) {
		return iResult;
	}
	try {
		// Fenster initialisieren
		m_sfWindow = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "FallenKingdom");
		// Event initialisieren
		m_sfEvent = new sf::Event();
		// Renderer erstellen
		m_pRenderer = new RenderManager();
	}
	catch (std::bad_alloc & exc) {
		// Wenn der Speicher nicht erstellt werden konnte,
		// Rückgabe entsprechendd anpassen
		DebugUtilities::printInfo("Konnte keinen Speicher reservieren...");
		iResult = -1;
		return iResult;
	}
	
	// Renderer initialisieren
	if (m_pRenderer->init(this->m_sfWindow)) {
		// Fehler
		iResult = -1;
		return iResult;
	}

	DebugUtilities::printInfo("Spiel wurde erfolgreich initialisiert...");

	return iResult;
}

int FallenKingdom::doGameLoop() {
	DebugUtilities::printInfo("Nachrichtenschleife wird betreten...");
	int iResult = 0;
	// Solange m_bRunning true ist, läuft das Spiel
	while (m_bRunning) {
		// Auf Ereignisse testen
		while (m_sfWindow->pollEvent(*m_sfEvent)) {
			switch (m_sfEvent->type){
				// Wenn das 'X' des Fensters geklickt wurde,
				// Anwendung schließen
			case sf::Event::Closed: {
				m_bRunning = false;
			}break;
				// Alle nicht bekannten Ereignisse durchlassen
			default:
				break;
			}
		}
		// Bild rendern
		m_pRenderer->render();
	}
	DebugUtilities::printInfo("Nachrichtenschleife wird verlassen...");
	return iResult;
}