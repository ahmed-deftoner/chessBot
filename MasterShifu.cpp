#include "MasterShifu.h"

namespace evaluationMetrics {
	//  P - KN - B - R - Q - K
	int weightsW[6] = { 4,7,9,10,20,6 };
	int checkmateW = -50;

	int pawnValsW[8][8] = {
	{0, 0, 0, 0, 0, 0, 0, 0},
	{5, 10, 10, -20, -20, 10, 10, 5},
	{5, -5, -10, 0, 0, -10, -5, 5},
	{0, 0, 0, 20, 20, 0, 0, 0 },
	{5, 5, 10, 25, 25, 10, 5, 5},
	{10, 10, 20, 30, 30, 20, 10, 10},
	{50, 50, 50, 50, 50, 50, 50, 50},
	{0, 0, 0, 0, 0, 0, 0, 0 } };

	int knightValsW[8][8] = {
	{-50, -40, -30, -30, -30, -30, -40, -50 },
	{-40, -20, 0, 0, 0, 0, -20, -40},
	{-30, 0, 10, 15, 15, 10, 0, -30},
	{-30, 5, 15, 20, 20, 15, 5, -30},
	{-30, 0, 15, 20, 20, 15, 0, -30},
	{-30, 5, 10, 15, 15, 10, 5, -30},
	{-40, -20, 0, 5, 5, 0, -20, -40},
	{-50, -40, -30, -30, -30, -30, -40, -50 } };

	int bishopValsW[8][8] = {
	{-20, -10, -10, -10, -10, -10, -10, -20},
	{-10, 5, 0, 0, 0, 0, 5, -10},
	{-10, 10, 10, 10, 10, 10, 10, -10},
	{-10, 0, 10, 10, 10, 10, 0, -10},
	{-10, 5, 5, 10, 10, 5, 5, -10},
	{-10, 0, 5, 10, 10, 5, 0, -10},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-20, -10, -10, -10, -10, -10, -10, -20 } };

	int rookValsW[8][8] = {
	{0, 0, 0, 5, 5, 0, 0, 0},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{-5, 0, 0, 0, 0, 0, 0, -5},
	{5, 10, 10, 10, 10, 10, 10, 5},
	{0, 0, 0, 0, 0, 0, 0, 0 } };

	int queenValsW[8][8] = {
	{-20, -10, -10, -5, -5, -10, -10, -20},
	{-10, 0, 0, 0, 0, 0, 0, -10},
	{-10, 0, 5, 5, 5, 5, 0, -10},
	{-5, 0, 5, 5, 5, 5, 0, -5},
	{0, 0, 5, 5, 5, 5, 0, -5},
	{-10, 5, 5, 5, 5, 5, 0, -10},
	{-10, 0, 5, 0, 0, 0, 0, -10},
	{-20, -10, -10, -5, -5, -10, -10, -20 } };

	int kingValsW[8][8] = {
	{20, 30, 10, 0, 0, 10, 30, 20},
	{20, 20, 0, 0, 0, 0, 20, 20},
	{-10, -20, -20, -20, -20, -20, -20, -10},
	{20, -30, -30, -40, -40, -30, -30, -20},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30},
	{-30, -40, -40, -50, -50, -40, -40, -30 } };

	int pawnValsB[8][8];
	int knightValsB[8][8];
	int bishopValsB[8][8];
	int rookValsB[8][8];
	int queenValsB[8][8];
	int kingValsB[8][8];
	int weightsB[6];
	int checkmateB;

	void generatorBlack() {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				pawnValsB[i][j] = pawnValsW[i][j] * -1;
				knightValsB[i][j] = knightValsW[i][j] * -1;
				bishopValsB[i][j] = bishopValsW[i][j] * -1;
				rookValsB[i][j] = rookValsW[i][j] * -1;
				queenValsB[i][j] = queenValsW[i][j] * -1;
				kingValsB[i][j] = kingValsW[i][j] * -1;
			}
		}
		for (int i = 0; i < 6; ++i)
			weightsB[i] = weightsW[i] * -1;
		checkmateB = checkmateW * -1;
	}
}

MasterShifu::MasterShifu(Color playerColor):chessPlayer("Master Shifu",playerColor) {
	evaluationMetrics::generatorBlack();
}

void MasterShifu::decideMove(gameState* state, action* Move, int maxDepth) {
	int bestMove = INT_MIN;
	action* bestMoveFound = Move;
	gameState statecpy;
	chessBoard board1;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			statecpy.Board.board[i][j] = state->Board.board[i][j];

	int x = 0;
	for (int i = 0; i < state->Actions.getActionCount();++i) {

		statecpy.Actions.getAction(i, Move);
		int value = minimax(&statecpy, Move, 6, 0, state->getPlayer(), state->Board, true, INT_MIN, INT_MAX);
		if (value >= bestMove) {
			bestMove = value;
			x = i;
			bestMoveFound = Move;
		}
	}
	state->Actions.getAction(x, bestMoveFound);
}

int MasterShifu::evaluate(chessBoard Board,Color playerColor) {
	int total = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			int pieceVal = Board.board[i][j];
			switch (pieceVal)
			{
			case 1:
				if (playerColor == White) 
					total += pieceVal * evaluationMetrics::pawnValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::pawnValsB[i][j];
				continue;
			case 2:
				if (playerColor == White)
					total += pieceVal * evaluationMetrics::knightValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::knightValsB[i][j];
				continue;
			case 3:
				if (playerColor == White)
					total += pieceVal * evaluationMetrics::bishopValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::bishopValsB[i][j];
				continue;
			case 4:
				if (playerColor == White)
					total += pieceVal * evaluationMetrics::rookValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::rookValsB[i][j];
				continue;
			case 5:
				if (playerColor == White)
					total += pieceVal * evaluationMetrics::queenValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::queenValsB[i][j];
				continue;
			case 6:
				if (playerColor == White)
					total += pieceVal * evaluationMetrics::kingValsW[i][j];
				else
					total -= pieceVal * evaluationMetrics::kingValsB[i][j];
				continue;
			default:
				continue;
			}
		}
	}
	return total;
}

bool MasterShifu::checkMate(Color playerColor, gameState* state) {
	if (state->kingUnderThreat(playerColor) == true)
		return true;
	return false;
}

int MasterShifu::minimax(
	gameState* state, action* Move, int maxDepth,
	int depth, 
	Color playerColor,
	chessBoard Board,
	bool maximizingPlayer, int alpha,
	int beta)
{
	if (checkMate(playerColor, state) == true)
		if (maximizingPlayer)
			return evaluationMetrics::checkmateB;
		else
			return evaluationMetrics::checkmateW;
	if (state->Actions.getActionCount() == 0)
		return 0;
	// Terminating condition. i.e
	// leaf node is reached
	if (depth == maxDepth)
		return evaluate(Board,playerColor);

	if (maximizingPlayer)
	{
		int best = INT_MIN;

		// Recur for left and
		// right children
		for (int i = 0; i < state->Actions.getActionCount(); i++)
		{
			state->Actions.getAction(i, Move);
			int val = minimax(state, Move, maxDepth,
				depth + 1,
				Black,
				Board,
				false, alpha, beta);
			best = max(best, val);
			alpha = max(alpha, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
	else
	{
		int best = INT_MAX;

		// Recur for left and
		// right children
		for (int i = 0; i < state->Actions.getActionCount(); i++)
		{
			state->Actions.getAction(i, Move);
			int val = minimax(
				state, Move, maxDepth,
				depth + 1,
				White,
				Board,
				true, alpha, beta);
			best = min(best, val);
			beta = min(beta, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
}
