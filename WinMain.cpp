#include <iostream>
#include <Windows.h>
#include "FallenKingdom.h"
#include "DebugUtilities.h"

int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	FallenKingdom Game;

	// Spiel initialisieren
	if (Game.init()) {
		// Fehler aufgetreten
		DebugUtilities::printErr("Spiel konnte nicht gestartet werden...");
		return 1;
	}

	// Spiel ausf�hren
	return Game.doGameLoop();
}