#include "Tile.h"
#include "DeadTile.h"
#include "DieCup.h"

class Game
{
	private:
		BaseTile map[28];
		DieCup dieCup;
		Player player1;
		Player player2;
		Player *playerInTurn;
		const int NUM_OF_PIECES = 7;
	public:
		Game();
		bool tryMovePiece(int from, int to);
		BaseTile getTileAt(int position);
		DieCup getDieCup() const;
		Player getPlayerInTurn() const;
};
