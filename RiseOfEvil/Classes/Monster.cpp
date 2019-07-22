#include "Monster.h"
#include "ResourceManager.h"
using namespace std;
Monster::Monster(Layer * layer, int type)
{
	m_type = type;
	this->layer = layer;
	Init();
	m_maxHitPoint = m_hitPoint;
	layer->addChild(m_spriteNode, 3);
}

Monster::~Monster()
{
}

void Monster::Init()
{
	switch (m_type)
	{
	case NORMAL_MONSTER:
	{	
		m_spriteNode = SpriteBatchNode::create("Orc_Warrior_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Orc_Warrior_Walking.plist");
		
		m_sprite = Sprite::createWithSpriteFrameName("Orc_Walking_1.png");
		m_bloodBar = Sprite::createWithSpriteFrameName("loadingbar_bgWarrior.png");
		m_blood = Sprite::createWithSpriteFrameName("loadingbarWarrior.png");
		
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height/2));
		
		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood,8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "Orc_Walking_";		
		m_hitPoint = 24;
		m_maxHitPoint = 24;
		m_minimumAtk = 1;
		m_maximumAtk = 4;
		m_attackSpeed = 1.0;
		m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 6;
		break;
	}
	case MAGICAN_MONSTER:
		m_spriteNode = SpriteBatchNode::create("Gobin_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Gobin_Walking.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_gobin_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("loadingbar_bgGobin.png");
		m_blood = Sprite::createWithSpriteFrameName("loadingbarGobin.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_gobin_";
		m_hitPoint = 120;
		m_maxHitPoint = 120;
		m_minimumAtk = 5;
		m_maximumAtk = 7;
		m_attackSpeed = 1.0;
		m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case TANK_MONSTER:
		m_spriteNode = SpriteBatchNode::create("Minotaur_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur_Walking.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_Minotaur_1.png");
	
		m_bloodBar = Sprite::createWithSpriteFrameName("loadingbar_bgMinotaur.png");
		m_blood = Sprite::createWithSpriteFrameName("loadingbarMinotaur.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_Minotaur_";
		
		m_hitPoint = 960;
		m_maxHitPoint = 960;
		m_minimumAtk = 40;
		m_maximumAtk = 60;
		m_attackSpeed = 1.9;
		m_movementSpeed = m_velocity = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 40;
		break;
	case SPEED_MONSTER:
		m_spriteNode = SpriteBatchNode::create("Ant_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Ant_Walking.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_ant_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("loadingbar_bgAnt.png");
		m_blood = Sprite::createWithSpriteFrameName("loadingbarAnt.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_ant_";
		m_hitPoint = 42;
		m_maxHitPoint = 42;
		m_minimumAtk = 2;
		m_maximumAtk = 3;
		m_attackSpeed = 1.2;
		m_movementSpeed = m_velocity = FAST_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case SIEGE_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(SIEGE_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 58;
		m_minimumAtk = 3;
		m_maximumAtk = 8;
		m_attackSpeed = 1.0;
		m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case ELITE_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(ELITE_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 12000;
		m_minimumAtk = 150;
		m_maximumAtk = 250;
		m_attackSpeed = 2.5;
		m_movementSpeed = m_velocity = SLOW_SPEED;
		//sm_armor = 0;
		m_gold = 100;
		break;
	case DARKLORD:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(DARKLORD)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 21600;
		m_minimumAtk = 200;
		m_maximumAtk = 400;
		m_attackSpeed = 2.0;
		m_movementSpeed = m_velocity = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 500;
		break;
	default:
		break;
	}
}
float timeCount = 0.5;
void Monster::Update(float deltaTime)
{
	if (timeCount >= 1.0)
	{
		m_sprite->setVisible(true);
		timeCount = 0;
	}
	else {
		timeCount += deltaTime;
	}
	
}

void Monster::Move(Vec2 point)
{
	if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x <= point.x)) {
		Action(E);
		checkMove = 1;
	}
	else if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x >= point.x)) {
		Action(W);
		checkMove = 2;
	}
	else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(S);
		checkMove = 3;
	}
	else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y <= point.y)) {
		Action(N);
		checkMove = 4;
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(SE);
		checkMove = 5;
	}
	else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(SW);
		checkMove = 6;
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y <= point.y)) {
		Action(NE);
		checkMove = 7;
	}
	else if((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y <= point.y))
	{
		Action(NW);
		checkMove = 8;
	}

	m_sprite->runAction(MoveTo::create(point.getDistance(m_sprite->getPosition()) / m_movementSpeed, Vec2(point.x, point.y)));
}
Animation* Monster::AnimationMonster(string prefixName, int pFrameBegin, int pFrameEnd, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = pFrameBegin; i <= pFrameEnd; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);

		string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}

