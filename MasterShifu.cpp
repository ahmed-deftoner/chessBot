#include "MasterShifu.h"

MasterShifu::MasterShifu(Color playerColor):chessPlayer("Master Shifu",playerColor) {

}

void MasterShifu::decideMove(gameState* state, action* Move, int maxDepth) {

}

int MasterShifu::minimax(
	gameState* state, action* Move, int maxDepth,
	int depth, 
	bool maximizingPlayer, int alpha,
	int beta)
{

	// Terminating condition. i.e
	// leaf node is reached
	if (depth == maxDepth)
		return 5;

	if (maximizingPlayer)
	{
		int best = INT_MIN;

		// Recur for left and
		// right children
		for (int i = 0; i < state->Actions.getActionCount(); i++)
		{

			int val = minimax(state, Move, maxDepth,
				depth + 1,
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
			int val = minimax(
				state, Move, maxDepth,
				depth + 1,
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
