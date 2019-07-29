#include "Soldier.h"

void Soldier::Init()
{
	switch (level)
	{
	case LEVEL1:
		m_sprite = Sprite::create("soldier.png");
		m_hitPoint = 50;
		m_attackSpeed = 1.0;
		m_velocity = m_speed = m_movementSpeed = MEDIUM_SPEED;
		break;
	case LEVEL2:
		m_sprite = Sprite::create("soldier.png");
		m_hitPoint = 100;
		m_attackSpeed = 1.0;
		m_velocity = m_speed = m_movementSpeed = MEDIUM_SPEED;
		break;
	case LEVEL3:
		m_sprite = Sprite::create("soldier.png");
		m_hitPoint = 150;
		m_attackSpeed = 1.0;
		m_velocity = m_speed = m_movementSpeed = MEDIUM_SPEED;
		break;
	}
}

void Soldier::Update(float deltaTime)
{
}

void Soldier::MoveSoldier(Vec2 point, bool check, float timedelay, float delay)
{
	if (timeMove >= delay)
	{
		if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x <= point.x)) {
			Action(E, check);
			checkMove = 1;
		}
		else if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x >= point.x)) {
			Action(W, check);
			checkMove = 2;
		}
		else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y >= point.y)) {
			Action(S, check);
			checkMove = 3;
		}
		else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y <= point.y)) {
			Action(N, check);
			checkMove = 4;
		}
		else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y >= point.y)) {
			Action(SE, check);
			checkMove = 5;
		}
		else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y >= point.y)) {
			Action(SW, check);
			checkMove = 6;
		}
		else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y <= point.y)) {
			Action(NE, check);
			checkMove = 7;
		}
		else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y <= point.y))
		{
			Action(NW, check);
			checkMove = 8;
		}
		m_sprite->runAction(MoveTo::create(point.getDistance(m_sprite->getPosition()) / m_movementSpeed, Vec2(point.x, point.y)));

		timeMove = 0;
	}
	else
	{
		timeMove += timedelay;
	}
}

void Soldier::Action(int direction, bool check)
{
	switch (direction)
	{
	}
}

void Soldier::MoveToFlag(Vec2 Pos)
{
	float dis = m_sprite->getPosition().distance(Pos);
	auto moveToFlag = MoveTo::create(dis/ m_movementSpeed, Pos);
	m_sprite->runAction(moveToFlag);
}

Monster *Soldier::FindNearestMonster(Monster * monster)
{
	float dis = m_sprite->getPosition().distance(monster->GetSprite()->getPosition());
	if (!monster->IsDead() && dis <= rangeOfSoldier)
	{
		return monster;
	}
}

Soldier::Soldier(Layer * layer, int level)
{
	this->level = level;
	this->layer = layer;
	Init();
}

Soldier::~Soldier()
{
}
