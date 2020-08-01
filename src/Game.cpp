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
		map[i] = Tile();
	}

	map[2] = Tile(2, &player1);
	map[25] = Tile(2, &player2);

	map[20] = Tile(5, &player1);
	map[7] = Tile(5, &player2);

	map[18] = Tile(3, &player1);
	map[9] = Tile(3, &player2);

	map[13] = Tile(5, &player1);
	map[14] = Tile(5, &player2);

	//set the owner of Tiles for dead pieces
	map[0] = DeadTile(&player1);
	map[27] = DeadTile(&player2);
	//set the owner of Tiles for finished pieces
	map[26] = FinishTile(&player1);
	map[1] = FinishTile(&player2);
}
 
// try to move a piece between from and to, return indicates success
bool Game::tryMovePiece(int from, int to, bool doMove)
{
	// you have to move dead pieces first
	int player1DeadPos = 0;
	int player2DeadPos = 27;
	if(playerInTurn == &player1 && getTileAt(player1DeadPos).getNoOfPieces() > 0 && from != player1DeadPos) {return false;}
	if(playerInTurn == &player2 && getTileAt(player2DeadPos).getNoOfPieces() > 0 && from != player2DeadPos) {return false;}

	// dont move from the finish-Tiles
	if(from == 1 || from == 26) {return false;}
	// dont move to dead Tiles
	if(to == player1DeadPos || to == player2DeadPos) {return false;}
	// only move if you own pieces at from
	if(map[from].getOwner() != playerInTurn) {return false;}
	// check right move direction for player1
	if(*playerInTurn == player1 && from - to >= 0) {return false;}
	// check right move direction for player2
	if(*playerInTurn == player2 && from - to <= 0) {return false;}

	bool tryMove = false;
	// this will be subtracted to the from-to difference
	// since the dead tile is "one extra behind"
	int movingFromDeadTileBoost = (from == 0 || from == 27) ? 1 : 0;

	// if to is empty, try move
	if(map[to].getOwner() == nullptr)
	{
		tryMove = true;
	}
	// if to is owned by player in turn, try move
	else if(map[to].getOwner() == playerInTurn)
	{
		tryMove = true;
	}
	// if to is owned by the other player,
	// try move only if there is only 1 piece
	else if(map[to].getOwner() != playerInTurn 
			&& map[to].getNoOfPieces() == 1)
	{
		tryMove = true;
	}

	if(tryMove)
	{
		int needEyes = abs(from - to) - movingFromDeadTileBoost;
		bool moveSuccess = (dieCup.tryUseDieWithEyes(needEyes));
		if(moveSuccess && doMove)
		{
			// kill enemy if present
			if(map[to].getOwner() != playerInTurn 
				&& map[to].getNoOfPieces() == 1)
			{
				if(playerInTurn == &player1)
				{
					map[player2DeadPos].incrementNoOfPieces();
				}
				else 
				{
					map[player1DeadPos].incrementNoOfPieces();
				}
				map[to].decrementNoOfPieces();
			}

			map[from].decrementNoOfPieces();
			map[to].incrementNoOfPieces();
			map[to].setOwner(playerInTurn);
		}
		return moveSuccess;
	}
	return false;
}

BaseTile Game::getTileAt(int position)
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
	if(playerInTurn == &player1)
	{
		playerInTurn = &player2;
	}
	else
	{
		playerInTurn = &player1;
	}
	dieCup.roll();

	return false;
}

bool Game::validMoveExists()
{


	return false;
}
