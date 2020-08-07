#include "BaseTile.h"

BaseTile::BaseTile()
{
	noOfPieces = 0;
	owner = nullptr;
}

BaseTile::~BaseTile()
{
}

BaseTile::BaseTile(int noOfStartingPieces, Player *p)
{
	noOfPieces = noOfStartingPieces;
	owner = p;
}

int BaseTile::getNoOfPieces()
{
	return noOfPieces;
}

void BaseTile::incrementNoOfPieces()
{
	noOfPieces = noOfPieces + 1;
}

void BaseTile::decrementNoOfPieces()
{
	noOfPieces = noOfPieces - 1;
}

Player * BaseTile::getOwner()
{
	return owner;
}

void BaseTile::setOwner(Player *p)
{
	owner = p;
}
