#include "Tile.h"
#include "DieCup.h"

class Game
{
	private:
		Tile map[28];
		DieCup dieCup;
		Player player1;
		Player player2;
		Player *playerInTurn;
		const int NUM_OF_PIECES = 7;
	public:
		Game();
		bool tryMovePiece(int from, int to);
		Tile getTileAt(int position);
		DieCup getDieCup() const;
};
