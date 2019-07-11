//#pragma once
//#include "cocos2d.h"
//
//class WorldScene1 : public cocos2d::Scene
//{
//private:
//	cocos2d::TMXTiledMap* mTileMap;
//public:
//	static cocos2d::Scene* createScene();
//	virtual bool init();
//	void update(float deltaTime);
//	CREATE_FUNC(WorldScene1);
//};
//===================================================
#pragma once
#include "cocos2d.h"
#include "Tower.h"
#define E  1
#define W  2
#define S  3
#define N  4
#define SE 5
#define NE 6
#define NW 7
#define SW 8
using namespace cocos2d;

class WorldScene1 : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap* mTileMap;
	PhysicsBody *body;

	//cocos2d::Sprite *mole1;


public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	//float Distance(float xa, float ya, float xb, float yb);
	Sprite * monster;
	Animation *createAnimation(std::string prefixName, int pFrameBegin, int pFrameEnd, float delay);
	Animation *animation;
	int nextPoint;
	Tower * tower;
	//void createRange();
	void run(Vec2 point);
	void action(int direction, Sprite *);
	CREATE_FUNC(WorldScene1);
};