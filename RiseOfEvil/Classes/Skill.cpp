#include "Skill.h"

Skill::Skill(int type)
{
	typeSkill = type;
	Init();
}

Skill::~Skill()
{
}

void Skill::Init()
{
	switch (typeSkill)
	{
	case SLOW_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case BURN_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case INCREASE_ATTACKSPEED_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	case INCREASE_ATTACKDAMAGE_SKILL:
		m_sprite = Sprite::create("range_of_barrack_tower.png");
		m_sprite->setOpacity(30);
		break;
	}
}

Sprite * Skill::getSprite()
{
	return m_sprite;
}

void Skill::effect(Objects*)
{
}
