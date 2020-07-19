#include "MainWindow.h"
#include <iostream>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qwidget.h>

MainWindow::MainWindow()
{
	std::cout << "HELLO FROM MW" << std::endl;
	guiFromPos = -2;
	guiToPos = -2;
}

void MainWindow::buildWindow()
{
	// vertical box layout to hold the rows
	QVBoxLayout * boardLayout = new QVBoxLayout;
	boardLayout->setAlignment(Qt::AlignCenter);

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
		int pieceCount = game.getPiecesAt(i - 0);
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
}
