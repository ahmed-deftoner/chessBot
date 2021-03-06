#pragma once
#include "chessPlayer.h"
#include "ENUM.h"
#include "chessBoard.h"
#include <algorithm>
#include <iostream>
using namespace std;

class MasterShifu:public chessPlayer
{
public:
	MasterShifu(Color playerColor = White);
	void decideMove(gameState* state, action* Move, int maxDepth);
	int minimax(
		gameState* state, action* Move, int maxDepth,
		int depth,
		Color playerColor,
		chessBoard Board,
		bool maximizingPlayer, int alpha,
		int beta);
	bool checkMate(Color playerColor, gameState* state);
	int evaluate(chessBoard Board, Color playerColor);
};

