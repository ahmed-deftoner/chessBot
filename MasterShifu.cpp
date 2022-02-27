#include "MasterShifu.h"

namespace evaluationMetrics {
	//  P - KN - B - R - Q - K
	const int pawn = 95, bishop = 330, knight = 320, rook = 500, queen = 900, king = 2000;
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

}

MasterShifu::MasterShifu(Color playerColor):chessPlayer("Master Shifu",playerColor) {
}

void MasterShifu::decideMove(gameState* state, action* Move, int maxDepth) {
	int bestMove = INT_MAX;
	if (state->getPlayer() == White)
		bestMove = INT_MIN;
	Move->fromCol = 0;
	Move->fromRow = 0; 
	Move->toCol = 0;
	Move->toRow = 0;
	
	action* bestMoveFound = Move;
	gameState statecpy;
	chessBoard board1;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			statecpy.Board.board[i][j] = state->Board.board[i][j];

	int x = 0;
	for (int i = 0; i < state->Actions.getActionCount();++i) {
		int r1 = Move->fromRow;
		int c1 = Move->fromCol;
		int r2 = Move->toRow;
		int c2 = Move->toCol;
		int b = statecpy.Board.board[r1][c1];
		//cout << b;
		int c = statecpy.Board.board[r2][c2];
		statecpy.Actions.getAction(i, Move);
		int value = minimax(&statecpy, Move, 5, 0, state->getPlayer(), state->Board, true, INT_MIN, INT_MAX);
		statecpy.Board.board[r1][c1] = b;
		statecpy.Board.board[r2][c2] = c;
		if (state->getPlayer()==White && value >= bestMove) {
			bestMove = value;
			x = i;
			bestMoveFound = Move;
		}
		else if (state->getPlayer() == Black && value <= bestMove) {
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
				total -= evaluationMetrics::pawnValsW[i][j];
				total -= evaluationMetrics::pawn;
				continue;
			case 2:
				total -= evaluationMetrics::knightValsW[i][j];
				total -= evaluationMetrics::knight;
				continue;
			case 3:
				total -= evaluationMetrics::bishopValsW[i][j];
				total -= evaluationMetrics::bishop;
				continue;
			case 4:
				total -= evaluationMetrics::rookValsW[i][j];
				total -= evaluationMetrics::rook;
				continue;
			case 5:
				total -= evaluationMetrics::queenValsW[i][j];
				total -= evaluationMetrics::queen;
				continue;
			case 6:
				total -= evaluationMetrics::kingValsW[i][j];
				total -= evaluationMetrics::king;
				continue;
			case -1:
				total += evaluationMetrics::pawnValsW[7-i][7-j];
				total += evaluationMetrics::pawn;
				continue;
			case -2:
				total += evaluationMetrics::knightValsW[7 - i][7 - j];
				total += evaluationMetrics::knight;
				continue;
			case -3:
				total += evaluationMetrics::bishopValsW[7 - i][7 - j];
				total += evaluationMetrics::bishop;
				continue;
			case -4:
				total += evaluationMetrics::rookValsW[7 - i][7 - j];
				total += evaluationMetrics::rook;
				continue;
			case -5:
				total += evaluationMetrics::queenValsW[7 - i][7 - j];
				total += evaluationMetrics::queen;
				continue;
			case -6:
				total += evaluationMetrics::kingValsW[7 - i][7 - j];
				total += evaluationMetrics::king;
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
			return evaluationMetrics::checkmateW;
		else
			return -evaluationMetrics::checkmateW;
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
			int r1 = Move->fromRow;
			int c1 = Move->fromCol;
			int r2 = Move->toRow;
			int c2 = Move->toCol;
			int b = state->Board.board[r1][c1];
			//cout << b;
			int c = state->Board.board[r2][c2];
			state->Actions.getAction(i, Move);
			int val = minimax(state, Move, maxDepth,
				depth + 1,
				Black,
				Board,
				false, alpha, beta);
			state->Board.board[r1][c1] = b;
			state->Board.board[r2][c2] = c;
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
			int r1 = Move->fromRow;
			int c1 = Move->fromCol;
			int r2 = Move->toRow;
			int c2 = Move->toCol;
			int b = state->Board.board[r1][c1];
			//cout << b;
			int c = state->Board.board[r2][c2];
			state->Actions.getAction(i, Move);
			int val = minimax(
				state, Move, maxDepth,
				depth + 1,
				White,
				Board,
				true, alpha, beta);
			state->Board.board[r1][c1] = b;
			state->Board.board[r2][c2] = c;
			best = min(best, val);
			beta = min(beta, best);

			// Alpha Beta Pruning
			if (beta <= alpha)
				break;
		}
		return best;
	}
}
