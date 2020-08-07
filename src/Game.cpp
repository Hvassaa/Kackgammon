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

	//set the owner of Tiles for dead pieces
	map[0] = new DeadTile(&player1);
	map[27] = new DeadTile(&player2);
	//set the owner of Tiles for finished pieces
	map[26] = new FinishTile(&player1);
	map[1] = new FinishTile(&player2);
}
 
// try to move a piece between from and to, return indicates success
bool Game::tryMovePiece(int from, int to, bool doMove)
{
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
		int needEyes = abs(from - to) - movingFromDeadTileBoost;
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
		if(t->getOwner() == playerInTurn)
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
