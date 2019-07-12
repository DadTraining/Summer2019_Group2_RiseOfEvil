#include "WorldScene1.h"
#include "MainMenuScene.h"
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

vector<Vec2> listPoint;
int i = 0;

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

	mTileMap = TMXTiledMap::create("res/MapScene/Map01.tmx");
	mTileMap->setAnchorPoint(Vec2(0, 0));
	mTileMap->setPosition(0, 0);
	addChild(mTileMap, 0);

	pause_bg = Sprite::create("res/WorldScene1/pause_bg.png");
	pause_bg->setScale(0.7);
	pause_bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(pause_bg, -1);

	auto pauseBtn = ui::Button::create("res/Buttons/WorldScene1/pauseBtn.png");
	pauseBtn->setScale(0.2);
	pauseBtn->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 50));
	pauseBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPause, this));
	addChild(pauseBtn, 1);

	resumeBtn = ui::Button::create("res/Buttons/WorldScene1/resumeBtn.png");
	resumeBtn->setScaleX(1.4);
	resumeBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 50));
	resumeBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeinPause, this));
	addChild(resumeBtn, -1);

	restartBtn = ui::Button::create("res/Buttons/WorldScene1/restartBtn.png");
	restartBtn->setScaleX(1.4);
	restartBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 20));
	//restartBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::FadeoutPasue, this));
	addChild(restartBtn, -1);

	mainmenuBtn = ui::Button::create("res/Buttons/WorldScene1/mainmenuBtn.png");
	mainmenuBtn->setScaleX(1.4);
	mainmenuBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 90));
	//mainmenuBtn->addTouchEventListener(CC_CALLBACK_0(WorldScene1::returnToMainMenu, this));
	addChild(mainmenuBtn, -1);

	SpriteBatchNode *spriteNode = SpriteBatchNode::create("Orc_Warrior_Walking.png");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Orc_Warrior_Walking.plist");
	monster = Sprite::createWithSpriteFrameName("Orc_Walking_1.png");
	this->addChild(spriteNode, 2);

	auto obj = mTileMap->getObjectGroup("Monster");
	float x = obj->getObject("monster")["x"].asInt();
	float y = obj->getObject("monster")["y"].asInt();

	auto walkingE = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 1, 10, 0.05f));
	walkingE->retain();
	monster->runAction(RepeatForever::create(walkingE));
	auto road = mTileMap->getObjectGroup("Point");
	tower = new Tower(this);
	auto body = PhysicsBody::createCircle(150, PHYSICSBODY_MATERIAL_DEFAULT);
	body->setDynamic(false);
	tower->GetSprite()->setPhysicsBody(body);
	//===========================================================================
	for (int i = 0; i < 15; i++)
	{
		float x = road->getObject("P" + to_string(i + 1))["x"].asInt();
		float y = road->getObject("P" + to_string(i + 1))["y"].asInt();
		listPoint.push_back(Vec2(x, y));
	}

	monster->setPosition(x, y);
	monster->setAnchorPoint(Vec2(0.5, 0.35));
	monster->setScale(0.6);
	spriteNode->addChild(monster);
	scheduleUpdate();
	return true;
}
cocos2d::Animation * WorldScene1::createAnimation(std::string prefixName, int pFrameBegin, int pFrameEnd, float delay)
{
	Vector<SpriteFrame*> animFrames;
	for (int i = pFrameBegin; i <= pFrameEnd; i++)
	{
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);

		std::string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}

	animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}

