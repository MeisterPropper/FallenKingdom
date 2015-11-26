#include <iostream>
#include <Windows.h>
#include "FallenKingdom.h"

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	FallenKingdom Game;

	// Spiel initialisieren
	if (Game.init()) {
		// Fehler aufgetreten
		return 1;
	}

	// Spiel ausführen
	return Game.doGameLoop();
}