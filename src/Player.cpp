#include <iostream>
#include <string>
#include "Player.h"

Player::Player(std::string color)
{
	playerColor = color;
}

std::string Player::getPlayerColor() 
{
	return playerColor;
}

int Player::getFinishedPieces() 
{
	return finishedPieces;
}

// finish a piece (a piece has moved out)
void Player::finishPiece()
{
	finishedPieces = finishedPieces + 1;
}

int Player::getDeadPieces() 
{
	return deadPieces;
}

void Player::incrementDeadPieces()
{
	deadPieces = deadPieces + 1;
}

void Player::decrementDeadPieces()
{
	deadPieces = deadPieces - 1;
}

// bool indicating if all pieces is in the 
// home (the last 6 positions for a player)
// or finished
bool Player::isAllPiecesHome(int board[])
{
	int startPos;
	if(getPlayerColor() == "Red")
	{
		startPos = 0;
	}
	else
	{
		startPos = 18;
	}
	int numberOfPiecesInHome = 0;
	for(int i = 0; i < 5; i++)
	{
		numberOfPiecesInHome = getFinishedPieces() + board[startPos + i];
	}
	return numberOfPiecesInHome + getFinishedPieces() == 7;
}
