#include "WorldScene1.h"
#include "WorldMapScene.h"
#include "Popup.h"
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
	
	//==============================================================
	//use camera
	//cam = Camera::create();
	//addChild(cam, 100);

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
	cancelMenu = MenuItemImage::create("res/WorldScene1/closeMenu.png", "res/WorldScene1/closeMenu_press.png", [&](Ref* sender) {
		menu->setVisible(false);
		towerArcherDetails->setVisible(false);
		towerMagicDetails->setVisible(false);
		towerSlowDetails->setVisible(false);
		towerBoombardDetails->setVisible(false);
		towerBarrackDetails->setVisible(false);
	});
	cancelMenu->setAnchorPoint(Vec2(1, 0));
	cancelMenu->setScale(0.5);
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
	menu->setScale(0.8f);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setContentSize(Size(-77 * 2.5, 84));
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
	//================Flag==================================================
	Flag = Sprite::create("flag.png");
	Flag->setVisible(false);
	Flag->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(Flag,5);
	//==================================================================
	mTileMap = TMXTiledMap::create("res/MapScene/Map01.tmx");
	mTileMap->setAnchorPoint(Vec2(0, 0));
	mTileMap->setPosition(0, 0);
	addChild(mTileMap, 0);
	//==========================================================
	//Create pause menu 
	pause_bg = Sprite::create("res/WorldScene1/pause_bag.png");
	pause_bg->setAnchorPoint(Vec2(0.5, 0));

	//use camera
	//pause_bg->setPosition(Vec2(cam->getPosition().x, cam->getPosition().y + visibleSize.height/2));
	
	pause_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	addChild(pause_bg, 6);


	pauseBtn = ui::Button::create("res/Buttons/WorldScene1/pauseBtn.png", "res/Buttons/WorldScene1/pauseBtn-press.png");
	pauseBtn->setScale(0.7);
	pauseBtn->setPosition(Vec2(visibleSize.width - 20, visibleSize.height - 20));
	pauseBtn->addClickEventListener(CC_CALLBACK_0(WorldScene1::ClickPauseButton, this));
	addChild(pauseBtn, 1);

	resumeBtn = ui::Button::create("res/Buttons/WorldScene1/resumeButton.png");
	resumeBtn->setPosition(Vec2(pause_bg->getContentSize().width / 2, pause_bg->getContentSize().height / 2));
	resumeBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::ExitPauseMenu, this));
	resumeBtn->setScale(0.7);
	pause_bg->addChild(resumeBtn);
	log("%f - %f", resumeBtn->getPositionX(), resumeBtn->getPositionY());

	restartBtn = ui::Button::create("res/Buttons/WorldScene1/restartButton.png");
	restartBtn->setPosition(Vec2(pause_bg->getContentSize().width / 1.32, pause_bg->getContentSize().height / 2));
	restartBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::restart, this));
	restartBtn->setScale(0.7);
	pause_bg->addChild(restartBtn);

	muteBTN = ui::Button::create("res/Buttons/WorldScene1/muteButton.png");
	muteBTN->setPosition(Vec2(pause_bg->getContentSize().width / 4, pause_bg->getContentSize().height / 2));
	muteBTN->addTouchEventListener(CC_CALLBACK_0(WorldScene1::muteSound, this));
	muteBTN->setScale(0.7);
	pause_bg->addChild(muteBTN);

	worldMapBtn = ui::Button::create("res/Buttons/WorldScene1/worldMapBtn.png");
	worldMapBtn->setPosition(Vec2(pause_bg->getContentSize().width / 3, pause_bg->getContentSize().height / 4.5));
	worldMapBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::returnToMainMenu, this));
	worldMapBtn->setScaleX(0.7);
	pause_bg->addChild(worldMapBtn);

	auto exitBtn = ui::Button::create("res/Buttons/WorldScene1/Exit.png");
	exitBtn->setPosition(Vec2(pause_bg->getContentSize().width / 1.5, pause_bg->getContentSize().height / 4.5));
	exitBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::exit, this));
	exitBtn->setScaleX(0.7);
	pause_bg->addChild(exitBtn);
	//==========================================================
	//Create start button 
	startBTN = ui::Button::create("res/Buttons/WorldScene1/startbtn.png", "res/Buttons/WorldScene1/startbtn-unactive.png", "res/Buttons/WorldScene1/startbtn-unactive.png");
	startBTN->setAnchorPoint(Vec2(1, 0));
	startBTN->setPosition(Vec2(visibleSize.width - 5, 5));
	startBTN->addClickEventListener(CC_CALLBACK_0(WorldScene1::startWave, this));
	startBTN->setScale(0.5);
	addChild(startBTN, 3);
	//==========================================================
	//Create start wave button 
	auto obj = mTileMap->getObjectGroup("StartWaveBTNPosition");
	float x = obj->getObject("P1")["x"].asInt();
	float y = obj->getObject("P1")["y"].asInt();
	float x2 = obj->getObject("P2")["x"].asInt();
	float y2 = obj->getObject("P2")["y"].asInt();
	startWaveBTN = ui::Button::create("res/Buttons/WorldScene1/nextWaveBTN.png");
	startWaveBTN->setPosition(Vec2(x, y));
	startWaveBTN->setScale(0.5);
	startWaveBTN->addClickEventListener(CC_CALLBACK_0(WorldScene1::startWave, this));
	startWaveBTN->setVisible(false);
	addChild(startWaveBTN, 3);
	startWaveBTN2 = ui::Button::create("res/Buttons/WorldScene1/nextWaveBTN.png");
	startWaveBTN2->setPosition(Vec2(x2, y2));
	startWaveBTN2->setScale(0.5);
	startWaveBTN2->addClickEventListener(CC_CALLBACK_0(WorldScene1::startWave, this));
	startWaveBTN2->setVisible(false);
	addChild(startWaveBTN2, 3);

	
	//==========================================================
	//Create first list monster from Wave list
	numOfWave = 0;
	wave = new Wave();
	//==========================================================
	crystal = new Crystal(this);
	auto crystal_position = mTileMap->getObjectGroup("Crystal");
	float xPoint = crystal_position->getObject("bossCrystal")["x"].asInt();
	float yPoint = crystal_position->getObject("bossCrystal")["y"].asInt();
	crystal->getSprite()->setAnchorPoint(Vec2(0.5, 0.3));
	//crystal->getSprite()->setScale(1.5);
	crystal->getSprite()->setPosition(Vec2(xPoint,yPoint));
	//===========================================================================
	//First Location Tower
	listLocationTower.push_back(Vec2(0, 0));
	//===========================================================================

	listTower.push_back(new Tower(this, 1, Vec2(-500,-500)));
	//===========================================================================
	//List point to move monster
	auto road = mTileMap->getObjectGroup("Point");
	for (int i = 0; i < 16; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	//List point 2 to move monster
	auto road2 = mTileMap->getObjectGroup("Point2");
	for (int i = 0; i < 9; i++)
	{
		float x = road2->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road2->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint2.push_back(Vec2(x, y));
	}
	
	//=====================================================
	//Create gold frame
	goldFrame = Sprite::create("goldFrame.png");
	goldFrame->setAnchorPoint(Vec2(0, 1));
	goldFrame->setPosition(10, visibleSize.height - 10);
	goldFrame->removeFromParent();
	addChild(goldFrame, 0);
	//=====================================================
	//Create gold label
	goldLabel = ResourceManager::GetInstance()->GetLabelById(2);
	goldLabel->setPosition(goldFrame->getContentSize().width / 2 + 25, goldFrame->getContentSize().height / 2);
	goldLabel->setAnchorPoint(Vec2(0.5, 0.5));
	goldLabel->setString("");
	goldLabel->removeFromParent();
	goldFrame->addChild(goldLabel);
	//=====================================================
	//Create label start game

	startLabel = ResourceManager::GetInstance()->GetLabelById(3);
	startLabel->setPosition(-6, 10);
	startLabel->setAnchorPoint(Vec2(1, 0));
	startLabel->setString("Click here to start");
	startLabel->setVisible(true);
	startLabel->removeFromParent();
	startBTN->addChild(startLabel);
	//=====================================================
	//Create label that show Wave number when new wave start;
	messageWaveLabel = ResourceManager::GetInstance()->GetLabelById(4);
	messageWaveLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	messageWaveLabel->setScale(0.0001);
	messageWaveLabel->setColor(Color3B::RED);
	messageWaveLabel->removeFromParent();
	addChild(messageWaveLabel, 5);
	//=====================================================
	//Assign gold from Player to gold
	currentGold = Player::GetInstance()->GetCurrentGold();
	//=====================================================
	//Touch event
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(WorldScene1::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(WorldScene1::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(WorldScene1::onTouchEnded, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	time = 0;
	countTimeToPause = 0;
	scheduleUpdate();
	return true;
}
void WorldScene1::update(float deltaTime)
{
	if (clickPause)
	{
		if (countTimeToPause >= 0.6)
		{
			Director::getInstance()->pause();
		}
		else
		{
			countTimeToPause += deltaTime;
		}
	}
	//Set Gold to Label
	goldLabel->setString(to_string(currentGold));
	//Check start click
	if (start)
	{
		crystal->setPercentOfHealthBar();
		for (int i = 0; i < listMonster.size(); i++)
		{
			listMonster[i]->setProgressBar();
		}
		for (int i = 0; i < listMonster.size(); i++)
		{
			MonsterAttack(listMonster[i], crystal->getSprite()->getPosition());
			if (listMonster[i]->GetSprite()->getPosition().getDistance(crystal->getSprite()->getPosition()) < 50)
			{
				listMonster[i]->AttackCrystal(crystal, deltaTime);
			}
		}
		if (time >= 30) {
			if ((numOfWave + 1) <= 5)
			{
				startWaveBTN->setVisible(true);
				startWaveBTN2->setVisible(true);
			}
			else
			{
				startWaveBTN->setEnabled(false);
				startWaveBTN2->setEnabled(false);
			}
		}
		else {
			time += deltaTime;
		}
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
			if ((listMonster[i]->m_flag < listPoint.size() - 1) && (listMonster[i]->GetSprite()->getTag() == 1) && (listMonster[i]->GetSprite()->isVisible()))
			{	
				if (listPoint[listMonster[i]->m_flag].getDistance(listMonster[i]->GetSprite()->getPosition()) == 0)
				{
					listMonster[i]->m_flag++;
					delay = 0;
				}
				else 
				{
					delay = 0.4;
				}
			}
			else if ((listMonster[i]->m_flag < listPoint2.size() - 1) && (listMonster[i]->GetSprite()->getTag() == 0) && (listMonster[i]->GetSprite()->isVisible()))
			{
				if (listPoint2[listMonster[i]->m_flag].getDistance(listMonster[i]->GetSprite()->getPosition()) == 0)
				{
					listMonster[i]->m_flag++;
					delay = 0;
				}
				else
				{
					delay = 0.4;
				}
			}
			
			for (int j = 0; j < listTower.size(); j++)
			{
				if (listTower[j]->GetType() == 5)
				{
					for (int k = 0; k < listTower[j]->GetListSoldier().size(); k++)
					{
						MonsterAttack(listMonster[i], listTower[j]->GetListSoldier()[k]->GetSprite()->getPosition());
					}
				}
			}
			MonsterMove(listMonster[i], listMonster[i]->GetSprite()->getTag(), checkAttack, deltaTime, delay);
		}
		
		//Tower shoot
		for (int tower = 0; tower < listTower.size(); tower++)
		{
			for (int i = 0; i < listMonster.size(); i++)
			{
				nearestMonster = listMonster[0];
				if (listMonster[i]->GetSprite()->getPosition().getDistance(listTower[tower]->GetSprite()->getPosition()) < nearestMonster->GetSprite()->getPosition().getDistance(listTower[tower]->GetSprite()->getPosition()))
				{
					nearestMonster = listMonster[i];
				}
				if (nearestMonster->GetSprite()->getPosition().getDistance(listTower[tower]->GetSprite()->getPosition()) < listTower[tower]->GetRange())
				{
					listTower[tower]->Update(deltaTime, nearestMonster);
					if (listTower[tower]->GetTypeTower() == SLOW_TOWER)
					{
						nearestMonster->SetIsSlow(true);
						nearestMonster->SetSlowRunSpeed();
					}
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
				currentGold += listMonster[i]->GetGold();
				delete listMonster[i];
				listMonster.erase(listMonster.begin() + i);
			}
		}
		//increase speed
		for (int i = 0; i<listMonster.size(); i++)
		{
			if (listMonster[i]->GetMovementSpeed() < listMonster[i]->GetMaxSpeed())
			{
				listMonster[i]->SetMovementSpeed(listMonster[i]->GetMovementSpeed() + 1);
			}
			else
			{
				listMonster[i]->SetMovementSpeed(listMonster[i]->GetMaxSpeed());
			}
		}
	}
}

void WorldScene1::restart()
{
	Label *lbl = Label::createWithTTF("Restart this stage ?", "fonts/Comic_Book.ttf", 40);
	lbl->setWidth(300);
	UICustom::Popup *popup = UICustom::Popup::create("Warning", "", lbl, [=]() {
		clickPause = false;
		Director::getInstance()->resume();
		auto newScene = WorldScene1::createScene();
		Director::getInstance()->replaceScene(newScene);
	});
	this->addChild(popup, 15);
}

//Hide Pause menu
void WorldScene1::ExitPauseMenu()
{
	pauseBtn->setEnabled(true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	pause = false;
	clickPause = false;
	Director::getInstance()->resume();
	pause_bg->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 2, visibleSize.height)));
	//use camera
	//pause_bg->runAction(MoveTo::create(0.5, Vec2(cam->getPositionX(), cam->getPositionY() + visibleSize.height / 2)));
}

//Show Pause menu
void WorldScene1::ClickPauseButton()
{
	pauseBtn->setEnabled(false);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	pause = true;
	//Set other windows disappear
	menu->setVisible(false);
	towerArcherDetails->setVisible(false);
	towerMagicDetails->setVisible(false);
	towerSlowDetails->setVisible(false);
	towerBoombardDetails->setVisible(false);
	towerBarrackDetails->setVisible(false);
	pause_bg->runAction(MoveTo::create(0.5, Vec2(visibleSize.width / 2,visibleSize.height / 6)));
	//use camera
	//pause_bg->runAction(MoveTo::create(0.5, Vec2(cam->getPositionX(), cam->getPositionY()/4)));
	clickPause = true;
	countTimeToPause = 0;
}

void WorldScene1::returnToMainMenu()
{
	clickPause = false;
	Label *lbl = Label::createWithTTF("You will lost your process, continue ?", "fonts/Comic_Book.ttf", 40);
	lbl->setWidth(300);
	UICustom::Popup *popup = UICustom::Popup::create("Warning", "", lbl, [=]() {
		Director::getInstance()->resume();
		//Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(0.3, WorldMapScene::createScene()));
	});
	this->addChild(popup, 15);
}

//Build Tower
void WorldScene1::BuildTower(Ref* ref, int type)
{
	Tower * towerBuild = new Tower(this, type, touchLocation);
	currentGold -= towerBuild->GetGold();
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
void WorldScene1::MonsterAttack(Monster* monster, Vec2 point)
{
	if (monster->GetSprite()->getPosition().distance(point) <= 80 || 
		monster->GetSprite()->getPosition().getDistance(point) <= 60)
	{
		checkAttack = true;
	}
	else
	{
		checkAttack = false;
	}
}
void WorldScene1::MonsterMove(Monster* monster ,int tag, bool check, float timedelay, float delay)
{
	if (tag == 1 && monster->m_flag < listPoint.size())
	{
		monster->Move(listPoint[monster->m_flag], check, timedelay, delay);
	}
	else if (tag == 0 && monster->m_flag < listPoint2.size())
	{
		monster->Move(listPoint2[monster->m_flag], check, timedelay, delay);
	}
}
bool WorldScene1::onTouchBegan(Touch * touch, Event * event)
{
	if (pause)
	{
		return false;
	}
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
			towerChoosing = listTower[i];
			listTower[i]->FadeInPause();
		}
		else
		{
			listTower[i]->FadeOutPause();
		}
	}
	//======================flag======================
	if (towerChoosing != nullptr && towerChoosing->GetCheckTypeTowerBarrack() == true)
	{
		if (towerChoosing->GetCheckTouchFlag() == false)
		{
			//log("oke");
			towerChoosing->GetRangeBarrackTower()->setVisible(false);
		}
		else if (towerChoosing->GetCheckTouchFlag())
			{
				towerChoosing->SetCheckTouchFlag(false);
				towerChoosing->FadeOutPause();
				Flag->setVisible(true);
				towerChoosing->GetRangeBarrackTower()->setVisible(false);
				Flag->setPosition(touch->getLocation());
				if (towerChoosing->GetSprite()->getPosition().distance(Flag->getPosition()) < towerChoosing->GetRange() / 2)
					{
					for (int i = 0; i < towerChoosing->GetListSoldier().size(); i++)
					{
						towerChoosing->GetListSoldier()[i]->GetSprite()->setVisible(true);
						towerChoosing->GetListSoldier()[i]->Move(Vec2(Flag->getPositionX() + ((i + 1) * 5), Flag->getPositionY() + ((i + 1) * 10)));
					}
				}
			}
	}

	//==========================================

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
	auto visi = Director::getInstance()->getVisibleSize();
	Flag->setPosition(touch->getLocation());
	//use camera
	//===============================================================
	//if ((touch->getLocation().x - touch->getPreviousLocation().x) < 0)
	//{
	//	if ((cam->getPositionX() + (touch->getLocation().x - touch->getPreviousLocation().x)) > visi.width/2)
	//	{
	//		cam->setPositionX(cam->getPositionX() + (touch->getLocation().x - touch->getPreviousLocation().x));
	//		//mTileMap->setPositionX(mTileMap->getPositionX() - (touch->getLocation().x - touch->getPreviousLocation().x));
	//	}
	//}
	//else
	//{
	//	if ((cam->getPositionX() + (touch->getLocation().x - touch->getPreviousLocation().x)) < (mTileMap->getContentSize().width - visi.width/2))
	//	{
	//		cam->setPositionX(cam->getPositionX() + (touch->getLocation().x - touch->getPreviousLocation().x));
	//		//mTileMap->setPositionX(mTileMap->getPositionX() - (touch->getLocation().x - touch->getPreviousLocation().x));
	//	}
	//}

	//if ((touch->getLocation().y - touch->getPreviousLocation().y) < 0)
	//{
	//	if ((cam->getPositionY() + (touch->getLocation().y - touch->getPreviousLocation().y)) > visi.height/2)
	//	{
	//		cam->setPositionY(cam->getPositionY() + (touch->getLocation().y - touch->getPreviousLocation().y));
	//		//mTileMap->setPositionY(mTileMap->getPositionY() - (touch->getLocation().y - touch->getPreviousLocation().y));
	//	}
	//}
	//else
	//{
	//	if ((cam->getPositionY() + (touch->getLocation().y - touch->getPreviousLocation().y)) < mTileMap->getContentSize().height - visi.height/2)
	//	{
	//		cam->setPositionY(cam->getPositionY() + (touch->getLocation().y - touch->getPreviousLocation().y));
	//		//mTileMap->setPositionY(mTileMap->getPositionY() - (touch->getLocation().y - touch->getPreviousLocation().y));
	//	}
	//}

	//pauseBtn->setPosition(Vec2(cam->getPositionX() + visi.width / 2 - 20, cam->getPositionY() + visi.height / 2 - 20));
	//startBTN->setPosition(Vec2(cam->getPositionX() + visi.width / 2 - 5, cam->getPositionY() - visi.height / 2 + 5));
	//goldFrame->setPosition(Vec2(cam->getPositionX() - visi.width / 2 + 10, cam->getPositionY() + visi.height / 2 - 10));
	//pause_bg->setScale(0.5);
	//pause_bg->setPosition(Vec2(cam->getPosition().x, cam->getPosition().y + visi.height / 2));
	//================================================================
}

