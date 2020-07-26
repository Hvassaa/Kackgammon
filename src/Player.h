#include <string>

class Player
{
	private:
		std::string playerColor;
	public:
		Player(std::string color);
		bool operator== (Player const &rhs);
		std::string getPlayerColor() const;
};
