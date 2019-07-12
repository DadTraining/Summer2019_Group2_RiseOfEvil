#include "WorldScene1.h"
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

Scene* WorldScene1::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = WorldScene1::create();
	scene->addChild(layer);
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return scene;
}
bool WorldScene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mTileMap = TMXTiledMap::create("res/MapScene/Map01.tmx");
	mTileMap->setAnchorPoint(Vec2(0, 0));
	mTileMap->setPosition(0, 0);
	addChild(mTileMap, 0);

	pause_bg = Sprite::create("res/WorldScene1/pause_bg.png");
	pause_bg->setScale(0.7);
	pause_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(pause_bg, -1);

	auto pauseBtn = ui::Button::create("res/Buttons/WorldScene1/pauseBtn.png");
	pauseBtn->setScale(0.2);
	pauseBtn->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	pauseBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPause, this));
	addChild(pauseBtn, 1);

	resumeBtn = ui::Button::create("res/Buttons/WorldScene1/resumeBtn.png");
	resumeBtn->setScaleX(1.4);
	resumeBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	resumeBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeinPause, this));
	addChild(resumeBtn, -1);

	restartBtn = ui::Button::create("res/Buttons/WorldScene1/restartBtn.png");
	restartBtn->setScaleX(1.4);
	restartBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 20));
	//restartBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPasue, this));
	addChild(restartBtn, -1);

	mainmenuBtn = ui::Button::create("res/Buttons/WorldScene1/mainmenuBtn.png");
	mainmenuBtn->setScaleX(1.4);
	mainmenuBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 90));
	//mainmenuBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPasue, this));
	addChild(mainmenuBtn, -1);

	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	auto obj = mTileMap->getObjectGroup("Monster");
	float x = obj->getObject("monster")["x"].asInt();
	float y = obj->getObject("monster")["y"].asInt();
	for (int i = 0; i < listMonster.size(); i++)
	{
		listMonster[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
		listMonster[i]->GetSprite()->setPosition(x, y);
		listMonster[i]->GetSprite()->setScale(0.6);
	}
	auto road = mTileMap->getObjectGroup("Point");
	tower = new Tower(this);
	auto body = PhysicsBody::createCircle(150, PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	tower->GetSprite()->setPhysicsBody(body);
	//===========================================================================
	for (int i = 0; i < 15; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	time = 0;
	scheduleUpdate();
	return true;
}
float x;
float y;
void WorldScene1::update(float deltaTime)
{

	for (int i = 0; i < listMonster.size(); i++)
	{
		x = listMonster[i]->GetSprite()->getPositionX();
		y = listMonster[i]->GetSprite()->getPositionY();
		if (tower->Update(deltaTime, x, y) == 1)
		{
			//monster->setVisible(false);
			//monster->removeFromParent();
			//monster->release();
		}
		if (time >= 0.5)
		{
			if (listPoint[listMonster[i]->m_flag].getDistance(listMonster[i]->GetSprite()->getPosition()) == 0)
				{
			
					if (listMonster[i]->m_flag < listPoint.size() - 1)
						{
							listMonster[i]->m_flag++;
							
						}

					listMonster[i]->Move(listPoint[listMonster[i]->m_flag]);
				}
			log("Monster %d x: %f, y: %f", i, listMonster[i]->GetSprite()->getPositionX(), listMonster[i]->GetSprite()->getPositionY());
			time = 0;
		}
		else {
			time += deltaTime;
		}

	}
}


void WorldScene1::FadeinPause()
{
	pause_bg->setZOrder(-1);
	restartBtn->setZOrder(-1);
	resumeBtn->setZOrder(-1);
	mainmenuBtn->setZOrder(-1);
}

void WorldScene1::FadeoutPause()
{
	pause_bg->setZOrder(10);
	restartBtn->setZOrder(12);
	resumeBtn->setZOrder(11);
	mainmenuBtn->setZOrder(13);
}



