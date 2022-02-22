#pragma once
#include "chessPlayer.h"
#include "ENUM.h"

class autoPlayer : public chessPlayer {
public:
	autoPlayer(Color playerColor = White);
	void decideMove(gameState* state, action* Move, int maxDepth);
};