void WorldScene1::onTouchEnded(Touch * touch, Event * event)
{
	Flag->setPosition(touch->getLocation());
	Flag->setVisible(false);
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
		if (currentGold >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 1));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower->setEnabled(false);
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_deactive.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::Warning, this));
		}
		towerArcherDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerArcherDetails->getContentSize().width / 2 + 20, 25));
		towerArcherDetails->setAnchorPoint(Vec2(0.5, 0));
		towerArcherDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 100));
		towerArcherDetails->setVisible(true);
		break;
	case 2:
		if (currentGold >= 100)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy100_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 2));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower->setEnabled(false);
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy100_deactive.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::Warning, this));
		}
		towerMagicDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerMagicDetails->getContentSize().width / 2 + 20, 25));
		towerMagicDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 100));
		towerMagicDetails->setVisible(true);
		break;
	case 5:
		if (currentGold >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 5));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower->setEnabled(false);
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_deactive.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::Warning, this));
		}
		towerBarrackDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerBarrackDetails->getContentSize().width / 2 + 20, 25));
		towerBarrackDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 100));
		towerBarrackDetails->setVisible(true);
		break;
	case 3:
		if (currentGold >= 80)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 3));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower->setEnabled(false);
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_deactive.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::Warning, this));
		}
		towerSlowDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerSlowDetails->getContentSize().width / 2 + 20, 25));
		towerSlowDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 100));
		towerSlowDetails->setVisible(true);
		break;
	case 4: 
		if (currentGold >= 125)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_1(WorldScene1::BuildTower, this, 4));
			buyTower->setEnabled(true);
		}
		else
		{
			buyTower->setEnabled(false);
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_deactive.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::Warning, this));
		}
		towerBoombardDetails->addChild(buyTower);
		buyTower->setScale(0.5);
		buyTower->setPosition(Vec2(towerBoombardDetails->getContentSize().width / 2 + 20, 25));
		towerBoombardDetails->setPosition(Vec2(menu->getPosition().x, menu->getPosition().y + 100));
		towerBoombardDetails->setVisible(true);
		break;
	default:
		break;
	}
}

