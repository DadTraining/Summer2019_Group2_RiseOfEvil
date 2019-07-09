#include "UpgradeScene.h"
#include "SimpleAudioEngine.h"
#include "WorldMapScene.h"
using namespace CocosDenshion;

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
	//Background
	background = Sprite::create("res/UpgradeScene/background.png");
	background->setScaleY(visibleSize.height / background->getContentSize().height);
	background->setScaleX(1.5f);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 500));
	background->runAction(MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	this->addChild(background, 0);
	//---------------------------------------------------------
	//Done button
	doneBtn = ui::Button::create("res/UpgradeScene/doneButton.png");
	doneBtn->setPosition(Vec2(visibleSize.width / 1.2, visibleSize.height / 14));
	doneBtn->addTouchEventListener(CC_CALLBACK_0(UpgradeScene::BackToWorldMapScene, this));
	this->addChild(doneBtn, 1);
	auto seq_show = Sequence::create(FadeOut::create(0), DelayTime::create(1), FadeIn::create(0), nullptr);
	doneBtn->runAction(seq_show);
	//---------------------------------------------------------
	//Init all options upgrade
	auto archer_lv1 = ui::Button::create("res/UpgradeScene/IncreaseRange_active.png");
	archer_lv1->setPosition(Vec2(visibleSize.width / 4.8, visibleSize.height / 2.5));
	archer_lv1->setScale(1.5f);
	archer_lv1->runAction(seq_show->clone());
	this->addChild(archer_lv1, 1);
	auto archer_lv2 = ui::Button::create("res/UpgradeScene/DecreaseGold_active.png");
	archer_lv2->setPosition(Vec2(visibleSize.width / 4.8, visibleSize.height / 1.7));
	archer_lv2->setScale(1.5f);
	archer_lv2->runAction(seq_show->clone());
	this->addChild(archer_lv2, 1);
	auto archer_lv3 = ui::Button::create("res/UpgradeScene/IncreaseDamage_active.png");
	archer_lv3->setPosition(Vec2(visibleSize.width / 4.8, visibleSize.height / 1.3));
	archer_lv3->setScale(1.5f);
	archer_lv3->runAction(seq_show->clone());
	this->addChild(archer_lv3, 1);
	//---------------------------------------------------------
	auto magic_lv1 = ui::Button::create("res/UpgradeScene/IncreaseRange_active.png");
	magic_lv1->setPosition(Vec2(visibleSize.width / 2.83, visibleSize.height / 2.5));
	magic_lv1->setScale(1.5f);
	magic_lv1->runAction(seq_show->clone());
	this->addChild(magic_lv1, 1);
	auto magic_lv2 = ui::Button::create("res/UpgradeScene/IncreaseDamage_active.png");
	magic_lv2->setPosition(Vec2(visibleSize.width / 2.83, visibleSize.height / 1.7));
	magic_lv2->setScale(1.5f);
	magic_lv2->runAction(seq_show->clone());
	this->addChild(magic_lv2, 1);
	auto magic_lv3 = ui::Button::create("res/UpgradeScene/Magic_Ignore_active.png");
	magic_lv3->setPosition(Vec2(visibleSize.width / 2.83, visibleSize.height / 1.3));
	magic_lv3->setScale(1.5f);
	magic_lv3->runAction(seq_show->clone());
	this->addChild(magic_lv3, 1);
	//---------------------------------------------------------
	auto barrack_lv1 = ui::Button::create("res/UpgradeScene/Barrack_Defend_Active.png");
	barrack_lv1->setPosition(Vec2(visibleSize.width / 1.99, visibleSize.height / 2.5));
	barrack_lv1->setScale(1.5f);
	barrack_lv1->runAction(seq_show->clone());
	this->addChild(barrack_lv1, 1);
	auto barrack_lv2 = ui::Button::create("res/UpgradeScene/Barrack_Hitpoint_Active.png");
	barrack_lv2->setPosition(Vec2(visibleSize.width / 1.99, visibleSize.height / 1.7));
	barrack_lv2->setScale(1.5f);
	barrack_lv2->runAction(seq_show->clone());
	this->addChild(barrack_lv2, 1);
	auto barrack_lv3 = ui::Button::create("res/UpgradeScene/Barrack_Trainner_active.png");
	barrack_lv3->setPosition(Vec2(visibleSize.width / 1.99, visibleSize.height / 1.3));
	barrack_lv3->setScale(1.5f);
	barrack_lv3->runAction(seq_show->clone());
	this->addChild(barrack_lv3, 1);
	//---------------------------------------------------------
	auto bombard_lv1 = ui::Button::create("res/UpgradeScene/IncreaseRange_active.png");
	bombard_lv1->setPosition(Vec2(visibleSize.width / 1.515, visibleSize.height / 2.5));
	bombard_lv1->setScale(1.5f);
	bombard_lv1->runAction(seq_show->clone());
	this->addChild(bombard_lv1, 1);
	auto bombard_lv2 = ui::Button::create("res/UpgradeScene/Boombard_AttackSpeed_active.png");
	bombard_lv2->setPosition(Vec2(visibleSize.width / 1.515, visibleSize.height / 1.7));
	bombard_lv2->setScale(1.5f);
	bombard_lv2->runAction(seq_show->clone());
	this->addChild(bombard_lv2, 1);
	auto bombard_lv3 = ui::Button::create("res/UpgradeScene/IncreaseDamage_active.png");
	bombard_lv3->setPosition(Vec2(visibleSize.width / 1.515, visibleSize.height / 1.3));
	bombard_lv3->setScale(1.5f);
	bombard_lv3->runAction(seq_show->clone());
	this->addChild(bombard_lv3, 1);
	//---------------------------------------------------------
	auto slow_lv1 = ui::Button::create("res/UpgradeScene/IncreaseRange_active.png");
	slow_lv1->setPosition(Vec2(visibleSize.width / 1.23, visibleSize.height / 2.5));
	slow_lv1->setScale(1.5f);
	slow_lv1->runAction(seq_show->clone());
	this->addChild(slow_lv1, 1);
	auto slow_lv2 = ui::Button::create("res/UpgradeScene/Slow_IncreaseSlow_active.png");
	slow_lv2->setPosition(Vec2(visibleSize.width / 1.23, visibleSize.height / 1.7));
	slow_lv2->setScale(1.5f);
	slow_lv2->runAction(seq_show->clone());
	this->addChild(slow_lv2, 1);
	auto slow_lv3 = ui::Button::create("res/UpgradeScene/Slow_Increase_active.png");
	slow_lv3->setPosition(Vec2(visibleSize.width / 1.23, visibleSize.height / 1.3));
	slow_lv3->setScale(1.5f);
	slow_lv3->runAction(seq_show->clone());
	this->addChild(slow_lv3, 1);
	//---------------------------------------------------------
	//Music for begin
	auto music_begin = SimpleAudioEngine::getInstance();
	music_begin->playEffect("res/UpgradeScene/Update_begin_sound.mp3", false);
	//---------------------------------------------------------
	return true;
}

void UpgradeScene::BackToWorldMapScene()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//---------------------------------------------------------
	background->runAction(MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height + 500)));
	//---------------------------------------------------------
	doneBtn->runAction(FadeOut::create(0.2));
	//---------------------------------------------------------
	//Music for end
	auto music_begin = SimpleAudioEngine::getInstance();
	music_begin->playEffect("res/UpgradeScene/Update_begin_sound.mp3", false);
	//---------------------------------------------------------
	Scene *pScene = WorldMapScene::create();
	TransitionFade *crssfade = TransitionFade::create(1, pScene);
	Director::getInstance()->replaceScene(crssfade);
}

