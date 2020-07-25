#include <qlabel.h>
#include <qobjectdefs.h>
#include <qwidget.h>
//#include "IdPushButton.h"
#include "Game.h"

class IdPushButton;

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
		IdPushButton * positionButtons[24];
		IdPushButton * redDeadButton;// = new IdPushButton("0", -1);
		IdPushButton * blackDeadButton;// = new IdPushButton("0", 25);
		QLabel * die1Label;
		QLabel * die2Label;
		QLabel * statusLabel;
		QString redStyleSheet = "IdPushButton { color : red; }";
		QString blackStyleSheet = "IdPushButton { color : blue; }";
		QString neutralStyleSheet = "IdPushButton { color : black; }";
		Game game;
	public slots:
		void testPrint(int id);
};
