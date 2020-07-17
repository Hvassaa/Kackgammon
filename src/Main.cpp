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
#include "Game.h"

int main(int argc, char * argv[])
{
	std::cout << "argc : " << argc << ", argv: " << argv << std::endl;
	std::cout << "Qt version: " << qVersion() << std::endl;

	Game game;

	QApplication app(argc, argv);
	QWidget window;

	// vertical box layout to hold the rows
	QVBoxLayout * boardLayout = new QVBoxLayout;
	boardLayout->setAlignment(Qt::AlignVCenter);

	// the rows of the board
	QHBoxLayout * row1Layout = new QHBoxLayout;
	QHBoxLayout * row2Layout = new QHBoxLayout;
	row1Layout->setAlignment(Qt::AlignHCenter);
	row2Layout->setAlignment(Qt::AlignHCenter);
	QLabel * statusLabel = new QLabel("Status: ");
	// add them to the board layout
	boardLayout->addWidget(statusLabel);
	boardLayout->addLayout(row1Layout);
	boardLayout->addLayout(row2Layout);

	// TEST LABELS/BUTTONS
	QPushButton * posButtons[24];
	for(int i = 0; i < 24; i++)
	{
		int pieceCount = game.getPiecesAt(i);
		QString pieceCountString = QString::number(abs(pieceCount));
		QPushButton * posButton = new QPushButton(pieceCountString);
		posButton->setFlat(true);
		if(pieceCount > 0)
		{
			posButton->setStyleSheet("QPushButton { color : red; }");
		}
		else if(pieceCount < 0)
		{
			posButton->setStyleSheet("QPushButton { color : blue; }");
		}
		posButtons[i] = posButton;
	}
	for(int i = 0; i < 12; i++)
	{
		row1Layout->addWidget(posButtons[i]);
	}
	for(int i = 23; i > 11; i--)
	{
		row2Layout->addWidget(posButtons[i]);
	}

	window.resize(250, 150);
	window.setWindowTitle("My Window");
	window.setLayout(boardLayout);
	window.show();

	return app.exec();
}

/*
int main(int argc, const char * argv[]) {
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
*/
