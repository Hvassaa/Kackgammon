#include "Game.h"
#include <cstdlib>
#include <iostream>

Game::Game() : player1(Player("Red")), player2(Player("Black"))
{
	player1.setQtStyleSheet("IdPushButton { color : red; }");
	player2.setQtStyleSheet("IdPushButton { color : blue; }");
	// set player1 as first player in turn
	playerInTurn = &player1;

	// set up the board
	
	for (int i = 0; i < 28; i++)
	{
		if(i == 2) {continue;}
		if(i == 25) {continue;}
		if(i == 20) {continue;}
		if(i == 7) {continue;}
		if(i == 18) {continue;}
		if(i == 9) {continue;}
		if(i == 13) {continue;}
		if(i == 14) {continue;}
		if(i == 0) {continue;}
		if(i == 27) {continue;}
		if(i == 26) {continue;}
		if(i == 1) {continue;}
		map[i] = new Tile();
	}

	map[2] = new Tile(2, &player1);
	map[25] = new Tile(2, &player2);

	map[20] = new Tile(5, &player1);
	map[7] = new Tile(5, &player2);

	map[18] = new Tile(3, &player1);
	map[9] = new Tile(3, &player2);

	map[13] = new Tile(5, &player1);
	map[14] = new Tile(5, &player2);

	/* TESTING POSITIONS
	map[2] = new Tile(2, &player1);
	map[3] = new Tile(2, &player1);
	map[4] = new Tile(2, &player1);
	map[5] = new Tile(2, &player1);
	map[6] = new Tile(2, &player1);
	map[7] = new Tile(2, &player1);

	map[8] = new Tile(15, &player2);
	map[25] = new Tile(15, &player1);

	map[20] = new Tile();

	map[18] = new Tile();
	map[9] = new Tile();

	map[13] = new Tile();
	map[14] = new Tile();
	*/


	//set the owner of Tiles for dead pieces
	map[0] = new DeadTile(&player1);
	map[27] = new DeadTile(&player2);
	//set the owner of Tiles for finished pieces
	map[26] = new FinishTile(&player1);
	map[1] = new FinishTile(&player2);
}

Game::~Game()
{
	delete[] *map;
}
 
// try to move a piece between from and to, return indicates success
bool Game::tryMovePiece(int from, int to, bool doMove)
{
	if(to < 0 || to > 27) {return false;}
	// you have to move dead pieces first
	int player1DeadPos = 0;
	int player2DeadPos = 27;
	if(playerInTurn == &player1 && getTileAt(player1DeadPos)->getNoOfPieces() > 0 && from != player1DeadPos) {return false;}
	if(playerInTurn == &player2 && getTileAt(player2DeadPos)->getNoOfPieces() > 0 && from != player2DeadPos) {return false;}

	// dont move from the finish-Tiles
	if(from == 1 || from == 26) {return false;}
	// dont move to dead Tiles
	if(to == player1DeadPos || to == player2DeadPos) {return false;}
	// only move if you own pieces at from
	if(map[from]->getOwner() != playerInTurn) {return false;}
	// check right move direction for player1
	if(*playerInTurn == player1 && from - to >= 0) {return false;}
	// check right move direction for player2
	if(*playerInTurn == player2 && from - to <= 0) {return false;}
	// check that you can finish pieces
	bool isFinishingPiece = false;
	if( (to == 1 || to == 26) )
	{
		if(currentPlayerCanFinishPieces())
		{
			isFinishingPiece = true;
		}
		else
		{
			return false;
		}
	}

	bool tryMove = false;
	// this will be subtracted to the from-to difference
	// since the dead tile is "one extra behind"
	int movingFromDeadTileBoost = (from == 0 || from == 27) ? 1 : 0;

	// if to is empty, try move
	if(map[to]->getOwner() == nullptr)
	{
		tryMove = true;
	}
	// if to is owned by player in turn, try move
	else if(map[to]->getOwner() == playerInTurn)
	{
		tryMove = true;
	}
	// if to is owned by the other player,
	// try move only if there is only 1 piece
	else if(map[to]->getOwner() != playerInTurn 
			&& map[to]->getNoOfPieces() == 1)
	{
		tryMove = true;
	}

	if(tryMove)
	{
		// too advanced method to finish pieces with higher die-rolls
		// then the exact match
		int needEyes = abs(from - to) - movingFromDeadTileBoost;
		if(isFinishingPiece)
		{
			int endHomePos = (playerInTurn == &player1) ? 19 : 8; 
			int moveMultiplier = (playerInTurn == &player1) ? -1 : 1; 

			int lowestUseableEyes = 7;
			for (Die const &d : dieCup.dice)
			{
				int dEyes = d.getEyes();
				if (dEyes > needEyes && dEyes < lowestUseableEyes && d.isUnused())
				{
					bool noPiecesAbove = true;
					for (int i = from + moveMultiplier; i != endHomePos; i = i + moveMultiplier)
					{
						if(getTileAt(i)->getOwner() == playerInTurn && getTileAt(i)->getNoOfPieces() > 0) {noPiecesAbove = false;}
					}
					if(noPiecesAbove) {lowestUseableEyes = dEyes;}
				}
			}
			if(lowestUseableEyes != 7) {
				needEyes = lowestUseableEyes;
			}
		}
		bool moveSuccess = (dieCup.tryUseDieWithEyes(needEyes, doMove));
		if(moveSuccess && doMove)
		{
			// kill enemy if present
			if(map[to]->getOwner() != playerInTurn 
				&& map[to]->getNoOfPieces() == 1)
			{
				if(playerInTurn == &player1)
				{
					map[player2DeadPos]->incrementNoOfPieces();
				}
				else 
				{
					map[player1DeadPos]->incrementNoOfPieces();
				}
				map[to]->decrementNoOfPieces();
			}

			map[from]->decrementNoOfPieces();
			map[to]->incrementNoOfPieces();
			map[to]->setOwner(playerInTurn);
		}
		return moveSuccess;
	}
	return false;
}

