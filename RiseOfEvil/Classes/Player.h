#pragma once
class Player
{
private:
	int m_gold;
	int m_star;
	int m_life;
public:
	Player();
	~Player();
	int GetCurrentGold();
	int GetCurrentStar();
	int GetCurrentLife();
};
