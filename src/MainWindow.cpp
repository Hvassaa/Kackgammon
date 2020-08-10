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
#include <QMessageBox>

MainWindow::MainWindow() : diceLabel(new QLabel("", this)), playerInTurnLabel(new QLabel("", this)), statusLabel(new QLabel("", this))
{
	const int buttonHeight = 60;
	const int buttonWidth = buttonHeight;
	const int labelHeight = 30;
	const int labelWidth = buttonWidth;

	guiFromPos = -1;
	guiToPos = -1;

	// vertical box layout to hold the rows
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setAlignment(Qt::AlignCenter);
	this->setLayout(mainLayout);

	// a row to show status, player, dice etc.
	QHBoxLayout *statusRow = new QHBoxLayout;
	statusRow->setAlignment(Qt::AlignCenter);
	statusRow->addWidget(diceLabel);
	statusRow->addWidget(playerInTurnLabel);

	// button to go to next player
	QPushButton *nextTurnButton = new QPushButton("Change\nturn", this);
	nextTurnButton->setFixedHeight(buttonHeight);
	nextTurnButton->setFixedWidth(buttonWidth);
	QObject::connect(nextTurnButton, SIGNAL(released()), this, SLOT(nextTurnProxy()));

	// label to indicate where you're trying to move from
	moveFromIndicator = new QLabel("", this);
	moveFromIndicator->setFixedHeight(labelHeight);
	moveFromIndicator->setFixedWidth(labelHeight + 60);
	QHBoxLayout *moveRow = new QHBoxLayout;
	moveRow->setAlignment(Qt::AlignCenter);
	moveRow->addWidget(moveFromIndicator);

	// label and row to show messages
	QHBoxLayout *messageRow = new QHBoxLayout;
	messageRow->addWidget(statusLabel);
	messageRow->setAlignment(Qt::AlignCenter);

	// a row to show the "next" button 
	QHBoxLayout *controlRow = new QHBoxLayout;
	controlRow->setAlignment(Qt::AlignCenter);
	controlRow->addWidget(nextTurnButton);

	// rows to show labels for the tile/button rows
	QHBoxLayout *labelRow1 = new QHBoxLayout;
	QHBoxLayout *labelRow2 = new QHBoxLayout;
	labelRow1->setAlignment(Qt::AlignCenter);
	QLabel * deadLabel1 = new QLabel("Dead", this);
	deadLabel1->setFixedHeight(labelHeight);
	deadLabel1->setFixedWidth(labelWidth);
	deadLabel1->setAlignment(Qt::AlignCenter);
	labelRow1->addWidget(deadLabel1);
	QLabel * finishLabel1 = new QLabel("Finish", this);
	finishLabel1->setFixedHeight(labelHeight);
	finishLabel1->setFixedWidth(labelWidth);
	finishLabel1->setAlignment(Qt::AlignCenter);
	labelRow1->addWidget(finishLabel1);
	for (int i = 1; i < 13; i++)
	{
		QLabel *label = new QLabel(QString::number(i), this);
		label->setFixedHeight(labelHeight);
		label->setFixedWidth(labelWidth);
		label->setAlignment(Qt::AlignCenter);
		labelRow1->addWidget(label);
	}
	QLabel * deadLabel2 = new QLabel("Dead", this);
	deadLabel2->setFixedHeight(labelHeight);
	deadLabel2->setFixedWidth(labelWidth);
	deadLabel2->setAlignment(Qt::AlignCenter);
	labelRow2->addWidget(deadLabel2);
	QLabel * finishLabel2 = new QLabel("Finish", this);
	finishLabel2->setFixedHeight(labelHeight);
	finishLabel2->setFixedWidth(labelWidth);
	finishLabel2->setAlignment(Qt::AlignCenter);
	labelRow2->addWidget(finishLabel2);
	for (int i = 24; i > 12; i--)
	{
		QLabel *label = new QLabel(QString::number(i), this);
		label->setFixedHeight(labelHeight);
		label->setFixedWidth(labelWidth);
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
	mainLayout->addLayout(messageRow);
	mainLayout->addLayout(moveRow);
	mainLayout->addLayout(labelRow1);
	mainLayout->addLayout(topRow);
	mainLayout->addLayout(bottomRow);
	mainLayout->addLayout(labelRow2);

	for (int i = 0; i < 28; i++)
	{
		IdPushButton *button = new IdPushButton(QString::number(game.getTileAt(i)->getNoOfPieces()), i, this);
		button->setFixedHeight(buttonHeight);
		button->setFixedWidth(buttonWidth);
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
	setMoveFromIndicatorText(1);
}

MainWindow::~MainWindow() 
{
	//delete &game;
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
		positionButtons[i]->setText(QString::number(game.getTileAt(i)->getNoOfPieces()));
		if(game.getTileAt(i)->getOwner() == nullptr)
		{
			positionButtons[i]->setStyleSheet(neutralStyleSheet);
		}
		else
		{
			positionButtons[i]->setStyleSheet(QString::fromStdString(game.getTileAt(i)->getOwner()->getQtStyleSheet()));
		}
	}
	updateDiceLabel();
	playerInTurnLabel->setText(QString::fromStdString(game.getPlayerInTurn().getPlayerColor()));
}

void MainWindow::receivePosition(int position)
{
	//std::cout << "BUTTON " << position << std::endl;
	if(guiFromPos == -1)
	{
		guiFromPos = position;
		setMoveFromIndicatorText(position);
		statusLabel->setText("");
	} 
	else if(guiToPos == -1)
	{
		guiToPos = position;
		if(!game.tryMovePiece(guiFromPos, guiToPos))
		{
			statusLabel->setText("Invalid move!");
		}
		else
		{
			redrawBoard();
			checkForWinner();

		}
		guiFromPos = -1;
		guiToPos = -1;
		setMoveFromIndicatorText(1);
	}
}

void MainWindow::nextTurnProxy()
{
	if(game.changeTurn())
	{
		statusLabel->setText("");
		redrawBoard();
	}
	else
	{
		statusLabel->setText("Failed, valid move exists!");
	}
	guiFromPos = -1;
	guiToPos = -1;
	setMoveFromIndicatorText(1);
}

void MainWindow::setMoveFromIndicatorText(int realPosition)
{
	moveFromIndicator->setText(QString::number(realPosition - 1).prepend("Move from: "));
}

void MainWindow::checkForWinner()
{
	if(game.getWinner() != nullptr)
	{
		QMessageBox winnerWindow(this);
		winnerWindow.setStandardButtons(QMessageBox::Reset|QMessageBox::Close);
		winnerWindow.setDefaultButton(QMessageBox::Reset);
		winnerWindow.setText(QString::fromStdString(game.getWinner()->getPlayerColor()).append(" Wins! Reset game or close?"));
		int ret = winnerWindow.exec();
		
		switch (ret)
		{
			case QMessageBox::Reset:
				resetGame();
				break;
			case QMessageBox::Close:
				emit quitApp();
				break;
			default:
				break;
		}
	}
}

void MainWindow::resetGame()
{
	game.resetGame(true);
	redrawBoard();
}
