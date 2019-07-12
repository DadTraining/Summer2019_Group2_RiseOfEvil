#include "MainMenuScene.h"
#include "WorldMapScene.h"

cocos2d::Scene * MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

bool MainMenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	// add backgroud for menu scene
	auto backgroundMenu = Sprite::create("res/Sprites/MenuScene/bgMenuScene.jpg");
	backgroundMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundMenu->setScale(visibleSize.width / backgroundMenu->getContentSize().width, visibleSize.height / backgroundMenu->getContentSize().height);
	this->addChild(backgroundMenu, 0);

	//=====================================================================
	//create New Game Button
	btnNewGame = ui::Button::create("res/Buttons/MainMenuScene/BtnNewGame.png", "res/Buttons/MainMenuScene/BtnNewGame.png");
	btnNewGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnNewGame->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 40.0f));
	btnNewGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::FadeinChoose, this));
	this->addChild(btnNewGame, 2);

	//=====================================================================
	//create Load Game Buttons
	btnLoadGame = ui::Button::create("res/Buttons/MainMenuScene/BtnLoadGame.png", "res/Buttons/MainMenuScene/BtnLoadGame.png");
	btnLoadGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnLoadGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 140));
	btnLoadGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::FadeoutChoose, this));
	this->addChild(btnLoadGame, 2);
	//=====================================================================
	//create Credits Buttons
	btnCredits = ui::Button::create("res/Buttons/MainMenuScene/BtnCredits.png", "res/Buttons/MainMenuScene/BtnCredits.png");
	btnCredits->setAnchorPoint(Vec2(0.5, 0.5));
	btnCredits->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
	this->addChild(btnCredits, 2);

	//========================================================================================
	//create Campaign button
	btnCompaign = ui::Button::create("res/Buttons/MainMenuScene/BtnCompaign.png", "res/Buttons/MainMenuScene/BtnCompaign.png");
	btnCompaign->setAnchorPoint(Vec2(0.5, 0.5));
	btnCompaign->setPosition(Vec2(btnNewGame->getPosition().x + 300, btnNewGame->getPosition().y + 50));
	btnCompaign->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToWorldMap, this));

	this->addChild(btnCompaign, -1);

	//========================================================================================
	//create btnSurvival button
	btnSurvival = ui::Button::create("res/Buttons/MainMenuScene/BtnSurvival.png", "res/Buttons/MainMenuScene/BtnSurvival.png");
	btnSurvival->setAnchorPoint(Vec2(0.5, 0.5));
	btnSurvival->setPosition(Vec2(btnNewGame->getPosition().x + 300, btnNewGame->getPosition().y - 50));
	this->addChild(btnSurvival, -1);

	return true;
}


void MainMenuScene::GoToWorldMap()
{
	Scene *pScene = WorldMapScene::create();
	TransitionFade *crssfade = TransitionFade::create(1, pScene);
	Director::getInstance()->replaceScene(crssfade);
}

void MainMenuScene::FadeinChoose()
{
	btnCompaign->setZOrder(1);
	btnSurvival->setZOrder(1);
}

void MainMenuScene::FadeoutChoose()
{
	btnCompaign->setZOrder(-1);
	btnSurvival->setZOrder(-1);
}

