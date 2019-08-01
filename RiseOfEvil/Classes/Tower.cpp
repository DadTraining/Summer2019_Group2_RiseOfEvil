#include"Tower.h"
#define PI 3.14

void Tower::Init()
{
	switch (m_type)
	{
	case ARROW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/arrowtower1.png");
		m_hitPoint = 100;
		baseMinnimumAtk = m_minimumAtk = 4;
		baseMaximumAtk = m_maximumAtk = 6;
		baseAttackSpeed = m_minimumAttackSpeed = m_attackSpeed = 0.8;
		m_range = 160;
		m_gold = 70;
		break;
	case MAGIC_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/magictower1.png");
		m_hitPoint = 100;
		baseMinnimumAtk = m_minimumAtk = 9;
		baseMaximumAtk = m_maximumAtk = 17;
		m_minimumAttackSpeed = m_attackSpeed = 1.5;
		baseAttackSpeed = 1.5;
		m_range = 240;
		m_gold = 100;
		break;
	case SLOW_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/slowtower1.png");
		m_hitPoint = 100;
		baseMinnimumAtk = m_minimumAtk = 1;
		baseMaximumAtk = m_maximumAtk = 3;
		baseAttackSpeed = m_minimumAttackSpeed = m_attackSpeed = 1.3;
		m_range = 180;
		m_gold = 80;
		break;
	case BOMBARD_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/boomtower1.png");
		m_hitPoint = 100;
		baseMinnimumAtk = m_minimumAtk = 10;
		baseMaximumAtk = m_maximumAtk = 18;
		baseAttackSpeed = m_minimumAttackSpeed = m_attackSpeed = 3.0;
		m_range = 180;
		m_gold = 120;
		break;
	case BARRACKS_TOWER:
		m_sprite = Sprite::create("res/WorldScene1/brracktower1.png");
		m_hitPoint = 100;
		baseMinnimumAtk = m_minimumAtk = 0;
		baseMaximumAtk = m_maximumAtk = 0;
		baseAttackSpeed = m_minimumAttackSpeed = m_attackSpeed = 300000.0;
		m_range = 250;
		m_gold = 70;
		break;
	}
}

