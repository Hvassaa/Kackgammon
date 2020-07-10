#include <cstdlib>
#include <iostream>
#include <string>
#include "Game.h"

Game::Game()
{
	// set playerInTurn as pointer to redPlayer, so redPlayer starts
	playerInTurn = & redPlayer;
	// set up the board
	board[0] = 2;    
	board[23] = -2;    

	board[18] = 5;    
	board[5] = -5;    

	board[16] = 3;    
	board[7] = -3;    

	board[11] = 5;    
	board[12] = -5;

	// initialize random seed for dice
	srand((unsigned) time(0));

	// roll the dice
	rollDice();
}

Player Game::getPlayerInTurn() 
{
	return * playerInTurn;
}

bool Game::validMove(int from, int to)
{
	// if outside the board
	if(!(from >= 0 && from <= 23 && to >= 0 && to <= 23)) {return false;}

	// if no piece at from
	if(getPiecesAt(from) == 0) {return false;}

	std::string inTurnInColor = getPlayerInTurn().getPlayerColor();

	int difference = from - to;
	bool die1Check = d1.getEyes() == abs(difference) && !d1.isUsed();
	bool die2Check = d2.getEyes() == abs(difference) && !d2.isUsed();
	if( !(die1Check || die2Check) ) {return false;}

	// compare player in turn's color
	// if red, do if
	// if black, do else
	if(inTurnInColor == redPlayer.getPlayerColor())
	{
		// RED
		// if trying to move other players piece
		if(getPiecesAt(from) < 0) {return false;}
		// if more than 1 enemy piece at to 
		if(getPiecesAt(to) < -1) {return false;}
		// right move-direction / move more than 0
		// difference for red should be in ~ [-infty, -1)
		if(difference > -1) {return false;}
	} 
	else 
	{
		// BLACK
		// if trying to move other players piece
		if(getPiecesAt(from) > 0) {return false;}
		// if more than 1 enemy piece at to 
		if(getPiecesAt(to) > 1) {return false;}
		// right move-direction / move more than 0
		// difference for black should be in ~ [1, infty) 
		if(difference < 1) {return false;}
	}
	return true;
}

bool Game::movePiece(int from, int to)
{
	bool valid = validMove(from, to);
	if(valid)
	{
		// "use" die
		int diff = abs(from - to);
		if(d1.getEyes() == diff && !d1.isUsed()) {d1.setUsed();}
		else if(d2.getEyes() == diff && !d2.isUsed()) {d2.setUsed();}

		if(getPiecesAt(from) > 0) 
		{
			// red
			if(getPiecesAt(to) == -1)
			{
				board[to] = 0;
			}
			board[from] = board[from] - 1;
			board[to] = board[to] + 1;
		}
		else if(getPiecesAt(from) > 0) 
		{
			// black
				if(getPiecesAt(to) == 1)
			{
				board[to] = 0;
			}
			board[from] = board[from] + 1;
			board[to] = board[to] - 1;
		}
		checkForWonGame();
	}
	return valid;
}

int Game::getPiecesAt(int pos)
{
	return board[pos];
}

Player * Game::getWinner()
{
	if(redPlayer.getFinishedPieces() == numberOfBricks) 
	{
		// Red wins
		return &redPlayer;
	}
	else if(blackPlayer.getFinishedPieces() == numberOfBricks)
	{
		// Black wins
		return &blackPlayer;
	}
	return nullptr;
}

void Game::checkForWonGame()
{
	if(getWinner() != nullptr)
	{
		std::cout << "WINNER IS: " + (* getWinner()).getPlayerColor() << std::endl;
		std::exit(0);
	}
}

void Game::rollDice()
{
	d1.rollDie();
	d2.rollDie();
}

Die Game::getDie1()
{
	return d1;
}

Die Game::getDie2()
{
	return d2;
}

bool Game::validPlayerChange()
{
	return d1.isUsed() && d2.isUsed();
}

bool Game::changePlayer()
{
	bool validChange = validPlayerChange();
	if(validChange)
	{
		rollDice();
		if(getPlayerInTurn().getPlayerColor() == "Red")
		{
			playerInTurn = &blackPlayer;
		}
		else
		{
			playerInTurn = &redPlayer;
		}
	}
	return validChange;
}

// FUNCTIONS TO PRINT; HOPEFULLY TEMPORARY; START

/*
 * Negative numbers indicate some amount of pieces for the black player
 * Positive numbers indicate some amount of pieces for the red player
 * First print a row of numbers indicating the "cell" number
 * then print the top row of pieces
 * then the bottom row
 * and finally numbers indicating the "cell" again
 */
void Game::printBoard() {
	for(int i = 0; i < 12; i = i + 1) {
		std::cout << i;
		if(i >= 10) {std::cout << "   ";}
		else {std::cout << "    ";}
	}
	std::cout << std::endl;
	for(int i = 0; i < 12; i = i + 1) {
		int currentPieces = getPiecesAt(i);
		std::cout << currentPieces;
		printSpaces(currentPieces);
	}
	std::cout << std::endl 
		<< "---------------------------------------------------------" 
		<< std::endl;


	for(int i = 23; i >= 12; i = i - 1) {
		int currentPieces = getPiecesAt(i);
		std::cout << currentPieces;
		printSpaces(currentPieces);
	}
	std::cout << std::endl;
	for(int i = 23; i >= 12; i = i - 1) {
		std::cout << i << "   ";
	}
	std::cout << "d1: " << d1.getEyes() << " (used: " << d1.isUsed() << "), d2: " 
		<< d2.getEyes() << " (used: " << d2.isUsed() << ")" << std::endl;
}

// shitty utility function
void Game::printSpaces(int pieces) {
	if(pieces < 10 && pieces >= 0) {
		// 4 spaces
		std::cout << "    ";
	} else if(pieces > 9 || (pieces < 0 && pieces > -10)) {
		// 3 spaces
		std::cout << "   ";
	} else {
		// pieces must be <= -10
		// 2 spaces
		std::cout << "  ";
	}
}

// FUNCTIONS TO PRINT; HOPEFULLY TEMPORARY; END

