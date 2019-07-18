#include "WorldScene1.h"
#include "MainMenuScene.h"
#include "Wave.h"
#include <iostream>
#include <string.h>
#include <math.h>
#include "ResourceManager.h"
#include "Player.h"
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
	//Create function for icon build tower
	archerIcon = MenuItemImage::create("res/WorldScene1/archerTower.png", "res/WorldScene1/archerTower.png", [&](Ref* sender) {
		GetTowerDetails(1);
	});
	archerIcon->setPosition(0, 0);
	magicIcon = MenuItemImage::create("res/WorldScene1/magicTower.png", "res/WorldScene1/magicTower.png", [&](Ref* sender) {
		GetTowerDetails(2);
	});
	magicIcon->setPosition(0, 0);

	barrackIcon = MenuItemImage::create("res/WorldScene1/barrackTower.png", "res/WorldScene1/barrackTower.png", [&](Ref* sender) {
		GetTowerDetails(3);
	});
	barrackIcon->setPosition(0, 0);

	slowIcon = MenuItemImage::create("res/WorldScene1/slowTower.png", "res/WorldScene1/slowTower.png", [&](Ref* sender) {
		GetTowerDetails(4);
	});
	slowIcon->setPosition(0, 0);

	boombardIcon = MenuItemImage::create("res/WorldScene1/boombardTower.png", "res/WorldScene1/boombardTower.png", [&](Ref* sender) {
		GetTowerDetails(5);
	});
	boombardIcon->setPosition(0, 0);
	cancelMenu = MenuItemImage::create("res/WorldScene1/boombardTower.png", "res/WorldScene1/boombardTower.png", [&](Ref* sender) {
		menu->setVisible(false);
	});
	//==================================================================
	//Create tower details table
	towerArcherDetails = Sprite::create("res/WorldScene1/DetailsArcherTower.png");
	towerArcherDetails->setVisible(false);
	towerArcherDetails->setAnchorPoint(Vec2(0.5, 0));
	addChild(towerArcherDetails, 9);

	towerMagicDetails = Sprite::create("res/WorldScene1/DetailsMagicTower.png");
	towerMagicDetails->setVisible(false);
	towerMagicDetails->setAnchorPoint(Vec2(0.5, 0));
	addChild(towerMagicDetails, 9);

	towerSlowDetails = Sprite::create("res/WorldScene1/DetailsSlowTower.png");
	towerSlowDetails->setVisible(false);
	towerSlowDetails->setAnchorPoint(Vec2(0.5, 0));
	addChild(towerSlowDetails, 9);

	towerBoombardDetails = Sprite::create("res/WorldScene1/DetailsBoombardTower.png");
	towerBoombardDetails->setVisible(false);
	towerBoombardDetails->setAnchorPoint(Vec2(0.5, 0));
	addChild(towerBoombardDetails, 9);

	towerBarrackDetails = Sprite::create("res/WorldScene1/DetailsBrrackTower.png");
	towerBarrackDetails->setVisible(false);
	towerBarrackDetails->setAnchorPoint(Vec2(0.5, 0));
	addChild(towerBarrackDetails, 9);
  //==================================================================
	//Create list tower icon to build
	menu = Menu::create(archerIcon, magicIcon, slowIcon, boombardIcon, barrackIcon, cancelMenu, nullptr);
	menu->setPosition(0, 0);
	addChild(menu, 100);
	menu->setVisible(false);
	//==================================================================
	canBuild = Sprite::create("canbuild.png");
	canBuild->removeFromParent();
	canBuild->setPosition(0, 0);
	this->addChild(canBuild, 2);
	canBuild->setVisible(false);

	cannotBuild = Sprite::create("cantbuild.png");
	cannotBuild->removeFromParent();
	cannotBuild->setPosition(0, 0);
	this->addChild(cannotBuild, 2);
	cannotBuild->setVisible(false);
	//==================================================================
	mTileMap = TMXTiledMap::create("res/MapScene/Map01.tmx");
	mTileMap->setAnchorPoint(Vec2(0, 0));
	mTileMap->setPosition(0, 0);
	addChild(mTileMap, 0);
	//==========================================================
	//Create pause menu 
	pause_bg = Sprite::create("res/WorldScene1/pause_bg.png");
	pause_bg->setScale(0.7);
	pause_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(pause_bg, -1);

	auto pauseBtn = ui::Button::create("res/Buttons/WorldScene1/pauseBtn-press.png", "res/Buttons/WorldScene1/pauseBtn.png");
	//pauseBtn->setScale(0.2);
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
	//==========================================================
	//Create list monster
	Wave *wave = new Wave();
	vector<int> temp1 = wave->getWave(1);
	for (int i = 0; i < temp1.size(); i++)
	{
		Wave1.push_back(new Monster(this, temp1[i]));
	}
	listMonster = Wave1;
	//===========================================================================
	//First Location Tower
	listLocationTower.push_back(Vec2(0, 0));
	//===========================================================================
	//Monster appear
	auto obj = mTileMap->getObjectGroup("Monster");
	float x = obj->getObject("monster")["x"].asInt();
	float y = obj->getObject("monster")["y"].asInt();
	for (int i = 0; i < listMonster.size(); i++)
	{
		listMonster[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
		listMonster[i]->GetSprite()->setPosition(x, y);
		listMonster[i]->GetSprite()->setScale(0.6);
	}	
	
	listTower.push_back(new Tower(this, 1, touchLocation));
	//===========================================================================
	//List point to move monster
	auto road = mTileMap->getObjectGroup("Point");
	for (int i = 0; i < 15; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	//=====================================================
	//Create gold frame
	auto goldFrame = Sprite::create("goldFrame.png");
	goldFrame->setAnchorPoint(Vec2(0, 1));
	goldFrame->setPosition(10, visibleSize.height - 10);
	addChild(goldFrame, 0);
	//=====================================================
	//Create gold label
	goldLabel = ResourceManager::GetInstance()->GetLabelById(2);
	goldLabel->setPosition(goldFrame->getContentSize().width / 2 + 25, goldFrame->getContentSize().height / 2);
	goldLabel->setAnchorPoint(Vec2(0.5, 0.5));
	goldLabel->removeFromParent();
	goldFrame->addChild(goldLabel);
	//=====================================================
	//=====================================================
	//Touch event
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene1::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene1::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene1::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	menu->setScale(0.6f);
	time = 0;
	scheduleUpdate();
	return true;
}
void WorldScene1::update(float deltaTime)
{
	//Set Gold to Label
	goldLabel->setString(to_string(Player::GetInstance()->GetCurrentGold()));
	//Monster spawn
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (!(listMonster[i]->GetSprite()->isVisible()))
		{
			listMonster[i]->Update(deltaTime);
			i = 100;
		}
	}
	//Monster move
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
	//Tower shoot
	for (int tower = 0; tower < listTower.size(); tower++)
	{
		for (int i = 0; i < listMonster.size(); i++)
		{
			if (listMonster[i]->GetSprite()->isVisible() &&
				listMonster[i]->GetSprite()->getPosition().getDistance(listTower[tower]->GetSprite()->getPosition()) < listTower[tower]->GetRange())
			{
				listTower[tower]->Update(deltaTime, listMonster[i]);
				i = 100;
			}
		}
	}
	//Monster die
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (listMonster[i]->GetHitPoint() <= 0)
		{
			listMonster[i]->DoDead();
			listMonster[i]->GetSprite()->setVisible(false);
			Player::GetInstance()->SetGold(listMonster[i]->GetGold());
			listMonster.erase(listMonster.begin() + i);
		}
	}
}

