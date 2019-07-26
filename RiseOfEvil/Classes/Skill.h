#pragma once
#include "cocos2d.h"
#include "Objects.h"
#define SLOW 1
#define INCREASE_ATTACKSPEED 2
using namespace cocos2d;
class Skill
{
private:
	Sprite *m_sprite;
public:
	Skill();
	~Skill();
	void Init();
	Sprite * getSprite();
	void effect(Object*);
};
