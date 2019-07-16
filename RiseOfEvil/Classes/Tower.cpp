#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/archerTower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 4;
		m_maximumAtk = 6;
		m_attackSpeed = 0.8;
		m_range = 280;
		m_gold = 70;
		break;
	case MAGIC_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/magictower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 9;
		m_maximumAtk = 17;
		m_attackSpeed = 1.5;
		m_range = 280;
		m_gold = 100;
		break;
	case SLOW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/slowtower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 1;
		m_maximumAtk = 3;
		m_attackSpeed = 1.3;
		m_range = 180;
		m_gold = 80;
		break;
	case BOMBARD_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/boomtower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 10;
		m_maximumAtk = 18;
		m_attackSpeed = 3.0;
		m_range = 320;
		m_gold = 120;
		break;
	case BARRACKS_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/brracktower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 0;
		m_maximumAtk = 0;
		m_attackSpeed = 300000.0;
		m_range = 180;
		m_gold = 70;
		break;
	}
}

Tower::Tower(Layer * layer, int type, Vec2 Pos)
{
	m_type = type;
	Init();
	for (int i = 0; i < 10; i++)
	{
		Bullet * bullet = new Bullet(layer);
		listBullet.push_back(bullet);
	}
	m_sprite->setScale(0.5f);
	m_sprite->setPosition(Pos);
	m_sprite->removeFromParent();
	layer->addChild(m_sprite, 5);
}

Sprite * Tower::GetSprite()
{
	return m_sprite;
}
int hp = 20;
void Tower::Shoot(Monster * monster)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet.at(i)->GetSprite()->isVisible())
		{
			listBullet.at(i)->GetSprite()->setVisible(true);
			listBullet.at(i)->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY());
			listBullet.at(i)->Move(monster);
			break;
		}
	}
}

void Tower::Update(float deltaTime, Monster * monster)
{
	if (m_sprite->getPosition().getDistance(Vec2(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY())) < m_range)
	{
		timeDelay += deltaTime;
		if (timeDelay > m_attackSpeed)
		{
			Shoot(monster);
			timeDelay = 0;
		}
	}
}

float Tower::GetRange()
{
	return m_range;
}

float Tower::GetAttackSpeed()
{
	return m_attackSpeed;
}

void Tower::SetAttackSpeed(float as)
{
	m_attackSpeed = as;
}

int Tower::GetGold()
{
	return m_gold;
}

void Tower::SetGold(int gold)
{
	m_gold = gold;
}
