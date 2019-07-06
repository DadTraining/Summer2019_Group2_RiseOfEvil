#include "MainMenuScene.h"
#include "WorldScene1.h"

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
	auto backgroundMenu = Sprite::create("res/Sprites/MenuScene/MenuScene.png");
	backgroundMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	backgroundMenu->setScaleX(visibleSize.width / getContentSize().width );
	backgroundMenu->setScaleY(visibleSize.height / getContentSize().height);
	this->addChild(backgroundMenu, -10);

	//button new game
	btnNewGame = ui::Button::create("res/Buttons/MainMenuScene/NewGameBtn.png", "res/Buttons/MainMenuScene/NewGameBtn.png");
	btnNewGame->setPosition(Vec2((visibleSize.width / 2)+(visibleSize.width/60), (visibleSize.height / 2)-(visibleSize.height/12)));
	btnNewGame->addTouchEventListener(CC_CALLBACK_0(MainMenuScene::GoToTableChooseMode, this));
	this->addChild(btnNewGame);

	//button Load game
	btnLoadGame = ui::Button::create("res/Buttons/MainMenuScene/LoadGameBtn.png", "res/Buttons/MainMenuScene/LoadGameBtn.png");
	btnLoadGame->setPosition(Vec2((visibleSize.width / 2) + (visibleSize.width/60), (visibleSize.height / 2) - (visibleSize.height/4.0)));
	this->addChild(btnLoadGame);

	//button credit
	btnCredit = ui::Button::create("res/Buttons/MainMenuScene/CreditBtn.png", "res/Buttons/MainMenuScene/CreditBtn.png");
	btnCredit->setPosition(Vec2((visibleSize.width / 2) + (visibleSize.width / 60), (visibleSize.height / 2) - (visibleSize.height / 2.4)));
	log("%f", (visibleSize.width / 2) + (visibleSize.width / 85, 715));
	this->addChild(btnCredit);

}

//function choose mode game
void MainMenuScene::GoToTableChooseMode()
{
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto delayTime = DelayTime::create(1.0f);
	//auto delayTime2 = DelayTime::create(f);
	// sequen for animation button new game click
	auto sequence = Sequence::create(FadeOut::create(2), nullptr);
	btnNewGame->runAction(sequence);
	btnLoadGame->runAction(sequence->clone());
	//button mode compaign
	btnCompaign = ui::Button::create("res/Buttons/MainMenuScene/CampaignBtn.png", "res/Buttons/MainMenuScene/CampaignBtn.png");
	btnCompaign->setPosition(Vec2((visibleSize.width / 2) + (visibleSize.width / 60), (visibleSize.height / 2) - (visibleSize.height / 12)));

	//auto fadeIn = FadeIn::create(2.0f);
	auto sequenceBtnCompaign = Sequence::create(FadeOut::create(0), delayTime, FadeIn::create(2.0f), nullptr);
	btnCompaign->runAction(sequenceBtnCompaign->clone());
	btnCompaign->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			Director::getInstance()->replaceScene(TransitionRotoZoom::create(0.5f, WorldScene1::createScene()));
			break;
		}

	});
	this->addChild(btnCompaign,1);
	//button mode survival
	btnSurvival = ui::Button::create("res/Buttons/MainMenuScene/SurvivalBtn.png", "res/Buttons/MainMenuScene/SurvivalBtn.png");
	btnSurvival->setPosition(Vec2((visibleSize.width / 2) + (visibleSize.width / 60), (visibleSize.height / 2) - (visibleSize.height / 4.0)));
	btnSurvival->runAction(sequenceBtnCompaign->clone());
	this->addChild(btnSurvival);
}

