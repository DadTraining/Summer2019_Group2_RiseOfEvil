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
	m_sprite->addChild(hitpointpercentLabel);
	hpBar = CCProgressTimer::create(Sprite::create("res/WorldScene1/loadingbar.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(100);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
	hpBgSprite->setScale(0.05);
}

void Crystal::setPercentOfHealthBar()
{
	hitpointpercentLabel->setString(to_string((int)(m_hitpoint / (m_maxHitpoint * 1.0) * 100)) + "%");
	hpBar->setPercentage((m_hitpoint / (m_maxHitpoint * 1.0) * 100));
}

int Crystal::getHitPoint()
{
	return m_hitpoint;
}

void Crystal::setHitPoint(int hitPoint)
{
	m_hitpoint = hitPoint;
}

Sprite * Crystal::getSprite()
{
	return m_sprite;
}

