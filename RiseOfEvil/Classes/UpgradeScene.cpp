#include "UpgradeScene.h"

cocos2d::Scene * UpgradeScene::createScene()
{
	return UpgradeScene::create();
}

bool UpgradeScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//---------------------------------------------------------
	background = Sprite::create("res/UpgradeScene/background.png");
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setScaleX(1.5f);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 500));
	background->runAction(MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	this->addChild(background, 0);
	//---------------------------------------------------------
	doneBtn = ui::Button::create("res/UpgradeScene/doneButton.png");
	doneBtn->setPosition(Vec2(visibleSize.width / 1.2, visibleSize.height / 14));
	this->addChild(doneBtn);
	doneBtn->runAction(Sequence::create(FadeOut::create(0), DelayTime::create(1), FadeIn::create(0),nullptr));
	//---------------------------------------------------------
	return true;
}
