#include "Tile.h"

Tile::Tile() : BaseTile() {} 

Tile::Tile(int noOfStartingPieces, Player *p) : BaseTile(noOfStartingPieces, p) {} 

void Tile::decrementNoOfPieces()
{
	BaseTile::decrementNoOfPieces();
	if(noOfPieces == 0)
	{
		owner = nullptr;
	}
}
