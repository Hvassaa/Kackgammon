#include "MainWindow.h"
#include "IdPushButton.h"
#include <QVBoxLayout>
#include <iostream>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwidget.h>

MainWindow::MainWindow() : diceLabel(new QLabel("", this))
{
	guiFromPos = -1;
	guiToPos = -1;

	// vertical box layout to hold the rows
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->setAlignment(Qt::AlignCenter);

	QHBoxLayout *statusRow = new QHBoxLayout;
	statusRow->setAlignment(Qt::AlignCenter);
	statusRow->addWidget(diceLabel);
	updateDiceLabel();
	mainLayout->addLayout(statusRow);

	QHBoxLayout *topRow = new QHBoxLayout;
	QHBoxLayout *bottomRow = new QHBoxLayout;
	topRow->setAlignment(Qt::AlignCenter);
	bottomRow->setAlignment(Qt::AlignCenter);
	mainLayout->addLayout(topRow);
	mainLayout->addLayout(bottomRow);

	for (int i = 0; i < 28; i++)
	{
		IdPushButton *button = new IdPushButton(QString::number(game.getTileAt(i).getNoOfPieces()), i, this);
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
