#include "Player.h"
Player *Player::s_instance = nullptr;
Player::Player()
{
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

void Player::Load()
{
	auto content = FileUtils::getInstance()->getStringFromFile("PlayerInfo.bin");
	istringstream f(content);
	string off;
	f >> off;
	f >> m_gold;
	f >> off;
	f >> m_life;
	f >> off;
	f >> m_star;
	f >> off;
	f >> m_stage;
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

int Player::GetPlayStage()
{
	return m_playStage;
}

void Player::SetCurrentStage(int stage)
{
	m_stage = stage;
}

void Player::SetGold(int gold)
{
	m_gold = gold;
}

void Player::SetPlayStage(int play)
{
	m_playStage = play;
}
