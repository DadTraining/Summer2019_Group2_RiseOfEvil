#pragma once
#include "cocos2d.h"
#include "Objects.h"
using namespace cocos2d;
class Monster :public Objects
{
private:
	int m_type;//type monster
	float m_movementSpeed;// speed monster
	float m_attackSpeed; // speed attack of monster
	int m_gold;
	//vector<Skill *>m_listSkill; list skill for monster
	int m_range; //range attack of monster
	//Skill * special; //skill special of monster
public:

};