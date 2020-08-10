#include "IdPushButton.h"
#include "Game.h"
#include <QLabel>

class MainWindow : public QWidget
{
	Q_OBJECT
	public:
		MainWindow();
		~MainWindow();
		void redrawBoard();
		void getMovePositionsFromInput(int pos);
	private:
		int guiFromPos, guiToPos;
		IdPushButton *positionButtons[28];
		QLabel *diceLabel;
		QLabel *playerInTurnLabel;
		QLabel *moveFromIndicator;
		QLabel *statusLabel;
		QString redStyleSheet = "IdPushButton { color : red; }";
		QString blackStyleSheet = "IdPushButton { color : blue; }";
		QString neutralStyleSheet = "IdPushButton { color : black; }";
		Game game;
		void updateDiceLabel();
		void setMoveFromIndicatorText(int realPosition);
		void checkForWinner();
		void resetGame();
	public slots:
		void receivePosition(int position);
		void nextTurnProxy();
	signals:
		void quitApp();
};
