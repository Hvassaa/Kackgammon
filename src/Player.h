#include <string>

class Player
{
	private:
		std::string playerColor;
		int finishedPieces = 0;
		int deadPieces = 0;
	public:
		Player(std::string color);
		std::string getPlayerColor();
		int getFinishedPieces();
		int getDeadPieces();
		void incrementDeadPieces();
		void decrementDeadPieces();
		void finishPiece();
		bool isAllPiecesHome(int board[]);
};