void Monster::Action(int direction)
{
	switch (direction)
	{
	case E:
	{
		m_sprite->stopAllActions();
		auto walkingE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[8], m_png[9], 0.05f));
		walkingE->retain();
		m_sprite->runAction(RepeatForever::create(walkingE));
		break;
	}

	case W:
	{
		m_sprite->stopAllActions();
		auto walkingW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[0], m_png[1], 0.05f));
		walkingW->retain();
		m_sprite->runAction(RepeatForever::create(walkingW));
		break;
	}

	case S:
	{
		m_sprite->stopAllActions();
		auto walkingS = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[12], m_png[13], 0.05f));
		walkingS->retain();
		m_sprite->runAction(RepeatForever::create(walkingS));
		break;
	}

	case N:
	{
		m_sprite->stopAllActions();
		auto walkingN = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[4], m_png[5], 0.05f));
		walkingN->retain();
		m_sprite->runAction(RepeatForever::create(walkingN));
		break;
	}

	case SE:
	{
		m_sprite->stopAllActions();
		auto walkingSE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[10], m_png[11], 0.05f));
		walkingSE->retain();
		m_sprite->runAction(RepeatForever::create(walkingSE));
		break;
	}

	case SW:
	{
		m_sprite->stopAllActions();
		auto walkingSW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[14], m_png[15], 0.05f));
		walkingSW->retain();
		m_sprite->runAction(RepeatForever::create(walkingSW));
		break;
	}

	case NE:
	{
		m_sprite->stopAllActions();
		auto walkingNE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[6], m_png[7], 0.05f));
		walkingNE->retain();
		m_sprite->runAction(RepeatForever::create(walkingNE));
		break;
	}

	case NW:
	{
		m_sprite->stopAllActions();
		auto walkingNW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[2], m_png[3], 0.05f));
		walkingNW->retain();
		m_sprite->runAction(RepeatForever::create(walkingNW));
		break;
	}

	}
}

void Monster::Acttack(Object * target)
{
}

void Monster::DoDead()
{
	int num = random(1, 4);
	auto seq = Sequence::create(DelayTime::create(0.3f), FadeOut::create(0), nullptr);
	switch (num)
	{
	case 1:
		dead1 = Sprite::create("dead1.png");
		dead1->setPosition(m_sprite->getPosition());
		layer->addChild(dead1, 3);
		dead1->runAction(seq);
		break;
	case 2:
		dead2 = Sprite::create("dead2.png");
		dead2->setPosition(m_sprite->getPosition());
		layer->addChild(dead2, 3);
		dead2->runAction(seq->clone());
		break;
	case 3:
		dead3 = Sprite::create("dead3.png");
		dead3->setPosition(m_sprite->getPosition());
		layer->addChild(dead3, 3);
		dead3->runAction(seq->clone());
		break;
	default:
		break;
	}
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

void Monster::setProgressBar()
{
	m_blood->setScaleX(abs(m_hitPoint / (m_maxHitPoint * 1.0)));
}

float Monster::GetVelocity()
{
	return m_velocity;
}

int Monster::GetCheckMove()
{
	return checkMove;
}


