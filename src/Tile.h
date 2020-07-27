#include "BaseTile.h"

class Tile : public BaseTile
{
	public:
		Tile();
		Tile(int noOfStartingPieces, Player *p);
		void decrementNoOfPieces() override;
};