BaseTile* Game::getTileAt(int position)
{
	return map[position];
}

DieCup Game::getDieCup() const
{
	return dieCup;
}

Player Game::getPlayerInTurn() const
{
	return *playerInTurn;
}

bool Game::changeTurn()
{
	bool validChange = !validMoveExists();
	//std::cout << "Valid change: " << validChange << std::endl;
	if(validChange) {
		if(playerInTurn == &player1)
		{
			playerInTurn = &player2;
		}
		else
		{
			playerInTurn = &player1;
		}
		dieCup.roll();
	}

	return validChange;
}

bool Game::validMoveExists()
{
	int moveMultiplier, start, end;
	if(playerInTurn == &player1) {
		moveMultiplier = 1;
		start = 0;
		end = 26;
	}
	else
	{
		moveMultiplier = -1;
		start = 27;
		end = 1;
	}
	for(int i = start; i != end; i = i + moveMultiplier)
	{
		BaseTile *t = getTileAt(i);
		if(t->getOwner() == playerInTurn && t->getNoOfPieces() > 0)
		{
			for(Die const &d : dieCup.dice)
			{
				int newPos = i + (d.getEyes() * moveMultiplier);
				// if moving from dead, move one furter
				if(i == 0 || 28) { newPos = newPos + moveMultiplier; }
				//std::cout << "From " << i << ", to " << newPos << " - " << (d.isUnused() && tryMovePiece(i, newPos, false)) << std::endl;
				if(d.isUnused() && tryMovePiece(i, newPos, false)) {return true;}
			}
		}
	}
	return false;
}

bool Game::currentPlayerCanFinishPieces()
{
	int start, end, finishPosition;
	
	if(playerInTurn == &player1)
	{
		start = 20;
		end = 26;
		finishPosition = 26;
	}
	else
	{
		start = 2;
		end = 8;
		finishPosition = 1;
	}

	int piecesHome = 0;
	for (int i = start; i != end; i++)
	{
		if(getTileAt(i)->getOwner() == playerInTurn)
		{
			piecesHome += getTileAt(i)->getNoOfPieces();
		}
	}
	piecesHome += getTileAt(finishPosition)->getNoOfPieces();
	std::cout << piecesHome << std::endl;

	return piecesHome == 15;
}
