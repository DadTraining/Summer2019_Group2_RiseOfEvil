#include <string.h>
#include <iostream>
#include "WorldMapScene.h"
#include "UpgradeScene.h"
#include "ui/CocosGUI.h"
#include "WorldScene1.h"
#include "MainMenuScene.h"
#include "Player.h"

using namespace std;
Scene * WorldMapScene::createScene()
{
	return WorldMapScene::create();
}

bool WorldMapScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto world_bg = TMXTiledMap::create("res/Sprites/WorldMapScene/map.tmx");
	world_bg->setAnchorPoint(Vec2(0, 0));
	world_bg->setPosition(Vec2(0, 0));
	addChild(world_bg);

	auto obj_flag = world_bg->getObjectGroup("stage");
	vector<ui::Button*> staged;
	for (int i = 0; i < 5; i++) {
		float x = obj_flag->getObject("Stage" + to_string(i + 1))["x"].asInt();
		float y = obj_flag->getObject("Stage" + to_string(i + 1))["y"].asInt();
		auto flag = ui::Button::create("res/Sprites/WorldMapScene/flag_normal.png", "res/Sprites/WorldMapScene/flag_pressed.png","res/Sprites/WorldMapScene/flag_disable.png");
		flag->setEnabled(false);
		flag->setPosition(Vec2(x, y));
		flag->setScale(0.8);
		flag->setAnchorPoint(Vec2(0.5, 0));
		flag->addClickEventListener(CC_CALLBACK_1(WorldMapScene::GoToStage, this, i + 1));
		addChild(flag, 1);
		staged.push_back(flag);
	}

	for (int i = 0; i < Player::GetInstance()->GetCurrentStage(); i++)
	{
		staged[i]->setEnabled(true);
		add_star(staged[i]->getPosition());
	}

	auto backBtn = ui::Button::create("res/Sprites/WorldMapScene/backBtn_normal.png", "res/Sprites/WorldMapScene/backBtn_pressed.png");
	//backBtn->setScale(0.2);
	backBtn->setPosition(Vec2(100, 50));
	backBtn->setScale(0.2);
	backBtn->addClickEventListener(CC_CALLBACK_0(WorldMapScene::GoToMainMenu, this));
	addChild(backBtn);

	auto upgradeBtn = ui::Button::create("res/Sprites/WorldMapScene/UpgradeNormalBtn.png", "res/Sprites/WorldMapScene/UpgradePressBtn.png");
	upgradeBtn->setPosition(Vec2(visibleSize.width - 100, 50));
	upgradeBtn->setAnchorPoint(Vec2(1, 0.5));
	upgradeBtn->addClickEventListener(CC_CALLBACK_0(WorldMapScene::GoToUpgrade, this));
	addChild(upgradeBtn);

	return true;
}

void WorldMapScene::GoToStage(Ref* sender, int numOfStage)
{
	Player::GetInstance()->SetCurrentStage(numOfStage);
	Scene *pScene = WorldScene1::createScene();
	TransitionFade *crssfade = TransitionFade::create(0.5f, pScene);
	Director::getInstance()->replaceScene(crssfade);
	touchMusic = SimpleAudioEngine::getInstance();
	touchMusic->playEffect("sound/Sound_GUIButtonCommon.wav", false, 1.0f, 1.0f, 1.0f);
}


void WorldMapScene::GoToMainMenu()
{
	Scene *pScene = MainMenuScene::create();
	TransitionFade *crssfade = TransitionFade::create(0.5f, pScene);
	Director::getInstance()->replaceScene(crssfade);
	touchMusic = SimpleAudioEngine::getInstance();
	touchMusic->playEffect("sound/Sound_GUIOpenTowerMenu.wav", false, 1.0f, 1.0f, 1.0f);
}

void WorldMapScene::GoToUpgrade()
{
	Scene *pScene = UpgradeScene::create();
	TransitionFade *crssfade = TransitionFade::create(0.5f, pScene);
	Director::getInstance()->replaceScene(crssfade);
	touchMusic = SimpleAudioEngine::getInstance();
	touchMusic->playEffect("sound/Sound_GUIButtonCommon.wav", false, 1.0f, 1.0f, 1.0f);
}

void WorldMapScene::add_star(Vec2 vec)
{
	auto star1 = Sprite::create("res/Sprites/WorldMapScene/star.png");
	star1->setScale(0.05);
	star1->setPosition(vec.x - 20, vec.y - 20);
	addChild(star1);

	auto star2 = Sprite::create("res/Sprites/WorldMapScene/star.png");
	star2->setScale(0.05);
	star2->setPosition(vec.x, vec.y - 20);
	addChild(star2);

	auto star3 = Sprite::create("res/Sprites/WorldMapScene/star.png");
	star3->setScale(0.05);
	star3->setPosition(vec.x + 20, vec.y - 20);
	addChild(star3);
}

