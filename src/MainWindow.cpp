#include "MainWindow.h"
#include "IdPushButton.h"
#include <iostream>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qobject.h>
#include <qwidget.h>
#include <string>

MainWindow::MainWindow()
{
	std::cout << "HELLO FROM MW" << std::endl;
	guiFromPos = -2;
	guiToPos = -2;
	redDeadButton = new IdPushButton("0", -1);
	blackDeadButton = new IdPushButton("0", 24);
	QObject::connect(redDeadButton, SIGNAL(emitId(int)), this, SLOT(testPrint(int)));
	QObject::connect(blackDeadButton, SIGNAL(emitId(int)), this, SLOT(testPrint(int)));
	die1Label = new QLabel(QString::number(game.getDie1().getEyes()));
	die2Label = new QLabel(QString::number(game.getDie2().getEyes()));
	QString status = QString::fromStdString("Player in turn: ").append(QString::fromStdString(game.getPlayerInTurn().getPlayerColor()));
	statusLabel = new QLabel(status);
}

void MainWindow::buildWindow()
{

	// vertical box layout to hold the rows
	QVBoxLayout * boardLayout = new QVBoxLayout;
	boardLayout->setAlignment(Qt::AlignCenter);

	QHBoxLayout * statusRow = new QHBoxLayout;
	statusRow->setAlignment(Qt::AlignCenter);
	statusRow->addWidget(die1Label);
	statusRow->addWidget(die2Label);
	statusRow->addWidget(statusLabel);
	boardLayout->addLayout(statusRow);

	// the rows of the board
	QHBoxLayout * row1Layout = new QHBoxLayout;
	QHBoxLayout * row2Layout = new QHBoxLayout;
	row1Layout->setAlignment(Qt::AlignCenter);
	row2Layout->setAlignment(Qt::AlignCenter);

	// add them to the board layout
	boardLayout->addLayout(row1Layout);
	boardLayout->addLayout(row2Layout);

	// create the buttons, that represent pieces
	row1Layout->addWidget(redDeadButton);
	row2Layout->addWidget(blackDeadButton);

	for(int i = 0; i < 24; i++)
	{
		int pieceCount = game.getPiecesAt(i);
		QString pieceCountString = QString::number(abs(pieceCount));
		IdPushButton * posButton = new IdPushButton(pieceCountString, i);
		posButton->setFlat(true);

		QObject::connect(posButton, SIGNAL(emitId(int)), this, SLOT(testPrint(int)));

		if(pieceCount > 0)
		{
			posButton->setStyleSheet(redStyleSheet);
		}
		else if(pieceCount < 0)
		{
			posButton->setStyleSheet(blackStyleSheet);
		}
		positionButtons[i] = posButton;
	}
	for(int i = 0; i < 12; i++)
	{
		row1Layout->addWidget(positionButtons[i]);
	}
	for(int i = 23; i >= 12; i--)
	{
		row2Layout->addWidget(positionButtons[i]);
	}

	QWidget::setLayout(boardLayout);
	QWidget::show();
}

void MainWindow::getMovePositionsFromInput(int pos)
{
	if(guiFromPos == -2)
	{
		guiFromPos = pos;
	}
	else if(guiToPos == -2)
	{
		guiToPos = pos;
		std::cout << game.movePiece(guiFromPos, guiToPos) << std::endl;
		guiFromPos = -2;
		guiToPos = -2;
	}
	game.changePlayer();
	redrawBoard();
}

void MainWindow::testPrint(int id)
{
	std::cout << "BUTTON " << id << " RELEASED" << std::endl;
	getMovePositionsFromInput(id);
}

void MainWindow::redrawBoard()
{
	for(int i = 0; i < 24; i++)
	{
		int pieceCount = game.getPiecesAt(i);
		QString pieceCountString = QString::number(abs(pieceCount));
		IdPushButton * button = positionButtons[i];
		button->setText(pieceCountString);
		if(pieceCount > 0)
		{
			button->setStyleSheet(redStyleSheet);
		}
		else if(pieceCount < 0)
		{
			button->setStyleSheet(blackStyleSheet);
		}
		else
		{
			button->setStyleSheet(neutralStyleSheet);
		}
	}
	redDeadButton->setText(QString::number(game.getDeadRedPieces()));
	blackDeadButton->setText(QString::number(game.getDeadBlackPieces()));
	die1Label->setText(QString::number(game.getDie1().getEyes()));
	die2Label->setText(QString::number(game.getDie2().getEyes()));
	std::string status = "Player in turn: " + game.getPlayerInTurn().getPlayerColor();
	statusLabel->setText(QString::fromStdString(status));
}
