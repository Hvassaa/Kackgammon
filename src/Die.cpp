#include <cstdlib>
#include "Die.h"

Die::Die(int fixedEyes)
{
	eyes = fixedEyes;
	unused = true;
}

int Die::getEyes()
{
	return eyes;
}

bool Die::isUnused()
{
	return unused;
}

// this method relies on a random seed already being set
// ie srand should be called before, somewhere else
// (in Game)
// It also set used to false
void Die::roll()
{
	eyes = 1 + (rand() % 6);
	unused = true;
}

void Die::use()
{
	unused = false;
}
