#include <string>

class Player
{
	private:
		std::string playerColor;
		std::string QtStyleSheet;
	public:
		Player(std::string color);
		bool operator== (Player const &rhs);
		std::string getPlayerColor() const;
		std::string getQtStyleSheet();
		void setQtStyleSheet(std::string newStyle);
};
