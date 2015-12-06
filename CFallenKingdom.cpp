#include "CFallenKingdom.h"
#include "DebugUtilities.h"
#include "CTextureManager.h"

extern CTextureManager* g_pTextureManager;

CFallenKingdom::CFallenKingdom(){
	m_bRunning = true;		// Anwendung läuft
	m_bInitialized = false;	// Anwendung wurde noch nicht initialisiert
	m_sfWindow = nullptr;	// Zeiger mit 0 initialisieren
	m_sfEvent = nullptr;		//			-"-
	m_pRenderer = nullptr;	//			-"-

	DebugUtilities::printInfo("Spielinstanz wurde erfolgreich erstellt...");
}

CFallenKingdom::~CFallenKingdom(){
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

int CFallenKingdom::init()
{
	int iResult = 0;
	// Wurde init() bereits aufgerufen?
	if (m_bInitialized) {
		return iResult;
	}
	try {
		// Fenster initialisieren
		m_sfWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080, 32), "FallenKingdom");
		// Event initialisieren
		m_sfEvent = new sf::Event();
		// Renderer erstellen
		m_pRenderer = new CRenderManager();
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

	g_pTextureManager->readTextureList("Data/Textures/TextureTable.dat");
	
	/*
	sf::Texture* tex01 = new sf::Texture;
	tex01->loadFromFile("Data/Textures/DevTextures/DevTex001.png");
	CMaterial* pmat01 = new CMaterial("Texture", tex01, 0, 1.0f);
	sf::Texture* tex02 = new sf::Texture;
	tex02->loadFromFile("Data/Textures/DevTextures/DevTex002.png");
	CMaterial* pmat02 = new CMaterial("Texture", tex02, 0, 1.0f);
	m_ObjectManager.addObject(pmat01);
	m_ObjectManager.addObject(pmat02);
	*/
	m_ObjectManager.loadObjectTable();

	m_pWorld = new CWorld(m_sfWindow, &m_ObjectManager);
	m_pWorld->load();
	
	

	DebugUtilities::printInfo("Spiel wurde erfolgreich initialisiert...");

	return iResult;
}

int CFallenKingdom::doGameLoop() {
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
			// Event an die Welt weiterleiten
			m_pWorld->eventHandler(m_sfEvent);
		}
		// Bild rendern
		//m_pRenderer->render();
		m_sfWindow->clear();
		m_pWorld->update();
		m_sfWindow->display();
	}
	DebugUtilities::printInfo("Nachrichtenschleife wird verlassen...");
	return iResult;
}