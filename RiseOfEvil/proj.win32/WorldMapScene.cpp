#include "UpgradeScene.h"
#include "ui/CocosGUI.h"
#include "WorldMapScene.h"
#include "WorldScene1.h"

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

	auto world_bg = Sprite::create("res/Sprites/WorldMapScene/worldscene_bg.jpg");
	world_bg->setScaleX(visibleSize.width / world_bg->getContentSize().width);
	world_bg->setScaleY(visibleSize.height / world_bg->getContentSize().height);
	world_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(world_bg);

	auto backBtn = ui::Button::create("res/Sprites/WorldMapScene/backBtn_normal.png", "res/Sprites/WorldMapScene/backBtn_pressed.png");
	backBtn->setScale(0.2);
	backBtn->setPosition(Vec2(100, 50));
	addChild(backBtn);

	auto upgradeBtn = ui::Button::create("res/Sprites/WorldMapScene/UpgradePressBtn.png", "res/Sprites/WorldMapScene/UpgradeNormalBtn.png");
	upgradeBtn->setPosition(Vec2(visibleSize.width - 150, 50));
	addChild(upgradeBtn);


	auto flagBtn1 = ui::Button::create("res/Sprites/WorldMapScene/flag_pressed.png", "res/Sprites/WorldMapScene/flag_normal.png");
	flagBtn1->setScale(0.2);
	flagBtn1->setAnchorPoint(Vec2(0.5, 0));
	flagBtn1->setPosition(Vec2(150, visibleSize.height - 150));
	flagBtn1->addTouchEventListener(CC_CALLBACK_0(WorldMapScene::GoToWorldScene1, this));
	addChild(flagBtn1);
	add_star(flagBtn1->getPosition(), 10);

	auto flagBtn2 = ui::Button::create("res/Sprites/WorldMapScene/flag_normal.png", "res/Sprites/WorldMapScene/flag_pressed.png");
	flagBtn2->setScale(0.2);
	flagBtn2->setAnchorPoint(Vec2(0.5, 0));
	flagBtn2->setPosition(Vec2(250, visibleSize.height - 450));
	flagBtn2->addClickEventListener([&](Ref* event) {
	});
	addChild(flagBtn2);
	add_star(flagBtn2->getPosition(), 10);

	auto flagBtn3 = ui::Button::create("res/Sprites/WorldMapScene/flag_normal.png", "res/Sprites/WorldMapScene/flag_pressed.png");
	flagBtn3->setScale(0.2);
	flagBtn3->setAnchorPoint(Vec2(0.5, 0));
	flagBtn3->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	flagBtn3->addClickEventListener([&](Ref* event) {
	});
	addChild(flagBtn3);
	add_star(flagBtn3->getPosition(), 10);

	auto flagBtn4 = ui::Button::create("res/Sprites/WorldMapScene/flag_normal.png", "res/Sprites/WorldMapScene/flag_pressed.png");
	flagBtn4->setScale(0.2);
	flagBtn4->setAnchorPoint(Vec2(0.5, 0));
	flagBtn4->setPosition(Vec2(visibleSize.width - 250, visibleSize.height - 150));
	addChild(flagBtn4);
	add_star(flagBtn4->getPosition(), 10);

	auto flagBtn5 = ui::Button::create("res/Sprites/WorldMapScene/flag_normal.png", "res/Sprites/WorldMapScene/flag_pressed.png");
	flagBtn5->setScale(0.2);
	flagBtn5->setAnchorPoint(Vec2(0.5, 0));
	flagBtn5->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 450));
	flagBtn5->addClickEventListener([&](Ref* event) {
	});
	addChild(flagBtn5);
	add_star(flagBtn5->getPosition(), 10);


	return true;
}

void WorldMapScene::add_star(Vec2 vec, int score)
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

void WorldMapScene::GoToWorldScene1()
{
	Scene *pScene = WorldScene1::create();
	TransitionFade *crssfade = TransitionFade::create(1, pScene);
	Director::getInstance()->replaceScene(crssfade);
}
