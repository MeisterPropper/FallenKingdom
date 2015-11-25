#include "FallenKingdom.h"
#include "DebugUtilities.h"

FallenKingdom::FallenKingdom(){
	m_bRunning = true;		// Anwendung l‰uft
	m_bInitialized = false;	// Anwendung wurde noch nicht initialisiert
	m_sfWindow = nullptr;	// Zeiger mit 0 initialisieren
	m_sfEvent = nullptr;	//			-"-

	DebugUtilities::printLn("Spielinstanz wurde erfolgreich erstellt...");
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

	DebugUtilities::printLn("Spielinstanz wurde erfolgreich zerstˆrt...");
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
	}
	catch (std::bad_alloc & exc) {
		// Wenn der Speicher nicht erstellt werden konnte,
		// R¸ckgabe entsprechendd anpassen
		DebugUtilities::printLn("Konnte keinen Speicher reservieren...");
		iResult = -1;
	}

	DebugUtilities::printLn("Spiel wurde erfolgreich initialisiert...");

	return iResult;
}

int FallenKingdom::doGameLoop() {
	DebugUtilities::printLn("Nachrichtenschleife wird betreten...");
	int iResult = 0;
	// Solange m_bRunning true ist, l‰uft das Spiel
	while (m_bRunning) {
		// Auf Ereignisse testen
		while (m_sfWindow->pollEvent(*m_sfEvent)) {
			switch (m_sfEvent->type){
				// Wenn das 'X' des Fensters geklickt wurde,
				// Anwendung schlieﬂen
			case sf::Event::Closed: {
				m_bRunning = false;
			}break;
				// Alle nicht bekannten Ereignisse durchlassen
			default:
				break;
			}
		}
	}
	DebugUtilities::printLn("Nachrichtenschleife wird verlassen...");
	return iResult;
}