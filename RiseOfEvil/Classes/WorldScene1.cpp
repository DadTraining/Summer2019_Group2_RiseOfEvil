#include "WorldScene1.h"
#include "MainMenuScene.h"
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

	//===============================================================
	archerIcon = MenuItemImage::create("res/WorldScene1/archerTower.png", "res/WorldScene1/archerTower.png", [&](Ref* sender) {
		//new Tower(this, 1, touchLocation);
		BuildTower(1, touchLocation);
	});
	archerIcon->setPosition(0, 0);

	magicIcon = MenuItemImage::create("res/WorldScene1/magicTower.png", "res/WorldScene1/magicTower.png", [&](Ref* sender) {
		BuildTower(2, touchLocation);
	});
	magicIcon->setPosition(0, 0);

	barrackIcon = MenuItemImage::create("res/WorldScene1/barrackTower.png", "res/WorldScene1/barrackTower.png", [&](Ref* sender) {
		BuildTower(3, touchLocation);
	});
	barrackIcon->setPosition(0, 0);

	slowIcon = MenuItemImage::create("res/WorldScene1/slowTower.png", "res/WorldScene1/slowTower.png", [&](Ref* sender) {
		BuildTower(4, touchLocation);
	});
	slowIcon->setPosition(0, 0);

	boombardIcon = MenuItemImage::create("res/WorldScene1/boombardTower.png", "res/WorldScene1/boombardTower.png", [&](Ref* sender) {
		BuildTower(5, touchLocation);
	});
	boombardIcon->setPosition(0, 0);

	menu = Menu::create(archerIcon, magicIcon, slowIcon, boombardIcon, barrackIcon, nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 100);
	menu->setVisible(false);
	//==================================================================

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
	pauseBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeInPause, this));
	addChild(pauseBtn, 1);

	resumeBtn = ui::Button::create("res/Buttons/WorldScene1/resumeBtn.png");
	resumeBtn->setScaleX(1.4);
	resumeBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	resumeBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeOutPause, this));
	resumeBtn->setEnabled(false);
	addChild(resumeBtn, -1);

	restartBtn = ui::Button::create("res/Buttons/WorldScene1/restartBtn.png");
	restartBtn->setScaleX(1.4);
	restartBtn->setEnabled(false);
	restartBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 20));
	//restartBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPasue, this));
	addChild(restartBtn, -1);

	mainmenuBtn = ui::Button::create("res/Buttons/WorldScene1/mainmenuBtn.png");
	mainmenuBtn->setScaleX(1.4);
	mainmenuBtn->setEnabled(false);
	mainmenuBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 90));
	mainmenuBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::returnToMainMenu, this));
	addChild(mainmenuBtn, -1);


	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
	listMonster.push_back(new Monster(this, NORMAL_MONSTER));
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
	new Tower(this, 1, touchLocation);
	//auto body = PhysicsBody::createCircle(150, PHYSICSBODY_MATERIAL_DEFAULT);
	//body->setDynamic(false);
	//tower->GetSprite()->setPhysicsBody(body);
	//===========================================================================
	for (int i = 0; i < 15; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	//touch event
	//=====================================================
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene1::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene1::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene1::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//=======================================================
	menu->setScale(0.6f);
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
		if (!(listMonster[i]->GetSprite()->isVisible()))
		{
			listMonster[i]->Update(deltaTime);
			i = 100;
		}
	}
	for (int i = 0; i < listMonster.size(); i++)

	{
		if ((listPoint[listMonster[i]->m_flag].getDistance(listMonster[i]->GetSprite()->getPosition()) == 0) && (listMonster[i]->GetSprite()->isVisible()))
		{
			
					if (listMonster[i]->m_flag < listPoint.size() - 1)
						{
							listMonster[i]->m_flag++;
							
						}

					listMonster[i]->Move(listPoint[listMonster[i]->m_flag]);
		}
	}
	for (int tower = 0; tower < listTower.size(); tower++)
	{

		for (int i = 0; i < listMonster.size(); i++)
		{

			if (listMonster[i]->GetSprite()->isVisible() &&
				listMonster[i]->GetSprite()->getPosition().getDistance(listTower[tower]->GetSprite()->getPosition()) < listTower[tower]->GetRange())
			{
				x = listMonster[i]->GetSprite()->getPositionX();
				y = listMonster[i]->GetSprite()->getPositionY();
				listTower[tower]->Update(deltaTime, listMonster[i]);
				i = 100;
			}
		}
	}
	
}

void WorldScene1::FadeOutPause()

{
	Director::getInstance()->resume();
	pause_bg->setZOrder(-1);
	restartBtn->setZOrder(-1);
	resumeBtn->setZOrder(-1);
	mainmenuBtn->setZOrder(-1);
	resumeBtn->setEnabled(false);
	restartBtn->setEnabled(false);
	mainmenuBtn->setEnabled(false);
}

void WorldScene1::FadeInPause()
{
	Director::getInstance()->pause();
	resumeBtn->setEnabled(true);
	restartBtn->setEnabled(true);
	mainmenuBtn->setEnabled(true);
	pause_bg->setZOrder(10);
	restartBtn->setZOrder(12);
	resumeBtn->setZOrder(11);
	mainmenuBtn->setZOrder(13);
}

void WorldScene1::returnToMainMenu()
{
	Director::getInstance()->getRunningScene()->pause();
	Director::getInstance()->replaceScene(TransitionZoomFlipAngular::create(1, MainMenuScene::createScene()));
}

void WorldScene1::BuildTower(int type, Vec2 Pos)
{
	Tower * towerBuild = new Tower(this, type, Pos);
	listTower.push_back(towerBuild);
	menu->setVisible(false);
}

bool WorldScene1::onTouchBegan(Touch * touch, Event * event)
{
	touchLocation = touch->getLocation();
	//====================Get Tileset List Tower=====================================
	auto listPosTower = mTileMap->getLayer("ListTower");
	Size sizeListTower = listPosTower->getLayerSize();
	log("width tilemaps: %f", sizeListTower.width);
	log("height tilemaps: %f", sizeListTower.height);
	for (int i = 0; i < sizeListTower.width; i++)
	{
		for (int j = 0; j < sizeListTower.height; j++)
		{
			auto TowerSet = listPosTower->getTileAt(Vec2(i, j));
			if (TowerSet != NULL  && TowerSet->getBoundingBox().containsPoint(touchLocation))
			{
		
				createmenu(touchLocation);
			}
		}
	}
	return true;
}

void WorldScene1::createmenu(Vec2 point)
{
	archerIcon->setPosition(point);
	magicIcon->setPosition(point.x + magicIcon->getContentSize().width, point.y);
	slowIcon->setPosition(point.x + 2 * slowIcon->getContentSize().width, point.y);
	boombardIcon->setPosition(point.x + 3 * boombardIcon->getContentSize().width, point.y);
	barrackIcon->setPosition(point.x + 4 * barrackIcon->getContentSize().width, point.y);
	if (!menu->isVisible())
	{
		menu->setVisible(true);
	}
	else
	{
		menu->setVisible(false);
	}
}



