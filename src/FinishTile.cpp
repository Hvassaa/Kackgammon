#include "FinishTile.h"
#include <iostream>

FinishTile::FinishTile(Player *p) : BaseTile(0, p) {}

void FinishTile::decrementNoOfPieces() 
{
	std::cout << "ERROR: decrementNoOfPieces called on FinishTile" << std::endl;
}

void FinishTile::setOwner(Player *p)
{
	std::cout << "ERROR: setOwner called on FinishTile, with" << p->getPlayerColor() << std::endl;
}
