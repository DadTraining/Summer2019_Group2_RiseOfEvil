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
		GetTowerDetails(5);
	});
	barrackIcon->setPosition(0, 0);

	slowIcon = MenuItemImage::create("res/WorldScene1/slowTower.png", "res/WorldScene1/slowTower.png", [&](Ref* sender) {
		GetTowerDetails(3);
	});
	slowIcon->setPosition(0, 0);

	boombardIcon = MenuItemImage::create("res/WorldScene1/boombardTower.png", "res/WorldScene1/boombardTower.png", [&](Ref* sender) {
		GetTowerDetails(4);
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
	addChild(menu, 100);
	menu->setVisible(false);
	//==================================================================
	canBuild = Sprite::create("canbuild.png");
	canBuild->removeFromParent();
	canBuild->setPosition(0, 0);
	canBuild->setScale(0.5);
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
	//Create start button 
	startBTN = ui::Button::create("res/Buttons/WorldScene1/startbtn.png", "res/Buttons/WorldScene1/startbtn-unactive.png");
	startBTN->setAnchorPoint(Vec2(1, 0));
	startBTN->setPosition(Vec2(visibleSize.width - 5, 5));
	startBTN->addClickEventListener(CC_CALLBACK_0(WorldScene1::startGame, this));
	startBTN->setScale(0.5);
	addChild(startBTN, 3);
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
	listTemp = listMonster;
	auto obj = mTileMap->getObjectGroup("Monster");
	float x = obj->getObject("monster")["x"].asInt();
	float y = obj->getObject("monster")["y"].asInt();
	float x2 = obj->getObject("monster2")["x"].asInt();
	float y2 = obj->getObject("monster2")["y"].asInt();
	for (int i = 0; i < listTemp.size(); i++)
	{
		if (i % 2 == 0)
		{
			listTemp[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
			listTemp[i]->GetSprite()->setPosition(x, y);
			listTemp[i]->GetSprite()->setScale(0.6);
		}
		else
		{
		//	//===================Gate2====================================
			listTemp[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
			listTemp[i]->GetSprite()->setPosition(x2, y2);
			listTemp[i]->GetSprite()->setScale(0.6);
		}
	}

	
	listTower.push_back(new Tower(this, 1, Vec2(-500,-500)));
	//===========================================================================
	//List point to move monster
	auto road = mTileMap->getObjectGroup("Point");
	for (int i = 0; i < 15; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	//List point 2 to move monster
	auto road2 = mTileMap->getObjectGroup("Point2");
	for (int i = 0; i < 8; i++)
	{
		float x = road2->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road2->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint2.push_back(Vec2(x, y));
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
	//Create label start game
	startLabel = ResourceManager::GetInstance()->GetLabelById(3);
	startLabel->setPosition(-6, startBTN->getContentSize().height / 2);
	startLabel->setAnchorPoint(Vec2(1, 0));
	startLabel->setString("Click here to start");
	startBTN->addChild(startLabel);
	//=====================================================
	//Touch event
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene1::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene1::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene1::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	menu->setScale(0.6f);
	menu->setAnchorPoint(Vec2(0,0));
	menu->setContentSize(Size(-77 * 2.5, 84));
	log("%f - %f ", menu->getContentSize().width, menu->getContentSize().height);
	time = 0;
	scheduleUpdate();
	return true;
}
void WorldScene1::update(float deltaTime)
{
	//Set Gold to Label
	goldLabel->setString(to_string(Player::GetInstance()->GetCurrentGold()));
	if (start)
	{
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
		for (int i = 0; i < listTemp.size(); i++)
		{
			if (i % 2 == 0)
			{
				if ((listPoint[listTemp[i]->m_flag].getDistance(listTemp[i]->GetSprite()->getPosition()) == 0) && (listTemp[i]->GetSprite()->isVisible()))
				{
					if (listTemp[i]->m_flag < listPoint.size() - 1)
					{
						listTemp[i]->m_flag++;
					}
					listTemp[i]->Move(listPoint[listTemp[i]->m_flag]);
				}
			}
			else
			{
				if ((listPoint2[listTemp[i]->m_flag].getDistance(listTemp[i]->GetSprite()->getPosition()) == 0) && (listTemp[i]->GetSprite()->isVisible()))
				{
					if (listTemp[i]->m_flag < listPoint2.size() - 1)
					{
						listTemp[i]->m_flag++;
					}
					listTemp[i]->Move(listPoint2[listTemp[i]->m_flag]);
				}
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
				Player::GetInstance()->SetGold(Player::GetInstance()->GetCurrentGold() + listMonster[i]->GetGold());
				listMonster.erase(listMonster.begin() + i);
			}
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
	Director::getInstance()->resume();
	Director::getInstance()->getRunningScene()->pause();
	Director::getInstance()->replaceScene(TransitionFade::create(1, MainMenuScene::createScene()));
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
					towerArcherDetails->setVisible(false);
					towerMagicDetails->setVisible(false);
					towerSlowDetails->setVisible(false);
					towerBoombardDetails->setVisible(false);
					towerBarrackDetails->setVisible(false);
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
	}
	if (touchOut == false && touchIn == true)
	{
		StatusMenu(false);
	}
	if (touchOut == false && touchIn == false)
	{
		StatusMenu(false);
	}
	return true;
}
//Check Location To Build
bool WorldScene1::checkLocationBuildTower(Vec2 newPoint)
{
	for (int i = 0; i < listLocationTower.size(); i++)
	{
		if (newPoint.getDistance(listLocationTower[i]) < 32)
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
	menu->setPosition(point);
	archerIcon->setPosition(menu->getContentSize().width, menu->getContentSize().height);
	magicIcon->setPosition(menu->getContentSize().width + magicIcon->getContentSize().width, menu->getContentSize().height);
	slowIcon->setPosition(menu->getContentSize().width + 2 * slowIcon->getContentSize().width, menu->getContentSize().height);
	boombardIcon->setPosition(menu->getContentSize().width + 3 * boombardIcon->getContentSize().width, menu->getContentSize().height);
	barrackIcon->setPosition(menu->getContentSize().width + 4 * barrackIcon->getContentSize().width, menu->getContentSize().height);
	cancelMenu->setPosition(menu->getContentSize().width + 5 * cancelMenu->getContentSize().width, menu->getContentSize().height);
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
		towerArcherDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 84));
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
		towerMagicDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 84));
		towerMagicDetails->setVisible(true);
		break;
	case 5:
		if (Player::GetInstance()->GetCurrentGold() >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 5));
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
		towerBarrackDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 84));
		towerBarrackDetails->setVisible(true);
		break;
	case 3:
		if (Player::GetInstance()->GetCurrentGold() >= 80)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 3));
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
		towerSlowDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 84));
		towerSlowDetails->setVisible(true);
		break;
	case 4: 
		if (Player::GetInstance()->GetCurrentGold() >= 125)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 4));
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
		towerBoombardDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 84));
		towerBoombardDetails->setVisible(true);
		break;
	default:
		break;
	}
}

void WorldScene1::startGame()
{
	start = true;
	startLabel->setVisible(false);
	startBTN->setEnabled(false);
}

