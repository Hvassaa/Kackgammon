#include "MainWindow.h"
#include "IdPushButton.h"
#include <QVBoxLayout>
#include <cstdio>
#include <iostream>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwidget.h>

MainWindow::MainWindow() : diceLabel(new QLabel("", this)), playerInTurnLabel(new QLabel("", this))
{
	guiFromPos = -1;
	guiToPos = -1;

	// vertical box layout to hold the rows
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setAlignment(Qt::AlignCenter);

	// a row to show status, player, dice etc.
	QHBoxLayout *statusRow = new QHBoxLayout;
	statusRow->setAlignment(Qt::AlignCenter);
	statusRow->addWidget(diceLabel);
	statusRow->addWidget(playerInTurnLabel);

	// button to go to next player
	QPushButton *nextTurnButton = new QPushButton("Next", this);
	nextTurnButton->setFixedHeight(60);
	nextTurnButton->setFixedWidth(60);
	QObject::connect(nextTurnButton, SIGNAL(released()), this, SLOT(nextTurnProxy()));

	// a row to show the "next" button
	QHBoxLayout *controlRow = new QHBoxLayout;
	controlRow->addWidget(nextTurnButton);

	// rows to show labels for the tile/button rows
	QHBoxLayout *labelRow1 = new QHBoxLayout;
	QHBoxLayout *labelRow2 = new QHBoxLayout;
	labelRow1->setAlignment(Qt::AlignCenter);
	QLabel * deadLabel1 = new QLabel("Dead", this);
	deadLabel1->setFixedHeight(60);
	deadLabel1->setFixedWidth(60);
	deadLabel1->setAlignment(Qt::AlignCenter);
	labelRow1->addWidget(deadLabel1);
	QLabel * finishLabel1 = new QLabel("Finish", this);
	finishLabel1->setFixedHeight(60);
	finishLabel1->setFixedWidth(60);
	finishLabel1->setAlignment(Qt::AlignCenter);
	labelRow1->addWidget(finishLabel1);
	for (int i = 1; i < 13; i++)
	{
		QLabel *label = new QLabel(QString::number(i), this);
		label->setFixedHeight(60);
		label->setFixedWidth(60);
		label->setAlignment(Qt::AlignCenter);
		labelRow1->addWidget(label);
	}
	QLabel * deadLabel2 = new QLabel("Dead", this);
	deadLabel2->setFixedHeight(60);
	deadLabel2->setFixedWidth(60);
	deadLabel2->setAlignment(Qt::AlignCenter);
	labelRow2->addWidget(deadLabel2);
	QLabel * finishLabel2 = new QLabel("Finish", this);
	finishLabel2->setFixedHeight(60);
	finishLabel2->setFixedWidth(60);
	finishLabel2->setAlignment(Qt::AlignCenter);
	labelRow2->addWidget(finishLabel2);
	for (int i = 24; i > 12; i--)
	{
		QLabel *label = new QLabel(QString::number(i), this);
		label->setFixedHeight(60);
		label->setFixedWidth(60);
		label->setAlignment(Qt::AlignCenter);
		labelRow2->addWidget(label);
	}


	// rows to show the buttons that represent tiles
	QHBoxLayout *topRow = new QHBoxLayout;
	QHBoxLayout *bottomRow = new QHBoxLayout;
	topRow->setAlignment(Qt::AlignCenter);
	bottomRow->setAlignment(Qt::AlignCenter);

	mainLayout->addLayout(statusRow);
	mainLayout->addLayout(controlRow);
	mainLayout->addLayout(labelRow1);
	mainLayout->addLayout(topRow);
	mainLayout->addLayout(bottomRow);
	mainLayout->addLayout(labelRow2);

	for (int i = 0; i < 28; i++)
	{
		IdPushButton *button = new IdPushButton(QString::number(game.getTileAt(i).getNoOfPieces()), i, this);
		button->setFixedHeight(60);
		button->setFixedWidth(60);
		QObject::connect(button, SIGNAL(emitId(int)), this, SLOT(receivePosition(int)));
		positionButtons[i] = button;
	}
	for (int i = 0; i < 14; i++)
	{
		topRow->addWidget(positionButtons[i]);
	}
	for (int i = 27; i >= 14; i--)
	{
		bottomRow->addWidget(positionButtons[i]);
	}
	redrawBoard();
	QWidget::show();
}

void MainWindow::updateDiceLabel()
{
	QString diceString = "";
	for (Die const &d : game.getDieCup().dice)
	{
		diceString.append(QString::number(d.getEyes()));
		diceString.append(" ");
		diceString.append(d.isUnused() ? "Unused, " : "Used, ");
	}
	diceLabel->setText(diceString);
}

void MainWindow::redrawBoard()
{
	for (int i = 0; i < 28; i++)
	{
		positionButtons[i]->setText(QString::number(game.getTileAt(i).getNoOfPieces()));
		if(game.getTileAt(i).getOwner() == nullptr)
		{
			positionButtons[i]->setStyleSheet(neutralStyleSheet);
		}
		else
		{
			positionButtons[i]->setStyleSheet(QString::fromStdString(game.getTileAt(i).getOwner()->getQtStyleSheet()));
		}
	}
	updateDiceLabel();
	playerInTurnLabel->setText(QString::fromStdString(game.getPlayerInTurn().getPlayerColor()));
}

void MainWindow::receivePosition(int position)
{
	std::cout << "BUTTON " << position << std::endl;
	if(guiFromPos == -1)
	{
		guiFromPos = position;
	} 
	else if(guiToPos == -1)
	{
		guiToPos = position;
		game.tryMovePiece(guiFromPos, guiToPos);
		redrawBoard();
		guiFromPos = -1;
		guiToPos = -1;
	}
}

void MainWindow::nextTurnProxy()
{
	game.changeTurn();
	guiFromPos = -1;
	guiToPos = -1;
	redrawBoard();
}
