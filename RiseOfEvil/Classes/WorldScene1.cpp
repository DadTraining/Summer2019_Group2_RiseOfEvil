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
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
		TowerFake->setVisible(false);
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
	canBuild->setAnchorPoint(Vec2(0.5, 0));
	canBuild->setOpacity(80);
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

	////================TowerFake===================================
	TowerFake = Sprite::create("res/WorldScene1/arrowtower1.png");
	TowerFake->setVisible(false);
	TowerFake->setAnchorPoint(Vec2(0.3, 0));
	TowerFake->setScale(0.5);
	this->addChild(TowerFake, 6);
	//==================Range Fake Tower===============================
	rangeFakeTower = Sprite::create("range_of_barrack_tower.png");
	rangeFakeTower->setVisible(true);
	TowerFake->addChild(rangeFakeTower);
	//=================================================================
	//Create pause menu 
	pause_bg = Sprite::create("res/WorldScene1/pause_bag.png");
	pause_bg->setAnchorPoint(Vec2(0.5, 0));
	pause_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	addChild(pause_bg, 6);

	pauseBtn = ui::Button::create("res/Buttons/WorldScene1/pauseBtn.png", "res/Buttons/WorldScene1/pauseBtn-press.png");
	pauseBtn->setScale(1.2);
	pauseBtn->setPosition(Vec2(visibleSize.width - 40, visibleSize.height - 40));
	pauseBtn->addClickEventListener(CC_CALLBACK_0(WorldScene1::ClickPauseButton, this));
	addChild(pauseBtn, 1);

	resumeBtn = ui::Button::create("res/Buttons/WorldScene1/resumeButton.png");
	resumeBtn->setPosition(Vec2(pause_bg->getContentSize().width / 2, pause_bg->getContentSize().height / 2));
	resumeBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::ExitPauseMenu, this));
	resumeBtn->setScale(0.7);
	pause_bg->addChild(resumeBtn);

	moreGoldBtn = ui::Button::create("res/Buttons/WorldScene1/moreGold.png");
	moreGoldBtn->setPosition(Vec2(pause_bg->getContentSize().width - 10, 10));
	moreGoldBtn->setScale(0.3);
	moreGoldBtn->setAnchorPoint(Vec2(1, 0));
	moreGoldBtn->addClickEventListener(CC_CALLBACK_0(WorldScene1::moreGold, this));
	pause_bg->addChild(moreGoldBtn);
	
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
	startBTN->setScale(0.7);
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
	currentStage = Player::GetInstance()->GetCurrentStage();
	wave = new Wave(currentStage);
	road1TotalPoint = wave->getRoad1TotalPoint();
	road2TotalPoint = wave->getRoad2TotalPoint();
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
	for (int i = 0; i < road1TotalPoint; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}
	//List point 2 to move monster
	auto road2 = mTileMap->getObjectGroup("Point2");
	for (int i = 0; i < road2TotalPoint; i++)
	{
		float x = road2->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road2->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint2.push_back(Vec2(x, y));
	}
	
	//=====================================================
	//Create gold frame
	goldFrame = Sprite::create("goldFrame.png");
	goldFrame->setAnchorPoint(Vec2(0, 1));
	goldFrame->setPosition(40, visibleSize.height - 20);
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
	startBTN->setVisible(false);
	startBTN->addChild(startLabel);
	//=====================================================
	//Create label that show Wave number when new wave start
	messageWaveLabel = ResourceManager::GetInstance()->GetLabelById(4);
	messageWaveLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	messageWaveLabel->setScale(0.0001);
	messageWaveLabel->setColor(Color3B::RED);
	messageWaveLabel->removeFromParent();
	addChild(messageWaveLabel, 10);
	//=====================================================
	//Create label show how to build Tower
	showHowToBuildTower = Label::createWithTTF("Touch anywhere on the ground to build Tower", "fonts/Comic_Book.ttf", 20);
	showHowToBuildTower->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	showHowToBuildTower->removeFromParent();
	addChild(showHowToBuildTower, 5);
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
	//=====================================================
	scheduleUpdate();
	return true;
}

