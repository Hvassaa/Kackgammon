#include "BaseTile.h"

class DeadTile : public BaseTile
{
	public:
		DeadTile(Player *p);
		void setOwner(Player *p) override;
};
