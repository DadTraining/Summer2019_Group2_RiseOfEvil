#include "Soldier.h"

Soldier::Soldier(Layer * layer)
{
	Init();
	m_sprite->removeFromParent();
	layer->addChild(m_sprite, 5);
}

Soldier::~Soldier()
{
}

void Soldier::Init()
{
	m_spriteNode = SpriteBatchNode::create("soldier1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("soldier1.plist");

	m_sprite = Sprite::createWithSpriteFrameName("_soldier1_1.png");
	m_bloodBar = Sprite::createWithSpriteFrameName("healthbar_bg_soldier1.png");
	m_blood = Sprite::createWithSpriteFrameName("healthbar_soldier1.png");
	m_blood->setColor(Color3B(051,255,255));
	m_blood->setAnchorPoint(Point(0, 0.5));
	m_blood->setPosition(Point(0, m_bloodBar->getContentSize().height / 2));

	m_bloodBar->setPosition(Point(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height * 0.8));
	m_bloodBar->setScale(0.2);

	auto mBody = PhysicsBody::createBox(m_sprite->getContentSize() / 2);
	mBody->setDynamic(true);
	mBody->setGravityEnable(false);
	mBody->setRotationEnable(false);
	m_sprite->setScale(0.5);
	m_sprite->setPhysicsBody(mBody);

	m_bloodBar->addChild(m_blood, 8);
	m_sprite->addChild(m_bloodBar, 6);
	m_spriteNode->addChild(m_sprite);
	m_sprite->setVisible(false);
	m_fomatAnimation = "_soldier1_";
	m_png[0] = 1; m_png[1] = 8; m_png[2] = 9; m_png[3] = 16; m_png[4] = 17; m_png[5] = 24; m_png[6] = 25; m_png[7] = 32; m_png[8] = 33; m_png[9] = 40; m_png[10] = 41; m_png[11] = 48; m_png[12] = 49; m_png[13] = 56; m_png[14] = 57; m_png[15] = 64;
	m_png[16] = 65; m_png[17] = 71; m_png[18] = 72; m_png[19] = 78; m_png[20] = 79; m_png[21] = 85; m_png[22] = 86; m_png[23] = 92; m_png[24] = 93; m_png[25] = 99; m_png[26] = 100; m_png[27] = 106; m_png[28] = 107; m_png[29] = 113; m_png[30] = 114; m_png[31] = 120;
	m_png[32] = 121; m_png[33] = 124; m_png[34] = 125; m_png[35] = 128; m_png[36] = 129; m_png[37] = 132; m_png[38] = 133; m_png[39] = 136; m_png[40] = 137; m_png[41] = 140; m_png[42] = 141; m_png[43] = 144; m_png[44] = 145; m_png[45] = 148; m_png[46] = 149; m_png[47] = 152;
	m_hitPoint = 24;
	m_maxHitPoint = 24;
	m_minimumAtk = 1;
	m_maximumAtk = 4;
	m_attackSpeed = 1.0;
	m_runAnimation = 0.05f;
	m_attackAnimation = 0.1f;
	m_guardAnimation = 0.1f;
	m_range = 60;
	m_speed = m_movementSpeed = m_velocity = SOLDIERSPEED;
	m_armor = 0;
	m_gold = 6;
}

void Soldier::Update(float deltaTime)
{
}

void Soldier::Move(Vec2 point)
{
	
	if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x <= point.x)) 
	{
		Action(E);
	}
	else if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x >= point.x)) 
	{
		Action(W);
	}
	else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y >= point.y)) 
	{
		Action(S);
	}
	else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y <= point.y)) 
	{
		Action(N);
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y >= point.y)) 
	{
		Action(SE);
	}
	else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y >= point.y)) 
	{
		Action(SW);
	}
	else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y <= point.y)) 
	{
		Action(NE);
	}
	else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y <= point.y))
	{
		Action(NW);
	}
	auto moveTo = MoveTo::create(point.getDistance(m_sprite->getPosition()) / m_speed, Vec2(point.x, point.y));
	auto callbackHide = CallFunc::create(CC_CALLBACK_0(Soldier::SetTouchFlagTwo,this));
	auto callbackHide2 = CallFunc::create(CC_CALLBACK_0(Soldier::StopAction, this));
	auto sequen = Sequence::create(moveTo,  callbackHide, callbackHide2, NULL);
	m_sprite->runAction(sequen);

}
float timeRun = 0;
int count11 = 0;
void Soldier::MoveToMonster(Vec2 point, float timedelay)
{
	if (!touchFlag)
	{
		if (timeRun >= 0.4)
		{
			
			if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x <= point.x)) {
				ActionMove(E);
				
			}
			else if ((m_sprite->getPosition().y == point.y) && (m_sprite->getPosition().x >= point.x)) {
				ActionMove(W);
				
			}
			else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y >= point.y)) {
				ActionMove(S);
			}
			else if ((m_sprite->getPosition().x == point.x) && (m_sprite->getPosition().y <= point.y)) {
				ActionMove(N);
			}
			else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y >= point.y)) {
				ActionMove(SE);
			}
			else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y >= point.y)) {
				ActionMove(SW);
			}
			else if ((m_sprite->getPosition().x <= point.x) && (m_sprite->getPosition().y <= point.y)) {
				ActionMove(NE);
			} 
			else if ((m_sprite->getPosition().x >= point.x) && (m_sprite->getPosition().y <= point.y))
			{
				ActionMove(NW);
			}		
			;
			auto sequence = Sequence::create(MoveTo::create(point.getDistance(m_sprite->getPosition()) / m_movementSpeed, Vec2(point.x, point.y)),NULL);
			m_sprite->runAction(sequence);			
			timeRun = 0;
		}
		else
		{
			timeRun += timedelay;
		}
		
	}	
}
Animation * Soldier::AnimationMonster(string prefixName, int pFrameBegin, int pFrameEnd, float delay)
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

