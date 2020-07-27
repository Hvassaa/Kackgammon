#include "DeadTile.h"
#include <iostream>

DeadTile::DeadTile(Player *p) : BaseTile(0, p) {}

void DeadTile::setOwner(Player *p)
{
	std::cout << "ERROR: Tried setting " << (*p).getPlayerColor() << " as error of a DeadTile" << std::endl;
}
