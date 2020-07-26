#include "Tile.h"

Tile::Tile()
{
	noOfPieces = 0;
	owner = nullptr;
}

Tile::Tile(int noOfStartingPieces, Player *p)
{
	noOfPieces = noOfStartingPieces;
	owner = p;
}

int Tile::getNoOfPieces()
{
	return noOfPieces;
}

void Tile::incrementNoOfPieces()
{
	noOfPieces = noOfPieces + 1;
}

void Tile::decrementNoOfPieces()
{
	noOfPieces = noOfPieces - 1;
	// this good?
	if(noOfPieces == 0)
	{
		owner = nullptr;
	}
}

Player * Tile::getOwner()
{
	return owner;
}

void Tile::setOwner(Player *p)
{
	owner = p;
}
