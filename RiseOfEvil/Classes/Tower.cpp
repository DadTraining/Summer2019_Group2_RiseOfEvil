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
		m_range = 200;
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
		m_range = 180;
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

	circleIcon = MenuItemImage::create("CircleMenu.png", "CircleMenu.png", [&](Ref* sender) {
	});
	circleIcon->setPosition(m_sprite->getPosition() + m_sprite->getContentSize() / 2);

	flagIcon = MenuItemImage::create("FlagCallSoldier.png", "FlagCallSoldier.png", [&](Ref* sender) {
		FadeOutPause();
		rangeBarrackTower->setVisible(true);
		checkTouchFlag = true;
		log("oke");
	});
	log("%d", checkTouchFlag);
	flagIcon->setPosition(circleIcon->getPosition().x + circleIcon->getContentSize().width / 2 -10, circleIcon->getPosition().y);
	// upgrade
	upgradeIcon = MenuItemImage::create("upgrade_button_normal.png", "upgrade_button_press.png", "upgrade_button_normal.png",[&](Ref* sender)
	{

	});
	upgradeIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y + circleIcon->getContentSize().height/2 -10);
	//=============================================
	circleMenu = Menu::create(flagIcon, upgradeIcon, nullptr);
	circleMenu->setPosition(0,0);
	circleMenu->setVisible(false);
	circleMenu->setEnabled(true);
	m_sprite->addChild(circleIcon);
	circleIcon->setVisible(false);
	m_sprite->addChild(circleMenu,100);
	m_sprite->setScale(0.5f);
	m_sprite->setPosition(Pos);
	m_sprite->setAnchorPoint(Vec2(0.3, 0));
	m_sprite->removeFromParent();
	layer->addChild(m_sprite, 5);
	if (type == BARRACKS_TOWER)
	{
		checkTypeTowerBarrack = true;
		rangeBarrackTower = Sprite::create("range_of_barrack_tower.png");
		//rangeBarrackTower->setScale(2.0f);
		rangeBarrackTower->setVisible(false);
		rangeBarrackTower->setPosition(m_sprite->getContentSize().width/2, m_sprite->getContentSize().height/2);
		m_sprite->addChild(rangeBarrackTower);
		for (int i = 0; i < 3; i++)
		{
			Soldier * m_soldier = new Soldier(layer);
			listSoldier.push_back(m_soldier);
			if ((i+1) % 2 != 0)
			{
				listSoldier[i]->GetSprite()->setPosition(Vec2(Pos.x + (i*i) * i, Pos.y + (i *i) * 2 * i));
			}
			else
			{
				listSoldier[i]->GetSprite()->setPosition(Vec2(Pos.x - (i*i) * i* 32, Pos.y + (i *i) * i*16));
			}
			//auto moveBy = MoveBy::create(1, Vec2(50, - 100));
			//listSoldier[i]->GetSprite()->runAction(moveBy->clone());
			listSoldier[i]->GetSprite()->setVisible(false);
		}
		

	}
	else
	{
		flagIcon->setEnabled(false);
		//rangeBarrackTower->setVisible(false);
	}
	for (int i = 0; i < 10; i++)
	{
		Bullet * bullet = new Bullet(layer, m_type);
		listBullet.push_back(bullet);
	}
}

Sprite * Tower::GetSprite()
{
	return m_sprite;
}
void Tower::Shoot(Monster * monster)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet[i]->GetSprite()->isVisible())
		{
			listBullet[i]->GetSprite()->setVisible(true);
			listBullet[i]->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height/2);
			listBullet[i]->Move(monster);
			break;
		}
	}
}

void Tower::Update(float deltaTime, Monster * monster)
{
	if (m_sprite->getPosition().getDistance(monster->GetSprite()->getPosition()) < m_range)
	{
		timeDelay += deltaTime;
		if (timeDelay > m_attackSpeed)
		{
			Shoot(monster);
			timeDelay = 0;
			checkTowerShoot = true;
		}
	}
}

bool Tower::GetCheckTowerShoot()
{
	return checkTowerShoot;
}

void Tower::SetCheckTowerShoot(bool check)
{
	checkTowerShoot = check;
}

vector<Monster*> Tower::GetlistMonsterInRange()
{
	return listMonsterInRange;
}

vector<Monster*> Tower::GetListMonsterNeighbor()
{
	return listMonsterNeighbor;
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

void Tower::FadeInPause()
{
	circleMenu->setVisible(true);
	circleMenu->setEnabled(true);
	circleIcon->setVisible(true);
}

void Tower::FadeOutPause()
{
	circleMenu->setVisible(false);
	circleMenu->setEnabled(false);
	circleIcon->setVisible(false);
}

bool Tower::GetCheckTouchFlag()
{
	return checkTouchFlag;
}

void Tower::SetCheckTouchFlag(bool checkTouchFlag)
{
	this->checkTouchFlag = checkTouchFlag;
}

Sprite * Tower::GetRangeBarrackTower()
{
	return rangeBarrackTower;
}

bool Tower::GetCheckTypeTowerBarrack()
{
	return checkTypeTowerBarrack;
}

vector<Soldier*> Tower::GetListSoldier()
{
	return listSoldier;
}

int Tower::GetTypeTower()
{
	return m_type;
}

int Tower::GetDamage()
{
	return random(m_minimumAtk, m_maximumAtk);
}
