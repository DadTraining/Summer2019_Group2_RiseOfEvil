#include "Monster.h"
#include "ResourceManager.h"

Monster::Monster(Scene * scene, int type)
{
	m_type = type;
	Init();
	m_sprite->removeFromParent();
	scene->addChild(m_sprite);
}

Monster::~Monster()
{
}

void Monster::Init()
{
	switch (m_type)
	{
	case NORMAL_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(NORMAL_MONSTER)); //id = id of NORMAL_MONSTER
		m_hitPoint = 24;
		m_minimumAtk = 1;
		m_maximumAtk = 4;
		m_attackSpeed = 1.0;
		m_movementSpeed = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 6;
		break;
	case MAGICAN_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGICAN_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 120;
		m_minimumAtk = 5;
		m_maximumAtk = 7;
		m_attackSpeed = 1.0;
		m_movementSpeed = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case TANK_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(TANK_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 960;
		m_minimumAtk = 40;
		m_maximumAtk = 60;
		m_attackSpeed = 1.9;
		m_movementSpeed = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 40;
		break;
	case SPEED_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGICAN_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 42;
		m_minimumAtk = 2;
		m_maximumAtk = 3;
		m_attackSpeed = 1.2;
		m_movementSpeed = FAST_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case SIEGE_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SIEGE_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 58;
		m_minimumAtk = 3;
		m_maximumAtk = 8;
		m_attackSpeed = 1.0;
		m_movementSpeed = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case ELITE_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(ELITE_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 12000;
		m_minimumAtk = 150;
		m_maximumAtk = 250;
		m_attackSpeed = 2.5;
		m_movementSpeed = SLOW_SPEED;
		//sm_armor = 0;
		m_gold = 100;
		break;
	case DARKLORD:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(DARKLORD)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 21600;
		m_minimumAtk = 200;
		m_maximumAtk = 400;
		m_attackSpeed = 2.0;
		m_movementSpeed = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 500;
		break;
	default:
		break;
	}
}

void Monster::Update(float deltaTime)
{
}

void Monster::Move()
{
}

void Monster::Acttack(Object * target)
{
}

void Monster::DoDead()
{
}

void Monster::SetType(int type)
{
	m_type = type;
}

void Monster::SetMovementSpeed(float movementSpeed)
{
	m_movementSpeed = movementSpeed;
}

void Monster::SetAttackSpeed(float attackSpeed)
{
	m_attackSpeed = attackSpeed;
}

void Monster::SetGold(int gold)
{
	m_gold = gold;
}

void Monster::SetRange(int range)
{
	m_range = range;
}

int Monster::GetType()
{
	return m_type;
}

float Monster::GetMovementSpeed()
{
	return m_movementSpeed;
}

float Monster::GetAttackSpeed()
{
	return m_attackSpeed;
}

int Monster::GetGold()
{
	return m_gold;
}

int Monster::GetRange()
{
	return m_range;
}
