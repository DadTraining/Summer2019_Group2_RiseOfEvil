#include "Monster.h"
#include "ResourceManager.h"
using namespace std;
Monster::Monster(Layer * layer, int type)
{
	m_type = type;
	this->layer = layer;
	Init();
	speed = m_speed * 80 / 100;
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

		rand = random(0, 1);
		if (rand == 0)
		{
			m_spriteNode = SpriteBatchNode::create("skeleton.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skeleton.plist");

			m_sprite = Sprite::createWithSpriteFrameName("_skeleton_1.png");
			m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_skeleton.png");
			m_blood = Sprite::createWithSpriteFrameName("healthbar_skeleton.png");

			m_blood->setAnchorPoint(Point(0, 0.5));
			m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

			m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
			m_bloodBar->setScale(0.2);

			m_bloodBar->addChild(m_blood, 8);
			m_sprite->addChild(m_bloodBar, 6);
			m_spriteNode->addChild(m_sprite);
			m_sprite->setVisible(false);
			m_fomatAnimation = "_skeleton_";
			m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
			m_png[16] = 65; m_png[17] = 78; m_png[18] = 79; m_png[19] = 92; m_png[20] = 93; m_png[21] = 106; m_png[22] = 107; m_png[23] = 120; m_png[24] = 121; m_png[25] = 134; m_png[26] = 135; m_png[27] = 148; m_png[28] = 149; m_png[29] = 162; m_png[30] = 163; m_png[31] = 176;
			m_hitPoint = 24;
			m_maxHitPoint = 24;
			m_minimumAtk = 1;
			m_maximumAtk = 4;
			m_attackSpeed = 1.0;
			m_runAnimation = 0.05f;
			m_attackAnimation = 0.1f;
			m_range = 20;
			m_speed = m_movementSpeed = m_velocity = MEDIUM_SPEED;
			m_armor = 0;
			m_gold = 6;
			break;
		}
		else
		{
			m_spriteNode = SpriteBatchNode::create("skeletongirl.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("skeletongirl.plist");

			m_sprite = Sprite::createWithSpriteFrameName("_skeletongirl_1.png");
			m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_skeletongirl.png");
			m_blood = Sprite::createWithSpriteFrameName("healthbar_skeletongirl.png");

			m_blood->setAnchorPoint(Point(0, 0.5));
			m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

			m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
			m_bloodBar->setScale(0.2);

			m_bloodBar->addChild(m_blood, 8);
			m_sprite->addChild(m_bloodBar, 6);
			m_spriteNode->addChild(m_sprite);
			m_sprite->setVisible(false);
			m_fomatAnimation = "_skeletongirl_";
			m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
			m_png[16] = 65; m_png[17] = 74; m_png[18] = 75; m_png[19] = 84; m_png[20] = 85; m_png[21] = 94; m_png[22] = 95; m_png[23] = 104; m_png[24] = 105; m_png[25] = 114; m_png[26] = 115; m_png[27] = 124; m_png[28] = 125; m_png[29] = 134; m_png[30] = 135; m_png[31] = 144;
			m_hitPoint = 24;
			m_maxHitPoint = 24;
			m_minimumAtk = 1;
			m_maximumAtk = 4;
			m_attackSpeed = 1.0;
			m_runAnimation = 0.05f;
			m_attackAnimation = 0.1f;
			m_range = 20;
			m_speed = m_movementSpeed = m_velocity = MEDIUM_SPEED;
			m_armor = 0;
			m_gold = 6;
			break;
		}		
	}
	case MAGICAN_MONSTER:
	{
		rand = random(0, 1);
		if (rand == 0)
		{
			m_spriteNode = SpriteBatchNode::create("globin.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("globin.plist");

			m_sprite = Sprite::createWithSpriteFrameName("_globin_1.png");

			m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_globin.png");
			m_blood = Sprite::createWithSpriteFrameName("healthbar_globin.png");
			m_blood->setAnchorPoint(Point(0, 0.5));
			m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

			m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
			m_bloodBar->setScale(0.2);

			m_bloodBar->addChild(m_blood, 8);
			m_sprite->addChild(m_bloodBar, 6);
			m_spriteNode->addChild(m_sprite);
			m_sprite->setVisible(false);
			m_fomatAnimation = "_globin_";
			m_png[0] = 1; m_png[1] = 16; m_png[2] = 17; m_png[3] = 32; m_png[4] = 33; m_png[5] = 48; m_png[6] = 49; m_png[7] = 64; m_png[8] = 65; m_png[9] = 80; m_png[10] = 81; m_png[11] = 96; m_png[12] = 97; m_png[13] = 112; m_png[14] = 113; m_png[15] = 128;
			m_png[16] = 129; m_png[17] = 136; m_png[18] = 137; m_png[19] = 144; m_png[20] = 145; m_png[21] = 152; m_png[22] = 153; m_png[23] = 160; m_png[24] = 161; m_png[25] = 168; m_png[26] = 169; m_png[27] = 176; m_png[28] = 177; m_png[29] = 184; m_png[30] = 185; m_png[31] = 192;

			m_hitPoint = 120;
			m_maxHitPoint = 120;
			m_minimumAtk = 5;
			m_maximumAtk = 7;
			m_attackSpeed = 1.0;
			m_runAnimation = 0.07f;
			m_attackAnimation = 0.1f;
			m_speed = m_movementSpeed = m_velocity = MEDIUM_SPEED;
			m_armor = 0;
			m_gold = 15;
			break;
		}
		else 
		{
			m_spriteNode = SpriteBatchNode::create("zombie.png");
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("zombie.plist");

			m_sprite = Sprite::createWithSpriteFrameName("_zombie_1.png");

			m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_zombie.png");
			m_blood = Sprite::createWithSpriteFrameName("healthbar_zombie.png");
			m_blood->setAnchorPoint(Point(0, 0.5));
			m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

			m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
			m_bloodBar->setScale(0.2);

			m_bloodBar->addChild(m_blood, 8);
			m_sprite->addChild(m_bloodBar, 6);
			m_spriteNode->addChild(m_sprite);
			m_sprite->setVisible(false);
			m_fomatAnimation = "_zombie_";
			m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
			m_png[16] = 65; m_png[17] = 74; m_png[18] = 75; m_png[19] = 84; m_png[20] = 85; m_png[21] = 94; m_png[22] = 95; m_png[23] = 104; m_png[24] = 105; m_png[25] = 114; m_png[26] = 115; m_png[27] = 124; m_png[28] = 125; m_png[29] = 134; m_png[30] = 135; m_png[31] = 144;

			m_hitPoint = 120;
			m_maxHitPoint = 120;
			m_minimumAtk = 5;
			m_maximumAtk = 7;
			m_attackSpeed = 1.0;
			m_runAnimation = 0.07f;
			m_attackAnimation = 0.1f;
			m_speed = m_movementSpeed = m_velocity = MEDIUM_SPEED;
			m_armor = 0;
			m_gold = 15;
			break;
		}
		
	}		
	case TANK_MONSTER:
	{
		m_spriteNode = SpriteBatchNode::create("minotaur.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("minotaur.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_minotaur_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_minotaur.png");
		m_blood = Sprite::createWithSpriteFrameName("healthbar_minotaur.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_minotaur_";
		m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
		m_png[16] = 65; m_png[17] = 69; m_png[18] = 70; m_png[19] = 74; m_png[20] = 75; m_png[21] = 79; m_png[22] = 80; m_png[23] = 84; m_png[24] = 85; m_png[25] = 89; m_png[26] = 90; m_png[27] = 94; m_png[28] = 95; m_png[29] = 99; m_png[30] = 100; m_png[31] = 104;
		m_sprite->setScale(1.3);
		m_hitPoint = 960;
		m_maxHitPoint = 960;
		m_minimumAtk = 40;
		m_maximumAtk = 60;
		m_attackSpeed = 1.9;
		m_runAnimation = 0.04f;
		m_attackAnimation = 0.1f;
		m_speed = m_movementSpeed = m_velocity = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 40;
		break;
	}		
	case SPEED_MONSTER:		
	{
		m_spriteNode = SpriteBatchNode::create("ant.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ant.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_ant_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_ant.png");
		m_blood = Sprite::createWithSpriteFrameName("healthbar_ant.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.6));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_ant_";
		m_png[0] = 1; m_png[1] = 12; m_png[2] = 13; m_png[3] = 24; m_png[4] = 25; m_png[5] = 36; m_png[6] = 37; m_png[7] = 48; m_png[8] = 49; m_png[9] = 60; m_png[10] = 61; m_png[11] = 72; m_png[12] = 73; m_png[13] = 84; m_png[14] = 85; m_png[15] = 96;
		m_png[16] = 97; m_png[17] = 103; m_png[18] = 104; m_png[19] = 110; m_png[20] = 111; m_png[21] = 117; m_png[22] = 118; m_png[23] = 124; m_png[24] = 125; m_png[25] = 131; m_png[26] = 132; m_png[27] = 138; m_png[28] = 139; m_png[29] = 145; m_png[30] = 146; m_png[31] = 152;

		m_hitPoint = 42;
		m_maxHitPoint = 42;
		m_minimumAtk = 2;
		m_maximumAtk = 3;
		m_attackSpeed = 1.2;
		m_runAnimation = 0.03f;
		m_attackAnimation = 0.1f;
		m_speed = m_movementSpeed = m_velocity = FAST_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	}
		
	case SIEGE_MONSTER:
	{
		m_spriteNode = SpriteBatchNode::create("dragon.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("dragon.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_dragon_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_dragon.png");
		m_blood = Sprite::createWithSpriteFrameName("healthbar_dragon.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_dragon_";
		m_png[0] = 1; m_png[1] = 16; m_png[2] = 17; m_png[3] = 32; m_png[4] = 33; m_png[5] = 48; m_png[6] = 49; m_png[7] = 64; m_png[8] = 65; m_png[9] = 80; m_png[10] = 81; m_png[11] = 96; m_png[12] = 97; m_png[13] = 112; m_png[14] = 113; m_png[15] = 128;
		m_png[16] = 129; m_png[17] = 136; m_png[18] = 137; m_png[19] = 144; m_png[20] = 145; m_png[21] = 152; m_png[22] = 153; m_png[23] = 160; m_png[24] = 161; m_png[25] = 168; m_png[26] = 169; m_png[27] = 176; m_png[28] = 177; m_png[29] = 184; m_png[30] = 185; m_png[31] = 192;
		m_hitPoint = 58;
		m_minimumAtk = 3;
		m_maximumAtk = 8;
		m_attackSpeed = 1.0;
		m_runAnimation = 0.07f;
		m_attackAnimation = 0.1f;
		m_speed = m_movementSpeed = m_velocity = MEDIUM_SPEED;
		m_armor = 0;
		m_gold = 15;
		break;
	}
		
	case ELITE_MONSTER:
	{
		m_spriteNode = SpriteBatchNode::create("troll.png");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("troll.plist");

		m_sprite = Sprite::createWithSpriteFrameName("_troll_1.png");

		m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_troll.png");
		m_blood = Sprite::createWithSpriteFrameName("healthbar_troll.png");
		m_blood->setAnchorPoint(Point(0, 0.5));
		m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

		m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 1.05));
		m_bloodBar->setScale(0.2);

		m_bloodBar->addChild(m_blood, 8);
		m_sprite->addChild(m_bloodBar, 6);
		m_spriteNode->addChild(m_sprite);
		m_sprite->setVisible(false);
		m_fomatAnimation = "_troll_";
		m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
		m_png[16] = 65; m_png[17] = 73; m_png[18] = 74; m_png[19] = 82; m_png[20] = 83; m_png[21] = 91; m_png[22] = 92; m_png[23] = 100; m_png[24] = 101; m_png[25] = 109; m_png[26] = 110; m_png[27] = 118; m_png[28] = 119; m_png[29] = 127; m_png[30] = 128; m_png[31] = 136;
		m_hitPoint = 12000;
		m_minimumAtk = 150;
		m_maximumAtk = 250;
		m_attackSpeed = 2.5;
		m_runAnimation = 0.05f;
		m_attackAnimation = 0.1f;
		m_speed = m_movementSpeed = m_velocity = SLOW_SPEED;
		//sm_armor = 0;
		m_gold = 100;
		break;
	}	
	case DARKLORD:
		m_sprite = ResourceManager::GetInstance()->DuplicateSprite(ResourceManager::GetInstance()->GetSpriteById(DARKLORD)); //id = id of MAGICAN_MONSTER
		m_hitPoint = 21600;
		m_minimumAtk = 200;
		m_maximumAtk = 400;
		m_attackSpeed = 2.0;
		m_speed = m_movementSpeed = m_velocity = SLOW_SPEED;
		//m_armor = 0;
		m_gold = 500;
		break;
	default:
		break;
	}
}
float timeCount = 0.5;
float timeMove = 0;

void Monster::Update(float deltaTime)
{
	if (timeCount >= (1.0 + (random(0, 10) / 10 * 1.0)))
	{
		m_sprite->setVisible(true);
		timeCount = 0;
	}
	else {
		timeCount += deltaTime;
	}
}


void Monster::Move(Vec2 point, bool check, float timedelay, float delay)
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

void Monster::Action(int direction, bool check)
{
	switch (direction)
	{
	case E:
	{
		auto walkingE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[8], m_png[9], 0.05f));
		walkingE->retain();
		auto AttackE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[24], m_png[25], m_attackAnimation));
		AttackE->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingE)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackE)->clone());
		}
		break;
	}

	case W:
	{
		
		auto walkingW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[0], m_png[1], m_runAnimation));
		walkingW->retain();
		auto AttackW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[16], m_png[17], m_attackAnimation));
		AttackW->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingW)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackW)->clone());
		}
		break;
	}

	case S:
	{
		auto walkingS = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[12], m_png[13], m_runAnimation));
		walkingS->retain();
		auto AttackS = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[28], m_png[29], m_attackAnimation));
		AttackS->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingS)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackS)->clone());
		}
		break;
	}

	case N:
	{
		auto walkingN = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[4], m_png[5], m_runAnimation));
		walkingN->retain();
		auto AttackN = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[20], m_png[21], m_attackAnimation));
		AttackN->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingN)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackN)->clone());
		}
		break;
	}

	case SE:
	{
		auto walkingSE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[10], m_png[11], m_runAnimation));
		walkingSE->retain();
		auto AttackSE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[26], m_png[27], m_attackAnimation));
		AttackSE->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingSE)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackSE)->clone());
		}
		break;
	}

	case SW:
	{
		auto walkingSW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[14], m_png[15], m_runAnimation));
		walkingSW->retain();
		auto AttackSW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[30], m_png[31], m_attackAnimation));
		AttackSW->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingSW)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackSW)->clone());
		}
		break;
	}
    case NE: 
      {
        auto walkingNE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[6], m_png[7], m_runAnimation));
		walkingNE->retain();
		auto AttackNE = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[22], m_png[23], m_attackAnimation));
		AttackNE->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingNE)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackNE)->clone());
		}
		break;
      }
    case NW:
      {
        auto walkingNW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[2], m_png[3], m_runAnimation));
		walkingNW->retain();
		auto AttackNW = Animate::create(Monster::AnimationMonster(m_fomatAnimation, m_png[18], m_png[19], m_attackAnimation));
		AttackNW->retain();
		if (!check)
		{
			m_movementSpeed = m_speed;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(walkingNW)->clone());
		}
		else
		{
			m_movementSpeed = m_speed / 10000;
			m_sprite->stopAllActions();
			m_sprite->runAction(RepeatForever::create(AttackNW)->clone());
		}
		break;
      }
}
}

