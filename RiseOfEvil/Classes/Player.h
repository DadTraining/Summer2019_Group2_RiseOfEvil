#pragma once
#include <iostream>
#include <fstream>
#include "cocos2d.h"
using namespace std;
using namespace cocos2d;
class Player
{
private:
	static Player *s_instance;
	int m_gold;
	int m_star;
	int m_life;
	int m_stage;
	int m_playStage;
public:
	Player();
	~Player();
	static Player * GetInstance();
	void Load();
	int GetCurrentGold();
	int GetCurrentStar();
	int GetCurrentLife();
	int GetCurrentStage();
	int GetPlayStage();
	void SetCurrentStage(int stage);
	void SetGold(int);
	void SetPlayStage(int);
};
