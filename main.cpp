#include "actionList.h"
#include <iostream>
#include <iomanip>
#include "chess.h"
#include "autoPlayer.h"
#include "humanPlayer.h"

using namespace std;

/*
int pawnVals[8][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0},
	{5, 10, 10, -20, -20, 10, 10, 5},
	{5, -5, -10, 0, 0, -10, -5, 5},
	{0, 0, 0, 20, 20, 0, 0, 0 },
	{5, 5, 10, 25, 25, 10, 5, 5},
	{10, 10, 20, 30, 30, 20, 10, 10},
	{50, 50, 50, 50, 50, 50, 50, 50},
	{0, 0, 0, 0, 0, 0, 0, 0 } };	 */

int main() {
	/*for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			cout << pawnVals[i][j] << " ";
		}
		cout << endl;
	}		   */

	chess Game;
	Game.Players[0] = new humanPlayer("Human Player Name", White);
	Game.Players[1] = new autoPlayer();
	Game.playGame();  
	return 0;
}
