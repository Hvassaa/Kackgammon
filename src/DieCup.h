#include "Die.h"
#include <vector>

class DieCup
{
	public:
		DieCup();
		std::vector<Die> dice;
		void roll();
};
