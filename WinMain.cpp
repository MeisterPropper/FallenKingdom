#include <iostream>
#include <Windows.h>
#include "CFallenKingdom.h"
#include "DebugUtilities.h"

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	CFallenKingdom Game;

	// Spiel initialisieren
	if (Game.init()) {
		// Fehler aufgetreten
		DebugUtilities::printErr("Spiel konnte nicht gestartet werden...");
		return 1;
	}

	loadMatFromFile("Data/Materials/devmat001.mat");

	// Spiel ausführen
	return Game.doGameLoop();
}