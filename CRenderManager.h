#pragma once

#include <SFML\Graphics.hpp>
#include <list>

class CRenderManager{
public:
	// Konstruktor
	//
	CRenderManager();
	// Destruktor
	//
	~CRenderManager();

	/// Methoden

	// addDrawable()
	void addDrawable(sf::Drawable* ptr);
	// delDrawable()
	void delDrawable(sf::Drawable* ptr);

	// init()
	// xxxxxxxxxxxxx
	// Initialisiert den Renderer
	// xxxxxxxxxxxxx
	// @ptr - Zeiger auf ein bestehendes Fenster
	// xxxxxxxxxxxxx
	// return - Status: 0 wenn alles geklappt hat
	int  init(sf::RenderWindow * ptr);

	// render()
	// xxxxxxxxxxxxx
	// Rendert alle Objekte und zeichnet das Bild neu
	void render();

	/// Setter und Getter

	// setFillColor()
	void		setFillColor(sf::Color color);
	// getFillColor()
	sf::Color	getFillColor();


private:
	sf::RenderWindow *		 m_pWindow;		// Zeiger auf ein bestehendes Fenster
	sf::Color				 m_sfFillColor;	// Hintergrundfarbe des Bildschirmes
	std::list<sf::Drawable*> m_sfDrawList;	// Liste mit allen zu rendernden Daten
};

