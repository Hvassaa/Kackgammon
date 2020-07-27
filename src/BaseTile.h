#include "Player.h"

class BaseTile
{
	protected:
		int noOfPieces;
		Player *owner;
	public:
		BaseTile();
		BaseTile(int noOfStartingPieces, Player *p);
		int getNoOfPieces();
		virtual void decrementNoOfPieces();
		virtual void incrementNoOfPieces();
		Player *getOwner();
		virtual void setOwner(Player *p);
};
