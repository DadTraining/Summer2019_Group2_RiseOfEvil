#include "Monster.h"
#include "ResourceManager.h"
using namespace std;
Monster::Monster(Layer * layer, int type)
{
	m_type = type;
	Init();
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
		//	m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(NORMAL_MONSTER)); //id = id of NORMAL_MONSTER
		m_spriteNode = SpriteBatchNode::create("Orc_Warrior_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Orc_Warrior_Walking.plist");
		m_sprite = Sprite::createWithSpriteFrameName("Orc_Walking_1.png");
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "Orc_Walking_";
		m_png[0] = 1;
		m_png[1] = 10;
		m_png[2] = 71;
		m_png[3] = 80;
		m_png[4] = 41;
		m_png[5] = 50;
		m_png[6] = 11;
		m_png[7] = 20;
		m_png[8] = 51;
		m_png[9] = 60;
		m_png[10] = 61;
		m_png[11] = 70;
		m_png[12] = 21;
		m_png[13] = 30;
		m_png[14] = 31;
		m_png[15] = 40;
		m_hitPoint = 24;
		m_minimumAtk = 1;
		m_maximumAtk = 4;
		m_attackSpeed = 1.0;
		m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 6;
		break;
	case MAGICAN_MONSTER:
		m_spriteNode = SpriteBatchNode::create("Minotaur_Walking.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur_Walking.plist");
		m_sprite = Sprite::createWithSpriteFrameName("_Minotaur_1.png");
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_Minotaur_";
		m_png[0] = 1;
		m_png[1] = 10;
		m_png[2] = 71;
		m_png[3] = 80;
		m_png[4] = 41;
		m_png[5] = 50;
		m_png[6] = 11;
		m_png[7] = 20;
		m_png[8] = 51;
		m_png[9] = 60;
		m_png[10] = 61;
		m_png[11] = 70;
		m_png[12] = 21;
		m_png[13] = 30;
		m_png[14] = 31;
		m_png[15] = 40;
		m_hitPoint = 120;
		m_minimumAtk = 5;
		m_maximumAtk = 7;
		m_attackSpeed = 1.0;
		m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	case TANK_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(TANK_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 960;
		m_minimumAtk = 40;
		m_maximumAtk = 60;
		m_attackSpeed = 1.9;
		m_movementSpeed = m_velocity = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 40;
		break;
	case SPEED_MONSTER:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(MAGICAN_MONSTER)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 42;
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
	if (timeCount >= 2.0)
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
	}
	else if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x >= point.x)) {
		Action(W);
		m_velocity = -m_velocity;
	}
	else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(S);
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(SE);
	}
	else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y >= point.y)) {
		Action(SW);
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y <= point.y)) {
		Action(NE);
	}
	else
		Action(NW);
	m_sprite->runAction(MoveTo::create(point.getDistance(m_sprite->getPosition()) / abs(m_movementSpeed), Vec2(point.x, point.y)));
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
		auto walkingE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[0], m_png[1], 0.05f));
		walkingE->retain();
		m_sprite->runAction(RepeatForever::create(walkingE));
		break;
	}

	case W:
	{
		m_sprite->stopAllActions();
		auto walkingW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[2], m_png[3], 0.05f));
		walkingW->retain();
		m_sprite->runAction(RepeatForever::create(walkingW));
		break;
	}

	case S:
	{
		m_sprite->stopAllActions();
		auto walkingS = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[4], m_png[5], 0.05f));
		walkingS->retain();
		m_sprite->runAction(RepeatForever::create(walkingS));
		break;
	}

	case N:
	{
		m_sprite->stopAllActions();
		auto walkingN = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[6], m_png[7], 0.05f));
		walkingN->retain();
		m_sprite->runAction(RepeatForever::create(walkingN));
		break;
	}

	case SE:
	{
		m_sprite->stopAllActions();
		auto walkingSE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[8], m_png[9], 0.05f));
		walkingSE->retain();
		m_sprite->runAction(RepeatForever::create(walkingSE));
		break;
	}

	case SW:
	{
		m_sprite->stopAllActions();
		auto walkingSW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[10], m_png[11], 0.05f));
		walkingSW->retain();
		m_sprite->runAction(RepeatForever::create(walkingSW));
		break;
	}

	case NE:
	{
		m_sprite->stopAllActions();
		auto walkingNE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[12], m_png[13], 0.05f));
		walkingNE->retain();
		m_sprite->runAction(RepeatForever::create(walkingNE));
		break;
	}

	case NW:
	{
		m_sprite->stopAllActions();
		auto walkingNW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[14], m_png[15], 0.05f));
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

float Monster::GetVelocity()
{
	return m_velocity;
}
