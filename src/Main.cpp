#include <iostream>
#include <string>
#include "Game.h"

int main(int argc, const char * argv[]) {
	std::cout << std::boolalpha;
	int debug = 1;
	Game game;

	if(debug > 10)
	{
		std::cout << "Number of args to program: " << argc << std::endl;
		std::cout << "Player starting: " << game.getPlayerInTurn().getPlayerColor() << std::endl;
	}

	char input;
	int fromPos;
	int toPos;
	while(true)
	{
		game.printBoard();
		if(debug > 0)
		{
			game.validMoveExists();
		}

		std::cin >> input;
		switch (input) {
			case 'q':
				//quit 
				std::cout << "GAME QUITTED" << std::endl;
				return 0;
			case 'm':
				// move piece
				std::cout << "Move from: ";
				std::cin >> fromPos;
				std::cout << "Move to: ";
				std::cin >> toPos;
				std::cout << "Move succeeded: " << game.movePiece(fromPos, toPos) << std::endl;
				break;
			case 'n':
				game.changePlayer();
				// next turn
				break;
			default:
				std::cout << "Unknown input" << std::endl;
		}
	}
}
