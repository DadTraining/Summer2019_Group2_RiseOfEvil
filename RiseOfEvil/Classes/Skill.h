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
};
