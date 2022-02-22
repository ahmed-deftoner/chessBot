#pragma once
#include "gameState.h"
#include <string>

class UI {
private:
	void showPiece(int pieceCode);
public:
	gameState* state;
	void updateView(std::string whitePlayerName, std::string blackPlayerName);
};

