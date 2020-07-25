#include <iostream>
#include <string>
#include "Player.h"
#include "Die.h"

class Game
{
	private:
		Die d1;
		Die d2;
		Player redPlayer = Player("Red");
		Player blackPlayer = Player("Black");
		Player * playerInTurn;
		Player * nextPlayer;
		int board [24] = {0};
		int numberOfBricks = 7;
	public:
		Game();
		Player getPlayerInTurn();
		Player getNextPlayer();
		bool movePiece(int from, int to);
		bool validMove(int from, int to);
		int getPiecesAt(int pos);
		void decreasePiecesAt(int pos);
		void increasePiecesAt(int pos);
		void pieceKilledAt(int pos);
		Player * getWinner();
		void checkForWonGame();
		void rollDice();
		Die getDie1();
		Die getDie2();
		bool validPlayerChange();
		bool changePlayer();
		bool validMoveExists();
		void finishPieceAt(int pos);
		int getDeadRedPieces();
		int getDeadBlackPieces();
		// REMOVE AT SOME POINT
		void printBoard();
		void printSpaces(int p);
};