void WorldScene1::update(float deltaTime)
{
	if (listTower.size() > 1 && !start)
	{
		startBTN->setVisible(true);
	}
	//Check pause or not
	if (clickPause)
	{
		if (countTimeToPause >= 0.4)
		{
			Director::getInstance()->pause();
		}
		else
		{
			countTimeToPause += deltaTime;
		}
	}
	//Check sell tower
	for (int i = 0; i < listTower.size(); i++)
	{
		if (listTower[i]->getIsSell())
		{
			for (int j = 0; j < listLocationTower.size(); j++)
			{
				if (listTower[i]->GetSprite()->getPosition() == listLocationTower[j])
				{
					listLocationTower.erase(listLocationTower.begin() + j);
				}
			}
			listTower[i]->GetSprite()->setVisible(false);
			currentGold += listTower[i]->GetGold() / 2;
			//delete listTower[i];
			listTower.erase(listTower.begin() + i);
		}
	}
	//Check tower update
	for (int i = 0; i < listTower.size(); i++)
	{
		if (listTower[i]->getRequestUpdate())
		{
			if (listTower[i]->GetGold() > currentGold || listTower[i]->getLevel() >= 3) //not enough money and more than 3 level upgraded
			{
				listTower[i]->acceptUpdate(false);
			}
			else
			{
				currentGold -= listTower[i]->GetGold();	
				listTower[i]->acceptUpdate(true);
				listTower[i]->HideCircleMenu();
			}
		}
	}
	//Check build tower
	if (checkClickBuildButton)
	{
		if (hpBar->getPercentage() >= 100)
		{
			BuildTower();
		}
		hpBar->setPercentage(hpBar->getPercentage() + 5);
	}
	//Set Gold to Label
	goldLabel->setString(to_string(currentGold));
	//Check start click
	if (start)
	{
		crystal->setPercentOfHealthBar();
		//Set health bar of monster
		for (int i = 0; i < listMonster.size(); i++)
		{
			listMonster[i]->setProgressBar();
		}
		for (int i = 0; i < listMonster.size(); i++)
		{
			if (listMonster[i]->GetSprite()->getPosition().getDistance(crystal->getSprite()->getPosition()) < 50)
			{
				listMonster[i]->AttackCrystal(crystal, deltaTime);
			}
		}
		if (time >= 40)
		{
			startWave();
		}
		if (time >= 35) {
			if ((numOfWave + 1) <= 8)
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
		time += deltaTime;
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
			if ((listMonster[i]->m_flag < listPoint.size()) && (listMonster[i]->GetSprite()->getTag() == 1) && (listMonster[i]->GetSprite()->isVisible()))
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
			else if ((listMonster[i]->m_flag < listPoint2.size()) && (listMonster[i]->GetSprite()->getTag() == 0) && (listMonster[i]->GetSprite()->isVisible()))
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
			checkMonsterAttack = MonsterAttack(listMonster[i]);
			MonsterMove(listMonster[i], listMonster[i]->GetSprite()->getTag(), checkMonsterAttack, deltaTime, delay);
		}
		//Monster die
		for (int m = 0; m < listMonster.size(); m++)
		{
			if (listMonster[m]->GetHitPoint() <= 0)
			{
				listMonster[m]->DoDead();
				listMonster[m]->GetSprite()->setVisible(false);
				currentGold += listMonster[m]->GetGold();
				listMonster.erase(listMonster.begin() + m);
			}
		}
		//Monster attack
		for (int tower = 0; tower < listTower.size(); tower++)
		{
			for (int monster = 0; monster < listMonster.size(); monster++)
			{
//Check in range and alive
if (listMonster[monster]->GetSprite()->getPosition().distance(listTower[tower]->GetSprite()->getPosition())
	<
	listTower[tower]->GetRange()
	&&
	listMonster[monster]->GetSprite()->isVisible() == true)
{
	//check target out range or die, set target by nullptr when it happen
	if (listTower[tower]->getStatusOfTarget())
	{
		listTower[tower]->setTarget(listMonster[monster]);
	}
	else
	{
		break;
	}
}
			}
		}
		//Soldier Attack
		for (int i = 0; i < listTower.size(); i++)
		{
			if (listTower[i]->GetType() == 5)
			{
				for (int j = 0; j < listTower[i]->GetListSoldier().size(); j++)
				{
					checkSoldierAttack = SoldierAttack(listTower[i]->GetListSoldier()[j]);
					if (listTower[i]->GetListSoldier()[j]->GetCheckFindMonster() == false)
					{
						SoldierFindMonster(listTower[i]->GetListSoldier()[j], listTower[i]->GetListSoldier()[j], deltaTime);
					}
					if (!listTower[i]->GetListSoldier()[j]->GetListMonsterAttack().empty())
					{
						log("ListSolderMonstet:%d", listTower[i]->GetListSoldier()[j]->GetListMonsterAttack().size());
						log("PositionX: %f  PositionY: %f", listTower[i]->GetListSoldier()[j]->GetListMonsterAttack()[0]->GetSprite()->getPosition().x, listTower[i]->GetListSoldier()[j]->GetListMonsterAttack()[0]->GetSprite()->getPosition().y);
						listTower[i]->GetListSoldier()[j]->MoveToMonster(listTower[i]->GetListSoldier()[j]->GetListMonsterAttack()[0]->GetSprite()->getPosition(), checkSoldierAttack, deltaTime);
						if (listTower[i]->GetListSoldier()[j]->GetSprite()->getPosition().distance(listTower[i]->GetListSoldier()[j]->GetListMonsterAttack()[0]->GetSprite()->getPosition()) > 200)
						{
							listTower[i]->GetListSoldier()[j]->SetListMonsterAttackClear();
						}
					}
				}
			}
		}
		//Tower main shoot and decrease HP of monster
		for (int i = 0; i < listTower.size(); i++)
		{
			listTower[i]->Update(deltaTime, listMonster);

		}
		//increase speed when monster is slowing
		if (countTimeToIncreaseSpeedMonster > 0.3)
		{
			for (int i = 0; i < listMonster.size(); i++)
			{
				if (listMonster[i]->GetMovementSpeed() < listMonster[i]->GetMSpeed())
				{
					listMonster[i]->SetMovementSpeed(listMonster[i]->GetMovementSpeed() + 1);
				}
				else
				{
					listMonster[i]->SetMovementSpeed(listMonster[i]->GetMSpeed());
					listMonster[i]->GetSprite()->setColor(Color3B(255, 255, 255));
				}
			}
			countTimeToIncreaseSpeedMonster = 0;

		}
		else
		{
			countTimeToIncreaseSpeedMonster += deltaTime;
		}

		for (int i = 0; i < listTower.size(); i++)
		{
			if (listTower[i]->getLevel() == 3)
			{
				switch (listTower[i]->GetType())
				{
				case ARROW_TOWER:
					listTower[i]->setIncreaseAttackSpeedSkill(true);
					break;
				case MAGIC_TOWER:
					listTower[i]->setIncreaseAttackDamageSkill(true);
					break;
				case SLOW_TOWER:
					listTower[i]->slowSkill(listMonster);
					//listTower[i]->getTowerSkill()->getSprite()->setVisible(true);
					break;
				case BOMBARD_TOWER:
					listTower[i]->burnSkill(listMonster, deltaTime);
					//listTower[i]->getTowerSkill()->getSprite()->setVisible(true);
				}

			}
			if (listTower[i]->getIncreaseAttackSpeedSkill() == true)
			{
				for (int j = 0; j < listTower.size(); j++)
				{
					if (listTower[i]->GetSprite()->getPosition().distance(listTower[j]->GetSprite()->getPosition()) < 150
						&& listTower[i]->GetSprite()->getPosition().distance(listTower[j]->GetSprite()->getPosition()) > 10)
					{
						if (listTower[j]->GetAttackSpeed() > listTower[j]->getMinimumAttackSpeed()* 90 / 100)
						{
							listTower[j]->SetAttackSpeed(listTower[j]->GetAttackSpeed() * 98 / 100);
						}
					}
				}
			}
			if (listTower[i]->getIncreaseAttackDamageSkill() == true)
			{
				for (int j = 0; j < listTower.size(); j++)
				{
					if (listTower[i]->GetSprite()->getPosition().distance(listTower[j]->GetSprite()->getPosition()) < 150
						&& listTower[i]->GetSprite()->getPosition().distance(listTower[j]->GetSprite()->getPosition()) > 10)
					{
						if (listTower[j]->GetMinimumAtk() < 20 && listTower[j]->GetMaximumAtk() < 60)
						{
							listTower[j]->SetMinimumAtk(listTower[j]->GetMinimumAtk() * 110 / 100);
							listTower[j]->SetMaximumAtk(listTower[j]->GetMaximumAtk() * 110 / 100);
						}
					}
				}
			}
		}

	}

		for (int i = 0; i < listTower.size(); i++)
		{
			if (listTower[i]->GetType() == 5)
			{
				for (int j = 0; j < listTower[i]->GetListSoldier().size(); j++)
				{
					if (listTower[i]->GetListSoldier()[j]->GetMovementSpeed() < listTower[i]->GetListSoldier()[j]->GetMSpeed())
					{
						listTower[i]->GetListSoldier()[j]->SetMovementSpeed(listTower[i]->GetListSoldier()[j]->GetMovementSpeed() + 0.5);
					}
					if (listTower[i]->GetListSoldier()[j]->GetMovementSpeed() >= listTower[i]->GetListSoldier()[j]->GetMSpeed())
					{
						listTower[i]->GetListSoldier()[j]->SetMovementSpeed(listTower[i]->GetListSoldier()[j]->GetMSpeed());
						listTower[i]->GetListSoldier()[j]->GetSprite()->setColor(Color3B(255, 255, 255));
					}
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

//Exit Pause menu
void WorldScene1::ExitPauseMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	pause = false;
	clickPause = false;
	Director::getInstance()->resume();
	pauseBtn->setEnabled(true);
	pauseBtn->setPosition(Vec2(visibleSize.width - 40, visibleSize.height - 40));
	pause_bg->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2, visibleSize.height)));
	//use camera
	//pause_bg->runAction(MoveTo::create(0.5, Vec2(cam->getPositionX(), cam->getPositionY() + visibleSize.height / 2)));
}

