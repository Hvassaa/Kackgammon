#include "Player.h"
#include <memory>

class Tile
{
	private:
		int noOfPieces;
		Player *owner;
	public:
		Tile();
		Tile(int noOfStartingPieces, Player *p);
		int getNoOfPieces();
		void decrementNoOfPieces();
		void incrementNoOfPieces();
		Player *getOwner();
		void setOwner(Player *p);
};
