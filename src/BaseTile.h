#include "Player.h"

#ifndef BASE_TILE
#define BASE_TILE

class BaseTile
{
	protected:
		int noOfPieces;
		Player *owner;
	public:
		BaseTile();
		virtual ~BaseTile();
		BaseTile(int noOfStartingPieces, Player *p);
		int getNoOfPieces();
		virtual void decrementNoOfPieces();
		virtual void incrementNoOfPieces();
		Player *getOwner();
		virtual void setOwner(Player *p);
};

#endif
