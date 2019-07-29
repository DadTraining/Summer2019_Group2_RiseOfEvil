#include "Crystal.h"
#include "Player.h"
Crystal::Crystal(Layer * layer)
{
	Init();
	layer->addChild(m_sprite, 3);
}

Crystal::~Crystal()
{
}

void Crystal::Init()
{
	m_sprite = Sprite::create("crystalBoss.png");
	m_hitpoint = Player::GetInstance()->GetCurrentLife();
	m_maxHitpoint = m_hitpoint;
	
	hpBgSprite = Sprite::create("res/WorldScene1/loadingbar_bg.png");
	hpBgSprite->setPosition(Point(m_sprite->getContentSize().width / 2 + 5, m_sprite->getContentSize().height + 10));
	hitpointpercentLabel = Label::createWithTTF("100%", "fonts/Comic_Book.ttf", 12);
	hitpointpercentLabel->setPosition(Point(m_sprite->getContentSize().width / 2 + 10, m_sprite->getContentSize().height + 10));
	m_sprite->addChild(hpBgSprite);
	m_sprite->addChild(hitpointpercentLabel,1);
	hpBar = CCProgressTimer::create(Sprite::create("res/WorldScene1/loadingbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(100);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
	hpBgSprite->setScale(0.05);

	//make crystal fire
	fire = ParticleFire::create();
	fire->setPosition(Vec2(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2));
	fire->setVisible(false);
	m_sprite->addChild(fire);
}

void Crystal::setPercentOfHealthBar()
{
	crystalBurst = false;
	hitpointpercentLabel->setString(to_string((int)(m_hitpoint / (m_maxHitpoint * 1.0) * 100)) + "%");
	hpBar->setPercentage((m_hitpoint / (m_maxHitpoint * 1.0) * 100));
	if (hpBar->getPercentage() < 0)
	{
		hpBar->setPercentage(0);
	}
	//make crystal fire
	if (hpBar->getPercentage() < 60 && hpBar->getPercentage() > 40)
	{
		hitpointpercentLabel->setColor(Color3B::ORANGE);
		if (10 / hpBar->getPercentage() <= 1)
		{
			fire->setScale(10 / hpBar->getPercentage());
		}
		fire->setVisible(true);
	}
	if (hpBar->getPercentage() < 30)
	{
		hitpointpercentLabel->setColor(Color3B::RED);
	}
	if (hpBar->getPercentage() == 0)
	{
		count++;
		if (count <= 2)
		{
			auto burst = ParticleSystemQuad::create("explotion.plist");
			burst->setScale(3);
			burst->setDuration(0.4);
			burst->setPosition(Vec2(m_sprite->getContentSize().width / 2, m_sprite->getContentSize().height / 2));
			burst->setAutoRemoveOnFinish(true);
			m_sprite->addChild(burst);
			fire->setVisible(false);
		}
		if (count == 2)
		{
			checkLose = true;
		}
		crystalBurst = true;
	}
}

int Crystal::getHitPoint()
{
	return m_hitpoint;
}

void Crystal::setHitPoint(int hitPoint)
{
	m_hitpoint = hitPoint;
}

bool Crystal::getcrystalBurst()
{
	return crystalBurst;
}

bool Crystal::getCheckLose()
{
	return checkLose;
}

int Crystal::getmaxHitPoint()
{
	return m_maxHitpoint;
}

Sprite * Crystal::getSprite()
{
	return m_sprite;
}

