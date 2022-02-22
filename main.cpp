#include "actionList.h"
#include <iostream>
#include <iomanip>
#include "chess.h"
#include "autoPlayer.h"
#include "humanPlayer.h"

using namespace std;

int main() {
	chess Game;
	Game.Players[0] = new humanPlayer("Human Player Name", White);
	Game.Players[1] = new autoPlayer();
	Game.playGame();
	return 0;
}
