#include <iostream>
#include <string>
#include "Player.h"

Player::Player(std::string color)
{
	playerColor = color;
}

std::string Player::getPlayerColor() const
{
	return playerColor;
}

bool Player::operator== (Player const &rhs)
{
	return this->getPlayerColor() == rhs.getPlayerColor();
}

std::string Player::getQtStyleSheet()
{
	return QtStyleSheet;
}

void Player::setQtStyleSheet(std::string newStyle)
{
	QtStyleSheet = newStyle;
}
