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
	case NORMAL:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(NORMAL));//id = id of path NORMAL_MONSTER 
		m_hitPoint = 24;
		m_minimumAtk = 1;
		m_maximumAtk = 4;
		m_attackSpeed = 1.0;
		//m_armor = urnarmor
		// gold = ?
		//m_movementSpeed = medium
		// special = ?

		break;
	case MAGICAN:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGICAN));//id = id of path MAGICAN _MONSTER
		m_hitPoint = 120;
		m_minimumAtk = 5;
		m_maximumAtk = 7;
		m_attackSpeed = 1.0;
		//m_armor = urnarmor
		// gold = ?
		//m_movementSpeed = medium
		// special = ?
		break;
	case TANK:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(TANK));//id = id of path TANK _MONSTER
		m_hitPoint = 960;
		m_minimumAtk = 40;
		m_maximumAtk = 60;
		m_attackSpeed = 1.9;
		//m_armor = antiphysic
		// gold = ?
		//m_movementSpeed = slow
		// special = ?
		break;
	case SPEED:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SPEED));//id = id of path SPEED _MONSTER 
		m_hitPoint = 42;
		m_minimumAtk = 2;
		m_maximumAtk = 3;
		m_attackSpeed = 1.2;
		//m_armor = Unarmor
		// gold = ?
		//m_movementSpeed = fast
		// special = ?
		break;
	case SIEGE:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SIEGE));//id = id of path SIEGE _MONSTER 
		m_hitPoint = 58;
		m_minimumAtk = 3;
		m_maximumAtk = 8;
		m_attackSpeed = 1.0;
		//m_armor = Unarmor
		// gold = ?
		//m_movementSpeed = medium
		// special = ?
		break;
	case ELITE:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(ELITE));//id = id of path ELITE _MONSTER 
		m_hitPoint = 12000;
		m_minimumAtk = 150;
		m_maximumAtk = 250;
		m_attackSpeed = 2.5;
		//m_armor = Elitearmor
		// gold = ?
		//m_movementSpeed = slow
		// special = ?
		break;
	case DARKLORD:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(DARKLORD));//id = id of path DARKLORD _MONSTER 
		m_hitPoint = 21600;
		m_minimumAtk = 200;
		m_maximumAtk = 400;
		m_attackSpeed = 2.0;
		//m_armor = Elitearmor
		// gold = ?
		//m_movementSpeed = slow
		// special = ?
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
void Monster::Attack(Objects * target)
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