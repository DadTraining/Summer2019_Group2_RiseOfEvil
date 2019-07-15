#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/archerTower1.png");
		m_minimumAtk = 4;
		m_maximumAtk = 6;
		break;
	case MAGIC_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/magictower1.png");
		m_minimumAtk = 9;
		m_maximumAtk = 17;
		break;
	case SLOW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/slowtower1.png");
		m_minimumAtk = 1;
		m_maximumAtk = 3;
		break;
	case BOMBARD_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/boomtower1.png");
		m_minimumAtk = 10;
		m_maximumAtk = 18;
		break;
	case BARRACKS_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/brracktower1.png");
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
	if (checkTowerShoot)
	{
		coutTimeToDamage += deltaTime;
		if (coutTimeToDamage >= 0.4)
		{
			monster->SetHitPoint(monster->GetHitPoint() - GetDamage());
			coutTimeToDamage = 0;
			if (monster->GetHitPoint() <= 0)
			{
				//monster->GetSprite()->release();
			}
		}
	}
	if (m_sprite->getPosition().getDistance(Vec2(monster->GetSprite()->getPositionX(), monster->GetSprite()->getPositionY())) < range)
	{
		timeDelay += deltaTime;
		if (timeDelay > 0.8)
		{
			Shoot(monster);
			checkTowerShoot = true;
			timeDelay = 0;
		}
	}
}

float Tower::GetRange()
{
	return range;
}

int Tower::GetDamage()
{
	return random(m_minimumAtk,m_maximumAtk);
}
