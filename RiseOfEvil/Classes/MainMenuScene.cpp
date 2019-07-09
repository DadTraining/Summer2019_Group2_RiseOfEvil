#include "MainMenuScene.h"
//#include "WorldScene1.h"
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
	//log("x:%f", backgroundMenu->getContentSize().width);
	//log("y:%f", backgroundMenu->getContentSize().height);
	this->addChild(backgroundMenu, -10);

	//=====================================================================
	//create New Game Button
	btnNewGame = ui::Button::create("res/Buttons/MainMenuScene/BtnNewGame.png", "res/Buttons/MainMenuScene/BtnNewGame.png");
	btnNewGame->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 40.0f));
	btnNewGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToChooseMode, this));
	this->addChild(btnNewGame);

	//=====================================================================
	//create Load Game Buttons
	btnLoadGame = ui::Button::create("res/Buttons/MainMenuScene/BtnLoadGame.png", "res/Buttons/MainMenuScene/BtnLoadGame.png");
	btnLoadGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 140));
	this->addChild(btnLoadGame);
	//=====================================================================
	//create Credits Buttons
	btnCredits = ui::Button::create("res/Buttons/MainMenuScene/BtnCredits.png", "res/Buttons/MainMenuScene/BtnCredits.png");
	btnCredits->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 240));
	this->addChild(btnCredits);
	//========================================================================================
	//create Campaign button
	btnCompaign = ui::Button::create("res/Buttons/MainMenuScene/BtnCompaign.png", "res/Buttons/MainMenuScene/BtnCompaign.png");
	btnCompaign->setPosition(Vec2(visibleSize.width / 2, -100));
	btnCompaign->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToWorldMap, this));
	this->addChild(btnCompaign);

	//========================================================================================
	//create btnSurvival button
	btnSurvival = ui::Button::create("res/Buttons/MainMenuScene/BtnSurvival.png", "res/Buttons/MainMenuScene/BtnSurvival.png");
	btnSurvival->setPosition(Vec2(visibleSize.width / 2, -100));
	this->addChild(btnSurvival);

	btnBack = ui::Button::create("res/Buttons/MainMenuScene/BtnBack.png", "res/Buttons/MainMenuScene/BtnBack.png");
	btnBack->setPosition(Vec2(visibleSize.width / 2, -100));
	btnBack->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToMenu, this));
	this->addChild(btnBack);
	//==============================================================================================
	return true;
}
void MainMenuScene::GoToChooseMode()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto move = MoveBy::create(1, Vec2(0, 100));
	//auto move2 = MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto fade = FadeOut::create(1);
	btnNewGame->runAction(move);
	btnNewGame->runAction(fade);
	btnLoadGame->runAction(move->clone());
	btnLoadGame->runAction(fade->clone());
	btnCredits->runAction(move->clone());
	btnCredits->runAction(fade->clone());
	//================================================
	log("%f", visibleSize.width);
	btnCompaign->runAction(MoveBy::create(1, Vec2(0, 180)));
	btnSurvival->runAction(MoveBy::create(1, Vec2(0, 130)));
	btnBack->runAction(MoveBy::create(1, Vec2(0, 80)));
	//btnBack->runAction(MoveTo::create(1, Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 240.0f)));

}

void MainMenuScene::GoToWorldMap()
{
	Scene *pScene = WorldMapScene::create();
	TransitionFade *crssfade = TransitionFade::create(1, pScene);
	Director::getInstance()->replaceScene(crssfade);
}

void MainMenuScene::GoToMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto move = MoveBy::create(1, Vec2(0, -100));
	//auto move2 = MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	auto fade = FadeIn::create(1);
	btnNewGame->runAction(move);
	btnNewGame->runAction(fade);
	btnLoadGame->runAction(move->clone());
	btnLoadGame->runAction(fade->clone());
	btnCredits->runAction(move->clone());
	btnCredits->runAction(fade->clone());
	//================================================
	log("%f", visibleSize.width);
	btnCompaign->runAction(MoveBy::create(1, Vec2(0, -180)));
	btnSurvival->runAction(MoveBy::create(1, Vec2(0, -130)));
	btnBack->runAction(MoveBy::create(1, Vec2(0, -80)));
}



void MainMenuScene::ActionMode()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto compaignMove = MoveTo::create(1, Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 40.0f));
	auto survivalMove = MoveTo::create(1, Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 140.0f));
	auto backMove = MoveTo::create(1, Vec2(visibleSize.width / 2, (visibleSize.height / 2) - 240.0f));
	btnCompaign->runAction(compaignMove);
	btnSurvival->runAction(survivalMove);
	btnBack->runAction(backMove);
}

void MainMenuScene::ActionMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();


	//btnNewGame->setPosition()
}

void MainMenuScene::BackMenu()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	btnNewGame->setPosition(Vec2(visibleSize.width / 2, -100));
	btnLoadGame->setPosition(Vec2(visibleSize.width / 2, -100));
	btnCredits->setPosition(Vec2(visibleSize.width / 2, -100));

}

