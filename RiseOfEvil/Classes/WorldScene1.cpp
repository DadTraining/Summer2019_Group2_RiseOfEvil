#include "WorldScene1.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* WorldScene1::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = WorldScene1::create();
	scene->addChild(layer);
	return scene;
}

bool WorldScene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	mTileMap = TMXTiledMap::create("res/WorldScene1/Map01.tmx");
	mTileMap->setAnchorPoint(Vec2(0, 0));
	mTileMap->setPosition(0 - 960, 0 - 500);
	addChild(mTileMap, 1);


}

void WorldScene1::update(float deltaTime)
{
}


