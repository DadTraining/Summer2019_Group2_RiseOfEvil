#pragma once
class Player
{
private:
	static Player *s_instance;
	int m_gold;
	int m_star;
	int m_life;
	int m_stage;
public:
	Player();
	~Player();
	static Player * GetInstance();
	int GetCurrentGold();
	int GetCurrentStar();
	int GetCurrentLife();
	int GetCurrentStage();
};
