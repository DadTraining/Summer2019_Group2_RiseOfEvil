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
	auto backgroundMenu = Sprite::create("res/Sprites/MainMenuScene/background.png");
	backgroundMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundMenu->setScale(visibleSize.width / backgroundMenu->getContentSize().width, visibleSize.height / backgroundMenu->getContentSize().height);
	this->addChild(backgroundMenu, 0);

	//=====================================================================
	//create New Game Button
	btnNewGame = ui::Button::create("res/Sprites/MainMenuScene/newgameBTN.png", "res/Sprites/MainMenuScene/newgameBTN.png");
	btnNewGame->setScale(0.4);
	btnNewGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnNewGame->setPosition(Vec2(visibleSize.width /2 , visibleSize.height / 1.9));
	btnNewGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::FadeinChoose, this));
	this->addChild(btnNewGame, 2);

	//=====================================================================
	//create Load Game Buttons
	btnLoadGame = ui::Button::create("res/Sprites/MainMenuScene/loadgameBTN.png", "res/Sprites/MainMenuScene/loadgameBTN.png");
	btnLoadGame->setScale(0.5);
	btnLoadGame->setAnchorPoint(Vec2(0.5, 0.5));
	btnLoadGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 110));
	btnLoadGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::FadeoutChoose, this));
	this->addChild(btnLoadGame, 2);
	//=====================================================================
	//create Credits Buttons
	btnCredits = ui::Button::create("res/Sprites/MainMenuScene/creditsBTN.png", "res/Sprites/MainMenuScene/creditsBTN.png");
	btnCredits->setScale(0.5);
	btnCredits->setAnchorPoint(Vec2(0.5, 0.5));
	btnCredits->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 190));
	this->addChild(btnCredits, 2);

	//========================================================================================
	//create Campaign button
	btnCampaign = ui::Button::create("res/Sprites/MainMenuScene/campaignBTN.png", "res/Sprites/MainMenuScene/campaignBTN.png");
	btnCampaign->setScale(0.5);
	btnCampaign->setAnchorPoint(Vec2(0.5, 0.5));
	btnCampaign->setPosition(Vec2(btnLoadGame->getPositionX(), btnLoadGame->getPositionY() + 40));
	btnCampaign->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToWorldMap, this));
	btnCampaign->setEnabled(false);
	btnCampaign->runAction(FadeOut::create(0));
	this->addChild(btnCampaign, 2);

	//========================================================================================
	//create btnSurvival button
	btnSurvival = ui::Button::create("res/Sprites/MainMenuScene/survivalBTN.png", "res/Sprites/MainMenuScene/survivalBTN.png");
	btnSurvival->setScale(0.5);
	btnSurvival->setEnabled(false);
	btnSurvival->setAnchorPoint(Vec2(0.5, 0.5));
	btnSurvival->setPosition(Vec2(btnCredits->getPositionX(), btnCredits->getPositionY() + 40));
	btnSurvival->runAction(FadeOut::create(0));
	this->addChild(btnSurvival, 2);
	//========================================================================================
	btnBack = ui::Button::create("res/Sprites/MainMenuScene/backBTN.png", "res/Sprites/MainMenuScene/backBTN.png");
	btnBack->setScale(0.5);
	btnBack->setEnabled(false);
	btnBack->setPosition(Vec2(btnCredits->getPositionX(), btnCredits->getPositionY() - 40));
	btnBack->runAction(FadeOut::create(0));
	btnBack->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::FadeoutChoose, this));
	this->addChild(btnBack, 2);
	return true;
}

void MainMenuScene::update(float)
{

}


void MainMenuScene::GoToWorldMap()
{
	Scene *pScene = WorldMapScene::create();
	TransitionFade *crssfade = TransitionFade::create(1, pScene);
	Director::getInstance()->replaceScene(crssfade);
}

void MainMenuScene::FadeinChoose()
{
	auto fadeOut = FadeOut::create(0.3f);
	auto fadeIn = FadeIn::create(0.3f);
	/*auto seq = Sequence::create(fadeOut, fadeIn, fadeOut->clone(), fadeIn->clone(), nullptr);
	btnNewGame->runAction(seq);
	auto seq2 = Sequence::create(DelayTime::create(1.8), FadeOut::create(0.2f), nullptr);*/
	btnNewGame->runAction(fadeOut);
	btnLoadGame->runAction(fadeOut->clone());
	btnCredits->runAction(fadeOut->clone());
	btnNewGame->setEnabled(false);
	btnLoadGame->setEnabled(false);
	btnCredits->setEnabled(false);

	btnCampaign->runAction(fadeIn);
	btnSurvival->runAction(fadeIn->clone());
	btnBack->runAction(fadeIn->clone());
	btnCampaign->setEnabled(true);
	btnBack->setEnabled(true);
}

void MainMenuScene::FadeoutChoose()
{
	auto fadeOut = FadeOut::create(0.3f);
	auto fadeIn = FadeIn::create(0.3f);

	btnCampaign->runAction(fadeOut);
	btnSurvival->runAction(fadeOut->clone());
	btnBack->runAction(fadeOut->clone());
	btnCampaign->setEnabled(false);
	btnBack->setEnabled(false);

	btnNewGame->runAction(fadeIn);
	btnLoadGame->runAction(fadeIn->clone());
	btnCredits->runAction(fadeIn->clone());
	btnNewGame->setEnabled(true);
	btnLoadGame->setEnabled(true);
	btnCredits->setEnabled(true);
}

