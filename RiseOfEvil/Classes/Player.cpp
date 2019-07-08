#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

int Player::GetCurrentGold()
{
	return m_gold;
}

int Player::GetCurrentStar()
{
	return m_star;
}

int Player::GetCurrentLife()
{
	return m_life;
}
