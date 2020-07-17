#include <QWidget>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <iostream>
#include "Gui.h"

Gui::Gui(QWidget * window)
{
	std::cout << "GUI CONSTRUCTOR CALLED" << std::endl;

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

	window->resize(250, 150);
	window->setWindowTitle("My Window");
	window->setLayout(boardLayout);
	window->show();
}