//Hide Pause menu
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

//Show Pause menu
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

//Build Tower
void WorldScene1::BuildTower(Ref* ref, int type)
{
	Tower * towerBuild = new Tower(this, type, touchLocation);
	Player::GetInstance()->SetGold(Player::GetInstance()->GetCurrentGold() - towerBuild->GetGold());
	listLocationTower.push_back(touchLocation);
	listTower.push_back(towerBuild);
	menu->setVisible(false);
	canBuild->setVisible(false);
	towerArcherDetails->setVisible(false);
	towerMagicDetails->setVisible(false);
	towerSlowDetails->setVisible(false);
	towerBoombardDetails->setVisible(false);
	towerBarrackDetails->setVisible(false);
}

void WorldScene1::moveFlag(Vec2 Pos)
{
}

bool WorldScene1::onTouchBegan(Touch * touch, Event * event)
{
	touchOut = false;
	touchIn = false;
	checkClick = false;
	
	for (int i = 0; i < listTower.size(); i++)
	{
		if (listTower[i]->GetSprite()->getBoundingBox().containsPoint(touch->getLocation()))
		{
			towerChoosing = listTower[i];
			touchOut = false;
			touchIn = true;
			checkClick = true;
		}
	}
	/*if (towerChoosing->GetFlagIcon()->getBoundingBox().containsPoint(touch->getLocation()))
	{
		log("oke");
	}*/
	if (checkClick == false && checkLocationBuildTower(touch->getLocation()))
	{	
		canBuild->setVisible(false);
		canBuild->setPosition(touch->getLocation());
		auto listPosTower = mTileMap->getLayer("ListTower");
		Size sizeListTower = listPosTower->getLayerSize();
		for (int i = 0; i < sizeListTower.width; i++)
		{
			for (int j = 0; j < sizeListTower.height; j++)
			{
				auto TowerSet = listPosTower->getTileAt(Vec2(i, j));
				if (TowerSet != NULL  && TowerSet->getBoundingBox().containsPoint(touch->getLocation()))
				{
					touchOut = true;
					touchIn = false;
					touchLocation = touch->getLocation();	
					createmenu(touch->getLocation());
				}
			}
		}
	}
	else 
	{
		cannotBuild->setPosition(touch->getLocation());
		cannotBuild->setVisible(true);
		canBuild->setVisible(false);
	}
	for (int i = 0; i < listTower.size(); i++)
	{
		if (listTower[i]->GetSprite()->getBoundingBox().containsPoint(touch->getLocation()))
		{
			listTower[i]->FadeInPause();
		}
		else
		{
			listTower[i]->FadeOutPause();
		}
	}

	if (touchOut == true && touchIn == false)
	{
		StatusMenu(true);
		createMenuTower(touchLocation, false);
	}
	if (touchOut == false && touchIn == true)
	{
		StatusMenu(false);
		createMenuTower(touchLocation, true);	
	}
	if (touchOut == false && touchIn == false)
	{
		StatusMenu(false);
		createMenuTower(touchLocation, false);
	}
//	checkTouchFlagIcon();
	return true;
}
//Check Location To Build
bool WorldScene1::checkLocationBuildTower(Vec2 newPoint)
{
	for (int i = 0; i < listLocationTower.size(); i++)
	{
		if (newPoint.getDistance(listLocationTower[i]) < 10)
		{
			return false;
		}
	}
	return true;
}


