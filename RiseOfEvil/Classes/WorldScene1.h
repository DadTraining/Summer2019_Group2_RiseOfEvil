#pragma once
#include "cocos2d.h"

class WorldScene1 : public cocos2d::Scene
{
private:
	cocos2d::TMXTiledMap* mTileMap;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float deltaTime);
	CREATE_FUNC(WorldScene1);
	void FadeinPause();
	void FadeoutPause();
};