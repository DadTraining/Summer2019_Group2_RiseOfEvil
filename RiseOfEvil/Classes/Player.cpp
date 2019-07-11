#include "Player.h"
Player *Player::s_instance = nullptr;
Player::Player()
{
	m_gold = 0;
	m_star = 0;
	m_life = 0;
	m_stage = 1;
}

Player::~Player()
{
}

Player * Player::GetInstance()
{
	if (!s_instance)
	{
		s_instance = new Player();
	}
	return s_instance;
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

int Player::GetCurrentStage()
{
	return m_stage;
}