void WorldScene1::onTouchMoved(Touch * touch, Event * event)
{

}

void WorldScene1::onTouchEnded(Touch * touch, Event * event)
{
}

//Create list Tower icon 
void WorldScene1::createmenu(Vec2 point)
{
	archerIcon->setPosition(point);
	magicIcon->setPosition(point.x + magicIcon->getContentSize().width, point.y);
	slowIcon->setPosition(point.x + 2 * slowIcon->getContentSize().width, point.y);
	boombardIcon->setPosition(point.x + 3 * boombardIcon->getContentSize().width, point.y);
	barrackIcon->setPosition(point.x + 4 * barrackIcon->getContentSize().width, point.y);
	cancelMenu->setPosition(point.x + 5 * cancelMenu->getContentSize().width, point.y);
	if (!menu->isVisible())
	{
		menu->setVisible(true);
		canBuild->setVisible(true);
	}
}
void WorldScene1::StatusMenu(bool check)
{
	if (check == true)
	{
		menu->setVisible(true);
		canBuild->setVisible(true);
		cannotBuild->setVisible(false);
	}
	else if (check == false)
	{
		towerArcherDetails->setVisible(false);
		towerMagicDetails->setVisible(false);
		towerSlowDetails->setVisible(false);
		towerBoombardDetails->setVisible(false);
		towerBarrackDetails->setVisible(false);
		menu->setVisible(false);
		canBuild->setVisible(false);
		cannotBuild->setVisible(false);
	}
}

