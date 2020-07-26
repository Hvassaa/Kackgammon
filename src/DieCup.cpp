#include "DieCup.h"
#include <cstdlib>
#include <ctime>

DieCup::DieCup()
{
	// initialize random seed for dice
	srand((unsigned) time(0));
	dice.push_back(Die());
	dice.push_back(Die());
}

void DieCup::roll()
{
	// reset to 2 dice
	dice.resize(2);
	for (Die &d : dice)
	{
		d.roll();
	}
	// check if it's a double and add two more dice if it is
	if(dice.at(0).getEyes() == dice.at(1).getEyes())
	{
		dice.push_back(Die(dice.at(0)));
		dice.push_back(Die(dice.at(0)));
	}
}

bool DieCup::tryUseDieWithEyes(int eyes)
{
	for (Die &d : dice)
	{
		if(d.isUnused() && d.getEyes() == eyes)
		{
			d.use();
			return true;
		}
	}
	return false;
}
