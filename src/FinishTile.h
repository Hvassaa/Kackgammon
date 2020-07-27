#include "BaseTile.h"

class FinishTile : public BaseTile
{
	public:
		FinishTile(Player *p);
		void decrementNoOfPieces() override;
		void setOwner(Player *p) override;
};