void WorldScene1::GetTowerDetails(int type)
{
	towerArcherDetails->setVisible(false);
	towerMagicDetails->setVisible(false);
	towerSlowDetails->setVisible(false);
	towerBoombardDetails->setVisible(false);
	towerBarrackDetails->setVisible(false);
	switch (type)
	{
	case 1:
		if (Player::GetInstance()->GetCurrentGold() >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 1));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_deactive.png");
			buyTower->setEnabled(false);
		}
		towerArcherDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerArcherDetails->getContentSize().width / 2 + 20, 30));
		towerArcherDetails->setPosition(Vec2(archerIcon->getPositionX(), archerIcon->getPositionY() + 40));
		towerArcherDetails->setVisible(true);
		break;
	case 2:
		if (Player::GetInstance()->GetCurrentGold() >= 100)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy100_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 2));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy100_deactive.png");
			buyTower->setEnabled(false);
		}
		towerMagicDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerMagicDetails->getContentSize().width / 2 + 20, 30));
		towerMagicDetails->setPosition(Vec2(archerIcon->getPosition().x, archerIcon->getPositionY() + 40));
		towerMagicDetails->setVisible(true);
		break;
	case 3:
		if (Player::GetInstance()->GetCurrentGold() >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 3));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_deactive.png");
			buyTower->setEnabled(false);
		}
		towerBarrackDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerBarrackDetails->getContentSize().width / 2 + 20, 30));
		towerBarrackDetails->setPosition(Vec2(archerIcon->getPosition().x, archerIcon->getPositionY() + 40));
		towerBarrackDetails->setVisible(true);
		break;
	case 4:
		if (Player::GetInstance()->GetCurrentGold() >= 80)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 4));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_deactive.png");
			buyTower->setEnabled(false);
		}
		towerSlowDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerSlowDetails->getContentSize().width / 2 + 20, 30));
		towerSlowDetails->setPosition(Vec2(archerIcon->getPosition().x, archerIcon->getPositionY() + 40));
		towerSlowDetails->setVisible(true);
		break;
	case 5: 
		if (Player::GetInstance()->GetCurrentGold() >= 125)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 5));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_deactive.png");
			buyTower->setEnabled(false);
		}
		towerBoombardDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerBoombardDetails->getContentSize().width / 2 + 20, 30));
		towerBoombardDetails->setPosition(Vec2(archerIcon->getPosition().x, archerIcon->getPositionY() + 40));
		towerBoombardDetails->setVisible(true);
		break;
	default:
		break;
	}
}

void WorldScene1::createMenuTower(Vec2 Point, bool check)
{
	//if (check == true)
	//{
	//	for (int i = 0; i < listTower.size(); i++)
	//	{
	//		listTower[i]->GetCircleMenu()->setVisible(false);
	//	}
	//	towerChoosing->GetCircleMenu()->setVisible(true);
	//	towerChoosing->GetCircleMenu()->runAction(ScaleTo::create(0.2f, 1));
	//}
	//else if(check == false)
	//	for (int i = 0; i < listTower.size(); i++)
	//	{
	//		listTower[i]->GetCircleMenu()->setVisible(false);
	//		listTower[i]->GetCircleMenu()->runAction(ScaleTo::create(0.2f, 0.1f));
	//	}
}
