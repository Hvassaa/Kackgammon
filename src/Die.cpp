#include <cstdlib>
#include <ctime>
#include "Die.h"

Die::Die() 
{
	eyes = 0;
	used = false;
	isDoubleRoll = false;
}

int Die::getEyes()
{
	return eyes;
}

bool Die::isUsed()
{
	return used;
}

void Die::setUnused()
{
	used = false;
}

void Die::setUsed()
{
	if(isDoubleRoll)
	{
		isDoubleRoll = false;
	}
	else
	{
		used = true;
	}
}

void Die::setAsDoubleRoll()
{
	isDoubleRoll = true;
}

bool Die::isUnusedDouble()
{
	return isDoubleRoll;
}

// this method relies on a random seed already being set
// ie srand should be called before, somewhere else
// (in Game)
// It also set used to false
void Die::rollDie()
{
	eyes = 1 + (rand() % 6);
	setUnused();
}