void WorldScene1::Warning()
{
}

void WorldScene1::startWave()
{
	if (!start)
	{
		startBTN->setVisible(false);
		startBTN->setEnabled(false);
		start = true;
	}
	startWaveBTN->setVisible(false);
	startWaveBTN2->setVisible(false);
	time = 0;
	//Plus num of wave
	numOfWave++;
	messageWaveLabel->setString("Wave " + to_string(numOfWave) + " is coming !"); //Change string of Wave label
	messageWaveLabel->runAction(Sequence::create(ScaleTo::create(0.5, 1), DelayTime::create(2), ScaleTo::create(0.3, 0.001), nullptr));
	vector<int> temp = wave->getWave(numOfWave); //Get info wave from Wave class
	listTemp.clear();
	for (int i = 0; i < temp.size(); i++) //Create monsster and push to list Monster
	{
		Monster *a = new Monster(this, temp[i]);
		a->GetSprite()->setTag(i % 2 == 0 ? 0 : 1);
		listMonster.push_back(a);
		listTemp.push_back(a);
	}
	auto obj = mTileMap->getObjectGroup("Monster");
	float x = obj->getObject("monster")["x"].asInt();
	float y = obj->getObject("monster")["y"].asInt();
	float x2 = obj->getObject("monster2")["x"].asInt();
	float y2 = obj->getObject("monster2")["y"].asInt();
	for (int i = 0; i < listTemp.size(); i++)
	{
		if (listTemp[i]->GetSprite()->getTag() == 0)
		{
			//===================Gate2====================================
			listTemp[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
			listTemp[i]->GetSprite()->setPosition(x2, y2);
			listTemp[i]->GetSprite()->setScale(0.6);
		}
		else if (listTemp[i]->GetSprite()->getTag() == 1)
		{
			listTemp[i]->GetSprite()->setAnchorPoint(Vec2(0.5, 0.35));
			listTemp[i]->GetSprite()->setPosition(x, y);
			listTemp[i]->GetSprite()->setScale(0.6);
		}
	}
}

void WorldScene1::muteSound()
{
}

void WorldScene1::exit()
{
}
