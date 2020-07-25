#include <cmath>
#include <exception>
#include <iostream>
#include <qnamespace.h>
#include <string>
#include <QtCore>
#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char * argv[])
{
	std::cout << "argc : " << argc << ", argv: " << argv << std::endl;
	std::cout << "Qt version: " << qVersion() << std::endl;
	if(argc == 1) 
	{
		QApplication app(argc, argv);
		MainWindow mainWindow;
		mainWindow.buildWindow();
		return app.exec();
	}
	else
	{
		// BAD BAD UNIX ONLY
		system("clear");

		std::cout << std::boolalpha;
		int debug = 1;
		if(argc > 1)
		{
			debug = atoll(argv[1]);
		}

		Game game;

		if(debug > 10)
		{
			std::cout << "Number of args to program: " << argc << std::endl;
			std::cout << "Player starting: " << game.getPlayerInTurn().getPlayerColor() << std::endl;
		}

		char input;
		std::string fromPos;
		std::string toPos;
		while(true)
		{
			std::cout << "DEBUG LEVEL: " << debug << std::endl;
			std::cout << "q: quit, m: move, n: next player" << std::endl;
			game.printBoard();
			if(debug > 0)
			{
				game.validMoveExists();
			}

			std::cout << "Command: ";
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
					try {
						bool moveSucceded = game.movePiece(std::stoi(fromPos), std::stoi(toPos));
						std::cout << "Move succeeded: " << moveSucceded << std::endl;
					}
					catch(std::exception& e) {
						// break, but we already do
					}
					break;
				case 'n':
					game.changePlayer();
					// next turn
					break;
				default:
					std::cout << "Unknown input" << std::endl;
			}
		// BAD BAD UNIX ONLY
		system("clear");
		}
	}
}