void Soldier::Action(int direction)
{
	switch (direction)
	{
	case E:
	{
		auto walkingE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[8], m_png[9], m_runAnimation));
		walkingE->retain();
		auto AttackE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[24], m_png[25], m_attackAnimation));
		AttackE->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingE)->clone());
		break;
	}

	case W:
	{

		auto walkingW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[0], m_png[1], m_runAnimation));
		walkingW->retain();
		auto AttackW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[16], m_png[17], m_attackAnimation));
		AttackW->retain();
	
		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingW)->clone());
		break;
	}

	case S:
	{
		auto walkingS = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[12], m_png[13], m_runAnimation));
		walkingS->retain();
		auto AttackS = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[28], m_png[29], m_attackAnimation));
		AttackS->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingS)->clone());
		break;
	}

	case N:
	{
		auto walkingN = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[4], m_png[5], m_runAnimation));
		walkingN->retain();
		auto AttackN = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[20], m_png[21], m_attackAnimation));
		AttackN->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingN)->clone());
		break;
	}

	case SE:
	{
		auto walkingSE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[10], m_png[11], m_runAnimation));
		walkingSE->retain();
		auto AttackSE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[26], m_png[27], m_attackAnimation));
		AttackSE->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingSE)->clone());
		break;
	}

	case SW:
	{
		auto walkingSW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[14], m_png[15], m_runAnimation));
		walkingSW->retain();
		auto AttackSW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[30], m_png[31], m_attackAnimation));
		AttackSW->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingSW)->clone());
		break;
	}
	case NE:
	{
		auto walkingNE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[6], m_png[7], m_runAnimation));
		walkingNE->retain();
		auto AttackNE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[22], m_png[23], m_attackAnimation));
		AttackNE->retain();
		
		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingNE)->clone());
		break;
	}
	case NW:
	{
		auto walkingNW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[2], m_png[3], m_runAnimation));
		walkingNW->retain();
		auto AttackNW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[18], m_png[19], m_attackAnimation));
		AttackNW->retain();

		m_sprite->stopAllActions();
		m_sprite->runAction(RepeatForever::create(walkingNW)->clone());	
		break;
	}
	}
}

void Soldier::ActionMove(int direction)
{
	switch (direction)
	{
	case E:
	{	
		auto walkingE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[8], m_png[9], 0.05f));
		walkingE->retain();
		auto AttackE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[24], m_png[25], m_attackAnimation));
		AttackE->retain();
		
		if (!checkAttack)
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

		auto walkingW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[0], m_png[1], m_runAnimation));
		walkingW->retain();
		auto AttackW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[16], m_png[17], m_attackAnimation));
		AttackW->retain();
		
		if (!checkAttack)
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
		auto walkingS = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[12], m_png[13], m_runAnimation));
		walkingS->retain();
		auto AttackS = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[28], m_png[29], m_attackAnimation));
		AttackS->retain();
		
		if (!checkAttack)
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
		auto walkingN = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[4], m_png[5], m_runAnimation));
		walkingN->retain();
		auto AttackN = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[20], m_png[21], m_attackAnimation));
		AttackN->retain();

		if (!checkAttack)
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
		auto walkingSE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[10], m_png[11], m_runAnimation));
		walkingSE->retain();
		auto AttackSE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[26], m_png[27], m_attackAnimation));
		AttackSE->retain();
		
		if (!checkAttack)
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
		auto walkingSW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[14], m_png[15], m_runAnimation));
		walkingSW->retain();
		auto AttackSW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[30], m_png[31], m_attackAnimation));
		AttackSW->retain();
		
		if (!checkAttack)
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
		auto walkingNE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[6], m_png[7], m_runAnimation));
		walkingNE->retain();
		auto AttackNE = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[22], m_png[23], m_attackAnimation));
		AttackNE->retain();
		
		if (!checkAttack)
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
		auto walkingNW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[2], m_png[3], m_runAnimation));
		walkingNW->retain();
		auto AttackNW = Animate::create(Soldier::AnimationMonster(m_fomatAnimation, m_png[18], m_png[19], m_attackAnimation));
		AttackNW->retain();
	
		if (!checkAttack)
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

bool Soldier::GetTouchFlag()
{
	return touchFlag;
}

void Soldier::StopAction()
{
	m_sprite->stopAllActions();
}

void Soldier::SetTouchFlag(bool touchFlag)
{
	this->touchFlag = touchFlag;
}

void Soldier::SetTouchFlagTwo()
{
	touchFlag = false;
}

void Soldier::SetCheckAttack(bool checkAttack)
{
	this->checkAttack = checkAttack;
}

int Soldier::GetRange()
{
	return m_range;
}

void Soldier::SetRange(int m_range)
{
	this->m_range = m_range;
}

float Soldier::GetMSpeed()
{
	return m_speed;
}

float Soldier::GetMovementSpeed()
{
  return m_movementSpeed;
}

void Soldier::SetMovementSpeed(float movement)
{
	m_movementSpeed = movement;
}