//Show Pause menu
void WorldScene1::ClickPauseButton()
{
	pauseBtn->setEnabled(false);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	pauseBtn->setPosition(Vec2(visibleSize.width + 100, visibleSize.height + 100));
	pause = true;
	countTimeToPause = 0;
	//Set other windows disappear
	menu->setVisible(false);
	towerArcherDetails->setVisible(false);
	towerMagicDetails->setVisible(false);
	towerSlowDetails->setVisible(false);
	towerBoombardDetails->setVisible(false);
	towerBarrackDetails->setVisible(false);
	pause_bg->runAction(MoveTo::create(0.4, Vec2(visibleSize.width / 2,visibleSize.height / 6)));
	//use camera
	//pause_bg->runAction(MoveTo::create(0.5, Vec2(cam->getPositionX(), cam->getPositionY()/4)));
	clickPause = true;
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
void WorldScene1::BuildTower()
{
	Tower * towerBuild = new Tower(this, typeOfTowerPrepairToBuild, touchLocation);
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
	TowerFake->setVisible(false);
	checkClickBuildButton = false;
	hpBgSprite->setVisible(false);
	hpBar->setPercentage(0);
}

void WorldScene1::moveFlag(Vec2 Pos)
{
}

bool WorldScene1::MonsterAttack(Monster* monster)
{
	if (monster->GetSprite()->getPosition().distance(crystal->getSprite()->getPosition()) <= 50)
	{
		return true;
	}
	for (int j = 0; j < listTower.size(); j++)
	{
		if (listTower[j]->GetType() == 5)
		{
			for (int k = 0; k < listTower[j]->GetListSoldier().size(); k++)
			{
				if (monster->GetSprite()->getPosition().distance(listTower[j]->GetListSoldier()[k]->GetSprite()->getPosition()) <= 20)
				{
					return true;
				}
			}
		}
	}
	return false;
}
void WorldScene1::SoldierFindMonster(Soldier* soldier, bool checkAttack, float timedelay)
{
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (soldier->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) <= 200)
		{	
			if (CheckListMonsterSoldierFound(listMonster[i]))
			{
				m_listMonsterSoldierFound.push_back(listMonster[i]);
				soldier->SetListMonsterAttack(listMonster[i]);
				soldier->SetCheckFindMonster(true);
				i = 100;
			}		
		}
	}
}
bool WorldScene1::CheckListMonsterSoldierFound(Monster* monster)
{
	if (!m_listMonsterSoldierFound.empty()) 
	{
		for (int i = 0; i < m_listMonsterSoldierFound.size(); i++)
		{
			if (monster == m_listMonsterSoldierFound[i])
			{
				return false;
			}
		}
		return true;
	}
}
bool WorldScene1::SoldierAttack(Soldier* soldier)
{
	for (int i = 0; i < listMonster.size(); i++)
	{
		if (soldier->GetSprite()->getPosition().distance(listMonster[i]->GetSprite()->getPosition()) <= 20)
		{
			return true;
		}
	}
	return false;
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
					TowerFake->setVisible(false);
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
			if (listTower[i]->getLevel() == 3)
			{
				listTower[i]->getPriceUpgradeLabel()->setString("MAX");
			}
			if (listTower[i]->GetGold() > currentGold || listTower[i]->getLevel() >= 3)
			{
				listTower[i]->getUpgradeIcon()->setEnabled(false);
				listTower[i]->getPriceUpgradeLabel()->setColor(Color3B::RED);
			}
			else
			{
				listTower[i]->getUpgradeIcon()->setEnabled(true);
				listTower[i]->getPriceUpgradeLabel()->setColor(Color3B::YELLOW);
			}
			listTower[i]->ShowCircleMenu();
		}
		else
		{
			listTower[i]->HideCircleMenu();
		}
	}
	//======================flag======================
	if (towerChoosing != nullptr && towerChoosing->GetCheckTypeTowerBarrack() == true)
	{
		if (towerChoosing->GetCheckTouchFlag() == false)
		{
			towerChoosing->GetRangeBarrackTower()->setVisible(false);
		}
		else if (towerChoosing->GetCheckTouchFlag())
			{		
				for (int i = 0; i < towerChoosing->GetListSoldier().size(); i++)
				{
					towerChoosing->GetListSoldier()[i]->SetTouchFlag(true);
				}
				towerChoosing->SetCheckTouchFlag(false);
				towerChoosing->HideCircleMenu();
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
//Check Location have tower or not
bool WorldScene1::checkLocationBuildTower(Vec2 newPoint)
{
	for (int i = 0; i < listLocationTower.size(); i++)
	{
		if (newPoint.getDistance(listLocationTower[i]) < 25)
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
}

void WorldScene1::onTouchEnded(Touch * touch, Event * event)
{
	showHowToBuildTower->setVisible(false);
	Flag->setPosition(touch->getLocation());
	Flag->setVisible(false);
}

//Create menu build Tower
void WorldScene1::createmenu(Vec2 point)
{
	if (touchLocation.x > 350)
	{
		menu->setPosition(Vec2(point.x - 150, point.y));
	}
	else
	{
		menu->setPosition(Vec2(point.x + 150, point.y));
	}
	//menu->setPosition(Vec2(point.x -150, point.y));
	archerIcon->setPosition(menu->getContentSize().width, menu->getContentSize().height);
	magicIcon->setPosition(menu->getContentSize().width + magicIcon->getContentSize().width, menu->getContentSize().height);
	slowIcon->setPosition(menu->getContentSize().width + 2 * slowIcon->getContentSize().width, menu->getContentSize().height);
	boombardIcon->setPosition(menu->getContentSize().width + 3 * boombardIcon->getContentSize().width, menu->getContentSize().height);
	barrackIcon->setPosition(menu->getContentSize().width + 4 * barrackIcon->getContentSize().width, menu->getContentSize().height);
	cancelMenu->setPosition(menu->getContentSize().width + 5 * cancelMenu->getContentSize().width, menu->getContentSize().height);
	if (!menu->isVisible())
	{
		menu->setVisible(true);
		//canBuild->setVisible(true);
	}
}

void WorldScene1::StatusMenu(bool check)
{
	if (check == true)
	{
		menu->setVisible(true);
		//canBuild->setVisible(true);
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
		TowerFake->setVisible(false);
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
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::LoadingBuildTower, this));
			typeOfTowerPrepairToBuild = 1;
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

		checkTouchBuildTowerFake = true;
		BuildTowerFake(1);
		break;
	case 2:
		if (currentGold >= 100)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy100_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::LoadingBuildTower, this));
			typeOfTowerPrepairToBuild = 2;
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

		checkTouchBuildTowerFake = true;
		BuildTowerFake(2);
		break;
	case 5:
		if (currentGold >= 70)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy70_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::LoadingBuildTower, this));
			typeOfTowerPrepairToBuild = 5;
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

		checkTouchBuildTowerFake = true;
		BuildTowerFake(3);
		break;
	case 3:
		if (currentGold >= 80)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy80_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::LoadingBuildTower, this));
			typeOfTowerPrepairToBuild = 3;
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

		checkTouchBuildTowerFake = true;
		BuildTowerFake(4);
		break;
	case 4: 
		if (currentGold >= 125)
		{
			buyTower = ui::Button::create("res/WorldScene1/buttonBuy125_active.png");
			buyTower->addClickEventListener(CC_CALLBACK_0(WorldScene1::LoadingBuildTower, this));
			typeOfTowerPrepairToBuild = 4;
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

		checkTouchBuildTowerFake = true;
		BuildTowerFake(5);
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

void WorldScene1::moreGold()
{
	currentGold += 200;
}


void WorldScene1::BuildTowerFake(int type)
{
	if (checkTouchBuildTowerFake)
	{
	switch (type)
	{
	case 1:
		TowerFake->setTexture("res/WorldScene1/arrowtower1.png");
		rangeFakeTower->setScale(1.11);
		break;
	case 2:
		TowerFake->setTexture("res/WorldScene1/magictower1.png");
		rangeFakeTower->setScale(1.556);
		break;
	case 3:
		TowerFake->setTexture("res/WorldScene1/brracktower1.png");
		rangeFakeTower->setScale(1);
		break;
	case 4:
		TowerFake->setTexture("res/WorldScene1/slowtower1.png");
		rangeFakeTower->setScale(1);
		break;
	case 5:
		TowerFake->setTexture("res/WorldScene1/boomtower1.png");
		rangeFakeTower->setScale(1);
		break;
	default:
		break;
	}
		TowerFake->setVisible(true);
		TowerFake->setOpacity(100);
		TowerFake->setPosition(touchLocation);
		rangeFakeTower->setVisible(true);
		rangeFakeTower->setPosition(TowerFake->getContentSize().width / 2, TowerFake->getContentSize().height / 2);
		checkTouchBuildTowerFake = false;
	}
	else
	{
		TowerFake->setVisible(false);
	}
}

void WorldScene1::LoadingBuildTower()
{
	checkClickBuildButton = true;
	hpBgSprite = Sprite::create("res/WorldScene1/loadingbar_bg.png");
	hpBgSprite->setVisible(true);
	hpBgSprite->setPosition(Point(TowerFake->getContentSize().width / 2, TowerFake->getContentSize().height /2));
	TowerFake->addChild(hpBgSprite);
	hpBar = CCProgressTimer::create(Sprite::create("res/WorldScene1/loadingbar.png"));
	hpBar->setColor(Color3B::RED);
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(0);
	hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 2));
	hpBgSprite->addChild(hpBar);
	hpBgSprite->setScale(0.1);
}
