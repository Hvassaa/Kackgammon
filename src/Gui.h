#include <QPushButton>
#include "Game.h"

class Gui
{
	private:
		int guiMoveFrom;
		int guiMoveTo;
		Game game;
		QPushButton * posButtons[24];
	public:
		Gui(QWidget * window);
		void buildWindow();
		void redrawBoard();
		int exec();
};
