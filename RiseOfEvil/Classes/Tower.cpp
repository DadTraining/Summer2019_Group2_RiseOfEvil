#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/arrowtower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 4;
		m_maximumAtk = 6;
		m_attackSpeed = 0.8;
		m_range = 160;
		m_gold = 70;
		break;
	case MAGIC_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/magictower1.png");
		m_hitPoint = 100;
		m_minimumAtk = 9;
		m_maximumAtk = 17;
		m_attackSpeed = 1.5;
		m_range = 240;
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
	m_level = 1;
	circleIcon = MenuItemImage::create("CircleMenu.png", "CircleMenu.png", [&](Ref* sender) {
	});
	circleIcon->setPosition(m_sprite->getPosition() + m_sprite->getContentSize() / 2);

	flagIcon = MenuItemImage::create("FlagCallSoldier.png", "FlagCallSoldier_disable.png", "FlagCallSoldier_disable.png", [&](Ref* sender) {
		HideCircleMenu();
		rangeBarrackTower->setVisible(true);
		checkTouchFlag = true;
	});
	flagIcon->setPosition(circleIcon->getPosition().x + circleIcon->getContentSize().width / 2 -10, circleIcon->getPosition().y);
	upgradeIcon = MenuItemImage::create("upgrade_button_normal.png", "upgrade_button_press.png", "upgrade_button_press.png",[&](Ref* sender)
	{
		requestUpdate = true;
	});
	upgradeIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y + circleIcon->getContentSize().height/2 -10);
	//=============================================
	sellIcon = MenuItemImage::create("sellBtn.png", "sellBtn.png", "sellBtn.png", [&](Ref* sender) {
		isSell = true;
	});
	sellIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y - circleIcon->getContentSize().height/2 + 10);
	circleMenu = Menu::create(flagIcon, sellIcon, upgradeIcon, nullptr);
	circleMenu->setPosition(0,0);
	circleMenu->setVisible(false);
	circleMenu->setEnabled(true);
	m_sprite->addChild(circleIcon);
	circleIcon->setVisible(false);
	m_sprite->addChild(circleMenu);
	m_sprite->setScale(0.6f);
	m_sprite->setPosition(Pos);
	m_sprite->setAnchorPoint(Vec2(0.3, 0));
	m_sprite->removeFromParent();
	layer->addChild(m_sprite, 5);
	if (type == BARRACKS_TOWER)
	{
		checkTypeTowerBarrack = true;
		rangeBarrackTower = Sprite::create("range_of_barrack_tower.png");
		rangeBarrackTower->setVisible(false);
		rangeBarrackTower->setPosition(m_sprite->getContentSize().width/2, m_sprite->getContentSize().height/2);
		switch (m_level)
		{
		case 1:
			numberOfSoldier = 3;
			break;
		case 2:
			numberOfSoldier = 4;
			break;
		case 3:
			numberOfSoldier = 5;
			break;
		}
		//for (int i = 0; i < numberOfSoldier; i++)
		//{
		//	Soldier * m_soldier = new Soldier(layer, m_level);
		//	listSoldier.push_back(m_soldier);
		//}
		//for (int i = 0; i < listSoldier.size(); i++)
		//{
		//	m_sprite->addChild(listSoldier[i]->GetSprite(), 6);
		//}
		//listSoldier[0]->GetSprite()->setPosition(Vec2(Pos.x, Pos.y));
		//listSoldier[1]->GetSprite()->setPosition(Vec2(Pos.x + 15, Pos.y));
		//listSoldier[2]->GetSprite()->setPosition(Vec2(Pos.x + 30, Pos.y + 30));
	}
	else
	{
		flagIcon->setEnabled(false);
	}
	for (int i = 0; i < 10; i++)
	{
		Bullet * bullet = new Bullet(layer, m_type);
		listBullet.push_back(bullet);
	}
	switch (m_type)
	{
		case ARROW_TOWER:
		{
			towerSkill = new Skill(INCREASE_ATTACKSPEED_SKILL);
			break;
		}
		case MAGIC_TOWER:
		{
			towerSkill = new Skill(INCREASE_ATTACKDAMAGE_SKILL);
			break;
		}
		case SLOW_TOWER:
		{
			towerSkill = new Skill(SLOW_TOWER);
			break;
		}
		case BOMBARD_TOWER:
		{
			towerSkill = new Skill(BOMBARD_TOWER);
			break;
		}
	}
	towerSkill->getSprite()->setPosition(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2);
	towerSkill->getSprite()->setVisible(false);
	m_sprite->addChild(towerSkill->getSprite(), 6);
}

Tower::~Tower()
{
	m_sprite->removeFromParent();
	m_sprite->release();
}

Sprite * Tower::GetSprite()
{
	return m_sprite;
}

void Tower::Shoot(vector<Monster*> listMonster)
{
	for (int i = 0; i < listBullet.size(); i++)
	{
		if (!listBullet[i]->GetSprite()->isVisible())
		{
			listBullet[i]->GetSprite()->setVisible(true);
			listBullet[i]->GetSprite()->setPosition(m_sprite->getPositionX(), m_sprite->getPositionY() + m_sprite->getContentSize().height/2);
			listBullet[i]->Move(target, GetDamage(), listMonster, m_type);
			break;
		}
	}
}