Tower::Tower(Layer * layer, int type, Vec2 Pos)
{
	m_type = type;
	this->layer = layer;
	Init();
	m_level = 1;
	priceUpgradeLabel = Label::createWithTTF(to_string(m_gold), "fonts/Comic_Book.ttf", 25);
	priceUpgradeLabel->setColor(Color3B::YELLOW);
	circleIcon = MenuItemImage::create("CircleMenu.png", "CircleMenu.png", [&](Ref* sender) {
	});
	circleIcon->setPosition(m_sprite->getPosition() + m_sprite->getContentSize() / 2);

	flagIcon = MenuItemImage::create("FlagCallSoldier.png", "FlagCallSoldier_disable.png", "FlagCallSoldier_disable.png", [&](Ref* sender) {
		HideCircleMenu();
		rangeBarrackTower->setVisible(true);
		checkTouchFlag = true;
		for (int i = 0; i < GetListSoldier().size(); i++)
		{
			GetListSoldier()[i]->SetTouchFlag(true);
		}
	});
	flagIcon->setPosition(circleIcon->getPosition().x + circleIcon->getContentSize().width / 2 -10, circleIcon->getPosition().y);
	flagIcon->setVisible(false);
	upgradeIcon = MenuItemImage::create("upgrade_button_normal.png", "upgrade_button_press.png", "upgrade_button_press.png",[&](Ref* sender)
	{
		requestUpdate = true;
	});
	upgradeIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y + circleIcon->getContentSize().height/2 -10);
	priceUpgradeLabel->setPosition(upgradeIcon->getContentSize().width / 2, 10);
	upgradeIcon->addChild(priceUpgradeLabel);
	//=============================================
	sellIcon = MenuItemImage::create("sellBtn.png", "sellBtn.png", "sellBtn.png", [&](Ref* sender) {
		clickSellIcon();
	});
	sellIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y - circleIcon->getContentSize().height/2 + 10);
	//=============================================
	confirmIcon = MenuItemImage::create("confirm.png", "confirm_disable.png", "confirm_disable.png", [&](Ref* sender) {
		isSell = true;

		confirmSell();
	});
	confirmIcon->setPosition(circleIcon->getPosition().x, circleIcon->getPosition().y - circleIcon->getContentSize().height / 2 + 10);
	confirmIcon->setScale(0.9f);
	confirmIcon->setVisible(false);
	//===================================================
	skillIcon = MenuItemImage::create("Skills/icon_skill.png", "Skills/icon_skill.png", [&](Ref* sender) {
		skillDetail->setVisible(true);
	});
	skillIcon->setPosition(-circleIcon->getContentSize().width/2 + 40, circleIcon->getPosition().y);
	skillIcon->setVisible(false);
	skillIcon->setScale(0.8f);
	//=====================================================
	circleMenu = Menu::create(flagIcon, sellIcon, upgradeIcon, confirmIcon, skillIcon, nullptr);
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
		flagIcon->setVisible(true);
		checkTypeTowerBarrack = true;
		rangeBarrackTower = Sprite::create("range_of_barrack_tower.png");
		rangeBarrackTower->setVisible(false);
		rangeBarrackTower->setPosition(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2);
		m_sprite->addChild(rangeBarrackTower);
		
		for (int i = 0; i < 3; i++)
		{
			Soldier * m_soldier = new Soldier(layer);
			listSoldier.push_back(m_soldier);
			m_soldier->GetSprite()->setPosition(Vec2(m_sprite->getPosition()));
			if ((i + 1) % 2 != 0)
			{
				listSoldier[i]->Move(Vec2(Pos.x + (i*i) *i, Pos.y + (i *i) * 2 * i));
			}
			else
			{
				listSoldier[i]->Move(Vec2(Pos.x - (i*i) * i * 32, Pos.y + (i * i) *  i * 16));
			}
		}
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
			skillDetail = Sprite::create("Skills/details/arrowskill_detail.png");
			skillDetail->setPosition(-circleIcon->getContentSize().width / 2, circleIcon->getPosition().y);
			skillDetail->setVisible(false);
			skillIcon->addChild(skillDetail);
			break;
		}
		case MAGIC_TOWER:
		{
			towerSkill = new Skill(INCREASE_ATTACKDAMAGE_SKILL);
			skillDetail = Sprite::create("Skills/details/magic_skill.png");
			skillDetail->setPosition(-circleIcon->getContentSize().width / 2, circleIcon->getPosition().y);
			skillDetail->setVisible(false);
			skillIcon->addChild(skillDetail);
			break;
		}
		case SLOW_TOWER:
		{
			towerSkill = new Skill(SLOW_TOWER);
			skillDetail = Sprite::create("Skills/details/slow_detail.png");
			skillDetail->setPosition(-circleIcon->getContentSize().width / 2, circleIcon->getPosition().y);
			skillDetail->setVisible(false);
			skillIcon->addChild(skillDetail);
			break;
		}
		case BOMBARD_TOWER:
		{
			towerSkill = new Skill(BOMBARD_TOWER);
			skillDetail = Sprite::create("Skills/details/burn_detail.png");
			skillDetail->setPosition(-circleIcon->getContentSize().width / 2, circleIcon->getPosition().y);
			skillDetail->setVisible(false);
			skillIcon->addChild(skillDetail);
			break;
		}
	}
	if (m_type != BARRACKS_TOWER)
	{
		towerSkill->getSprite()->setPosition(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2);
		towerSkill->getSprite()->setVisible(false);
		if (m_type == SLOW_TOWER)
		{
			auto scaleTo1 = ScaleTo::create(0.2, 0.2);
			auto scaleTo2 = ScaleTo::create(0.2, 0.4);
			auto scaleTo3 = ScaleTo::create(0.2, 0.6);
			auto scaleTo4 = ScaleTo::create(0.2, 0.8);
			auto scaleTo5 = ScaleTo::create(0.2, 1);
			auto seq = Sequence::create(scaleTo1, scaleTo2, scaleTo3, scaleTo4, scaleTo5, scaleTo4->clone(), scaleTo3->clone(), scaleTo2->clone(), scaleTo1->clone(), nullptr);
			towerSkill->getSprite()->runAction(RepeatForever::create(seq));
		}
		if (m_type == BOMBARD_TOWER)
		{
			auto scaleTo1 = ScaleTo::create(0.2, 0.2);
			auto scaleTo2 = ScaleTo::create(0.2, 0.4);
			auto scaleTo3 = ScaleTo::create(0.2, 0.6);
			auto scaleTo4 = ScaleTo::create(0.2, 0.8);
			auto scaleTo5 = ScaleTo::create(0.2, 1);
			auto seq = Sequence::create(scaleTo1, scaleTo2, scaleTo3, scaleTo4, scaleTo5, scaleTo4->clone(), scaleTo3->clone(), scaleTo2->clone(), scaleTo1->clone(), nullptr);
			towerSkill->getSprite()->runAction(RepeatForever::create(seq));
		}
		m_sprite->addChild(towerSkill->getSprite(), 6);
	}
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
	switch (m_type)
	{
	case ARROW_TOWER:
		towerArrowAttackSound = SimpleAudioEngine::getInstance();
		towerArrowAttackSound->playEffect("sound/Sound_ArrowHit3.wav", false);
		break;
	case MAGIC_TOWER:
		towerMagicAttackSound = SimpleAudioEngine::getInstance();
		towerMagicAttackSound->playEffect("sound/necromancer_attack.wav", false);
		break;
	case SLOW_TOWER:
		towerSlowwAttackSound = SimpleAudioEngine::getInstance();
		towerSlowwAttackSound->playEffect("sound/Sound_MageShot.wav", false);
		break;
	case BOMBARD_TOWER:
		towerBoombardAttackSound = SimpleAudioEngine::getInstance();
		towerBoombardAttackSound->playEffect("sound/Sound_Bomb1.wav", false);
		break;
	case BARRACKS_TOWER:
		towerBarrackAttackSound = SimpleAudioEngine::getInstance();
		towerBarrackAttackSound->playEffect("sound/Sound_TowerOpenDoor.wav", false);
		break;
	}

}

