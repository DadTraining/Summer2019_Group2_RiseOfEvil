#include "Tower.h"
#include "ResourceManager.h"
Tower::Tower(Scene * scene, int type)
{
	m_type = type;
	Init();
	m_sprite->removeFromParent();
	scene->addChild(m_sprite);
}

Tower::~Tower()
{
}

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(ARROW_TOWER));//id = id of path arrow_tower 
		m_hitPoint = 100;
		m_minimumAtk = 4;
		m_maximumAtk = 6;
		m_armor = 0;
		m_attackSpeed = 0.8;
		m_range = 280;
		m_cost = 70;
		break;
	case MAGIC_TOWER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGIC_TOWER));//id = id of path MAGIC_TOWER 
		m_hitPoint = 100;
		m_minimumAtk = 9;
		m_maximumAtk = 17;
		m_armor = 0;
		m_attackSpeed = 1.5;
		m_range = 280;
		m_cost = 100;
		break;
	case SLOW_TOWER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SLOW_TOWER));//id = id of path SLOW_TOWER 
		m_hitPoint = 100;
		m_minimumAtk = 1;
		m_maximumAtk = 3;
		m_armor = 0;
		m_attackSpeed = 1.3;
		m_range = 180;
		m_cost = 80;
		break;
	case BOMBARD_TOWER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(BOMBARD_TOWER));//id = id of path BOMBARD_TOWER 
		m_hitPoint = 100;
		m_minimumAtk = 10;
		m_maximumAtk = 18;
		m_armor = 0;
		m_attackSpeed = 3.0;
		m_range = 320;
		m_cost = 125;
		break;
	case BARRACKS_TOWER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(BARRACKS_TOWER));//id = id of path BARRACKS_TOWER 
		m_hitPoint = 100;
		m_minimumAtk = 0;
		m_maximumAtk = 0;
		m_armor = 0;
		m_attackSpeed = 0;
		m_range = 180;
		m_cost = 70;
		break;
	default:
		break;
	}
}


void Tower::Update(float deltaTime)
{
}

void Tower::Attack(Objects *)
{
}

void Tower::Destroyed()
{
}

void Tower::SetTarget(Objects * target)
{
}

void Tower::SetType(int type)
{
	m_type = type;
}

void Tower::SetAttackSpeed(float attackSpeed)
{
	m_attackSpeed = attackSpeed;
}

void Tower::SetRange(int range)
{
	m_range = range;
}

void Tower::SetCost(int cost)
{
	m_cost = cost;
}

void Tower::SetLevel(int level)
{
	m_level = level;
}

int Tower::GetType()
{
	return m_level;
}

float Tower::GetAttackSpeed()
{
	return m_attackSpeed;
}

int Tower::GetRange()
{
	return m_range;
}

int Tower::GetLevel()
{
	return m_level;
}

int Tower::GetCost()
{
	return m_cost;
}