void Tower::Update(float deltaTime, vector<Monster*> listMonster)
{
	if (target != nullptr)
	{
		if (!target->GetSprite()->isVisible() || target->GetSprite()->getPosition().getDistance(m_sprite->getPosition()) > m_range)
		{
			target = nullptr;
		}
		if (timeDelay > m_attackSpeed)
		{
			Shoot(listMonster);
			timeDelay = 0;
			checkTowerShoot = true;
		}
		else
		{
			timeDelay += deltaTime;
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

void Tower::ShowCircleMenu()
{
	circleMenu->setVisible(true);
	circleMenu->setEnabled(true);
	circleIcon->setVisible(true);
}

void Tower::HideCircleMenu()
{
	circleMenu->setVisible(false);
	circleMenu->setEnabled(false);
	circleIcon->setVisible(false);
}

bool Tower::GetCheckTouchFlag()
{
	return checkTouchFlag;
}

int Tower::GetType()
{
	return m_type;
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

bool Tower::getIsSell()
{
	return isSell;
}

int Tower::getLevel()
{
	return m_level;
}

void Tower::upgrade()
{
	m_level++;
	if (m_level <= 3)
	{
		switch (m_type)
		{
		case ARROW_TOWER:
			m_sprite->setTexture("res/WorldScene1/arrowtower" + to_string(m_level) + ".png");
			break;
		case MAGIC_TOWER:
			m_sprite->setTexture("res/WorldScene1/magictower" + to_string(m_level) + ".png");
			break;
		case SLOW_TOWER:
			m_sprite->setTexture("res/WorldScene1/slowtower" + to_string(m_level) + ".png");
			break;
		case BOMBARD_TOWER:
			m_sprite->setTexture("res/WorldScene1/boomtower" + to_string(m_level) + ".png");
			break;
		case BARRACKS_TOWER:
			m_sprite->setTexture("res/WorldScene1/brracktower" + to_string(m_level) + ".png");
			break;
		default:
			break;
		}
		m_hitPoint *= m_level;
		m_minimumAtk *= m_level;
		m_maximumAtk *= m_level;
		m_gold += m_gold;
	}
	if (m_level == 3)
	{
		towerSkill->getSprite()->setVisible(true);
	}
}

bool Tower::getRequestUpdate()
{
	return requestUpdate;
}

void Tower::acceptUpdate(bool condition)
{
	if (condition)
	{
		upgrade();
		requestUpdate = false;
	}
}

MenuItemImage * Tower::getUpgradeIcon()
{
	return upgradeIcon;
}

Monster * Tower::getTarget()
{
	return target;
}

void Tower::setTarget(Monster * monster)
{
	target = monster;
}

bool Tower::getStatusOfTarget()
{
	if (target == nullptr)
	{
		return true;
	}
	if (m_sprite->getPosition().distance(target->GetSprite()->getPosition()) > m_range
		||
		target->GetSprite()->isVisible() == false
		)
	{
		return true;
	}
	return false;
}

void Tower::increaseAttackSpeedSkill(vector<Tower*> listTower)
{
	for (int i = 0; i < listTower.size(); i++)
	{
		float increaseAttackSpeed = listTower[i]->GetAttackSpeed() + listTower[i]->GetAttackSpeed() * 20 / 100;
		if (m_sprite->getPosition().distance(listTower[i]->GetSprite()->getPosition()) < 150)
		{
			listTower[i]->SetAttackSpeed(increaseAttackSpeed);
		}
	}
}

void Tower::increaseAttackDamageSkill(vector<Tower*> listTower)
{
	for (int i = 0; i < listTower.size(); i++)
	{
		int increaseMinimumAtk = listTower[i]->GetMinimumAtk() + (int)listTower[i]->GetMinimumAtk() * 20 / 100;
		int increaseMaximumAtk = listTower[i]->GetMaximumAtk() + (int)listTower[i]->GetMaximumAtk() * 20 / 100;
		if (m_sprite->getPosition().distance(listTower[i]->GetSprite()->getPosition()) < 150)
		{
			listTower[i]->SetMinimumAtk(increaseMinimumAtk);
			listTower[i]->SetMaximumAtk(increaseMaximumAtk);
		}
	}
}

void Tower::slowSkill(vector<Monster*> listMonster)
{
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (m_sprite->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150 
			&& listMonster[i]->GetMovementSpeed() > listMonster[i]->GetMSpeed() * 60 / 100)
		{
			listMonster[i]->SetMovementSpeed(listMonster[i]->GetMovementSpeed() - listMonster[i]->GetMSpeed() * 10 / 100);
		}
	//	log("speed of monster %d: %f", i ,listMonster[i]->GetMovementSpeed());
			// if monster out range increase speed 
	}
}

void Tower::burnSkill(vector<Monster*> listMonster, float deltaTime)
{
	if (countTimeToReduceHPForBurnSkill >= 1)
	{
		for (int i = 0; i < listMonster.size(); i++)
		{
				if (m_sprite->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150)
				{
					listMonster[i]->SetHitPoint(listMonster[i]->GetHitPoint() - 5);
					countTimeToReduceHPForBurnSkill = 0;
				}
			}
		}
	else
	{
		countTimeToReduceHPForBurnSkill += deltaTime;
	}
}

void Tower::bossSkill(Monster * boss, vector<Monster*> listMonster, float deltaTime)
{
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (boss->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150)
		{
			listMonster[i]->SetMSpeed(listMonster[i]->GetMSpeed() + 10);
			if (listMonster[i]->GetHitPoint() < listMonster[i]->GetMaxHitPoint())
			{
				if (countTimeToIncreaseHP > 1)
				{
					listMonster[i]->SetHitPoint(listMonster[i]->GetHitPoint() + 5);
					countTimeToIncreaseHP = 0;
				}
				else
				{
					countTimeToIncreaseHP += deltaTime;
				}
			}
		}
	}
}

int Tower::GetDamage()
{
	return random(m_minimumAtk, m_maximumAtk);
}