void Tower::Update(float deltaTime, vector<Monster*> listMonster)
{
	if (target != nullptr)
	{
		if (!target->GetSprite()->isVisible() || target->GetSprite()->getPosition().getDistance(m_sprite->getPosition()) > m_range)
		{
			target = nullptr;
			return;
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
	if (m_type != BARRACKS_TOWER)
	{
		skillDetail->setVisible(false);
	}
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
	auto *animation = Sprite::create("upgradeAnimation.png");
	animation->setPosition(m_sprite->getPosition());
	animation->setAnchorPoint(Vec2(0.5, 0));
	animation->runAction(Sequence::create(MoveBy::create(0.2, Vec2(0, 20)), FadeOut::create(0), RemoveSelf::create(), nullptr));
	layer->addChild(animation, 6);
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
		m_gold *= m_level;
		if (m_level == 2)
		{
			m_gold *= 2;
		}
	}
	if (m_level == 3 && m_type != BARRACKS_TOWER)
	{
		towerSkill->getSprite()->setVisible(true);
		skillIcon->setVisible(true);
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

Label * Tower::getPriceUpgradeLabel()
{
	return priceUpgradeLabel;
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

bool Tower::getIncreaseAttackSpeedSkill()
{
	return checkIncreaseAttackSpeedSkill;
}
bool Tower::getIncreaseAttackDamageSkill()
{
	return checkIncreaseAttackDamageSkill;
}

void Tower::setIncreaseAttackSpeedSkill(bool check)
{
	checkIncreaseAttackSpeedSkill = check;
}

void Tower::setIncreaseAttackDamageSkill(bool check)
{
	checkIncreaseAttackDamageSkill = check;
}


void Tower::slowSkill(vector<Monster*> listMonster)
{
	try
	{
		for (int i = 0; i < listMonster.size(); i++)
		{
			if (m_sprite->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150
				&& listMonster[i]->GetMovementSpeed() > listMonster[i]->GetMSpeed() * 60 / 100 && !listMonster[i]->IsDead())
			{
				listMonster[i]->SetMovementSpeed(listMonster[i]->GetMovementSpeed() - listMonster[i]->GetMSpeed() * 10 / 100);
				//checkSlowSkill = true;
			}
		}
	}
	catch (...)
	{
		log("error in slow skill in Tower.cpp");
	}
	
}

void Tower::burnSkill(vector<Monster*> listMonster, float deltaTime)
{
	try
	{
		if (countTimeToReduceHPForBurnSkill >= 1)
		{
			for (int i = 0; i < listMonster.size(); i++)
			{
				if (m_sprite->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) < 150 && !listMonster[i]->IsDead())
				{
					listMonster[i]->SetHitPoint(listMonster[i]->GetHitPoint() - 10);
					countTimeToReduceHPForBurnSkill = 0;
					checkBurnSkill = true;
				}
			}
		}
		else
		{
			countTimeToReduceHPForBurnSkill += deltaTime;
		}
	}
	catch (...)
	{
		log("error in burn skill in Tower.cpp");
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
void Tower::clickSellIcon()
{
	confirmIcon->setEnabled(true);
	confirmIcon->setVisible(true);
	sellIcon->setEnabled(false);
	sellIcon->setVisible(false);
}

void Tower::confirmSell()
{
	confirmIcon->setEnabled(false);
	confirmIcon->setVisible(false);
	sellIcon->setEnabled(true);
	sellIcon->setVisible(true);
}

float Tower::getMinimumAttackSpeed()
{
	return m_minimumAttackSpeed;
}

Skill * Tower::getTowerSkill()
{
	return towerSkill;
}

void Tower::showDetailSkill()
{

}

void Tower::resetTower(int level)
{
	switch (level)
	{
	case 1:
		m_minimumAtk = baseMinnimumAtk;
		m_maximumAtk = baseMaximumAtk;
		m_attackSpeed = baseAttackSpeed;
		break;
	case 2:
		m_minimumAtk = baseMinnimumAtk * 2;
		m_maximumAtk = baseMaximumAtk * 2;
		m_attackSpeed = baseAttackSpeed * 2;
		break;
	case 3:
		m_minimumAtk = baseMinnimumAtk * 6;
		m_maximumAtk = baseMaximumAtk * 6;
		m_attackSpeed = baseAttackSpeed * 6;
		break;
	}
}
float timeReborn = 0;
void Tower::Reborn(float deltaTime)
{
	if (timeReborn > 10)
	{
		for (int i = 0; i < listSoldier.size(); i++)
		{
			if (listSoldier[i]->IsDead())
			{
				listSoldier[i]->GetSprite()->setPosition(Vec2(m_sprite->getPosition()));
				listSoldier[i]->SetHitPoint(listSoldier[i]->GetMaxHitPoint());
				listSoldier[i]->GetSprite()->setVisible(true);
				listSoldier[i]->SetCheckGuard(false);
				listSoldier[i]->SetTouchFlag(true);		
				listSoldier[i]->Reborn();
				listSoldier[i]->Move(Vec2(flag.x + random(-5, 5), flag.y + random(-5, 5)));				
			}
		}
		timeReborn = 0;
	}
	else
	{
		timeReborn += deltaTime;
	}
	
}
void Tower::SetFlagLocation(Vec2 flag)
{
	this->flag = flag;
}
Sprite * Tower::getSkillDetails()
{
	return skillDetail;
}

int Tower::GetDamage()
{
	return random(m_minimumAtk, m_maximumAtk);
}