void WorldScene1::run(Vec2 point)
{

	int x = i - 1;
	if (x < 0)
	{
		x = 0;
	}

	if ((listPoint[x].y == listPoint[i].y) && (listPoint[x].x <= listPoint[i].x)) {
		action(E, monster);
	}
	else if ((listPoint[x].y == listPoint[i].y) && (listPoint[x].x >= listPoint[i].x)) {
		action(W, monster);
	}
	else if ((listPoint[x].x == listPoint[i].x) && (listPoint[x].y >= listPoint[i].y)) {
		action(S, monster);
	}
	else if ((listPoint[x].x <= listPoint[i].x) && (listPoint[x].y >= listPoint[i].y)) {
		action(SE, monster);
	}
	else if ((listPoint[x].x >= listPoint[i].x) && (listPoint[x].y >= listPoint[i].y)) {
		action(SW, monster);
	}
	else if ((listPoint[x].x <= listPoint[i].x) && (listPoint[x].y <= listPoint[i].y)) {
		action(NE, monster);
	}
	else
		action(NW, monster);

	auto v = listPoint[1].getDistance(listPoint[0]) / 1.0f;
	monster->runAction(MoveTo::create(listPoint[i].getDistance(monster->getPosition()) / v * 2, Vec2(point.x, point.y)));
}
void WorldScene1::action(int direction, Sprite *monster)
{
	switch (direction)
	{
	case E:
	{
		monster->stopAllActions();
		auto walkingE = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 1, 10, 0.05f));
		walkingE->retain();
		monster->runAction(RepeatForever::create(walkingE));
		break;
	}

	case W:
	{
		monster->stopAllActions();
		auto walkingW = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 71, 80, 0.05f));
		walkingW->retain();
		monster->runAction(RepeatForever::create(walkingW));
		break;
	}

	case S:
	{
		monster->stopAllActions();
		auto walkingS = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 41, 50, 0.05f));
		walkingS->retain();
		monster->runAction(RepeatForever::create(walkingS));
		break;
	}

	case N:
	{
		monster->stopAllActions();
		auto walkingN = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 11, 20, 0.05f));
		walkingN->retain();
		monster->runAction(RepeatForever::create(walkingN));
		break;
	}

	case SE:
	{
		monster->stopAllActions();
		auto walkingSE = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 51, 60, 0.05f));
		walkingSE->retain();
		monster->runAction(RepeatForever::create(walkingSE));
		break;
	}

	case SW:
	{
		monster->stopAllActions();
		auto walkingSW = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 61, 70, 0.05f));
		walkingSW->retain();
		monster->runAction(RepeatForever::create(walkingSW));
		break;
	}

	case NE:
	{
		monster->stopAllActions();
		auto walkingNE = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 21, 30, 0.05f));
		walkingNE->retain();
		monster->runAction(RepeatForever::create(walkingNE));
		break;
	}

	case NW:
	{
		monster->stopAllActions();
		auto walkingNW = Animate::create(WorldScene1::createAnimation("Orc_Walking_", 31, 40, 0.05f));
		walkingNW->retain();
		monster->runAction(RepeatForever::create(walkingNW));
		break;
	}

	}
}


void WorldScene1::update(float deltaTime)
{
	float x = monster->getPositionX();
	float y = monster->getPositionY();

	if (tower->Update(deltaTime, x, y) == 1)
	{
		//monster->setVisible(false);
		//monster->removeFromParent();
		//monster->release();
	}
	float f = 1.0f;
	//==========================================
	if (listPoint[i].getDistance(monster->getPosition()) == 0)
	{
		if (i < listPoint.size() - 1)
		{
			i++;
		}
		run(listPoint[i]);
	}
}


void WorldScene1::FadeinPause()
{
	Director::getInstance()->resume();
	pause_bg->setZOrder(-1);
	restartBtn->setZOrder(-1);
	resumeBtn->setZOrder(-1);
	mainmenuBtn->setZOrder(-1);
}

void WorldScene1::FadeoutPause()
{
	Director::getInstance()->pause();
	pause_bg->setZOrder(10);
	restartBtn->setZOrder(12);
	resumeBtn->setZOrder(11);
	mainmenuBtn->setZOrder(13);
}

//void WorldScene1::returnToMainMenu()
//{
//	Scene *pScene = MainMenuScene::create();
//	TransitionFade *crssfade = TransitionFade::create(1, pScene);
//	Director::getInstance()->replaceScene(crssfade);
//}