void Monster::AttackCrystal(Crystal *crystal, float deltaTime)
{
	if (countToAttack >= m_attackSpeed)
	{
		auto damage = GetDamage();
		if (crystal->getHitPoint() > 0)
		{
			crystal->setHitPoint(crystal->getHitPoint() - damage);
		}
		auto damageLabel = Label::createWithTTF("" + to_string(random(1, 10)), "fonts/Comic_Book.ttf", 20);
		if (damage > 50)
		{
			damageLabel->setString(to_string(damage) + "!");
			damageLabel->setColor(Color3B::RED);
		}
		else
		{
			damageLabel->setString("-" + to_string(damage));
			damageLabel->setColor(Color3B::YELLOW);
		}
		damageLabel->setPosition(Vec2(crystal->getSprite()->getContentSize().width / 2, crystal->getSprite()->getContentSize().height / 2));
		damageLabel->runAction(FadeOut::create(0.4));
		damageLabel->runAction(Sequence::create(MoveBy::create(0.4, Vec2(0, 10)), RemoveSelf::create(), nullptr));	
		crystal->getSprite()->addChild(damageLabel);
		countToAttack = 0;

	}
	else
	{
		countToAttack += deltaTime;
	}
}

void Monster::DoDead()
{
	auto seq = Sequence::create(DelayTime::create(0.3f), FadeOut::create(0), RemoveSelf::create(), nullptr);
	dead1 = Sprite::create("dead.png");
	dead1->setScale(0.6);
	dead1->setPosition(m_sprite->getPosition());
	layer->addChild(dead1, 3);
	dead1->runAction(MoveBy::create(0.3f, Vec2(0, 10)));
	dead1->runAction(seq);
}

void Monster::SetType(int type)
{
	m_type = type;
}

void Monster::SetMovementSpeed(float movementSpeed)
{
	m_movementSpeed = movementSpeed;
}

void Monster::SetMSpeed(float mSpeed)
{
	m_speed = mSpeed;
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

bool Monster::GetIsSlow()
{
	return isSlow;
}

void Monster::SetSlowRunSpeed()
{
	if (m_movementSpeed > speed)
	{
		m_movementSpeed -= m_speed * 20 / 100;
		m_sprite->setColor(Color3B::BLUE);
		log("movement speed:%f", m_movementSpeed);
	}
}

void Monster::SetIsSlow(bool isSlow)
{
	this->isSlow = isSlow;
}

float Monster::GetMSpeed()
{
	return m_speed;
}

int Monster::GetDamage()
{
	return random(m_minimumAtk, m_maximumAtk);
}

int Monster::GetMaxHitPoint()
{
	return m_maxHitPoint;
}

void Monster::ReduceHitPointMonster(int damage)
{
	m_hitPoint -= damage;
}

bool Monster::IsDead()
{
	if (m_hitPoint > 0)
	{
		return false;
	}
	else
		return true;
}

