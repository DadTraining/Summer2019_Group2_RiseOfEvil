#pragma once
#include "cocos2d.h"
#include "Objects.h"
//#include "Tower.h"
//#include "Monster.h"
#define INCREASE_ATTACKSPEED_SKILL 1
#define INCREASE_ATTACKDAMAGE_SKILL 2
#define SLOW_SKILL 3
#define BURN_SKILL 4


using namespace cocos2d;
class Skill
{
private:
	Sprite *m_sprite;
	int typeSkill;
public:
	Skill(int type);
	~Skill();
	void Init();
	Sprite * getSprite();
	void effect(Objects*);
	//void increaseAttackSpeedSkill(Tower * tower, vector<Tower*>listTower);
	//void increaseAttackDamageSkill(Tower * tower, vector<Tower*>listTower);
	//void slowSkill(Tower * tower, vector<Monster*> listMonster);
	//void burnSkill(Tower * tower, vector<Monster*> listMonster, float deltaTime);
	//void bossSkill(Monster * boss, vector<Monster *>listMonster, float deltaTime);
};
