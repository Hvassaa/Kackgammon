#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include "Game.h"

class MainWindow : public QWidget
{
	Q_OBJECT

	public:
		MainWindow();
		void buildWindow();
		void redrawBoard();
		void getMovePositionsFromInput(int pos);
	private:
		int guiFromPos, guiToPos;
		QPushButton * positionButtons[24];
		QPushButton * redDeadButton = new QPushButton("0");
		QPushButton * blackDeadButton = new QPushButton("0");
		Game game;
};
